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

#include "thunk/qemu_windows.h"
#include "thunk/qemu_winternl.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifdef QEMU_DLL_GUEST

/* I can't make mingw's ddk headers work :-( . */

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_RtlCreateActivationContext
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCreateActivationContext(HANDLE *handle, const void *ptr)
{
    struct qemu_RtlCreateActivationContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATEACTIVATIONCONTEXT);
    call.handle = (ULONG_PTR)handle;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateActivationContext(struct qemu_syscall *call)
{
    struct qemu_RtlCreateActivationContext *c = (struct qemu_RtlCreateActivationContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCreateActivationContext(QEMU_G2H(c->handle), QEMU_G2H(c->ptr));
}

#endif

struct qemu_RtlAddRefActivationContext
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlAddRefActivationContext(HANDLE handle)
{
    struct qemu_RtlAddRefActivationContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDREFACTIVATIONCONTEXT);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlAddRefActivationContext(struct qemu_syscall *call)
{
    struct qemu_RtlAddRefActivationContext *c = (struct qemu_RtlAddRefActivationContext *)call;
    WINE_FIXME("Unverified!\n");
    RtlAddRefActivationContext(QEMU_G2H(c->handle));
}

#endif

struct qemu_RtlReleaseActivationContext
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlReleaseActivationContext(HANDLE handle)
{
    struct qemu_RtlReleaseActivationContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLRELEASEACTIVATIONCONTEXT);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlReleaseActivationContext(struct qemu_syscall *call)
{
    struct qemu_RtlReleaseActivationContext *c = (struct qemu_RtlReleaseActivationContext *)call;
    WINE_FIXME("Unverified!\n");
    RtlReleaseActivationContext(QEMU_G2H(c->handle));
}

#endif

struct qemu_RtlZombifyActivationContext
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlZombifyActivationContext(HANDLE handle)
{
    struct qemu_RtlZombifyActivationContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLZOMBIFYACTIVATIONCONTEXT);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlZombifyActivationContext(struct qemu_syscall *call)
{
    struct qemu_RtlZombifyActivationContext *c = (struct qemu_RtlZombifyActivationContext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlZombifyActivationContext(QEMU_G2H(c->handle));
}

#endif

struct qemu_RtlActivateActivationContext
{
    struct qemu_syscall super;
    uint64_t unknown;
    uint64_t handle;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlActivateActivationContext(ULONG unknown, HANDLE handle, PULONG_PTR cookie)
{
    struct qemu_RtlActivateActivationContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLACTIVATEACTIVATIONCONTEXT);
    call.unknown = (ULONG_PTR)unknown;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);
    *cookie = call.cookie;

    return call.super.iret;
}

#else

void qemu_RtlActivateActivationContext(struct qemu_syscall *call)
{
    struct qemu_RtlActivateActivationContext *c = (struct qemu_RtlActivateActivationContext *)call;
    ULONG_PTR cookie;
    WINE_FIXME("Unverified!\n");

    c->super.iret = RtlActivateActivationContext(c->unknown, QEMU_G2H(c->handle), &cookie);
    c->cookie = cookie;
}

#endif

struct qemu_RtlDeactivateActivationContext
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t cookie;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlDeactivateActivationContext(ULONG flags, ULONG_PTR cookie)
{
    struct qemu_RtlDeactivateActivationContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDEACTIVATEACTIVATIONCONTEXT);
    call.flags = flags;
    call.cookie = cookie;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlDeactivateActivationContext(struct qemu_syscall *call)
{
    struct qemu_RtlDeactivateActivationContext *c = (struct qemu_RtlDeactivateActivationContext *)call;
    WINE_FIXME("Unverified!\n");
    RtlDeactivateActivationContext(c->flags, c->cookie);
}

#endif

struct qemu_RtlFreeThreadActivationContextStack
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlFreeThreadActivationContextStack(void)
{
    struct qemu_RtlFreeThreadActivationContextStack call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFREETHREADACTIVATIONCONTEXTSTACK);

    qemu_syscall(&call.super);
}

#else

void qemu_RtlFreeThreadActivationContextStack(struct qemu_syscall *call)
{
    struct qemu_RtlFreeThreadActivationContextStack *c = (struct qemu_RtlFreeThreadActivationContextStack *)call;
    WINE_FIXME("Unverified!\n");
    RtlFreeThreadActivationContextStack();
}

#endif

struct qemu_RtlGetActiveActivationContext
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetActiveActivationContext(HANDLE *handle)
{
    struct qemu_RtlGetActiveActivationContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETACTIVEACTIVATIONCONTEXT);

    qemu_syscall(&call.super);
    *handle = (HANDLE)(ULONG_PTR)call.handle;

    return call.super.iret;
}

#else

void qemu_RtlGetActiveActivationContext(struct qemu_syscall *call)
{
    struct qemu_RtlGetActiveActivationContext *c = (struct qemu_RtlGetActiveActivationContext *)call;
    HANDLE handle;
    WINE_FIXME("Unverified!\n");

    c->super.iret = RtlGetActiveActivationContext(&handle);
    c->handle = QEMU_H2G(handle);
}

#endif

