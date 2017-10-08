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

/* Looks like mingw's werapi.h is broken. */
#ifdef QEMU_DLL_GUEST
typedef HANDLE HREPORT;
typedef void *PWER_SUBMIT_RESULT;
#define WER_MAX_PREFERRED_MODULES_BUFFER    256
#endif
#include <werapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_WerRegisterFile
{
    struct qemu_syscall super;
    uint64_t file;
    uint64_t regfiletype;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WerRegisterFile(PCWSTR file, WER_REGISTER_FILE_TYPE regfiletype, DWORD flags)
{
    struct qemu_WerRegisterFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WERREGISTERFILE);
    call.file = (ULONG_PTR)file;
    call.regfiletype = (ULONG_PTR)regfiletype;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WerRegisterFile(struct qemu_syscall *call)
{
    struct qemu_WerRegisterFile *c = (struct qemu_WerRegisterFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WerRegisterFile(QEMU_G2H(c->file), c->regfiletype, c->flags);
}

#endif

struct qemu_WerRegisterRuntimeExceptionModule
{
    struct qemu_syscall super;
    uint64_t callbackdll;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WerRegisterRuntimeExceptionModule(PCWSTR callbackdll, PVOID context)
{
    struct qemu_WerRegisterRuntimeExceptionModule call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WERREGISTERRUNTIMEEXCEPTIONMODULE);
    call.callbackdll = (ULONG_PTR)callbackdll;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WerRegisterRuntimeExceptionModule(struct qemu_syscall *call)
{
    struct qemu_WerRegisterRuntimeExceptionModule *c = (struct qemu_WerRegisterRuntimeExceptionModule *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WerRegisterRuntimeExceptionModule(QEMU_G2H(c->callbackdll), QEMU_G2H(c->context));
}

#endif

struct qemu_WerSetFlags
{
    struct qemu_syscall super;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WerSetFlags(DWORD flags)
{
    struct qemu_WerSetFlags call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WERSETFLAGS);
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WerSetFlags(struct qemu_syscall *call)
{
    struct qemu_WerSetFlags *c = (struct qemu_WerSetFlags *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WerSetFlags(c->flags);
}

#endif

struct qemu_WerRegisterMemoryBlock
{
    struct qemu_syscall super;
    uint64_t block;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WerRegisterMemoryBlock(void *block, DWORD size)
{
    struct qemu_WerRegisterMemoryBlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WERREGISTERMEMORYBLOCK);
    call.block = (ULONG_PTR)block;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WerRegisterMemoryBlock(struct qemu_syscall *call)
{
    struct qemu_WerRegisterMemoryBlock *c = (struct qemu_WerRegisterMemoryBlock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WerRegisterMemoryBlock(QEMU_G2H(c->block), c->size);
}

#endif

struct qemu_WerUnregisterMemoryBlock
{
    struct qemu_syscall super;
    uint64_t block;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WerUnregisterMemoryBlock(void *block)
{
    struct qemu_WerUnregisterMemoryBlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WERUNREGISTERMEMORYBLOCK);
    call.block = (ULONG_PTR)block;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WerUnregisterMemoryBlock(struct qemu_syscall *call)
{
    struct qemu_WerUnregisterMemoryBlock *c = (struct qemu_WerUnregisterMemoryBlock *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WerUnregisterMemoryBlock(QEMU_G2H(c->block));
}

#endif

