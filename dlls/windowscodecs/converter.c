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


struct qemu_WICFormatConverter_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICFormatConverter_QueryInterface(IWICFormatConverter *iface, REFIID iid, void **ppv)
{
    struct qemu_WICFormatConverter_QueryInterface call;
    struct qemu_wic_converter *converter = impl_from_IWICFormatConverter(iface);

    WINE_TRACE("(%p,%s,%p)\n", iface, wine_dbgstr_guid(iid), ppv);

    if (!ppv)
        return E_INVALIDARG;

    if (IsEqualIID(&IID_IUnknown, iid)
            || IsEqualIID(&IID_IWICBitmapSource, iid)
            || IsEqualIID(&IID_IWICFormatConverter, iid))
    {
        *ppv = &converter->IWICFormatConverter_iface;
        IUnknown_AddRef((IUnknown*)*ppv);
        return S_OK;
    }

    call.super.id = QEMU_SYSCALL_ID(CALL_WICFORMATCONVERTER_QUERYINTERFACE);
    call.iface = (ULONG_PTR)converter;
    call.iid = (ULONG_PTR)iid;

    qemu_syscall(&call.super);

    *ppv = NULL;
    return E_NOINTERFACE;
}

#else

void qemu_WICFormatConverter_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICFormatConverter_QueryInterface *c = (struct qemu_WICFormatConverter_QueryInterface *)call;
    struct qemu_wic_converter *converter;
    IUnknown *obj;

    WINE_TRACE("\n");
    converter = QEMU_G2H(c->iface);

    c->super.iret = IWICFormatConverter_QueryInterface(converter->host, QEMU_G2H(c->iid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->iid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_WICFormatConverter_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICFormatConverter_AddRef(IWICFormatConverter *iface)
{
    struct qemu_WICFormatConverter_AddRef call;
    struct qemu_wic_converter *converter = impl_from_IWICFormatConverter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICFORMATCONVERTER_ADDREF);
    call.iface = (ULONG_PTR)converter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICFormatConverter_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICFormatConverter_AddRef *c = (struct qemu_WICFormatConverter_AddRef *)call;
    struct qemu_wic_converter *converter;

    WINE_TRACE("\n");
    converter = QEMU_G2H(c->iface);

    c->super.iret = IWICFormatConverter_AddRef(converter->host);
}

#endif

struct qemu_WICFormatConverter_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICFormatConverter_Release(IWICFormatConverter *iface)
{
    struct qemu_WICFormatConverter_Release call;
    struct qemu_wic_converter *converter = impl_from_IWICFormatConverter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICFORMATCONVERTER_RELEASE);
    call.iface = (ULONG_PTR)converter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

ULONG qemu_WICFormatConverter_Release_internal(struct qemu_wic_converter *converter)
{
    ULONG ref;

    if (converter->source_clipper)
        IWICBitmapClipper_AddRef(converter->source_clipper->host);
    else if (converter->source_bitmap)
        IWICBitmap_AddRef(converter->source_bitmap->bitmap_host);
    else if (converter->source_converter)
        IWICFormatConverter_AddRef(converter->source_converter->host);

    ref = IWICFormatConverter_Release(converter->host);

    if (converter->source_clipper)
        qemu_WICBitmapClipper_Release_internal(converter->source_clipper);
    else if (converter->source_bitmap)
        qemu_WICBitmap_Release_internal(converter->source_bitmap);
    else if (converter->source_converter)
        qemu_WICFormatConverter_Release_internal(converter->source_converter);

    if (!ref)
    {
        WINE_TRACE("Destroying converter wrapper %p for host converter %p.\n", converter, converter->host);
        HeapFree(GetProcessHeap(), 0, converter);
    }

    return ref;
}

void qemu_WICFormatConverter_Release(struct qemu_syscall *call)
{
    struct qemu_WICFormatConverter_Release *c = (struct qemu_WICFormatConverter_Release *)call;
    struct qemu_wic_converter *converter;

    WINE_TRACE("\n");
    converter = QEMU_G2H(c->iface);

    c->super.iret = qemu_WICFormatConverter_Release_internal(converter);
}

#endif

struct qemu_WICFormatConverter_GetSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t puiWidth;
    uint64_t puiHeight;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICFormatConverter_GetSize(IWICFormatConverter *iface, UINT *puiWidth, UINT *puiHeight)
{
    struct qemu_WICFormatConverter_GetSize call;
    struct qemu_wic_converter *converter = impl_from_IWICFormatConverter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICFORMATCONVERTER_GETSIZE);
    call.iface = (ULONG_PTR)converter;
    call.puiWidth = (ULONG_PTR)puiWidth;
    call.puiHeight = (ULONG_PTR)puiHeight;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICFormatConverter_GetSize(struct qemu_syscall *call)
{
    struct qemu_WICFormatConverter_GetSize *c = (struct qemu_WICFormatConverter_GetSize *)call;
    struct qemu_wic_converter *converter;

    WINE_TRACE("\n");
    converter = QEMU_G2H(c->iface);

    c->super.iret = IWICFormatConverter_GetSize(converter->host, QEMU_G2H(c->puiWidth), QEMU_G2H(c->puiHeight));
}

#endif

struct qemu_WICFormatConverter_GetPixelFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pPixelFormat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICFormatConverter_GetPixelFormat(IWICFormatConverter *iface, WICPixelFormatGUID *pPixelFormat)
{
    struct qemu_WICFormatConverter_GetPixelFormat call;
    struct qemu_wic_converter *converter = impl_from_IWICFormatConverter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICFORMATCONVERTER_GETPIXELFORMAT);
    call.iface = (ULONG_PTR)converter;
    call.pPixelFormat = (ULONG_PTR)pPixelFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICFormatConverter_GetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_WICFormatConverter_GetPixelFormat *c = (struct qemu_WICFormatConverter_GetPixelFormat *)call;
    struct qemu_wic_converter *converter;

    WINE_TRACE("\n");
    converter = QEMU_G2H(c->iface);

    c->super.iret = IWICFormatConverter_GetPixelFormat(converter->host, QEMU_G2H(c->pPixelFormat));
}

