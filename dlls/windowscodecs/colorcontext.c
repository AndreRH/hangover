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
#include <assert.h>

#include "windows-user-services.h"
#include "dll_list.h"

#include <wine/debug.h>
#include <wine/list.h>

#include "qemu_windowscodecs.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_wic);

struct qemu_WICColorContext_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_color_context *impl_from_IWICColorContext(IWICColorContext *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_color_context, IWICColorContext_iface);
}

static HRESULT WINAPI WICColorContext_QueryInterface(IWICColorContext *iface, REFIID iid, void **ppv)
{
    struct qemu_WICColorContext_QueryInterface call;
    struct qemu_wic_color_context *context = impl_from_IWICColorContext(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOLORCONTEXT_QUERYINTERFACE);
    call.iface = (ULONG_PTR)iface;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICColorContext_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICColorContext_QueryInterface *c = (struct qemu_WICColorContext_QueryInterface *)call;
    struct qemu_wic_color_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = IWICColorContext_QueryInterface(context->host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_WICColorContext_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICColorContext_AddRef(IWICColorContext *iface)
{
    struct qemu_WICColorContext_AddRef call;
    struct qemu_wic_color_context *context = impl_from_IWICColorContext(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOLORCONTEXT_ADDREF);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICColorContext_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICColorContext_AddRef *c = (struct qemu_WICColorContext_AddRef *)call;
    struct qemu_wic_color_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = IWICColorContext_AddRef(context->host);
}

#endif

struct qemu_WICColorContext_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICColorContext_Release(IWICColorContext *iface)
{
    struct qemu_WICColorContext_Release call;
    struct qemu_wic_color_context *context = impl_from_IWICColorContext(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOLORCONTEXT_RELEASE);
    call.iface = (ULONG_PTR)iface;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICColorContext_Release(struct qemu_syscall *call)
{
    struct qemu_WICColorContext_Release *c = (struct qemu_WICColorContext_Release *)call;
    struct qemu_wic_color_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = IWICColorContext_Release(context->host);
    if (!c->super.iret)
    {
        WINE_TRACE("Destroying color context wrapper %p for host context %p.\n", context, context->host);
        HeapFree(GetProcessHeap(), 0, context);
    }
}

#endif

struct qemu_WICColorContext_InitializeFromFilename
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t wzFilename;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICColorContext_InitializeFromFilename(IWICColorContext *iface, LPCWSTR wzFilename)
{
    struct qemu_WICColorContext_InitializeFromFilename call;
    struct qemu_wic_color_context *context = impl_from_IWICColorContext(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOLORCONTEXT_INITIALIZEFROMFILENAME);
    call.iface = (ULONG_PTR)iface;
    call.wzFilename = (ULONG_PTR)wzFilename;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICColorContext_InitializeFromFilename(struct qemu_syscall *call)
{
    struct qemu_WICColorContext_InitializeFromFilename *c = (struct qemu_WICColorContext_InitializeFromFilename *)call;
    struct qemu_wic_color_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = IWICColorContext_InitializeFromFilename(context->host, QEMU_G2H(c->wzFilename));
}

#endif

struct qemu_WICColorContext_InitializeFromMemory
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pbBuffer;
    uint64_t cbBufferSize;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICColorContext_InitializeFromMemory(IWICColorContext *iface, const BYTE *pbBuffer, UINT cbBufferSize)
{
    struct qemu_WICColorContext_InitializeFromMemory call;
    struct qemu_wic_color_context *context = impl_from_IWICColorContext(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOLORCONTEXT_INITIALIZEFROMMEMORY);
    call.iface = (ULONG_PTR)iface;
    call.pbBuffer = (ULONG_PTR)pbBuffer;
    call.cbBufferSize = cbBufferSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICColorContext_InitializeFromMemory(struct qemu_syscall *call)
{
    struct qemu_WICColorContext_InitializeFromMemory *c = (struct qemu_WICColorContext_InitializeFromMemory *)call;
    struct qemu_wic_color_context *context;

    WINE_FIXME("Unverified!\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = IWICColorContext_InitializeFromMemory(context->host, QEMU_G2H(c->pbBuffer), c->cbBufferSize);
}

#endif

struct qemu_WICColorContext_InitializeFromExifColorSpace
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICColorContext_InitializeFromExifColorSpace(IWICColorContext *iface, UINT value)
{
    struct qemu_WICColorContext_InitializeFromExifColorSpace call;
    struct qemu_wic_color_context *context = impl_from_IWICColorContext(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOLORCONTEXT_INITIALIZEFROMEXIFCOLORSPACE);
    call.iface = (ULONG_PTR)iface;
    call.value = value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICColorContext_InitializeFromExifColorSpace(struct qemu_syscall *call)
{
    struct qemu_WICColorContext_InitializeFromExifColorSpace *c =
            (struct qemu_WICColorContext_InitializeFromExifColorSpace *)call;
    struct qemu_wic_color_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = IWICColorContext_InitializeFromExifColorSpace(context->host, c->value);
}

#endif

struct qemu_WICColorContext_GetType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pType;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICColorContext_GetType(IWICColorContext *iface, WICColorContextType *pType)
{
    struct qemu_WICColorContext_GetType call;
    struct qemu_wic_color_context *context = impl_from_IWICColorContext(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOLORCONTEXT_GETTYPE);
    call.iface = (ULONG_PTR)iface;
    call.pType = (ULONG_PTR)pType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICColorContext_GetType(struct qemu_syscall *call)
{
    struct qemu_WICColorContext_GetType *c = (struct qemu_WICColorContext_GetType *)call;
    struct qemu_wic_color_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = IWICColorContext_GetType(context->host, QEMU_G2H(c->pType));
}

#endif

struct qemu_WICColorContext_GetProfileBytes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cbBuffer;
    uint64_t pbBuffer;
    uint64_t pcbActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICColorContext_GetProfileBytes(IWICColorContext *iface, UINT cbBuffer,
        BYTE *pbBuffer, UINT *pcbActual)
{
    struct qemu_WICColorContext_GetProfileBytes call;
    struct qemu_wic_color_context *context = impl_from_IWICColorContext(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOLORCONTEXT_GETPROFILEBYTES);
    call.iface = (ULONG_PTR)iface;
    call.cbBuffer = cbBuffer;
    call.pbBuffer = (ULONG_PTR)pbBuffer;
    call.pcbActual = (ULONG_PTR)pcbActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICColorContext_GetProfileBytes(struct qemu_syscall *call)
{
    struct qemu_WICColorContext_GetProfileBytes *c = (struct qemu_WICColorContext_GetProfileBytes *)call;
    struct qemu_wic_color_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = IWICColorContext_GetProfileBytes(context->host, c->cbBuffer, QEMU_G2H(c->pbBuffer),
            QEMU_G2H(c->pcbActual));
}

#endif

struct qemu_WICColorContext_GetExifColorSpace
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pValue;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICColorContext_GetExifColorSpace(IWICColorContext *iface, UINT *pValue)
{
    struct qemu_WICColorContext_GetExifColorSpace call;
    struct qemu_wic_color_context *context = impl_from_IWICColorContext(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOLORCONTEXT_GETEXIFCOLORSPACE);
    call.iface = (ULONG_PTR)iface;
    call.pValue = (ULONG_PTR)pValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICColorContext_GetExifColorSpace(struct qemu_syscall *call)
{
    struct qemu_WICColorContext_GetExifColorSpace *c = (struct qemu_WICColorContext_GetExifColorSpace *)call;
    struct qemu_wic_color_context *context;

    WINE_TRACE("\n");
    context = QEMU_G2H(c->iface);

    c->super.iret = IWICColorContext_GetExifColorSpace(context->host, QEMU_G2H(c->pValue));
}

#endif

#ifdef QEMU_DLL_GUEST

static const IWICColorContextVtbl WICColorContext_Vtbl =
{
    WICColorContext_QueryInterface,
    WICColorContext_AddRef,
    WICColorContext_Release,
    WICColorContext_InitializeFromFilename,
    WICColorContext_InitializeFromMemory,
    WICColorContext_InitializeFromExifColorSpace,
    WICColorContext_GetType,
    WICColorContext_GetProfileBytes,
    WICColorContext_GetExifColorSpace
};

void WICColorContext_init_guest(struct qemu_wic_color_context *context)
{
    context->IWICColorContext_iface.lpVtbl = &WICColorContext_Vtbl;
}

struct qemu_wic_color_context *unsafe_impl_from_IWICColorContext(IWICColorContext *iface)
{
    if (!iface)
        return NULL;

    /* TODO: We might have to be able to deal with custom color context implementations. */
    assert(iface->lpVtbl == &WICColorContext_Vtbl);

    return CONTAINING_RECORD(iface, struct qemu_wic_color_context, IWICColorContext_iface);
}

#else

struct qemu_wic_color_context *WICColorContext_create_host(IWICColorContext *host)
{
    struct qemu_wic_color_context *ret;
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
