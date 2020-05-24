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
typedef struct _CPTABLEINFO CPTABLEINFO;
typedef struct _NLSTABLEINFO NLSTABLEINFO;
#else
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif

struct qemu_NtQueryDefaultLocale
{
    struct qemu_syscall super;
    uint64_t user;
    uint64_t lcid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryDefaultLocale(BOOLEAN user, LCID *lcid)
{
    struct qemu_NtQueryDefaultLocale call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYDEFAULTLOCALE);
    call.user = user;
    call.lcid = (ULONG_PTR)lcid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryDefaultLocale(struct qemu_syscall *call)
{
    struct qemu_NtQueryDefaultLocale *c = (struct qemu_NtQueryDefaultLocale *)call;
    
    /* A plain DWORD is hiding behind LCID. */
    WINE_TRACE("\n");
    c->super.iret = NtQueryDefaultLocale(c->user, QEMU_G2H(c->lcid));
}

#endif

struct qemu_NtSetDefaultLocale
{
    struct qemu_syscall super;
    uint64_t user;
    uint64_t lcid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetDefaultLocale(BOOLEAN user, LCID lcid)
{
    struct qemu_NtSetDefaultLocale call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETDEFAULTLOCALE);
    call.user = user;
    call.lcid = lcid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetDefaultLocale(struct qemu_syscall *call)
{
    struct qemu_NtSetDefaultLocale *c = (struct qemu_NtSetDefaultLocale *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetDefaultLocale(c->user, c->lcid);
}

#endif

struct qemu_NtQueryDefaultUILanguage
{
    struct qemu_syscall super;
    uint64_t lang;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryDefaultUILanguage(LANGID *lang)
{
    struct qemu_NtQueryDefaultUILanguage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYDEFAULTUILANGUAGE);
    call.lang = (ULONG_PTR)lang;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryDefaultUILanguage(struct qemu_syscall *call)
{
    struct qemu_NtQueryDefaultUILanguage *c = (struct qemu_NtQueryDefaultUILanguage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryDefaultUILanguage(QEMU_G2H(c->lang));
}

#endif

struct qemu_NtSetDefaultUILanguage
{
    struct qemu_syscall super;
    uint64_t lang;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetDefaultUILanguage(LANGID lang)
{
    struct qemu_NtSetDefaultUILanguage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETDEFAULTUILANGUAGE);
    call.lang = lang;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetDefaultUILanguage(struct qemu_syscall *call)
{
    struct qemu_NtSetDefaultUILanguage *c = (struct qemu_NtSetDefaultUILanguage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetDefaultUILanguage(c->lang);
}

#endif

struct qemu_NtQueryInstallUILanguage
{
    struct qemu_syscall super;
    uint64_t lang;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryInstallUILanguage(LANGID *lang)
{
    struct qemu_NtQueryInstallUILanguage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYINSTALLUILANGUAGE);
    call.lang = (ULONG_PTR)lang;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryInstallUILanguage(struct qemu_syscall *call)
{
    struct qemu_NtQueryInstallUILanguage *c = (struct qemu_NtQueryInstallUILanguage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryInstallUILanguage(QEMU_G2H(c->lang));
}

#endif

struct qemu_NtGetNlsSectionPtr
{
    struct qemu_syscall super;
    uint64_t type;
    uint64_t id;
    uint64_t unknown;
    uint64_t ptr;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtGetNlsSectionPtr(ULONG type, ULONG id, void *unknown, void **ptr, SIZE_T *size)
{
    struct qemu_NtGetNlsSectionPtr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTGETNLSSECTIONPTR);
    call.type = type;
    call.id = id;
    call.unknown = (ULONG_PTR)unknown;

    qemu_syscall(&call.super);
    *ptr = (void *)(ULONG_PTR)call.ptr;
    if (!call.super.iret)
        *size = call.size;

    return call.super.iret;
}

#else

void qemu_NtGetNlsSectionPtr(struct qemu_syscall *call)
{
    struct qemu_NtGetNlsSectionPtr *c = (struct qemu_NtGetNlsSectionPtr *)call;
    void *ptr;
    SIZE_T size;

    WINE_TRACE("\n");
    if (c->unknown)
        WINE_FIXME("Not sure how to handle void *unknown\n");

    c->super.iret = NtGetNlsSectionPtr(c->type, c->id, QEMU_G2H(c->unknown), &ptr, &size);
    c->ptr = QEMU_H2G(ptr);
    c->size = size;
}

#endif

struct qemu_RtlInitCodePageTable
{
    struct qemu_syscall super;
    uint64_t ptr;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlInitCodePageTable(USHORT *ptr, CPTABLEINFO *info)
{
    struct qemu_RtlInitCodePageTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITCODEPAGETABLE);
    call.ptr = (ULONG_PTR)ptr;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlInitCodePageTable(struct qemu_syscall *call)
{
    struct qemu_RtlInitCodePageTable *c = (struct qemu_RtlInitCodePageTable *)call;
    WINE_FIXME("Unverified!\n");
    RtlInitCodePageTable(QEMU_G2H(c->ptr), QEMU_G2H(c->info));
}

#endif

struct qemu_RtlInitNlsTables
{
    struct qemu_syscall super;
    uint64_t ansi;
    uint64_t oem;
    uint64_t casetable;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlInitNlsTables(USHORT *ansi, USHORT *oem, USHORT *casetable, NLSTABLEINFO *info)
{
    struct qemu_RtlInitNlsTables call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLINITNLSTABLES);
    call.ansi = (ULONG_PTR)ansi;
    call.oem = (ULONG_PTR)oem;
    call.casetable = (ULONG_PTR)casetable;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlInitNlsTables(struct qemu_syscall *call)
{
    struct qemu_RtlInitNlsTables *c = (struct qemu_RtlInitNlsTables *)call;
    NLSTABLEINFO stack, *info = &stack;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->info);
#endif

    RtlInitNlsTables(QEMU_G2H(c->ansi), QEMU_G2H(c->oem), QEMU_G2H(c->casetable), info);

#if GUEST_BIT != HOST_BIT
    NLSTABLEINFO_h2g(QEMU_G2H(c->info), info);
#endif
}

#endif

struct qemu_RtlResetRtlTranslations
{
    struct qemu_syscall super;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI RtlResetRtlTranslations(const NLSTABLEINFO *info)
{
    struct qemu_RtlResetRtlTranslations call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLRESETRTLTRANSLATIONS);
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);
}

#else

void qemu_RtlResetRtlTranslations(struct qemu_syscall *call)
{
    struct qemu_RtlResetRtlTranslations *c = (struct qemu_RtlResetRtlTranslations *)call;
    NLSTABLEINFO stack, *info = &stack;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->info);
#else
    if (QEMU_G2H(c->info))
        NLSTABLEINFO_g2h(info, QEMU_G2H(c->info));
    else
        info = NULL;
#endif

    RtlResetRtlTranslations(info);
}

#endif

struct qemu_RtlAnsiCharToUnicodeChar
{
    struct qemu_syscall super;
    uint64_t ansi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WCHAR WINAPI RtlAnsiCharToUnicodeChar(char **ansi)
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
    call.len1 = len1;
    call.s2 = (ULONG_PTR)s2;
    call.len2 = len2;
    call.case_insensitive = case_insensitive;

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
    call.ignore_case = ignore_case;

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

struct qemu_RtlHashUnicodeString
{
    struct qemu_syscall super;
    uint64_t string;
    uint64_t case_insensitive;
    uint64_t alg;
    uint64_t hash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlHashUnicodeString(const UNICODE_STRING *string, BOOLEAN case_insensitive, ULONG alg, ULONG *hash)
{
    struct qemu_RtlHashUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLHASHUNICODESTRING);
    call.string = (ULONG_PTR)string;
    call.case_insensitive = case_insensitive;
    call.alg = alg;
    call.hash = (ULONG_PTR)hash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI RtlHashUnicodeString(const UNICODE_STRING *string, BOOLEAN case_insensitive, ULONG alg, ULONG *hash);
void qemu_RtlHashUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlHashUnicodeString *c = (struct qemu_RtlHashUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlHashUnicodeString(QEMU_G2H(c->string), c->case_insensitive, c->alg, QEMU_G2H(c->hash));
}

#endif

struct qemu_RtlCustomCPToUnicodeN
{
    struct qemu_syscall super;
    uint64_t info;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t reslen;
    uint64_t src;
    uint64_t srclen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlCustomCPToUnicodeN(CPTABLEINFO *info, WCHAR *dst, DWORD dstlen, DWORD *reslen, const char *src, DWORD srclen)
{
    struct qemu_RtlCustomCPToUnicodeN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLCUSTOMCPTOUNICODEN);
    call.info = (ULONG_PTR)info;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlCustomCPToUnicodeN(struct qemu_syscall *call)
{
    struct qemu_RtlCustomCPToUnicodeN *c = (struct qemu_RtlCustomCPToUnicodeN *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlCustomCPToUnicodeN(QEMU_G2H(c->info), QEMU_G2H(c->dst), c->dstlen, QEMU_G2H(c->reslen), QEMU_G2H(c->src), c->srclen);
}

#endif

struct qemu_RtlUnicodeToCustomCPN
{
    struct qemu_syscall super;
    uint64_t info;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t reslen;
    uint64_t src;
    uint64_t srclen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUnicodeToCustomCPN(CPTABLEINFO *info, char *dst, DWORD dstlen, DWORD *reslen, const WCHAR *src, DWORD srclen)
{
    struct qemu_RtlUnicodeToCustomCPN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNICODETOCUSTOMCPN);
    call.info = (ULONG_PTR)info;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUnicodeToCustomCPN(struct qemu_syscall *call)
{
    struct qemu_RtlUnicodeToCustomCPN *c = (struct qemu_RtlUnicodeToCustomCPN *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUnicodeToCustomCPN(QEMU_G2H(c->info), QEMU_G2H(c->dst), c->dstlen, QEMU_G2H(c->reslen), QEMU_G2H(c->src), c->srclen);
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

WINBASEAPI NTSTATUS WINAPI RtlMultiByteToUnicodeN(WCHAR *dst, DWORD dstlen, DWORD *reslen, const char *src, DWORD srclen)
{
    struct qemu_RtlMultiByteToUnicodeN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLMULTIBYTETOUNICODEN);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;

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

struct qemu_RtlMultiByteToUnicodeSize
{
    struct qemu_syscall super;
    uint64_t size;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlMultiByteToUnicodeSize(DWORD *size, const char *str, DWORD len)
{
    struct qemu_RtlMultiByteToUnicodeSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLMULTIBYTETOUNICODESIZE);
    call.size = (ULONG_PTR)size;
    call.str = (ULONG_PTR)str;
    call.len = len;

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

WINBASEAPI NTSTATUS WINAPI RtlOemToUnicodeN(WCHAR *dst, DWORD dstlen, DWORD *reslen, const char *src, DWORD srclen)
{
    struct qemu_RtlOemToUnicodeN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLOEMTOUNICODEN);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;

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

struct qemu_RtlOemStringToUnicodeSize
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI RtlOemStringToUnicodeSize(const STRING *str)
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

WINBASEAPI NTSTATUS WINAPI RtlUnicodeToMultiByteN(char *dst, DWORD dstlen, DWORD *reslen, const WCHAR *src, DWORD srclen)
{
    struct qemu_RtlUnicodeToMultiByteN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNICODETOMULTIBYTEN);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;

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

struct qemu_RtlUnicodeToMultiByteSize
{
    struct qemu_syscall super;
    uint64_t size;
    uint64_t str;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUnicodeToMultiByteSize(DWORD *size, WCHAR *str, DWORD len)
{
    struct qemu_RtlUnicodeToMultiByteSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNICODETOMULTIBYTESIZE);
    call.size = (ULONG_PTR)size;
    call.str = (ULONG_PTR)str;
    call.len = len;

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

WINBASEAPI NTSTATUS WINAPI RtlUnicodeToOemN(char *dst, DWORD dstlen, DWORD *reslen, const WCHAR *src, DWORD srclen)
{
    struct qemu_RtlUnicodeToOemN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNICODETOOEMN);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;

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
    call.wch = wch;

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

struct qemu_RtlDowncaseUnicodeString
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
    uint64_t alloc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlDowncaseUnicodeString(UNICODE_STRING *dest, const UNICODE_STRING *src, BOOLEAN alloc)
{
    struct qemu_RtlDowncaseUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLDOWNCASEUNICODESTRING);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;
    call.alloc = alloc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlDowncaseUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlDowncaseUnicodeString *c = (struct qemu_RtlDowncaseUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlDowncaseUnicodeString(QEMU_G2H(c->dest), QEMU_G2H(c->src), c->alloc);
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUpcaseUnicodeChar(c->wch);
}

#endif

struct qemu_RtlUpcaseUnicodeString
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t src;
    uint64_t alloc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUpcaseUnicodeString(UNICODE_STRING *dest, const UNICODE_STRING *src, BOOLEAN alloc)
{
    struct qemu_RtlUpcaseUnicodeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPCASEUNICODESTRING);
    call.dest = (ULONG_PTR)dest;
    call.src = (ULONG_PTR)src;
    call.alloc = alloc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUpcaseUnicodeString(struct qemu_syscall *call)
{
    struct qemu_RtlUpcaseUnicodeString *c = (struct qemu_RtlUpcaseUnicodeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUpcaseUnicodeString(QEMU_G2H(c->dest), QEMU_G2H(c->src), c->alloc);
}

#endif

struct qemu_RtlUpcaseUnicodeToCustomCPN
{
    struct qemu_syscall super;
    uint64_t info;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t reslen;
    uint64_t src;
    uint64_t srclen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUpcaseUnicodeToCustomCPN(CPTABLEINFO *info, char *dst, DWORD dstlen, DWORD *reslen, const WCHAR *src, DWORD srclen)
{
    struct qemu_RtlUpcaseUnicodeToCustomCPN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPCASEUNICODETOCUSTOMCPN);
    call.info = (ULONG_PTR)info;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUpcaseUnicodeToCustomCPN(struct qemu_syscall *call)
{
    struct qemu_RtlUpcaseUnicodeToCustomCPN *c = (struct qemu_RtlUpcaseUnicodeToCustomCPN *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUpcaseUnicodeToCustomCPN(QEMU_G2H(c->info), QEMU_G2H(c->dst), c->dstlen, QEMU_G2H(c->reslen), QEMU_G2H(c->src), c->srclen);
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

WINBASEAPI NTSTATUS WINAPI RtlUpcaseUnicodeToMultiByteN(char *dst, DWORD dstlen, DWORD *reslen, const WCHAR *src, DWORD srclen)
{
    struct qemu_RtlUpcaseUnicodeToMultiByteN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPCASEUNICODETOMULTIBYTEN);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;

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

WINBASEAPI NTSTATUS WINAPI RtlUpcaseUnicodeToOemN(char *dst, DWORD dstlen, DWORD *reslen, const WCHAR *src, DWORD srclen)
{
    struct qemu_RtlUpcaseUnicodeToOemN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUPCASEUNICODETOOEMN);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;

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

struct qemu_RtlLocaleNameToLcid
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t lcid;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlLocaleNameToLcid(const WCHAR *name, LCID *lcid, ULONG flags)
{
    struct qemu_RtlLocaleNameToLcid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLLOCALENAMETOLCID);
    call.name = (ULONG_PTR)name;
    call.lcid = (ULONG_PTR)lcid;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlLocaleNameToLcid(struct qemu_syscall *call)
{
    struct qemu_RtlLocaleNameToLcid *c = (struct qemu_RtlLocaleNameToLcid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlLocaleNameToLcid(QEMU_G2H(c->name), QEMU_G2H(c->lcid), c->flags);
}

#endif

struct qemu_RtlUTF8ToUnicodeN
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t reslen;
    uint64_t src;
    uint64_t srclen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUTF8ToUnicodeN(WCHAR *dst, DWORD dstlen, DWORD *reslen, const char *src, DWORD srclen)
{
    struct qemu_RtlUTF8ToUnicodeN call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUTF8TOUNICODEN);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUTF8ToUnicodeN(struct qemu_syscall *call)
{
    struct qemu_RtlUTF8ToUnicodeN *c = (struct qemu_RtlUTF8ToUnicodeN *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUTF8ToUnicodeN(QEMU_G2H(c->dst), c->dstlen, QEMU_G2H(c->reslen), QEMU_G2H(c->src), c->srclen);
}

#endif

struct qemu_RtlUnicodeToUTF8N
{
    struct qemu_syscall super;
    uint64_t dst;
    uint64_t dstlen;
    uint64_t reslen;
    uint64_t src;
    uint64_t srclen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlUnicodeToUTF8N(char *dst, DWORD dstlen, DWORD *reslen, const WCHAR *src, DWORD srclen)
{
    struct qemu_RtlUnicodeToUTF8N call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLUNICODETOUTF8N);
    call.dst = (ULONG_PTR)dst;
    call.dstlen = dstlen;
    call.reslen = (ULONG_PTR)reslen;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlUnicodeToUTF8N(struct qemu_syscall *call)
{
    struct qemu_RtlUnicodeToUTF8N *c = (struct qemu_RtlUnicodeToUTF8N *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlUnicodeToUTF8N(QEMU_G2H(c->dst), c->dstlen, QEMU_G2H(c->reslen), QEMU_G2H(c->src), c->srclen);
}

#endif

struct qemu_RtlIsNormalizedString
{
    struct qemu_syscall super;
    uint64_t form;
    uint64_t str;
    uint64_t len;
    uint64_t res;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlIsNormalizedString(ULONG form, const WCHAR *str, INT len, BOOLEAN *res)
{
    struct qemu_RtlIsNormalizedString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLISNORMALIZEDSTRING);
    call.form = form;
    call.str = (ULONG_PTR)str;
    call.len = len;
    call.res = (ULONG_PTR)res;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlIsNormalizedString(struct qemu_syscall *call)
{
    struct qemu_RtlIsNormalizedString *c = (struct qemu_RtlIsNormalizedString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIsNormalizedString(c->form, QEMU_G2H(c->str), c->len, QEMU_G2H(c->res));
}

#endif

struct qemu_RtlNormalizeString
{
    struct qemu_syscall super;
    uint64_t form;
    uint64_t src;
    uint64_t src_len;
    uint64_t dst;
    uint64_t dst_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlNormalizeString(ULONG form, const WCHAR *src, INT src_len, WCHAR *dst, INT *dst_len)
{
    struct qemu_RtlNormalizeString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLNORMALIZESTRING);
    call.form = form;
    call.src = (ULONG_PTR)src;
    call.src_len = src_len;
    call.dst = (ULONG_PTR)dst;
    call.dst_len = (ULONG_PTR)dst_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlNormalizeString(struct qemu_syscall *call)
{
    struct qemu_RtlNormalizeString *c = (struct qemu_RtlNormalizeString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlNormalizeString(c->form, QEMU_G2H(c->src), c->src_len, QEMU_G2H(c->dst), QEMU_G2H(c->dst_len));
}

#endif

struct qemu_RtlIdnToAscii
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t src;
    uint64_t srclen;
    uint64_t dst;
    uint64_t dstlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlIdnToAscii(DWORD flags, const WCHAR *src, INT srclen, WCHAR *dst, INT *dstlen)
{
    struct qemu_RtlIdnToAscii call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLIDNTOASCII);
    call.flags = flags;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = (ULONG_PTR)dstlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlIdnToAscii(struct qemu_syscall *call)
{
    struct qemu_RtlIdnToAscii *c = (struct qemu_RtlIdnToAscii *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIdnToAscii(c->flags, QEMU_G2H(c->src), c->srclen, QEMU_G2H(c->dst), QEMU_G2H(c->dstlen));
}

#endif

struct qemu_RtlIdnToNameprepUnicode
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t src;
    uint64_t srclen;
    uint64_t dst;
    uint64_t dstlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlIdnToNameprepUnicode(DWORD flags, const WCHAR *src, INT srclen, WCHAR *dst, INT *dstlen)
{
    struct qemu_RtlIdnToNameprepUnicode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLIDNTONAMEPREPUNICODE);
    call.flags = flags;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = (ULONG_PTR)dstlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlIdnToNameprepUnicode(struct qemu_syscall *call)
{
    struct qemu_RtlIdnToNameprepUnicode *c = (struct qemu_RtlIdnToNameprepUnicode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIdnToNameprepUnicode(c->flags, QEMU_G2H(c->src), c->srclen, QEMU_G2H(c->dst), QEMU_G2H(c->dstlen));
}

#endif

struct qemu_RtlIdnToUnicode
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t src;
    uint64_t srclen;
    uint64_t dst;
    uint64_t dstlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlIdnToUnicode(DWORD flags, const WCHAR *src, INT srclen, WCHAR *dst, INT *dstlen)
{
    struct qemu_RtlIdnToUnicode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLIDNTOUNICODE);
    call.flags = flags;
    call.src = (ULONG_PTR)src;
    call.srclen = srclen;
    call.dst = (ULONG_PTR)dst;
    call.dstlen = (ULONG_PTR)dstlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlIdnToUnicode(struct qemu_syscall *call)
{
    struct qemu_RtlIdnToUnicode *c = (struct qemu_RtlIdnToUnicode *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIdnToUnicode(c->flags, QEMU_G2H(c->src), c->srclen, QEMU_G2H(c->dst), QEMU_G2H(c->dstlen));
}

#endif

struct qemu___wine_get_unix_codepage
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

UINT CDECL __wine_get_unix_codepage(void)
{
    struct qemu___wine_get_unix_codepage call;
    call.super.id = QEMU_SYSCALL_ID(CALL___WINE_GET_UNIX_CODEPAGE);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern UINT CDECL __wine_get_unix_codepage(void);
void qemu___wine_get_unix_codepage(struct qemu_syscall *call)
{
    struct qemu___wine_get_unix_codepage *c = (struct qemu___wine_get_unix_codepage *)call;
    WINE_TRACE("\n");
    c->super.iret = __wine_get_unix_codepage();
}

#endif

struct qemu_RtlGetProcessPreferredUILanguages
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t count;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetProcessPreferredUILanguages(DWORD flags, ULONG *count, WCHAR *buffer, ULONG *size)
{
    struct qemu_RtlGetProcessPreferredUILanguages call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETPROCESSPREFERREDUILANGUAGES);
    call.flags = flags;
    call.count = (ULONG_PTR)count;
    call.buffer = (ULONG_PTR)buffer;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetProcessPreferredUILanguages(struct qemu_syscall *call)
{
    struct qemu_RtlGetProcessPreferredUILanguages *c = (struct qemu_RtlGetProcessPreferredUILanguages *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetProcessPreferredUILanguages(c->flags, QEMU_G2H(c->count), QEMU_G2H(c->buffer), QEMU_G2H(c->size));
}

#endif

struct qemu_RtlGetSystemPreferredUILanguages
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t unknown;
    uint64_t count;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetSystemPreferredUILanguages(DWORD flags, ULONG unknown, ULONG *count, WCHAR *buffer, ULONG *size)
{
    struct qemu_RtlGetSystemPreferredUILanguages call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETSYSTEMPREFERREDUILANGUAGES);
    call.flags = flags;
    call.unknown = unknown;
    call.count = (ULONG_PTR)count;
    call.buffer = (ULONG_PTR)buffer;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetSystemPreferredUILanguages(struct qemu_syscall *call)
{
    struct qemu_RtlGetSystemPreferredUILanguages *c = (struct qemu_RtlGetSystemPreferredUILanguages *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetSystemPreferredUILanguages(c->flags, c->unknown, QEMU_G2H(c->count), QEMU_G2H(c->buffer), QEMU_G2H(c->size));
}

#endif

struct qemu_RtlGetThreadPreferredUILanguages
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t count;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetThreadPreferredUILanguages(DWORD flags, ULONG *count, WCHAR *buffer, ULONG *size)
{
    struct qemu_RtlGetThreadPreferredUILanguages call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETTHREADPREFERREDUILANGUAGES);
    call.flags = flags;
    call.count = (ULONG_PTR)count;
    call.buffer = (ULONG_PTR)buffer;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetThreadPreferredUILanguages(struct qemu_syscall *call)
{
    struct qemu_RtlGetThreadPreferredUILanguages *c = (struct qemu_RtlGetThreadPreferredUILanguages *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetThreadPreferredUILanguages(c->flags, QEMU_G2H(c->count), QEMU_G2H(c->buffer), QEMU_G2H(c->size));
}

#endif

struct qemu_RtlGetUserPreferredUILanguages
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t unknown;
    uint64_t count;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlGetUserPreferredUILanguages(DWORD flags, ULONG unknown, ULONG *count, WCHAR *buffer, ULONG *size)
{
    struct qemu_RtlGetUserPreferredUILanguages call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLGETUSERPREFERREDUILANGUAGES);
    call.flags = flags;
    call.unknown = unknown;
    call.count = (ULONG_PTR)count;
    call.buffer = (ULONG_PTR)buffer;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlGetUserPreferredUILanguages(struct qemu_syscall *call)
{
    struct qemu_RtlGetUserPreferredUILanguages *c = (struct qemu_RtlGetUserPreferredUILanguages *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlGetUserPreferredUILanguages(c->flags, c->unknown, QEMU_G2H(c->count), QEMU_G2H(c->buffer), QEMU_G2H(c->size));
}

#endif

struct qemu_RtlSetProcessPreferredUILanguages
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSetProcessPreferredUILanguages(DWORD flags, PCZZWSTR buffer, ULONG *count)
{
    struct qemu_RtlSetProcessPreferredUILanguages call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETPROCESSPREFERREDUILANGUAGES);
    call.flags = flags;
    call.buffer = buffer;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetProcessPreferredUILanguages(struct qemu_syscall *call)
{
    struct qemu_RtlSetProcessPreferredUILanguages *c = (struct qemu_RtlSetProcessPreferredUILanguages *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetProcessPreferredUILanguages(c->flags, c->buffer, QEMU_G2H(c->count));
}

#endif

struct qemu_RtlSetThreadPreferredUILanguages
{
    struct qemu_syscall super;
    uint64_t flags;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI RtlSetThreadPreferredUILanguages(DWORD flags, PCZZWSTR buffer, ULONG *count)
{
    struct qemu_RtlSetThreadPreferredUILanguages call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLSETTHREADPREFERREDUILANGUAGES);
    call.flags = flags;
    call.buffer = buffer;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlSetThreadPreferredUILanguages(struct qemu_syscall *call)
{
    struct qemu_RtlSetThreadPreferredUILanguages *c = (struct qemu_RtlSetThreadPreferredUILanguages *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlSetThreadPreferredUILanguages(c->flags, c->buffer, QEMU_G2H(c->count));
}

#endif
