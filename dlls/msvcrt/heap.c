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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif


struct qemu_operator_new
{
    struct qemu_syscall super;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* CDECL MSVCRT_operator_new(size_t size)
{
    struct qemu_operator_new call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPERATOR_NEW);
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_operator_new(struct qemu_syscall *call)
{
    struct qemu_operator_new *c = (struct qemu_operator_new *)call;
    WINE_TRACE("\n");

    /* This is only half the fun as long as we don't implement the new handler setter. */
    c->super.iret = QEMU_H2G(p_operator_new(c->size));
}

#endif

struct qemu_operator_new_dbg
{
    struct qemu_syscall super;
    uint64_t size;
    uint64_t type;
    uint64_t file;
    uint64_t line;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* CDECL MSVCRT_operator_new_dbg(size_t size, int type, const char *file, int line)
{
    struct qemu_operator_new_dbg call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPERATOR_NEW_DBG);
    call.size = size;
    call.type = type;
    call.file = (ULONG_PTR)file;
    call.line = line;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_operator_new_dbg(struct qemu_syscall *call)
{
    struct qemu_operator_new_dbg *c = (struct qemu_operator_new_dbg *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_operator_new_dbg(c->size, c->type, QEMU_G2H(c->file), c->line));
}

#endif

struct qemu_operator_delete
{
    struct qemu_syscall super;
    uint64_t mem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT_operator_delete(void *mem)
{
    struct qemu_operator_delete call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OPERATOR_DELETE);
    call.mem = (ULONG_PTR)mem;

