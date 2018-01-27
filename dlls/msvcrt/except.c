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

#define TRACE(str, ...)
#define ERR(str, ...)

#define EH_UNWINDING        0x02
#define EH_EXIT_UNWIND      0x04

#include "cppexcept.h"

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

typedef struct
{
  int   gs_cookie_offset;
  ULONG gs_cookie_xor;
  int   eh_cookie_offset;
  ULONG eh_cookie_xor;
  SCOPETABLE entries[1];
} SCOPETABLE_V4;

static const SCOPETABLE_V4 *get_scopetable_v4( MSVCRT_EXCEPTION_FRAME *frame, ULONG_PTR cookie )
{
    return (const SCOPETABLE_V4 *)((ULONG_PTR)frame->scopetable ^ cookie);
}

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

int CDECL __CppXcptFilter(unsigned long _ExceptionNum,struct _EXCEPTION_POINTERS * _ExceptionPtr)
{
    /* only filter c++ exceptions */
    if (_ExceptionNum != CXX_EXCEPTION) return EXCEPTION_CONTINUE_SEARCH;
    return MSVCRT__XcptFilter( _ExceptionNum, _ExceptionPtr );
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

#ifdef QEMU_DLL_GUEST

BOOL CDECL MSVCRT___uncaught_exception(void)
{
    struct qemu_syscall call;
    call.id = CALL___UNCAUGHT_EXCEPTION;

    qemu_syscall(&call);

    return call.iret;
}

#else

void qemu___uncaught_exception(struct qemu_syscall *call)
{
    WINE_FIXME("Unverified\n");
    call->iret = p___uncaught_exception();
}

#endif

#ifdef QEMU_DLL_GUEST

void CDECL __DestructExceptionObject(EXCEPTION_RECORD *rec)
{
    cxx_exception_type *info = (cxx_exception_type*) rec->ExceptionInformation[2];
    void *object = (void*)rec->ExceptionInformation[1];

    TRACE("(%p)\n", rec);

    if (rec->ExceptionCode != CXX_EXCEPTION) return;
#ifndef __x86_64__
    if (rec->NumberParameters != 3) return;
#else
    if (rec->NumberParameters != 4) return;
#endif
    if (rec->ExceptionInformation[0] < CXX_FRAME_MAGIC_VC6 ||
            rec->ExceptionInformation[0] > CXX_FRAME_MAGIC_VC8) return;

    if (!info || !info->destructor)
        return;

#if defined(__i386__)
    __asm__ __volatile__("call *%0" : : "r" (info->destructor), "c" (object) : "eax", "edx", "memory" );
#elif defined(__x86_64__)
    ((void (__cdecl*)(void*))(info->destructor+rec->ExceptionInformation[3]))(object);
#else
    ((void (__cdecl*)(void*))info->destructor)(object);
#endif
}

#ifdef _WIN64

#else

static inline void call_finally_block( void *code_block, void *base_ptr )
{
    __asm__ __volatile__ ("movl %1,%%ebp; call *%%eax"
                          : : "a" (code_block), "g" (base_ptr));
}

static inline int call_filter( int (*func)(PEXCEPTION_POINTERS), void *arg, void *ebp )
{
    int ret;
    __asm__ __volatile__ ("pushl %%ebp; pushl %3; movl %2,%%ebp; call *%%eax; popl %%ebp; popl %%ebp"
                          : "=a" (ret)
                          : "0" (func), "r" (ebp), "r" (arg)
                          : "ecx", "edx", "memory" );
    return ret;
}

static inline int call_unwind_func( int (*func)(void), void *ebp )
{
    int ret;
    __asm__ __volatile__ ("pushl %%ebp\n\t"
                          "pushl %%ebx\n\t"
                          "pushl %%esi\n\t"
                          "pushl %%edi\n\t"
                          "movl %2,%%ebp\n\t"
                          "call *%0\n\t"
                          "popl %%edi\n\t"
                          "popl %%esi\n\t"
                          "popl %%ebx\n\t"
                          "popl %%ebp"
                          : "=a" (ret)
                          : "0" (func), "r" (ebp)
                          : "ecx", "edx", "memory" );
    return ret;
}

static void msvcrt_local_unwind4( ULONG *cookie, MSVCRT_EXCEPTION_FRAME* frame, int trylevel, void *ebp )
{
//     EXCEPTION_REGISTRATION_RECORD reg;
    const SCOPETABLE_V4 *scopetable = get_scopetable_v4( frame, *cookie );

    TRACE("(%p,%d,%d)\n",frame, frame->trylevel, trylevel);

    /* Register a handler in case of a nested exception */
//     reg.Handler = MSVCRT_nested_handler;
//     reg.Prev = NtCurrentTeb()->Tib.ExceptionList;
//     __wine_push_frame(&reg);

    while (frame->trylevel != -2 && frame->trylevel != trylevel)
    {
        int level = frame->trylevel;
        frame->trylevel = scopetable->entries[level].previousTryLevel;
        if (!scopetable->entries[level].lpfnFilter)
        {
            TRACE( "__try block cleanup level %d handler %p ebp %p\n",
                   level, scopetable->entries[level].lpfnHandler, ebp );
            call_unwind_func( scopetable->entries[level].lpfnHandler, ebp );
        }
    }
//     __wine_pop_frame(&reg);
    TRACE("unwound OK\n");
}

void CDECL _global_unwind2(EXCEPTION_REGISTRATION_RECORD* frame)
{
    TRACE("(%p)\n",frame);
    RtlUnwind( frame, 0, 0, 0 );
}

int CDECL _except_handler4_common( ULONG *cookie, void (*check_cookie)(void),
                                   EXCEPTION_RECORD *rec, MSVCRT_EXCEPTION_FRAME *frame,
                                   CONTEXT *context, EXCEPTION_REGISTRATION_RECORD **dispatcher )
{
    int retval, trylevel;
    EXCEPTION_POINTERS exceptPtrs;
    const SCOPETABLE_V4 *scope_table = get_scopetable_v4( frame, *cookie );

    TRACE( "exception %x flags=%x at %p handler=%p %p %p cookie=%x scope table=%p cookies=%d/%x,%d/%x\n",
           rec->ExceptionCode, rec->ExceptionFlags, rec->ExceptionAddress,
           frame->handler, context, dispatcher, *cookie, scope_table,
           scope_table->gs_cookie_offset, scope_table->gs_cookie_xor,
           scope_table->eh_cookie_offset, scope_table->eh_cookie_xor );

    /* FIXME: no cookie validation yet */

    if (rec->ExceptionFlags & (EH_UNWINDING | EH_EXIT_UNWIND))
    {
        /* Unwinding the current frame */
        msvcrt_local_unwind4( cookie, frame, -2, &frame->_ebp );
        TRACE("unwound current frame, returning ExceptionContinueSearch\n");
        return ExceptionContinueSearch;
    }
    else
    {
        /* Hunting for handler */
        exceptPtrs.ExceptionRecord = rec;
        exceptPtrs.ContextRecord = context;
        *((DWORD *)frame-1) = (DWORD)&exceptPtrs;
        trylevel = frame->trylevel;

        while (trylevel != -2)
        {
            TRACE( "level %d prev %d filter %p\n", trylevel,
                   scope_table->entries[trylevel].previousTryLevel,
                   scope_table->entries[trylevel].lpfnFilter );
            if (scope_table->entries[trylevel].lpfnFilter)
            {
                retval = call_filter( scope_table->entries[trylevel].lpfnFilter, &exceptPtrs, &frame->_ebp );

                TRACE("filter returned %s\n", retval == EXCEPTION_CONTINUE_EXECUTION ?
                      "CONTINUE_EXECUTION" : retval == EXCEPTION_EXECUTE_HANDLER ?
                      "EXECUTE_HANDLER" : "CONTINUE_SEARCH");

                if (retval == EXCEPTION_CONTINUE_EXECUTION)
                    return ExceptionContinueExecution;

                if (retval == EXCEPTION_EXECUTE_HANDLER)
                {
                    __DestructExceptionObject(rec);

                    /* Unwind all higher frames, this one will handle the exception */
                    _global_unwind2((EXCEPTION_REGISTRATION_RECORD*)frame);
                    msvcrt_local_unwind4( cookie, frame, trylevel, &frame->_ebp );

                    /* Set our trylevel to the enclosing block, and call the __finally
                     * code, which won't return
                     */
                    frame->trylevel = scope_table->entries[trylevel].previousTryLevel;
                    TRACE("__finally block %p\n",scope_table->entries[trylevel].lpfnHandler);
                    call_finally_block(scope_table->entries[trylevel].lpfnHandler, &frame->_ebp);
                    ERR("Returned from __finally block - expect crash!\n");
                }
            }
            trylevel = scope_table->entries[trylevel].previousTryLevel;
        }
    }
    TRACE("reached -2, returning ExceptionContinueSearch\n");
    return ExceptionContinueSearch;
}

#endif

#else

/* FIXME: Do I want some logging helper? */

#endif
