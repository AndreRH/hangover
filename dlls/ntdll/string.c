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
#include <ntdef.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif


struct qemu_memchr
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t c;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * CDECL NTDLL_memchr(const void *ptr, int c, size_t n)
{
    struct qemu_memchr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMCHR);
    call.ptr = (ULONG_PTR)ptr;
    call.c = (ULONG_PTR)c;
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_memchr(struct qemu_syscall *call)
{
    struct qemu_memchr *c = (struct qemu_memchr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_memchr(QEMU_G2H(c->ptr), c->c, c->n));
}

#endif

struct qemu_memcmp
{
    struct qemu_syscall super;
    uint64_t ptr1;
    uint64_t ptr2;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
    struct qemu_memcmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMCMP);
    call.ptr1 = (ULONG_PTR)ptr1;
    call.ptr2 = (ULONG_PTR)ptr2;
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_memcmp(struct qemu_syscall *call)
{
    struct qemu_memcmp *c = (struct qemu_memcmp *)call;
    WINE_TRACE("\n");
    c->super.iret = p_memcmp(QEMU_G2H(c->ptr1), QEMU_G2H(c->ptr2), c->n);
}

#endif

struct qemu_memcpy
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * CDECL NTDLL_memcpy(void *dst, const void *src, size_t n)
{
    struct qemu_memcpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMCPY);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_memcpy(struct qemu_syscall *call)
{
    struct qemu_memcpy *c = (struct qemu_memcpy *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_memcpy(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->n));
}

#endif

struct qemu_memmove
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * CDECL NTDLL_memmove(void *dst, const void *src, size_t n)
{
    struct qemu_memmove call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMMOVE);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_memmove(struct qemu_syscall *call)
{
    struct qemu_memmove *c = (struct qemu_memmove *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_memmove(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->n));
}

#endif

struct qemu_memset
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t c;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * CDECL NTDLL_memset(void *dst, int c, size_t n)
{
    struct qemu_memset call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MEMSET);
    call.dst = (ULONG_PTR)dst;
    call.c = (ULONG_PTR)c;
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_memset(struct qemu_syscall *call)
{
    struct qemu_memset *c = (struct qemu_memset *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_memset(QEMU_G2H(c->dst), c->c, c->n));
}

#endif

struct qemu_strcat
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL NTDLL_strcat(char *dst, const char *src)
{
    struct qemu_strcat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCAT);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strcat(struct qemu_syscall *call)
{
    struct qemu_strcat *c = (struct qemu_strcat *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_strcat(QEMU_G2H(c->dst), QEMU_G2H(c->src)));
}

#endif

struct qemu_strchr
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL NTDLL_strchr(const char *str, int c)
{
    struct qemu_strchr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCHR);
    call.str = (ULONG_PTR)str;
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strchr(struct qemu_syscall *call)
{
    struct qemu_strchr *c = (struct qemu_strchr *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_strchr(QEMU_G2H(c->str), c->c));
}

#endif

