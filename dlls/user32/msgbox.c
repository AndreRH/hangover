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

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_MessageBoxA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t text;
    uint64_t title;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI MessageBoxA(HWND hWnd, LPCSTR text, LPCSTR title, UINT type)
{
    struct qemu_MessageBoxA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MESSAGEBOXA);
    call.hWnd = (LONG_PTR)hWnd;
    call.text = (ULONG_PTR)text;
    call.title = (ULONG_PTR)title;
    call.type = (ULONG_PTR)type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MessageBoxA(struct qemu_syscall *call)
{
    struct qemu_MessageBoxA *c = (struct qemu_MessageBoxA *)call;
    WINE_TRACE("\n");
    c->super.iret = MessageBoxA(QEMU_G2H(c->hWnd), QEMU_G2H(c->text), QEMU_G2H(c->title), c->type);
}

#endif

struct qemu_MessageBoxW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t text;
    uint64_t title;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI MessageBoxW(HWND hwnd, LPCWSTR text, LPCWSTR title, UINT type)
{
    struct qemu_MessageBoxW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MESSAGEBOXW);
    call.hwnd = (LONG_PTR)hwnd;
    call.text = (ULONG_PTR)text;
    call.title = (ULONG_PTR)title;
    call.type = (ULONG_PTR)type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MessageBoxW(struct qemu_syscall *call)
{
    struct qemu_MessageBoxW *c = (struct qemu_MessageBoxW *)call;
    WINE_TRACE("\n");
    c->super.iret = MessageBoxW(QEMU_G2H(c->hwnd), QEMU_G2H(c->text), QEMU_G2H(c->title), c->type);
}

#endif

