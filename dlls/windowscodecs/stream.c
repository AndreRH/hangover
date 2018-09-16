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

#define COBJMACROS

#include <windows.h>
#include <wincodec.h>
#include <wincodecsdk.h>

#include "windows-user-services.h"
#include "dll_list.h"

#include <wine/debug.h>
#include <wine/list.h>

#include "qemu_windowscodecs.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_wic);

struct qemu_WICStream_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_stream *impl_from_IWICStream(IWICStream *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_stream, IWICStream_iface);
}

static HRESULT WINAPI WICStream_QueryInterface(IWICStream *iface, REFIID iid, void **ppv)
{
    struct qemu_WICStream_QueryInterface call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_QUERYINTERFACE);
    call.iface = (ULONG_PTR)stream;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICStream_QueryInterface *c = (struct qemu_WICStream_QueryInterface *)call;
    struct qemu_wic_stream *stream;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);

    c->super.iret = IWICStream_QueryInterface(stream->host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_WICStream_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICStream_AddRef(IWICStream *iface)
{
    struct qemu_WICStream_AddRef call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_ADDREF);
    call.iface = (ULONG_PTR)stream;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICStream_AddRef *c = (struct qemu_WICStream_AddRef *)call;
    struct qemu_wic_stream *stream;

    WINE_TRACE("\n");
    stream = QEMU_G2H(c->iface);

    c->super.iret = IWICStream_AddRef(stream->host);
}

#endif

struct qemu_WICStream_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICStream_Release(IWICStream *iface)
{
    struct qemu_WICStream_Release call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_RELEASE);
    call.iface = (ULONG_PTR)stream;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_Release(struct qemu_syscall *call)
{
    struct qemu_WICStream_Release *c = (struct qemu_WICStream_Release *)call;
    struct qemu_wic_stream *stream;

    WINE_TRACE("\n");
    stream = QEMU_G2H(c->iface);

    c->super.iret = IWICStream_Release(stream->host);
    if (!c->super.iret)
    {
        WINE_TRACE("Destroying WIC stream wrapper %p for host stream %p.\n", stream, stream->host);
        HeapFree(GetProcessHeap(), 0, stream);
    }
}

#endif

struct qemu_WICStream_Read
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pv;
    uint64_t cb;
    uint64_t pcbRead;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_Read(IWICStream *iface, void *pv, ULONG cb, ULONG *pcbRead)
{
    struct qemu_WICStream_Read call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_READ);
    call.iface = (ULONG_PTR)stream;
    call.pv = (ULONG_PTR)pv;
    call.cb = cb;
    call.pcbRead = (ULONG_PTR)pcbRead;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_Read(struct qemu_syscall *call)
{
    struct qemu_WICStream_Read *c = (struct qemu_WICStream_Read *)call;
    struct qemu_wic_stream *stream;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);

    c->super.iret = IWICStream_Read(stream->host, QEMU_G2H(c->pv), c->cb, QEMU_G2H(c->pcbRead));
}

#endif

struct qemu_WICStream_Write
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pv;
    uint64_t cb;
    uint64_t pcbWritten;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_Write(IWICStream *iface, void const *pv, ULONG cb, ULONG *pcbWritten)
{
    struct qemu_WICStream_Write call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_WRITE);
    call.iface = (ULONG_PTR)stream;
    call.pv = (ULONG_PTR)pv;
    call.cb = cb;
    call.pcbWritten = (ULONG_PTR)pcbWritten;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_Write(struct qemu_syscall *call)
{
    struct qemu_WICStream_Write *c = (struct qemu_WICStream_Write *)call;
    struct qemu_wic_stream *stream;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);

    c->super.iret = IWICStream_Write(stream->host, QEMU_G2H(c->pv), c->cb, QEMU_G2H(c->pcbWritten));
}

#endif