struct qemu_strcmp
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_strcmp(const char *str1, const char *str2)
{
    struct qemu_strcmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCMP);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strcmp(struct qemu_syscall *call)
{
    struct qemu_strcmp *c = (struct qemu_strcmp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strcmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu_strcpy
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL NTDLL_strcpy(char *dst, const char *src)
{
    struct qemu_strcpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCPY);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strcpy(struct qemu_syscall *call)
{
    struct qemu_strcpy *c = (struct qemu_strcpy *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_strcpy(QEMU_G2H(c->dst), QEMU_G2H(c->src)));
}

#endif

struct qemu_strcspn
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t reject;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL NTDLL_strcspn(const char *str, const char *reject)
{
    struct qemu_strcspn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRCSPN);
    call.str = (ULONG_PTR)str;
    call.reject = (ULONG_PTR)reject;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strcspn(struct qemu_syscall *call)
{
    struct qemu_strcspn *c = (struct qemu_strcspn *)call;
    WINE_TRACE("\n");
    c->super.iret = p_strcspn(QEMU_G2H(c->str), QEMU_G2H(c->reject));
}

#endif

struct qemu_strlen
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL NTDLL_strlen(const char *str)
{
    struct qemu_strlen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRLEN);
    call.str = (ULONG_PTR)str;

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

struct qemu_strncat
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL NTDLL_strncat(char *dst, const char *src, size_t len)
{
    struct qemu_strncat call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRNCAT);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strncat(struct qemu_syscall *call)
{
    struct qemu_strncat *c = (struct qemu_strncat *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_strncat(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->len));
}

#endif

struct qemu_strncmp
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_strncmp(const char *str1, const char *str2, size_t len)
{
    struct qemu_strncmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRNCMP);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.len = (ULONG_PTR)len;

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

struct qemu_strncpy
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL NTDLL_strncpy(char *dst, const char *src, size_t len)
{
    struct qemu_strncpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRNCPY);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strncpy(struct qemu_syscall *call)
{
    struct qemu_strncpy *c = (struct qemu_strncpy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_strncpy(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->len));
}

#endif

struct qemu_strpbrk
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t accept;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL NTDLL_strpbrk(const char *str, const char *accept)
{
    struct qemu_strpbrk call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRPBRK);
    call.str = (ULONG_PTR)str;
    call.accept = (ULONG_PTR)accept;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strpbrk(struct qemu_syscall *call)
{
    struct qemu_strpbrk *c = (struct qemu_strpbrk *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_strpbrk(QEMU_G2H(c->str), QEMU_G2H(c->accept)));
}

#endif

struct qemu_strrchr
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL NTDLL_strrchr(const char *str, int c)
{
    struct qemu_strrchr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRCHR);
    call.str = (ULONG_PTR)str;
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strrchr(struct qemu_syscall *call)
{
    struct qemu_strrchr *c = (struct qemu_strrchr *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(p_strrchr(QEMU_G2H(c->str), c->c));
}

#endif

struct qemu_strspn
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t accept;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI size_t CDECL NTDLL_strspn(const char *str, const char *accept)
{
    struct qemu_strspn call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRSPN);
    call.str = (ULONG_PTR)str;
    call.accept = (ULONG_PTR)accept;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strspn(struct qemu_syscall *call)
{
    struct qemu_strspn *c = (struct qemu_strspn *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strspn(QEMU_G2H(c->str), QEMU_G2H(c->accept));
}

#endif

struct qemu_strstr
{
    struct qemu_syscall super;
    uint64_t haystack;
    uint64_t needle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL NTDLL_strstr(const char *haystack, const char *needle)
{
    struct qemu_strstr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRSTR);
    call.haystack = (ULONG_PTR)haystack;
    call.needle = (ULONG_PTR)needle;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_strstr(struct qemu_syscall *call)
{
    struct qemu_strstr *c = (struct qemu_strstr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_strstr(QEMU_G2H(c->haystack), QEMU_G2H(c->needle)));
}

#endif

struct qemu__memccpy
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t c;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void * CDECL _memccpy(void *dst, const void *src, int c, size_t n)
{
    struct qemu__memccpy call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MEMCCPY);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.c = (ULONG_PTR)c;
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return (void *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__memccpy(struct qemu_syscall *call)
{
    struct qemu__memccpy *c = (struct qemu__memccpy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__memccpy(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->c, c->n));
}

#endif

struct qemu__memicmp
{
    struct qemu_syscall super;
    uint64_t s1;
    uint64_t s2;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT CDECL NTDLL__memicmp(LPCSTR s1, LPCSTR s2, DWORD len)
{
    struct qemu__memicmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__MEMICMP);
    call.s1 = (ULONG_PTR)s1;
    call.s2 = (ULONG_PTR)s2;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__memicmp(struct qemu_syscall *call)
{
    struct qemu__memicmp *c = (struct qemu__memicmp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__memicmp(QEMU_G2H(c->s1), QEMU_G2H(c->s2), c->len));
}

#endif

struct qemu__stricmp
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _stricmp(LPCSTR str1, LPCSTR str2)
{
    struct qemu__stricmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRICMP);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__stricmp(struct qemu_syscall *call)
{
    struct qemu__stricmp *c = (struct qemu__stricmp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__stricmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu__strnicmp
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
    uint64_t n;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL _strnicmp(LPCSTR str1, LPCSTR str2, size_t n)
{
    struct qemu__strnicmp call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRNICMP);
    call.str1 = (ULONG_PTR)str1;
    call.str2 = (ULONG_PTR)str2;
    call.n = (ULONG_PTR)n;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__strnicmp(struct qemu_syscall *call)
{
    struct qemu__strnicmp *c = (struct qemu__strnicmp *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__strnicmp(QEMU_G2H(c->str1), QEMU_G2H(c->str2), c->n);
}

#endif

struct qemu__strupr
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR CDECL _strupr(LPSTR str)
{
    struct qemu__strupr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRUPR);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu__strupr(struct qemu_syscall *call)
{
    struct qemu__strupr *c = (struct qemu__strupr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strupr(QEMU_G2H(c->str)));
}

#endif

struct qemu__strlwr
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPSTR CDECL _strlwr(LPSTR str)
{
    struct qemu__strlwr call;
    call.super.id = QEMU_SYSCALL_ID(CALL__STRLWR);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return (LPSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu__strlwr(struct qemu_syscall *call)
{
    struct qemu__strlwr *c = (struct qemu__strlwr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__strlwr(QEMU_G2H(c->str)));
}

#endif

struct qemu_tolower
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_tolower(int c)
{
    struct qemu_tolower call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TOLOWER);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_tolower(struct qemu_syscall *call)
{
    struct qemu_tolower *c = (struct qemu_tolower *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_tolower(c->c);
}

#endif

struct qemu_toupper
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_toupper(int c)
{
    struct qemu_toupper call;
    call.super.id = QEMU_SYSCALL_ID(CALL_TOUPPER);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_toupper(struct qemu_syscall *call)
{
    struct qemu_toupper *c = (struct qemu_toupper *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_toupper(c->c);
}

#endif

struct qemu_isalnum
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_isalnum(int c)
{
    struct qemu_isalnum call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISALNUM);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isalnum(struct qemu_syscall *call)
{
    struct qemu_isalnum *c = (struct qemu_isalnum *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_isalnum(c->c);
}

#endif

struct qemu_isalpha
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_isalpha(int c)
{
    struct qemu_isalpha call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISALPHA);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isalpha(struct qemu_syscall *call)
{
    struct qemu_isalpha *c = (struct qemu_isalpha *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_isalpha(c->c);
}

#endif

struct qemu_iscntrl
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_iscntrl(int c)
{
    struct qemu_iscntrl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISCNTRL);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_iscntrl(struct qemu_syscall *call)
{
    struct qemu_iscntrl *c = (struct qemu_iscntrl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_iscntrl(c->c);
}

#endif

struct qemu_isdigit
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_isdigit(int c)
{
    struct qemu_isdigit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISDIGIT);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isdigit(struct qemu_syscall *call)
{
    struct qemu_isdigit *c = (struct qemu_isdigit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_isdigit(c->c);
}

#endif

struct qemu_isgraph
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_isgraph(int c)
{
    struct qemu_isgraph call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISGRAPH);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isgraph(struct qemu_syscall *call)
{
    struct qemu_isgraph *c = (struct qemu_isgraph *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_isgraph(c->c);
}

#endif

struct qemu_islower
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_islower(int c)
{
    struct qemu_islower call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISLOWER);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_islower(struct qemu_syscall *call)
{
    struct qemu_islower *c = (struct qemu_islower *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_islower(c->c);
}

#endif

struct qemu_isprint
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_isprint(int c)
{
    struct qemu_isprint call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISPRINT);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isprint(struct qemu_syscall *call)
{
    struct qemu_isprint *c = (struct qemu_isprint *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_isprint(c->c);
}

#endif

struct qemu_ispunct
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_ispunct(int c)
{
    struct qemu_ispunct call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISPUNCT);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ispunct(struct qemu_syscall *call)
{
    struct qemu_ispunct *c = (struct qemu_ispunct *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_ispunct(c->c);
}

#endif

struct qemu_isspace
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_isspace(int c)
{
    struct qemu_isspace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISSPACE);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isspace(struct qemu_syscall *call)
{
    struct qemu_isspace *c = (struct qemu_isspace *)call;
    WINE_TRACE("\n");
    c->super.iret = p_isspace(c->c);
}

#endif

struct qemu_isupper
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_isupper(int c)
{
    struct qemu_isupper call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISUPPER);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isupper(struct qemu_syscall *call)
{
    struct qemu_isupper *c = (struct qemu_isupper *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_isupper(c->c);
}

#endif

struct qemu_isxdigit
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_isxdigit(int c)
{
    struct qemu_isxdigit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISXDIGIT);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_isxdigit(struct qemu_syscall *call)
{
    struct qemu_isxdigit *c = (struct qemu_isxdigit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_isxdigit(c->c);
}

#endif

struct qemu___isascii
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL___isascii(int c)
{
    struct qemu___isascii call;
    call.super.id = QEMU_SYSCALL_ID(CALL___ISASCII);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___isascii(struct qemu_syscall *call)
{
    struct qemu___isascii *c = (struct qemu___isascii *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___isascii(c->c);
}

#endif

struct qemu___toascii
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL___toascii(int c)
{
    struct qemu___toascii call;
    call.super.id = QEMU_SYSCALL_ID(CALL___TOASCII);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___toascii(struct qemu_syscall *call)
{
    struct qemu___toascii *c = (struct qemu___toascii *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___toascii(c->c);
}

#endif

struct qemu___iscsym
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL___iscsym(int c)
{
    struct qemu___iscsym call;
    call.super.id = QEMU_SYSCALL_ID(CALL___ISCSYM);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___iscsym(struct qemu_syscall *call)
{
    struct qemu___iscsym *c = (struct qemu___iscsym *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___iscsym(c->c);
}

#endif

struct qemu___iscsymf
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL___iscsymf(int c)
{
    struct qemu___iscsymf call;
    call.super.id = QEMU_SYSCALL_ID(CALL___ISCSYMF);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___iscsymf(struct qemu_syscall *call)
{
    struct qemu___iscsymf *c = (struct qemu___iscsymf *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p___iscsymf(c->c);
}

#endif

struct qemu__toupper
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL__toupper(int c)
{
    struct qemu__toupper call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TOUPPER);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__toupper(struct qemu_syscall *call)
{
    struct qemu__toupper *c = (struct qemu__toupper *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__toupper(c->c);
}

#endif

struct qemu__tolower
{
    struct qemu_syscall super;
    uint64_t c;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL__tolower(int c)
{
    struct qemu__tolower call;
    call.super.id = QEMU_SYSCALL_ID(CALL__TOLOWER);
    call.c = (ULONG_PTR)c;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__tolower(struct qemu_syscall *call)
{
    struct qemu__tolower *c = (struct qemu__tolower *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__tolower(c->c);
}

#endif

struct qemu_strtol
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t endptr;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG CDECL NTDLL_strtol(const char *nptr, char **endptr, int base)
{
    struct qemu_strtol call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOL);
    call.nptr = (ULONG_PTR)nptr;
    call.endptr = (ULONG_PTR)endptr;
    call.base = (ULONG_PTR)base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strtol(struct qemu_syscall *call)
{
    struct qemu_strtol *c = (struct qemu_strtol *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strtol(QEMU_G2H(c->nptr), QEMU_G2H(c->endptr), c->base);
}

#endif

struct qemu_strtoul
{
    struct qemu_syscall super;
    uint64_t nptr;
    uint64_t endptr;
    uint64_t base;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG CDECL NTDLL_strtoul(const char *nptr, char **endptr, int base)
{
    struct qemu_strtoul call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOUL);
    call.nptr = (ULONG_PTR)nptr;
    call.endptr = (ULONG_PTR)endptr;
    call.base = (ULONG_PTR)base;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_strtoul(struct qemu_syscall *call)
{
    struct qemu_strtoul *c = (struct qemu_strtoul *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_strtoul(QEMU_G2H(c->nptr), QEMU_G2H(c->endptr), c->base);
}

#endif

struct qemu__ultoa
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL _ultoa(ULONG value, char *str, int radix)
{
    struct qemu__ultoa call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ULTOA);
    call.value = (ULONG_PTR)value;
    call.str = (ULONG_PTR)str;
    call.radix = (ULONG_PTR)radix;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__ultoa(struct qemu_syscall *call)
{
    struct qemu__ultoa *c = (struct qemu__ultoa *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__ultoa(c->value, QEMU_G2H(c->str), c->radix));
}

#endif

struct qemu__ltoa
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL _ltoa(LONG value, char *str, int radix)
{
    struct qemu__ltoa call;
    call.super.id = QEMU_SYSCALL_ID(CALL__LTOA);
    call.value = (ULONG_PTR)value;
    call.str = (ULONG_PTR)str;
    call.radix = (ULONG_PTR)radix;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__ltoa(struct qemu_syscall *call)
{
    struct qemu__ltoa *c = (struct qemu__ltoa *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__ltoa(c->value, QEMU_G2H(c->str), c->radix));
}

#endif

struct qemu__itoa
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL _itoa(int value, char *str, int radix)
{
    struct qemu__itoa call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ITOA);
    call.value = (ULONG_PTR)value;
    call.str = (ULONG_PTR)str;
    call.radix = (ULONG_PTR)radix;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__itoa(struct qemu_syscall *call)
{
    struct qemu__itoa *c = (struct qemu__itoa *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__itoa(c->value, QEMU_G2H(c->str), c->radix));
}

#endif

struct qemu__ui64toa
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL _ui64toa(ULONGLONG value, char *str, int radix)
{
    struct qemu__ui64toa call;
    call.super.id = QEMU_SYSCALL_ID(CALL__UI64TOA);
    call.value = (ULONG_PTR)value;
    call.str = (ULONG_PTR)str;
    call.radix = (ULONG_PTR)radix;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__ui64toa(struct qemu_syscall *call)
{
    struct qemu__ui64toa *c = (struct qemu__ui64toa *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__ui64toa(c->value, QEMU_G2H(c->str), c->radix));
}

#endif

struct qemu__i64toa
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t str;
    uint64_t radix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char * CDECL _i64toa(LONGLONG value, char *str, int radix)
{
    struct qemu__i64toa call;
    call.super.id = QEMU_SYSCALL_ID(CALL__I64TOA);
    call.value = (ULONG_PTR)value;
    call.str = (ULONG_PTR)str;
    call.radix = (ULONG_PTR)radix;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu__i64toa(struct qemu_syscall *call)
{
    struct qemu__i64toa *c = (struct qemu__i64toa *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p__i64toa(c->value, QEMU_G2H(c->str), c->radix));
}

#endif

struct qemu__atoi64
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONGLONG CDECL _atoi64(const char *str)
{
    struct qemu__atoi64 call;
    call.super.id = QEMU_SYSCALL_ID(CALL__ATOI64);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__atoi64(struct qemu_syscall *call)
{
    struct qemu__atoi64 *c = (struct qemu__atoi64 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p__atoi64(QEMU_G2H(c->str));
}

#endif

struct qemu_atoi
{
    struct qemu_syscall super;
    uint64_t nptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_atoi(const char *nptr)
{
    struct qemu_atoi call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATOI);
    call.nptr = (ULONG_PTR)nptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_atoi(struct qemu_syscall *call)
{
    struct qemu_atoi *c = (struct qemu_atoi *)call;
    WINE_TRACE("\n");
    c->super.iret = p_atoi(QEMU_G2H(c->nptr));
}

#endif

struct qemu_atol
{
    struct qemu_syscall super;
    uint64_t nptr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG CDECL NTDLL_atol(const char *nptr)
{
    struct qemu_atol call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ATOL);
    call.nptr = (ULONG_PTR)nptr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_atol(struct qemu_syscall *call)
{
    struct qemu_atol *c = (struct qemu_atol *)call;
    WINE_TRACE("\n");
    c->super.iret = p_atol(QEMU_G2H(c->nptr));
}

#endif

struct qemu__splitpath
{
    struct qemu_syscall super;
    uint64_t inpath;
    uint64_t drv;
    uint64_t dir;
    uint64_t fname;
    uint64_t ext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void CDECL _splitpath(const char* inpath, char * drv, char * dir, char* fname, char * ext)
{
    struct qemu__splitpath call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SPLITPATH);
    call.inpath = (ULONG_PTR)inpath;
    call.drv = (ULONG_PTR)drv;
    call.dir = (ULONG_PTR)dir;
    call.fname = (ULONG_PTR)fname;
    call.ext = (ULONG_PTR)ext;

    qemu_syscall(&call.super);
}

#else

void qemu__splitpath(struct qemu_syscall *call)
{
    struct qemu__splitpath *c = (struct qemu__splitpath *)call;
    WINE_FIXME("Unverified!\n");
    p__splitpath(QEMU_G2H(c->inpath), QEMU_G2H(c->drv), QEMU_G2H(c->dir), QEMU_G2H(c->fname), QEMU_G2H(c->ext));
}

#endif

struct qemu_sscanf
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPIV NTDLL_sscanf(const char *str, const char *format, ...)
{
    struct qemu_sscanf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDLL_SSCANF);
    call.str = (ULONG_PTR)str;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NTDLL_sscanf(struct qemu_syscall *call)
{
    struct qemu_sscanf *c = (struct qemu_sscanf *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = 0;
}

#endif
