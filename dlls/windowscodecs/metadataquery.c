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

#include "thunk/qemu_windows.h"
#include "thunk/qemu_wincodec.h"

#include <wine/debug.h>
#include <wine/list.h>

#include "qemu_windowscodecs.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_wic);

struct qemu_WICMetadataQueryReader_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppvObject;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_query_reader *impl_from_IWICMetadataQueryReader(IWICMetadataQueryReader *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_query_reader, IWICMetadataQueryReader_iface);
}

static HRESULT WINAPI WICMetadataQueryReader_QueryInterface(IWICMetadataQueryReader *iface, REFIID riid, void **ppvObject)
{
    struct qemu_WICMetadataQueryReader_QueryInterface call;
    struct qemu_wic_query_reader *reader = impl_from_IWICMetadataQueryReader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAQUERYREADER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)reader;
    call.riid = (ULONG_PTR)riid;
    call.ppvObject = (ULONG_PTR)ppvObject;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataQueryReader_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICMetadataQueryReader_QueryInterface *c = (struct qemu_WICMetadataQueryReader_QueryInterface *)call;
    struct qemu_wic_query_reader *reader;

    WINE_FIXME("Unverified!\n");
    c->super.iret = IWICMetadataQueryReader_QueryInterface(reader->host, QEMU_G2H(c->riid), QEMU_G2H(c->ppvObject));
}

#endif

struct qemu_WICMetadataQueryReader_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICMetadataQueryReader_AddRef(IWICMetadataQueryReader *iface)
{
    struct qemu_WICMetadataQueryReader_AddRef call;
    struct qemu_wic_query_reader *reader = impl_from_IWICMetadataQueryReader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAQUERYREADER_ADDREF);
    call.iface = (ULONG_PTR)reader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataQueryReader_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICMetadataQueryReader_AddRef *c = (struct qemu_WICMetadataQueryReader_AddRef *)call;
    struct qemu_wic_query_reader *reader;

    WINE_FIXME("Unverified!\n");
    reader = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataQueryReader_AddRef(reader->host);
}

#endif

struct qemu_WICMetadataQueryReader_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICMetadataQueryReader_Release(IWICMetadataQueryReader *iface)
{
    struct qemu_WICMetadataQueryReader_Release call;
    struct qemu_wic_query_reader *reader = impl_from_IWICMetadataQueryReader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAQUERYREADER_RELEASE);
    call.iface = (ULONG_PTR)reader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataQueryReader_Release(struct qemu_syscall *call)
{
    struct qemu_WICMetadataQueryReader_Release *c = (struct qemu_WICMetadataQueryReader_Release *)call;
    struct qemu_wic_query_reader *reader;

    WINE_TRACE("\n");
    reader = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataQueryReader_Release(reader->host);
    if (!c->super.iret)
    {
        WINE_TRACE("Destroying query reader wrapper %p for host reader %p.\n", reader, reader->host);
        HeapFree(GetProcessHeap(), 0, reader);
    }
}

#endif

struct qemu_WICMetadataQueryReader_GetContainerFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataQueryReader_GetContainerFormat(IWICMetadataQueryReader *iface, GUID *format)
{
    struct qemu_WICMetadataQueryReader_GetContainerFormat call;
    struct qemu_wic_query_reader *reader = impl_from_IWICMetadataQueryReader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAQUERYREADER_GETCONTAINERFORMAT);
    call.iface = (ULONG_PTR)reader;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataQueryReader_GetContainerFormat(struct qemu_syscall *call)
{
    struct qemu_WICMetadataQueryReader_GetContainerFormat *c =
            (struct qemu_WICMetadataQueryReader_GetContainerFormat *)call;
    struct qemu_wic_query_reader *reader;

    WINE_TRACE("\n");
    reader = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataQueryReader_GetContainerFormat(reader->host, QEMU_G2H(c->format));
}

#endif

