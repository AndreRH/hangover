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

#include "thunk/qemu_windows.h"
#include "thunk/qemu_objidl.h"

#include "istream_wrapper.h"

struct istream_wrapper
{
    IStream IStream_iface;
    uint64_t guest_iface;
    LONG ref;
};

struct istream_wrapper_funcs
{
    uint64_t addref;
    uint64_t release;
    uint64_t seek;
    uint64_t read;
    uint64_t write;
    uint64_t stat;
};

struct istream_wrapper_Seek
{
    uint64_t iface;
    uint64_t offset, origin, new_pos;
};

struct istream_wrapper_ReadWrite
{
    uint64_t iface;
    uint64_t pv, cb, count;
};

struct istream_wrapper_Stat
{
    uint64_t iface;
    uint64_t statstg;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static ULONG __fastcall istream_wrapper_AddRef(IStream *stream)
{
    return stream->lpVtbl->AddRef(stream);
}

static ULONG __fastcall istream_wrapper_Release(IStream *stream)
{
    return stream->lpVtbl->Release(stream);
}

static HRESULT __fastcall istream_wrapper_Seek(struct istream_wrapper_Seek *call)
{
    IStream *stream = (IStream *)(ULONG_PTR)call->iface;
    LARGE_INTEGER li;
    li.QuadPart = call->offset;
    return stream->lpVtbl->Seek(stream, li, call->origin, (ULARGE_INTEGER *)(ULONG_PTR)call->new_pos);
}

static HRESULT __fastcall istream_wrapper_Read(struct istream_wrapper_ReadWrite *call)
{
    IStream *stream = (IStream *)(ULONG_PTR)call->iface;
    return stream->lpVtbl->Read(stream, (void *)(ULONG_PTR)call->pv, call->cb, (ULONG *)(ULONG_PTR)call->count);
}

static HRESULT __fastcall istream_wrapper_Write(struct istream_wrapper_ReadWrite *call)
{
    IStream *stream = (IStream *)(ULONG_PTR)call->iface;
    return stream->lpVtbl->Write(stream, (void *)(ULONG_PTR)call->pv, call->cb, (ULONG *)(ULONG_PTR)call->count);
}

static HRESULT __fastcall istream_wrapper_Stat(struct istream_wrapper_Stat *call)
{
    IStream *stream = (IStream *)(ULONG_PTR)call->iface;
    return stream->lpVtbl->Stat(stream, (void *)(ULONG_PTR)call->statstg, call->flags);
}

static void istream_wrapper_get_funcs(struct istream_wrapper_funcs *funcs)
{
    funcs->addref = (ULONG_PTR)istream_wrapper_AddRef;
    funcs->release = (ULONG_PTR)istream_wrapper_Release;
    funcs->seek = (ULONG_PTR)istream_wrapper_Seek;
    funcs->read = (ULONG_PTR)istream_wrapper_Read;
    funcs->write = (ULONG_PTR)istream_wrapper_Write;
    funcs->stat = (ULONG_PTR)istream_wrapper_Stat;
}

#else

static uint64_t istream_wrapper_AddRef_guest;
static uint64_t istream_wrapper_Release_guest;
static uint64_t istream_wrapper_Seek_guest;
static uint64_t istream_wrapper_Read_guest;
static uint64_t istream_wrapper_Write_guest;
static uint64_t istream_wrapper_Stat_guest;

static void istream_wrapper_set_funcs(const struct istream_wrapper_funcs *funcs)
{
    if (funcs)
    {
        istream_wrapper_AddRef_guest = funcs->addref;
        istream_wrapper_Release_guest = funcs->release;
        istream_wrapper_Seek_guest = funcs->seek;
        istream_wrapper_Read_guest = funcs->read;
        istream_wrapper_Write_guest = funcs->write;
        istream_wrapper_Stat_guest = funcs->stat;
    }
    else
    {
        istream_wrapper_AddRef_guest = 0;
        istream_wrapper_Release_guest = 0;
        istream_wrapper_Seek_guest = 0;
        istream_wrapper_Read_guest = 0;
        istream_wrapper_Write_guest = 0;
        istream_wrapper_Stat_guest = 0;
    }
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
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    ULONG ref = InterlockedIncrement(&stream->ref);

    WINE_TRACE("(%p) refcount=%u\n", stream, ref);

    return ref;
}

static ULONG STDMETHODCALLTYPE istream_wrapper_Release(IStream *iface)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    ULONG ref = InterlockedDecrement(&stream->ref), ref2;