struct qemu_WICStream_Seek
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dlibMove;
    uint64_t dwOrigin;
    uint64_t plibNewPosition;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_Seek(IWICStream *iface, LARGE_INTEGER dlibMove, DWORD dwOrigin,
        ULARGE_INTEGER *plibNewPosition)
{
    struct qemu_WICStream_Seek call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_SEEK);
    call.iface = (ULONG_PTR)stream;
    call.dlibMove = dlibMove.QuadPart;
    call.dwOrigin = dwOrigin;
    call.plibNewPosition = (ULONG_PTR)plibNewPosition;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_Seek(struct qemu_syscall *call)
{
    struct qemu_WICStream_Seek *c = (struct qemu_WICStream_Seek *)call;
    struct qemu_wic_stream *stream;
    LARGE_INTEGER dlibMove;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);
    dlibMove.QuadPart = c->dlibMove;

    c->super.iret = IWICStream_Seek(stream->host, dlibMove, c->dwOrigin, QEMU_G2H(c->plibNewPosition));
}

#endif

struct qemu_WICStream_SetSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t libNewSize;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_SetSize(IWICStream *iface, ULARGE_INTEGER libNewSize)
{
    struct qemu_WICStream_SetSize call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_SETSIZE);
    call.iface = (ULONG_PTR)stream;
    call.libNewSize = libNewSize.QuadPart;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_SetSize(struct qemu_syscall *call)
{
    struct qemu_WICStream_SetSize *c = (struct qemu_WICStream_SetSize *)call;
    struct qemu_wic_stream *stream;
    ULARGE_INTEGER libNewSize;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);
    libNewSize.QuadPart = c->libNewSize;

    c->super.iret = IWICStream_SetSize(stream->host, libNewSize);
}

#endif

struct qemu_WICStream_CopyTo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pstm;
    uint64_t cb;
    uint64_t pcbRead;
    uint64_t pcbWritten;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_CopyTo(IWICStream *iface, IStream *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead,
        ULARGE_INTEGER *pcbWritten)
{
    struct qemu_WICStream_CopyTo call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_COPYTO);
    call.iface = (ULONG_PTR)stream;
    call.pstm = (ULONG_PTR)pstm;
    call.cb = cb.QuadPart;
    call.pcbRead = (ULONG_PTR)pcbRead;
    call.pcbWritten = (ULONG_PTR)pcbWritten;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_CopyTo(struct qemu_syscall *call)
{
    struct qemu_WICStream_CopyTo *c = (struct qemu_WICStream_CopyTo *)call;
    struct qemu_wic_stream *stream;
    ULARGE_INTEGER cb;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);
    cb.QuadPart = c->cb;

    c->super.iret = IWICStream_CopyTo(stream->host, QEMU_G2H(c->pstm), cb, QEMU_G2H(c->pcbRead),
            QEMU_G2H(c->pcbWritten));
}

#endif

struct qemu_WICStream_Commit
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t grfCommitFlags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_Commit(IWICStream *iface, DWORD grfCommitFlags)
{
    struct qemu_WICStream_Commit call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_COMMIT);
    call.iface = (ULONG_PTR)stream;
    call.grfCommitFlags = grfCommitFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_Commit(struct qemu_syscall *call)
{
    struct qemu_WICStream_Commit *c = (struct qemu_WICStream_Commit *)call;
    struct qemu_wic_stream *stream;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);

    c->super.iret = IWICStream_Commit(stream->host, c->grfCommitFlags);
}

#endif

struct qemu_WICStream_Revert
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_Revert(IWICStream *iface)
{
    struct qemu_WICStream_Revert call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_REVERT);
    call.iface = (ULONG_PTR)stream;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_Revert(struct qemu_syscall *call)
{
    struct qemu_WICStream_Revert *c = (struct qemu_WICStream_Revert *)call;
    struct qemu_wic_stream *stream;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);

    c->super.iret = IWICStream_Revert(stream->host);
}

#endif

