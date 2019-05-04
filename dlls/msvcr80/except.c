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

frame_info* CDECL _CreateFrameInfo(frame_info *fi, void *obj)
{
    thread_data_t *data = msvcrt_get_thread_data();

    TRACE("(%p, %p)\n", fi, obj);

    fi->next = data->frame_info_head;
    data->frame_info_head = fi;
    fi->object = obj;
    return fi;
}

void CDECL _FindAndUnlinkFrame(frame_info *fi)
{
    thread_data_t *data = msvcrt_get_thread_data();
    frame_info *cur = data->frame_info_head;

    TRACE("(%p)\n", fi);

    if (cur == fi)
    {
        data->frame_info_head = cur->next;
        return;
    }

    for (; cur->next; cur = cur->next)
    {
        if (cur->next == fi)
        {
            cur->next = fi->next;
            return;
        }
    }

    ERR("frame not found, native crashes in this case\n");
}

BOOL __cdecl _IsExceptionObjectToBeDestroyed(const void *obj)
{
    frame_info *cur;

    TRACE( "%p\n", obj );

    for (cur = msvcrt_get_thread_data()->frame_info_head; cur; cur = cur->next)
    {
        if (cur->object == obj)
            return FALSE;
    }

    return TRUE;
}

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

BOOL CDECL __CxxRegisterExceptionObject(EXCEPTION_RECORD **rec, cxx_frame_info *frame_info)
{
    thread_data_t *data = msvcrt_get_thread_data();

    TRACE("(%p, %p)\n", rec, frame_info);

    if (!rec || !*rec)
    {
        frame_info->rec = (void*)-1;
        frame_info->unk = (void*)-1;
        return TRUE;
    }

    frame_info->rec = data->exc_record;
    frame_info->unk = 0;
    data->exc_record = *rec;
    _CreateFrameInfo(&frame_info->frame_info, (void*)(*rec)->ExceptionInformation[1]);
    return TRUE;
}

void CDECL __CxxUnregisterExceptionObject(cxx_frame_info *frame_info, BOOL in_use)
{
    thread_data_t *data = msvcrt_get_thread_data();

    TRACE("(%p)\n", frame_info);

    if(frame_info->rec == (void*)-1)
        return;

    _FindAndUnlinkFrame(&frame_info->frame_info);
    if(data->exc_record->ExceptionCode == CXX_EXCEPTION && !in_use
            && _IsExceptionObjectToBeDestroyed((void*)data->exc_record->ExceptionInformation[1]))
        __DestructExceptionObject(data->exc_record);
    data->exc_record = frame_info->rec;
}

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

/* the exception frame used by CxxFrameHandler */
typedef struct __cxx_exception_frame
{
    EXCEPTION_REGISTRATION_RECORD  frame;    /* the standard exception frame */
    int                            trylevel;
    DWORD                          ebp;
} cxx_exception_frame;

/* info about a single catch {} block */
typedef struct __catchblock_info
{
    UINT             flags;         /* flags (see below) */
    const type_info *type_info;     /* C++ type caught by this block */
    int              offset;        /* stack offset to copy exception object to */
    void           (*handler)(void);/* catch block handler code */
} catchblock_info;
#define TYPE_FLAG_CONST      1
#define TYPE_FLAG_VOLATILE   2
#define TYPE_FLAG_REFERENCE  8

/* info about a single try {} block */
typedef struct __tryblock_info
{
    int                    start_level;      /* start trylevel of that block */
    int                    end_level;        /* end trylevel of that block */
    int                    catch_level;      /* initial trylevel of the catch block */
    int                    catchblock_count; /* count of catch blocks in array */
    const catchblock_info *catchblock;       /* array of catch blocks */
} tryblock_info;

/* info about the unwind handler for a given trylevel */
typedef struct __unwind_info
{
    int    prev;          /* prev trylevel unwind handler, to run after this one */
    void (*handler)(void);/* unwind handler */
} unwind_info;

/* descriptor of all try blocks of a given function */
typedef struct __cxx_function_descr
{
    UINT                 magic;          /* must be CXX_FRAME_MAGIC */
    UINT                 unwind_count;   /* number of unwind handlers */
    const unwind_info   *unwind_table;   /* array of unwind handlers */
    UINT                 tryblock_count; /* number of try blocks */
    const tryblock_info *tryblock;       /* array of try blocks */
    UINT                 ipmap_count;
    const void          *ipmap;
    const void          *expect_list;    /* expected exceptions list when magic >= VC7 */
    UINT                 flags;          /* flags when magic >= VC8 */
} cxx_function_descr;

