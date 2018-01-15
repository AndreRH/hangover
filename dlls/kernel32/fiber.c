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
#include <winternl.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_CreateFiber
{
    struct qemu_syscall super;
    uint64_t stack;
    uint64_t start;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI CreateFiber(SIZE_T stack, LPFIBER_START_ROUTINE start, LPVOID param)
{
    struct qemu_CreateFiber call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFIBER);
    call.stack = stack;
    call.start = (ULONG_PTR)start;
    call.param = (ULONG_PTR)param;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateFiber(struct qemu_syscall *call)
{
    struct qemu_CreateFiber *c = (struct qemu_CreateFiber *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CreateFiber(c->stack, QEMU_G2H(c->start), QEMU_G2H(c->param)));
}

#endif

struct qemu_CreateFiberEx
{
    struct qemu_syscall super;
    uint64_t stack_commit;
    uint64_t stack_reserve;
    uint64_t flags;
    uint64_t start;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI CreateFiberEx(SIZE_T stack_commit, SIZE_T stack_reserve, DWORD flags, LPFIBER_START_ROUTINE start, LPVOID param)
{
    struct qemu_CreateFiberEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEFIBEREX);
    call.stack_commit = stack_commit;
    call.stack_reserve = stack_reserve;
    call.flags = flags;
    call.start = (ULONG_PTR)start;
    call.param = (ULONG_PTR)param;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateFiberEx(struct qemu_syscall *call)
{
    struct qemu_CreateFiberEx *c = (struct qemu_CreateFiberEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(CreateFiberEx(c->stack_commit, c->stack_reserve, c->flags, QEMU_G2H(c->start), QEMU_G2H(c->param)));
}

#endif

struct qemu_DeleteFiber
{
    struct qemu_syscall super;
    uint64_t fiber_ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI DeleteFiber(LPVOID fiber_ptr)
{
    struct qemu_DeleteFiber call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEFIBER);
    call.fiber_ptr = (ULONG_PTR)fiber_ptr;

    qemu_syscall(&call.super);
}

#else

void qemu_DeleteFiber(struct qemu_syscall *call)
{
    struct qemu_DeleteFiber *c = (struct qemu_DeleteFiber *)call;
    WINE_FIXME("Unverified!\n");
    DeleteFiber(QEMU_G2H(c->fiber_ptr));
}

#endif

struct qemu_ConvertThreadToFiber
{
    struct qemu_syscall super;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI ConvertThreadToFiber(LPVOID param)
{
    struct qemu_ConvertThreadToFiber call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTTHREADTOFIBER);
    call.param = (ULONG_PTR)param;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ConvertThreadToFiber(struct qemu_syscall *call)
{
    struct qemu_ConvertThreadToFiber *c = (struct qemu_ConvertThreadToFiber *)call;
    WINE_FIXME("Unverified!\n");
    /* FIXME: May need to update FlsSlots */
    c->super.iret = QEMU_H2G(ConvertThreadToFiber(QEMU_G2H(c->param)));
}

#endif

struct qemu_ConvertThreadToFiberEx
{
    struct qemu_syscall super;
    uint64_t param;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI ConvertThreadToFiberEx(LPVOID param, DWORD flags)
{
    struct qemu_ConvertThreadToFiberEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTTHREADTOFIBEREX);
    call.param = (ULONG_PTR)param;
    call.flags = flags;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ConvertThreadToFiberEx(struct qemu_syscall *call)
{
    struct qemu_ConvertThreadToFiberEx *c = (struct qemu_ConvertThreadToFiberEx *)call;
    WINE_FIXME("Unverified!\n");
    /* FIXME: May need to update FlsSlots. */
    c->super.iret = QEMU_H2G(ConvertThreadToFiberEx(QEMU_G2H(c->param), c->flags));
}

#endif

struct qemu_ConvertFiberToThread
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ConvertFiberToThread(void)
{
    struct qemu_ConvertFiberToThread call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CONVERTFIBERTOTHREAD);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ConvertFiberToThread(struct qemu_syscall *call)
{
    struct qemu_ConvertFiberToThread *c = (struct qemu_ConvertFiberToThread *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ConvertFiberToThread();
}

#endif

struct qemu_SwitchToFiber
{
    struct qemu_syscall super;
    uint64_t fiber;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI SwitchToFiber(LPVOID fiber)
{
    struct qemu_SwitchToFiber call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SWITCHTOFIBER);
    call.fiber = (ULONG_PTR)fiber;

    qemu_syscall(&call.super);
}

#else

void qemu_SwitchToFiber(struct qemu_syscall *call)
{
    struct qemu_SwitchToFiber *c = (struct qemu_SwitchToFiber *)call;
    WINE_FIXME("Unverified!\n");
    /* FIXME: May need to update FlsSlots. */
    SwitchToFiber(QEMU_G2H(c->fiber));
}

#endif

struct qemu_FlsAlloc
{
    struct qemu_syscall super;
    uint64_t callback;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI FlsAlloc(PFLS_CALLBACK_FUNCTION callback)
{
    struct qemu_FlsAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLSALLOC);
    call.callback = (ULONG_PTR)callback;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlsAlloc(struct qemu_syscall *call)
{
    TEB *guest_teb = qemu_ops->qemu_getTEB(), *host_teb = NtCurrentTeb();
    TEB32 *guest_teb32 = qemu_ops->qemu_getTEB32();

    struct qemu_FlsAlloc *c = (struct qemu_FlsAlloc *)call;
    WINE_TRACE("\n");
    c->super.iret = FlsAlloc(QEMU_G2H(c->callback));

    guest_teb->FlsSlots = host_teb->FlsSlots;
    if (guest_teb32)
        guest_teb32->FlsSlots = (ULONG_PTR)host_teb->FlsSlots;
}

#endif

struct qemu_FlsFree
{
    struct qemu_syscall super;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FlsFree(DWORD index)
{
    struct qemu_FlsFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FLSFREE);
    call.index = index;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FlsFree(struct qemu_syscall *call)
{
    struct qemu_FlsFree *c = (struct qemu_FlsFree *)call;
    WINE_TRACE("\n");
    c->super.iret = FlsFree(c->index);
}

#endif

struct qemu_FlsGetValue
{
    struct qemu_syscall super;
    uint64_t index;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PVOID WINAPI FlsGetValue(DWORD index)
{
    myTEB *teb = (myTEB *)NtCurrentTeb();

    /* Copypasted from Wine. */
    if (!index || index >= 8 * sizeof(teb->Peb->FlsBitmapBits) || !teb->FlsSlots)
    {
        kernel32_SetLastError( ERROR_INVALID_PARAMETER );
        return NULL;
    }
    kernel32_SetLastError( ERROR_SUCCESS );
    return teb->FlsSlots[index];
}

#else

void qemu_FlsGetValue(struct qemu_syscall *call)
{
    struct qemu_FlsGetValue *c = (struct qemu_FlsGetValue *)call;
    WINE_TRACE("\n");
}

#endif

struct qemu_FlsSetValue
{
    struct qemu_syscall super;
    uint64_t index;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FlsSetValue(DWORD index, PVOID data)
{
    myTEB *teb = (myTEB *)NtCurrentTeb();

    if (!index || index >= 8 * sizeof(teb->Peb->FlsBitmapBits))
    {
        kernel32_SetLastError( ERROR_INVALID_PARAMETER );
        return FALSE;
    }
    if (!teb->FlsSlots)
    {
        struct qemu_FlsSetValue call;
        call.super.id = QEMU_SYSCALL_ID(CALL_FLSSETVALUE);
        call.index = index;
        call.data = (ULONG_PTR)data;

        qemu_syscall(&call.super);

        /* On a 64 bit system we're done here. On a 32 bit system, native FlsSetValue
         * wrote the value to the wrong offset, so we have to set it again. Also set
         * the "wrong" value back to 0 to avoid initializing index * 2 to something
         * wrong. */
#if GUEST_BIT == HOST_BIT
        return call.super.iret;
#else
        call.data = 0;
        qemu_syscall(&call.super);
#endif
    }
    teb->FlsSlots[index] = data;
    return TRUE;
}

#else

void qemu_FlsSetValue(struct qemu_syscall *call)
{
    TEB *guest_teb = qemu_ops->qemu_getTEB(), *host_teb = NtCurrentTeb();
    TEB32 *guest_teb32 = qemu_ops->qemu_getTEB32();
    struct qemu_FlsSetValue *c = (struct qemu_FlsSetValue *)call;
    WINE_TRACE("\n");

    c->super.iret = FlsSetValue(c->index, QEMU_G2H(c->data));
    guest_teb->FlsSlots = host_teb->FlsSlots;
    if (guest_teb32)
        guest_teb32->FlsSlots = (ULONG_PTR)host_teb->FlsSlots;
}

#endif

struct qemu_IsThreadAFiber
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IsThreadAFiber(void)
{
    struct qemu_IsThreadAFiber call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISTHREADAFIBER);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IsThreadAFiber to Wine headers? */
extern BOOL WINAPI IsThreadAFiber(void);
void qemu_IsThreadAFiber(struct qemu_syscall *call)
{
    struct qemu_IsThreadAFiber *c = (struct qemu_IsThreadAFiber *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IsThreadAFiber();
}

#endif

