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
#include "qemu_msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

struct qemu___crt_debugger_hook
{
    struct qemu_syscall super;
    uint64_t reserved;
};


#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT___crt_debugger_hook(int reserved)
{
    struct qemu___crt_debugger_hook call;
    call.super.id = QEMU_SYSCALL_ID(CALL___CRT_DEBUGGER_HOOK);
    call.reserved = (ULONG_PTR)reserved;

    qemu_syscall(&call.super);
}

#else

void qemu___crt_debugger_hook(struct qemu_syscall *call)
{
    struct qemu___crt_debugger_hook *c = (struct qemu___crt_debugger_hook *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    p___crt_debugger_hook(c->reserved);
}

#endif

/* FIXME: The context switch cost of this thing is most likely horrible. */
struct qemu_bsearch
{
    struct qemu_syscall super;
    uint64_t key;
    uint64_t base;
    uint64_t nmemb;
    uint64_t size;
    uint64_t compare;
    uint64_t wrapper;
};

struct qemu_bsearch_cb
{
    uint64_t func;
    uint64_t ptr1, ptr2;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall bsearch_guest_wrapper(const struct qemu_bsearch_cb *cb)
{
    int (__cdecl *compare)(const void *,const void *) = (void *)(ULONG_PTR)cb->func;

    return compare((void *)(ULONG_PTR)cb->ptr1, (void *)(ULONG_PTR)cb->ptr2);
}

void * CDECL MSVCRT_bsearch(const void *key, const void *base, size_t nmemb,
        size_t size, int (__cdecl *compare)(const void *, const void *))
{
    struct qemu_bsearch call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BSEARCH);
    call.key = (ULONG_PTR)key;
    call.base = (ULONG_PTR)base;
    call.nmemb = nmemb;
    call.size = size;
    call.compare = (ULONG_PTR)compare;
    call.wrapper = (ULONG_PTR)bsearch_guest_wrapper;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

static uint64_t bsearch_guest_wrapper;

static int CDECL bsearch_wrapper(const void *ptr1, const void *ptr2)
{
    uint64_t *guest_proc = TlsGetValue(msvcrt_tls);
    struct qemu_bsearch_cb stack_copy, *call = &stack_copy;
    int ret;

#if HOST_BIT != GUEST_BIT
    call = HeapAlloc(GetProcessHeap(), 0, sizeof(*call));
#endif

    call->func = *guest_proc;
    call->ptr1 = QEMU_H2G(ptr1);
    call->ptr2 = QEMU_H2G(ptr2);

    WINE_TRACE("Calling guest proc 0x%lx(%p, %p).\n", (unsigned long)*guest_proc, ptr1, ptr2);
    ret = qemu_ops->qemu_execute(QEMU_G2H(bsearch_guest_wrapper), QEMU_H2G(call));
    WINE_TRACE("Guest proc returned %d.\n", ret);

    if (call != &stack_copy)
        HeapFree(GetProcessHeap(), 0, call);

    return ret;
}

void qemu_bsearch(struct qemu_syscall *call)
{
    struct qemu_bsearch *c = (struct qemu_bsearch *)(ULONG_PTR)call;
    uint64_t *old = TlsGetValue(msvcrt_tls);
    WINE_TRACE("\n");

    bsearch_guest_wrapper = c->wrapper;
    TlsSetValue(msvcrt_tls, &c->compare);
    c->super.iret = QEMU_H2G(p_bsearch(QEMU_G2H(c->key), QEMU_G2H(c->base), c->nmemb, c->size, bsearch_wrapper));

    TlsSetValue(msvcrt_tls, old);
}

#endif

/* FIXME: The context switch cost of this thing is most likely horrible. */
struct qemu_qsort
{
    struct qemu_syscall super;
    uint64_t base;
    uint64_t elem_count;
    uint64_t elem_size;
    uint64_t compare;
    uint64_t wrapper;
};

struct qemu_qsort_cb
{
    uint64_t func;
    uint64_t ptr1, ptr2;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall qsort_guest_wrapper(void *data)
{
    const struct qemu_qsort_cb *cb = data;
    int (__cdecl *compare)(const void *,const void *) = (void *)(ULONG_PTR)cb->func;

    return compare((void *)(ULONG_PTR)cb->ptr1, (void *)(ULONG_PTR)cb->ptr2);
}

void __cdecl MSVCRT_qsort(void *base, size_t elem_count, size_t elem_size,
        int (__cdecl *compare)(const void *,const void *))
{
    struct qemu_qsort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QSORT);
    call.base = (ULONG_PTR)base;
    call.elem_count = elem_count;
    call.elem_size = elem_size;
    call.compare = (ULONG_PTR)compare;
    call.wrapper = (ULONG_PTR)qsort_guest_wrapper;

    qemu_syscall(&call.super);
}

#else

static uint64_t qsort_guest_wrapper;

static int CDECL qsort_wrapper(const void *ptr1, const void *ptr2)
{
    uint64_t *guest_proc = TlsGetValue(msvcrt_tls);
    struct qemu_qsort_cb call = {*guest_proc, QEMU_H2G(ptr1), QEMU_H2G(ptr2)};
    int ret;

    WINE_TRACE("Calling guest proc 0x%lx(%p, %p).\n", (unsigned long)*guest_proc, ptr1, ptr2);
    ret = qemu_ops->qemu_execute(QEMU_G2H(qsort_guest_wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest proc returned %d.\n", ret);

    return ret;
}

void qemu_qsort(struct qemu_syscall *call)
{
    struct qemu_qsort *c = (struct qemu_qsort *)(ULONG_PTR)call;
    WINE_TRACE("\n");

    qsort_guest_wrapper = c->wrapper;
    TlsSetValue(msvcrt_tls, &c->compare);
    p_qsort(QEMU_G2H(c->base), c->elem_count, c->elem_size, qsort_wrapper);
}

#endif

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_rand(void)
{
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_RAND);

    qemu_syscall(&call);

    return call.iret;
}

#else

void qemu_rand(struct qemu_syscall *c)
{
    WINE_TRACE("\n");
    c->iret = p_rand();
}

#endif

struct qemu_srand
{
    struct qemu_syscall super;
    uint64_t seed;
};

#ifdef QEMU_DLL_GUEST

void CDECL MSVCRT_srand(unsigned int seed)
{
    struct qemu_srand call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SRAND);
    call.seed = seed;

    qemu_syscall(&call.super);
}

#else

void qemu_srand(struct qemu_syscall *call)
{
    struct qemu_srand *c = (struct qemu_srand *)(ULONG_PTR)call;
    WINE_TRACE("\n");
    p_srand(c->seed);
}

#endif

struct qemu_decode_pointer
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_decode_pointer(void * ptr)
{
    struct qemu_decode_pointer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DECODE_POINTER);
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);
}