typedef struct
{
    cxx_exception_frame *frame;
    const cxx_function_descr *descr;
    EXCEPTION_REGISTRATION_RECORD *nested_frame;
} se_translator_ctx;

/* call a function with a given ebp */
static inline void *call_ebp_func( void *func, void *ebp )
{
    void *ret;
    int dummy;
    __asm__ __volatile__ ("pushl %%ebx\n\t"
                          "pushl %%ebp\n\t"
                          "movl %4,%%ebp\n\t"
                          "call *%%eax\n\t"
                          "popl %%ebp\n\t"
                          "popl %%ebx"
                          : "=a" (ret), "=S" (dummy), "=D" (dummy)
                          : "0" (func), "1" (ebp) : "ecx", "edx", "memory" );
    return ret;
}

static inline void call_copy_ctor( void *func, void *this, void *src, int has_vbase )
{
    TRACE( "calling copy ctor %p object %p src %p\n", func, this, src );
    if (has_vbase)
        /* in that case copy ctor takes an extra bool indicating whether to copy the base class */
        __asm__ __volatile__("pushl $1; pushl %2; call *%0"
                             : : "r" (func), "c" (this), "r" (src) : "eax", "edx", "memory" );
    else
        __asm__ __volatile__("pushl %2; call *%0"
                             : : "r" (func), "c" (this), "r" (src) : "eax", "edx", "memory" );
}

static inline void DECLSPEC_NORETURN continue_after_catch( cxx_exception_frame* frame, void *addr )
{
    __asm__ __volatile__("movl -4(%0),%%esp; leal 12(%0),%%ebp; jmp *%1"
                         : : "r" (frame), "a" (addr) );
    for (;;) ; /* unreached */
}

static const cxx_type_info *find_caught_type( cxx_exception_type *exc_type,
                                              const type_info *catch_ti, UINT catch_flags )
{
    UINT i;

    for (i = 0; i < exc_type->type_info_table->count; i++)
    {
        const cxx_type_info *type = exc_type->type_info_table->info[i];

        if (!catch_ti) return type;   /* catch(...) matches any type */
        if (catch_ti != type->type_info)
        {
            if (strcmp( catch_ti->mangled, type->type_info->mangled )) continue;
        }
        /* type is the same, now check the flags */
        if ((exc_type->flags & TYPE_FLAG_CONST) &&
            !(catch_flags & TYPE_FLAG_CONST)) continue;
        if ((exc_type->flags & TYPE_FLAG_VOLATILE) &&
            !(catch_flags & TYPE_FLAG_VOLATILE)) continue;
        return type;  /* it matched */
    }
    return NULL;
}


/* copy the exception object where the catch block wants it */
static void copy_exception( void *object, cxx_exception_frame *frame,
                            const catchblock_info *catchblock, const cxx_type_info *type )
{
    void **dest_ptr;

    if (!catchblock->type_info || !catchblock->type_info->mangled[0]) return;
    if (!catchblock->offset) return;
    dest_ptr = (void **)((char *)&frame->ebp + catchblock->offset);

    if (catchblock->flags & TYPE_FLAG_REFERENCE)
    {
        *dest_ptr = get_this_pointer( &type->offsets, object );
    }
    else if (type->flags & CLASS_IS_SIMPLE_TYPE)
    {
        memmove( dest_ptr, object, type->size );
        /* if it is a pointer, adjust it */
        if (type->size == sizeof(void *)) *dest_ptr = get_this_pointer( &type->offsets, *dest_ptr );
    }
    else  /* copy the object */
    {
        if (type->copy_ctor)
            call_copy_ctor( type->copy_ctor, dest_ptr, get_this_pointer(&type->offsets,object),
                            (type->flags & CLASS_HAS_VIRTUAL_BASE_CLASS) );
        else
            memmove( dest_ptr, get_this_pointer(&type->offsets,object), type->size );
    }
}