#endif

struct qemu_WICFormatConverter_GetResolution
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pDpiX;
    uint64_t pDpiY;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICFormatConverter_GetResolution(IWICFormatConverter *iface, double *pDpiX, double *pDpiY)
{
    struct qemu_WICFormatConverter_GetResolution call;
    struct qemu_wic_converter *converter = impl_from_IWICFormatConverter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICFORMATCONVERTER_GETRESOLUTION);
    call.iface = (ULONG_PTR)converter;
    call.pDpiX = (ULONG_PTR)pDpiX;
    call.pDpiY = (ULONG_PTR)pDpiY;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICFormatConverter_GetResolution(struct qemu_syscall *call)
{
    struct qemu_WICFormatConverter_GetResolution *c = (struct qemu_WICFormatConverter_GetResolution *)call;
    struct qemu_wic_converter *converter;

    WINE_TRACE("\n");
    converter = QEMU_G2H(c->iface);

    c->super.iret = IWICFormatConverter_GetResolution(converter->host, QEMU_G2H(c->pDpiX), QEMU_G2H(c->pDpiY));
}

#endif

struct qemu_WICFormatConverter_CopyPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIPalette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICFormatConverter_CopyPalette(IWICFormatConverter *iface, IWICPalette *pIPalette)
{
    struct qemu_WICFormatConverter_CopyPalette call;
    struct qemu_wic_converter *converter = impl_from_IWICFormatConverter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICFORMATCONVERTER_COPYPALETTE);
    call.iface = (ULONG_PTR)converter;
    call.pIPalette = (ULONG_PTR)pIPalette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICFormatConverter_CopyPalette(struct qemu_syscall *call)
{
    struct qemu_WICFormatConverter_CopyPalette *c = (struct qemu_WICFormatConverter_CopyPalette *)call;
    struct qemu_wic_converter *converter;

    WINE_FIXME("Unverified!\n");
    converter = QEMU_G2H(c->iface);

    c->super.iret = IWICFormatConverter_CopyPalette(converter->host, QEMU_G2H(c->pIPalette));
}

#endif

