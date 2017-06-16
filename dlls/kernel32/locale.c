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
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_CompareStringW
{
    struct qemu_syscall super;
    uint64_t lcid;
    uint64_t flags;
    uint64_t str1;
    uint64_t len1;
    uint64_t str2;
    uint64_t len2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI CompareStringW(LCID lcid, DWORD flags, LPCWSTR str1, INT len1, LPCWSTR str2, INT len2)
{
    struct qemu_CompareStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMPARESTRINGW);
    call.lcid = (uint64_t)lcid;
    call.flags = (uint64_t)flags;
    call.str1 = (uint64_t)str1;
    call.len1 = (uint64_t)len1;
    call.str2 = (uint64_t)str2;
    call.len2 = (uint64_t)len2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CompareStringW(struct qemu_syscall *call)
{
    struct qemu_CompareStringW *c = (struct qemu_CompareStringW *)call;
    WINE_TRACE("\n");
    c->super.iret = CompareStringW(c->lcid, c->flags, QEMU_G2H(c->str1), c->len1, QEMU_G2H(c->str2), c->len2);
}

#endif

struct qemu_GetCPInfoExW
{
    struct qemu_syscall super;
    uint64_t codepage;
    uint64_t flags;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI GetCPInfoExW(UINT codepage, DWORD flags, CPINFOEXW *info)
{
    struct qemu_GetCPInfoExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCPINFOEXW);
    call.codepage = codepage;
    call.flags = flags;
    call.info = (uint64_t)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCPInfoExW(struct qemu_syscall *call)
{
    struct qemu_GetCPInfoExW *c = (struct qemu_GetCPInfoExW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetCPInfoExW(c->codepage, c->flags, QEMU_G2H(c->info));
}

#endif

struct qemu_lstrcmpW
{
    struct qemu_syscall super;
    uint64_t str1;
    uint64_t str2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI lstrcmpW(const WCHAR *str1, const WCHAR *str2)
{
    struct qemu_lstrcmpW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSTRCMPW);
    call.str1 = (uint64_t)str1;
    call.str2 = (uint64_t)str2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_lstrcmpW(struct qemu_syscall *call)
{
    struct qemu_lstrcmpW *c = (struct qemu_lstrcmpW *)call;
    c->super.iret = lstrcmpW(QEMU_G2H(c->str1), QEMU_G2H(c->str2));
}

#endif

struct qemu_MultiByteToWideChar
{
    struct qemu_syscall super;
    uint64_t codepage;
    uint64_t flags;
    uint64_t mbstr;
    uint64_t mblen;
    uint64_t wstr;
    uint64_t wlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI MultiByteToWideChar(UINT codepage, DWORD flags, LPCCH mbstr, int mblen, WCHAR *wstr, int wlen)
{
    struct qemu_MultiByteToWideChar call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MULTIBYTETOWIDECHAR);
    call.codepage = codepage;
    call.flags = flags;
    call.mbstr = (uint64_t)mbstr;
    call.mblen = mblen;
    call.wstr = (uint64_t)wstr;
    call.wlen = wlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MultiByteToWideChar(struct qemu_syscall *call)
{
    struct qemu_MultiByteToWideChar *c = (struct qemu_MultiByteToWideChar *)call;
    WINE_TRACE("\n");
    c->super.iret = MultiByteToWideChar(c->codepage, c->flags, QEMU_G2H(c->mbstr), c->mblen, QEMU_G2H(c->wstr), c->wlen);
}


#endif

struct qemu_WideCharToMultiByte
{
    struct qemu_syscall super;
    uint64_t codepage;
    uint64_t flags;
    uint64_t wstr;
    uint64_t wlen;
    uint64_t mbstr;
    uint64_t mblen;
    uint64_t default_char;
    uint64_t used_default;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WideCharToMultiByte(UINT codepage, DWORD flags, LPCWCH wstr, int wlen, CHAR *mbstr, int mblen,
        LPCCH default_char, BOOL *used_default)
{
    struct qemu_WideCharToMultiByte call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WIDECHARTOMULTIBYTE);
    call.codepage = codepage;
    call.flags = flags;
    call.wstr = (uint64_t)wstr;
    call.wlen = wlen;
    call.mbstr = (uint64_t)mbstr;
    call.mblen = mblen;
    call.default_char = (uint64_t)default_char;
    call.used_default = (uint64_t)used_default;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WideCharToMultiByte(struct qemu_syscall *call)
{
    struct qemu_WideCharToMultiByte *c = (struct qemu_WideCharToMultiByte *)call;
    WINE_TRACE("\n");
    c->super.iret = WideCharToMultiByte(c->codepage, c->flags, QEMU_G2H(c->wstr), c->wlen, QEMU_G2H(c->mbstr), c->mblen,
            QEMU_G2H(c->default_char), QEMU_G2H(c->used_default));
}

#endif