struct qemu_WICStream_LockRegion
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t libOffset;
    uint64_t cb;
    uint64_t dwLockType;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_LockRegion(IWICStream *iface, ULARGE_INTEGER libOffset,
        ULARGE_INTEGER cb, DWORD dwLockType)
{
    struct qemu_WICStream_LockRegion call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_LOCKREGION);
    call.iface = (ULONG_PTR)stream;
    call.libOffset = libOffset.QuadPart;
    call.cb = cb.QuadPart;
    call.dwLockType = dwLockType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_LockRegion(struct qemu_syscall *call)
{
    struct qemu_WICStream_LockRegion *c = (struct qemu_WICStream_LockRegion *)call;
    struct qemu_wic_stream *stream;
    ULARGE_INTEGER libOffset, cb;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);
    libOffset.QuadPart = c->libOffset;
    cb.QuadPart = c->cb;

    c->super.iret = IWICStream_LockRegion(stream->host, libOffset, cb, c->dwLockType);
}

#endif

struct qemu_WICStream_UnlockRegion
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t libOffset;
    uint64_t cb;
    uint64_t dwLockType;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_UnlockRegion(IWICStream *iface, ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
    struct qemu_WICStream_UnlockRegion call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_UNLOCKREGION);
    call.iface = (ULONG_PTR)stream;
    call.libOffset = libOffset.QuadPart;
    call.cb = cb.QuadPart;
    call.dwLockType = dwLockType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_UnlockRegion(struct qemu_syscall *call)
{
    struct qemu_WICStream_UnlockRegion *c = (struct qemu_WICStream_UnlockRegion *)call;
    struct qemu_wic_stream *stream;
    ULARGE_INTEGER libOffset, cb;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);
    libOffset.QuadPart = c->libOffset;
    cb.QuadPart = c->cb;

    c->super.iret = IWICStream_UnlockRegion(stream->host, libOffset, cb, c->dwLockType);
}

#endif

struct qemu_WICStream_Stat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pstatstg;
    uint64_t grfStatFlag;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_Stat(IWICStream *iface, STATSTG *pstatstg, DWORD grfStatFlag)
{
    struct qemu_WICStream_Stat call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_STAT);
    call.iface = (ULONG_PTR)stream;
    call.pstatstg = (ULONG_PTR)pstatstg;
    call.grfStatFlag = grfStatFlag;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_Stat(struct qemu_syscall *call)
{
    struct qemu_WICStream_Stat *c = (struct qemu_WICStream_Stat *)call;
    struct qemu_wic_stream *stream;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);

    c->super.iret = IWICStream_Stat(stream->host, QEMU_G2H(c->pstatstg), c->grfStatFlag);
}

#endif

struct qemu_WICStream_Clone
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppstm;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_Clone(IWICStream *iface, IStream **ppstm)
{
    struct qemu_WICStream_Clone call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_CLONE);
    call.iface = (ULONG_PTR)stream;
    call.ppstm = (ULONG_PTR)ppstm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_Clone(struct qemu_syscall *call)
{
    struct qemu_WICStream_Clone *c = (struct qemu_WICStream_Clone *)call;
    struct qemu_wic_stream *stream;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);

    c->super.iret = IWICStream_Clone(stream->host, QEMU_G2H(c->ppstm));
}

#endif

struct qemu_WICStream_InitializeFromIStream
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIStream;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_InitializeFromIStream(IWICStream *iface, IStream *pIStream)
{
    struct qemu_WICStream_InitializeFromIStream call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_INITIALIZEFROMISTREAM);
    call.iface = (ULONG_PTR)stream;
    call.pIStream = (ULONG_PTR)pIStream;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_InitializeFromIStream(struct qemu_syscall *call)
{
    struct qemu_WICStream_InitializeFromIStream *c = (struct qemu_WICStream_InitializeFromIStream *)call;
    struct qemu_wic_stream *stream;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);

    c->super.iret = IWICStream_InitializeFromIStream(stream->host, QEMU_G2H(c->pIStream));
}

#endif

struct qemu_WICStream_InitializeFromFilename
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t wzFileName;
    uint64_t dwDesiredAccess;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_InitializeFromFilename(IWICStream *iface, LPCWSTR wzFileName, DWORD dwDesiredAccess)
{
    struct qemu_WICStream_InitializeFromFilename call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_INITIALIZEFROMFILENAME);
    call.iface = (ULONG_PTR)stream;
    call.wzFileName = (ULONG_PTR)wzFileName;
    call.dwDesiredAccess = dwDesiredAccess;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_InitializeFromFilename(struct qemu_syscall *call)
{
    struct qemu_WICStream_InitializeFromFilename *c = (struct qemu_WICStream_InitializeFromFilename *)call;
    struct qemu_wic_stream *stream;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);

    c->super.iret = IWICStream_InitializeFromFilename(stream->host, QEMU_G2H(c->wzFileName), c->dwDesiredAccess);
}

