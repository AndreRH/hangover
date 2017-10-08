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


struct qemu_LZStart
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI LZStart(void)
{
    struct qemu_LZStart call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LZSTART);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LZStart(struct qemu_syscall *call)
{
    struct qemu_LZStart *c = (struct qemu_LZStart *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LZStart();
}

#endif

struct qemu_LZInit
{
    struct qemu_syscall super;
    uint64_t hfSrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HFILE WINAPI LZInit(HFILE hfSrc)
{
    struct qemu_LZInit call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LZINIT);
    call.hfSrc = hfSrc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LZInit(struct qemu_syscall *call)
{
    struct qemu_LZInit *c = (struct qemu_LZInit *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LZInit(c->hfSrc);
}

#endif

struct qemu_LZDone
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI LZDone(void)
{
    struct qemu_LZDone call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LZDONE);

    qemu_syscall(&call.super);
}

#else

void qemu_LZDone(struct qemu_syscall *call)
{
    struct qemu_LZDone *c = (struct qemu_LZDone *)call;
    WINE_FIXME("Unverified!\n");
    LZDone();
}

#endif

struct qemu_GetExpandedNameA
{
    struct qemu_syscall super;
    uint64_t in;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetExpandedNameA(LPSTR in, LPSTR out)
{
    struct qemu_GetExpandedNameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETEXPANDEDNAMEA);
    call.in = (ULONG_PTR)in;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetExpandedNameA(struct qemu_syscall *call)
{
    struct qemu_GetExpandedNameA *c = (struct qemu_GetExpandedNameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetExpandedNameA(QEMU_G2H(c->in), QEMU_G2H(c->out));
}

#endif

struct qemu_GetExpandedNameW
{
    struct qemu_syscall super;
    uint64_t in;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI GetExpandedNameW(LPWSTR in, LPWSTR out)
{
    struct qemu_GetExpandedNameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETEXPANDEDNAMEW);
    call.in = (ULONG_PTR)in;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetExpandedNameW(struct qemu_syscall *call)
{
    struct qemu_GetExpandedNameW *c = (struct qemu_GetExpandedNameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetExpandedNameW(QEMU_G2H(c->in), QEMU_G2H(c->out));
}

#endif

struct qemu_LZRead
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t vbuf;
    uint64_t toread;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI LZRead(HFILE fd, LPSTR vbuf, INT toread)
{
    struct qemu_LZRead call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LZREAD);
    call.fd = fd;
    call.vbuf = (ULONG_PTR)vbuf;
    call.toread = toread;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LZRead(struct qemu_syscall *call)
{
    struct qemu_LZRead *c = (struct qemu_LZRead *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LZRead(c->fd, QEMU_G2H(c->vbuf), c->toread);
}

#endif

struct qemu_LZSeek
{
    struct qemu_syscall super;
    uint64_t fd;
    uint64_t off;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI LZSeek(HFILE fd, LONG off, INT type)
{
    struct qemu_LZSeek call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LZSEEK);
    call.fd = fd;
    call.off = off;
    call.type = type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LZSeek(struct qemu_syscall *call)
{
    struct qemu_LZSeek *c = (struct qemu_LZSeek *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LZSeek(c->fd, c->off, c->type);
}

#endif

struct qemu_LZCopy
{
    struct qemu_syscall super;
    uint64_t src;
    uint64_t dest;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI LZCopy(HFILE src, HFILE dest)
{
    struct qemu_LZCopy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LZCOPY);
    call.src = src;
    call.dest = dest;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LZCopy(struct qemu_syscall *call)
{
    struct qemu_LZCopy *c = (struct qemu_LZCopy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LZCopy(c->src, c->dest);
}

#endif

struct qemu_LZOpenFileA
{
    struct qemu_syscall super;
    uint64_t fn;
    uint64_t ofs;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HFILE WINAPI LZOpenFileA(LPSTR fn, LPOFSTRUCT ofs, WORD mode)
{
    struct qemu_LZOpenFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LZOPENFILEA);
    call.fn = (ULONG_PTR)fn;
    call.ofs = (ULONG_PTR)ofs;
    call.mode = mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LZOpenFileA(struct qemu_syscall *call)
{
    struct qemu_LZOpenFileA *c = (struct qemu_LZOpenFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LZOpenFileA(QEMU_G2H(c->fn), QEMU_G2H(c->ofs), c->mode);
}

#endif

struct qemu_LZOpenFileW
{
    struct qemu_syscall super;
    uint64_t fn;
    uint64_t ofs;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HFILE WINAPI LZOpenFileW(LPWSTR fn, LPOFSTRUCT ofs, WORD mode)
{
    struct qemu_LZOpenFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LZOPENFILEW);
    call.fn = (ULONG_PTR)fn;
    call.ofs = (ULONG_PTR)ofs;
    call.mode = mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LZOpenFileW(struct qemu_syscall *call)
{
    struct qemu_LZOpenFileW *c = (struct qemu_LZOpenFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LZOpenFileW(QEMU_G2H(c->fn), QEMU_G2H(c->ofs), c->mode);
}

#endif

struct qemu_LZClose
{
    struct qemu_syscall super;
    uint64_t fd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI LZClose(HFILE fd)
{
    struct qemu_LZClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LZCLOSE);
    call.fd = fd;

    qemu_syscall(&call.super);
}

#else

void qemu_LZClose(struct qemu_syscall *call)
{
    struct qemu_LZClose *c = (struct qemu_LZClose *)call;
    WINE_FIXME("Unverified!\n");
    LZClose(c->fd);
}

#endif

