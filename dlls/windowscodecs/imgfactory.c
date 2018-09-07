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

struct qemu_component_factory
{
    /* Guest fields */
    IWICComponentFactory IWICComponentFactory_iface;

    /* Host fields */
    IWICComponentFactory *host;
};

struct qemu_ComponentFactory_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_component_factory *impl_from_IWICComponentFactory(IWICComponentFactory *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_component_factory, IWICComponentFactory_iface);
}

static HRESULT WINAPI ComponentFactory_QueryInterface(IWICComponentFactory *iface, REFIID iid, void **ppv)
{
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);
    WINE_TRACE("(%p,%s,%p)\n", iface, wine_dbgstr_guid(iid), ppv);

    if (!ppv)
        return E_INVALIDARG;

    if (IsEqualIID(&IID_IUnknown, iid) ||
            IsEqualIID(&IID_IWICImagingFactory, iid) ||
            IsEqualIID(&IID_IWICComponentFactory, iid))
    {
        *ppv = &factory->IWICComponentFactory_iface;
        IUnknown_AddRef((IUnknown*)*ppv);
        return S_OK;
    }
    *ppv = NULL;


    struct qemu_ComponentFactory_QueryInterface call;

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_QUERYINTERFACE);
    call.iface = (ULONG_PTR)factory;
    call.iid = (ULONG_PTR)iid;

    qemu_syscall(&call.super);

    return E_NOINTERFACE;
}

#else

void qemu_ComponentFactory_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_QueryInterface *c = (struct qemu_ComponentFactory_QueryInterface *)call;
    struct qemu_component_factory *factory;
    IUnknown *obj;

    WINE_TRACE("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_QueryInterface(factory->host, QEMU_G2H(c->iid), (void **)&obj);
    if (SUCCEEDED(c->super.iret))
    {
        WINE_FIXME("Host returned an interface for %s which this wrapper does not know about.\n",
                wine_dbgstr_guid(QEMU_G2H(c->iid)));
        IUnknown_Release(obj);
    }
}

#endif

