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

struct qemu_MetadataHandler_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_metadata_handler *impl_from_IWICMetadataWriter(IWICMetadataWriter *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_metadata_handler, IWICMetadataWriter_iface);
}

static inline struct qemu_wic_metadata_handler *impl_from_IWICPersistStream(IWICPersistStream *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_metadata_handler, IWICPersistStream_iface);
}

static HRESULT WINAPI MetadataHandler_QueryInterface(IWICMetadataWriter *iface, REFIID iid, void **ppv)
{
    struct qemu_MetadataHandler_QueryInterface call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICMetadataWriter(iface);

    if (!ppv)
        return E_INVALIDARG;

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)handler;
    call.iid = (ULONG_PTR)iid;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        *ppv = NULL;
        return call.super.iret;
    }

    if (IsEqualIID(&IID_IUnknown, iid) || IsEqualIID(&IID_IWICMetadataReader, iid)
            || (IsEqualIID(&IID_IWICMetadataWriter, iid)))
    {
        *ppv = &handler->IWICMetadataWriter_iface;
    }
    else if (IsEqualIID(&IID_IPersist, iid) ||
             IsEqualIID(&IID_IPersistStream, iid) ||
             IsEqualIID(&IID_IWICPersistStream, iid))
    {
        *ppv = &handler->IWICPersistStream_iface;
    }
    else
    {
        WINE_FIXME("unknown interface %s, but host knows about it.\n", wine_dbgstr_guid(iid));
        *ppv = NULL;
        IWICMetadataWriter_Release(iface);
        return E_NOINTERFACE;
    }

    return call.super.iret;
}

#else

void qemu_MetadataHandler_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_QueryInterface *c = (struct qemu_MetadataHandler_QueryInterface *)call;
    struct qemu_wic_metadata_handler *handler;
    IUnknown *obj;

    WINE_TRACE("\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataWriter_QueryInterface(handler->host_writer, QEMU_G2H(c->iid), (void **)&obj);
    /* Pass the reference to the guest. */
}

#endif

