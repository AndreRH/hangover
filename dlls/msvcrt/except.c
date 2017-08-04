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
#include <signal.h>
#include <setjmp.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

#ifdef QEMU_DLL_GUEST

EXCEPTION_DISPOSITION CDECL __CxxFrameHandler(EXCEPTION_RECORD *rec, ULONG64 frame,
        CONTEXT *context, DISPATCHER_CONTEXT *dispatch)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL___CXXFRAMEHANDLER);

    qemu_syscall(&call);

    return 0;
}

#else

void qemu___cxxframehandler(struct qemu_syscall *c)
{
    WINE_FIXME("Stub!\n");
}

#endif

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__setjmp_log()
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL__SETJMP);

    qemu_syscall(&call);
}

#define __ASM_NAME(name) name
#define __ASM_DEFINE_FUNC(name,suffix,code) asm(".text\n\t.align 4\n\t.globl " #name suffix "\n\t.def " #name suffix "; .scl 2; .type 32; .endef\n" #name suffix ":\n\t.cfi_startproc\n\t" code "\n\t.cfi_endproc");
#define __ASM_GLOBAL_FUNC(name,code) __ASM_DEFINE_FUNC(name,"",code)

__ASM_GLOBAL_FUNC( MSVCRT__setjmp,
                   "jmp " __ASM_NAME("MSVCRT__setjmpex") );

__ASM_GLOBAL_FUNC( MSVCRT__setjmpex,
                   "subq $0x28,%rsp\n\t"
                   "movq %rcx,0x20(%rsp)\n\t"
                   "call " __ASM_NAME("MSVCRT__setjmp_log") "\n\t"
                   "movq 0x20(%rsp),%rcx\n\t"
                   "addq $0x28,%rsp\n\t"
                   "movq %rdx,(%rcx)\n\t"          /* jmp_buf->Frame */
                   "movq %rbx,0x8(%rcx)\n\t"       /* jmp_buf->Rbx */
                   "leaq 0x8(%rsp),%rax\n\t"
                   "movq %rax,0x10(%rcx)\n\t"      /* jmp_buf->Rsp */
                   "movq %rbp,0x18(%rcx)\n\t"      /* jmp_buf->Rbp */
                   "movq %rsi,0x20(%rcx)\n\t"      /* jmp_buf->Rsi */
                   "movq %rdi,0x28(%rcx)\n\t"      /* jmp_buf->Rdi */
                   "movq %r12,0x30(%rcx)\n\t"      /* jmp_buf->R12 */
                   "movq %r13,0x38(%rcx)\n\t"      /* jmp_buf->R13 */
                   "movq %r14,0x40(%rcx)\n\t"      /* jmp_buf->R14 */
                   "movq %r15,0x48(%rcx)\n\t"      /* jmp_buf->R15 */
                   "movq (%rsp),%rax\n\t"
                   "movq %rax,0x50(%rcx)\n\t"      /* jmp_buf->Rip */
                   "movdqa %xmm6,0x60(%rcx)\n\t"   /* jmp_buf->Xmm6 */
                   "movdqa %xmm7,0x70(%rcx)\n\t"   /* jmp_buf->Xmm7 */
                   "movdqa %xmm8,0x80(%rcx)\n\t"   /* jmp_buf->Xmm8 */
                   "movdqa %xmm9,0x90(%rcx)\n\t"   /* jmp_buf->Xmm9 */
                   "movdqa %xmm10,0xa0(%rcx)\n\t"  /* jmp_buf->Xmm10 */
                   "movdqa %xmm11,0xb0(%rcx)\n\t"  /* jmp_buf->Xmm11 */
                   "movdqa %xmm12,0xc0(%rcx)\n\t"  /* jmp_buf->Xmm12 */
                   "movdqa %xmm13,0xd0(%rcx)\n\t"  /* jmp_buf->Xmm13 */
                   "movdqa %xmm14,0xe0(%rcx)\n\t"  /* jmp_buf->Xmm14 */
                   "movdqa %xmm15,0xf0(%rcx)\n\t"  /* jmp_buf->Xmm15 */
                   "xorq %rax,%rax\n\t"
                   "retq" );