static void cxx_local_unwind( cxx_exception_frame* frame, const cxx_function_descr *descr, int last_level)
{
    void (*handler)(void);
    int trylevel = frame->trylevel;

    while (trylevel != last_level)
    {
        if (trylevel < 0 || trylevel >= descr->unwind_count)
        {
            ERR( "invalid trylevel %d\n", trylevel );
            MSVCRT_terminate();
        }
        handler = descr->unwind_table[trylevel].handler;
        if (handler)
        {
            TRACE( "calling unwind handler %p trylevel %d last %d ebp %p\n",
                   handler, trylevel, last_level, &frame->ebp );
            call_ebp_func( handler, &frame->ebp );
        }
        trylevel = descr->unwind_table[trylevel].prev;
    }
    frame->trylevel = last_level;
}

/* exception frame for nested exceptions in catch block */
struct catch_func_nested_frame
{
    EXCEPTION_REGISTRATION_RECORD frame;     /* standard exception frame */
    cxx_exception_frame          *cxx_frame; /* frame of parent exception */
    const cxx_function_descr     *descr;     /* descriptor of parent exception */
    int                           trylevel;  /* current try level */
    cxx_frame_info                frame_info;
};

DWORD CDECL cxx_frame_handler( PEXCEPTION_RECORD rec, cxx_exception_frame* frame,
                               PCONTEXT context, EXCEPTION_REGISTRATION_RECORD** dispatch,
                               const cxx_function_descr *descr,
                               EXCEPTION_REGISTRATION_RECORD* nested_frame, int nested_trylevel );

/* handler for exceptions happening while calling a catch function */
static DWORD catch_function_nested_handler( EXCEPTION_RECORD *rec, EXCEPTION_REGISTRATION_RECORD *frame,
                                            CONTEXT *context, EXCEPTION_REGISTRATION_RECORD **dispatcher )
{
    struct catch_func_nested_frame *nested_frame = (struct catch_func_nested_frame *)frame;

    if (rec->ExceptionFlags & (EH_UNWINDING | EH_EXIT_UNWIND))
    {
        __CxxUnregisterExceptionObject(&nested_frame->frame_info, FALSE);
        return ExceptionContinueSearch;
    }

    TRACE( "got nested exception in catch function\n" );

    if(rec->ExceptionCode == CXX_EXCEPTION)
    {
        PEXCEPTION_RECORD prev_rec = msvcrt_get_thread_data()->exc_record;

        if((rec->ExceptionInformation[1] == 0 && rec->ExceptionInformation[2] == 0) ||
                (prev_rec->ExceptionCode == CXX_EXCEPTION &&
                 rec->ExceptionInformation[1] == prev_rec->ExceptionInformation[1] &&
                 rec->ExceptionInformation[2] == prev_rec->ExceptionInformation[2]))
        {
            /* exception was rethrown */
            *rec = *prev_rec;
            rec->ExceptionFlags &= ~EH_UNWINDING;
        }
        else
        {
            TRACE("detect threw new exception in catch block\n");
        }
    }

    return cxx_frame_handler( rec, nested_frame->cxx_frame, context,
                              NULL, nested_frame->descr, &nested_frame->frame,
                              nested_frame->trylevel );
}

