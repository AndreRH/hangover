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

#include "windows-user-services.h"
#include "dll_list.h"
#include "shlwapi.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shlwapi);
#endif


struct qemu_SHCreateStreamOnFileEx
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t dwMode;
    uint64_t dwAttributes;
    uint64_t bCreate;
    uint64_t lpTemplate;
    uint64_t lppStream;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateStreamOnFileEx(LPCWSTR lpszPath, DWORD dwMode, DWORD dwAttributes, BOOL bCreate, IStream *lpTemplate, IStream **lppStream)
{
    struct qemu_SHCreateStreamOnFileEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESTREAMONFILEEX);
    call.lpszPath = (uint64_t)lpszPath;
    call.dwMode = (uint64_t)dwMode;
    call.dwAttributes = (uint64_t)dwAttributes;
    call.bCreate = (uint64_t)bCreate;
    call.lpTemplate = (uint64_t)lpTemplate;
    call.lppStream = (uint64_t)lppStream;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateStreamOnFileEx(struct qemu_syscall *call)
{
    struct qemu_SHCreateStreamOnFileEx *c = (struct qemu_SHCreateStreamOnFileEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateStreamOnFileEx(QEMU_G2H(c->lpszPath), c->dwMode, c->dwAttributes, c->bCreate, QEMU_G2H(c->lpTemplate), QEMU_G2H(c->lppStream));
}

#endif

struct qemu_SHCreateStreamOnFileW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t dwMode;
    uint64_t lppStream;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateStreamOnFileW(LPCWSTR lpszPath, DWORD dwMode, IStream **lppStream)
{
    struct qemu_SHCreateStreamOnFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESTREAMONFILEW);
    call.lpszPath = (uint64_t)lpszPath;
    call.dwMode = (uint64_t)dwMode;
    call.lppStream = (uint64_t)lppStream;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateStreamOnFileW(struct qemu_syscall *call)
{
    struct qemu_SHCreateStreamOnFileW *c = (struct qemu_SHCreateStreamOnFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateStreamOnFileW(QEMU_G2H(c->lpszPath), c->dwMode, QEMU_G2H(c->lppStream));
}

#endif

struct qemu_SHCreateStreamOnFileA
{
    struct qemu_syscall super;
    uint64_t lpszPath;
    uint64_t dwMode;
    uint64_t lppStream;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateStreamOnFileA(LPCSTR lpszPath, DWORD dwMode, IStream **lppStream)
{
    struct qemu_SHCreateStreamOnFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESTREAMONFILEA);
    call.lpszPath = (uint64_t)lpszPath;
    call.dwMode = (uint64_t)dwMode;
    call.lppStream = (uint64_t)lppStream;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateStreamOnFileA(struct qemu_syscall *call)
{
    struct qemu_SHCreateStreamOnFileA *c = (struct qemu_SHCreateStreamOnFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateStreamOnFileA(QEMU_G2H(c->lpszPath), c->dwMode, QEMU_G2H(c->lppStream));
}

#endif

struct qemu_SHIStream_Read
{
    struct qemu_syscall super;
    uint64_t lpStream;
    uint64_t lpvDest;
    uint64_t ulSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHIStream_Read(IStream *lpStream, LPVOID lpvDest, ULONG ulSize)
{
    struct qemu_SHIStream_Read call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHISTREAM_READ);
    call.lpStream = (uint64_t)lpStream;
    call.lpvDest = (uint64_t)lpvDest;
    call.ulSize = (uint64_t)ulSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHIStream_Read(struct qemu_syscall *call)
{
    struct qemu_SHIStream_Read *c = (struct qemu_SHIStream_Read *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = E_FAIL;
}

#endif

struct qemu_SHIsEmptyStream
{
    struct qemu_syscall super;
    uint64_t lpStream;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHIsEmptyStream(IStream *lpStream)
{
    struct qemu_SHIsEmptyStream call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHISEMPTYSTREAM);
    call.lpStream = (uint64_t)lpStream;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHIsEmptyStream to Wine headers? */
extern BOOL WINAPI SHIsEmptyStream(IStream *lpStream);
void qemu_SHIsEmptyStream(struct qemu_syscall *call)
{
    struct qemu_SHIsEmptyStream *c = (struct qemu_SHIsEmptyStream *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHIsEmptyStream(QEMU_G2H(c->lpStream));
}

#endif

struct qemu_SHIStream_Write
{
    struct qemu_syscall super;
    uint64_t lpStream;
    uint64_t lpvSrc;
    uint64_t ulSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHIStream_Write(IStream *lpStream, LPCVOID lpvSrc, ULONG ulSize)
{
    struct qemu_SHIStream_Write call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHISTREAM_WRITE);
    call.lpStream = (uint64_t)lpStream;
    call.lpvSrc = (uint64_t)lpvSrc;
    call.ulSize = (uint64_t)ulSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHIStream_Write(struct qemu_syscall *call)
{
    struct qemu_SHIStream_Write *c = (struct qemu_SHIStream_Write *)call;
    WINE_FIXME("Stub!\n");
    c->super.iret = E_FAIL;
}

#endif

struct qemu_IStream_Reset
{
    struct qemu_syscall super;
    uint64_t lpStream;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI IStream_Reset(IStream *lpStream)
{
    struct qemu_IStream_Reset call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISTREAM_RESET);
    call.lpStream = (uint64_t)lpStream;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IStream_Reset(struct qemu_syscall *call)
{
    struct qemu_IStream_Reset *c = (struct qemu_IStream_Reset *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IStream_Reset(QEMU_G2H(c->lpStream));
}

#endif

struct qemu_IStream_Size
{
    struct qemu_syscall super;
    uint64_t lpStream;
    uint64_t lpulSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI IStream_Size(IStream *lpStream, ULARGE_INTEGER* lpulSize)
{
    struct qemu_IStream_Size call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ISTREAM_SIZE);
    call.lpStream = (uint64_t)lpStream;
    call.lpulSize = (uint64_t)lpulSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IStream_Size(struct qemu_syscall *call)
{
    struct qemu_IStream_Size *c = (struct qemu_IStream_Size *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IStream_Size(QEMU_G2H(c->lpStream), QEMU_G2H(c->lpulSize));
}

#endif

