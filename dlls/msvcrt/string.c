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
#include "msvcrt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_msvcrt);
#endif

struct qemu__strdup
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

char * CDECL MSVCRT__strdup(const char *str)
{
    struct qemu__strdup call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRDUP);
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return (char *)call.super.iret;
}

#else

void qemu__strdup(struct qemu_syscall *call)
{
    struct qemu__strdup *c = (struct qemu__strdup *)call;
    WINE_TRACE("\n", c->str);
    c->super.iret = QEMU_H2G(p__strdup(QEMU_G2H(c->str)));
}

#endif

/* FIXME: Calling out of the vm for _stricmp is probably a waste of time. */
struct qemu__stricmp
{
    struct qemu_syscall super;
    uint64_t s1, s2;
};

#ifdef QEMU_DLL_GUEST

int __cdecl MSVCRT__stricmp(const char *s1, const char *s2)
{
    struct qemu__stricmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRICMP);
    call.s1 = (uint64_t)s1;
    call.s2 = (uint64_t)s2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__stricmp(struct qemu_syscall *call)
{
    struct qemu__stricmp *c = (struct qemu__stricmp *)call;
    WINE_TRACE("\n");
    c->super.iret = p__stricmp(QEMU_G2H(c->s1), QEMU_G2H(c->s2));
}

#endif

/* FIXME: Calling out of the vm for _strtoui64 is probably a waste of time. */
struct qemu__strtoui64
{
    struct qemu_syscall super;
    uint64_t nptr, endptr;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT__strtoui64(const char *nptr, char **endptr, int base)
{
    struct qemu__strtoui64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRTOUI64);
    call.nptr = (uint64_t)nptr;
    call.endptr = (uint64_t)endptr;
    call.base = base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strtoui64(struct qemu_syscall *call)
{
    struct qemu__strtoui64 *c = (struct qemu__strtoui64 *)call;
    WINE_TRACE("\n");
    c->super.iret = p__strtoui64(QEMU_G2H(c->nptr), QEMU_G2H(c->endptr), c->base);
}

#endif

struct qemu_atof
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

double CDECL MSVCRT_atof(const char *str)
{
    struct qemu_atof call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATOF);
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_atof(struct qemu_syscall *call)
{
    struct qemu_atof *c = (struct qemu_atof *)call;
    WINE_TRACE("\n");
    c->super.dret = p_atof(QEMU_G2H(c->str));
}

#endif

/* FIXME: Calling out of the vm for memcmp is probably a waste of time. */
struct qemu_memcmp
{
    struct qemu_syscall super;
    uint64_t ptr1, ptr2;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_memcmp(const void *ptr1, const void *ptr2, size_t size)
{
    struct qemu_memcmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMCMP);
    call.ptr1 = (uint64_t)ptr1;
    call.ptr2 = (uint64_t)ptr2;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_memcmp(struct qemu_syscall *call)
{
    struct qemu_memcmp *c = (struct qemu_memcmp *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_memcmp(QEMU_G2H(c->ptr1), QEMU_G2H(c->ptr2), c->size));
}

#endif

/* FIXME: Calling out of the vm for memset is probably a waste of time. */
struct qemu_memset
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t c;
    uint64_t size;
};


#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_memset(void *ptr,int c,size_t size)
{
    struct qemu_memset call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMSET);
    call.ptr = (uint64_t)ptr;
    call.c = c;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_memset(struct qemu_syscall *call)
{
    struct qemu_memset *c = (struct qemu_memset *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_memset(QEMU_G2H(c->ptr), c->c, c->size));
}

#endif

/* FIXME: Calling out of the vm for memcpy and memmove is probably a waste of time. */
struct qemu_memcpy
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

void * CDECL MSVCRT_memcpy(void *dst, const void *src, size_t size)
{
    struct qemu_memcpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMCPY);
    call.dst = (uint64_t)dst;
    call.src = (uint64_t)src;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

void * CDECL MSVCRT_memmove(void *dst, const void *src, size_t size)
{
    struct qemu_memcpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMMOVE);
    call.dst = (uint64_t)dst;
    call.src = (uint64_t)src;
    call.size = size;

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

void qemu_memmove(struct qemu_syscall *call)
{
    struct qemu_memcpy *c = (struct qemu_memcpy *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_memmove(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->size));
}

void qemu_memcpy(struct qemu_syscall *call)
{
    struct qemu_memcpy *c = (struct qemu_memcpy *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_memcpy(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->size));
}

#endif

/* FIXME: Calling out of the vm for strcat_s is probably a waste of time. */
struct qemu_strcat_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t elem;
    uint64_t src;
};