struct qemu_WICFormatConverter_CopyPixels
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t prc;
    uint64_t cbStride;
    uint64_t cbBufferSize;
    uint64_t pbBuffer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICFormatConverter_CopyPixels(IWICFormatConverter *iface, const WICRect *prc, UINT cbStride,
        UINT cbBufferSize, BYTE *pbBuffer)
{
    struct qemu_WICFormatConverter_CopyPixels call;
    struct qemu_wic_converter *converter = impl_from_IWICFormatConverter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICFORMATCONVERTER_COPYPIXELS);
    call.iface = (ULONG_PTR)converter;
    call.prc = (ULONG_PTR)prc;
    call.cbStride = cbStride;
    call.cbBufferSize = cbBufferSize;
    call.pbBuffer = (ULONG_PTR)pbBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICFormatConverter_CopyPixels(struct qemu_syscall *call)
{
    struct qemu_WICFormatConverter_CopyPixels *c = (struct qemu_WICFormatConverter_CopyPixels *)call;
    struct qemu_wic_converter *converter;

    WINE_TRACE("\n");
    converter = QEMU_G2H(c->iface);

    c->super.iret = IWICFormatConverter_CopyPixels(converter->host, QEMU_G2H(c->prc), c->cbStride, c->cbBufferSize,
            QEMU_G2H(c->pbBuffer));
}

#endif

struct qemu_WICFormatConverter_Initialize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pISource;
    uint64_t dstFormat;
    uint64_t dither;
    uint64_t pIPalette;
    uint64_t alphaThresholdPercent;
    uint64_t paletteTranslate;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICFormatConverter_Initialize(IWICFormatConverter *iface, IWICBitmapSource *pISource,
        REFWICPixelFormatGUID dstFormat, WICBitmapDitherType dither, IWICPalette *pIPalette,
        double alphaThresholdPercent, WICBitmapPaletteType paletteTranslate)
{
    struct qemu_WICFormatConverter_Initialize call;
    struct qemu_wic_converter *converter = impl_from_IWICFormatConverter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICFORMATCONVERTER_INITIALIZE);
    call.iface = (ULONG_PTR)converter;
    call.pISource = (ULONG_PTR)pISource;
    call.dstFormat = (ULONG_PTR)dstFormat;
    call.dither = dither;
    call.pIPalette = (ULONG_PTR)pIPalette;
    call.alphaThresholdPercent = alphaThresholdPercent;
    call.paletteTranslate = paletteTranslate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICFormatConverter_Initialize(struct qemu_syscall *call)
{
    struct qemu_WICFormatConverter_Initialize *c = (struct qemu_WICFormatConverter_Initialize *)call;
    struct qemu_wic_converter *converter;

    WINE_FIXME("Unverified!\n");
    converter = QEMU_G2H(c->iface);

    c->super.iret = IWICFormatConverter_Initialize(converter->host, QEMU_G2H(c->pISource), QEMU_G2H(c->dstFormat),
            c->dither, QEMU_G2H(c->pIPalette), c->alphaThresholdPercent, c->paletteTranslate);
}

#endif