static inline void call_catch_block( PEXCEPTION_RECORD rec, cxx_exception_frame *frame,
                                     const cxx_function_descr *descr, int nested_trylevel,
                                     EXCEPTION_REGISTRATION_RECORD *catch_frame,
                                     cxx_exception_type *info )
{
    UINT i;
    int j;
    void *addr, *object = (void *)rec->ExceptionInformation[1];
    struct catch_func_nested_frame nested_frame;
    int trylevel = frame->trylevel;
    DWORD save_esp = ((DWORD*)frame)[-1];
    thread_data_t *data;

    for (i = 0; i < descr->tryblock_count; i++)
    {
        const tryblock_info *tryblock = &descr->tryblock[i];

        /* only handle try blocks inside current catch block */
        if (catch_frame && nested_trylevel > tryblock->start_level) continue;

        if (trylevel < tryblock->start_level) continue;
        if (trylevel > tryblock->end_level) continue;

        /* got a try block */
        for (j = 0; j < tryblock->catchblock_count; j++)
        {
            const catchblock_info *catchblock = &tryblock->catchblock[j];
            if(info)
            {
                const cxx_type_info *type = find_caught_type( info,
                        catchblock->type_info, catchblock->flags );
                if (!type) continue;

                TRACE( "matched type %p in tryblock %d catchblock %d\n", type, i, j );

                /* copy the exception to its destination on the stack */
                copy_exception( object, frame, catchblock, type );
            }
            else
            {
                /* no CXX_EXCEPTION only proceed with a catch(...) block*/
                if(catchblock->type_info)
                    continue;
                TRACE("found catch(...) block\n");
            }

            /* Add frame info here so exception is not freed inside RtlUnwind call */
            _CreateFrameInfo(&nested_frame.frame_info.frame_info,
                    (void*)rec->ExceptionInformation[1]);

            /* unwind the stack */
            RtlUnwind( catch_frame ? catch_frame : &frame->frame, 0, rec, 0 );
            cxx_local_unwind( frame, descr, tryblock->start_level );
            frame->trylevel = tryblock->end_level + 1;

            data = msvcrt_get_thread_data();
            nested_frame.frame_info.rec = data->exc_record;
            data->exc_record = rec;

            /* call the catch block */
            TRACE( "calling catch block %p addr %p ebp %p\n",
                   catchblock, catchblock->handler, &frame->ebp );

            /* setup an exception block for nested exceptions */
            nested_frame.frame.Handler = catch_function_nested_handler;
            nested_frame.cxx_frame = frame;
            nested_frame.descr     = descr;
            nested_frame.trylevel  = nested_trylevel + 1;

//             __wine_push_frame( &nested_frame.frame );
            addr = call_ebp_func( catchblock->handler, &frame->ebp );
//             __wine_pop_frame( &nested_frame.frame );

            ((DWORD*)frame)[-1] = save_esp;
            __CxxUnregisterExceptionObject(&nested_frame.frame_info, FALSE);
            TRACE( "done, continuing at %p\n", addr );

            continue_after_catch( frame, addr );
        }
    }
}

DWORD CDECL cxx_frame_handler( PEXCEPTION_RECORD rec, cxx_exception_frame* frame,
                               PCONTEXT context, EXCEPTION_REGISTRATION_RECORD** dispatch,
                               const cxx_function_descr *descr,
                               EXCEPTION_REGISTRATION_RECORD* nested_frame,
                               int nested_trylevel )
{
    cxx_exception_type *exc_type;

    if (descr->magic < CXX_FRAME_MAGIC_VC6 || descr->magic > CXX_FRAME_MAGIC_VC8)
    {
        ERR( "invalid frame magic %x\n", descr->magic );
        return ExceptionContinueSearch;
    }
    if (descr->magic >= CXX_FRAME_MAGIC_VC8 &&
        (descr->flags & FUNC_DESCR_SYNCHRONOUS) &&
        (rec->ExceptionCode != CXX_EXCEPTION))
        return ExceptionContinueSearch;  /* handle only c++ exceptions */

    if (rec->ExceptionFlags & (EH_UNWINDING|EH_EXIT_UNWIND))
    {
        if (descr->unwind_count && !nested_trylevel) cxx_local_unwind( frame, descr, -1 );
        return ExceptionContinueSearch;
    }
    if (!descr->tryblock_count) return ExceptionContinueSearch;

    if(rec->ExceptionCode == CXX_EXCEPTION &&
            rec->ExceptionInformation[1] == 0 && rec->ExceptionInformation[2] == 0)
    {
        *rec = *msvcrt_get_thread_data()->exc_record;
        rec->ExceptionFlags &= ~EH_UNWINDING;
    }

    if(rec->ExceptionCode == CXX_EXCEPTION)
    {
        exc_type = (cxx_exception_type *)rec->ExceptionInformation[2];

        if (rec->ExceptionInformation[0] > CXX_FRAME_MAGIC_VC8 &&
                exc_type->custom_handler)
        {
            return exc_type->custom_handler( rec, frame, context, dispatch,
                                         descr, nested_trylevel, nested_frame, 0 );
        }
    }
    else
    {
        thread_data_t *data = msvcrt_get_thread_data();

        exc_type = NULL;
        TRACE("handling C exception code %x  rec %p frame %p trylevel %d descr %p nested_frame %p\n",
              rec->ExceptionCode,  rec, frame, frame->trylevel, descr, nested_frame );

        if (data->se_translator) {
            EXCEPTION_POINTERS except_ptrs;
            se_translator_ctx ctx;

            ctx.frame = frame;
            ctx.descr = descr;
            ctx.nested_frame = nested_frame;
//             __TRY
//             {
                except_ptrs.ExceptionRecord = rec;
                except_ptrs.ContextRecord = context;
                data->se_translator( rec->ExceptionCode, &except_ptrs );
//             }
//             __EXCEPT_CTX(se_translation_filter, &ctx)
//             {
//             }
//             __ENDTRY
        }
    }

    call_catch_block( rec, frame, descr, frame->trylevel, nested_frame, exc_type );
    return ExceptionContinueSearch;
}

