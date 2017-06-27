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
#include "user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_EnumPropsA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t func;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI EnumPropsA(HWND hwnd, PROPENUMPROCA func)
{
    struct qemu_EnumPropsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPROPSA);
    call.hwnd = (uint64_t)hwnd;
    call.func = (uint64_t)func;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPropsA(struct qemu_syscall *call)
{
    struct qemu_EnumPropsA *c = (struct qemu_EnumPropsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPropsA(QEMU_G2H(c->hwnd), QEMU_G2H(c->func));
}

#endif

struct qemu_EnumPropsW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t func;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI EnumPropsW(HWND hwnd, PROPENUMPROCW func)
{
    struct qemu_EnumPropsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPROPSW);
    call.hwnd = (uint64_t)hwnd;
    call.func = (uint64_t)func;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPropsW(struct qemu_syscall *call)
{
    struct qemu_EnumPropsW *c = (struct qemu_EnumPropsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPropsW(QEMU_G2H(c->hwnd), QEMU_G2H(c->func));
}

#endif

struct qemu_GetPropA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HANDLE WINAPI GetPropA(HWND hwnd, LPCSTR str)
{
    struct qemu_GetPropA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROPA);
    call.hwnd = (uint64_t)hwnd;
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_GetPropA(struct qemu_syscall *call)
{
    struct qemu_GetPropA *c = (struct qemu_GetPropA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetPropA(QEMU_G2H(c->hwnd), QEMU_G2H(c->str));
}

#endif

struct qemu_GetPropW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HANDLE WINAPI GetPropW(HWND hwnd, LPCWSTR str)
{
    struct qemu_GetPropW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETPROPW);
    call.hwnd = (uint64_t)hwnd;
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_GetPropW(struct qemu_syscall *call)
{
    struct qemu_GetPropW *c = (struct qemu_GetPropW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetPropW(QEMU_G2H(c->hwnd), QEMU_G2H(c->str));
}

#endif

struct qemu_SetPropA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t str;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetPropA(HWND hwnd, LPCSTR str, HANDLE handle)
{
    struct qemu_SetPropA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPROPA);
    call.hwnd = (uint64_t)hwnd;
    call.str = (uint64_t)str;
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPropA(struct qemu_syscall *call)
{
    struct qemu_SetPropA *c = (struct qemu_SetPropA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPropA(QEMU_G2H(c->hwnd), QEMU_G2H(c->str), QEMU_G2H(c->handle));
}

#endif

struct qemu_SetPropW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t str;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI BOOL WINAPI SetPropW(HWND hwnd, LPCWSTR str, HANDLE handle)
{
    struct qemu_SetPropW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETPROPW);
    call.hwnd = (uint64_t)hwnd;
    call.str = (uint64_t)str;
    call.handle = (uint64_t)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetPropW(struct qemu_syscall *call)
{
    struct qemu_SetPropW *c = (struct qemu_SetPropW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetPropW(QEMU_G2H(c->hwnd), QEMU_G2H(c->str), QEMU_G2H(c->handle));
}

#endif

struct qemu_RemovePropA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HANDLE WINAPI RemovePropA(HWND hwnd, LPCSTR str)
{
    struct qemu_RemovePropA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVEPROPA);
    call.hwnd = (uint64_t)hwnd;
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_RemovePropA(struct qemu_syscall *call)
{
    struct qemu_RemovePropA *c = (struct qemu_RemovePropA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)RemovePropA(QEMU_G2H(c->hwnd), QEMU_G2H(c->str));
}

#endif

struct qemu_RemovePropW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI HANDLE WINAPI RemovePropW(HWND hwnd, LPCWSTR str)
{
    struct qemu_RemovePropW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_REMOVEPROPW);
    call.hwnd = (uint64_t)hwnd;
    call.str = (uint64_t)str;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_RemovePropW(struct qemu_syscall *call)
{
    struct qemu_RemovePropW *c = (struct qemu_RemovePropW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)RemovePropW(QEMU_G2H(c->hwnd), QEMU_G2H(c->str));
}

#endif

struct qemu_EnumPropsExA
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t func;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI EnumPropsExA(HWND hwnd, PROPENUMPROCEXA func, LPARAM lParam)
{
    struct qemu_EnumPropsExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPROPSEXA);
    call.hwnd = (uint64_t)hwnd;
    call.func = (uint64_t)func;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPropsExA(struct qemu_syscall *call)
{
    struct qemu_EnumPropsExA *c = (struct qemu_EnumPropsExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPropsExA(QEMU_G2H(c->hwnd), QEMU_G2H(c->func), c->lParam);
}

#endif

struct qemu_EnumPropsExW
{
    struct qemu_syscall super;
    uint64_t hwnd;
    uint64_t func;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI INT WINAPI EnumPropsExW(HWND hwnd, PROPENUMPROCEXW func, LPARAM lParam)
{
    struct qemu_EnumPropsExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPROPSEXW);
    call.hwnd = (uint64_t)hwnd;
    call.func = (uint64_t)func;
    call.lParam = (uint64_t)lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumPropsExW(struct qemu_syscall *call)
{
    struct qemu_EnumPropsExW *c = (struct qemu_EnumPropsExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumPropsExW(QEMU_G2H(c->hwnd), QEMU_G2H(c->func), c->lParam);
}

#endif

