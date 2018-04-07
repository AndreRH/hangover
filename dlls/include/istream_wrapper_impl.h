/*
 * Copyright 2018 Stefan Dösinger for CodeWeavers
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

#include "istream_wrapper.h"

struct istream_wrapper
{
    IStream IStream_iface;
    uint64_t guest_iface;
};

struct istream_wrapper_funcs
{
    uint64_t seek;
    uint64_t read;
};

struct istream_wrapper_Seek
{
    uint64_t iface;
    uint64_t offset, origin, new_pos;
};

struct istream_wrapper_Read
{
    uint64_t iface;
    uint64_t pv, cb, read;
};

#ifdef QEMU_DLL_GUEST

static HRESULT __fastcall istream_wrapper_Seek(struct istream_wrapper_Seek *call)
{
    IStream *stream = (IStream *)(ULONG_PTR)call->iface;
    LARGE_INTEGER li;
    li.QuadPart = call->offset;
    return stream->lpVtbl->Seek(stream, li, call->origin, (ULARGE_INTEGER *)(ULONG_PTR)call->new_pos);
}

static HRESULT __fastcall istream_wrapper_Read(struct istream_wrapper_Read *call)
{
    IStream *stream = (IStream *)(ULONG_PTR)call->iface;
    return stream->lpVtbl->Read(stream, (void *)(ULONG_PTR)call->pv, call->cb, (ULONG *)(ULONG_PTR)call->read);
}

static void istream_wrapper_get_funcs(struct istream_wrapper_funcs *funcs)
{
    funcs->seek = (ULONG_PTR)istream_wrapper_Seek;
    funcs->read = (ULONG_PTR)istream_wrapper_Read;
}

#else

static uint64_t istream_wrapper_Seek_guest;
static uint64_t istream_wrapper_Read_guest;

static void istream_wrapper_set_funcs(const struct istream_wrapper_funcs *funcs)
{
    istream_wrapper_Seek_guest = funcs->seek;
    istream_wrapper_Read_guest = funcs->read;
}

struct istream_wrapper *istream_wrapper_from_IStream(IStream *iface)
{
    return CONTAINING_RECORD(iface, struct istream_wrapper, IStream_iface);
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_QueryInterface(IStream *iface, const IID *iid,
        void **out)
{
    WINE_FIXME("Not implemented.\n");
    return E_NOTIMPL;
}

static ULONG STDMETHODCALLTYPE istream_wrapper_AddRef(IStream *iface)
{
    WINE_FIXME("Not implemented.\n");
    return 2;
}

static ULONG STDMETHODCALLTYPE istream_wrapper_Release(IStream *iface)
{
    WINE_FIXME("Not implemented.\n");
    return 1;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Read(IStream *iface, void *pv, ULONG cb,
        ULONG *read)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    struct istream_wrapper_Read call;
    HRESULT hr;

    WINE_TRACE("\n");
    call.iface = istream_wrapper_guest_iface(stream);
    call.pv = QEMU_H2G(pv);
    call.cb = cb;
    call.read = QEMU_H2G(read);

    WINE_TRACE("Calling guest callback %p.\n", (void *)istream_wrapper_Read_guest);
    hr = qemu_ops->qemu_execute(QEMU_G2H(istream_wrapper_Read_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", hr);

    return hr;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Write(IStream *iface, const void *pv, ULONG cb,
        ULONG *written)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Seek(IStream *iface, LARGE_INTEGER offset, DWORD origin,
        ULARGE_INTEGER *new_pos)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    struct istream_wrapper_Seek call;
    HRESULT hr;

    WINE_TRACE("\n");
    call.iface = istream_wrapper_guest_iface(stream);
    call.offset = offset.QuadPart;
    call.origin = origin;
    call.new_pos = QEMU_H2G(new_pos);

    WINE_TRACE("Calling guest callback %p.\n", (void *)istream_wrapper_Seek_guest);
    hr = qemu_ops->qemu_execute(QEMU_G2H(istream_wrapper_Seek_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", hr);

    return hr;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_SetSize(IStream *iface, ULARGE_INTEGER libNewSize)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_CopyTo(IStream *iface, IStream *pstm,
                                                    ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead,
                                                    ULARGE_INTEGER *pcbWritten)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Commit(IStream *iface, DWORD grfCommitFlags)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Revert(IStream *iface)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_LockRegion(IStream *iface, ULARGE_INTEGER libOffset,
                                                        ULARGE_INTEGER cb, DWORD dwLockType)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_UnlockRegion(IStream *iface, ULARGE_INTEGER libOffset,
                                                          ULARGE_INTEGER cb, DWORD dwLockType)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Stat(IStream *iface, STATSTG *pstatstg,
                                                  DWORD grfStatFlag)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Clone(IStream *iface, IStream **ppstm)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME("Not implemented.\n");
    return E_FAIL;
}

static const IStreamVtbl istream_wrapper_Vtbl =
{
    istream_wrapper_QueryInterface,
    istream_wrapper_AddRef,
    istream_wrapper_Release,
    istream_wrapper_Read,
    istream_wrapper_Write,
    istream_wrapper_Seek,
    istream_wrapper_SetSize,
    istream_wrapper_CopyTo,
    istream_wrapper_Commit,
    istream_wrapper_Revert,
    istream_wrapper_LockRegion,
    istream_wrapper_UnlockRegion,
    istream_wrapper_Stat,
    istream_wrapper_Clone
};

struct istream_wrapper *istream_wrapper_create(uint64_t guest_iface)
{
    struct istream_wrapper *ret;
    
    if (!guest_iface)
        return NULL;

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
        return NULL;

    ret->guest_iface = guest_iface;
    ret->IStream_iface.lpVtbl = &istream_wrapper_Vtbl;

    return ret;
}

void istream_wrapper_destroy(struct istream_wrapper *wrapper)
{
    HeapFree(GetProcessHeap(), 0, wrapper);
}

uint64_t istream_wrapper_guest_iface(struct istream_wrapper *wrapper)
{
    return wrapper->guest_iface;
}

IStream *istream_wrapper_host_iface(struct istream_wrapper *wrapper)
{
    return &wrapper->IStream_iface;
}

#endif
