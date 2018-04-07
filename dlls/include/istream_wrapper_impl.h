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
    
};

#ifdef QEMU_DLL_GUEST

static void istream_wrapper_get_funcs(struct istream_wrapper_funcs *funcs)
{
    
}

#else

#include <wine/debug.h>
WINE_DECLARE_DEBUG_CHANNEL(istream_wrapper);

static void istream_wrapper_set_funcs(const struct istream_wrapper_funcs *funcs)
{
    
}

struct istream_wrapper *istream_wrapper_from_IStream(IStream *iface)
{
    return CONTAINING_RECORD(iface, struct istream_wrapper, IStream_iface);
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_QueryInterface(IStream *iface, const IID *iid,
        void **out)
{
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
    return E_NOTIMPL;
}

static ULONG STDMETHODCALLTYPE istream_wrapper_AddRef(IStream *iface)
{
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
    return 2;
}

static ULONG STDMETHODCALLTYPE istream_wrapper_Release(IStream *iface)
{
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
    return 1;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Read(IStream *iface, void *pv, ULONG cb,
        ULONG *read)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Write(IStream *iface, const void *pv, ULONG cb,
        ULONG *written)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Seek(IStream *iface, LARGE_INTEGER offset, DWORD origin,
        ULARGE_INTEGER *new_pos)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_SetSize(IStream *iface, ULARGE_INTEGER libNewSize)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_CopyTo(IStream *iface, IStream *pstm,
                                                    ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead,
                                                    ULARGE_INTEGER *pcbWritten)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Commit(IStream *iface, DWORD grfCommitFlags)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Revert(IStream *iface)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_LockRegion(IStream *iface, ULARGE_INTEGER libOffset,
                                                        ULARGE_INTEGER cb, DWORD dwLockType)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_UnlockRegion(IStream *iface, ULARGE_INTEGER libOffset,
                                                          ULARGE_INTEGER cb, DWORD dwLockType)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Stat(IStream *iface, STATSTG *pstatstg,
                                                  DWORD grfStatFlag)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE istream_wrapper_Clone(IStream *iface, IStream **ppstm)
{
    struct istream_wrapper *stream = istream_wrapper_from_IStream(iface);
    WINE_FIXME_(istream_wrapper)("Not implemented.\n");
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
