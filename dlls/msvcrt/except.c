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
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

#ifdef QEMU_DLL_GUEST

#ifdef _WIN64

EXCEPTION_DISPOSITION CDECL __CxxFrameHandler(EXCEPTION_RECORD *rec, ULONG64 frame,
        CONTEXT *context, DISPATCHER_CONTEXT *dispatch)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL___CXXFRAMEHANDLER);

    qemu_syscall(&call);

    return 0;
}

#else

DWORD CDECL __CxxFrameHandler( PEXCEPTION_RECORD rec, EXCEPTION_REGISTRATION_RECORD* frame,
        PCONTEXT context, EXCEPTION_REGISTRATION_RECORD** dispatch )
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL___CXXFRAMEHANDLER);

    qemu_syscall(&call);

    return 0;
}

#endif

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

#ifdef _WIN64
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

typedef struct _SCOPETABLE
{
  int previousTryLevel;
  int (*lpfnFilter)(PEXCEPTION_POINTERS);
  int (*lpfnHandler)(void);
} SCOPETABLE, *PSCOPETABLE;

typedef struct _MSVCRT_EXCEPTION_FRAME
{
  EXCEPTION_REGISTRATION_RECORD *prev;
  void (*handler)(PEXCEPTION_RECORD, EXCEPTION_REGISTRATION_RECORD*,
                  PCONTEXT, PEXCEPTION_RECORD);
  PSCOPETABLE scopetable;
  int trylevel;
  int _ebp;
  PEXCEPTION_POINTERS xpointers;
} MSVCRT_EXCEPTION_FRAME;

#define TRYLEVEL_END (-1) /* End of trylevel list */

struct MSVCRT___JUMP_BUFFER {
    unsigned long Ebp;
    unsigned long Ebx;
    unsigned long Edi;
    unsigned long Esi;
    unsigned long Esp;
    unsigned long Eip;
    unsigned long Registration;
    unsigned long TryLevel;
    /* Start of new struct members */
    unsigned long Cookie;
    unsigned long UnwindFunc;
    unsigned long UnwindData[6];
};

#define MSVCRT_JMP_MAGIC 0x56433230 /* ID value for new jump structure */
typedef void (__stdcall *MSVCRT_unwind_function)(const struct MSVCRT___JUMP_BUFFER *);

/* define an entrypoint for setjmp/setjmp3 that stores the registers in the jmp buf */
/* and then jumps to the C backend function */
#define DEFINE_SETJMP_ENTRYPOINT(name) \
    __ASM_GLOBAL_FUNC( name, \
                       "movl 4(%esp),%ecx\n\t"   /* jmp_buf */      \
                       "movl %ebp,0(%ecx)\n\t"   /* jmp_buf.Ebp */  \
                       "movl %ebx,4(%ecx)\n\t"   /* jmp_buf.Ebx */  \
                       "movl %edi,8(%ecx)\n\t"   /* jmp_buf.Edi */  \
                       "movl %esi,12(%ecx)\n\t"  /* jmp_buf.Esi */  \
                       "movl %esp,16(%ecx)\n\t"  /* jmp_buf.Esp */  \
                       "movl 0(%esp),%eax\n\t"                      \
                       "movl %eax,20(%ecx)\n\t"  /* jmp_buf.Eip */  \
                       "jmp " __ASM_NAME("__regs_") # name )

/* restore the registers from the jmp buf upon longjmp */
extern void DECLSPEC_NORETURN longjmp_set_regs( struct MSVCRT___JUMP_BUFFER *jmp, int retval );
__ASM_GLOBAL_FUNC( longjmp_set_regs,
                  "movl 4(%esp),%ecx\n\t"   /* jmp_buf */
                  "movl 8(%esp),%eax\n\t"   /* retval */
                  "movl 0(%ecx),%ebp\n\t"   /* jmp_buf.Ebp */
                  "movl 4(%ecx),%ebx\n\t"   /* jmp_buf.Ebx */
                  "movl 8(%ecx),%edi\n\t"   /* jmp_buf.Edi */
                  "movl 12(%ecx),%esi\n\t"  /* jmp_buf.Esi */
                  "movl 16(%ecx),%esp\n\t"  /* jmp_buf.Esp */
                  "addl $4,%esp\n\t"        /* get rid of return address */
                  "jmp *20(%ecx)\n\t"       /* jmp_buf.Eip */ )

/*
 * The signatures of the setjmp/longjmp functions do not match that
 * declared in the setjmp header so they don't follow the regular naming
 * convention to avoid conflicts.
 */

/*******************************************************************
 *        _setjmp (MSVCRT.@)
 */
DEFINE_SETJMP_ENTRYPOINT(MSVCRT__setjmp)
int CDECL __regs_MSVCRT__setjmp(struct MSVCRT___JUMP_BUFFER *jmp)
{
    jmp->Registration = (unsigned long)((NT_TIB *)NtCurrentTeb())->ExceptionList;
    if (jmp->Registration == ~0UL)
        jmp->TryLevel = TRYLEVEL_END;
    else
        jmp->TryLevel = ((MSVCRT_EXCEPTION_FRAME*)jmp->Registration)->trylevel;

    /*TRACE("buf=%p ebx=%08lx esi=%08lx edi=%08lx ebp=%08lx esp=%08lx eip=%08lx frame=%08lx\n",
          jmp, jmp->Ebx, jmp->Esi, jmp->Edi, jmp->Ebp, jmp->Esp, jmp->Eip, jmp->Registration );*/

    return 0;
}

/*******************************************************************
 *        _setjmp3 (MSVCRT.@)
 */
DEFINE_SETJMP_ENTRYPOINT( MSVCRT__setjmp3 )
int WINAPIV __regs_MSVCRT__setjmp3(struct MSVCRT___JUMP_BUFFER *jmp, int nb_args, ...)
{
    jmp->Cookie = MSVCRT_JMP_MAGIC;
    jmp->UnwindFunc = 0;
    jmp->Registration = (unsigned long)((NT_TIB *)NtCurrentTeb())->ExceptionList;
    if (jmp->Registration == ~0UL)
    {
        jmp->TryLevel = TRYLEVEL_END;
    }
    else
    {
        int i;
        va_list args;

        va_start( args, nb_args );
        if (nb_args > 0) jmp->UnwindFunc = va_arg( args, unsigned long );
        if (nb_args > 1) jmp->TryLevel = va_arg( args, unsigned long );
        else jmp->TryLevel = ((MSVCRT_EXCEPTION_FRAME*)jmp->Registration)->trylevel;
        for (i = 0; i < 6 && i < nb_args - 2; i++)
        jmp->UnwindData[i] = va_arg( args, unsigned long );
        va_end( args );
    }

    /*TRACE("buf=%p ebx=%08lx esi=%08lx edi=%08lx ebp=%08lx esp=%08lx eip=%08lx frame=%08lx\n",
          jmp, jmp->Ebx, jmp->Esi, jmp->Edi, jmp->Ebp, jmp->Esp, jmp->Eip, jmp->Registration );*/

    return 0;
}

#endif

#else

void qemu__setjmp(struct qemu_syscall *c)
{
    /* Only called for the purpose of writing something in the trace. */
    WINE_TRACE("\n");
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

#ifdef _WIN64

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

#endif

void __cdecl MSVCRT_longjmp(void *jmp, int retval)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_LONGJMP);

    qemu_syscall(&call);

    /* FIXME: jmp->frame. */

    if (!retval) retval = 1;
    longjmp_set_regs( jmp, retval );
    ExitProcess(1);
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