    WINE_TRACE("(%p) refcount=%u\n", stream, ref);
    if (!ref)
    {
        WINE_TRACE("Calling guest Release %p.\n", (void *)istream_wrapper_Release_guest);
        ref2 = qemu_ops->qemu_execute(QEMU_G2H(istream_wrapper_Release_guest), istream_wrapper_guest_iface(stream));
        WINE_TRACE("Guest Release returned %u.\n", ref2);

        HeapFree(GetProcessHeap(), 0, stream);
    }

    return ref;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Read(IStream *iface, void *pv, ULONG cb,
        ULONG *read)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    struct istream_wrapper_ReadWrite call;
    HRESULT hr;
    void *bounce_buffer = NULL;

    WINE_TRACE("\n");
    call.iface = istream_wrapper_guest_iface(stream);
    call.pv = QEMU_H2G(pv);
    call.cb = cb;
    call.count = QEMU_H2G(read);

    /* Sigh. Windowscodecs passes pointers allocated by libpng, which somehow manages to allocate something > 4GB.
     * Or they just pass static data, I can't check right now because the libpng servers are down. */
#if GUEST_BIT != HOST_BIT
    if (call.pv > ~0U)
    {
        bounce_buffer = HeapAlloc(GetProcessHeap(), 0, cb);
        call.pv = QEMU_H2G(bounce_buffer);
    }
#endif

    WINE_TRACE("Calling guest callback %p.\n", (void *)istream_wrapper_Read_guest);
    hr = qemu_ops->qemu_execute(QEMU_G2H(istream_wrapper_Read_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", hr);

#if GUEST_BIT != HOST_BIT
    if (SUCCEEDED(hr) && bounce_buffer)
        memcpy(pv, bounce_buffer, *read);

    HeapFree(GetProcessHeap(), 0, bounce_buffer);
#endif

    return hr;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Write(IStream *iface, const void *pv, ULONG cb,
        ULONG *written)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    struct istream_wrapper_ReadWrite call;
    HRESULT hr;
    void *bounce_buffer = NULL;

    WINE_TRACE("\n");
    call.iface = istream_wrapper_guest_iface(stream);
    call.pv = QEMU_H2G(pv);
    call.cb = cb;
    call.count = QEMU_H2G(written);
#if GUEST_BIT != HOST_BIT
    if (call.pv > ~0U)
    {
        bounce_buffer = HeapAlloc(GetProcessHeap(), 0, cb);
        memcpy(bounce_buffer, pv, cb);
        call.pv = QEMU_H2G(bounce_buffer);
    }
#endif

    WINE_TRACE("Calling guest callback %p.\n", (void *)istream_wrapper_Write_guest);
    hr = qemu_ops->qemu_execute(QEMU_G2H(istream_wrapper_Write_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", hr);

#if GUEST_BIT != HOST_BIT
    HeapFree(GetProcessHeap(), 0, bounce_buffer);
#endif

    return hr;
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
        DWORD flags)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    struct istream_wrapper_Stat call;
    HRESULT hr;
    struct qemu_STATSTG stat32;

    WINE_TRACE("\n");
    call.iface = istream_wrapper_guest_iface(stream);
    call.flags = flags;

#if GUEST_BIT == HOST_BIT
    call.statstg = QEMU_H2G(pstatstg);
#else
    STATSTG_h2g(&stat32, pstatstg);
    call.statstg = QEMU_H2G(&stat32);
#endif

    WINE_TRACE("Calling guest callback %p.\n", (void *)istream_wrapper_Stat_guest);
    hr = qemu_ops->qemu_execute(QEMU_G2H(istream_wrapper_Stat_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", hr);

#if GUEST_BIT != HOST_BIT
    STATSTG_g2h(pstatstg, &stat32);
#endif

    return hr;
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
    ULONG ref;

    if (!guest_iface)
        return NULL;

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
        return NULL;

    WINE_TRACE("Calling guest AddRef %p.\n", (void *)istream_wrapper_AddRef_guest);
    ref = qemu_ops->qemu_execute(QEMU_G2H(istream_wrapper_AddRef_guest), guest_iface);
    WINE_TRACE("Guest AddRef returned %u.\n", ref);

    ret->ref = 1;
    ret->guest_iface = guest_iface;
    ret->IStream_iface.lpVtbl = &istream_wrapper_Vtbl;

    return ret;
}

uint64_t istream_wrapper_guest_iface(struct istream_wrapper *wrapper)
{
    return wrapper ? wrapper->guest_iface : 0;
}

IStream *istream_wrapper_host_iface(struct istream_wrapper *wrapper)
{
    return wrapper ? &wrapper->IStream_iface : NULL;
}

#endif