#else

void qemu__setjmp(struct qemu_syscall *c)
{
    /* Only called for the purpose of writing something in the trace. */
    WINE_FIXME("\n");
}

#endif

#ifdef QEMU_DLL_GUEST

int __cdecl MSVCRT__XcptFilter(unsigned long exception_num, struct _EXCEPTION_POINTERS *ptr)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL__XCPTFILTER);

    qemu_syscall(&call);

    return 0;
}

#else

void qemu__xcptfilter(struct qemu_syscall *c)
{
    WINE_FIXME("Stub!\n");
}

#endif

#ifdef QEMU_DLL_GUEST

extern void DECLSPEC_NORETURN CDECL longjmp_set_regs( jmp_buf jmp, int retval );
__ASM_GLOBAL_FUNC( longjmp_set_regs,
                   "movq %rdx,%rax\n\t"            /* retval */
                   "movq 0x8(%rcx),%rbx\n\t"       /* jmp_buf->Rbx */
                   "movq 0x18(%rcx),%rbp\n\t"      /* jmp_buf->Rbp */
                   "movq 0x20(%rcx),%rsi\n\t"      /* jmp_buf->Rsi */
                   "movq 0x28(%rcx),%rdi\n\t"      /* jmp_buf->Rdi */
                   "movq 0x30(%rcx),%r12\n\t"      /* jmp_buf->R12 */
                   "movq 0x38(%rcx),%r13\n\t"      /* jmp_buf->R13 */
                   "movq 0x40(%rcx),%r14\n\t"      /* jmp_buf->R14 */
                   "movq 0x48(%rcx),%r15\n\t"      /* jmp_buf->R15 */
                   "movdqa 0x60(%rcx),%xmm6\n\t"   /* jmp_buf->Xmm6 */
                   "movdqa 0x70(%rcx),%xmm7\n\t"   /* jmp_buf->Xmm7 */
                   "movdqa 0x80(%rcx),%xmm8\n\t"   /* jmp_buf->Xmm8 */
                   "movdqa 0x90(%rcx),%xmm9\n\t"   /* jmp_buf->Xmm9 */
                   "movdqa 0xa0(%rcx),%xmm10\n\t"  /* jmp_buf->Xmm10 */
                   "movdqa 0xb0(%rcx),%xmm11\n\t"  /* jmp_buf->Xmm11 */
                   "movdqa 0xc0(%rcx),%xmm12\n\t"  /* jmp_buf->Xmm12 */
                   "movdqa 0xd0(%rcx),%xmm13\n\t"  /* jmp_buf->Xmm13 */
                   "movdqa 0xe0(%rcx),%xmm14\n\t"  /* jmp_buf->Xmm14 */
                   "movdqa 0xf0(%rcx),%xmm15\n\t"  /* jmp_buf->Xmm15 */
                   "movq 0x50(%rcx),%rdx\n\t"      /* jmp_buf->Rip */
                   "movq 0x10(%rcx),%rsp\n\t"      /* jmp_buf->Rsp */
                   "jmp *%rdx" );

void __cdecl MSVCRT_longjmp(jmp_buf jmp, int retval)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_LONGJMP);

    qemu_syscall(&call);

    /* FIXME: jmp->frame. */

    if (!retval) retval = 1;
    longjmp_set_regs( jmp, retval );
}

#else

void qemu_longjmp(struct qemu_syscall *c)
{
    /* Only called for the purpose of writing something in the trace. */
    WINE_FIXME("\n");
}

#endif

#ifdef QEMU_DLL_GUEST

__p_sig_fn_t CDECL MSVCRT_signal(int sig, __p_sig_fn_t func)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_SIGNAL);

    qemu_syscall(&call);

    return NULL;
}

#else

void qemu_signal(struct qemu_syscall *call)
{
    WINE_FIXME("Stub!\n");
}

#endif

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_raise(int signum)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_RAISE);

    qemu_syscall(&call);

    return 0;
}

#else

void qemu_raise(struct qemu_syscall *call)
{
    WINE_FIXME("Stub!\n");
}

#endif