struct qemu_MessageBoxExA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t text;
    uint64_t title;
    uint64_t type;
    uint64_t langid;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI MessageBoxExA(HWND hWnd, LPCSTR text, LPCSTR title, UINT type, WORD langid)
{
    struct qemu_MessageBoxExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MESSAGEBOXEXA);
    call.hWnd = (LONG_PTR)hWnd;
    call.text = (ULONG_PTR)text;
    call.title = (ULONG_PTR)title;
    call.type = (ULONG_PTR)type;
    call.langid = (ULONG_PTR)langid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MessageBoxExA(struct qemu_syscall *call)
{
    struct qemu_MessageBoxExA *c = (struct qemu_MessageBoxExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MessageBoxExA(QEMU_G2H(c->hWnd), QEMU_G2H(c->text), QEMU_G2H(c->title), c->type, c->langid);
}

#endif

struct qemu_MessageBoxExW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t text;
    uint64_t title;
    uint64_t type;
    uint64_t langid;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI MessageBoxExW(HWND hWnd, LPCWSTR text, LPCWSTR title, UINT type, WORD langid)
{
    struct qemu_MessageBoxExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MESSAGEBOXEXW);
    call.hWnd = (LONG_PTR)hWnd;
    call.text = (ULONG_PTR)text;
    call.title = (ULONG_PTR)title;
    call.type = (ULONG_PTR)type;
    call.langid = (ULONG_PTR)langid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MessageBoxExW(struct qemu_syscall *call)
{
    struct qemu_MessageBoxExW *c = (struct qemu_MessageBoxExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MessageBoxExW(QEMU_G2H(c->hWnd), QEMU_G2H(c->text), QEMU_G2H(c->title), c->type, c->langid);
}

#endif

struct qemu_MessageBoxTimeoutA
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t text;
    uint64_t title;
    uint64_t type;
    uint64_t langid;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI MessageBoxTimeoutA(HWND hWnd, LPCSTR text, LPCSTR title, UINT type, WORD langid, DWORD timeout)
{
    struct qemu_MessageBoxTimeoutA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MESSAGEBOXTIMEOUTA);
    call.hWnd = (LONG_PTR)hWnd;
    call.text = (ULONG_PTR)text;
    call.title = (ULONG_PTR)title;
    call.type = (ULONG_PTR)type;
    call.langid = (ULONG_PTR)langid;
    call.timeout = (ULONG_PTR)timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add MessageBoxTimeoutA to Wine headers? */
extern INT WINAPI MessageBoxTimeoutA(HWND hWnd, LPCSTR text, LPCSTR title, UINT type, WORD langid, DWORD timeout);
void qemu_MessageBoxTimeoutA(struct qemu_syscall *call)
{
    struct qemu_MessageBoxTimeoutA *c = (struct qemu_MessageBoxTimeoutA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MessageBoxTimeoutA(QEMU_G2H(c->hWnd), QEMU_G2H(c->text), QEMU_G2H(c->title), c->type, c->langid, c->timeout);
}

#endif

struct qemu_MessageBoxTimeoutW
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t text;
    uint64_t title;
    uint64_t type;
    uint64_t langid;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI MessageBoxTimeoutW(HWND hWnd, LPCWSTR text, LPCWSTR title, UINT type, WORD langid, DWORD timeout)
{
    struct qemu_MessageBoxTimeoutW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MESSAGEBOXTIMEOUTW);
    call.hWnd = (LONG_PTR)hWnd;
    call.text = (ULONG_PTR)text;
    call.title = (ULONG_PTR)title;
    call.type = (ULONG_PTR)type;
    call.langid = (ULONG_PTR)langid;
    call.timeout = (ULONG_PTR)timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add MessageBoxTimeoutW to Wine headers? */
extern INT WINAPI MessageBoxTimeoutW(HWND hWnd, LPCWSTR text, LPCWSTR title, UINT type, WORD langid, DWORD timeout);
void qemu_MessageBoxTimeoutW(struct qemu_syscall *call)
{
    struct qemu_MessageBoxTimeoutW *c = (struct qemu_MessageBoxTimeoutW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = MessageBoxTimeoutW(QEMU_G2H(c->hWnd), QEMU_G2H(c->text), QEMU_G2H(c->title), c->type, c->langid, c->timeout);
}

#endif

struct qemu_MessageBoxIndirectA
{
    struct qemu_syscall super;
    uint64_t lpmbp;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI int WINAPI MessageBoxIndirectA(CONST MSGBOXPARAMSA *lpmbp)
{
    struct qemu_MessageBoxIndirectA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MESSAGEBOXINDIRECTA);
    call.lpmbp = (ULONG_PTR)lpmbp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MessageBoxIndirectA(struct qemu_syscall *call)
{
    struct qemu_MessageBoxIndirectA *c = (struct qemu_MessageBoxIndirectA *)call;
    MSGBOXPARAMSA copy, *params = &copy;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    params = QEMU_G2H(c->lpmbp);
#else
    MSGBOXPARAMS_g2h((MSGBOXPARAMSW *)params, QEMU_G2H(c->lpmbp));
#endif

    if (params->lpfnMsgBoxCallback)
        WINE_FIXME("Handle message box callback\n");
    c->super.iret = MessageBoxIndirectA(params);
}

#endif

struct qemu_MessageBoxIndirectW
{
    struct qemu_syscall super;
    uint64_t lpmbp;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI int WINAPI MessageBoxIndirectW(CONST MSGBOXPARAMSW *lpmbp)
{
    struct qemu_MessageBoxIndirectW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MESSAGEBOXINDIRECTW);
    call.lpmbp = (ULONG_PTR)lpmbp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MessageBoxIndirectW(struct qemu_syscall *call)
{
    struct qemu_MessageBoxIndirectW *c = (struct qemu_MessageBoxIndirectW *)call;
    MSGBOXPARAMSW copy, *params = &copy;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    params = QEMU_G2H(c->lpmbp);
#else
    MSGBOXPARAMS_g2h(params, QEMU_G2H(c->lpmbp));
#endif

    if (params->lpfnMsgBoxCallback)
        WINE_FIXME("Handle message box callback\n");
    c->super.iret = MessageBoxIndirectW(params);
}

#endif