#endif

struct qemu_WICStream_InitializeFromMemory
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pbBuffer;
    uint64_t cbBufferSize;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_InitializeFromMemory(IWICStream *iface, BYTE *pbBuffer, DWORD cbBufferSize)
{
    struct qemu_WICStream_InitializeFromMemory call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_INITIALIZEFROMMEMORY);
    call.iface = (ULONG_PTR)stream;
    call.pbBuffer = (ULONG_PTR)pbBuffer;
    call.cbBufferSize = cbBufferSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_InitializeFromMemory(struct qemu_syscall *call)
{
    struct qemu_WICStream_InitializeFromMemory *c = (struct qemu_WICStream_InitializeFromMemory *)call;
    struct qemu_wic_stream *stream;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);

    c->super.iret = IWICStream_InitializeFromMemory(stream->host, QEMU_G2H(c->pbBuffer), c->cbBufferSize);
}

#endif

struct qemu_WICStream_InitializeFromIStreamRegion
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIStream;
    uint64_t ulOffset;
    uint64_t ulMaxSize;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICStream_InitializeFromIStreamRegion(IWICStream *iface, IStream *pIStream,
        ULARGE_INTEGER ulOffset, ULARGE_INTEGER ulMaxSize)
{
    struct qemu_WICStream_InitializeFromIStreamRegion call;
    struct qemu_wic_stream *stream = impl_from_IWICStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICSTREAM_INITIALIZEFROMISTREAMREGION);
    call.iface = (ULONG_PTR)stream;
    call.pIStream = (ULONG_PTR)pIStream;
    call.ulOffset = ulOffset.QuadPart;
    call.ulMaxSize = ulMaxSize.QuadPart;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICStream_InitializeFromIStreamRegion(struct qemu_syscall *call)
{
    struct qemu_WICStream_InitializeFromIStreamRegion *c = (struct qemu_WICStream_InitializeFromIStreamRegion *)call;
    struct qemu_wic_stream *stream;
    ULARGE_INTEGER ulOffset, ulMaxSize;

    WINE_FIXME("Unverified!\n");
    stream = QEMU_G2H(c->iface);
    ulOffset.QuadPart = c->ulOffset;
    ulMaxSize.QuadPart = c->ulMaxSize;

    c->super.iret = IWICStream_InitializeFromIStreamRegion(stream->host, QEMU_G2H(c->pIStream), ulOffset, ulMaxSize);
}

#endif

#ifdef QEMU_DLL_GUEST

static const IWICStreamVtbl WICStream_Vtbl =
{
    /*** IUnknown methods ***/
    WICStream_QueryInterface,
    WICStream_AddRef,
    WICStream_Release,
    /*** ISequentialStream methods ***/
    WICStream_Read,
    WICStream_Write,
    /*** IStream methods ***/
    WICStream_Seek,
    WICStream_SetSize,
    WICStream_CopyTo,
    WICStream_Commit,
    WICStream_Revert,
    WICStream_LockRegion,
    WICStream_UnlockRegion,
    WICStream_Stat,
    WICStream_Clone,
    /*** IWICStream methods ***/
    WICStream_InitializeFromIStream,
    WICStream_InitializeFromFilename,
    WICStream_InitializeFromMemory,
    WICStream_InitializeFromIStreamRegion,
};

void WICStream_init_guest(struct qemu_wic_stream *stream)
{
    stream->IWICStream_iface.lpVtbl = &WICStream_Vtbl;
}

#else

struct qemu_wic_stream *WICStream_create_host(IWICStream *host)
{
    struct qemu_wic_stream *ret;
    HRESULT hr;

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
    {
        WINE_WARN("Out of memory\n");
        return NULL;
    }

    ret->host = host;

}

#endif