    qemu_syscall(&call.super);
}

#else

void qemu_operator_delete(struct qemu_syscall *call)
{
    struct qemu_operator_delete *c = (struct qemu_operator_delete *)call;
    WINE_TRACE("\n");
    p_operator_delete(QEMU_G2H(c->mem));
}

#endif

struct qemu__query_new_handler
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT_new_handler_func CDECL MSVCRT__query_new_handler(void)
{
    struct qemu__query_new_handler call;
    call.super.id = QEMU_SYSCALL_ID(CALL__QUERY_NEW_HANDLER);

    qemu_syscall(&call.super);

    return (MSVCRT_new_handler_func)call.super.iret;
}

#else

void qemu__query_new_handler(struct qemu_syscall *call)
{
    struct qemu__query_new_handler *c = (struct qemu__query_new_handler *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__query_new_handler());
}

#endif

struct qemu__query_new_mode
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__query_new_mode(void)
{
    struct qemu__query_new_mode call;
    call.super.id = QEMU_SYSCALL_ID(CALL__QUERY_NEW_MODE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__query_new_mode(struct qemu_syscall *call)
{
    struct qemu__query_new_mode *c = (struct qemu__query_new_mode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__query_new_mode();
}

#endif

struct qemu__set_new_handler
{
    struct qemu_syscall super;
    uint64_t func;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT_new_handler_func CDECL MSVCRT__set_new_handler(MSVCRT_new_handler_func func)
{
    struct qemu__set_new_handler call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SET_NEW_HANDLER);
    call.func = (ULONG_PTR)func;

    qemu_syscall(&call.super);

    return (MSVCRT_new_handler_func)call.super.iret;
}

#else

void qemu__set_new_handler(struct qemu_syscall *call)
{
    struct qemu__set_new_handler *c = (struct qemu__set_new_handler *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__set_new_handler(QEMU_G2H(c->func)));
}

#endif

struct qemu_set_new_handler
{
    struct qemu_syscall super;
    uint64_t func;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MSVCRT_new_handler_func CDECL MSVCRT_set_new_handler(void *func)
{
    struct qemu_set_new_handler call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SET_NEW_HANDLER);
    call.func = (ULONG_PTR)func;

    qemu_syscall(&call.super);

    return (MSVCRT_new_handler_func)call.super.iret;
}

#else

void qemu_set_new_handler(struct qemu_syscall *call)
{
    struct qemu_set_new_handler *c = (struct qemu_set_new_handler *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_set_new_handler(QEMU_G2H(c->func)));
}

#endif

struct qemu__set_new_mode
{
    struct qemu_syscall super;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__set_new_mode(int mode)
{
    struct qemu__set_new_mode call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SET_NEW_MODE);
    call.mode = mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__set_new_mode(struct qemu_syscall *call)
{
    struct qemu__set_new_mode *c = (struct qemu__set_new_mode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__set_new_mode(c->mode);
}

#endif

struct qemu__callnewh
{
    struct qemu_syscall super;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _callnewh(size_t size)
{
    struct qemu__callnewh call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CALLNEWH);
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__callnewh(struct qemu_syscall *call)
{
    struct qemu__callnewh *c = (struct qemu__callnewh *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__callnewh(c->size);
}

#endif

struct qemu__expand
{
    struct qemu_syscall super;
    uint64_t mem;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* CDECL _expand(void* mem, size_t size)
{
    struct qemu__expand call;
    call.super.id = QEMU_SYSCALL_ID(CALL__EXPAND);
    call.mem = (ULONG_PTR)mem;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu__expand(struct qemu_syscall *call)
{
    struct qemu__expand *c = (struct qemu__expand *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__expand(QEMU_G2H(c->mem), c->size));
}

#endif

struct qemu__heapchk
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _heapchk(void)
{
    struct qemu__heapchk call;
    call.super.id = QEMU_SYSCALL_ID(CALL__HEAPCHK);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__heapchk(struct qemu_syscall *call)
{
    struct qemu__heapchk *c = (struct qemu__heapchk *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__heapchk();
}

#endif

struct qemu__heapmin
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _heapmin(void)
{
    struct qemu__heapmin call;
    call.super.id = QEMU_SYSCALL_ID(CALL__HEAPMIN);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__heapmin(struct qemu_syscall *call)
{
    struct qemu__heapmin *c = (struct qemu__heapmin *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__heapmin();
}

#endif

struct qemu__heapwalk
{
    struct qemu_syscall super;
    uint64_t next;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT__heapwalk(struct MSVCRT__heapinfo* next)
{
    struct qemu__heapwalk call;
    call.super.id = QEMU_SYSCALL_ID(CALL__HEAPWALK);
    call.next = (ULONG_PTR)next;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__heapwalk(struct qemu_syscall *call)
{
    struct qemu__heapwalk *c = (struct qemu__heapwalk *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__heapwalk(QEMU_G2H(c->next));
}

#endif

struct qemu__heapset
{
    struct qemu_syscall super;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _heapset(unsigned int value)
{
    struct qemu__heapset call;
    call.super.id = QEMU_SYSCALL_ID(CALL__HEAPSET);
    call.value = value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__heapset(struct qemu_syscall *call)
{
    struct qemu__heapset *c = (struct qemu__heapset *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__heapset(c->value);
}

#endif

struct qemu__heapadd
{
    struct qemu_syscall super;
    uint64_t mem;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _heapadd(void* mem, size_t size)
{
    struct qemu__heapadd call;
    call.super.id = QEMU_SYSCALL_ID(CALL__HEAPADD);
    call.mem = (ULONG_PTR)mem;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__heapadd(struct qemu_syscall *call)
{
    struct qemu__heapadd *c = (struct qemu__heapadd *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__heapadd(QEMU_G2H(c->mem), c->size);
}

#endif

struct qemu__get_heap_handle
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI intptr_t CDECL _get_heap_handle(void)
{
    struct qemu__get_heap_handle call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_HEAP_HANDLE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_heap_handle(struct qemu_syscall *call)
{
    struct qemu__get_heap_handle *c = (struct qemu__get_heap_handle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_heap_handle();
}

#endif

struct qemu__msize
{
    struct qemu_syscall super;
    uint64_t mem;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL _msize(void* mem)
{
    struct qemu__msize call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MSIZE);
    call.mem = (ULONG_PTR)mem;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__msize(struct qemu_syscall *call)
{
    struct qemu__msize *c = (struct qemu__msize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__msize(QEMU_G2H(c->mem));
}

#endif

struct qemu__aligned_msize
{
    struct qemu_syscall super;
    uint64_t p;
    uint64_t alignment;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL _aligned_msize(void *p, size_t alignment, size_t offset)
{
    struct qemu__aligned_msize call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ALIGNED_MSIZE);
    call.p = (ULONG_PTR)p;
    call.alignment = alignment;
    call.offset = offset;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__aligned_msize(struct qemu_syscall *call)
{
    struct qemu__aligned_msize *c = (struct qemu__aligned_msize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__aligned_msize(QEMU_G2H(c->p), c->alignment, c->offset);
}

#endif

struct qemu_calloc
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* CDECL MSVCRT_calloc(size_t count, size_t size)
{
    struct qemu_calloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CALLOC);
    call.count = count;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_calloc(struct qemu_syscall *call)
{
    struct qemu_calloc *c = (struct qemu_calloc *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_calloc(c->count, c->size));
}

#endif

struct qemu__calloc_base
{
    struct qemu_syscall super;
    uint64_t count;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* CDECL _calloc_base(size_t count, size_t size)
{
    struct qemu__calloc_base call;
    call.super.id = QEMU_SYSCALL_ID(CALL__CALLOC_BASE);
    call.count = count;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu__calloc_base(struct qemu_syscall *call)
{
    struct qemu__calloc_base *c = (struct qemu__calloc_base *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__calloc_base(c->count, c->size));
}

#endif

struct qemu_free
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT_free(void* ptr)
{
    struct qemu_free call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREE);
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);
}

#else

void qemu_free(struct qemu_syscall *call)
{
    struct qemu_free *c = (struct qemu_free *)call;
    WINE_TRACE("\n");
    p_free(QEMU_G2H(c->ptr));
}

#endif

struct qemu__free_base
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL _free_base(void* ptr)
{
    struct qemu__free_base call;
    call.super.id = QEMU_SYSCALL_ID(CALL__FREE_BASE);
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);
}

#else

void qemu__free_base(struct qemu_syscall *call)
{
    struct qemu__free_base *c = (struct qemu__free_base *)call;
    WINE_FIXME("Unverified!\n");
    p__free_base(QEMU_G2H(c->ptr));
}

#endif

struct qemu_malloc
{
    struct qemu_syscall super;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* CDECL MSVCRT_malloc(size_t size)
{
    struct qemu_malloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MALLOC);
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_malloc(struct qemu_syscall *call)
{
    struct qemu_malloc *c = (struct qemu_malloc *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_malloc(c->size));
}

#endif

struct qemu__malloc_base
{
    struct qemu_syscall super;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* CDECL _malloc_base(size_t size)
{
    struct qemu__malloc_base call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MALLOC_BASE);
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu__malloc_base(struct qemu_syscall *call)
{
    struct qemu__malloc_base *c = (struct qemu__malloc_base *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__malloc_base(c->size));
}

#endif

struct qemu_realloc
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* CDECL MSVCRT_realloc(void* ptr, size_t size)
{
    struct qemu_realloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REALLOC);
    call.ptr = (ULONG_PTR)ptr;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_realloc(struct qemu_syscall *call)
{
    struct qemu_realloc *c = (struct qemu_realloc *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_realloc(QEMU_G2H(c->ptr), c->size));
}

#endif

struct qemu__realloc_base
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* CDECL _realloc_base(void* ptr, size_t size)
{
    struct qemu__realloc_base call;
    call.super.id = QEMU_SYSCALL_ID(CALL__REALLOC_BASE);
    call.ptr = (ULONG_PTR)ptr;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu__realloc_base(struct qemu_syscall *call)
{
    struct qemu__realloc_base *c = (struct qemu__realloc_base *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__realloc_base(QEMU_G2H(c->ptr), c->size));
}

#endif

struct qemu__recalloc
{
    struct qemu_syscall super;
    uint64_t mem;
    uint64_t num;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* CDECL _recalloc(void *mem, size_t num, size_t size)
{
    struct qemu__recalloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL__RECALLOC);
    call.mem = (ULONG_PTR)mem;
    call.num = num;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu__recalloc(struct qemu_syscall *call)
{
    struct qemu__recalloc *c = (struct qemu__recalloc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__recalloc(QEMU_G2H(c->mem), c->num, c->size));
}

#endif

struct qemu___p__amblksiz
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI unsigned int* CDECL __p__amblksiz(void)
{
    struct qemu___p__amblksiz call;
    call.super.id = QEMU_SYSCALL_ID(CALL___P__AMBLKSIZ);

    qemu_syscall(&call.super);

    return (unsigned int *)call.super.iret;
}

#else

void qemu___p__amblksiz(struct qemu_syscall *call)
{
    struct qemu___p__amblksiz *c = (struct qemu___p__amblksiz *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p___p__amblksiz());
}

#endif

struct qemu__get_sbh_threshold
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL _get_sbh_threshold(void)
{
    struct qemu__get_sbh_threshold call;
    call.super.id = QEMU_SYSCALL_ID(CALL__GET_SBH_THRESHOLD);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__get_sbh_threshold(struct qemu_syscall *call)
{
    struct qemu__get_sbh_threshold *c = (struct qemu__get_sbh_threshold *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__get_sbh_threshold();
}

#endif

struct qemu__set_sbh_threshold
{
    struct qemu_syscall super;
    uint64_t threshold;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _set_sbh_threshold(size_t threshold)
{
    struct qemu__set_sbh_threshold call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SET_SBH_THRESHOLD);
    call.threshold = threshold;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__set_sbh_threshold(struct qemu_syscall *call)
{
    struct qemu__set_sbh_threshold *c = (struct qemu__set_sbh_threshold *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__set_sbh_threshold(c->threshold);
}

#endif

struct qemu__aligned_free
{
    struct qemu_syscall super;
    uint64_t memblock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL MSVCRT__aligned_free(void *memblock)
{
    struct qemu__aligned_free call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ALIGNED_FREE);
    call.memblock = (ULONG_PTR)memblock;

    qemu_syscall(&call.super);
}

#else

void qemu__aligned_free(struct qemu_syscall *call)
{
    struct qemu__aligned_free *c = (struct qemu__aligned_free *)call;
    WINE_FIXME("Unverified!\n");
    p__aligned_free(QEMU_G2H(c->memblock));
}

#endif

struct qemu__aligned_offset_malloc
{
    struct qemu_syscall super;
    uint64_t size;
    uint64_t alignment;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * CDECL _aligned_offset_malloc(size_t size, size_t alignment, size_t offset)
{
    struct qemu__aligned_offset_malloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ALIGNED_OFFSET_MALLOC);
    call.size = size;
    call.alignment = alignment;
    call.offset = offset;

    qemu_syscall(&call.super);
}

#else

void qemu__aligned_offset_malloc(struct qemu_syscall *call)
{
    struct qemu__aligned_offset_malloc *c = (struct qemu__aligned_offset_malloc *)call;
    WINE_FIXME("Unverified!\n");
    p__aligned_offset_malloc(c->size, c->alignment, c->offset);
}

#endif

struct qemu__aligned_malloc
{
    struct qemu_syscall super;
    uint64_t size;
    uint64_t alignment;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * CDECL MSVCRT__aligned_malloc(size_t size, size_t alignment)
{
    struct qemu__aligned_malloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ALIGNED_MALLOC);
    call.size = size;
    call.alignment = alignment;

    qemu_syscall(&call.super);
}

#else

void qemu__aligned_malloc(struct qemu_syscall *call)
{
    struct qemu__aligned_malloc *c = (struct qemu__aligned_malloc *)call;
    WINE_FIXME("Unverified!\n");
    p__aligned_malloc(c->size, c->alignment);
}

#endif

struct qemu__aligned_offset_realloc
{
    struct qemu_syscall super;
    uint64_t memblock;
    uint64_t size;
    uint64_t alignment;
    uint64_t offset;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * CDECL _aligned_offset_realloc(void *memblock, size_t size, size_t alignment, size_t offset)
{
    struct qemu__aligned_offset_realloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ALIGNED_OFFSET_REALLOC);
    call.memblock = (ULONG_PTR)memblock;
    call.size = size;
    call.alignment = alignment;
    call.offset = offset;

    qemu_syscall(&call.super);
}

#else

void qemu__aligned_offset_realloc(struct qemu_syscall *call)
{
    struct qemu__aligned_offset_realloc *c = (struct qemu__aligned_offset_realloc *)call;
    WINE_FIXME("Unverified!\n");
    p__aligned_offset_realloc(QEMU_G2H(c->memblock), c->size, c->alignment, c->offset);
}

#endif

struct qemu__aligned_realloc
{
    struct qemu_syscall super;
    uint64_t memblock;
    uint64_t size;
    uint64_t alignment;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * CDECL _aligned_realloc(void *memblock, size_t size, size_t alignment)
{
    struct qemu__aligned_realloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ALIGNED_REALLOC);
    call.memblock = (ULONG_PTR)memblock;
    call.size = size;
    call.alignment = alignment;

    qemu_syscall(&call.super);
}

#else

void qemu__aligned_realloc(struct qemu_syscall *call)
{
    struct qemu__aligned_realloc *c = (struct qemu__aligned_realloc *)call;
    WINE_FIXME("Unverified!\n");
    p__aligned_realloc(QEMU_G2H(c->memblock), c->size, c->alignment);
}

#endif

struct qemu_memmove_s
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t numberOfElements;
    uint64_t src;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_memmove_s(void *dest, size_t numberOfElements, const void *src, size_t count)
{
    struct qemu_memmove_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMMOVE_S);
    call.dest = (ULONG_PTR)dest;
    call.numberOfElements = numberOfElements;
    call.src = (ULONG_PTR)src;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_memmove_s(struct qemu_syscall *call)
{
    struct qemu_memmove_s *c = (struct qemu_memmove_s *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_memmove_s(QEMU_G2H(c->dest), c->numberOfElements, QEMU_G2H(c->src), c->count);
}

#endif

struct qemu_wmemmove_s
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t numberOfElements;
    uint64_t src;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL wmemmove_s(WCHAR *dest, size_t numberOfElements, const WCHAR *src, size_t count)
{
    struct qemu_wmemmove_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMEMMOVE_S);
    call.dest = (ULONG_PTR)dest;
    call.numberOfElements = numberOfElements;
    call.src = (ULONG_PTR)src;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wmemmove_s(struct qemu_syscall *call)
{
    struct qemu_wmemmove_s *c = (struct qemu_wmemmove_s *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wmemmove_s(QEMU_G2H(c->dest), c->numberOfElements, QEMU_G2H(c->src), c->count);
}

#endif

struct qemu_memcpy_s
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t numberOfElements;
    uint64_t src;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_memcpy_s(void *dest, size_t numberOfElements, const void *src, size_t count)
{
    struct qemu_memcpy_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMCPY_S);
    call.dest = (ULONG_PTR)dest;
    call.numberOfElements = numberOfElements;
    call.src = (ULONG_PTR)src;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_memcpy_s(struct qemu_syscall *call)
{
    struct qemu_memcpy_s *c = (struct qemu_memcpy_s *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_memcpy_s(QEMU_G2H(c->dest), c->numberOfElements, QEMU_G2H(c->src), c->count);
}

#endif

struct qemu_wmemcpy_s
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t numberOfElements;
    uint64_t src;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL wmemcpy_s(WCHAR *dest, size_t numberOfElements, const WCHAR *src, size_t count)
{
    struct qemu_wmemcpy_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WMEMCPY_S);
    call.dest = (ULONG_PTR)dest;
    call.numberOfElements = numberOfElements;
    call.src = (ULONG_PTR)src;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_wmemcpy_s(struct qemu_syscall *call)
{
    struct qemu_wmemcpy_s *c = (struct qemu_wmemcpy_s *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_wmemcpy_s(QEMU_G2H(c->dest), c->numberOfElements, QEMU_G2H(c->src), c->count);
}

#endif

struct qemu_strncpy_s
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t numberOfElements;
    uint64_t src;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL MSVCRT_strncpy_s(char *dest, size_t numberOfElements, const char *src, size_t count)
{
    struct qemu_strncpy_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRNCPY_S);
    call.dest = (ULONG_PTR)dest;
    call.numberOfElements = numberOfElements;
    call.src = (ULONG_PTR)src;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strncpy_s(struct qemu_syscall *call)
{
    struct qemu_strncpy_s *c = (struct qemu_strncpy_s *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strncpy_s(QEMU_G2H(c->dest), c->numberOfElements, QEMU_G2H(c->src), c->count);
}

#endif