extern DWORD CDECL __CxxFrameHandler( PEXCEPTION_RECORD rec, EXCEPTION_REGISTRATION_RECORD* frame,
                                      PCONTEXT context, EXCEPTION_REGISTRATION_RECORD** dispatch );
__ASM_GLOBAL_FUNC( __CxxFrameHandler,
                   "pushl $0\n\t"        /* nested_trylevel */
                   __ASM_CFI(".cfi_adjust_cfa_offset 4\n\t")
                   "pushl $0\n\t"        /* nested_frame */
                   __ASM_CFI(".cfi_adjust_cfa_offset 4\n\t")
                   "pushl %eax\n\t"      /* descr */
                   __ASM_CFI(".cfi_adjust_cfa_offset 4\n\t")
                   "pushl 28(%esp)\n\t"  /* dispatch */
                   __ASM_CFI(".cfi_adjust_cfa_offset 4\n\t")
                   "pushl 28(%esp)\n\t"  /* context */
                   __ASM_CFI(".cfi_adjust_cfa_offset 4\n\t")
                   "pushl 28(%esp)\n\t"  /* frame */
                   __ASM_CFI(".cfi_adjust_cfa_offset 4\n\t")
                   "pushl 28(%esp)\n\t"  /* rec */
                   __ASM_CFI(".cfi_adjust_cfa_offset 4\n\t")
                   "call " __ASM_NAME("cxx_frame_handler") "\n\t"
                   "add $28,%esp\n\t"
                   __ASM_CFI(".cfi_adjust_cfa_offset -28\n\t")
                   "ret" )

#endif

#else

void qemu___cxxframehandler(struct qemu_syscall *c)
{
    WINE_FIXME("Stub!\n");
}

#endif

struct qemu__setjmp
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT__setjmp_log(const char *str)
{
    struct qemu__setjmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SETJMP);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);
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
    MSVCRT__setjmp_log("setjmp");
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
    static char blob[4096];
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

    MSVCRT_sprintf(blob, "setjmp3 buf=%p ebx=%08lx esi=%08lx edi=%08lx ebp=%08lx esp=%08lx eip=%08lx frame=%08lx, unwind=%08lx\n",
           jmp, jmp->Ebx, jmp->Esi, jmp->Edi, jmp->Ebp, jmp->Esp, jmp->Eip, jmp->Registration, jmp->UnwindFunc);
    MSVCRT__setjmp_log(blob);

    return 0;
}

#endif

#else

void qemu__setjmp(struct qemu_syscall *call)
{
    struct qemu__setjmp *c = (struct qemu__setjmp *)call;
    /* Only called for the purpose of writing something in the trace. */
    WINE_TRACE("%s\n", (char *)QEMU_G2H(c->str));
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

struct qemu_longjmp
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

#ifdef _WIN64

extern void DECLSPEC_NORETURN CDECL longjmp_set_regs( void *jmp, int retval );
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
    struct qemu_longjmp call;
    static char blob[4096];

#ifdef _WIN64
    MSVCRT_sprintf(blob, "longjmp, buf=%p\n", jmp);
#else
    struct MSVCRT___JUMP_BUFFER *jmp32 = jmp;
    MSVCRT_sprintf(blob, "buf=%p ebx=%08lx esi=%08lx edi=%08lx ebp=%08lx esp=%08lx eip=%08lx frame=%08lx, unwind=%08lx\n",
           jmp32, jmp32->Ebx, jmp32->Esi, jmp32->Edi, jmp32->Ebp, jmp32->Esp, jmp32->Eip, jmp32->Registration, jmp32->UnwindFunc);
#endif

    call.super.id = QEMU_SYSCALL_ID(CALL_LONGJMP);
    call.str = (ULONG_PTR)blob;
    qemu_syscall(&call.super);

    /* FIXME: jmp->frame. */

    if (!retval) retval = 1;
    longjmp_set_regs( jmp, retval );
    ExitProcess(1);
}