#else

void qemu_decode_pointer(struct qemu_syscall *call)
{
    struct qemu_decode_pointer *c = (struct qemu_decode_pointer *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_decode_pointer(QEMU_G2H(c->ptr)));
}

#endif

struct qemu_encode_pointer
{
    struct qemu_syscall super;
    uint64_t ptr;
};

#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_encode_pointer(void * ptr)
{
    struct qemu_encode_pointer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENCODE_POINTER);
    call.ptr = (ULONG_PTR)ptr;

    qemu_syscall(&call.super);
}

#else

void qemu_encode_pointer(struct qemu_syscall *call)
{
    struct qemu_encode_pointer *c = (struct qemu_encode_pointer *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_encode_pointer(QEMU_G2H(c->ptr)));
}

#endif

struct qemu__encoded_null
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

void * CDECL _encoded_null(void)
{
    struct qemu__encoded_null call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ENCODED_NULL);

    qemu_syscall(&call.super);
}

#else

void qemu__encoded_null(struct qemu_syscall *call)
{
    struct qemu__encoded_null *c = (struct qemu__encoded_null *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p__encoded_null());
}

#endif

#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_generic_stub(void)
{
    /* The @stub entries in .spec files don't work in mingw builds. Provide this function for
     * stubs that are actually imported to shut up the loader warnings. */
    struct qemu_syscall call;
    call.id = QEMU_SYSCALL_ID(CALL_GENERIC_STUB);

    qemu_syscall(&call);
}

#else

void qemu_generic_stub(struct qemu_syscall *call)
{
    WINE_FIXME("MSVCRT's generic stub function has been called...\n");
    DebugBreak();
    ExitProcess(1);
}

#endif
