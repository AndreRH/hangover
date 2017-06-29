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


struct qemu_DeleteMetaFile
{
    struct qemu_syscall super;
    uint64_t hmf;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI DeleteMetaFile(HMETAFILE hmf)
{
    struct qemu_DeleteMetaFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DELETEMETAFILE);
    call.hmf = (uint64_t)hmf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteMetaFile(struct qemu_syscall *call)
{
    struct qemu_DeleteMetaFile *c = (struct qemu_DeleteMetaFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeleteMetaFile(QEMU_G2H(c->hmf));
}

#endif

struct qemu_GetMetaFileA
{
    struct qemu_syscall super;
    uint64_t lpFilename;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HMETAFILE WINAPI GetMetaFileA(LPCSTR lpFilename)
{
    struct qemu_GetMetaFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMETAFILEA);
    call.lpFilename = (uint64_t)lpFilename;

    qemu_syscall(&call.super);

    return (HMETAFILE)call.super.iret;
}

#else

void qemu_GetMetaFileA(struct qemu_syscall *call)
{
    struct qemu_GetMetaFileA *c = (struct qemu_GetMetaFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetMetaFileA(QEMU_G2H(c->lpFilename));
}

#endif

struct qemu_GetMetaFileW
{
    struct qemu_syscall super;
    uint64_t lpFilename;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HMETAFILE WINAPI GetMetaFileW(LPCWSTR lpFilename)
{
    struct qemu_GetMetaFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMETAFILEW);
    call.lpFilename = (uint64_t)lpFilename;

    qemu_syscall(&call.super);

    return (HMETAFILE)call.super.iret;
}

#else

void qemu_GetMetaFileW(struct qemu_syscall *call)
{
    struct qemu_GetMetaFileW *c = (struct qemu_GetMetaFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)GetMetaFileW(QEMU_G2H(c->lpFilename));
}

#endif

struct qemu_CopyMetaFileW
{
    struct qemu_syscall super;
    uint64_t hSrcMetaFile;
    uint64_t lpFilename;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HMETAFILE WINAPI CopyMetaFileW(HMETAFILE hSrcMetaFile, LPCWSTR lpFilename)
{
    struct qemu_CopyMetaFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COPYMETAFILEW);
    call.hSrcMetaFile = (uint64_t)hSrcMetaFile;
    call.lpFilename = (uint64_t)lpFilename;

    qemu_syscall(&call.super);

    return (HMETAFILE)call.super.iret;
}

#else

void qemu_CopyMetaFileW(struct qemu_syscall *call)
{
    struct qemu_CopyMetaFileW *c = (struct qemu_CopyMetaFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CopyMetaFileW(QEMU_G2H(c->hSrcMetaFile), QEMU_G2H(c->lpFilename));
}

#endif

struct qemu_CopyMetaFileA
{
    struct qemu_syscall super;
    uint64_t hSrcMetaFile;
    uint64_t lpFilename;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HMETAFILE WINAPI CopyMetaFileA(HMETAFILE hSrcMetaFile, LPCSTR lpFilename)
{
    struct qemu_CopyMetaFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_COPYMETAFILEA);
    call.hSrcMetaFile = (uint64_t)hSrcMetaFile;
    call.lpFilename = (uint64_t)lpFilename;

    qemu_syscall(&call.super);

    return (HMETAFILE)call.super.iret;
}

#else

void qemu_CopyMetaFileA(struct qemu_syscall *call)
{
    struct qemu_CopyMetaFileA *c = (struct qemu_CopyMetaFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CopyMetaFileA(QEMU_G2H(c->hSrcMetaFile), QEMU_G2H(c->lpFilename));
}

#endif

struct qemu_PlayMetaFile
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hmf;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI PlayMetaFile(HDC hdc, HMETAFILE hmf)
{
    struct qemu_PlayMetaFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PLAYMETAFILE);
    call.hdc = (uint64_t)hdc;
    call.hmf = (uint64_t)hmf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PlayMetaFile(struct qemu_syscall *call)
{
    struct qemu_PlayMetaFile *c = (struct qemu_PlayMetaFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PlayMetaFile(QEMU_G2H(c->hdc), QEMU_G2H(c->hmf));
}

#endif

struct qemu_EnumMetaFile
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t hmf;
    uint64_t lpEnumFunc;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI EnumMetaFile(HDC hdc, HMETAFILE hmf, MFENUMPROC lpEnumFunc, LPARAM lpData)
{
    struct qemu_EnumMetaFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMMETAFILE);
    call.hdc = (uint64_t)hdc;
    call.hmf = (uint64_t)hmf;
    call.lpEnumFunc = (uint64_t)lpEnumFunc;
    call.lpData = (uint64_t)lpData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumMetaFile(struct qemu_syscall *call)
{
    struct qemu_EnumMetaFile *c = (struct qemu_EnumMetaFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumMetaFile(QEMU_G2H(c->hdc), QEMU_G2H(c->hmf), QEMU_G2H(c->lpEnumFunc), c->lpData);
}

#endif

struct qemu_PlayMetaFileRecord
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t ht;
    uint64_t mr;
    uint64_t handles;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI BOOL WINAPI PlayMetaFileRecord(HDC hdc, HANDLETABLE *ht, METARECORD *mr, UINT handles)
{
    struct qemu_PlayMetaFileRecord call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PLAYMETAFILERECORD);
    call.hdc = (uint64_t)hdc;
    call.ht = (uint64_t)ht;
    call.mr = (uint64_t)mr;
    call.handles = (uint64_t)handles;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PlayMetaFileRecord(struct qemu_syscall *call)
{
    struct qemu_PlayMetaFileRecord *c = (struct qemu_PlayMetaFileRecord *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PlayMetaFileRecord(QEMU_G2H(c->hdc), QEMU_G2H(c->ht), QEMU_G2H(c->mr), c->handles);
}

#endif

struct qemu_SetMetaFileBitsEx
{
    struct qemu_syscall super;
    uint64_t size;
    uint64_t lpData;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI HMETAFILE WINAPI SetMetaFileBitsEx(UINT size, const BYTE *lpData)
{
    struct qemu_SetMetaFileBitsEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETMETAFILEBITSEX);
    call.size = (uint64_t)size;
    call.lpData = (uint64_t)lpData;

    qemu_syscall(&call.super);

    return (HMETAFILE)call.super.iret;
}

#else

void qemu_SetMetaFileBitsEx(struct qemu_syscall *call)
{
    struct qemu_SetMetaFileBitsEx *c = (struct qemu_SetMetaFileBitsEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)SetMetaFileBitsEx(c->size, QEMU_G2H(c->lpData));
}

#endif

struct qemu_GetMetaFileBitsEx
{
    struct qemu_syscall super;
    uint64_t hmf;
    uint64_t nSize;
    uint64_t buf;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI UINT WINAPI GetMetaFileBitsEx(HMETAFILE hmf, UINT nSize, LPVOID buf)
{
    struct qemu_GetMetaFileBitsEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETMETAFILEBITSEX);
    call.hmf = (uint64_t)hmf;
    call.nSize = (uint64_t)nSize;
    call.buf = (uint64_t)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMetaFileBitsEx(struct qemu_syscall *call)
{
    struct qemu_GetMetaFileBitsEx *c = (struct qemu_GetMetaFileBitsEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetMetaFileBitsEx(QEMU_G2H(c->hmf), c->nSize, QEMU_G2H(c->buf));
}

#endif

struct qemu_GetWinMetaFileBits
{
    struct qemu_syscall super;
    uint64_t hemf;
    uint64_t cbBuffer;
    uint64_t lpbBuffer;
    uint64_t map_mode;
    uint64_t hdcRef;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI UINT WINAPI GetWinMetaFileBits(HENHMETAFILE hemf, UINT cbBuffer, LPBYTE lpbBuffer, INT map_mode, HDC hdcRef)
{
    struct qemu_GetWinMetaFileBits call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETWINMETAFILEBITS);
    call.hemf = (uint64_t)hemf;
    call.cbBuffer = (uint64_t)cbBuffer;
    call.lpbBuffer = (uint64_t)lpbBuffer;
    call.map_mode = (uint64_t)map_mode;
    call.hdcRef = (uint64_t)hdcRef;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWinMetaFileBits(struct qemu_syscall *call)
{
    struct qemu_GetWinMetaFileBits *c = (struct qemu_GetWinMetaFileBits *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetWinMetaFileBits(QEMU_G2H(c->hemf), c->cbBuffer, QEMU_G2H(c->lpbBuffer), c->map_mode, QEMU_G2H(c->hdcRef));
}

#endif