struct qemu_RtlIsActivationContextActive
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlIsActivationContextActive(HANDLE handle)
{
    struct qemu_RtlIsActivationContextActive call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLISACTIVATIONCONTEXTACTIVE);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlIsActivationContextActive(struct qemu_syscall *call)
{
    struct qemu_RtlIsActivationContextActive *c = (struct qemu_RtlIsActivationContextActive *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIsActivationContextActive(QEMU_G2H(c->handle));
}

#endif

struct qemu_RtlQueryInformationActivationContext
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t handle;
    uint64_t subinst;
    uint64_t class;
    uint64_t buffer;
    uint64_t bufsize;
    uint64_t retlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlQueryInformationActivationContext(ULONG flags, HANDLE handle, PVOID subinst, ULONG class, PVOID buffer, SIZE_T bufsize, SIZE_T *retlen)
{
    struct qemu_RtlQueryInformationActivationContext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLQUERYINFORMATIONACTIVATIONCONTEXT);
    call.flags = (ULONG_PTR)flags;
    call.handle = (ULONG_PTR)handle;
    call.subinst = (ULONG_PTR)subinst;
    call.class = (ULONG_PTR)class;
    call.buffer = (ULONG_PTR)buffer;
    call.bufsize = (ULONG_PTR)bufsize;
    call.retlen = (ULONG_PTR)retlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlQueryInformationActivationContext(struct qemu_syscall *call)
{
    struct qemu_RtlQueryInformationActivationContext *c = (struct qemu_RtlQueryInformationActivationContext *)call;
    WINE_FIXME("Unverified!\n");
    /* FIXME: Copy the code from kernel32 here and make kernel32 call this function on the guest side. */
    c->super.iret = RtlQueryInformationActivationContext(c->flags, QEMU_G2H(c->handle), QEMU_G2H(c->subinst), c->class, QEMU_G2H(c->buffer), c->bufsize, QEMU_G2H(c->retlen));
}

#endif

struct qemu_RtlFindActivationContextSectionString
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t guid;
    uint64_t section_kind;
    uint64_t section_name;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlFindActivationContextSectionString(ULONG flags, const GUID *guid, ULONG section_kind, const UNICODE_STRING *section_name, PVOID ptr)
{
    struct qemu_RtlFindActivationContextSectionString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDACTIVATIONCONTEXTSECTIONSTRING);
    call.flags = (ULONG_PTR)flags;
    call.guid = (ULONG_PTR)guid;
    call.section_kind = (ULONG_PTR)section_kind;
    call.section_name = (ULONG_PTR)section_name;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindActivationContextSectionString(struct qemu_syscall *call)
{
    struct qemu_RtlFindActivationContextSectionString *c = (struct qemu_RtlFindActivationContextSectionString *)call;
    struct qemu_ACTCTX_SECTION_KEYED_DATA *guest_info;
    ACTCTX_SECTION_KEYED_DATA stack, *info = &stack;
    UNICODE_STRING stack_str, *section = &stack_str;
    WINE_TRACE("\n");

    /* I duplicating this between kernel32 and ntdll because of the different UNICODE_STRING handling
     * (minor issue) and A<->W conversion, which I prefer to leave up to Wine's kernel32. */

#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->ptr);
    section = QEMU_G2H(c->section_name);
#else
    guest_info = QEMU_G2H(c->ptr);
    if (guest_info)
    {
        if (guest_info->cbSize < offsetof(struct qemu_ACTCTX_SECTION_KEYED_DATA, ulAssemblyRosterIndex))
            info->cbSize = 0;
        else
            ACTCTX_SECTION_KEYED_DATA_g2h(info, guest_info);
    }
    else
    {
        info = NULL;
    }

    if (QEMU_G2H(c->section_name))
        UNICODE_STRING_g2h(section, QEMU_G2H(c->section_name));
    else
        section = NULL;
#endif

    c->super.iret = RtlFindActivationContextSectionString(c->flags, QEMU_G2H(c->guid), c->section_kind,
            section, info);

#if GUEST_BIT != HOST_BIT
    if (info && !c->super.iret)
        ACTCTX_SECTION_KEYED_DATA_h2g(guest_info, info);
#endif
}

#endif

struct qemu_RtlFindActivationContextSectionGuid
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t extguid;
    uint64_t section_kind;
    uint64_t guid;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlFindActivationContextSectionGuid(ULONG flags, const GUID *extguid, ULONG section_kind, const GUID *guid, void *ptr)
{
    struct qemu_RtlFindActivationContextSectionGuid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDACTIVATIONCONTEXTSECTIONGUID);
    call.flags = (ULONG_PTR)flags;
    call.extguid = (ULONG_PTR)extguid;
    call.section_kind = (ULONG_PTR)section_kind;
    call.guid = (ULONG_PTR)guid;
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindActivationContextSectionGuid(struct qemu_syscall *call)
{
    struct qemu_RtlFindActivationContextSectionGuid *c = (struct qemu_RtlFindActivationContextSectionGuid *)call;
    WINE_FIXME("Unverified!\n");
    /* This could be moved from kernel32. */
    c->super.iret = RtlFindActivationContextSectionGuid(c->flags, QEMU_G2H(c->extguid), c->section_kind, QEMU_G2H(c->guid), QEMU_G2H(c->ptr));
}

#endif

