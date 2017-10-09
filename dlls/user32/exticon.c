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
#include "qemu_user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);
#endif


struct qemu_PrivateExtractIconsW
{
    struct qemu_syscall super;
    uint64_t lpwstrFile;
    uint64_t nIndex;
    uint64_t sizeX;
    uint64_t sizeY;
    uint64_t phicon;
    uint64_t pIconId;
    uint64_t nIcons;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI PrivateExtractIconsW (LPCWSTR lpwstrFile, int nIndex, int sizeX, int sizeY, HICON * phicon, UINT* pIconId, UINT nIcons, UINT flags)
{
    struct qemu_PrivateExtractIconsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRIVATEEXTRACTICONSW);
    call.lpwstrFile = (ULONG_PTR)lpwstrFile;
    call.nIndex = (ULONG_PTR)nIndex;
    call.sizeX = (ULONG_PTR)sizeX;
    call.sizeY = (ULONG_PTR)sizeY;
    call.phicon = (ULONG_PTR)phicon;
    call.pIconId = (ULONG_PTR)pIconId;
    call.nIcons = (ULONG_PTR)nIcons;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrivateExtractIconsW(struct qemu_syscall *call)
{
    struct qemu_PrivateExtractIconsW *c = (struct qemu_PrivateExtractIconsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrivateExtractIconsW(QEMU_G2H(c->lpwstrFile), c->nIndex, c->sizeX, c->sizeY, QEMU_G2H(c->phicon), QEMU_G2H(c->pIconId), c->nIcons, c->flags);
}

#endif

struct qemu_PrivateExtractIconsA
{
    struct qemu_syscall super;
    uint64_t lpstrFile;
    uint64_t nIndex;
    uint64_t sizeX;
    uint64_t sizeY;
    uint64_t phicon;
    uint64_t piconid;
    uint64_t nIcons;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI PrivateExtractIconsA (LPCSTR lpstrFile, int nIndex, int sizeX, int sizeY, HICON * phicon, UINT* piconid, UINT nIcons, UINT flags)
{
    struct qemu_PrivateExtractIconsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRIVATEEXTRACTICONSA);
    call.lpstrFile = (ULONG_PTR)lpstrFile;
    call.nIndex = (ULONG_PTR)nIndex;
    call.sizeX = (ULONG_PTR)sizeX;
    call.sizeY = (ULONG_PTR)sizeY;
    call.phicon = (ULONG_PTR)phicon;
    call.piconid = (ULONG_PTR)piconid;
    call.nIcons = (ULONG_PTR)nIcons;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrivateExtractIconsA(struct qemu_syscall *call)
{
    struct qemu_PrivateExtractIconsA *c = (struct qemu_PrivateExtractIconsA *)call;
    WINE_TRACE("\n");
    c->super.iret = PrivateExtractIconsA(QEMU_G2H(c->lpstrFile), c->nIndex, c->sizeX, c->sizeY, QEMU_G2H(c->phicon), QEMU_G2H(c->piconid), c->nIcons, c->flags);
}

#endif

struct qemu_PrivateExtractIconExW
{
    struct qemu_syscall super;
    uint64_t lpwstrFile;
    uint64_t nIndex;
    uint64_t phIconLarge;
    uint64_t phIconSmall;
    uint64_t nIcons;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI PrivateExtractIconExW (LPCWSTR lpwstrFile, int nIndex, HICON * phIconLarge, HICON * phIconSmall, UINT nIcons)
{
    struct qemu_PrivateExtractIconExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRIVATEEXTRACTICONEXW);
    call.lpwstrFile = (ULONG_PTR)lpwstrFile;
    call.nIndex = (ULONG_PTR)nIndex;
    call.phIconLarge = (ULONG_PTR)phIconLarge;
    call.phIconSmall = (ULONG_PTR)phIconSmall;
    call.nIcons = (ULONG_PTR)nIcons;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrivateExtractIconExW(struct qemu_syscall *call)
{
    struct qemu_PrivateExtractIconExW *c = (struct qemu_PrivateExtractIconExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrivateExtractIconExW(QEMU_G2H(c->lpwstrFile), c->nIndex, QEMU_G2H(c->phIconLarge), QEMU_G2H(c->phIconSmall), c->nIcons);
}

#endif

struct qemu_PrivateExtractIconExA
{
    struct qemu_syscall super;
    uint64_t lpstrFile;
    uint64_t nIndex;
    uint64_t phIconLarge;
    uint64_t phIconSmall;
    uint64_t nIcons;
};

#ifdef QEMU_DLL_GUEST

WINUSERAPI UINT WINAPI PrivateExtractIconExA (LPCSTR lpstrFile, int nIndex, HICON * phIconLarge, HICON * phIconSmall, UINT nIcons)
{
    struct qemu_PrivateExtractIconExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PRIVATEEXTRACTICONEXA);
    call.lpstrFile = (ULONG_PTR)lpstrFile;
    call.nIndex = (ULONG_PTR)nIndex;
    call.phIconLarge = (ULONG_PTR)phIconLarge;
    call.phIconSmall = (ULONG_PTR)phIconSmall;
    call.nIcons = (ULONG_PTR)nIcons;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PrivateExtractIconExA(struct qemu_syscall *call)
{
    struct qemu_PrivateExtractIconExA *c = (struct qemu_PrivateExtractIconExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PrivateExtractIconExA(QEMU_G2H(c->lpstrFile), c->nIndex, QEMU_G2H(c->phIconLarge), QEMU_G2H(c->phIconSmall), c->nIcons);
}

#endif

