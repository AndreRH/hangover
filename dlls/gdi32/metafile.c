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
#include <usp10.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_gdi32.h"

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
    call.hmf = (ULONG_PTR)hmf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeleteMetaFile(struct qemu_syscall *call)
{
    struct qemu_DeleteMetaFile *c = (struct qemu_DeleteMetaFile *)call;
    WINE_TRACE("\n");
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
    call.lpFilename = (ULONG_PTR)lpFilename;

    qemu_syscall(&call.super);

    return (HMETAFILE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetMetaFileA(struct qemu_syscall *call)
{
    struct qemu_GetMetaFileA *c = (struct qemu_GetMetaFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)GetMetaFileA(QEMU_G2H(c->lpFilename));
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
    call.lpFilename = (ULONG_PTR)lpFilename;

    qemu_syscall(&call.super);

    return (HMETAFILE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GetMetaFileW(struct qemu_syscall *call)
{
    struct qemu_GetMetaFileW *c = (struct qemu_GetMetaFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)GetMetaFileW(QEMU_G2H(c->lpFilename));
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
    call.hSrcMetaFile = (ULONG_PTR)hSrcMetaFile;
    call.lpFilename = (ULONG_PTR)lpFilename;

    qemu_syscall(&call.super);

    return (HMETAFILE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CopyMetaFileW(struct qemu_syscall *call)
{
    struct qemu_CopyMetaFileW *c = (struct qemu_CopyMetaFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CopyMetaFileW(QEMU_G2H(c->hSrcMetaFile), QEMU_G2H(c->lpFilename));
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
    call.hSrcMetaFile = (ULONG_PTR)hSrcMetaFile;
    call.lpFilename = (ULONG_PTR)lpFilename;

    qemu_syscall(&call.super);

    return (HMETAFILE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CopyMetaFileA(struct qemu_syscall *call)
{
    struct qemu_CopyMetaFileA *c = (struct qemu_CopyMetaFileA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)CopyMetaFileA(QEMU_G2H(c->hSrcMetaFile), QEMU_G2H(c->lpFilename));
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
    call.hdc = (ULONG_PTR)hdc;
    call.hmf = (ULONG_PTR)hmf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PlayMetaFile(struct qemu_syscall *call)
{
    struct qemu_PlayMetaFile *c = (struct qemu_PlayMetaFile *)call;
    WINE_TRACE("\n");

    /* There are GDI commands that set callbacks. Once upon a time there was a
     * security issue caused by executing callback bytecode from a metafile. I
     * assume if such a file is run crashing is the correct course of action. */

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
    uint64_t wrapper;
};

struct qemu_EnumMetaFile_cb
{
    uint64_t proc;
    uint64_t dc;
    uint64_t handle_table;
    uint64_t emr;
    uint64_t n_objs;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall EnumMetaFile_guest_cb(struct qemu_EnumMetaFile_cb *data)
{
    MFENUMPROC proc = (MFENUMPROC)(ULONG_PTR)data->proc;
    return proc((HDC)(ULONG_PTR)data->dc, (HANDLETABLE *)(ULONG_PTR)data->handle_table, (METARECORD *)(ULONG_PTR)data->emr, data->n_objs, data->param);
}

WINGDIAPI BOOL WINAPI EnumMetaFile(HDC hdc, HMETAFILE hmf, MFENUMPROC lpEnumFunc, LPARAM lpData)
{
    struct qemu_EnumMetaFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMMETAFILE);
    call.hdc = (ULONG_PTR)hdc;
    call.hmf = (ULONG_PTR)hmf;
    call.lpEnumFunc = (ULONG_PTR)lpEnumFunc;
    call.lpData = (ULONG_PTR)lpData;
    call.wrapper = (ULONG_PTR)EnumMetaFile_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct qemu_EnumMetaFile_host_data
{
    uint64_t wrapper, guest_func;
    uint64_t guest_data;
};

static int CALLBACK qemu_EnumEnhMetaFile_host_cb(HDC hdc, HANDLETABLE *handle_table,
        METARECORD *emr, int n_objs, LPARAM param)
{
    struct qemu_EnumMetaFile_host_data *data = (struct qemu_EnumMetaFile_host_data *)param;
    struct qemu_EnumMetaFile_cb call;
    int ret;

    WINE_TRACE("Calling guest callback 0x%lx(%p, %p, %p, %d, 0x%lx).\n", (unsigned long)data->guest_func,
            hdc, handle_table, emr, n_objs, (unsigned long)data->guest_data);
    call.proc = data->guest_func;
    call.dc = (ULONG_PTR)hdc;
    call.handle_table = QEMU_H2G(handle_table);
    call.emr = QEMU_H2G(emr);
    call.n_objs = n_objs;
    call.param = data->guest_data;

    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&call));

    WINE_TRACE("Callback returned %d.\n", ret);
    return ret;
}

void qemu_EnumMetaFile(struct qemu_syscall *call)
{
    struct qemu_EnumMetaFile *c = (struct qemu_EnumMetaFile *)call;
    struct qemu_EnumMetaFile_host_data data;

    WINE_TRACE("\n");
    data.wrapper = c->wrapper;
    data.guest_func = c->lpEnumFunc;
    data.guest_data = c->lpData;
    c->super.iret = EnumMetaFile((HDC)c->hdc, QEMU_G2H(c->hmf),
            c->lpEnumFunc ? qemu_EnumEnhMetaFile_host_cb : NULL, (LPARAM)&data);
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
    call.hdc = (ULONG_PTR)hdc;
    call.ht = (ULONG_PTR)ht;
    call.mr = (ULONG_PTR)mr;
    call.handles = (ULONG_PTR)handles;

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
    call.size = (ULONG_PTR)size;
    call.lpData = (ULONG_PTR)lpData;

    qemu_syscall(&call.super);

    return (HMETAFILE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SetMetaFileBitsEx(struct qemu_syscall *call)
{
    struct qemu_SetMetaFileBitsEx *c = (struct qemu_SetMetaFileBitsEx *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)SetMetaFileBitsEx(c->size, QEMU_G2H(c->lpData));
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
    call.hmf = (ULONG_PTR)hmf;
    call.nSize = (ULONG_PTR)nSize;
    call.buf = (ULONG_PTR)buf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetMetaFileBitsEx(struct qemu_syscall *call)
{
    struct qemu_GetMetaFileBitsEx *c = (struct qemu_GetMetaFileBitsEx *)call;
    WINE_TRACE("\n");
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
    call.hemf = (ULONG_PTR)hemf;
    call.cbBuffer = (ULONG_PTR)cbBuffer;
    call.lpbBuffer = (ULONG_PTR)lpbBuffer;
    call.map_mode = (ULONG_PTR)map_mode;
    call.hdcRef = (ULONG_PTR)hdcRef;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetWinMetaFileBits(struct qemu_syscall *call)
{
    struct qemu_GetWinMetaFileBits *c = (struct qemu_GetWinMetaFileBits *)call;
    WINE_TRACE("\n");
    c->super.iret = GetWinMetaFileBits(QEMU_G2H(c->hemf), c->cbBuffer, QEMU_G2H(c->lpbBuffer), c->map_mode, QEMU_G2H(c->hdcRef));
}

#endif