struct qemu_WICFormatConverter_CanConvert
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t srcPixelFormat;
    uint64_t dstPixelFormat;
    uint64_t pfCanConvert;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICFormatConverter_CanConvert(IWICFormatConverter *iface, REFWICPixelFormatGUID srcPixelFormat,
        REFWICPixelFormatGUID dstPixelFormat, BOOL *pfCanConvert)
{
    struct qemu_WICFormatConverter_CanConvert call;
    struct qemu_wic_converter *converter = impl_from_IWICFormatConverter(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICFORMATCONVERTER_CANCONVERT);
    call.iface = (ULONG_PTR)converter;
    call.srcPixelFormat = (ULONG_PTR)srcPixelFormat;
    call.dstPixelFormat = (ULONG_PTR)dstPixelFormat;
    call.pfCanConvert = (ULONG_PTR)pfCanConvert;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICFormatConverter_CanConvert(struct qemu_syscall *call)
{
    struct qemu_WICFormatConverter_CanConvert *c = (struct qemu_WICFormatConverter_CanConvert *)call;
    struct qemu_wic_converter *converter;

    WINE_TRACE("\n");
    converter = QEMU_G2H(c->iface);

    c->super.iret = IWICFormatConverter_CanConvert(converter->host, QEMU_G2H(c->srcPixelFormat),
            QEMU_G2H(c->dstPixelFormat), QEMU_G2H(c->pfCanConvert));
}

#endif

struct qemu_WICFormatConverter_create_host
{
    struct qemu_syscall super;
    uint64_t clsid;
    uint64_t converter;
};

#ifdef QEMU_DLL_GUEST

const IWICFormatConverterVtbl WICFormatConverter_Vtbl =
{
    WICFormatConverter_QueryInterface,
    WICFormatConverter_AddRef,
    WICFormatConverter_Release,
    WICFormatConverter_GetSize,
    WICFormatConverter_GetPixelFormat,
    WICFormatConverter_GetResolution,
    WICFormatConverter_CopyPalette,
    WICFormatConverter_CopyPixels,
    WICFormatConverter_Initialize,
    WICFormatConverter_CanConvert
};

void WICFormatConverter_init_guest(struct qemu_wic_converter *converter)
{
    converter->IWICFormatConverter_iface.lpVtbl = &WICFormatConverter_Vtbl;
}

HRESULT FormatConverter_CreateInstance(const CLSID *clsid, const IID *iid, void **obj)
{
    struct qemu_WICFormatConverter_create_host call;
    struct qemu_wic_converter *converter;
    HRESULT hr;

    WINE_TRACE("(%s,%p)\n", wine_dbgstr_guid(iid), obj);

    *obj = NULL;
    call.super.id = QEMU_SYSCALL_ID(CALL_WICFORMATCONVERTER_CREATE_HOST);
    call.clsid = (ULONG_PTR)clsid;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
        return call.super.iret;

    converter = (struct qemu_wic_converter *)(ULONG_PTR)call.converter;
    WICFormatConverter_init_guest(converter);

    hr = IWICFormatConverter_QueryInterface(&converter->IWICFormatConverter_iface, iid, obj);
    IWICFormatConverter_Release(&converter->IWICFormatConverter_iface);

    return hr;
}

#else

struct qemu_wic_converter *WICFormatConverter_create_host(IWICBitmapSource *host)
{
    struct qemu_wic_converter *ret;
    HRESULT hr;

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
    {
        WINE_WARN("Out of memory\n");
        return NULL;
    }

    hr = IWICBitmapSource_QueryInterface(host, &IID_IWICFormatConverter, (void **)&ret->host);
    if (FAILED(hr))
        WINE_ERR("Failed to QI IWICFormatConverter.\n");
    /* Keep the refcount at 1. Ok, in theory the caller should release its ref, but consistency with
     * other functions. And OK, the other functions should AddRef and the callers always release. */
    IWICFormatConverter_Release(ret->host);

    return ret;
}

void qemu_WICFormatConverter_create_host(struct qemu_syscall *call)
{
    struct qemu_WICFormatConverter_create_host *c = (struct qemu_WICFormatConverter_create_host *)call;
    struct qemu_wic_converter *converter;
    HMODULE lib;
    HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **obj);
    IClassFactory *host_factory;
    HRESULT hr;
    IWICBitmapSource *host;

    lib = GetModuleHandleA("windowscodecs");
    p_DllGetClassObject = (void *)GetProcAddress(lib, "DllGetClassObject");

    hr = p_DllGetClassObject(QEMU_G2H(c->clsid), &IID_IClassFactory, (void *)&host_factory);
    if (FAILED(hr))
        WINE_ERR("Cannot create class factory\n");

    hr = IClassFactory_CreateInstance(host_factory, NULL, &IID_IWICBitmapSource, (void **)&host);
    IClassFactory_Release(host_factory);
    if (FAILED(hr))
    {
        WINE_WARN("Failed to create an IWICFormatConverter object.\n");
        c->super.iret = hr;
        return;
    }

    converter = WICFormatConverter_create_host(host);
    if (!converter)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->converter = QEMU_H2G(converter);
    c->super.iret = hr;
}

#endif

