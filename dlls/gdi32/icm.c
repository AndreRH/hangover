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
#include "gdi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);
#endif


struct qemu_EnumICMProfilesA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t func;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI EnumICMProfilesA(HDC hdc, ICMENUMPROCA func, LPARAM lparam)
{
    struct qemu_EnumICMProfilesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMICMPROFILESA);
    call.hdc = (uint64_t)hdc;
    call.func = (uint64_t)func;
    call.lparam = (uint64_t)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumICMProfilesA(struct qemu_syscall *call)
{
    struct qemu_EnumICMProfilesA *c = (struct qemu_EnumICMProfilesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumICMProfilesA(QEMU_G2H(c->hdc), QEMU_G2H(c->func), c->lparam);
}

#endif

struct qemu_EnumICMProfilesW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t func;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI EnumICMProfilesW(HDC hdc, ICMENUMPROCW func, LPARAM lparam)
{
    struct qemu_EnumICMProfilesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMICMPROFILESW);
    call.hdc = (uint64_t)hdc;
    call.func = (uint64_t)func;
    call.lparam = (uint64_t)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumICMProfilesW(struct qemu_syscall *call)
{
    struct qemu_EnumICMProfilesW *c = (struct qemu_EnumICMProfilesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumICMProfilesW(QEMU_G2H(c->hdc), QEMU_G2H(c->func), c->lparam);
}

#endif

struct qemu_GetICMProfileA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t size;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetICMProfileA(HDC hdc, LPDWORD size, LPSTR filename)
{
    struct qemu_GetICMProfileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETICMPROFILEA);
    call.hdc = (uint64_t)hdc;
    call.size = (uint64_t)size;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetICMProfileA(struct qemu_syscall *call)
{
    struct qemu_GetICMProfileA *c = (struct qemu_GetICMProfileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetICMProfileA(QEMU_G2H(c->hdc), QEMU_G2H(c->size), QEMU_G2H(c->filename));
}

#endif

struct qemu_GetICMProfileW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t size;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetICMProfileW(HDC hdc, LPDWORD size, LPWSTR filename)
{
    struct qemu_GetICMProfileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETICMPROFILEW);
    call.hdc = (uint64_t)hdc;
    call.size = (uint64_t)size;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetICMProfileW(struct qemu_syscall *call)
{
    struct qemu_GetICMProfileW *c = (struct qemu_GetICMProfileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetICMProfileW(QEMU_G2H(c->hdc), QEMU_G2H(c->size), QEMU_G2H(c->filename));
}

#endif

struct qemu_GetLogColorSpaceA
{
    struct qemu_syscall super;
    uint64_t colorspace;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetLogColorSpaceA(HCOLORSPACE colorspace, LPLOGCOLORSPACEA buffer, DWORD size)
{
    struct qemu_GetLogColorSpaceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLOGCOLORSPACEA);
    call.colorspace = (uint64_t)colorspace;
    call.buffer = (uint64_t)buffer;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLogColorSpaceA(struct qemu_syscall *call)
{
    struct qemu_GetLogColorSpaceA *c = (struct qemu_GetLogColorSpaceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetLogColorSpaceA(QEMU_G2H(c->colorspace), QEMU_G2H(c->buffer), c->size);
}

#endif

struct qemu_GetLogColorSpaceW
{
    struct qemu_syscall super;
    uint64_t colorspace;
    uint64_t buffer;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetLogColorSpaceW(HCOLORSPACE colorspace, LPLOGCOLORSPACEW buffer, DWORD size)
{
    struct qemu_GetLogColorSpaceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETLOGCOLORSPACEW);
    call.colorspace = (uint64_t)colorspace;
    call.buffer = (uint64_t)buffer;
    call.size = (uint64_t)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetLogColorSpaceW(struct qemu_syscall *call)
{
    struct qemu_GetLogColorSpaceW *c = (struct qemu_GetLogColorSpaceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetLogColorSpaceW(QEMU_G2H(c->colorspace), QEMU_G2H(c->buffer), c->size);
}

#endif

struct qemu_SetICMProfileA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetICMProfileA(HDC hdc, LPSTR filename)
{
    struct qemu_SetICMProfileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETICMPROFILEA);
    call.hdc = (uint64_t)hdc;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetICMProfileA(struct qemu_syscall *call)
{
    struct qemu_SetICMProfileA *c = (struct qemu_SetICMProfileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetICMProfileA(QEMU_G2H(c->hdc), QEMU_G2H(c->filename));
}

#endif

struct qemu_SetICMProfileW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t filename;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SetICMProfileW(HDC hdc, LPWSTR filename)
{
    struct qemu_SetICMProfileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETICMPROFILEW);
    call.hdc = (uint64_t)hdc;
    call.filename = (uint64_t)filename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetICMProfileW(struct qemu_syscall *call)
{
    struct qemu_SetICMProfileW *c = (struct qemu_SetICMProfileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetICMProfileW(QEMU_G2H(c->hdc), QEMU_G2H(c->filename));
}

#endif

struct qemu_UpdateICMRegKeyA
{
    struct qemu_syscall super;
    uint64_t reserved;
    uint64_t cmid;
    uint64_t filename;
    uint64_t command;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UpdateICMRegKeyA(DWORD reserved, LPSTR cmid, LPSTR filename, UINT command)
{
    struct qemu_UpdateICMRegKeyA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UPDATEICMREGKEYA);
    call.reserved = (uint64_t)reserved;
    call.cmid = (uint64_t)cmid;
    call.filename = (uint64_t)filename;
    call.command = (uint64_t)command;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UpdateICMRegKeyA(struct qemu_syscall *call)
{
    struct qemu_UpdateICMRegKeyA *c = (struct qemu_UpdateICMRegKeyA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UpdateICMRegKeyA(c->reserved, QEMU_G2H(c->cmid), QEMU_G2H(c->filename), c->command);
}

#endif

struct qemu_UpdateICMRegKeyW
{
    struct qemu_syscall super;
    uint64_t reserved;
    uint64_t cmid;
    uint64_t filename;
    uint64_t command;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UpdateICMRegKeyW(DWORD reserved, LPWSTR cmid, LPWSTR filename, UINT command)
{
    struct qemu_UpdateICMRegKeyW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UPDATEICMREGKEYW);
    call.reserved = (uint64_t)reserved;
    call.cmid = (uint64_t)cmid;
    call.filename = (uint64_t)filename;
    call.command = (uint64_t)command;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UpdateICMRegKeyW(struct qemu_syscall *call)
{
    struct qemu_UpdateICMRegKeyW *c = (struct qemu_UpdateICMRegKeyW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UpdateICMRegKeyW(c->reserved, QEMU_G2H(c->cmid), QEMU_G2H(c->filename), c->command);
}

#endif

