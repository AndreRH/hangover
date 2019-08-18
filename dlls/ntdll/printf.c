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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);
#endif


struct qemu_snprintf
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPIV NTDLL__snprintf(char *str, SIZE_T len, const char *format, ...)
{
    struct qemu_snprintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDLL__SNPRINTF);
    call.str = (ULONG_PTR)str;
    call.len = len;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NTDLL__snprintf(struct qemu_syscall *call)
{
    struct qemu_snprintf *c = (struct qemu_snprintf *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = -1;//p_snprintf(QEMU_G2H(c->str), c->len, QEMU_G2H(c->format),);
}

#endif

struct qemu_snwprintf
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPIV NTDLL__snwprintf(WCHAR *str, SIZE_T len, const WCHAR *format, ...)
{
    struct qemu_snwprintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDLL__SNWPRINTF);
    call.str = (ULONG_PTR)str;
    call.len = len;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NTDLL__snwprintf(struct qemu_syscall *call)
{
    struct qemu_snwprintf *c = (struct qemu_snwprintf *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = -1;//p_snwprintf(QEMU_G2H(c->str), c->len, QEMU_G2H(c->format));
}

#endif

struct qemu__snprintf_s
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t size;
    uint64_t len;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPIV ntdll_snprintf_s(char *str, SIZE_T size, SIZE_T len, const char *format, ...)
{
    struct qemu__snprintf_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__SNPRINTF_S);
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.len = len;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__snprintf_s(struct qemu_syscall *call)
{
    struct qemu__snprintf_s *c = (struct qemu__snprintf_s *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = -1;//_snprintf_s(QEMU_G2H(c->str), c->size, c->len, QEMU_G2H(c->format));
}

#endif

struct qemu_NTDLL_sprintf
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPIV NTDLL_sprintf(char *str, const char *format, ...)
{
    struct qemu_NTDLL_sprintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDLL_SPRINTF);
    call.str = (ULONG_PTR)str;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NTDLL_sprintf(struct qemu_syscall *call)
{
    struct qemu_NTDLL_sprintf *c = (struct qemu_NTDLL_sprintf *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = -1;//NTDLL_sprintf(QEMU_G2H(c->str), QEMU_G2H(c->format));
}

#endif

struct qemu_NTDLL_swprintf
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPIV NTDLL_swprintf(WCHAR *str, const WCHAR *format, ...)
{
    struct qemu_NTDLL_swprintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDLL_SWPRINTF);
    call.str = (ULONG_PTR)str;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NTDLL_swprintf(struct qemu_syscall *call)
{
    struct qemu_NTDLL_swprintf *c = (struct qemu_NTDLL_swprintf *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = -1;//NTDLL_swprintf(QEMU_G2H(c->str), QEMU_G2H(c->format));
}

#endif

struct qemu_vsnprintf
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
    uint64_t format;
    uint64_t args;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL__vsnprintf(char *str, SIZE_T len, const char *format, va_list args)
{
    struct qemu_vsnprintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDLL__VSNPRINTF);
    call.str = (ULONG_PTR)str;
    call.len = len;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NTDLL__vsnprintf(struct qemu_syscall *call)
{
    struct qemu_vsnprintf *c = (struct qemu_vsnprintf *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = -1;//p_vsnprintf(QEMU_G2H(c->str), c->len, QEMU_G2H(c->format), c->args);
}

#endif

struct qemu_vsnwprintf
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t len;
    uint64_t format;
    uint64_t args;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL__vsnwprintf(WCHAR *str, SIZE_T len, const WCHAR *format, va_list args)
{
    struct qemu_vsnwprintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDLL__VSNWPRINTF);
    call.str = (ULONG_PTR)str;
    call.len = len;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NTDLL__vsnwprintf(struct qemu_syscall *call)
{
    struct qemu_vsnwprintf *c = (struct qemu_vsnwprintf *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = -1;//p_vsnwprintf(QEMU_G2H(c->str), c->len, QEMU_G2H(c->format), c->args);
}

#endif

struct qemu__vsnprintf_s
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t size;
    uint64_t len;
    uint64_t format;
    uint64_t args;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL ntdll_vsnprintf_s(char *str, SIZE_T size, SIZE_T len, const char *format, va_list args)
{
    struct qemu__vsnprintf_s call;
    call.super.id = QEMU_SYSCALL_ID(CALL__VSNPRINTF_S);
    call.str = (ULONG_PTR)str;
    call.size = size;
    call.len = len;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu__vsnprintf_s(struct qemu_syscall *call)
{
    struct qemu__vsnprintf_s *c = (struct qemu__vsnprintf_s *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = -1;//_vsnprintf_s(QEMU_G2H(c->str), c->size, c->len, QEMU_G2H(c->format), c->args);
}

#endif

struct qemu_NTDLL_vsprintf
{
    struct qemu_syscall super;
    uint64_t str;
    uint64_t format;
    uint64_t args;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int CDECL NTDLL_vsprintf(char *str, const char *format, va_list args)
{
    struct qemu_NTDLL_vsprintf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDLL_VSPRINTF);
    call.str = (ULONG_PTR)str;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NTDLL_vsprintf(struct qemu_syscall *call)
{
    struct qemu_NTDLL_vsprintf *c = (struct qemu_NTDLL_vsprintf *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = -1;//p_vsprintf(QEMU_G2H(c->str), QEMU_G2H(c->format), c->args);
}

#endif