#else

void qemu_longjmp(struct qemu_syscall *call)
{
    struct qemu_longjmp *c = (struct qemu_longjmp *)call;
    /* Only called for the purpose of writing something in the trace. */
    WINE_FIXME("%s\n", (char *)QEMU_G2H(c->str));
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

static void msvcrt_local_unwind2(MSVCRT_EXCEPTION_FRAME* frame, int trylevel, void *ebp)
{
//   EXCEPTION_REGISTRATION_RECORD reg;

  TRACE("(%p,%d,%d)\n",frame, frame->trylevel, trylevel);

  /* Register a handler in case of a nested exception */
//   reg.Handler = MSVCRT_nested_handler;
//   reg.Prev = NtCurrentTeb()->Tib.ExceptionList;
//   __wine_push_frame(&reg);

  while (frame->trylevel != TRYLEVEL_END && frame->trylevel != trylevel)
  {
      int level = frame->trylevel;
      frame->trylevel = frame->scopetable[level].previousTryLevel;
      if (!frame->scopetable[level].lpfnFilter)
      {
          TRACE( "__try block cleanup level %d handler %p ebp %p\n",
                 level, frame->scopetable[level].lpfnHandler, ebp );
          call_unwind_func( frame->scopetable[level].lpfnHandler, ebp );
      }
  }
//   __wine_pop_frame(&reg);
  TRACE("unwound OK\n");
}

int CDECL _except_handler3(PEXCEPTION_RECORD rec,
                           MSVCRT_EXCEPTION_FRAME* frame,
                           PCONTEXT context, void* dispatcher)
{
  int retval, trylevel;
  EXCEPTION_POINTERS exceptPtrs;
  PSCOPETABLE pScopeTable;

  TRACE("exception %x flags=%x at %p handler=%p %p %p semi-stub\n",
        rec->ExceptionCode, rec->ExceptionFlags, rec->ExceptionAddress,
        frame->handler, context, dispatcher);

  __asm__ __volatile__ ("cld");

  if (rec->ExceptionFlags & (EH_UNWINDING | EH_EXIT_UNWIND))
  {
    /* Unwinding the current frame */
    msvcrt_local_unwind2(frame, TRYLEVEL_END, &frame->_ebp);
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
    pScopeTable = frame->scopetable;

    while (trylevel != TRYLEVEL_END)
    {
      TRACE( "level %d prev %d filter %p\n", trylevel, pScopeTable[trylevel].previousTryLevel,
             pScopeTable[trylevel].lpfnFilter );
      if (pScopeTable[trylevel].lpfnFilter)
      {
        retval = call_filter( pScopeTable[trylevel].lpfnFilter, &exceptPtrs, &frame->_ebp );

        TRACE("filter returned %s\n", retval == EXCEPTION_CONTINUE_EXECUTION ?
              "CONTINUE_EXECUTION" : retval == EXCEPTION_EXECUTE_HANDLER ?
              "EXECUTE_HANDLER" : "CONTINUE_SEARCH");

        if (retval == EXCEPTION_CONTINUE_EXECUTION)
          return ExceptionContinueExecution;

        if (retval == EXCEPTION_EXECUTE_HANDLER)
        {
          /* Unwind all higher frames, this one will handle the exception */
          _global_unwind2((EXCEPTION_REGISTRATION_RECORD*)frame);
          msvcrt_local_unwind2(frame, trylevel, &frame->_ebp);

          /* Set our trylevel to the enclosing block, and call the __finally
           * code, which won't return
           */
          frame->trylevel = pScopeTable[trylevel].previousTryLevel;
          TRACE("__finally block %p\n",pScopeTable[trylevel].lpfnHandler);
          call_finally_block(pScopeTable[trylevel].lpfnHandler, &frame->_ebp);
          ERR("Returned from __finally block - expect crash!\n");
       }
      }
      trylevel = pScopeTable[trylevel].previousTryLevel;
    }
  }
  TRACE("reached TRYLEVEL_END, returning ExceptionContinueSearch\n");
  return ExceptionContinueSearch;
}

#endif

#else

/* FIXME: Do I want some logging helper? */

#endif