struct qemu_ComponentFactory_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI ComponentFactory_AddRef(IWICComponentFactory *iface)
{
    struct qemu_ComponentFactory_AddRef call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_ADDREF);
    call.iface = (ULONG_PTR)factory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_AddRef(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_AddRef *c = (struct qemu_ComponentFactory_AddRef *)call;
    struct qemu_component_factory *factory;

    WINE_TRACE("\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_AddRef(factory->host);
}

#endif

struct qemu_ComponentFactory_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI ComponentFactory_Release(IWICComponentFactory *iface)
{
    struct qemu_ComponentFactory_Release call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_RELEASE);
    call.iface = (ULONG_PTR)factory;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_Release(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_Release *c = (struct qemu_ComponentFactory_Release *)call;
    struct qemu_component_factory *factory;

    WINE_TRACE("\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_Release(factory->host);
    if (!c->super.iret)
    {
        WINE_TRACE("Destroying component factory wrapper %p for host texture %p.\n", factory, factory->host);
        HeapFree(GetProcessHeap(), 0, factory);
    }
}

#endif

struct qemu_ComponentFactory_CreateDecoderFromFilename
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t wzFilename;
    uint64_t pguidVendor;
    uint64_t dwDesiredAccess;
    uint64_t metadataOptions;
    uint64_t ppIDecoder;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateDecoderFromFilename(IWICComponentFactory *iface, LPCWSTR wzFilename, const GUID *pguidVendor, DWORD dwDesiredAccess, WICDecodeOptions metadataOptions, IWICBitmapDecoder **ppIDecoder)
{
    struct qemu_ComponentFactory_CreateDecoderFromFilename call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEDECODERFROMFILENAME);
    call.iface = (ULONG_PTR)factory;
    call.wzFilename = (ULONG_PTR)wzFilename;
    call.pguidVendor = (ULONG_PTR)pguidVendor;
    call.dwDesiredAccess = dwDesiredAccess;
    call.metadataOptions = metadataOptions;
    call.ppIDecoder = (ULONG_PTR)ppIDecoder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateDecoderFromFilename(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateDecoderFromFilename *c = (struct qemu_ComponentFactory_CreateDecoderFromFilename *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateDecoderFromFilename(factory->host, QEMU_G2H(c->wzFilename), QEMU_G2H(c->pguidVendor), c->dwDesiredAccess, c->metadataOptions, QEMU_G2H(c->ppIDecoder));
}

#endif

struct qemu_ComponentFactory_CreateDecoderFromStream
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIStream;
    uint64_t pguidVendor;
    uint64_t metadataOptions;
    uint64_t ppIDecoder;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateDecoderFromStream(IWICComponentFactory *iface, IStream *pIStream, const GUID *pguidVendor, WICDecodeOptions metadataOptions, IWICBitmapDecoder **ppIDecoder)
{
    struct qemu_ComponentFactory_CreateDecoderFromStream call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEDECODERFROMSTREAM);
    call.iface = (ULONG_PTR)factory;
    call.pIStream = (ULONG_PTR)pIStream;
    call.pguidVendor = (ULONG_PTR)pguidVendor;
    call.metadataOptions = metadataOptions;
    call.ppIDecoder = (ULONG_PTR)ppIDecoder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateDecoderFromStream(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateDecoderFromStream *c = (struct qemu_ComponentFactory_CreateDecoderFromStream *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateDecoderFromStream(factory->host, QEMU_G2H(c->pIStream), QEMU_G2H(c->pguidVendor), c->metadataOptions, QEMU_G2H(c->ppIDecoder));
}

#endif

struct qemu_ComponentFactory_CreateDecoderFromFileHandle
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hFile;
    uint64_t pguidVendor;
    uint64_t metadataOptions;
    uint64_t ppIDecoder;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateDecoderFromFileHandle(IWICComponentFactory *iface, ULONG_PTR hFile, const GUID *pguidVendor, WICDecodeOptions metadataOptions, IWICBitmapDecoder **ppIDecoder)
{
    struct qemu_ComponentFactory_CreateDecoderFromFileHandle call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEDECODERFROMFILEHANDLE);
    call.iface = (ULONG_PTR)factory;
    call.hFile = hFile;
    call.pguidVendor = (ULONG_PTR)pguidVendor;
    call.metadataOptions = metadataOptions;
    call.ppIDecoder = (ULONG_PTR)ppIDecoder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateDecoderFromFileHandle(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateDecoderFromFileHandle *c = (struct qemu_ComponentFactory_CreateDecoderFromFileHandle *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateDecoderFromFileHandle(factory->host, c->hFile, QEMU_G2H(c->pguidVendor), c->metadataOptions, QEMU_G2H(c->ppIDecoder));
}

#endif

struct qemu_ComponentFactory_CreateComponentInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t clsidComponent;
    uint64_t ppIInfo;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateComponentInfo(IWICComponentFactory *iface, REFCLSID clsidComponent, IWICComponentInfo **ppIInfo)
{
    struct qemu_ComponentFactory_CreateComponentInfo call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATECOMPONENTINFO);
    call.iface = (ULONG_PTR)factory;
    call.clsidComponent = (ULONG_PTR)clsidComponent;
    call.ppIInfo = (ULONG_PTR)ppIInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateComponentInfo(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateComponentInfo *c = (struct qemu_ComponentFactory_CreateComponentInfo *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateComponentInfo(factory->host, QEMU_G2H(c->clsidComponent), QEMU_G2H(c->ppIInfo));
}

#endif

struct qemu_ComponentFactory_CreateDecoder
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guidContainerFormat;
    uint64_t pguidVendor;
    uint64_t ppIDecoder;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateDecoder(IWICComponentFactory *iface, REFGUID guidContainerFormat, const GUID *pguidVendor, IWICBitmapDecoder **ppIDecoder)
{
    struct qemu_ComponentFactory_CreateDecoder call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEDECODER);
    call.iface = (ULONG_PTR)factory;
    call.guidContainerFormat = (ULONG_PTR)guidContainerFormat;
    call.pguidVendor = (ULONG_PTR)pguidVendor;
    call.ppIDecoder = (ULONG_PTR)ppIDecoder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateDecoder(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateDecoder *c = (struct qemu_ComponentFactory_CreateDecoder *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateDecoder(factory->host, QEMU_G2H(c->guidContainerFormat), QEMU_G2H(c->pguidVendor), QEMU_G2H(c->ppIDecoder));
}

#endif

struct qemu_ComponentFactory_CreateEncoder
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guidContainerFormat;
    uint64_t pguidVendor;
    uint64_t ppIEncoder;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateEncoder(IWICComponentFactory *iface, REFGUID guidContainerFormat, const GUID *pguidVendor, IWICBitmapEncoder **ppIEncoder)
{
    struct qemu_ComponentFactory_CreateEncoder call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEENCODER);
    call.iface = (ULONG_PTR)factory;
    call.guidContainerFormat = (ULONG_PTR)guidContainerFormat;
    call.pguidVendor = (ULONG_PTR)pguidVendor;
    call.ppIEncoder = (ULONG_PTR)ppIEncoder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateEncoder(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateEncoder *c = (struct qemu_ComponentFactory_CreateEncoder *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateEncoder(factory->host, QEMU_G2H(c->guidContainerFormat), QEMU_G2H(c->pguidVendor), QEMU_G2H(c->ppIEncoder));
}

#endif

struct qemu_ComponentFactory_CreatePalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIPalette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreatePalette(IWICComponentFactory *iface, IWICPalette **ppIPalette)
{
    struct qemu_ComponentFactory_CreatePalette call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);
    struct qemu_wic_palette *palette;

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEPALETTE);
    call.iface = (ULONG_PTR)factory;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    palette = (struct qemu_wic_palette *)(ULONG_PTR)call.ppIPalette;
    *ppIPalette = WICPalette_init_guest(palette);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreatePalette(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreatePalette *c = (struct qemu_ComponentFactory_CreatePalette *)call;
    struct qemu_component_factory *factory;
    IWICPalette *host;
    struct qemu_wic_palette *palette;

    WINE_TRACE("\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreatePalette(factory->host, &host);
    if (FAILED(c->super.iret))
        return;

    palette = WICPalette_create_host(host);
    if (!palette)
    {
        IWICPalette_Release(host);
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->ppIPalette = QEMU_H2G(palette);
}

#endif

struct qemu_ComponentFactory_CreateFormatConverter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIFormatConverter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateFormatConverter(IWICComponentFactory *iface, IWICFormatConverter **ppIFormatConverter)
{
    struct qemu_ComponentFactory_CreateFormatConverter call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEFORMATCONVERTER);
    call.iface = (ULONG_PTR)factory;
    call.ppIFormatConverter = (ULONG_PTR)ppIFormatConverter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateFormatConverter(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateFormatConverter *c = (struct qemu_ComponentFactory_CreateFormatConverter *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateFormatConverter(factory->host, QEMU_G2H(c->ppIFormatConverter));
}

#endif

struct qemu_ComponentFactory_CreateBitmapScaler
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIBitmapScaler;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateBitmapScaler(IWICComponentFactory *iface, IWICBitmapScaler **ppIBitmapScaler)
{
    struct qemu_ComponentFactory_CreateBitmapScaler call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEBITMAPSCALER);
    call.iface = (ULONG_PTR)factory;
    call.ppIBitmapScaler = (ULONG_PTR)ppIBitmapScaler;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateBitmapScaler(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateBitmapScaler *c = (struct qemu_ComponentFactory_CreateBitmapScaler *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateBitmapScaler(factory->host, QEMU_G2H(c->ppIBitmapScaler));
}

#endif

struct qemu_ComponentFactory_CreateBitmapClipper
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIBitmapClipper;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateBitmapClipper(IWICComponentFactory *iface, IWICBitmapClipper **ppIBitmapClipper)
{
    struct qemu_ComponentFactory_CreateBitmapClipper call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEBITMAPCLIPPER);
    call.iface = (ULONG_PTR)factory;
    call.ppIBitmapClipper = (ULONG_PTR)ppIBitmapClipper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateBitmapClipper(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateBitmapClipper *c = (struct qemu_ComponentFactory_CreateBitmapClipper *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateBitmapClipper(factory->host, QEMU_G2H(c->ppIBitmapClipper));
}

#endif

struct qemu_ComponentFactory_CreateBitmapFlipRotator
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIBitmapFlipRotator;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateBitmapFlipRotator(IWICComponentFactory *iface, IWICBitmapFlipRotator **ppIBitmapFlipRotator)
{
    struct qemu_ComponentFactory_CreateBitmapFlipRotator call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEBITMAPFLIPROTATOR);
    call.iface = (ULONG_PTR)factory;
    call.ppIBitmapFlipRotator = (ULONG_PTR)ppIBitmapFlipRotator;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateBitmapFlipRotator(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateBitmapFlipRotator *c = (struct qemu_ComponentFactory_CreateBitmapFlipRotator *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateBitmapFlipRotator(factory->host, QEMU_G2H(c->ppIBitmapFlipRotator));
}

#endif

struct qemu_ComponentFactory_CreateStream
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIWICStream;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateStream(IWICComponentFactory *iface, IWICStream **ppIWICStream)
{
    struct qemu_ComponentFactory_CreateStream call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATESTREAM);
    call.iface = (ULONG_PTR)factory;
    call.ppIWICStream = (ULONG_PTR)ppIWICStream;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateStream(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateStream *c = (struct qemu_ComponentFactory_CreateStream *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateStream(factory->host, QEMU_G2H(c->ppIWICStream));
}

#endif

struct qemu_ComponentFactory_CreateColorContext
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIColorContext;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateColorContext(IWICComponentFactory *iface, IWICColorContext **ppIColorContext)
{
    struct qemu_ComponentFactory_CreateColorContext call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATECOLORCONTEXT);
    call.iface = (ULONG_PTR)factory;
    call.ppIColorContext = (ULONG_PTR)ppIColorContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateColorContext(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateColorContext *c = (struct qemu_ComponentFactory_CreateColorContext *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateColorContext(factory->host, QEMU_G2H(c->ppIColorContext));
}

#endif

struct qemu_ComponentFactory_CreateColorTransformer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIColorTransform;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateColorTransformer(IWICComponentFactory *iface, IWICColorTransform **ppIColorTransform)
{
    struct qemu_ComponentFactory_CreateColorTransformer call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATECOLORTRANSFORMER);
    call.iface = (ULONG_PTR)factory;
    call.ppIColorTransform = (ULONG_PTR)ppIColorTransform;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateColorTransformer(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateColorTransformer *c = (struct qemu_ComponentFactory_CreateColorTransformer *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateColorTransformer(factory->host, QEMU_G2H(c->ppIColorTransform));
}

#endif

struct qemu_ComponentFactory_CreateBitmap
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t uiWidth;
    uint64_t uiHeight;
    uint64_t pixelFormat;
    uint64_t option;
    uint64_t ppIBitmap;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateBitmap(IWICComponentFactory *iface, UINT uiWidth, UINT uiHeight,
        REFWICPixelFormatGUID pixelFormat, WICBitmapCreateCacheOption option, IWICBitmap **ppIBitmap)
{
    struct qemu_ComponentFactory_CreateBitmap call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);
    struct qemu_wic_bitmap *bitmap;

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEBITMAP);
    call.iface = (ULONG_PTR)factory;
    call.uiWidth = uiWidth;
    call.uiHeight = uiHeight;
    call.pixelFormat = (ULONG_PTR)pixelFormat;
    call.option = option;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    bitmap = (struct qemu_wic_bitmap *)(ULONG_PTR)call.ppIBitmap;
    *ppIBitmap = WICBitmap_init_guest(bitmap);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateBitmap(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateBitmap *c = (struct qemu_ComponentFactory_CreateBitmap *)call;
    struct qemu_component_factory *factory;
    IWICBitmap *host;
    struct qemu_wic_bitmap *bitmap;

    WINE_TRACE("\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateBitmap(factory->host, c->uiWidth, c->uiHeight, QEMU_G2H(c->pixelFormat),
            c->option, &host);
    if (FAILED(c->super.iret))
        return;

    bitmap = WICBitmap_create_host(host);
    if (!bitmap)
    {
        IWICBitmap_Release(host);
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    c->ppIBitmap = QEMU_H2G(bitmap);
}

#endif

struct qemu_ComponentFactory_CreateBitmapFromSource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t piBitmapSource;
    uint64_t option;
    uint64_t ppIBitmap;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateBitmapFromSource(IWICComponentFactory *iface, IWICBitmapSource *piBitmapSource, WICBitmapCreateCacheOption option, IWICBitmap **ppIBitmap)
{
    struct qemu_ComponentFactory_CreateBitmapFromSource call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEBITMAPFROMSOURCE);
    call.iface = (ULONG_PTR)factory;
    call.piBitmapSource = (ULONG_PTR)piBitmapSource;
    call.option = option;
    call.ppIBitmap = (ULONG_PTR)ppIBitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateBitmapFromSource(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateBitmapFromSource *c = (struct qemu_ComponentFactory_CreateBitmapFromSource *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateBitmapFromSource(factory->host, QEMU_G2H(c->piBitmapSource), c->option, QEMU_G2H(c->ppIBitmap));
}

#endif

struct qemu_ComponentFactory_CreateBitmapFromSourceRect
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t piBitmapSource;
    uint64_t x;
    uint64_t y;
    uint64_t width;
    uint64_t height;
    uint64_t ppIBitmap;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateBitmapFromSourceRect(IWICComponentFactory *iface, IWICBitmapSource *piBitmapSource, UINT x, UINT y, UINT width, UINT height, IWICBitmap **ppIBitmap)
{
    struct qemu_ComponentFactory_CreateBitmapFromSourceRect call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEBITMAPFROMSOURCERECT);
    call.iface = (ULONG_PTR)factory;
    call.piBitmapSource = (ULONG_PTR)piBitmapSource;
    call.x = x;
    call.y = y;
    call.width = width;
    call.height = height;
    call.ppIBitmap = (ULONG_PTR)ppIBitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateBitmapFromSourceRect(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateBitmapFromSourceRect *c = (struct qemu_ComponentFactory_CreateBitmapFromSourceRect *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateBitmapFromSourceRect(factory->host, QEMU_G2H(c->piBitmapSource), c->x, c->y, c->width, c->height, QEMU_G2H(c->ppIBitmap));
}

#endif

struct qemu_ComponentFactory_CreateBitmapFromMemory
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
    uint64_t format;
    uint64_t stride;
    uint64_t size;
    uint64_t buffer;
    uint64_t bitmap;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateBitmapFromMemory(IWICComponentFactory *iface, UINT width, UINT height, REFWICPixelFormatGUID format, UINT stride, UINT size, BYTE *buffer, IWICBitmap **bitmap)
{
    struct qemu_ComponentFactory_CreateBitmapFromMemory call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEBITMAPFROMMEMORY);
    call.iface = (ULONG_PTR)factory;
    call.width = width;
    call.height = height;
    call.format = (ULONG_PTR)format;
    call.stride = stride;
    call.size = size;
    call.buffer = (ULONG_PTR)buffer;
    call.bitmap = (ULONG_PTR)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateBitmapFromMemory(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateBitmapFromMemory *c = (struct qemu_ComponentFactory_CreateBitmapFromMemory *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateBitmapFromMemory(factory->host, c->width, c->height, QEMU_G2H(c->format), c->stride, c->size, QEMU_G2H(c->buffer), QEMU_G2H(c->bitmap));
}

#endif

struct qemu_ComponentFactory_CreateBitmapFromHBITMAP
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hbm;
    uint64_t hpal;
    uint64_t option;
    uint64_t bitmap;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateBitmapFromHBITMAP(IWICComponentFactory *iface, HBITMAP hbm, HPALETTE hpal, WICBitmapAlphaChannelOption option, IWICBitmap **bitmap)
{
    struct qemu_ComponentFactory_CreateBitmapFromHBITMAP call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEBITMAPFROMHBITMAP);
    call.iface = (ULONG_PTR)factory;
    call.hbm = (ULONG_PTR)hbm;
    call.hpal = (ULONG_PTR)hpal;
    call.option = option;
    call.bitmap = (ULONG_PTR)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateBitmapFromHBITMAP(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateBitmapFromHBITMAP *c = (struct qemu_ComponentFactory_CreateBitmapFromHBITMAP *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateBitmapFromHBITMAP(factory->host, QEMU_G2H(c->hbm), QEMU_G2H(c->hpal), c->option, QEMU_G2H(c->bitmap));
}

#endif

struct qemu_ComponentFactory_CreateBitmapFromHICON
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t hicon;
    uint64_t bitmap;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateBitmapFromHICON(IWICComponentFactory *iface, HICON hicon, IWICBitmap **bitmap)
{
    struct qemu_ComponentFactory_CreateBitmapFromHICON call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEBITMAPFROMHICON);
    call.iface = (ULONG_PTR)factory;
    call.hicon = (ULONG_PTR)hicon;
    call.bitmap = (ULONG_PTR)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateBitmapFromHICON(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateBitmapFromHICON *c = (struct qemu_ComponentFactory_CreateBitmapFromHICON *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateBitmapFromHICON(factory->host, QEMU_G2H(c->hicon), QEMU_G2H(c->bitmap));
}

#endif

struct qemu_ComponentFactory_CreateComponentEnumerator
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t componentTypes;
    uint64_t options;
    uint64_t ppIEnumUnknown;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateComponentEnumerator(IWICComponentFactory *iface, DWORD componentTypes, DWORD options, IEnumUnknown **ppIEnumUnknown)
{
    struct qemu_ComponentFactory_CreateComponentEnumerator call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATECOMPONENTENUMERATOR);
    call.iface = (ULONG_PTR)factory;
    call.componentTypes = componentTypes;
    call.options = options;
    call.ppIEnumUnknown = (ULONG_PTR)ppIEnumUnknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateComponentEnumerator(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateComponentEnumerator *c = (struct qemu_ComponentFactory_CreateComponentEnumerator *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateComponentEnumerator(factory->host, c->componentTypes, c->options, QEMU_G2H(c->ppIEnumUnknown));
}

#endif

struct qemu_ComponentFactory_CreateFastMetadataEncoderFromDecoder
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIDecoder;
    uint64_t ppIFastEncoder;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateFastMetadataEncoderFromDecoder(IWICComponentFactory *iface, IWICBitmapDecoder *pIDecoder, IWICFastMetadataEncoder **ppIFastEncoder)
{
    struct qemu_ComponentFactory_CreateFastMetadataEncoderFromDecoder call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEFASTMETADATAENCODERFROMDECODER);
    call.iface = (ULONG_PTR)factory;
    call.pIDecoder = (ULONG_PTR)pIDecoder;
    call.ppIFastEncoder = (ULONG_PTR)ppIFastEncoder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateFastMetadataEncoderFromDecoder(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateFastMetadataEncoderFromDecoder *c = (struct qemu_ComponentFactory_CreateFastMetadataEncoderFromDecoder *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateFastMetadataEncoderFromDecoder(factory->host, QEMU_G2H(c->pIDecoder), QEMU_G2H(c->ppIFastEncoder));
}

#endif

struct qemu_ComponentFactory_CreateFastMetadataEncoderFromFrameDecode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIFrameDecoder;
    uint64_t ppIFastEncoder;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateFastMetadataEncoderFromFrameDecode(IWICComponentFactory *iface, IWICBitmapFrameDecode *pIFrameDecoder, IWICFastMetadataEncoder **ppIFastEncoder)
{
    struct qemu_ComponentFactory_CreateFastMetadataEncoderFromFrameDecode call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEFASTMETADATAENCODERFROMFRAMEDECODE);
    call.iface = (ULONG_PTR)factory;
    call.pIFrameDecoder = (ULONG_PTR)pIFrameDecoder;
    call.ppIFastEncoder = (ULONG_PTR)ppIFastEncoder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateFastMetadataEncoderFromFrameDecode(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateFastMetadataEncoderFromFrameDecode *c = (struct qemu_ComponentFactory_CreateFastMetadataEncoderFromFrameDecode *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateFastMetadataEncoderFromFrameDecode(factory->host, QEMU_G2H(c->pIFrameDecoder), QEMU_G2H(c->ppIFastEncoder));
}

#endif

struct qemu_ComponentFactory_CreateQueryWriter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t guidMetadataFormat;
    uint64_t pguidVendor;
    uint64_t ppIQueryWriter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateQueryWriter(IWICComponentFactory *iface, REFGUID guidMetadataFormat, const GUID *pguidVendor, IWICMetadataQueryWriter **ppIQueryWriter)
{
    struct qemu_ComponentFactory_CreateQueryWriter call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEQUERYWRITER);
    call.iface = (ULONG_PTR)factory;
    call.guidMetadataFormat = (ULONG_PTR)guidMetadataFormat;
    call.pguidVendor = (ULONG_PTR)pguidVendor;
    call.ppIQueryWriter = (ULONG_PTR)ppIQueryWriter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateQueryWriter(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateQueryWriter *c = (struct qemu_ComponentFactory_CreateQueryWriter *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateQueryWriter(factory->host, QEMU_G2H(c->guidMetadataFormat), QEMU_G2H(c->pguidVendor), QEMU_G2H(c->ppIQueryWriter));
}

#endif

struct qemu_ComponentFactory_CreateQueryWriterFromReader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIQueryReader;
    uint64_t pguidVendor;
    uint64_t ppIQueryWriter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateQueryWriterFromReader(IWICComponentFactory *iface, IWICMetadataQueryReader *pIQueryReader, const GUID *pguidVendor, IWICMetadataQueryWriter **ppIQueryWriter)
{
    struct qemu_ComponentFactory_CreateQueryWriterFromReader call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEQUERYWRITERFROMREADER);
    call.iface = (ULONG_PTR)factory;
    call.pIQueryReader = (ULONG_PTR)pIQueryReader;
    call.pguidVendor = (ULONG_PTR)pguidVendor;
    call.ppIQueryWriter = (ULONG_PTR)ppIQueryWriter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateQueryWriterFromReader(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateQueryWriterFromReader *c = (struct qemu_ComponentFactory_CreateQueryWriterFromReader *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateQueryWriterFromReader(factory->host, QEMU_G2H(c->pIQueryReader), QEMU_G2H(c->pguidVendor), QEMU_G2H(c->ppIQueryWriter));
}

#endif

struct qemu_ComponentFactory_CreateMetadataReader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
    uint64_t vendor;
    uint64_t options;
    uint64_t stream;
    uint64_t reader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateMetadataReader(IWICComponentFactory *iface, REFGUID format, const GUID *vendor, DWORD options, IStream *stream, IWICMetadataReader **reader)
{
    struct qemu_ComponentFactory_CreateMetadataReader call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEMETADATAREADER);
    call.iface = (ULONG_PTR)factory;
    call.format = (ULONG_PTR)format;
    call.vendor = (ULONG_PTR)vendor;
    call.options = options;
    call.stream = (ULONG_PTR)stream;
    call.reader = (ULONG_PTR)reader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateMetadataReader(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateMetadataReader *c = (struct qemu_ComponentFactory_CreateMetadataReader *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateMetadataReader(factory->host, QEMU_G2H(c->format), QEMU_G2H(c->vendor), c->options, QEMU_G2H(c->stream), QEMU_G2H(c->reader));
}

#endif

struct qemu_ComponentFactory_CreateMetadataReaderFromContainer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
    uint64_t vendor;
    uint64_t options;
    uint64_t stream;
    uint64_t reader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateMetadataReaderFromContainer(IWICComponentFactory *iface, REFGUID format, const GUID *vendor, DWORD options, IStream *stream, IWICMetadataReader **reader)
{
    struct qemu_ComponentFactory_CreateMetadataReaderFromContainer call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEMETADATAREADERFROMCONTAINER);
    call.iface = (ULONG_PTR)factory;
    call.format = (ULONG_PTR)format;
    call.vendor = (ULONG_PTR)vendor;
    call.options = options;
    call.stream = (ULONG_PTR)stream;
    call.reader = (ULONG_PTR)reader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateMetadataReaderFromContainer(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateMetadataReaderFromContainer *c = (struct qemu_ComponentFactory_CreateMetadataReaderFromContainer *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateMetadataReaderFromContainer(factory->host, QEMU_G2H(c->format), QEMU_G2H(c->vendor), c->options, QEMU_G2H(c->stream), QEMU_G2H(c->reader));
}

#endif

struct qemu_ComponentFactory_CreateMetadataWriter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
    uint64_t vendor;
    uint64_t options;
    uint64_t writer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateMetadataWriter(IWICComponentFactory *iface, REFGUID format, const GUID *vendor, DWORD options, IWICMetadataWriter **writer)
{
    struct qemu_ComponentFactory_CreateMetadataWriter call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEMETADATAWRITER);
    call.iface = (ULONG_PTR)factory;
    call.format = (ULONG_PTR)format;
    call.vendor = (ULONG_PTR)vendor;
    call.options = options;
    call.writer = (ULONG_PTR)writer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateMetadataWriter(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateMetadataWriter *c = (struct qemu_ComponentFactory_CreateMetadataWriter *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateMetadataWriter(factory->host, QEMU_G2H(c->format), QEMU_G2H(c->vendor), c->options, QEMU_G2H(c->writer));
}

#endif

struct qemu_ComponentFactory_CreateMetadataWriterFromReader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reader;
    uint64_t vendor;
    uint64_t writer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateMetadataWriterFromReader(IWICComponentFactory *iface, IWICMetadataReader *reader, const GUID *vendor, IWICMetadataWriter **writer)
{
    struct qemu_ComponentFactory_CreateMetadataWriterFromReader call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEMETADATAWRITERFROMREADER);
    call.iface = (ULONG_PTR)factory;
    call.reader = (ULONG_PTR)reader;
    call.vendor = (ULONG_PTR)vendor;
    call.writer = (ULONG_PTR)writer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateMetadataWriterFromReader(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateMetadataWriterFromReader *c = (struct qemu_ComponentFactory_CreateMetadataWriterFromReader *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateMetadataWriterFromReader(factory->host, QEMU_G2H(c->reader), QEMU_G2H(c->vendor), QEMU_G2H(c->writer));
}

#endif

struct qemu_ComponentFactory_CreateQueryReaderFromBlockReader
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t block_reader;
    uint64_t query_reader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateQueryReaderFromBlockReader(IWICComponentFactory *iface, IWICMetadataBlockReader *block_reader, IWICMetadataQueryReader **query_reader)
{
    struct qemu_ComponentFactory_CreateQueryReaderFromBlockReader call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEQUERYREADERFROMBLOCKREADER);
    call.iface = (ULONG_PTR)factory;
    call.block_reader = (ULONG_PTR)block_reader;
    call.query_reader = (ULONG_PTR)query_reader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateQueryReaderFromBlockReader(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateQueryReaderFromBlockReader *c = (struct qemu_ComponentFactory_CreateQueryReaderFromBlockReader *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateQueryReaderFromBlockReader(factory->host, QEMU_G2H(c->block_reader), QEMU_G2H(c->query_reader));
}

#endif

struct qemu_ComponentFactory_CreateQueryWriterFromBlockWriter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t block_writer;
    uint64_t query_writer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateQueryWriterFromBlockWriter(IWICComponentFactory *iface, IWICMetadataBlockWriter *block_writer, IWICMetadataQueryWriter **query_writer)
{
    struct qemu_ComponentFactory_CreateQueryWriterFromBlockWriter call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEQUERYWRITERFROMBLOCKWRITER);
    call.iface = (ULONG_PTR)factory;
    call.block_writer = (ULONG_PTR)block_writer;
    call.query_writer = (ULONG_PTR)query_writer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateQueryWriterFromBlockWriter(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateQueryWriterFromBlockWriter *c = (struct qemu_ComponentFactory_CreateQueryWriterFromBlockWriter *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateQueryWriterFromBlockWriter(factory->host, QEMU_G2H(c->block_writer), QEMU_G2H(c->query_writer));
}

#endif

struct qemu_ComponentFactory_CreateEncoderPropertyBag
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t options;
    uint64_t count;
    uint64_t property;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ComponentFactory_CreateEncoderPropertyBag(IWICComponentFactory *iface, PROPBAG2 *options, UINT count, IPropertyBag2 **property)
{
    struct qemu_ComponentFactory_CreateEncoderPropertyBag call;
    struct qemu_component_factory *factory = impl_from_IWICComponentFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATEENCODERPROPERTYBAG);
    call.iface = (ULONG_PTR)factory;
    call.options = (ULONG_PTR)options;
    call.count = count;
    call.property = (ULONG_PTR)property;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ComponentFactory_CreateEncoderPropertyBag(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_CreateEncoderPropertyBag *c = (struct qemu_ComponentFactory_CreateEncoderPropertyBag *)call;
    struct qemu_component_factory *factory;

    WINE_FIXME("Unverified!\n");
    factory = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentFactory_CreateEncoderPropertyBag(factory->host, QEMU_G2H(c->options), c->count, QEMU_G2H(c->property));
}

#endif

struct qemu_WICCreateBitmapFromSectionEx
{
    struct qemu_syscall super;
    uint64_t width;
    uint64_t height;
    uint64_t format;
    uint64_t section;
    uint64_t stride;
    uint64_t offset;
    uint64_t wicaccess;
    uint64_t bitmap;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WICCreateBitmapFromSectionEx(UINT width, UINT height, REFWICPixelFormatGUID format,
        HANDLE section, UINT stride, UINT offset, WICSectionAccessLevel wicaccess, IWICBitmap **bitmap)
{
    struct qemu_WICCreateBitmapFromSectionEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WICCREATEBITMAPFROMSECTIONEX);
    call.width = width;
    call.height = height;
    call.format = (ULONG_PTR)format;
    call.section = (ULONG_PTR)section;
    call.stride = stride;
    call.offset = offset;
    call.wicaccess = wicaccess;
    call.bitmap = (ULONG_PTR)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICCreateBitmapFromSectionEx(struct qemu_syscall *call)
{
    struct qemu_WICCreateBitmapFromSectionEx *c = (struct qemu_WICCreateBitmapFromSectionEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WICCreateBitmapFromSectionEx(c->width, c->height, QEMU_G2H(c->format), QEMU_G2H(c->section),
            c->stride, c->offset, c->wicaccess, QEMU_G2H(c->bitmap));
}

#endif

struct qemu_WICCreateBitmapFromSection
{
    struct qemu_syscall super;
    uint64_t width;
    uint64_t height;
    uint64_t format;
    uint64_t section;
    uint64_t stride;
    uint64_t offset;
    uint64_t bitmap;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WICCreateBitmapFromSection(UINT width, UINT height, REFWICPixelFormatGUID format,
        HANDLE section, UINT stride, UINT offset, IWICBitmap **bitmap)
{
    struct qemu_WICCreateBitmapFromSection call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WICCREATEBITMAPFROMSECTION);
    call.width = width;
    call.height = height;
    call.format = (ULONG_PTR)format;
    call.section = (ULONG_PTR)section;
    call.stride = stride;
    call.offset = offset;
    call.bitmap = (ULONG_PTR)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICCreateBitmapFromSection(struct qemu_syscall *call)
{
    struct qemu_WICCreateBitmapFromSection *c = (struct qemu_WICCreateBitmapFromSection *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WICCreateBitmapFromSection(c->width, c->height, QEMU_G2H(c->format), QEMU_G2H(c->section),
            c->stride, c->offset, QEMU_G2H(c->bitmap));
}

#endif

struct qemu_ComponentFactory_create_host
{
    struct qemu_syscall super;
    uint64_t factory;
};

#ifdef QEMU_DLL_GUEST

static const IWICComponentFactoryVtbl ComponentFactory_Vtbl =
{
    ComponentFactory_QueryInterface,
    ComponentFactory_AddRef,
    ComponentFactory_Release,
    ComponentFactory_CreateDecoderFromFilename,
    ComponentFactory_CreateDecoderFromStream,
    ComponentFactory_CreateDecoderFromFileHandle,
    ComponentFactory_CreateComponentInfo,
    ComponentFactory_CreateDecoder,
    ComponentFactory_CreateEncoder,
    ComponentFactory_CreatePalette,
    ComponentFactory_CreateFormatConverter,
    ComponentFactory_CreateBitmapScaler,
    ComponentFactory_CreateBitmapClipper,
    ComponentFactory_CreateBitmapFlipRotator,
    ComponentFactory_CreateStream,
    ComponentFactory_CreateColorContext,
    ComponentFactory_CreateColorTransformer,
    ComponentFactory_CreateBitmap,
    ComponentFactory_CreateBitmapFromSource,
    ComponentFactory_CreateBitmapFromSourceRect,
    ComponentFactory_CreateBitmapFromMemory,
    ComponentFactory_CreateBitmapFromHBITMAP,
    ComponentFactory_CreateBitmapFromHICON,
    ComponentFactory_CreateComponentEnumerator,
    ComponentFactory_CreateFastMetadataEncoderFromDecoder,
    ComponentFactory_CreateFastMetadataEncoderFromFrameDecode,
    ComponentFactory_CreateQueryWriter,
    ComponentFactory_CreateQueryWriterFromReader,
    ComponentFactory_CreateMetadataReader,
    ComponentFactory_CreateMetadataReaderFromContainer,
    ComponentFactory_CreateMetadataWriter,
    ComponentFactory_CreateMetadataWriterFromReader,
    ComponentFactory_CreateQueryReaderFromBlockReader,
    ComponentFactory_CreateQueryWriterFromBlockWriter,
    ComponentFactory_CreateEncoderPropertyBag
};

HRESULT ComponentFactory_CreateInstance(const IID *iid, void **obj)
{
    struct qemu_ComponentFactory_create_host call;
    struct qemu_component_factory *factory;
    HRESULT hr;

    WINE_TRACE("(%s,%p)\n", wine_dbgstr_guid(iid), obj);

    *obj = NULL;
    call.super.id = QEMU_SYSCALL_ID(CALL_COMPONENTFACTORY_CREATE_HOST);
    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    factory = (struct qemu_component_factory *)(ULONG_PTR)call.factory;
    factory->IWICComponentFactory_iface.lpVtbl = &ComponentFactory_Vtbl;

    hr = IWICComponentFactory_QueryInterface(&factory->IWICComponentFactory_iface, iid, obj);
    IWICComponentFactory_Release(&factory->IWICComponentFactory_iface);

    return hr;
}

#else

void qemu_ComponentFactory_create_host(struct qemu_syscall *call)
{
    struct qemu_ComponentFactory_create_host *c = (struct qemu_ComponentFactory_create_host *)call;
    struct qemu_component_factory *factory;
    HMODULE lib;
    HRESULT (* WINAPI p_DllGetClassObject)(REFCLSID rclsid, REFIID riid, void **obj);
    IClassFactory *host_factory;
    HRESULT hr;

    factory = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*factory));
    if (!factory)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }

    lib = GetModuleHandleA("windowscodecs");
    p_DllGetClassObject = (void *)GetProcAddress(lib, "DllGetClassObject");

    hr = p_DllGetClassObject(&CLSID_WICImagingFactory, &IID_IClassFactory, (void *)&host_factory);
    if (FAILED(hr))
        WINE_ERR("Cannot create class factory\n");

    hr = IClassFactory_CreateInstance(host_factory, NULL, &IID_IWICComponentFactory, (void **)&factory->host);
    if (FAILED(hr))
    {
        WINE_WARN("Failed to create an IWICComponentFactory object.\n");
        HeapFree(GetProcessHeap(), 0, factory);
        factory = NULL;
    }
    IClassFactory_Release(host_factory);

    c->factory = QEMU_H2G(factory);
    c->super.iret = hr;
}

#endif