#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_strcat_s(char *dst, size_t elem, const char *src)
{
    struct qemu_strcat_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCAT_S);
    call.dst = (uint64_t)dst;
    call.elem = elem;
    call.src = (uint64_t)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strcat_s(struct qemu_syscall *call)
{
    struct qemu_strcat_s *c = (struct qemu_strcat_s *)call;
    WINE_TRACE("\n");
    c->super.iret = p_strcat_s(QEMU_G2H(c->dst), c->elem, QEMU_G2H(c->src));
}

#endif

/* FIXME: Calling out of the vm for strcpy_s is probably a waste of time. */
struct qemu_strcpy_s
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t elem;
    uint64_t src;
};


#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_strcpy_s(char *dst, size_t elem, const char *src)
{
    struct qemu_strcpy_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCPY_S);
    call.dst = (uint64_t)dst;
    call.elem = elem;
    call.src = (uint64_t)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strcpy_s(struct qemu_syscall *call)
{
    struct qemu_strcpy_s *c = (struct qemu_strcpy_s *)call;
    WINE_TRACE("\n");
    c->super.iret = p_strcpy_s(QEMU_G2H(c->dst), c->elem, QEMU_G2H(c->src));
}

#endif

/* FIXME: Calling out of the vm for strlen is probably a waste of time. */
struct qemu_strlen
{
    struct qemu_syscall super;
    uint64_t str;
};


#ifdef QEMU_DLL_GUEST

size_t CDECL MSVCRT_strlen(const char *str)
{
    struct qemu_strlen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRLEN);
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strlen(struct qemu_syscall *call)
{
    struct qemu_strlen *c = (struct qemu_strlen *)call;
    WINE_TRACE("\n");
    c->super.iret = p_strlen(QEMU_G2H(c->str));
}

#endif

/* FIXME: Calling out of the vm for strncmp is probably a waste of time. */
struct qemu_strncmp
{
    struct qemu_syscall super;
    uint64_t str1, str2;
    uint64_t len;
};


#ifdef QEMU_DLL_GUEST

int CDECL MSVCRT_strncmp(const char *str1, const char *str2, size_t len)
{
    struct qemu_strncmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRNCMP);
    call.str1 = (uint64_t)str1;
    call.str2 = (uint64_t)str2;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strncmp(struct qemu_syscall *call)
{
    struct qemu_strncmp *c = (struct qemu_strncmp *)call;
    WINE_TRACE("\n");
    c->super.iret = p_strncmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->len);
}

#endif

struct qemu_strtod
{
    struct qemu_syscall super;
    uint64_t str, end;
};


#ifdef QEMU_DLL_GUEST

double CDECL MSVCRT_strtod(const char *str, char **end)
{
    struct qemu_strtod call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOD);
    call.str = (uint64_t)str;
    call.end = (uint64_t)end;

    qemu_syscall(&call.super);

    return call.super.dret;
}

#else

void qemu_strtod(struct qemu_syscall *call)
{
    struct qemu_strtod *c = (struct qemu_strtod *)call;
    WINE_TRACE("\n");
    c->super.dret = p_strtod(QEMU_G2H(c->str), QEMU_G2H(c->end));
}

#endif
