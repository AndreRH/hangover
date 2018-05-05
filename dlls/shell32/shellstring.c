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
#include <shlwapi.h>
#include <shlobj.h>

#include "thunk/qemu_shtypes.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

struct qemu_StrRetToStrNAW
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t len;
    uint64_t src;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StrRetToStrNAW(LPVOID dest, DWORD len, LPSTRRET src, const ITEMIDLIST *pidl)
{
    struct qemu_StrRetToStrNAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRRETTOSTRNAW);
    call.dest = (ULONG_PTR)dest;
    call.len = len;
    call.src = (ULONG_PTR)src;
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrRetToStrNAW(struct qemu_syscall *call)
{
    struct qemu_StrRetToStrNAW *c = (struct qemu_StrRetToStrNAW *)call;
    STRRET stack, *src = &stack;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    src = QEMU_G2H(c->src);
#else
    if (c->src)
        STRRET_g2h(src, QEMU_G2H(c->src));
    else
        src = NULL;

    /* The ITEMIDLIST ist just cast to a char * by the implementation. */
#endif

    c->super.iret = p_StrRetToStrNAW(QEMU_G2H(c->dest), c->len, src, QEMU_G2H(c->pidl));
}

#endif

struct qemu_StrToOleStrAW
{
    struct qemu_syscall super;
    uint64_t lpWideCharStr;
    uint64_t lpString;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StrToOleStrAW (LPWSTR lpWideCharStr, LPCVOID lpString)
{
    struct qemu_StrToOleStrAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOOLESTRAW);
    call.lpWideCharStr = (ULONG_PTR)lpWideCharStr;
    call.lpString = (ULONG_PTR)lpString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrToOleStrAW(struct qemu_syscall *call)
{
    struct qemu_StrToOleStrAW *c = (struct qemu_StrToOleStrAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_StrToOleStrAW(QEMU_G2H(c->lpWideCharStr), QEMU_G2H(c->lpString));
}

#endif

struct qemu_StrToOleStrNAW
{
    struct qemu_syscall super;
    uint64_t lpWide;
    uint64_t nWide;
    uint64_t lpStr;
    uint64_t nStr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI StrToOleStrNAW (LPWSTR lpWide, INT nWide, LPCVOID lpStr, INT nStr)
{
    struct qemu_StrToOleStrNAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STRTOOLESTRNAW);
    call.lpWide = (ULONG_PTR)lpWide;
    call.nWide = nWide;
    call.lpStr = (ULONG_PTR)lpStr;
    call.nStr = nStr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StrToOleStrNAW(struct qemu_syscall *call)
{
    struct qemu_StrToOleStrNAW *c = (struct qemu_StrToOleStrNAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_StrToOleStrNAW(QEMU_G2H(c->lpWide), c->nWide, QEMU_G2H(c->lpStr), c->nStr);
}

#endif

struct qemu_OleStrToStrNAW
{
    struct qemu_syscall super;
    uint64_t lpOut;
    uint64_t nOut;
    uint64_t lpIn;
    uint64_t nIn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI OleStrToStrNAW (LPVOID lpOut, INT nOut, LPCVOID lpIn, INT nIn)
{
    struct qemu_OleStrToStrNAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_OLESTRTOSTRNAW);
    call.lpOut = (ULONG_PTR)lpOut;
    call.nOut = nOut;
    call.lpIn = (ULONG_PTR)lpIn;
    call.nIn = nIn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_OleStrToStrNAW(struct qemu_syscall *call)
{
    struct qemu_OleStrToStrNAW *c = (struct qemu_OleStrToStrNAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_OleStrToStrNAW(QEMU_G2H(c->lpOut), c->nOut, QEMU_G2H(c->lpIn), c->nIn);
}

#endif

struct qemu_CheckEscapesA
{
    struct qemu_syscall super;
    uint64_t string;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CheckEscapesA(LPSTR string, DWORD len)
{
    struct qemu_CheckEscapesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHECKESCAPESA);
    call.string = (ULONG_PTR)string;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CheckEscapesA to Wine headers? */
extern DWORD WINAPI CheckEscapesA(LPSTR string, DWORD len);
void qemu_CheckEscapesA(struct qemu_syscall *call)
{
    struct qemu_CheckEscapesA *c = (struct qemu_CheckEscapesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CheckEscapesA(QEMU_G2H(c->string), c->len);
}

#endif

struct qemu_CheckEscapesW
{
    struct qemu_syscall super;
    uint64_t string;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI CheckEscapesW(LPWSTR string, DWORD len)
{
    struct qemu_CheckEscapesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CHECKESCAPESW);
    call.string = (ULONG_PTR)string;
    call.len = len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add CheckEscapesW to Wine headers? */
extern DWORD WINAPI CheckEscapesW(LPWSTR string, DWORD len);
void qemu_CheckEscapesW(struct qemu_syscall *call)
{
    struct qemu_CheckEscapesW *c = (struct qemu_CheckEscapesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CheckEscapesW(QEMU_G2H(c->string), c->len);
}

#endif