struct qemu_WICMetadataQueryReader_GetLocation
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t len;
    uint64_t location;
    uint64_t ret_len;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataQueryReader_GetLocation(IWICMetadataQueryReader *iface, UINT len, WCHAR *location, UINT *ret_len)
{
    struct qemu_WICMetadataQueryReader_GetLocation call;
    struct qemu_wic_query_reader *reader = impl_from_IWICMetadataQueryReader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAQUERYREADER_GETLOCATION);
    call.iface = (ULONG_PTR)reader;
    call.len = len;
    call.location = (ULONG_PTR)location;
    call.ret_len = (ULONG_PTR)ret_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataQueryReader_GetLocation(struct qemu_syscall *call)
{
    struct qemu_WICMetadataQueryReader_GetLocation *c = (struct qemu_WICMetadataQueryReader_GetLocation *)call;
    struct qemu_wic_query_reader *reader;

    WINE_FIXME("Unverified!\n");
    reader = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataQueryReader_GetLocation(reader->host, c->len, QEMU_G2H(c->location), QEMU_G2H(c->ret_len));
}

#endif

struct qemu_WICMetadataQueryReader_GetMetadataByName
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t query;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataQueryReader_GetMetadataByName(IWICMetadataQueryReader *iface,
        LPCWSTR query, PROPVARIANT *value)
{
    struct qemu_WICMetadataQueryReader_GetMetadataByName call;
    struct qemu_wic_query_reader *reader = impl_from_IWICMetadataQueryReader(iface), *new_reader;

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAQUERYREADER_GETMETADATABYNAME);
    call.iface = (ULONG_PTR)reader;
    call.query = (ULONG_PTR)query;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret) && value->vt == VT_UNKNOWN)
    {
        new_reader = (struct qemu_wic_query_reader *)value->punkVal;
        WICMetadataQueryReader_init_guest(new_reader);
        value->punkVal = (IUnknown *)&new_reader->IWICMetadataQueryReader_iface;
    }
    return call.super.iret;
}

#else

void qemu_WICMetadataQueryReader_GetMetadataByName(struct qemu_syscall *call)
{
    struct qemu_WICMetadataQueryReader_GetMetadataByName *c =
            (struct qemu_WICMetadataQueryReader_GetMetadataByName *)call;
    struct qemu_wic_query_reader *reader, *new_reader;
    PROPVARIANT stack, *value = &stack;
    IUnknown *unk;
    IWICMetadataQueryReader *host;
    HRESULT hr;

    WINE_TRACE("\n");
    reader = QEMU_G2H(c->iface);
#if GUEST_BIT == HOST_BIT
    value = QEMU_G2H(c->value);
#else
    if (!c->value)
        value = NULL;
#endif

    c->super.iret = IWICMetadataQueryReader_GetMetadataByName(reader->host, QEMU_G2H(c->query), value);

    if (SUCCEEDED(c->super.iret))
    {
        if (value->vt == VT_UNKNOWN)
        {
            WINE_TRACE("Returning a COM interface. Me %p, host %p, ret %p\n", reader, reader->host, value->punkVal);
            unk = value->punkVal;

            hr = IUnknown_QueryInterface(unk, &IID_IWICMetadataQueryReader, (void **)&host);
            IUnknown_Release(unk);
            if (FAILED(hr))
            {
                WINE_FIXME("Returned interface is not an IWICMetadataQueryReader.\n");
                c->super.iret = hr;
                return;
            }
            if (host == reader->host)
                WINE_FIXME("Returning self.\n");

            new_reader = WICMetadataQueryReader_create_host(host);
            if (!new_reader)
            {
                IWICMetadataQueryReader_Release(host);
                c->super.iret = E_OUTOFMEMORY;
                return;
            }
            value->punkVal = (IUnknown *)new_reader;
        }

#if GUEST_BIT != HOST_BIT
        PROPVARIANT_h2g(QEMU_G2H(c->value), value);
#endif
    }
}

#endif

