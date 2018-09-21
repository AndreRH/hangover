/*
 * Copyright 2009 Vincent Povirk for CodeWeavers
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

#ifdef QEMU_DLL_GUEST

#define COBJMACROS
#include <windows.h>
#include <wincodec.h>
#include <wincodecsdk.h>
#include <wine/debug.h>
#include <wine/list.h>
#include <wine/rbtree.h>

#include "windows-user-services.h"
#include "qemu_windowscodecs.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_wic);

extern HRESULT WINAPI WIC_DllGetClassObject(const CLSID *, const IID *, void **);

typedef struct {
    REFCLSID classid;
    class_constructor constructor;
} classinfo;

static HRESULT CommentReader_CreateInstance(const CLSID *clsid, const IID *iid, void **obj)
{
    WINE_FIXME("Stub\n");
    return E_FAIL;
}

static const classinfo wic_classes[] = {
    {&CLSID_WICImagingFactory, ComponentFactory_CreateInstance},
    {&CLSID_WICBmpDecoder, Decoder_CreateInstance},
    {&CLSID_WICPngDecoder, Decoder_CreateInstance},
    {&CLSID_WICPngEncoder, Encoder_CreateInstance},
    {&CLSID_WICBmpEncoder, Encoder_CreateInstance},
    {&CLSID_WICGifDecoder, Decoder_CreateInstance},
    {&CLSID_WICIcoDecoder, Decoder_CreateInstance},
    {&CLSID_WICJpegDecoder, Decoder_CreateInstance},
    {&CLSID_WICJpegEncoder, Encoder_CreateInstance},
    {&CLSID_WICTiffDecoder, Decoder_CreateInstance},
    {&CLSID_WICTiffEncoder, Encoder_CreateInstance},
    {&CLSID_WICIcnsEncoder, Encoder_CreateInstance},
    {&CLSID_WICDefaultFormatConverter, FormatConverter_CreateInstance},
    {&CLSID_WineTgaDecoder, Decoder_CreateInstance},
    {&CLSID_WICUnknownMetadataReader, MetadataReader_CreateInstance},
    {&CLSID_WICIfdMetadataReader, MetadataReader_CreateInstance},
    {&CLSID_WICPngChrmMetadataReader, MetadataReader_CreateInstance},
    {&CLSID_WICPngGamaMetadataReader, MetadataReader_CreateInstance},
    {&CLSID_WICPngTextMetadataReader, MetadataReader_CreateInstance},
    {&CLSID_WICLSDMetadataReader, MetadataReader_CreateInstance},
    {&CLSID_WICIMDMetadataReader, MetadataReader_CreateInstance},
    {&CLSID_WICGCEMetadataReader, MetadataReader_CreateInstance},
    {&CLSID_WICAPEMetadataReader, MetadataReader_CreateInstance},
    {&CLSID_WICGifCommentMetadataReader, CommentReader_CreateInstance},
    {0}};

typedef struct {
    IClassFactory           IClassFactory_iface;
    LONG                    ref;
    const classinfo         *info;
} ClassFactoryImpl;

static inline ClassFactoryImpl *impl_from_IClassFactory(IClassFactory *iface)
{
    return CONTAINING_RECORD(iface, ClassFactoryImpl, IClassFactory_iface);
}

static HRESULT WINAPI ClassFactoryImpl_QueryInterface(IClassFactory *iface,
    REFIID iid, void **ppv)
{
    ClassFactoryImpl *This = impl_from_IClassFactory(iface);
    WINE_TRACE("(%p,%s,%p)\n", iface, wine_dbgstr_guid(iid), ppv);

    if (!ppv) return E_INVALIDARG;

    if (IsEqualIID(&IID_IUnknown, iid) ||
        IsEqualIID(&IID_IClassFactory, iid))
    {
        *ppv = &This->IClassFactory_iface;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    IUnknown_AddRef((IUnknown*)*ppv);
    return S_OK;
}

static ULONG WINAPI ClassFactoryImpl_AddRef(IClassFactory *iface)
{
    ClassFactoryImpl *This = impl_from_IClassFactory(iface);
    ULONG ref = InterlockedIncrement(&This->ref);

    WINE_TRACE("(%p) refcount=%u\n", iface, ref);

    return ref;
}

static ULONG WINAPI ClassFactoryImpl_Release(IClassFactory *iface)
{
    ClassFactoryImpl *This = impl_from_IClassFactory(iface);
    ULONG ref = InterlockedDecrement(&This->ref);

    WINE_TRACE("(%p) refcount=%u\n", iface, ref);

    if (ref == 0)
        HeapFree(GetProcessHeap(), 0, This);

    return ref;
}

static HRESULT WINAPI ClassFactoryImpl_CreateInstance(IClassFactory *iface,
    IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
    ClassFactoryImpl *This = impl_from_IClassFactory(iface);

    *ppv = NULL;

    if (pUnkOuter) return CLASS_E_NOAGGREGATION;

    return This->info->constructor(This->info->classid, riid, ppv);
}

static HRESULT WINAPI ClassFactoryImpl_LockServer(IClassFactory *iface, BOOL lock)
{
    WINE_TRACE("(%p, %i): stub\n", iface, lock);
    return E_NOTIMPL;
}

static const IClassFactoryVtbl ClassFactoryImpl_Vtbl = {
    ClassFactoryImpl_QueryInterface,
    ClassFactoryImpl_AddRef,
    ClassFactoryImpl_Release,
    ClassFactoryImpl_CreateInstance,
    ClassFactoryImpl_LockServer
};

static HRESULT ClassFactoryImpl_Constructor(const classinfo *info, REFIID riid, LPVOID *ppv)
{
    ClassFactoryImpl *This;
    HRESULT ret;

    *ppv = NULL;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(ClassFactoryImpl));
    if (!This) return E_OUTOFMEMORY;

    This->IClassFactory_iface.lpVtbl = &ClassFactoryImpl_Vtbl;
    This->ref = 1;
    This->info = info;

    ret = IClassFactory_QueryInterface(&This->IClassFactory_iface, riid, ppv);
    IClassFactory_Release(&This->IClassFactory_iface);

    return ret;
}

HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID iid, LPVOID *ppv)
{
    HRESULT ret;
    const classinfo *info=NULL;
    int i;

    WINE_TRACE("(%s,%s,%p)\n", wine_dbgstr_guid(rclsid), wine_dbgstr_guid(iid), ppv);

    if (!rclsid || !iid || !ppv)
        return E_INVALIDARG;

    *ppv = NULL;

    for (i=0; wic_classes[i].classid; i++)
    {
        if (IsEqualCLSID(wic_classes[i].classid, rclsid))
        {
            info = &wic_classes[i];
            break;
        }
    }

    if (info)
    {
        ret = ClassFactoryImpl_Constructor(info, iid, ppv);
    }
    else
    {
        WINE_FIXME("Calling the magic blob\n");
        ret = WIC_DllGetClassObject(rclsid, iid, ppv);
        WINE_FIXME("Magic blob returned %08x\n", ret);
    }

    WINE_TRACE("<-- %08X\n", ret);
    return ret;
}

#endif
