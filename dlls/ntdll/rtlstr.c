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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ntdef.h>

#include "thunk/qemu_winternl.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifdef QEMU_DLL_GUEST

/* I can't make mingw's ddk headers work :-( . */

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_RtlInitAnsiString
{
    struct qemu_syscall super;
    uint64_t target;
    uint64_t source;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlInitAnsiString(PANSI_STRING target, PCSZ source)
{
    struct qemu_RtlInitAnsiString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITANSISTRING);
    call.target = (ULONG_PTR)target;
    call.source = (ULONG_PTR)source;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlInitAnsiString(struct qemu_syscall *call)
{
    struct qemu_RtlInitAnsiString *c = (struct qemu_RtlInitAnsiString *)call;
    ANSI_STRING stack, *target = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    target = QEMU_G2H(c->target);
#endif

    RtlInitAnsiString(target, QEMU_G2H(c->source));

#if GUEST_BIT != HOST_BIT
    STRING_h2g(QEMU_G2H(c->target), target);
#endif
}

#endif

struct qemu_RtlInitAnsiStringEx
{
    struct qemu_syscall super;
    uint64_t target;
    uint64_t source;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlInitAnsiStringEx(PANSI_STRING target, PCSZ source)
{
    struct qemu_RtlInitAnsiStringEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITANSISTRINGEX);
    call.target = (ULONG_PTR)target;
    call.source = (ULONG_PTR)source;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlInitAnsiStringEx(struct qemu_syscall *call)
{
    struct qemu_RtlInitAnsiStringEx *c = (struct qemu_RtlInitAnsiStringEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlInitAnsiStringEx(QEMU_G2H(c->target), QEMU_G2H(c->source));
}

#endif

struct qemu_RtlInitString
{
    struct qemu_syscall super;
    uint64_t target;
    uint64_t source;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlInitString(PSTRING target, PCSZ source)
{
    struct qemu_RtlInitString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITSTRING);
    call.target = (ULONG_PTR)target;
    call.source = (ULONG_PTR)source;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlInitString(struct qemu_syscall *call)
{
    struct qemu_RtlInitString *c = (struct qemu_RtlInitString *)call;
    WINE_FIXME("Unverified!\n");
    RtlInitString(QEMU_G2H(c->target), QEMU_G2H(c->source));
}

#endif

struct qemu_RtlFreeAnsiString
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlFreeAnsiString(PSTRING str)
{
    struct qemu_RtlFreeAnsiString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFREEANSISTRING);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlFreeAnsiString(struct qemu_syscall *call)
{
    struct qemu_RtlFreeAnsiString *c = (struct qemu_RtlFreeAnsiString *)call;
    WINE_FIXME("Unverified!\n");
    RtlFreeAnsiString(QEMU_G2H(c->str));
}

#endif

struct qemu_RtlFreeOemString
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlFreeOemString(PSTRING str)
{
    struct qemu_RtlFreeOemString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFREEOEMSTRING);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlFreeOemString(struct qemu_syscall *call)
{
    struct qemu_RtlFreeOemString *c = (struct qemu_RtlFreeOemString *)call;
    WINE_FIXME("Unverified!\n");
    RtlFreeOemString(QEMU_G2H(c->str));
}

#endif

struct qemu_RtlCopyString
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlCopyString(STRING *dst, const STRING *src)
{
    struct qemu_RtlCopyString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOPYSTRING);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlCopyString(struct qemu_syscall *call)
{
    struct qemu_RtlCopyString *c = (struct qemu_RtlCopyString *)call;
    WINE_FIXME("Unverified!\n");
    RtlCopyString(QEMU_G2H(c->dst), QEMU_G2H(c->src));
}

#endif

struct qemu_RtlInitUnicodeString
{
    struct qemu_syscall super;
    uint64_t target;
    uint64_t source;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlInitUnicodeString(PUNICODE_STRING target, PCWSTR source)
{
    struct qemu_RtlInitUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITUNICODESTRING);
    call.target = (ULONG_PTR)target;
    call.source = (ULONG_PTR)source;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlInitUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlInitUnicodeString *c = (struct qemu_RtlInitUnicodeString *)call;
    UNICODE_STRING stack, *target = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    target = QEMU_G2H(c->target);
#endif

    RtlInitUnicodeString(target, QEMU_G2H(c->source));

#if GUEST_BIT != HOST_BIT
    UNICODE_STRING_h2g(QEMU_G2H(c->target), target);
#endif
}

#endif

struct qemu_RtlInitUnicodeStringEx
{
    struct qemu_syscall super;
    uint64_t target;
    uint64_t source;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlInitUnicodeStringEx(PUNICODE_STRING target, PCWSTR source)
{
    struct qemu_RtlInitUnicodeStringEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITUNICODESTRINGEX);
    call.target = (ULONG_PTR)target;
    call.source = (ULONG_PTR)source;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlInitUnicodeStringEx(struct qemu_syscall *call)
{
    struct qemu_RtlInitUnicodeStringEx *c = (struct qemu_RtlInitUnicodeStringEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlInitUnicodeStringEx(QEMU_G2H(c->target), QEMU_G2H(c->source));
}

#endif

struct qemu_RtlCreateUnicodeString
{
    struct qemu_syscall super;
    uint64_t target;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlCreateUnicodeString(PUNICODE_STRING target, LPCWSTR src)
{
    struct qemu_RtlCreateUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATEUNICODESTRING);
    call.target = (ULONG_PTR)target;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlCreateUnicodeString *c = (struct qemu_RtlCreateUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCreateUnicodeString(QEMU_G2H(c->target), QEMU_G2H(c->src));
}

#endif

struct qemu_RtlCreateUnicodeStringFromAsciiz
{
    struct qemu_syscall super;
    uint64_t target;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlCreateUnicodeStringFromAsciiz(PUNICODE_STRING target, LPCSTR src)
{
    struct qemu_RtlCreateUnicodeStringFromAsciiz call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCREATEUNICODESTRINGFROMASCIIZ);
    call.target = (ULONG_PTR)target;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCreateUnicodeStringFromAsciiz(struct qemu_syscall *call)
{
    struct qemu_RtlCreateUnicodeStringFromAsciiz *c = (struct qemu_RtlCreateUnicodeStringFromAsciiz *)call;
    UNICODE_STRING stack, *target = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    target = QEMU_G2H(c->target);
#else
    if (!QEMU_G2H(c->target))
        target = NULL;
#endif

    c->super.iret = RtlCreateUnicodeStringFromAsciiz(target, QEMU_G2H(c->src));

#if GUEST_BIT != HOST_BIT
    if (QEMU_G2H(c->target))
        UNICODE_STRING_h2g(QEMU_G2H(c->target), target);
#endif
}

#endif

struct qemu_RtlFreeUnicodeString
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlFreeUnicodeString(PUNICODE_STRING str)
{
    struct qemu_RtlFreeUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFREEUNICODESTRING);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlFreeUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlFreeUnicodeString *c = (struct qemu_RtlFreeUnicodeString *)call;
    UNICODE_STRING stack, *str = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    str = QEMU_G2H(c->str);
#else
    UNICODE_STRING_g2h(str, QEMU_G2H(c->str));
#endif

    RtlFreeUnicodeString(str);
}

#endif

struct qemu_RtlCopyUnicodeString
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlCopyUnicodeString(UNICODE_STRING *dst, const UNICODE_STRING *src)
{
    struct qemu_RtlCopyUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOPYUNICODESTRING);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlCopyUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlCopyUnicodeString *c = (struct qemu_RtlCopyUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    RtlCopyUnicodeString(QEMU_G2H(c->dst), QEMU_G2H(c->src));
}

#endif

struct qemu_RtlDuplicateUnicodeString
{
    struct qemu_syscall super;
    uint64_t add_nul;
    uint64_t source;
    uint64_t destination;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDuplicateUnicodeString(int add_nul, const UNICODE_STRING *source, UNICODE_STRING *destination)
{
    struct qemu_RtlDuplicateUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDUPLICATEUNICODESTRING);
    call.add_nul = (ULONG_PTR)add_nul;
    call.source = (ULONG_PTR)source;
    call.destination = (ULONG_PTR)destination;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDuplicateUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlDuplicateUnicodeString *c = (struct qemu_RtlDuplicateUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDuplicateUnicodeString(c->add_nul, QEMU_G2H(c->source), QEMU_G2H(c->destination));
}

#endif

struct qemu_RtlEraseUnicodeString
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlEraseUnicodeString(UNICODE_STRING *str)
{
    struct qemu_RtlEraseUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLERASEUNICODESTRING);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlEraseUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlEraseUnicodeString *c = (struct qemu_RtlEraseUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    RtlEraseUnicodeString(QEMU_G2H(c->str));
}

#endif

struct qemu_RtlCompareString
{
    struct qemu_syscall super;
    uint64_t s1;
    uint64_t s2;
    uint64_t CaseInsensitive;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI RtlCompareString(const STRING *s1, const STRING *s2, BOOLEAN CaseInsensitive)
{
    struct qemu_RtlCompareString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOMPARESTRING);
    call.s1 = (ULONG_PTR)s1;
    call.s2 = (ULONG_PTR)s2;
    call.CaseInsensitive = (ULONG_PTR)CaseInsensitive;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCompareString(struct qemu_syscall *call)
{
    struct qemu_RtlCompareString *c = (struct qemu_RtlCompareString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCompareString(QEMU_G2H(c->s1), QEMU_G2H(c->s2), c->CaseInsensitive);
}

#endif

struct qemu_RtlCompareUnicodeStrings
{
    struct qemu_syscall super;
    uint64_t s1;
    uint64_t len1;
    uint64_t s2;
    uint64_t len2;
    uint64_t case_insensitive;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI RtlCompareUnicodeStrings(const WCHAR *s1, SIZE_T len1, const WCHAR *s2, SIZE_T len2, BOOLEAN case_insensitive)
{
    struct qemu_RtlCompareUnicodeStrings call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOMPAREUNICODESTRINGS);
    call.s1 = (ULONG_PTR)s1;
    call.len1 = (ULONG_PTR)len1;
    call.s2 = (ULONG_PTR)s2;
    call.len2 = (ULONG_PTR)len2;
    call.case_insensitive = (ULONG_PTR)case_insensitive;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCompareUnicodeStrings(struct qemu_syscall *call)
{
    struct qemu_RtlCompareUnicodeStrings *c = (struct qemu_RtlCompareUnicodeStrings *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCompareUnicodeStrings(QEMU_G2H(c->s1), c->len1, QEMU_G2H(c->s2), c->len2, c->case_insensitive);
}

#endif

struct qemu_RtlCompareUnicodeString
{
    struct qemu_syscall super;
    uint64_t s1;
    uint64_t s2;
    uint64_t CaseInsensitive;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI RtlCompareUnicodeString(const UNICODE_STRING *s1, const UNICODE_STRING *s2, BOOLEAN CaseInsensitive)
{
    struct qemu_RtlCompareUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCOMPAREUNICODESTRING);
    call.s1 = (ULONG_PTR)s1;
    call.s2 = (ULONG_PTR)s2;
    call.CaseInsensitive = (ULONG_PTR)CaseInsensitive;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCompareUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlCompareUnicodeString *c = (struct qemu_RtlCompareUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCompareUnicodeString(QEMU_G2H(c->s1), QEMU_G2H(c->s2), c->CaseInsensitive);
}

#endif

struct qemu_RtlEqualString
{
    struct qemu_syscall super;
    uint64_t s1;
    uint64_t s2;
    uint64_t CaseInsensitive;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlEqualString(const STRING *s1, const STRING *s2, BOOLEAN CaseInsensitive)
{
    struct qemu_RtlEqualString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLEQUALSTRING);
    call.s1 = (ULONG_PTR)s1;
    call.s2 = (ULONG_PTR)s2;
    call.CaseInsensitive = (ULONG_PTR)CaseInsensitive;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlEqualString(struct qemu_syscall *call)
{
    struct qemu_RtlEqualString *c = (struct qemu_RtlEqualString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlEqualString(QEMU_G2H(c->s1), QEMU_G2H(c->s2), c->CaseInsensitive);
}

#endif

struct qemu_RtlEqualUnicodeString
{
    struct qemu_syscall super;
    uint64_t s1;
    uint64_t s2;
    uint64_t CaseInsensitive;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlEqualUnicodeString(const UNICODE_STRING *s1, const UNICODE_STRING *s2, BOOLEAN CaseInsensitive)
{
    struct qemu_RtlEqualUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLEQUALUNICODESTRING);
    call.s1 = (ULONG_PTR)s1;
    call.s2 = (ULONG_PTR)s2;
    call.CaseInsensitive = (ULONG_PTR)CaseInsensitive;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlEqualUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlEqualUnicodeString *c = (struct qemu_RtlEqualUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlEqualUnicodeString(QEMU_G2H(c->s1), QEMU_G2H(c->s2), c->CaseInsensitive);
}

#endif

struct qemu_RtlPrefixString
{
    struct qemu_syscall super;
    uint64_t s1;
    uint64_t s2;
    uint64_t ignore_case;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlPrefixString(const STRING *s1, const STRING *s2, BOOLEAN ignore_case)
{
    struct qemu_RtlPrefixString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLPREFIXSTRING);
    call.s1 = (ULONG_PTR)s1;
    call.s2 = (ULONG_PTR)s2;
    call.ignore_case = (ULONG_PTR)ignore_case;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlPrefixString(struct qemu_syscall *call)
{
    struct qemu_RtlPrefixString *c = (struct qemu_RtlPrefixString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlPrefixString(QEMU_G2H(c->s1), QEMU_G2H(c->s2), c->ignore_case);
}

#endif

struct qemu_RtlPrefixUnicodeString
{
    struct qemu_syscall super;
    uint64_t s1;
    uint64_t s2;
    uint64_t ignore_case;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlPrefixUnicodeString(const UNICODE_STRING *s1, const UNICODE_STRING *s2, BOOLEAN ignore_case)
{
    struct qemu_RtlPrefixUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLPREFIXUNICODESTRING);
    call.s1 = (ULONG_PTR)s1;
    call.s2 = (ULONG_PTR)s2;
    call.ignore_case = (ULONG_PTR)ignore_case;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlPrefixUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlPrefixUnicodeString *c = (struct qemu_RtlPrefixUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlPrefixUnicodeString(QEMU_G2H(c->s1), QEMU_G2H(c->s2), c->ignore_case);
}

#endif

struct qemu_RtlEqualComputerName
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t right;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlEqualComputerName(const UNICODE_STRING *left, const UNICODE_STRING *right)
{
    struct qemu_RtlEqualComputerName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLEQUALCOMPUTERNAME);
    call.left = (ULONG_PTR)left;
    call.right = (ULONG_PTR)right;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlEqualComputerName(struct qemu_syscall *call)
{
    struct qemu_RtlEqualComputerName *c = (struct qemu_RtlEqualComputerName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlEqualComputerName(QEMU_G2H(c->left), QEMU_G2H(c->right));
}

#endif

struct qemu_RtlEqualDomainName
{
    struct qemu_syscall super;
    uint64_t left;
    uint64_t right;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlEqualDomainName(const UNICODE_STRING *left, const UNICODE_STRING *right)
{
    struct qemu_RtlEqualDomainName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLEQUALDOMAINNAME);
    call.left = (ULONG_PTR)left;
    call.right = (ULONG_PTR)right;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlEqualDomainName(struct qemu_syscall *call)
{
    struct qemu_RtlEqualDomainName *c = (struct qemu_RtlEqualDomainName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlEqualDomainName(QEMU_G2H(c->left), QEMU_G2H(c->right));
}

#endif

struct qemu_RtlAnsiCharToUnicodeChar
{
    struct qemu_syscall super;
    uint64_t ansi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR WINAPI RtlAnsiCharToUnicodeChar(LPSTR *ansi)
{
    struct qemu_RtlAnsiCharToUnicodeChar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLANSICHARTOUNICODECHAR);
    call.ansi = (ULONG_PTR)ansi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAnsiCharToUnicodeChar(struct qemu_syscall *call)
{
    struct qemu_RtlAnsiCharToUnicodeChar *c = (struct qemu_RtlAnsiCharToUnicodeChar *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAnsiCharToUnicodeChar(QEMU_G2H(c->ansi));
}

#endif

struct qemu_RtlAnsiStringToUnicodeString
{
    struct qemu_syscall super;
    uint64_t uni;
    uint64_t ansi;
    uint64_t doalloc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlAnsiStringToUnicodeString(UNICODE_STRING *uni, PCANSI_STRING ansi, BOOLEAN doalloc)
{
    struct qemu_RtlAnsiStringToUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLANSISTRINGTOUNICODESTRING);
    call.uni = (ULONG_PTR)uni;
    call.ansi = (ULONG_PTR)ansi;
    call.doalloc = doalloc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAnsiStringToUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlAnsiStringToUnicodeString *c = (struct qemu_RtlAnsiStringToUnicodeString *)call;
    UNICODE_STRING stack, *uni = &stack;
    ANSI_STRING ansi_stack, *ansi = &ansi_stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    uni = QEMU_G2H(c->uni);
    ansi = QEMU_G2H(c->ansi);
#else
    UNICODE_STRING_g2h(uni, QEMU_G2H(c->uni));
    STRING_g2h(ansi, QEMU_G2H(c->ansi));
#endif

    c->super.iret = RtlAnsiStringToUnicodeString(uni, ansi, c->doalloc);

#if GUEST_BIT != HOST_BIT
    UNICODE_STRING_h2g(QEMU_G2H(c->uni), uni);
#endif
}

#endif

struct qemu_RtlOemStringToUnicodeString
{
    struct qemu_syscall super;
    uint64_t uni;
    uint64_t oem;
    uint64_t doalloc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlOemStringToUnicodeString(UNICODE_STRING *uni, const STRING *oem, BOOLEAN doalloc)
{
    struct qemu_RtlOemStringToUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLOEMSTRINGTOUNICODESTRING);
    call.uni = (ULONG_PTR)uni;
    call.oem = (ULONG_PTR)oem;
    call.doalloc = (ULONG_PTR)doalloc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlOemStringToUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlOemStringToUnicodeString *c = (struct qemu_RtlOemStringToUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlOemStringToUnicodeString(QEMU_G2H(c->uni), QEMU_G2H(c->oem), c->doalloc);
}

#endif

struct qemu_RtlUnicodeStringToAnsiString
{
    struct qemu_syscall super;
    uint64_t ansi;
    uint64_t uni;
    uint64_t doalloc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUnicodeStringToAnsiString(STRING *ansi, const UNICODE_STRING *uni, BOOLEAN doalloc)
{
    struct qemu_RtlUnicodeStringToAnsiString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNICODESTRINGTOANSISTRING);
    call.ansi = (ULONG_PTR)ansi;
    call.uni = (ULONG_PTR)uni;
    call.doalloc = (ULONG_PTR)doalloc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUnicodeStringToAnsiString(struct qemu_syscall *call)
{
    struct qemu_RtlUnicodeStringToAnsiString *c = (struct qemu_RtlUnicodeStringToAnsiString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUnicodeStringToAnsiString(QEMU_G2H(c->ansi), QEMU_G2H(c->uni), c->doalloc);
}

#endif

struct qemu_RtlUnicodeStringToOemString
{
    struct qemu_syscall super;
    uint64_t oem;
    uint64_t uni;
    uint64_t doalloc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUnicodeStringToOemString(STRING *oem, const UNICODE_STRING *uni, BOOLEAN doalloc)
{
    struct qemu_RtlUnicodeStringToOemString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNICODESTRINGTOOEMSTRING);
    call.oem = (ULONG_PTR)oem;
    call.uni = (ULONG_PTR)uni;
    call.doalloc = (ULONG_PTR)doalloc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUnicodeStringToOemString(struct qemu_syscall *call)
{
    struct qemu_RtlUnicodeStringToOemString *c = (struct qemu_RtlUnicodeStringToOemString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUnicodeStringToOemString(QEMU_G2H(c->oem), QEMU_G2H(c->uni), c->doalloc);
}

#endif

struct qemu_RtlMultiByteToUnicodeN
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t reslen;
    uint64_t src;
    uint64_t srclen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlMultiByteToUnicodeN(LPWSTR dst, DWORD dstlen, LPDWORD reslen, LPCSTR src, DWORD srclen)
{
    struct qemu_RtlMultiByteToUnicodeN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLMULTIBYTETOUNICODEN);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = (ULONG_PTR)dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = (ULONG_PTR)srclen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlMultiByteToUnicodeN(struct qemu_syscall *call)
{
    struct qemu_RtlMultiByteToUnicodeN *c = (struct qemu_RtlMultiByteToUnicodeN *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlMultiByteToUnicodeN(QEMU_G2H(c->dst), c->dstlen, QEMU_G2H(c->reslen), QEMU_G2H(c->src), c->srclen);
}

#endif

struct qemu_RtlOemToUnicodeN
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t reslen;
    uint64_t src;
    uint64_t srclen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlOemToUnicodeN(LPWSTR dst, DWORD dstlen, LPDWORD reslen, LPCSTR src, DWORD srclen)
{
    struct qemu_RtlOemToUnicodeN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLOEMTOUNICODEN);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = (ULONG_PTR)dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = (ULONG_PTR)srclen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlOemToUnicodeN(struct qemu_syscall *call)
{
    struct qemu_RtlOemToUnicodeN *c = (struct qemu_RtlOemToUnicodeN *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlOemToUnicodeN(QEMU_G2H(c->dst), c->dstlen, QEMU_G2H(c->reslen), QEMU_G2H(c->src), c->srclen);
}

#endif

struct qemu_RtlUnicodeToMultiByteN
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t reslen;
    uint64_t src;
    uint64_t srclen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUnicodeToMultiByteN(LPSTR dst, DWORD dstlen, LPDWORD reslen, LPCWSTR src, DWORD srclen)
{
    struct qemu_RtlUnicodeToMultiByteN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNICODETOMULTIBYTEN);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = (ULONG_PTR)dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = (ULONG_PTR)srclen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUnicodeToMultiByteN(struct qemu_syscall *call)
{
    struct qemu_RtlUnicodeToMultiByteN *c = (struct qemu_RtlUnicodeToMultiByteN *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUnicodeToMultiByteN(QEMU_G2H(c->dst), c->dstlen, QEMU_G2H(c->reslen), QEMU_G2H(c->src), c->srclen);
}

#endif

struct qemu_RtlUnicodeToOemN
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t reslen;
    uint64_t src;
    uint64_t srclen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUnicodeToOemN(LPSTR dst, DWORD dstlen, LPDWORD reslen, LPCWSTR src, DWORD srclen)
{
    struct qemu_RtlUnicodeToOemN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNICODETOOEMN);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = (ULONG_PTR)dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = (ULONG_PTR)srclen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUnicodeToOemN(struct qemu_syscall *call)
{
    struct qemu_RtlUnicodeToOemN *c = (struct qemu_RtlUnicodeToOemN *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUnicodeToOemN(QEMU_G2H(c->dst), c->dstlen, QEMU_G2H(c->reslen), QEMU_G2H(c->src), c->srclen);
}

#endif

struct qemu_RtlUpperChar
{
    struct qemu_syscall super;
    uint64_t ch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI CHAR WINAPI RtlUpperChar(CHAR ch)
{
    struct qemu_RtlUpperChar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPPERCHAR);
    call.ch = (ULONG_PTR)ch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUpperChar(struct qemu_syscall *call)
{
    struct qemu_RtlUpperChar *c = (struct qemu_RtlUpperChar *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUpperChar(c->ch);
}

#endif

struct qemu_RtlUpperString
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlUpperString(STRING *dst, const STRING *src)
{
    struct qemu_RtlUpperString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPPERSTRING);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlUpperString(struct qemu_syscall *call)
{
    struct qemu_RtlUpperString *c = (struct qemu_RtlUpperString *)call;
    WINE_FIXME("Unverified!\n");
    RtlUpperString(QEMU_G2H(c->dst), QEMU_G2H(c->src));
}

#endif

struct qemu_RtlUpcaseUnicodeChar
{
    struct qemu_syscall super;
    uint64_t wch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR WINAPI RtlUpcaseUnicodeChar(WCHAR wch)
{
    struct qemu_RtlUpcaseUnicodeChar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPCASEUNICODECHAR);
    call.wch = wch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUpcaseUnicodeChar(struct qemu_syscall *call)
{
    struct qemu_RtlUpcaseUnicodeChar *c = (struct qemu_RtlUpcaseUnicodeChar *)call;
    WINE_TRACE("\n");
    c->super.iret = RtlUpcaseUnicodeChar(c->wch);
}

#endif

struct qemu_RtlDowncaseUnicodeChar
{
    struct qemu_syscall super;
    uint64_t wch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR WINAPI RtlDowncaseUnicodeChar(WCHAR wch)
{
    struct qemu_RtlDowncaseUnicodeChar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDOWNCASEUNICODECHAR);
    call.wch = (ULONG_PTR)wch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDowncaseUnicodeChar(struct qemu_syscall *call)
{
    struct qemu_RtlDowncaseUnicodeChar *c = (struct qemu_RtlDowncaseUnicodeChar *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDowncaseUnicodeChar(c->wch);
}

#endif

struct qemu_RtlUpcaseUnicodeString
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
    uint64_t doalloc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUpcaseUnicodeString(UNICODE_STRING *dest, const UNICODE_STRING *src, BOOLEAN doalloc)
{
    struct qemu_RtlUpcaseUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPCASEUNICODESTRING);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;
    call.doalloc = (ULONG_PTR)doalloc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUpcaseUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlUpcaseUnicodeString *c = (struct qemu_RtlUpcaseUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUpcaseUnicodeString(QEMU_G2H(c->dest), QEMU_G2H(c->src), c->doalloc);
}

#endif

struct qemu_RtlDowncaseUnicodeString
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
    uint64_t doalloc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDowncaseUnicodeString(UNICODE_STRING *dest, const UNICODE_STRING *src, BOOLEAN doalloc)
{
    struct qemu_RtlDowncaseUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDOWNCASEUNICODESTRING);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;
    call.doalloc = (ULONG_PTR)doalloc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDowncaseUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlDowncaseUnicodeString *c = (struct qemu_RtlDowncaseUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDowncaseUnicodeString(QEMU_G2H(c->dest), QEMU_G2H(c->src), c->doalloc);
}

#endif

struct qemu_RtlUpcaseUnicodeStringToAnsiString
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t doalloc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUpcaseUnicodeStringToAnsiString(STRING *dst, const UNICODE_STRING *src, BOOLEAN doalloc)
{
    struct qemu_RtlUpcaseUnicodeStringToAnsiString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPCASEUNICODESTRINGTOANSISTRING);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.doalloc = (ULONG_PTR)doalloc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUpcaseUnicodeStringToAnsiString(struct qemu_syscall *call)
{
    struct qemu_RtlUpcaseUnicodeStringToAnsiString *c = (struct qemu_RtlUpcaseUnicodeStringToAnsiString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUpcaseUnicodeStringToAnsiString(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->doalloc);
}

#endif

struct qemu_RtlUpcaseUnicodeStringToOemString
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t src;
    uint64_t doalloc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUpcaseUnicodeStringToOemString(STRING *dst, const UNICODE_STRING *src, BOOLEAN doalloc)
{
    struct qemu_RtlUpcaseUnicodeStringToOemString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPCASEUNICODESTRINGTOOEMSTRING);
    call.dst = (ULONG_PTR)dst;
    call.src = (ULONG_PTR)src;
    call.doalloc = (ULONG_PTR)doalloc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUpcaseUnicodeStringToOemString(struct qemu_syscall *call)
{
    struct qemu_RtlUpcaseUnicodeStringToOemString *c = (struct qemu_RtlUpcaseUnicodeStringToOemString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUpcaseUnicodeStringToOemString(QEMU_G2H(c->dst), QEMU_G2H(c->src), c->doalloc);
}

#endif

struct qemu_RtlUpcaseUnicodeStringToCountedOemString
{
    struct qemu_syscall super;
    uint64_t oem;
    uint64_t uni;
    uint64_t doalloc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUpcaseUnicodeStringToCountedOemString(STRING *oem, const UNICODE_STRING *uni, BOOLEAN doalloc)
{
    struct qemu_RtlUpcaseUnicodeStringToCountedOemString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPCASEUNICODESTRINGTOCOUNTEDOEMSTRING);
    call.oem = (ULONG_PTR)oem;
    call.uni = (ULONG_PTR)uni;
    call.doalloc = (ULONG_PTR)doalloc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUpcaseUnicodeStringToCountedOemString(struct qemu_syscall *call)
{
    struct qemu_RtlUpcaseUnicodeStringToCountedOemString *c = (struct qemu_RtlUpcaseUnicodeStringToCountedOemString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUpcaseUnicodeStringToCountedOemString(QEMU_G2H(c->oem), QEMU_G2H(c->uni), c->doalloc);
}

#endif

struct qemu_RtlUpcaseUnicodeToMultiByteN
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t reslen;
    uint64_t src;
    uint64_t srclen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUpcaseUnicodeToMultiByteN(LPSTR dst, DWORD dstlen, LPDWORD reslen, LPCWSTR src, DWORD srclen)
{
    struct qemu_RtlUpcaseUnicodeToMultiByteN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPCASEUNICODETOMULTIBYTEN);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = (ULONG_PTR)dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = (ULONG_PTR)srclen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUpcaseUnicodeToMultiByteN(struct qemu_syscall *call)
{
    struct qemu_RtlUpcaseUnicodeToMultiByteN *c = (struct qemu_RtlUpcaseUnicodeToMultiByteN *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUpcaseUnicodeToMultiByteN(QEMU_G2H(c->dst), c->dstlen, QEMU_G2H(c->reslen), QEMU_G2H(c->src), c->srclen);
}

#endif

struct qemu_RtlUpcaseUnicodeToOemN
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t reslen;
    uint64_t src;
    uint64_t srclen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUpcaseUnicodeToOemN(LPSTR dst, DWORD dstlen, LPDWORD reslen, LPCWSTR src, DWORD srclen)
{
    struct qemu_RtlUpcaseUnicodeToOemN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPCASEUNICODETOOEMN);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = (ULONG_PTR)dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = (ULONG_PTR)srclen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUpcaseUnicodeToOemN(struct qemu_syscall *call)
{
    struct qemu_RtlUpcaseUnicodeToOemN *c = (struct qemu_RtlUpcaseUnicodeToOemN *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUpcaseUnicodeToOemN(QEMU_G2H(c->dst), c->dstlen, QEMU_G2H(c->reslen), QEMU_G2H(c->src), c->srclen);
}

#endif

struct qemu_RtlOemStringToUnicodeSize
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI RtlOemStringToUnicodeSize(const STRING *str)
{
    struct qemu_RtlOemStringToUnicodeSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLOEMSTRINGTOUNICODESIZE);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlOemStringToUnicodeSize(struct qemu_syscall *call)
{
    struct qemu_RtlOemStringToUnicodeSize *c = (struct qemu_RtlOemStringToUnicodeSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlOemStringToUnicodeSize(QEMU_G2H(c->str));
}

#endif

struct qemu_RtlAnsiStringToUnicodeSize
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlAnsiStringToUnicodeSize(const STRING *str)
{
    struct qemu_RtlAnsiStringToUnicodeSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLANSISTRINGTOUNICODESIZE);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAnsiStringToUnicodeSize(struct qemu_syscall *call)
{
    struct qemu_RtlAnsiStringToUnicodeSize *c = (struct qemu_RtlAnsiStringToUnicodeSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAnsiStringToUnicodeSize(QEMU_G2H(c->str));
}

#endif

struct qemu_RtlMultiByteToUnicodeSize
{
    struct qemu_syscall super;
    uint64_t size;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlMultiByteToUnicodeSize(DWORD *size, LPCSTR str, UINT len)
{
    struct qemu_RtlMultiByteToUnicodeSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLMULTIBYTETOUNICODESIZE);
    call.size = (ULONG_PTR)size;
    call.str = (ULONG_PTR)str;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlMultiByteToUnicodeSize(struct qemu_syscall *call)
{
    struct qemu_RtlMultiByteToUnicodeSize *c = (struct qemu_RtlMultiByteToUnicodeSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlMultiByteToUnicodeSize(QEMU_G2H(c->size), QEMU_G2H(c->str), c->len);
}

#endif

struct qemu_RtlUnicodeToMultiByteSize
{
    struct qemu_syscall super;
    uint64_t size;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUnicodeToMultiByteSize(PULONG size, PWCH str, ULONG len)
{
    struct qemu_RtlUnicodeToMultiByteSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNICODETOMULTIBYTESIZE);
    call.size = (ULONG_PTR)size;
    call.str = (ULONG_PTR)str;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUnicodeToMultiByteSize(struct qemu_syscall *call)
{
    struct qemu_RtlUnicodeToMultiByteSize *c = (struct qemu_RtlUnicodeToMultiByteSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUnicodeToMultiByteSize(QEMU_G2H(c->size), QEMU_G2H(c->str), c->len);
}

#endif

struct qemu_RtlUnicodeStringToAnsiSize
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlUnicodeStringToAnsiSize(const UNICODE_STRING *str)
{
    struct qemu_RtlUnicodeStringToAnsiSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNICODESTRINGTOANSISIZE);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUnicodeStringToAnsiSize(struct qemu_syscall *call)
{
    struct qemu_RtlUnicodeStringToAnsiSize *c = (struct qemu_RtlUnicodeStringToAnsiSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUnicodeStringToAnsiSize(QEMU_G2H(c->str));
}

#endif

struct qemu_RtlUnicodeStringToOemSize
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlUnicodeStringToOemSize(const UNICODE_STRING *str)
{
    struct qemu_RtlUnicodeStringToOemSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNICODESTRINGTOOEMSIZE);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUnicodeStringToOemSize(struct qemu_syscall *call)
{
    struct qemu_RtlUnicodeStringToOemSize *c = (struct qemu_RtlUnicodeStringToOemSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUnicodeStringToOemSize(QEMU_G2H(c->str));
}

#endif

struct qemu_RtlAppendAsciizToString
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlAppendAsciizToString(STRING *dest, LPCSTR src)
{
    struct qemu_RtlAppendAsciizToString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLAPPENDASCIIZTOSTRING);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAppendAsciizToString(struct qemu_syscall *call)
{
    struct qemu_RtlAppendAsciizToString *c = (struct qemu_RtlAppendAsciizToString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAppendAsciizToString(QEMU_G2H(c->dest), QEMU_G2H(c->src));
}

#endif

struct qemu_RtlAppendStringToString
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlAppendStringToString(STRING *dest, const STRING *src)
{
    struct qemu_RtlAppendStringToString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLAPPENDSTRINGTOSTRING);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAppendStringToString(struct qemu_syscall *call)
{
    struct qemu_RtlAppendStringToString *c = (struct qemu_RtlAppendStringToString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAppendStringToString(QEMU_G2H(c->dest), QEMU_G2H(c->src));
}

#endif

struct qemu_RtlAppendUnicodeToString
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlAppendUnicodeToString(UNICODE_STRING *dest, LPCWSTR src)
{
    struct qemu_RtlAppendUnicodeToString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLAPPENDUNICODETOSTRING);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAppendUnicodeToString(struct qemu_syscall *call)
{
    struct qemu_RtlAppendUnicodeToString *c = (struct qemu_RtlAppendUnicodeToString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAppendUnicodeToString(QEMU_G2H(c->dest), QEMU_G2H(c->src));
}

#endif

struct qemu_RtlAppendUnicodeStringToString
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlAppendUnicodeStringToString(UNICODE_STRING *dest, const UNICODE_STRING *src)
{
    struct qemu_RtlAppendUnicodeStringToString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLAPPENDUNICODESTRINGTOSTRING);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlAppendUnicodeStringToString(struct qemu_syscall *call)
{
    struct qemu_RtlAppendUnicodeStringToString *c = (struct qemu_RtlAppendUnicodeStringToString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlAppendUnicodeStringToString(QEMU_G2H(c->dest), QEMU_G2H(c->src));
}

#endif

struct qemu_RtlFindCharInUnicodeString
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t main_str;
    uint64_t search_chars;
    uint64_t pos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlFindCharInUnicodeString(int flags, const UNICODE_STRING *main_str, const UNICODE_STRING *search_chars, USHORT *pos)
{
    struct qemu_RtlFindCharInUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLFINDCHARINUNICODESTRING);
    call.flags = (ULONG_PTR)flags;
    call.main_str = (ULONG_PTR)main_str;
    call.search_chars = (ULONG_PTR)search_chars;
    call.pos = (ULONG_PTR)pos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlFindCharInUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlFindCharInUnicodeString *c = (struct qemu_RtlFindCharInUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlFindCharInUnicodeString(c->flags, QEMU_G2H(c->main_str), QEMU_G2H(c->search_chars), QEMU_G2H(c->pos));
}

#endif

struct qemu_RtlIsTextUnicode
{
    struct qemu_syscall super;
    uint64_t buf;
    uint64_t len;
    uint64_t pf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlIsTextUnicode(LPCVOID buf, INT len, INT *pf)
{
    struct qemu_RtlIsTextUnicode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLISTEXTUNICODE);
    call.buf = (ULONG_PTR)buf;
    call.len = (ULONG_PTR)len;
    call.pf = (ULONG_PTR)pf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlIsTextUnicode(struct qemu_syscall *call)
{
    struct qemu_RtlIsTextUnicode *c = (struct qemu_RtlIsTextUnicode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIsTextUnicode(QEMU_G2H(c->buf), c->len, QEMU_G2H(c->pf));
}

#endif

struct qemu_RtlCharToInteger
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t base;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCharToInteger(PCSZ str, ULONG base, ULONG *value)
{
    struct qemu_RtlCharToInteger call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCHARTOINTEGER);
    call.str = (ULONG_PTR)str;
    call.base = (ULONG_PTR)base;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCharToInteger(struct qemu_syscall *call)
{
    struct qemu_RtlCharToInteger *c = (struct qemu_RtlCharToInteger *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCharToInteger(QEMU_G2H(c->str), c->base, QEMU_G2H(c->value));
}

#endif

struct qemu_RtlIntegerToChar
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t base;
    uint64_t length;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlIntegerToChar(ULONG value, ULONG base, ULONG length, PCHAR str)
{
    struct qemu_RtlIntegerToChar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINTEGERTOCHAR);
    call.value = (ULONG_PTR)value;
    call.base = (ULONG_PTR)base;
    call.length = (ULONG_PTR)length;
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlIntegerToChar(struct qemu_syscall *call)
{
    struct qemu_RtlIntegerToChar *c = (struct qemu_RtlIntegerToChar *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIntegerToChar(c->value, c->base, c->length, QEMU_G2H(c->str));
}

#endif

struct qemu_RtlUnicodeStringToInteger
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t base;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUnicodeStringToInteger(const UNICODE_STRING *str, ULONG base, ULONG *value)
{
    struct qemu_RtlUnicodeStringToInteger call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNICODESTRINGTOINTEGER);
    call.str = (ULONG_PTR)str;
    call.base = (ULONG_PTR)base;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUnicodeStringToInteger(struct qemu_syscall *call)
{
    struct qemu_RtlUnicodeStringToInteger *c = (struct qemu_RtlUnicodeStringToInteger *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUnicodeStringToInteger(QEMU_G2H(c->str), c->base, QEMU_G2H(c->value));
}

#endif

struct qemu_RtlIntegerToUnicodeString
{
    struct qemu_syscall super;
    uint64_t value;
    uint64_t base;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlIntegerToUnicodeString(ULONG value, ULONG base, UNICODE_STRING *str)
{
    struct qemu_RtlIntegerToUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINTEGERTOUNICODESTRING);
    call.value = (ULONG_PTR)value;
    call.base = (ULONG_PTR)base;
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlIntegerToUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlIntegerToUnicodeString *c = (struct qemu_RtlIntegerToUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIntegerToUnicodeString(c->value, c->base, QEMU_G2H(c->str));
}

#endif

struct qemu_RtlGUIDFromString
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGUIDFromString(PUNICODE_STRING str, GUID* guid)
{
    struct qemu_RtlGUIDFromString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGUIDFROMSTRING);
    call.str = (ULONG_PTR)str;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGUIDFromString(struct qemu_syscall *call)
{
    struct qemu_RtlGUIDFromString *c = (struct qemu_RtlGUIDFromString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGUIDFromString(QEMU_G2H(c->str), QEMU_G2H(c->guid));
}

#endif

struct qemu_RtlStringFromGUID
{
    struct qemu_syscall super;
    uint64_t guid;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlStringFromGUID(const GUID* guid, UNICODE_STRING *str)
{
    struct qemu_RtlStringFromGUID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSTRINGFROMGUID);
    call.guid = (ULONG_PTR)guid;
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlStringFromGUID(struct qemu_syscall *call)
{
    struct qemu_RtlStringFromGUID *c = (struct qemu_RtlStringFromGUID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlStringFromGUID(QEMU_G2H(c->guid), QEMU_G2H(c->str));
}

#endif

struct qemu_RtlHashUnicodeString
{
    struct qemu_syscall super;
    uint64_t string;
    uint64_t case_insensitive;
    uint64_t alg;
    uint64_t hash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlHashUnicodeString(PCUNICODE_STRING string, BOOLEAN case_insensitive, ULONG alg, ULONG *hash)
{
    struct qemu_RtlHashUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLHASHUNICODESTRING);
    call.string = (ULONG_PTR)string;
    call.case_insensitive = (ULONG_PTR)case_insensitive;
    call.alg = (ULONG_PTR)alg;
    call.hash = (ULONG_PTR)hash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add RtlHashUnicodeString to Wine headers? */
extern NTSTATUS WINAPI RtlHashUnicodeString(PCUNICODE_STRING string, BOOLEAN case_insensitive, ULONG alg, ULONG *hash);
void qemu_RtlHashUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlHashUnicodeString *c = (struct qemu_RtlHashUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlHashUnicodeString(QEMU_G2H(c->string), c->case_insensitive, c->alg, QEMU_G2H(c->hash));
}

#endif