struct qemu_WICMetadataQueryReader_GetEnumerator
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIEnumString;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataQueryReader_GetEnumerator(IWICMetadataQueryReader *iface, IEnumString **ppIEnumString)
{
    struct qemu_WICMetadataQueryReader_GetEnumerator call;
    struct qemu_wic_query_reader *reader = impl_from_IWICMetadataQueryReader(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAQUERYREADER_GETENUMERATOR);
    call.iface = (ULONG_PTR)reader;
    call.ppIEnumString = (ULONG_PTR)ppIEnumString;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataQueryReader_GetEnumerator(struct qemu_syscall *call)
{
    struct qemu_WICMetadataQueryReader_GetEnumerator *c = (struct qemu_WICMetadataQueryReader_GetEnumerator *)call;
    struct qemu_wic_query_reader *reader;

    WINE_FIXME("Unverified!\n");
    reader = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataQueryReader_GetEnumerator(reader->host, QEMU_G2H(c->ppIEnumString));
}

#endif

struct qemu_WICMapGuidToShortName
{
    struct qemu_syscall super;
    uint64_t guid;
    uint64_t len;
    uint64_t name;
    uint64_t ret_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WICMapGuidToShortName(REFGUID guid, UINT len, WCHAR *name, UINT *ret_len)
{
    struct qemu_WICMapGuidToShortName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WICMAPGUIDTOSHORTNAME);
    call.guid = (ULONG_PTR)guid;
    call.len = len;
    call.name = (ULONG_PTR)name;
    call.ret_len = (ULONG_PTR)ret_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMapGuidToShortName(struct qemu_syscall *call)
{
    struct qemu_WICMapGuidToShortName *c = (struct qemu_WICMapGuidToShortName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WICMapGuidToShortName(QEMU_G2H(c->guid), c->len, QEMU_G2H(c->name), QEMU_G2H(c->ret_len));
}

#endif

struct qemu_WICMapShortNameToGuid
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t guid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WICMapShortNameToGuid(PCWSTR name, GUID *guid)
{
    struct qemu_WICMapShortNameToGuid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WICMAPSHORTNAMETOGUID);
    call.name = (ULONG_PTR)name;
    call.guid = (ULONG_PTR)guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMapShortNameToGuid(struct qemu_syscall *call)
{
    struct qemu_WICMapShortNameToGuid *c = (struct qemu_WICMapShortNameToGuid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WICMapShortNameToGuid(QEMU_G2H(c->name), QEMU_G2H(c->guid));
}

#endif

struct qemu_WICMapSchemaToName
{
    struct qemu_syscall super;
    uint64_t format;
    uint64_t schema;
    uint64_t len;
    uint64_t name;
    uint64_t ret_len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WICMapSchemaToName(REFGUID format, LPWSTR schema, UINT len, WCHAR *name, UINT *ret_len)
{
    struct qemu_WICMapSchemaToName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WICMAPSCHEMATONAME);
    call.format = (ULONG_PTR)format;
    call.schema = (ULONG_PTR)schema;
    call.len = len;
    call.name = (ULONG_PTR)name;
    call.ret_len = (ULONG_PTR)ret_len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMapSchemaToName(struct qemu_syscall *call)
{
    struct qemu_WICMapSchemaToName *c = (struct qemu_WICMapSchemaToName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WICMapSchemaToName(QEMU_G2H(c->format), QEMU_G2H(c->schema), c->len,
            QEMU_G2H(c->name), QEMU_G2H(c->ret_len));
}

#endif

#ifdef QEMU_DLL_GUEST

static IWICMetadataQueryReaderVtbl WICMetadataQueryReader_vtbl =
{
    WICMetadataQueryReader_QueryInterface,
    WICMetadataQueryReader_AddRef,
    WICMetadataQueryReader_Release,
    WICMetadataQueryReader_GetContainerFormat,
    WICMetadataQueryReader_GetLocation,
    WICMetadataQueryReader_GetMetadataByName,
    WICMetadataQueryReader_GetEnumerator
};

void WICMetadataQueryReader_init_guest(struct qemu_wic_query_reader *reader)
{
    reader->IWICMetadataQueryReader_iface.lpVtbl = &WICMetadataQueryReader_vtbl;
}

#else

struct qemu_wic_query_reader *WICMetadataQueryReader_create_host(IWICMetadataQueryReader *host)
{
    struct qemu_wic_query_reader *ret;
    HRESULT hr;

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
    {
        WINE_WARN("Out of memory\n");
        return NULL;
    }

    ret->host = host;

    return ret;
}

#endif
