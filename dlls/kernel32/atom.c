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
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_InitAtomTable
{
    struct qemu_syscall super;
    uint64_t entries;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InitAtomTable(DWORD entries)
{
    struct qemu_InitAtomTable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INITATOMTABLE);
    call.entries = (uint64_t)entries;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InitAtomTable(struct qemu_syscall *call)
{
    struct qemu_InitAtomTable *c = (struct qemu_InitAtomTable *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InitAtomTable(c->entries);
}

#endif

struct qemu_GlobalAddAtomA
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ATOM WINAPI GlobalAddAtomA(LPCSTR str)
{
    struct qemu_GlobalAddAtomA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALADDATOMA);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GlobalAddAtomA(struct qemu_syscall *call)
{
    struct qemu_GlobalAddAtomA *c = (struct qemu_GlobalAddAtomA *)call;
    WINE_TRACE("\n");
    c->super.iret = GlobalAddAtomA(QEMU_G2H(c->str));
}

#endif

struct qemu_AddAtomA
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ATOM WINAPI AddAtomA(LPCSTR str)
{
    struct qemu_AddAtomA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDATOMA);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddAtomA(struct qemu_syscall *call)
{
    struct qemu_AddAtomA *c = (struct qemu_AddAtomA *)call;
    WINE_TRACE("\n");
    c->super.iret = AddAtomA(QEMU_G2H(c->str));
}

#endif

struct qemu_GlobalAddAtomW
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ATOM WINAPI GlobalAddAtomW(LPCWSTR str)
{
    struct qemu_GlobalAddAtomW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALADDATOMW);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GlobalAddAtomW(struct qemu_syscall *call)
{
    struct qemu_GlobalAddAtomW *c = (struct qemu_GlobalAddAtomW *)call;
    WINE_TRACE("\n");
    c->super.iret = GlobalAddAtomW(QEMU_G2H(c->str));
}

#endif

struct qemu_AddAtomW
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ATOM WINAPI AddAtomW(LPCWSTR str)
{
    struct qemu_AddAtomW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDATOMW);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AddAtomW(struct qemu_syscall *call)
{
    struct qemu_AddAtomW *c = (struct qemu_AddAtomW *)call;
    WINE_TRACE("\n");
    c->super.iret = AddAtomW(QEMU_G2H(c->str));
}

#endif

struct qemu_GlobalDeleteAtom
{
    struct qemu_syscall super;
    uint64_t atom;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ATOM WINAPI GlobalDeleteAtom(ATOM atom)
{
    struct qemu_GlobalDeleteAtom call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALDELETEATOM);
    call.atom = (uint64_t)atom;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GlobalDeleteAtom(struct qemu_syscall *call)
{
    struct qemu_GlobalDeleteAtom *c = (struct qemu_GlobalDeleteAtom *)call;
    WINE_TRACE("\n");
    c->super.iret = GlobalDeleteAtom(c->atom);
}

#endif

struct qemu_DeleteAtom
{
    struct qemu_syscall super;
    uint64_t atom;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ATOM WINAPI DeleteAtom(ATOM atom)
{
    struct qemu_DeleteAtom call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEATOM);
    call.atom = (uint64_t)atom;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteAtom(struct qemu_syscall *call)
{
    struct qemu_DeleteAtom *c = (struct qemu_DeleteAtom *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteAtom(c->atom);
}

#endif

struct qemu_GlobalFindAtomA
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ATOM WINAPI GlobalFindAtomA(LPCSTR str)
{
    struct qemu_GlobalFindAtomA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALFINDATOMA);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GlobalFindAtomA(struct qemu_syscall *call)
{
    struct qemu_GlobalFindAtomA *c = (struct qemu_GlobalFindAtomA *)call;
    WINE_TRACE("\n");
    c->super.iret = GlobalFindAtomA(QEMU_G2H(c->str));
}

#endif

struct qemu_FindAtomA
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ATOM WINAPI FindAtomA(LPCSTR str)
{
    struct qemu_FindAtomA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDATOMA);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindAtomA(struct qemu_syscall *call)
{
    struct qemu_FindAtomA *c = (struct qemu_FindAtomA *)call;
    WINE_TRACE("\n");
    c->super.iret = FindAtomA(QEMU_G2H(c->str));
}

#endif

struct qemu_GlobalFindAtomW
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ATOM WINAPI GlobalFindAtomW(LPCWSTR str)
{
    struct qemu_GlobalFindAtomW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALFINDATOMW);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GlobalFindAtomW(struct qemu_syscall *call)
{
    struct qemu_GlobalFindAtomW *c = (struct qemu_GlobalFindAtomW *)call;
    WINE_TRACE("\n");
    c->super.iret = GlobalFindAtomW(QEMU_G2H(c->str));
}

#endif

struct qemu_FindAtomW
{
    struct qemu_syscall super;
    uint64_t str;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ATOM WINAPI FindAtomW(LPCWSTR str)
{
    struct qemu_FindAtomW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDATOMW);
    call.str = (ULONG_PTR)str;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindAtomW(struct qemu_syscall *call)
{
    struct qemu_FindAtomW *c = (struct qemu_FindAtomW *)call;
    WINE_TRACE("\n");
    c->super.iret = FindAtomW(QEMU_G2H(c->str));
}

#endif

struct qemu_GlobalGetAtomNameA
{
    struct qemu_syscall super;
    uint64_t atom;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GlobalGetAtomNameA(ATOM atom, LPSTR buffer, INT count)
{
    struct qemu_GlobalGetAtomNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALGETATOMNAMEA);
    call.atom = atom;
    call.buffer = (ULONG_PTR)buffer;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GlobalGetAtomNameA(struct qemu_syscall *call)
{
    struct qemu_GlobalGetAtomNameA *c = (struct qemu_GlobalGetAtomNameA *)call;
    WINE_TRACE("\n");
    c->super.iret = GlobalGetAtomNameA(c->atom, QEMU_G2H(c->buffer), c->count);
}

#endif

struct qemu_GetAtomNameA
{
    struct qemu_syscall super;
    uint64_t atom;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetAtomNameA(ATOM atom, LPSTR buffer, INT count)
{
    struct qemu_GetAtomNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETATOMNAMEA);
    call.atom = atom;
    call.buffer = (ULONG_PTR)buffer;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAtomNameA(struct qemu_syscall *call)
{
    struct qemu_GetAtomNameA *c = (struct qemu_GetAtomNameA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetAtomNameA(c->atom, QEMU_G2H(c->buffer), c->count);
}

#endif

struct qemu_GlobalGetAtomNameW
{
    struct qemu_syscall super;
    uint64_t atom;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GlobalGetAtomNameW(ATOM atom, LPWSTR buffer, INT count)
{
    struct qemu_GlobalGetAtomNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GLOBALGETATOMNAMEW);
    call.atom = atom;
    call.buffer = (ULONG_PTR)buffer;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GlobalGetAtomNameW(struct qemu_syscall *call)
{
    struct qemu_GlobalGetAtomNameW *c = (struct qemu_GlobalGetAtomNameW *)call;
    WINE_TRACE("\n");
    c->super.iret = GlobalGetAtomNameW(c->atom, QEMU_G2H(c->buffer), c->count);
}

#endif

struct qemu_GetAtomNameW
{
    struct qemu_syscall super;
    uint64_t atom;
    uint64_t buffer;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI GetAtomNameW(ATOM atom, LPWSTR buffer, INT count)
{
    struct qemu_GetAtomNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETATOMNAMEW);
    call.atom = atom;
    call.buffer = (ULONG_PTR)buffer;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAtomNameW(struct qemu_syscall *call)
{
    struct qemu_GetAtomNameW *c = (struct qemu_GetAtomNameW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetAtomNameW(c->atom, QEMU_G2H(c->buffer), c->count);
}

#endif