struct qemu_MetadataHandler_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MetadataHandler_AddRef(IWICMetadataWriter *iface)
{
    struct qemu_MetadataHandler_AddRef call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICMetadataWriter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_ADDREF);
    call.iface = (ULONG_PTR)handler;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_AddRef(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_AddRef *c = (struct qemu_MetadataHandler_AddRef *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_TRACE("\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataWriter_AddRef(handler->host_writer);
}

#endif

struct qemu_MetadataHandler_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI MetadataHandler_Release(IWICMetadataWriter *iface)
{
    struct qemu_MetadataHandler_Release call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICMetadataWriter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_RELEASE);
    call.iface = (ULONG_PTR)handler;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static ULONG qemu_MetadataHandler_Release_internal(struct qemu_wic_metadata_handler *handler)
{
    ULONG ref = IWICMetadataWriter_Release(handler->host_writer);

    if (!ref)
    {
        WINE_TRACE("Destroying metadata handler %p for host handler %p.\n", handler, handler->host_writer);
        HeapFree(GetProcessHeap(), 0, handler);
    }

    return ref;
}

void qemu_MetadataHandler_Release(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_Release *c = (struct qemu_MetadataHandler_Release *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_TRACE("\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataWriter_Release(handler->host_writer);
}

#endif

struct qemu_MetadataHandler_GetMetadataHandlerInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIHandler;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_GetMetadataHandlerInfo(IWICMetadataWriter *iface, IWICMetadataHandlerInfo **ppIHandler)
{
    struct qemu_MetadataHandler_GetMetadataHandlerInfo call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICMetadataWriter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_GETMETADATAHANDLERINFO);
    call.iface = (ULONG_PTR)handler;
    call.ppIHandler = (ULONG_PTR)ppIHandler;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_GetMetadataHandlerInfo(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_GetMetadataHandlerInfo *c = (struct qemu_MetadataHandler_GetMetadataHandlerInfo *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataWriter_GetMetadataHandlerInfo(handler->host_writer, QEMU_G2H(c->ppIHandler));
}

#endif

struct qemu_MetadataHandler_GetMetadataFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pguidMetadataFormat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_GetMetadataFormat(IWICMetadataWriter *iface, GUID *pguidMetadataFormat)
{
    struct qemu_MetadataHandler_GetMetadataFormat call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICMetadataWriter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_GETMETADATAFORMAT);
    call.iface = (ULONG_PTR)handler;
    call.pguidMetadataFormat = (ULONG_PTR)pguidMetadataFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_GetMetadataFormat(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_GetMetadataFormat *c = (struct qemu_MetadataHandler_GetMetadataFormat *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataWriter_GetMetadataFormat(handler->host_writer, QEMU_G2H(c->pguidMetadataFormat));
}

#endif

struct qemu_MetadataHandler_GetCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pcCount;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_GetCount(IWICMetadataWriter *iface, UINT *pcCount)
{
    struct qemu_MetadataHandler_GetCount call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICMetadataWriter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_GETCOUNT);
    call.iface = (ULONG_PTR)handler;
    call.pcCount = (ULONG_PTR)pcCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_GetCount(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_GetCount *c = (struct qemu_MetadataHandler_GetCount *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataWriter_GetCount(handler->host_writer, QEMU_G2H(c->pcCount));
}

#endif

struct qemu_MetadataHandler_GetValueByIndex
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    uint64_t schema;
    uint64_t id;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_GetValueByIndex(IWICMetadataWriter *iface, UINT index, PROPVARIANT *schema, PROPVARIANT *id, PROPVARIANT *value)
{
    struct qemu_MetadataHandler_GetValueByIndex call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICMetadataWriter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_GETVALUEBYINDEX);
    call.iface = (ULONG_PTR)handler;
    call.index = index;
    call.schema = (ULONG_PTR)schema;
    call.id = (ULONG_PTR)id;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_GetValueByIndex(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_GetValueByIndex *c = (struct qemu_MetadataHandler_GetValueByIndex *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataWriter_GetValueByIndex(handler->host_writer, c->index, QEMU_G2H(c->schema), QEMU_G2H(c->id), QEMU_G2H(c->value));
}

#endif

struct qemu_MetadataHandler_GetValue
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t schema;
    uint64_t id;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_GetValue(IWICMetadataWriter *iface, const PROPVARIANT *schema, const PROPVARIANT *id, PROPVARIANT *value)
{
    struct qemu_MetadataHandler_GetValue call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICMetadataWriter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_GETVALUE);
    call.iface = (ULONG_PTR)handler;
    call.schema = (ULONG_PTR)schema;
    call.id = (ULONG_PTR)id;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_GetValue(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_GetValue *c = (struct qemu_MetadataHandler_GetValue *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataWriter_GetValue(handler->host_writer, QEMU_G2H(c->schema), QEMU_G2H(c->id), QEMU_G2H(c->value));
}

#endif

struct qemu_MetadataHandler_GetEnumerator
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIEnumMetadata;
};

#ifdef QEMU_DLL_GUEST

static void WICEnumMetadataItem_init_guest(struct qemu_wic_metadata_enum *item);
static HRESULT WINAPI MetadataHandler_GetEnumerator(IWICMetadataWriter *iface, IWICEnumMetadataItem **ppIEnumMetadata)
{
    struct qemu_MetadataHandler_GetEnumerator call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICMetadataWriter(iface);
    struct qemu_wic_metadata_enum *item;

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_GETENUMERATOR);
    call.iface = (ULONG_PTR)handler;
    call.ppIEnumMetadata = (ULONG_PTR)ppIEnumMetadata;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    item = (struct qemu_wic_metadata_enum *)(ULONG_PTR)call.ppIEnumMetadata;
    WICEnumMetadataItem_init_guest(item);
    *ppIEnumMetadata = &item->IWICEnumMetadataItem_iface;

    return call.super.iret;
}

#else

void qemu_MetadataHandler_GetEnumerator(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_GetEnumerator *c = (struct qemu_MetadataHandler_GetEnumerator *)call;
    struct qemu_wic_metadata_handler *handler;
    struct qemu_wic_metadata_enum *item;
    IWICEnumMetadataItem *host;

    WINE_TRACE("\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataWriter_GetEnumerator(handler->host_writer, c->ppIEnumMetadata ? &host : NULL);
    if (FAILED(c->super.iret))
        return;

    item = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*item));
    if (!item)
    {
        WINE_WARN("Out of memory.\n");
        IWICEnumMetadataItem_Release(host);
        c->super.iret = E_OUTOFMEMORY;
        return;
    }
    item->host = host;
    item->handler = handler;
    c->ppIEnumMetadata = QEMU_H2G(item);
}

#endif

struct qemu_MetadataHandler_SetValue
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pvarSchema;
    uint64_t pvarId;
    uint64_t pvarValue;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_SetValue(IWICMetadataWriter *iface, const PROPVARIANT *pvarSchema, const PROPVARIANT *pvarId, const PROPVARIANT *pvarValue)
{
    struct qemu_MetadataHandler_SetValue call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICMetadataWriter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_SETVALUE);
    call.iface = (ULONG_PTR)handler;
    call.pvarSchema = (ULONG_PTR)pvarSchema;
    call.pvarId = (ULONG_PTR)pvarId;
    call.pvarValue = (ULONG_PTR)pvarValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_SetValue(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_SetValue *c = (struct qemu_MetadataHandler_SetValue *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataWriter_SetValue(handler->host_writer, QEMU_G2H(c->pvarSchema), QEMU_G2H(c->pvarId), QEMU_G2H(c->pvarValue));
}

#endif

struct qemu_MetadataHandler_SetValueByIndex
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t nIndex;
    uint64_t pvarSchema;
    uint64_t pvarId;
    uint64_t pvarValue;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_SetValueByIndex(IWICMetadataWriter *iface, UINT nIndex, const PROPVARIANT *pvarSchema, const PROPVARIANT *pvarId, const PROPVARIANT *pvarValue)
{
    struct qemu_MetadataHandler_SetValueByIndex call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICMetadataWriter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_SETVALUEBYINDEX);
    call.iface = (ULONG_PTR)handler;
    call.nIndex = nIndex;
    call.pvarSchema = (ULONG_PTR)pvarSchema;
    call.pvarId = (ULONG_PTR)pvarId;
    call.pvarValue = (ULONG_PTR)pvarValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_SetValueByIndex(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_SetValueByIndex *c = (struct qemu_MetadataHandler_SetValueByIndex *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataWriter_SetValueByIndex(handler->host_writer, c->nIndex, QEMU_G2H(c->pvarSchema), QEMU_G2H(c->pvarId), QEMU_G2H(c->pvarValue));
}

#endif

struct qemu_MetadataHandler_RemoveValue
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pvarSchema;
    uint64_t pvarId;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_RemoveValue(IWICMetadataWriter *iface, const PROPVARIANT *pvarSchema, const PROPVARIANT *pvarId)
{
    struct qemu_MetadataHandler_RemoveValue call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICMetadataWriter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_REMOVEVALUE);
    call.iface = (ULONG_PTR)handler;
    call.pvarSchema = (ULONG_PTR)pvarSchema;
    call.pvarId = (ULONG_PTR)pvarId;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_RemoveValue(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_RemoveValue *c = (struct qemu_MetadataHandler_RemoveValue *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataWriter_RemoveValue(handler->host_writer, QEMU_G2H(c->pvarSchema), QEMU_G2H(c->pvarId));
}

#endif

struct qemu_MetadataHandler_RemoveValueByIndex
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t nIndex;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_RemoveValueByIndex(IWICMetadataWriter *iface, UINT nIndex)
{
    struct qemu_MetadataHandler_RemoveValueByIndex call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICMetadataWriter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_REMOVEVALUEBYINDEX);
    call.iface = (ULONG_PTR)handler;
    call.nIndex = nIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_RemoveValueByIndex(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_RemoveValueByIndex *c = (struct qemu_MetadataHandler_RemoveValueByIndex *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataWriter_RemoveValueByIndex(handler->host_writer, c->nIndex);
}

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_PersistStream_QueryInterface(IWICPersistStream *iface,
    REFIID iid, void **ppv)
{
    struct qemu_wic_metadata_handler *handler = impl_from_IWICPersistStream(iface);
    return IWICMetadataWriter_QueryInterface(&handler->IWICMetadataWriter_iface, iid, ppv);
}

static ULONG WINAPI MetadataHandler_PersistStream_AddRef(IWICPersistStream *iface)
{
    struct qemu_wic_metadata_handler *handler = impl_from_IWICPersistStream(iface);
    return IWICMetadataWriter_AddRef(&handler->IWICMetadataWriter_iface);
}

static ULONG WINAPI MetadataHandler_PersistStream_Release(IWICPersistStream *iface)
{
    struct qemu_wic_metadata_handler *handler = impl_from_IWICPersistStream(iface);
    return IWICMetadataWriter_Release(&handler->IWICMetadataWriter_iface);
}

#endif

struct qemu_MetadataHandler_GetClassID
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pClassID;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_GetClassID(IWICPersistStream *iface, CLSID *pClassID)
{
    struct qemu_MetadataHandler_GetClassID call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICPersistStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_GETCLASSID);
    call.iface = (ULONG_PTR)handler;
    call.pClassID = (ULONG_PTR)pClassID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_GetClassID(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_GetClassID *c = (struct qemu_MetadataHandler_GetClassID *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICPersistStream_GetClassID(handler->host_stream, QEMU_G2H(c->pClassID));
}

#endif

struct qemu_MetadataHandler_IsDirty
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_IsDirty(IWICPersistStream *iface)
{
    struct qemu_MetadataHandler_IsDirty call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICPersistStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_ISDIRTY);
    call.iface = (ULONG_PTR)handler;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_IsDirty(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_IsDirty *c = (struct qemu_MetadataHandler_IsDirty *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICPersistStream_IsDirty(handler->host_stream);
}

#endif

struct qemu_MetadataHandler_Load
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pStm;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_Load(IWICPersistStream *iface, IStream *pStm)
{
    struct qemu_MetadataHandler_Load call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICPersistStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_LOAD);
    call.iface = (ULONG_PTR)handler;
    call.pStm = (ULONG_PTR)pStm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_Load(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_Load *c = (struct qemu_MetadataHandler_Load *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICPersistStream_Load(handler->host_stream, QEMU_G2H(c->pStm));
}

#endif

struct qemu_MetadataHandler_Save
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pStm;
    uint64_t fClearDirty;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_Save(IWICPersistStream *iface, IStream *pStm, BOOL fClearDirty)
{
    struct qemu_MetadataHandler_Save call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICPersistStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_SAVE);
    call.iface = (ULONG_PTR)handler;
    call.pStm = (ULONG_PTR)pStm;
    call.fClearDirty = fClearDirty;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_Save(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_Save *c = (struct qemu_MetadataHandler_Save *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICPersistStream_Save(handler->host_stream, QEMU_G2H(c->pStm), c->fClearDirty);
}

#endif

struct qemu_MetadataHandler_GetSizeMax
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pcbSize;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_GetSizeMax(IWICPersistStream *iface, ULARGE_INTEGER *pcbSize)
{
    struct qemu_MetadataHandler_GetSizeMax call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICPersistStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_GETSIZEMAX);
    call.iface = (ULONG_PTR)handler;
    call.pcbSize = (ULONG_PTR)pcbSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_GetSizeMax(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_GetSizeMax *c = (struct qemu_MetadataHandler_GetSizeMax *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICPersistStream_GetSizeMax(handler->host_stream, QEMU_G2H(c->pcbSize));
}

#endif

struct qemu_MetadataHandler_LoadEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIStream;
    uint64_t pguidPreferredVendor;
    uint64_t dwPersistOptions;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_LoadEx(IWICPersistStream *iface, IStream *pIStream,
        const GUID *pguidPreferredVendor, DWORD dwPersistOptions)
{
    struct qemu_MetadataHandler_LoadEx call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICPersistStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_LOADEX);
    call.iface = (ULONG_PTR)handler;
    call.pIStream = (ULONG_PTR)pIStream;
    call.pguidPreferredVendor = (ULONG_PTR)pguidPreferredVendor;
    call.dwPersistOptions = dwPersistOptions;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_LoadEx(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_LoadEx *c = (struct qemu_MetadataHandler_LoadEx *)call;
    struct qemu_wic_metadata_handler *handler;
    struct qemu_component_factory *factory;
    struct istream_wrapper *stream;
    stream = istream_wrapper_create(c->pIStream);

    WINE_TRACE("\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICPersistStream_LoadEx(handler->host_stream, istream_wrapper_host_iface(stream),
            QEMU_G2H(c->pguidPreferredVendor), c->dwPersistOptions);

    if (stream)
        IStream_Release(istream_wrapper_host_iface(stream));
}

#endif

struct qemu_MetadataHandler_SaveEx
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIStream;
    uint64_t dwPersistOptions;
    uint64_t fClearDirty;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI MetadataHandler_SaveEx(IWICPersistStream *iface, IStream *pIStream, DWORD dwPersistOptions, BOOL fClearDirty)
{
    struct qemu_MetadataHandler_SaveEx call;
    struct qemu_wic_metadata_handler *handler = impl_from_IWICPersistStream(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_SAVEEX);
    call.iface = (ULONG_PTR)handler;
    call.pIStream = (ULONG_PTR)pIStream;
    call.dwPersistOptions = dwPersistOptions;
    call.fClearDirty = fClearDirty;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_MetadataHandler_SaveEx(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_SaveEx *c = (struct qemu_MetadataHandler_SaveEx *)call;
    struct qemu_wic_metadata_handler *handler;

    WINE_FIXME("Unverified!\n");
    handler = QEMU_G2H(c->iface);

    c->super.iret = IWICPersistStream_SaveEx(handler->host_stream, QEMU_G2H(c->pIStream), c->dwPersistOptions, c->fClearDirty);
}

#endif

struct qemu_WICEnumMetadataItem_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_metadata_enum *impl_from_IWICEnumMetadataItem(IWICEnumMetadataItem *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_metadata_enum, IWICEnumMetadataItem_iface);
}

static HRESULT WINAPI WICEnumMetadataItem_QueryInterface(IWICEnumMetadataItem *iface, REFIID iid, void **ppv)
{
    struct qemu_WICEnumMetadataItem_QueryInterface call;
    struct qemu_wic_metadata_enum *item = impl_from_IWICEnumMetadataItem(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICENUMMETADATAITEM_QUERYINTERFACE);
    call.iface = (ULONG_PTR)item;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICEnumMetadataItem_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICEnumMetadataItem_QueryInterface *c = (struct qemu_WICEnumMetadataItem_QueryInterface *)call;
    struct qemu_wic_metadata_enum *item;

    WINE_FIXME("Unverified!\n");
    item = QEMU_G2H(c->iface);

    c->super.iret = IWICEnumMetadataItem_QueryInterface(item->host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_WICEnumMetadataItem_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICEnumMetadataItem_AddRef(IWICEnumMetadataItem *iface)
{
    struct qemu_WICEnumMetadataItem_AddRef call;
    struct qemu_wic_metadata_enum *item = impl_from_IWICEnumMetadataItem(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICENUMMETADATAITEM_ADDREF);
    call.iface = (ULONG_PTR)item;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICEnumMetadataItem_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICEnumMetadataItem_AddRef *c = (struct qemu_WICEnumMetadataItem_AddRef *)call;
    struct qemu_wic_metadata_enum *item;

    WINE_TRACE("\n");
    item = QEMU_G2H(c->iface);

    c->super.iret = IWICEnumMetadataItem_AddRef(item->host);
}

#endif

struct qemu_WICEnumMetadataItem_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICEnumMetadataItem_Release(IWICEnumMetadataItem *iface)
{
    struct qemu_WICEnumMetadataItem_Release call;
    struct qemu_wic_metadata_enum *item = impl_from_IWICEnumMetadataItem(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICENUMMETADATAITEM_RELEASE);
    call.iface = (ULONG_PTR)item;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICEnumMetadataItem_Release(struct qemu_syscall *call)
{
    struct qemu_WICEnumMetadataItem_Release *c = (struct qemu_WICEnumMetadataItem_Release *)call;
    struct qemu_wic_metadata_enum *item;

    WINE_TRACE("\n");
    item = QEMU_G2H(c->iface);

    IWICMetadataWriter_AddRef(item->handler->host_writer);
    c->super.iret = IWICEnumMetadataItem_Release(item->host);
    qemu_MetadataHandler_Release_internal(item->handler);

    if (!c->super.iret)
    {
        WINE_TRACE("Destroying metadata item %p for host item %p.\n", item, item->host);
        HeapFree(GetProcessHeap(), 0, item);
    }
}

#endif

struct qemu_WICEnumMetadataItem_Next
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t celt;
    uint64_t rgeltSchema;
    uint64_t rgeltId;
    uint64_t rgeltValue;
    uint64_t pceltFetched;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICEnumMetadataItem_Next(IWICEnumMetadataItem *iface, ULONG celt, PROPVARIANT *rgeltSchema,
        PROPVARIANT *rgeltId, PROPVARIANT *rgeltValue, ULONG *pceltFetched)
{
    struct qemu_WICEnumMetadataItem_Next call;
    struct qemu_wic_metadata_enum *item = impl_from_IWICEnumMetadataItem(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICENUMMETADATAITEM_NEXT);
    call.iface = (ULONG_PTR)item;
    call.celt = celt;
    call.rgeltSchema = (ULONG_PTR)rgeltSchema;
    call.rgeltId = (ULONG_PTR)rgeltId;
    call.rgeltValue = (ULONG_PTR)rgeltValue;
    call.pceltFetched = (ULONG_PTR)pceltFetched;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICEnumMetadataItem_Next(struct qemu_syscall *call)
{
    struct qemu_WICEnumMetadataItem_Next *c = (struct qemu_WICEnumMetadataItem_Next *)call;
    struct qemu_wic_metadata_enum *item;
    PROPVARIANT *schema, *id, *value;
    ULONG *fetched, i;
    struct qemu_PROPVARIANT *schema32, *id32, *value32;

    WINE_TRACE("\n");
    item = QEMU_G2H(c->iface);
    fetched = QEMU_G2H(c->pceltFetched);
#if GUEST_BIT == HOST_BIT
    schema = QEMU_G2H(c->rgeltSchema);
    id = QEMU_G2H(c->rgeltId);
    value = QEMU_G2H(c->rgeltValue);
#else
    schema32 = QEMU_G2H(c->rgeltSchema);
    id32 = QEMU_G2H(c->rgeltId);
    value32 = QEMU_G2H(c->rgeltValue);

    if (schema32)
    {
        schema = HeapAlloc(GetProcessHeap(), 0, c->celt * sizeof(*schema));
        if (!schema)
        {
            WINE_WARN("Out of memory\n");
            c->super.iret = E_OUTOFMEMORY;
            return;
        }

        for (i = 0; i < c->celt; ++i)
            PROPVARIANT_g2h(&schema[i], &schema32[i]);
    }
    else
        schema = NULL;

    if (id32)
    {
        id = HeapAlloc(GetProcessHeap(), 0, c->celt * sizeof(*id));
        if (!id)
        {
            WINE_WARN("Out of memory\n");
            HeapFree(GetProcessHeap(), 0, schema);
            c->super.iret = E_OUTOFMEMORY;
            return;
        }

        for (i = 0; i < c->celt; ++i)
            PROPVARIANT_g2h(&id[i], &id32[i]);
    }
    else
        id = NULL;

    if (value32)
    {
        value = HeapAlloc(GetProcessHeap(), 0, c->celt * sizeof(*value));
        if (!value)
        {
            WINE_WARN("Out of memory\n");
            HeapFree(GetProcessHeap(), 0, schema);
            HeapFree(GetProcessHeap(), 0, id);
            c->super.iret = E_OUTOFMEMORY;
            return;
        }

        for (i = 0; i < c->celt; ++i)
            PROPVARIANT_g2h(&value[i], &value32[i]);
    }
    else
        value = NULL;
#endif

    c->super.iret = IWICEnumMetadataItem_Next(item->host, c->celt, schema, id, value, fetched);

    if (WINE_FIXME_ON(qemu_wic) && SUCCEEDED(c->super.iret))
    {
        for (i = 0; i < *fetched; ++i)
        {
            if (schema[i].vt == VT_UNKNOWN || id[i].vt == VT_UNKNOWN || value[i].vt == VT_UNKNOWN)
                WINE_FIXME("Handle VT_UNKNOWN\n");
        }
    }

#if GUEST_BIT != HOST_BIT
    if (SUCCEEDED(c->super.iret))
    {
        for (i = 0; i < *fetched; ++i)
        {
            PROPVARIANT_h2g(&schema32[i], &schema[i]);
            PROPVARIANT_h2g(&id32[i], &id[i]);
            PROPVARIANT_h2g(&value32[i], &value[i]);
        }
    }
    HeapFree(GetProcessHeap(), 0, schema);
    HeapFree(GetProcessHeap(), 0, id);
    HeapFree(GetProcessHeap(), 0, value);
#endif
}

#endif

struct qemu_WICEnumMetadataItem_Skip
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t celt;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICEnumMetadataItem_Skip(IWICEnumMetadataItem *iface, ULONG celt)
{
    struct qemu_WICEnumMetadataItem_Skip call;
    struct qemu_wic_metadata_enum *item = impl_from_IWICEnumMetadataItem(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICENUMMETADATAITEM_SKIP);
    call.iface = (ULONG_PTR)item;
    call.celt = celt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICEnumMetadataItem_Skip(struct qemu_syscall *call)
{
    struct qemu_WICEnumMetadataItem_Skip *c = (struct qemu_WICEnumMetadataItem_Skip *)call;
    struct qemu_wic_metadata_enum *item;

    WINE_FIXME("Unverified!\n");
    item = QEMU_G2H(c->iface);

    c->super.iret = IWICEnumMetadataItem_Skip(item->host, c->celt);
}

#endif

struct qemu_WICEnumMetadataItem_Reset
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICEnumMetadataItem_Reset(IWICEnumMetadataItem *iface)
{
    struct qemu_WICEnumMetadataItem_Reset call;
    struct qemu_wic_metadata_enum *item = impl_from_IWICEnumMetadataItem(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICENUMMETADATAITEM_RESET);
    call.iface = (ULONG_PTR)item;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICEnumMetadataItem_Reset(struct qemu_syscall *call)
{
    struct qemu_WICEnumMetadataItem_Reset *c = (struct qemu_WICEnumMetadataItem_Reset *)call;
    struct qemu_wic_metadata_enum *item;

    WINE_FIXME("Unverified!\n");
    item = QEMU_G2H(c->iface);

    c->super.iret = IWICEnumMetadataItem_Reset(item->host);
}

#endif

struct qemu_WICEnumMetadataItem_Clone
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIEnumMetadataItem;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICEnumMetadataItem_Clone(IWICEnumMetadataItem *iface, IWICEnumMetadataItem **ppIEnumMetadataItem)
{
    struct qemu_WICEnumMetadataItem_Clone call;
    struct qemu_wic_metadata_enum *item = impl_from_IWICEnumMetadataItem(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICENUMMETADATAITEM_CLONE);
    call.iface = (ULONG_PTR)item;
    call.ppIEnumMetadataItem = (ULONG_PTR)ppIEnumMetadataItem;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICEnumMetadataItem_Clone(struct qemu_syscall *call)
{
    struct qemu_WICEnumMetadataItem_Clone *c = (struct qemu_WICEnumMetadataItem_Clone *)call;
    struct qemu_wic_metadata_enum *item;

    WINE_FIXME("Unverified!\n");
    item = QEMU_G2H(c->iface);

    c->super.iret = IWICEnumMetadataItem_Clone(item->host, QEMU_G2H(c->ppIEnumMetadataItem));
}

#endif

struct qemu_MetadataHandler_create_host
{
    struct qemu_syscall super;
    uint64_t clsid;
    uint64_t handler;
};

#ifdef QEMU_DLL_GUEST

static const IWICMetadataWriterVtbl MetadataHandler_Vtbl = {
    MetadataHandler_QueryInterface,
    MetadataHandler_AddRef,
    MetadataHandler_Release,
    MetadataHandler_GetMetadataFormat,
    MetadataHandler_GetMetadataHandlerInfo,
    MetadataHandler_GetCount,
    MetadataHandler_GetValueByIndex,
    MetadataHandler_GetValue,
    MetadataHandler_GetEnumerator,
    MetadataHandler_SetValue,
    MetadataHandler_SetValueByIndex,
    MetadataHandler_RemoveValue,
    MetadataHandler_RemoveValueByIndex
};

static const IWICPersistStreamVtbl MetadataHandler_PersistStream_Vtbl =
{
    MetadataHandler_PersistStream_QueryInterface,
    MetadataHandler_PersistStream_AddRef,
    MetadataHandler_PersistStream_Release,
    MetadataHandler_GetClassID,
    MetadataHandler_IsDirty,
    MetadataHandler_Load,
    MetadataHandler_Save,
    MetadataHandler_GetSizeMax,
    MetadataHandler_LoadEx,
    MetadataHandler_SaveEx
};

static void MetadataHandler_init_guest(struct qemu_wic_metadata_handler *handler)
{
    handler->IWICMetadataWriter_iface.lpVtbl = &MetadataHandler_Vtbl;
    handler->IWICPersistStream_iface.lpVtbl = &MetadataHandler_PersistStream_Vtbl;
}

HRESULT MetadataReader_CreateInstance(const CLSID *clsid, const IID *iid, void **obj)
{
    struct qemu_MetadataHandler_create_host call;
    struct qemu_wic_metadata_handler *handler;
    HRESULT hr;

    WINE_TRACE("(%s,%p)\n", wine_dbgstr_guid(iid), obj);

    *obj = NULL;
    call.super.id = QEMU_SYSCALL_ID(CALL_METADATAHANDLER_CREATE_HOST);
    call.clsid = (ULONG_PTR)clsid;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
        return call.super.iret;

    handler = (struct qemu_wic_metadata_handler *)(ULONG_PTR)call.handler;
    MetadataHandler_init_guest(handler);

    hr = IWICMetadataWriter_QueryInterface(&handler->IWICMetadataWriter_iface, iid, obj);
    IWICMetadataWriter_Release(&handler->IWICMetadataWriter_iface);

    return hr;
}

static const IWICEnumMetadataItemVtbl WICEnumMetadataItem_Vtbl =
{
    WICEnumMetadataItem_QueryInterface,
    WICEnumMetadataItem_AddRef,
    WICEnumMetadataItem_Release,
    WICEnumMetadataItem_Next,
    WICEnumMetadataItem_Skip,
    WICEnumMetadataItem_Reset,
    WICEnumMetadataItem_Clone
};

static void WICEnumMetadataItem_init_guest(struct qemu_wic_metadata_enum *item)
{
    item->IWICEnumMetadataItem_iface.lpVtbl = &WICEnumMetadataItem_Vtbl;
}

#else

static struct qemu_wic_metadata_handler *MetadataHandler_create_host(IWICMetadataReader *host)
{
    struct qemu_wic_metadata_handler *ret;
    HRESULT hr;
    IWICMetadataWriter *writer;

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
    {
        WINE_WARN("Out of memory\n");
        return NULL;
    }

    hr = IWICMetadataReader_QueryInterface(host, &IID_IWICPersistStream, (void **)&ret->host_stream);
    if (FAILED(hr))
        WINE_ERR("Failed to QI IWICPeristStream.\n");
    IWICPersistStream_Release(ret->host_stream);

    hr = IWICMetadataReader_QueryInterface(host, &IID_IWICMetadataWriter, (void **)&writer);
    if (SUCCEEDED(hr))
    {
        if (host != (IWICMetadataReader *)writer)
            WINE_FIXME("IWICMetadataReader != IWICMetadataWriter.\n");

        IWICMetadataReader_Release(host);
        ret->host_writer = writer;
    }
    else
    {
        ret->host_writer = (IWICMetadataWriter *)host;
    }

    return ret;
}

void qemu_MetadataHandler_create_host(struct qemu_syscall *call)
{
    struct qemu_MetadataHandler_create_host *c = (struct qemu_MetadataHandler_create_host *)call;
    struct qemu_wic_metadata_handler *handler;
    HMODULE lib;
    HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **obj);
    IClassFactory *host_factory;
    HRESULT hr;
    IWICMetadataReader *host;

    lib = GetModuleHandleA("windowscodecs");
    p_DllGetClassObject = (void *)GetProcAddress(lib, "DllGetClassObject");

    hr = p_DllGetClassObject(QEMU_G2H(c->clsid), &IID_IClassFactory, (void *)&host_factory);
    if (FAILED(hr))
        WINE_ERR("Cannot create class factory\n");

    hr = IClassFactory_CreateInstance(host_factory, NULL, &IID_IWICMetadataReader, (void **)&host);
    IClassFactory_Release(host_factory);
    if (FAILED(hr))
    {
        WINE_WARN("Failed to create an IID_IWICMetadataWriter object.\n");
        c->super.iret = hr;
        return;
    }

    handler = MetadataHandler_create_host(host);
    if (!handler)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->handler = QEMU_H2G(handler);
    c->super.iret = hr;
}

#endif
