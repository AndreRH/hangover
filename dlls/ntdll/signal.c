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
#include "ntdll.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
#include <winternl.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif

#ifdef QEMU_DLL_GUEST

NTSYSAPI EXCEPTION_DISPOSITION WINAPI __C_specific_handler(EXCEPTION_RECORD *rec,
        ULONG64 frame, CONTEXT *context, struct _DISPATCHER_CONTEXT *dispatch)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL___C_SPECIFIC_HANDLER);

    qemu_syscall(&call);

    return call.iret;
}

#else

void qemu___C_specific_handler(struct qemu_syscall *call)
{
    WINE_FIXME("Stub!\n");
    call->iret = ExceptionContinueSearch;
}

#endif

struct qemu_RtlAddFunctionTable
{
    struct qemu_syscall super;
    uint64_t func;
    uint64_t entry_count;
    uint64_t base;
};


#ifdef QEMU_DLL_GUEST

#define __ASM_DEFINE_FUNC(name,suffix,code) asm(".text\n\t.align 4\n\t.globl " #name suffix "\n\t.def " #name suffix "; .scl 2; .type 32; .endef\n" #name suffix ":\n\t.cfi_startproc\n\t" code "\n\t.cfi_endproc")
#define __ASM_STDCALL(args)
#define __ASM_STDCALL_FUNC(name,args,code) __ASM_DEFINE_FUNC(name,__ASM_STDCALL(args),code)
__ASM_STDCALL_FUNC( DbgBreakPoint, 0, "int $3; ret");

#endif

#ifdef QEMU_DLL_GUEST

NTSYSAPI BOOLEAN CDECL RtlAddFunctionTable(PRUNTIME_FUNCTION func, DWORD entry_count, DWORD64 base)
{
    struct qemu_RtlAddFunctionTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLADDFUNCTIONTABLE);
    call.func = (uint64_t)func;
    call.entry_count = entry_count;
    call.base = base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAddFunctionTable(struct qemu_syscall *call)
{
    struct qemu_RtlAddFunctionTable *c = (struct qemu_RtlAddFunctionTable *)call;
    WINE_FIXME("(%p, %lu, %#lx) Stub!\n", QEMU_G2H(c->func), c->entry_count, c->base);
    c->super.iret = FALSE;
}

#endif

#ifdef QEMU_DLL_GUEST

/* We'll want to copypaste the assembler version from Wine and handle this entirely
 * inside the guest lib. This call out of the emulator is only there to print a
 * FIXME. */
NTSYSAPI void NTAPI RtlCaptureContext(CONTEXT *context)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_RTLCAPTURECONTEXT);
    qemu_syscall(&call);
}

#else

void qemu_RtlCaptureContext(struct qemu_syscall *call)
{
    WINE_FIXME("Stub!\n");
}

#endif

#ifdef QEMU_DLL_GUEST

/* This will probably have to cooperate with the qemu PE loader. */
NTSYSAPI PRUNTIME_FUNCTION NTAPI RtlLookupFunctionEntry(DWORD64 pc, DWORD64 *base, UNWIND_HISTORY_TABLE *history)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_RTLLOOKUPFUNCTIONENTRY);

    qemu_syscall(&call);

    return NULL;
}

#else

void qemu_RtlLookupFunctionEntry(struct qemu_syscall *call)
{
    WINE_FIXME("Stub!\n");
}

#endif

#ifdef QEMU_DLL_GUEST

NTSYSAPI PEXCEPTION_ROUTINE NTAPI RtlVirtualUnwind(DWORD type, DWORD64 image, DWORD64 pc, PRUNTIME_FUNCTION function,
        CONTEXT *context, void **data, DWORD64 *frame, KNONVOLATILE_CONTEXT_POINTERS *pointers)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_RTLVIRTUALUNWIND);

    qemu_syscall(&call);

    return NULL;
}

#else

void qemu_RtlVirtualUnwind(struct qemu_syscall *call)
{
    WINE_FIXME("Stub!\n");
}

#endif
