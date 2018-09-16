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

#include "thunk/qemu_windows.h"
#include "thunk/qemu_wincodec.h"

#include <wine/debug.h>
#include <wine/list.h>

#include "qemu_windowscodecs.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_wic);

struct qemu_WICComponentInfo_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_info *impl_from_IWICComponentInfo(IWICComponentInfo *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_info, IWICComponentInfo_iface);
}

static inline struct qemu_wic_info *impl_from_IWICBitmapDecoderInfo(IWICBitmapDecoderInfo *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_info, IWICComponentInfo_iface);
}

static HRESULT WINAPI WICComponentInfo_QueryInterface(IWICComponentInfo *iface, REFIID iid, void **ppv)
{
    struct qemu_WICComponentInfo_QueryInterface call;
    struct qemu_wic_info *info = impl_from_IWICComponentInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOMPONENTINFO_QUERYINTERFACE);
    call.iface = (ULONG_PTR)info;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
    {
        *ppv = NULL;
        return call.super.iret;
    }

    *ppv = iface;
    /* Already Addref'ed on the host side. */
    return call.super.iret;
}

#else

void qemu_WICComponentInfo_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICComponentInfo_QueryInterface *c = (struct qemu_WICComponentInfo_QueryInterface *)call;
    struct qemu_wic_info *info;
    IUnknown *unk;

    WINE_TRACE("\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentInfo_QueryInterface(info->host, QEMU_G2H(c->iid), (void **)&unk);
    if (FAILED(c->super.iret))
        return;

    assert(unk == (IUnknown *)info->host);
    /* Forward the reference */
}

#endif

struct qemu_WICComponentInfo_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICComponentInfo_AddRef(IWICComponentInfo *iface)
{
    struct qemu_WICComponentInfo_AddRef call;
    struct qemu_wic_info *info = impl_from_IWICComponentInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOMPONENTINFO_ADDREF);
    call.iface = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICComponentInfo_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICComponentInfo_AddRef *c = (struct qemu_WICComponentInfo_AddRef *)call;
    struct qemu_wic_info *info;

    WINE_TRACE("\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentInfo_AddRef(info->host);
}

#endif

struct qemu_WICComponentInfo_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICComponentInfo_Release(IWICComponentInfo *iface)
{
    struct qemu_WICComponentInfo_Release call;
    struct qemu_wic_info *info = impl_from_IWICComponentInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOMPONENTINFO_RELEASE);
    call.iface = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICComponentInfo_Release(struct qemu_syscall *call)
{
    struct qemu_WICComponentInfo_Release *c = (struct qemu_WICComponentInfo_Release *)call;
    struct qemu_wic_info *info;

    WINE_TRACE("\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentInfo_Release(info->host);
    if (!c->super.iret)
    {
        WINE_TRACE("Destroying component component info wrapper %p for host info %p.\n", info, info->host);
        HeapFree(GetProcessHeap(), 0, info);
    }
}

#endif

struct qemu_WICComponentInfo_GetComponentType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pType;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICComponentInfo_GetComponentType(IWICComponentInfo *iface, WICComponentType *pType)
{
    struct qemu_WICComponentInfo_GetComponentType call;
    struct qemu_wic_info *info = impl_from_IWICComponentInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOMPONENTINFO_GETCOMPONENTTYPE);
    call.iface = (ULONG_PTR)info;
    call.pType = (ULONG_PTR)pType;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICComponentInfo_GetComponentType(struct qemu_syscall *call)
{
    struct qemu_WICComponentInfo_GetComponentType *c = (struct qemu_WICComponentInfo_GetComponentType *)call;
    struct qemu_wic_info *info;

    WINE_TRACE("\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentInfo_GetComponentType(info->host, QEMU_G2H(c->pType));
}

#endif

struct qemu_WICComponentInfo_GetCLSID
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pclsid;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICComponentInfo_GetCLSID(IWICComponentInfo *iface, CLSID *pclsid)
{
    struct qemu_WICComponentInfo_GetCLSID call;
    struct qemu_wic_info *info = impl_from_IWICComponentInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOMPONENTINFO_GETCLSID);
    call.iface = (ULONG_PTR)info;
    call.pclsid = (ULONG_PTR)pclsid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICComponentInfo_GetCLSID(struct qemu_syscall *call)
{
    struct qemu_WICComponentInfo_GetCLSID *c = (struct qemu_WICComponentInfo_GetCLSID *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentInfo_GetCLSID(info->host, QEMU_G2H(c->pclsid));
}

#endif

struct qemu_WICComponentInfo_GetSigningStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pStatus;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICComponentInfo_GetSigningStatus(IWICComponentInfo *iface, DWORD *pStatus)
{
    struct qemu_WICComponentInfo_GetSigningStatus call;
    struct qemu_wic_info *info = impl_from_IWICComponentInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOMPONENTINFO_GETSIGNINGSTATUS);
    call.iface = (ULONG_PTR)info;
    call.pStatus = (ULONG_PTR)pStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICComponentInfo_GetSigningStatus(struct qemu_syscall *call)
{
    struct qemu_WICComponentInfo_GetSigningStatus *c = (struct qemu_WICComponentInfo_GetSigningStatus *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentInfo_GetSigningStatus(info->host, QEMU_G2H(c->pStatus));
}

#endif

struct qemu_WICComponentInfo_GetAuthor
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchAuthor;
    uint64_t wzAuthor;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICComponentInfo_GetAuthor(IWICComponentInfo *iface, UINT cchAuthor, WCHAR *wzAuthor, UINT *pcchActual)
{
    struct qemu_WICComponentInfo_GetAuthor call;
    struct qemu_wic_info *info = impl_from_IWICComponentInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOMPONENTINFO_GETAUTHOR);
    call.iface = (ULONG_PTR)info;
    call.cchAuthor = cchAuthor;
    call.wzAuthor = (ULONG_PTR)wzAuthor;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICComponentInfo_GetAuthor(struct qemu_syscall *call)
{
    struct qemu_WICComponentInfo_GetAuthor *c = (struct qemu_WICComponentInfo_GetAuthor *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentInfo_GetAuthor(info->host, c->cchAuthor, QEMU_G2H(c->wzAuthor), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICComponentInfo_GetVendorGUID
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pguidVendor;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICComponentInfo_GetVendorGUID(IWICComponentInfo *iface, GUID *pguidVendor)
{
    struct qemu_WICComponentInfo_GetVendorGUID call;
    struct qemu_wic_info *info = impl_from_IWICComponentInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOMPONENTINFO_GETVENDORGUID);
    call.iface = (ULONG_PTR)info;
    call.pguidVendor = (ULONG_PTR)pguidVendor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICComponentInfo_GetVendorGUID(struct qemu_syscall *call)
{
    struct qemu_WICComponentInfo_GetVendorGUID *c = (struct qemu_WICComponentInfo_GetVendorGUID *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentInfo_GetVendorGUID(info->host, QEMU_G2H(c->pguidVendor));
}

#endif

struct qemu_WICComponentInfo_GetVersion
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchVersion;
    uint64_t wzVersion;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICComponentInfo_GetVersion(IWICComponentInfo *iface, UINT cchVersion, WCHAR *wzVersion, UINT *pcchActual)
{
    struct qemu_WICComponentInfo_GetVersion call;
    struct qemu_wic_info *info = impl_from_IWICComponentInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOMPONENTINFO_GETVERSION);
    call.iface = (ULONG_PTR)info;
    call.cchVersion = cchVersion;
    call.wzVersion = (ULONG_PTR)wzVersion;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICComponentInfo_GetVersion(struct qemu_syscall *call)
{
    struct qemu_WICComponentInfo_GetVersion *c = (struct qemu_WICComponentInfo_GetVersion *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentInfo_GetVersion(info->host, c->cchVersion, QEMU_G2H(c->wzVersion), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICComponentInfo_GetSpecVersion
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchSpecVersion;
    uint64_t wzSpecVersion;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICComponentInfo_GetSpecVersion(IWICComponentInfo *iface, UINT cchSpecVersion, WCHAR *wzSpecVersion, UINT *pcchActual)
{
    struct qemu_WICComponentInfo_GetSpecVersion call;
    struct qemu_wic_info *info = impl_from_IWICComponentInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOMPONENTINFO_GETSPECVERSION);
    call.iface = (ULONG_PTR)info;
    call.cchSpecVersion = cchSpecVersion;
    call.wzSpecVersion = (ULONG_PTR)wzSpecVersion;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICComponentInfo_GetSpecVersion(struct qemu_syscall *call)
{
    struct qemu_WICComponentInfo_GetSpecVersion *c = (struct qemu_WICComponentInfo_GetSpecVersion *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentInfo_GetSpecVersion(info->host, c->cchSpecVersion, QEMU_G2H(c->wzSpecVersion), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICComponentInfo_GetFriendlyName
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchFriendlyName;
    uint64_t wzFriendlyName;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICComponentInfo_GetFriendlyName(IWICComponentInfo *iface, UINT cchFriendlyName, WCHAR *wzFriendlyName, UINT *pcchActual)
{
    struct qemu_WICComponentInfo_GetFriendlyName call;
    struct qemu_wic_info *info = impl_from_IWICComponentInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCOMPONENTINFO_GETFRIENDLYNAME);
    call.iface = (ULONG_PTR)info;
    call.cchFriendlyName = cchFriendlyName;
    call.wzFriendlyName = (ULONG_PTR)wzFriendlyName;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICComponentInfo_GetFriendlyName(struct qemu_syscall *call)
{
    struct qemu_WICComponentInfo_GetFriendlyName *c = (struct qemu_WICComponentInfo_GetFriendlyName *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICComponentInfo_GetFriendlyName(info->host, c->cchFriendlyName, QEMU_G2H(c->wzFriendlyName), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICBitmapDecoderInfo_GetContainerFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pguidContainerFormat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_GetContainerFormat(IWICBitmapDecoderInfo *iface, GUID *pguidContainerFormat)
{
    struct qemu_WICBitmapDecoderInfo_GetContainerFormat call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_GETCONTAINERFORMAT);
    call.iface = (ULONG_PTR)info;
    call.pguidContainerFormat = (ULONG_PTR)pguidContainerFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_GetContainerFormat(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_GetContainerFormat *c = (struct qemu_WICBitmapDecoderInfo_GetContainerFormat *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoderInfo_GetContainerFormat((IWICBitmapDecoderInfo *)info->host,
            QEMU_G2H(c->pguidContainerFormat));
}

#endif

struct qemu_WICBitmapDecoderInfo_GetPixelFormats
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cFormats;
    uint64_t pguidPixelFormats;
    uint64_t pcActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_GetPixelFormats(IWICBitmapDecoderInfo *iface, UINT cFormats, GUID *pguidPixelFormats, UINT *pcActual)
{
    struct qemu_WICBitmapDecoderInfo_GetPixelFormats call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_GETPIXELFORMATS);
    call.iface = (ULONG_PTR)info;
    call.cFormats = cFormats;
    call.pguidPixelFormats = (ULONG_PTR)pguidPixelFormats;
    call.pcActual = (ULONG_PTR)pcActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_GetPixelFormats(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_GetPixelFormats *c = (struct qemu_WICBitmapDecoderInfo_GetPixelFormats *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoderInfo_GetPixelFormats((IWICBitmapDecoderInfo *)info->host, c->cFormats, QEMU_G2H(c->pguidPixelFormats), QEMU_G2H(c->pcActual));
}

#endif

struct qemu_WICBitmapDecoderInfo_GetColorManagementVersion
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchColorManagementVersion;
    uint64_t wzColorManagementVersion;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_GetColorManagementVersion(IWICBitmapDecoderInfo *iface, UINT cchColorManagementVersion, WCHAR *wzColorManagementVersion, UINT *pcchActual)
{
    struct qemu_WICBitmapDecoderInfo_GetColorManagementVersion call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_GETCOLORMANAGEMENTVERSION);
    call.iface = (ULONG_PTR)info;
    call.cchColorManagementVersion = cchColorManagementVersion;
    call.wzColorManagementVersion = (ULONG_PTR)wzColorManagementVersion;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_GetColorManagementVersion(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_GetColorManagementVersion *c = (struct qemu_WICBitmapDecoderInfo_GetColorManagementVersion *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoderInfo_GetColorManagementVersion((IWICBitmapDecoderInfo *)info->host, c->cchColorManagementVersion, QEMU_G2H(c->wzColorManagementVersion), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICBitmapDecoderInfo_GetDeviceManufacturer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchDeviceManufacturer;
    uint64_t wzDeviceManufacturer;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_GetDeviceManufacturer(IWICBitmapDecoderInfo *iface, UINT cchDeviceManufacturer, WCHAR *wzDeviceManufacturer, UINT *pcchActual)
{
    struct qemu_WICBitmapDecoderInfo_GetDeviceManufacturer call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_GETDEVICEMANUFACTURER);
    call.iface = (ULONG_PTR)info;
    call.cchDeviceManufacturer = cchDeviceManufacturer;
    call.wzDeviceManufacturer = (ULONG_PTR)wzDeviceManufacturer;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_GetDeviceManufacturer(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_GetDeviceManufacturer *c = (struct qemu_WICBitmapDecoderInfo_GetDeviceManufacturer *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoderInfo_GetDeviceManufacturer((IWICBitmapDecoderInfo *)info->host, c->cchDeviceManufacturer, QEMU_G2H(c->wzDeviceManufacturer), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICBitmapDecoderInfo_GetDeviceModels
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchDeviceModels;
    uint64_t wzDeviceModels;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_GetDeviceModels(IWICBitmapDecoderInfo *iface, UINT cchDeviceModels, WCHAR *wzDeviceModels, UINT *pcchActual)
{
    struct qemu_WICBitmapDecoderInfo_GetDeviceModels call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_GETDEVICEMODELS);
    call.iface = (ULONG_PTR)info;
    call.cchDeviceModels = cchDeviceModels;
    call.wzDeviceModels = (ULONG_PTR)wzDeviceModels;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_GetDeviceModels(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_GetDeviceModels *c = (struct qemu_WICBitmapDecoderInfo_GetDeviceModels *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoderInfo_GetDeviceModels((IWICBitmapDecoderInfo *)info->host, c->cchDeviceModels, QEMU_G2H(c->wzDeviceModels), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICBitmapDecoderInfo_GetMimeTypes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchMimeTypes;
    uint64_t wzMimeTypes;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_GetMimeTypes(IWICBitmapDecoderInfo *iface, UINT cchMimeTypes, WCHAR *wzMimeTypes, UINT *pcchActual)
{
    struct qemu_WICBitmapDecoderInfo_GetMimeTypes call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_GETMIMETYPES);
    call.iface = (ULONG_PTR)info;
    call.cchMimeTypes = cchMimeTypes;
    call.wzMimeTypes = (ULONG_PTR)wzMimeTypes;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_GetMimeTypes(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_GetMimeTypes *c = (struct qemu_WICBitmapDecoderInfo_GetMimeTypes *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoderInfo_GetMimeTypes((IWICBitmapDecoderInfo *)info->host, c->cchMimeTypes, QEMU_G2H(c->wzMimeTypes), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICBitmapDecoderInfo_GetFileExtensions
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchFileExtensions;
    uint64_t wzFileExtensions;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_GetFileExtensions(IWICBitmapDecoderInfo *iface, UINT cchFileExtensions, WCHAR *wzFileExtensions, UINT *pcchActual)
{
    struct qemu_WICBitmapDecoderInfo_GetFileExtensions call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_GETFILEEXTENSIONS);
    call.iface = (ULONG_PTR)info;
    call.cchFileExtensions = cchFileExtensions;
    call.wzFileExtensions = (ULONG_PTR)wzFileExtensions;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_GetFileExtensions(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_GetFileExtensions *c = (struct qemu_WICBitmapDecoderInfo_GetFileExtensions *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoderInfo_GetFileExtensions((IWICBitmapDecoderInfo *)info->host, c->cchFileExtensions, QEMU_G2H(c->wzFileExtensions), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICBitmapDecoderInfo_DoesSupportAnimation
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pfSupportAnimation;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_DoesSupportAnimation(IWICBitmapDecoderInfo *iface, BOOL *pfSupportAnimation)
{
    struct qemu_WICBitmapDecoderInfo_DoesSupportAnimation call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_DOESSUPPORTANIMATION);
    call.iface = (ULONG_PTR)info;
    call.pfSupportAnimation = (ULONG_PTR)pfSupportAnimation;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_DoesSupportAnimation(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_DoesSupportAnimation *c = (struct qemu_WICBitmapDecoderInfo_DoesSupportAnimation *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoderInfo_DoesSupportAnimation((IWICBitmapDecoderInfo *)info->host, QEMU_G2H(c->pfSupportAnimation));
}

#endif

struct qemu_WICBitmapDecoderInfo_DoesSupportChromaKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pfSupportChromaKey;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_DoesSupportChromaKey(IWICBitmapDecoderInfo *iface, BOOL *pfSupportChromaKey)
{
    struct qemu_WICBitmapDecoderInfo_DoesSupportChromaKey call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_DOESSUPPORTCHROMAKEY);
    call.iface = (ULONG_PTR)info;
    call.pfSupportChromaKey = (ULONG_PTR)pfSupportChromaKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_DoesSupportChromaKey(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_DoesSupportChromaKey *c = (struct qemu_WICBitmapDecoderInfo_DoesSupportChromaKey *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoderInfo_DoesSupportChromaKey((IWICBitmapDecoderInfo *)info->host, QEMU_G2H(c->pfSupportChromaKey));
}

#endif

struct qemu_WICBitmapDecoderInfo_DoesSupportLossless
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pfSupportLossless;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_DoesSupportLossless(IWICBitmapDecoderInfo *iface, BOOL *pfSupportLossless)
{
    struct qemu_WICBitmapDecoderInfo_DoesSupportLossless call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_DOESSUPPORTLOSSLESS);
    call.iface = (ULONG_PTR)info;
    call.pfSupportLossless = (ULONG_PTR)pfSupportLossless;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_DoesSupportLossless(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_DoesSupportLossless *c = (struct qemu_WICBitmapDecoderInfo_DoesSupportLossless *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoderInfo_DoesSupportLossless((IWICBitmapDecoderInfo *)info->host, QEMU_G2H(c->pfSupportLossless));
}

#endif

struct qemu_WICBitmapDecoderInfo_DoesSupportMultiframe
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pfSupportMultiframe;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_DoesSupportMultiframe(IWICBitmapDecoderInfo *iface, BOOL *pfSupportMultiframe)
{
    struct qemu_WICBitmapDecoderInfo_DoesSupportMultiframe call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_DOESSUPPORTMULTIFRAME);
    call.iface = (ULONG_PTR)info;
    call.pfSupportMultiframe = (ULONG_PTR)pfSupportMultiframe;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_DoesSupportMultiframe(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_DoesSupportMultiframe *c = (struct qemu_WICBitmapDecoderInfo_DoesSupportMultiframe *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoderInfo_DoesSupportMultiframe((IWICBitmapDecoderInfo *)info->host, QEMU_G2H(c->pfSupportMultiframe));
}

#endif

struct qemu_WICBitmapDecoderInfo_MatchesMimeType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t wzMimeType;
    uint64_t pfMatches;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_MatchesMimeType(IWICBitmapDecoderInfo *iface, LPCWSTR wzMimeType, BOOL *pfMatches)
{
    struct qemu_WICBitmapDecoderInfo_MatchesMimeType call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_MATCHESMIMETYPE);
    call.iface = (ULONG_PTR)info;
    call.wzMimeType = (ULONG_PTR)wzMimeType;
    call.pfMatches = (ULONG_PTR)pfMatches;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_MatchesMimeType(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_MatchesMimeType *c = (struct qemu_WICBitmapDecoderInfo_MatchesMimeType *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoderInfo_MatchesMimeType((IWICBitmapDecoderInfo *)info->host, QEMU_G2H(c->wzMimeType), QEMU_G2H(c->pfMatches));
}

#endif

struct qemu_WICBitmapDecoderInfo_GetPatterns
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cbSizePatterns;
    uint64_t pPatterns;
    uint64_t pcPatterns;
    uint64_t pcbPatternsActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_GetPatterns(IWICBitmapDecoderInfo *iface, UINT cbSizePatterns,
        WICBitmapPattern *pPatterns, UINT *pcPatterns, UINT *pcbPatternsActual)
{
    struct qemu_WICBitmapDecoderInfo_GetPatterns call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_GETPATTERNS);
    call.iface = (ULONG_PTR)info;
    call.cbSizePatterns = cbSizePatterns;
    call.pPatterns = (ULONG_PTR)pPatterns;
    call.pcPatterns = (ULONG_PTR)pcPatterns;
    call.pcbPatternsActual = (ULONG_PTR)pcbPatternsActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_GetPatterns(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_GetPatterns *c = (struct qemu_WICBitmapDecoderInfo_GetPatterns *)call;
    struct qemu_wic_info *info;
    WICBitmapPattern *patterns;
    UINT i, *count;

    WINE_TRACE("\n");
    info = QEMU_G2H(c->iface);
    patterns = QEMU_G2H(c->pPatterns);
    count = QEMU_G2H(c->pcPatterns);

    c->super.iret = IWICBitmapDecoderInfo_GetPatterns((IWICBitmapDecoderInfo *)info->host, c->cbSizePatterns, 
            patterns, count, QEMU_G2H(c->pcbPatternsActual));

#if GUEST_BIT != HOST_BIT
    if (SUCCEEDED(c->super.iret) && patterns)
    {
        struct qemu_WICBitmapPattern *p32 = (struct qemu_WICBitmapPattern *)patterns;

        /* So it seems that the size contains extra data for variable-lengths Patterns and Mask arrays. So
         * I guess we get away with just forwarding the 64 bit size request to the app.
         *
         * The Patterns and Mask pointers seem to be absolute pointers, so we don't have to adjust them to
         * account for the unexpected size of the WICBitmapPattern structure. */
        for (i = 0; i < *count; ++i)
            WICBitmapPattern_h2g(&p32[i], &patterns[i]);
    }
    else if (SUCCEEDED(c->super.iret) == WINCODEC_ERR_INSUFFICIENTBUFFER)
    {
        WINE_FIXME("The host returned WINCODEC_ERR_INSUFFICIENTBUFFER.\n");
    }
#endif
}

#endif

struct qemu_WICBitmapDecoderInfo_MatchesPattern
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIStream;
    uint64_t pfMatches;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_MatchesPattern(IWICBitmapDecoderInfo *iface,
        IStream *pIStream, BOOL *pfMatches)
{
    struct qemu_WICBitmapDecoderInfo_MatchesPattern call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_MATCHESPATTERN);
    call.iface = (ULONG_PTR)info;
    call.pIStream = (ULONG_PTR)pIStream;
    call.pfMatches = (ULONG_PTR)pfMatches;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_MatchesPattern(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_MatchesPattern *c = (struct qemu_WICBitmapDecoderInfo_MatchesPattern *)call;
    struct qemu_wic_info *info;
    struct istream_wrapper *stream;

    WINE_TRACE("\n");
    info = QEMU_G2H(c->iface);
    stream = istream_wrapper_create(c->pIStream);

    c->super.iret = IWICBitmapDecoderInfo_MatchesPattern((IWICBitmapDecoderInfo *)info->host,
            istream_wrapper_host_iface(stream), QEMU_G2H(c->pfMatches));

    if (stream)
        IStream_Release(istream_wrapper_host_iface(stream));
}

#endif

struct qemu_WICBitmapDecoderInfo_CreateInstance
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIBitmapDecoder;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapDecoderInfo_CreateInstance(IWICBitmapDecoderInfo *iface,
        IWICBitmapDecoder **ppIBitmapDecoder)
{
    struct qemu_WICBitmapDecoderInfo_CreateInstance call;
    struct qemu_wic_info *info = impl_from_IWICBitmapDecoderInfo(iface);
    struct qemu_wic_decoder *decoder;

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPDECODERINFO_CREATEINSTANCE);
    call.iface = (ULONG_PTR)info;
    call.ppIBitmapDecoder = (ULONG_PTR)ppIBitmapDecoder;

    qemu_syscall(&call.super);
    if (FAILED(call.super.iret))
        return call.super.iret;

    decoder = (struct qemu_wic_decoder *)(ULONG_PTR)call.ppIBitmapDecoder;
    WICBitmapDecoder_init_guest(decoder);
    *ppIBitmapDecoder = &decoder->IWICBitmapDecoder_iface;

    return call.super.iret;
}

#else

void qemu_WICBitmapDecoderInfo_CreateInstance(struct qemu_syscall *call)
{
    struct qemu_WICBitmapDecoderInfo_CreateInstance *c = (struct qemu_WICBitmapDecoderInfo_CreateInstance *)call;
    struct qemu_wic_info *info;
    IWICBitmapDecoder *host;
    struct qemu_wic_decoder *decoder;

    WINE_TRACE("\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapDecoderInfo_CreateInstance((IWICBitmapDecoderInfo *)info->host, 
            c->ppIBitmapDecoder ? &host : NULL);
    if (FAILED(c->super.iret))
        return;

    decoder = WICBitmapDecoder_create_host(host);
    if (!decoder)
    {
        c->super.iret = E_OUTOFMEMORY;
        return;
    }
    c->ppIBitmapDecoder = QEMU_H2G(decoder);
}

#endif

struct qemu_WICBitmapEncoderInfo_GetContainerFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pguidContainerFormat;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_info *impl_from_IWICBitmapEncoderInfo(IWICBitmapEncoderInfo *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_info, IWICComponentInfo_iface);
}

static HRESULT WINAPI WICBitmapEncoderInfo_GetContainerFormat(IWICBitmapEncoderInfo *iface, GUID *pguidContainerFormat)
{
    struct qemu_WICBitmapEncoderInfo_GetContainerFormat call;
    struct qemu_wic_info *info = impl_from_IWICBitmapEncoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODERINFO_GETCONTAINERFORMAT);
    call.iface = (ULONG_PTR)info;
    call.pguidContainerFormat = (ULONG_PTR)pguidContainerFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoderInfo_GetContainerFormat(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoderInfo_GetContainerFormat *c = (struct qemu_WICBitmapEncoderInfo_GetContainerFormat *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoderInfo_GetContainerFormat((IWICBitmapEncoderInfo *)info->host, QEMU_G2H(c->pguidContainerFormat));
}

#endif

struct qemu_WICBitmapEncoderInfo_GetPixelFormats
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cFormats;
    uint64_t pguidPixelFormats;
    uint64_t pcActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoderInfo_GetPixelFormats(IWICBitmapEncoderInfo *iface, UINT cFormats, GUID *pguidPixelFormats, UINT *pcActual)
{
    struct qemu_WICBitmapEncoderInfo_GetPixelFormats call;
    struct qemu_wic_info *info = impl_from_IWICBitmapEncoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODERINFO_GETPIXELFORMATS);
    call.iface = (ULONG_PTR)info;
    call.cFormats = cFormats;
    call.pguidPixelFormats = (ULONG_PTR)pguidPixelFormats;
    call.pcActual = (ULONG_PTR)pcActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoderInfo_GetPixelFormats(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoderInfo_GetPixelFormats *c = (struct qemu_WICBitmapEncoderInfo_GetPixelFormats *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoderInfo_GetPixelFormats((IWICBitmapEncoderInfo *)info->host, c->cFormats, QEMU_G2H(c->pguidPixelFormats), QEMU_G2H(c->pcActual));
}

#endif

struct qemu_WICBitmapEncoderInfo_GetColorManagementVersion
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchColorManagementVersion;
    uint64_t wzColorManagementVersion;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoderInfo_GetColorManagementVersion(IWICBitmapEncoderInfo *iface, UINT cchColorManagementVersion, WCHAR *wzColorManagementVersion, UINT *pcchActual)
{
    struct qemu_WICBitmapEncoderInfo_GetColorManagementVersion call;
    struct qemu_wic_info *info = impl_from_IWICBitmapEncoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODERINFO_GETCOLORMANAGEMENTVERSION);
    call.iface = (ULONG_PTR)info;
    call.cchColorManagementVersion = cchColorManagementVersion;
    call.wzColorManagementVersion = (ULONG_PTR)wzColorManagementVersion;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoderInfo_GetColorManagementVersion(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoderInfo_GetColorManagementVersion *c = (struct qemu_WICBitmapEncoderInfo_GetColorManagementVersion *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoderInfo_GetColorManagementVersion((IWICBitmapEncoderInfo *)info->host, c->cchColorManagementVersion, QEMU_G2H(c->wzColorManagementVersion), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICBitmapEncoderInfo_GetDeviceManufacturer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchDeviceManufacturer;
    uint64_t wzDeviceManufacturer;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoderInfo_GetDeviceManufacturer(IWICBitmapEncoderInfo *iface, UINT cchDeviceManufacturer, WCHAR *wzDeviceManufacturer, UINT *pcchActual)
{
    struct qemu_WICBitmapEncoderInfo_GetDeviceManufacturer call;
    struct qemu_wic_info *info = impl_from_IWICBitmapEncoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODERINFO_GETDEVICEMANUFACTURER);
    call.iface = (ULONG_PTR)info;
    call.cchDeviceManufacturer = cchDeviceManufacturer;
    call.wzDeviceManufacturer = (ULONG_PTR)wzDeviceManufacturer;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoderInfo_GetDeviceManufacturer(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoderInfo_GetDeviceManufacturer *c = (struct qemu_WICBitmapEncoderInfo_GetDeviceManufacturer *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoderInfo_GetDeviceManufacturer((IWICBitmapEncoderInfo *)info->host, c->cchDeviceManufacturer, QEMU_G2H(c->wzDeviceManufacturer), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICBitmapEncoderInfo_GetDeviceModels
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchDeviceModels;
    uint64_t wzDeviceModels;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoderInfo_GetDeviceModels(IWICBitmapEncoderInfo *iface, UINT cchDeviceModels, WCHAR *wzDeviceModels, UINT *pcchActual)
{
    struct qemu_WICBitmapEncoderInfo_GetDeviceModels call;
    struct qemu_wic_info *info = impl_from_IWICBitmapEncoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODERINFO_GETDEVICEMODELS);
    call.iface = (ULONG_PTR)info;
    call.cchDeviceModels = cchDeviceModels;
    call.wzDeviceModels = (ULONG_PTR)wzDeviceModels;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoderInfo_GetDeviceModels(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoderInfo_GetDeviceModels *c = (struct qemu_WICBitmapEncoderInfo_GetDeviceModels *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoderInfo_GetDeviceModels((IWICBitmapEncoderInfo *)info->host, c->cchDeviceModels, QEMU_G2H(c->wzDeviceModels), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICBitmapEncoderInfo_GetMimeTypes
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchMimeTypes;
    uint64_t wzMimeTypes;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoderInfo_GetMimeTypes(IWICBitmapEncoderInfo *iface, UINT cchMimeTypes, WCHAR *wzMimeTypes, UINT *pcchActual)
{
    struct qemu_WICBitmapEncoderInfo_GetMimeTypes call;
    struct qemu_wic_info *info = impl_from_IWICBitmapEncoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODERINFO_GETMIMETYPES);
    call.iface = (ULONG_PTR)info;
    call.cchMimeTypes = cchMimeTypes;
    call.wzMimeTypes = (ULONG_PTR)wzMimeTypes;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoderInfo_GetMimeTypes(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoderInfo_GetMimeTypes *c = (struct qemu_WICBitmapEncoderInfo_GetMimeTypes *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoderInfo_GetMimeTypes((IWICBitmapEncoderInfo *)info->host, c->cchMimeTypes, QEMU_G2H(c->wzMimeTypes), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICBitmapEncoderInfo_GetFileExtensions
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cchFileExtensions;
    uint64_t wzFileExtensions;
    uint64_t pcchActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoderInfo_GetFileExtensions(IWICBitmapEncoderInfo *iface, UINT cchFileExtensions, WCHAR *wzFileExtensions, UINT *pcchActual)
{
    struct qemu_WICBitmapEncoderInfo_GetFileExtensions call;
    struct qemu_wic_info *info = impl_from_IWICBitmapEncoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODERINFO_GETFILEEXTENSIONS);
    call.iface = (ULONG_PTR)info;
    call.cchFileExtensions = cchFileExtensions;
    call.wzFileExtensions = (ULONG_PTR)wzFileExtensions;
    call.pcchActual = (ULONG_PTR)pcchActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoderInfo_GetFileExtensions(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoderInfo_GetFileExtensions *c = (struct qemu_WICBitmapEncoderInfo_GetFileExtensions *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoderInfo_GetFileExtensions((IWICBitmapEncoderInfo *)info->host, c->cchFileExtensions, QEMU_G2H(c->wzFileExtensions), QEMU_G2H(c->pcchActual));
}

#endif

struct qemu_WICBitmapEncoderInfo_DoesSupportAnimation
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pfSupportAnimation;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoderInfo_DoesSupportAnimation(IWICBitmapEncoderInfo *iface, BOOL *pfSupportAnimation)
{
    struct qemu_WICBitmapEncoderInfo_DoesSupportAnimation call;
    struct qemu_wic_info *info = impl_from_IWICBitmapEncoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODERINFO_DOESSUPPORTANIMATION);
    call.iface = (ULONG_PTR)info;
    call.pfSupportAnimation = (ULONG_PTR)pfSupportAnimation;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoderInfo_DoesSupportAnimation(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoderInfo_DoesSupportAnimation *c = (struct qemu_WICBitmapEncoderInfo_DoesSupportAnimation *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoderInfo_DoesSupportAnimation((IWICBitmapEncoderInfo *)info->host, QEMU_G2H(c->pfSupportAnimation));
}

#endif

struct qemu_WICBitmapEncoderInfo_DoesSupportChromaKey
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pfSupportChromaKey;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoderInfo_DoesSupportChromaKey(IWICBitmapEncoderInfo *iface, BOOL *pfSupportChromaKey)
{
    struct qemu_WICBitmapEncoderInfo_DoesSupportChromaKey call;
    struct qemu_wic_info *info = impl_from_IWICBitmapEncoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODERINFO_DOESSUPPORTCHROMAKEY);
    call.iface = (ULONG_PTR)info;
    call.pfSupportChromaKey = (ULONG_PTR)pfSupportChromaKey;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoderInfo_DoesSupportChromaKey(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoderInfo_DoesSupportChromaKey *c = (struct qemu_WICBitmapEncoderInfo_DoesSupportChromaKey *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoderInfo_DoesSupportChromaKey((IWICBitmapEncoderInfo *)info->host, QEMU_G2H(c->pfSupportChromaKey));
}

#endif

struct qemu_WICBitmapEncoderInfo_DoesSupportLossless
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pfSupportLossless;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoderInfo_DoesSupportLossless(IWICBitmapEncoderInfo *iface, BOOL *pfSupportLossless)
{
    struct qemu_WICBitmapEncoderInfo_DoesSupportLossless call;
    struct qemu_wic_info *info = impl_from_IWICBitmapEncoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODERINFO_DOESSUPPORTLOSSLESS);
    call.iface = (ULONG_PTR)info;
    call.pfSupportLossless = (ULONG_PTR)pfSupportLossless;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoderInfo_DoesSupportLossless(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoderInfo_DoesSupportLossless *c = (struct qemu_WICBitmapEncoderInfo_DoesSupportLossless *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoderInfo_DoesSupportLossless((IWICBitmapEncoderInfo *)info->host, QEMU_G2H(c->pfSupportLossless));
}

#endif

struct qemu_WICBitmapEncoderInfo_DoesSupportMultiframe
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pfSupportMultiframe;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoderInfo_DoesSupportMultiframe(IWICBitmapEncoderInfo *iface, BOOL *pfSupportMultiframe)
{
    struct qemu_WICBitmapEncoderInfo_DoesSupportMultiframe call;
    struct qemu_wic_info *info = impl_from_IWICBitmapEncoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODERINFO_DOESSUPPORTMULTIFRAME);
    call.iface = (ULONG_PTR)info;
    call.pfSupportMultiframe = (ULONG_PTR)pfSupportMultiframe;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoderInfo_DoesSupportMultiframe(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoderInfo_DoesSupportMultiframe *c = (struct qemu_WICBitmapEncoderInfo_DoesSupportMultiframe *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoderInfo_DoesSupportMultiframe((IWICBitmapEncoderInfo *)info->host, QEMU_G2H(c->pfSupportMultiframe));
}

#endif

struct qemu_WICBitmapEncoderInfo_MatchesMimeType
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t wzMimeType;
    uint64_t pfMatches;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoderInfo_MatchesMimeType(IWICBitmapEncoderInfo *iface, LPCWSTR wzMimeType, BOOL *pfMatches)
{
    struct qemu_WICBitmapEncoderInfo_MatchesMimeType call;
    struct qemu_wic_info *info = impl_from_IWICBitmapEncoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODERINFO_MATCHESMIMETYPE);
    call.iface = (ULONG_PTR)info;
    call.wzMimeType = (ULONG_PTR)wzMimeType;
    call.pfMatches = (ULONG_PTR)pfMatches;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoderInfo_MatchesMimeType(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoderInfo_MatchesMimeType *c = (struct qemu_WICBitmapEncoderInfo_MatchesMimeType *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoderInfo_MatchesMimeType((IWICBitmapEncoderInfo *)info->host, QEMU_G2H(c->wzMimeType), QEMU_G2H(c->pfMatches));
}

#endif

struct qemu_WICBitmapEncoderInfo_CreateInstance
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIBitmapEncoder;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapEncoderInfo_CreateInstance(IWICBitmapEncoderInfo *iface, IWICBitmapEncoder **ppIBitmapEncoder)
{
    struct qemu_WICBitmapEncoderInfo_CreateInstance call;
    struct qemu_wic_info *info = impl_from_IWICBitmapEncoderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPENCODERINFO_CREATEINSTANCE);
    call.iface = (ULONG_PTR)info;
    call.ppIBitmapEncoder = (ULONG_PTR)ppIBitmapEncoder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapEncoderInfo_CreateInstance(struct qemu_syscall *call)
{
    struct qemu_WICBitmapEncoderInfo_CreateInstance *c = (struct qemu_WICBitmapEncoderInfo_CreateInstance *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapEncoderInfo_CreateInstance((IWICBitmapEncoderInfo *)info->host, QEMU_G2H(c->ppIBitmapEncoder));
}

#endif

struct qemu_WICFormatConverterInfo_GetPixelFormats
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cFormats;
    uint64_t pguidPixelFormats;
    uint64_t pcActual;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_info *impl_from_IWICFormatConverterInfo(IWICFormatConverterInfo *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_info, IWICComponentInfo_iface);
}

static HRESULT WINAPI WICFormatConverterInfo_GetPixelFormats(IWICFormatConverterInfo *iface, UINT cFormats, GUID *pguidPixelFormats, UINT *pcActual)
{
    struct qemu_WICFormatConverterInfo_GetPixelFormats call;
    struct qemu_wic_info *info = impl_from_IWICFormatConverterInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICFORMATCONVERTERINFO_GETPIXELFORMATS);
    call.iface = (ULONG_PTR)info;
    call.cFormats = cFormats;
    call.pguidPixelFormats = (ULONG_PTR)pguidPixelFormats;
    call.pcActual = (ULONG_PTR)pcActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICFormatConverterInfo_GetPixelFormats(struct qemu_syscall *call)
{
    struct qemu_WICFormatConverterInfo_GetPixelFormats *c = (struct qemu_WICFormatConverterInfo_GetPixelFormats *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICFormatConverterInfo_GetPixelFormats((IWICFormatConverterInfo *)info->host, c->cFormats, QEMU_G2H(c->pguidPixelFormats), QEMU_G2H(c->pcActual));
}

#endif

struct qemu_WICFormatConverterInfo_CreateInstance
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIFormatConverter;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICFormatConverterInfo_CreateInstance(IWICFormatConverterInfo *iface, IWICFormatConverter **ppIFormatConverter)
{
    struct qemu_WICFormatConverterInfo_CreateInstance call;
    struct qemu_wic_info *info = impl_from_IWICFormatConverterInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICFORMATCONVERTERINFO_CREATEINSTANCE);
    call.iface = (ULONG_PTR)info;
    call.ppIFormatConverter = (ULONG_PTR)ppIFormatConverter;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICFormatConverterInfo_CreateInstance(struct qemu_syscall *call)
{
    struct qemu_WICFormatConverterInfo_CreateInstance *c = (struct qemu_WICFormatConverterInfo_CreateInstance *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICFormatConverterInfo_CreateInstance((IWICFormatConverterInfo *)info->host, QEMU_G2H(c->ppIFormatConverter));
}

#endif

struct qemu_WICPixelFormatInfo2_GetFormatGUID
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pFormat;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_info *impl_from_IWICPixelFormatInfo2(IWICPixelFormatInfo2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_info, IWICComponentInfo_iface);
}

static HRESULT WINAPI WICPixelFormatInfo2_GetFormatGUID(IWICPixelFormatInfo2 *iface, GUID *pFormat)
{
    struct qemu_WICPixelFormatInfo2_GetFormatGUID call;
    struct qemu_wic_info *info = impl_from_IWICPixelFormatInfo2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPIXELFORMATINFO2_GETFORMATGUID);
    call.iface = (ULONG_PTR)info;
    call.pFormat = (ULONG_PTR)pFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPixelFormatInfo2_GetFormatGUID(struct qemu_syscall *call)
{
    struct qemu_WICPixelFormatInfo2_GetFormatGUID *c = (struct qemu_WICPixelFormatInfo2_GetFormatGUID *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICPixelFormatInfo2_GetFormatGUID((IWICPixelFormatInfo2 *)info->host, QEMU_G2H(c->pFormat));
}

#endif

struct qemu_WICPixelFormatInfo2_GetColorContext
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppIColorContext;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPixelFormatInfo2_GetColorContext(IWICPixelFormatInfo2 *iface, IWICColorContext **ppIColorContext)
{
    struct qemu_WICPixelFormatInfo2_GetColorContext call;
    struct qemu_wic_info *info = impl_from_IWICPixelFormatInfo2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPIXELFORMATINFO2_GETCOLORCONTEXT);
    call.iface = (ULONG_PTR)info;
    call.ppIColorContext = (ULONG_PTR)ppIColorContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPixelFormatInfo2_GetColorContext(struct qemu_syscall *call)
{
    struct qemu_WICPixelFormatInfo2_GetColorContext *c = (struct qemu_WICPixelFormatInfo2_GetColorContext *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICPixelFormatInfo2_GetColorContext((IWICPixelFormatInfo2 *)info->host, QEMU_G2H(c->ppIColorContext));
}

#endif

struct qemu_WICPixelFormatInfo2_GetBitsPerPixel
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t puiBitsPerPixel;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPixelFormatInfo2_GetBitsPerPixel(IWICPixelFormatInfo2 *iface, UINT *puiBitsPerPixel)
{
    struct qemu_WICPixelFormatInfo2_GetBitsPerPixel call;
    struct qemu_wic_info *info = impl_from_IWICPixelFormatInfo2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPIXELFORMATINFO2_GETBITSPERPIXEL);
    call.iface = (ULONG_PTR)info;
    call.puiBitsPerPixel = (ULONG_PTR)puiBitsPerPixel;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPixelFormatInfo2_GetBitsPerPixel(struct qemu_syscall *call)
{
    struct qemu_WICPixelFormatInfo2_GetBitsPerPixel *c = (struct qemu_WICPixelFormatInfo2_GetBitsPerPixel *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICPixelFormatInfo2_GetBitsPerPixel((IWICPixelFormatInfo2 *)info->host, QEMU_G2H(c->puiBitsPerPixel));
}

#endif

struct qemu_WICPixelFormatInfo2_GetChannelCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t puiChannelCount;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPixelFormatInfo2_GetChannelCount(IWICPixelFormatInfo2 *iface, UINT *puiChannelCount)
{
    struct qemu_WICPixelFormatInfo2_GetChannelCount call;
    struct qemu_wic_info *info = impl_from_IWICPixelFormatInfo2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPIXELFORMATINFO2_GETCHANNELCOUNT);
    call.iface = (ULONG_PTR)info;
    call.puiChannelCount = (ULONG_PTR)puiChannelCount;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPixelFormatInfo2_GetChannelCount(struct qemu_syscall *call)
{
    struct qemu_WICPixelFormatInfo2_GetChannelCount *c = (struct qemu_WICPixelFormatInfo2_GetChannelCount *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICPixelFormatInfo2_GetChannelCount((IWICPixelFormatInfo2 *)info->host, QEMU_G2H(c->puiChannelCount));
}

#endif

struct qemu_WICPixelFormatInfo2_GetChannelMask
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t uiChannelIndex;
    uint64_t cbMaskBuffer;
    uint64_t pbMaskBuffer;
    uint64_t pcbActual;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPixelFormatInfo2_GetChannelMask(IWICPixelFormatInfo2 *iface, UINT uiChannelIndex, UINT cbMaskBuffer, BYTE *pbMaskBuffer, UINT *pcbActual)
{
    struct qemu_WICPixelFormatInfo2_GetChannelMask call;
    struct qemu_wic_info *info = impl_from_IWICPixelFormatInfo2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPIXELFORMATINFO2_GETCHANNELMASK);
    call.iface = (ULONG_PTR)info;
    call.uiChannelIndex = uiChannelIndex;
    call.cbMaskBuffer = cbMaskBuffer;
    call.pbMaskBuffer = (ULONG_PTR)pbMaskBuffer;
    call.pcbActual = (ULONG_PTR)pcbActual;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPixelFormatInfo2_GetChannelMask(struct qemu_syscall *call)
{
    struct qemu_WICPixelFormatInfo2_GetChannelMask *c = (struct qemu_WICPixelFormatInfo2_GetChannelMask *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICPixelFormatInfo2_GetChannelMask((IWICPixelFormatInfo2 *)info->host, c->uiChannelIndex, c->cbMaskBuffer, QEMU_G2H(c->pbMaskBuffer), QEMU_G2H(c->pcbActual));
}

#endif

struct qemu_WICPixelFormatInfo2_SupportsTransparency
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pfSupportsTransparency;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPixelFormatInfo2_SupportsTransparency(IWICPixelFormatInfo2 *iface, BOOL *pfSupportsTransparency)
{
    struct qemu_WICPixelFormatInfo2_SupportsTransparency call;
    struct qemu_wic_info *info = impl_from_IWICPixelFormatInfo2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPIXELFORMATINFO2_SUPPORTSTRANSPARENCY);
    call.iface = (ULONG_PTR)info;
    call.pfSupportsTransparency = (ULONG_PTR)pfSupportsTransparency;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPixelFormatInfo2_SupportsTransparency(struct qemu_syscall *call)
{
    struct qemu_WICPixelFormatInfo2_SupportsTransparency *c = (struct qemu_WICPixelFormatInfo2_SupportsTransparency *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICPixelFormatInfo2_SupportsTransparency((IWICPixelFormatInfo2 *)info->host, QEMU_G2H(c->pfSupportsTransparency));
}

#endif

struct qemu_WICPixelFormatInfo2_GetNumericRepresentation
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pNumericRepresentation;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICPixelFormatInfo2_GetNumericRepresentation(IWICPixelFormatInfo2 *iface, WICPixelFormatNumericRepresentation *pNumericRepresentation)
{
    struct qemu_WICPixelFormatInfo2_GetNumericRepresentation call;
    struct qemu_wic_info *info = impl_from_IWICPixelFormatInfo2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICPIXELFORMATINFO2_GETNUMERICREPRESENTATION);
    call.iface = (ULONG_PTR)info;
    call.pNumericRepresentation = (ULONG_PTR)pNumericRepresentation;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICPixelFormatInfo2_GetNumericRepresentation(struct qemu_syscall *call)
{
    struct qemu_WICPixelFormatInfo2_GetNumericRepresentation *c = (struct qemu_WICPixelFormatInfo2_GetNumericRepresentation *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICPixelFormatInfo2_GetNumericRepresentation((IWICPixelFormatInfo2 *)info->host, QEMU_G2H(c->pNumericRepresentation));
}

#endif

struct qemu_WICMetadataReaderInfo_GetMetadataFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_info *impl_from_IWICMetadataReaderInfo(IWICMetadataReaderInfo *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_info, IWICComponentInfo_iface);
}

static HRESULT WINAPI WICMetadataReaderInfo_GetMetadataFormat(IWICMetadataReaderInfo *iface, GUID *format)
{
    struct qemu_WICMetadataReaderInfo_GetMetadataFormat call;
    struct qemu_wic_info *info = impl_from_IWICMetadataReaderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAREADERINFO_GETMETADATAFORMAT);
    call.iface = (ULONG_PTR)info;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataReaderInfo_GetMetadataFormat(struct qemu_syscall *call)
{
    struct qemu_WICMetadataReaderInfo_GetMetadataFormat *c = (struct qemu_WICMetadataReaderInfo_GetMetadataFormat *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataReaderInfo_GetMetadataFormat((IWICMetadataReaderInfo *)info->host, QEMU_G2H(c->format));
}

#endif

struct qemu_WICMetadataReaderInfo_GetContainerFormats
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t length;
    uint64_t formats;
    uint64_t actual_length;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataReaderInfo_GetContainerFormats(IWICMetadataReaderInfo *iface, UINT length, GUID *formats, UINT *actual_length)
{
    struct qemu_WICMetadataReaderInfo_GetContainerFormats call;
    struct qemu_wic_info *info = impl_from_IWICMetadataReaderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAREADERINFO_GETCONTAINERFORMATS);
    call.iface = (ULONG_PTR)info;
    call.length = length;
    call.formats = (ULONG_PTR)formats;
    call.actual_length = (ULONG_PTR)actual_length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataReaderInfo_GetContainerFormats(struct qemu_syscall *call)
{
    struct qemu_WICMetadataReaderInfo_GetContainerFormats *c = (struct qemu_WICMetadataReaderInfo_GetContainerFormats *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataReaderInfo_GetContainerFormats((IWICMetadataReaderInfo *)info->host, c->length, QEMU_G2H(c->formats), QEMU_G2H(c->actual_length));
}

#endif

struct qemu_WICMetadataReaderInfo_GetDeviceManufacturer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t length;
    uint64_t manufacturer;
    uint64_t actual_length;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataReaderInfo_GetDeviceManufacturer(IWICMetadataReaderInfo *iface, UINT length, WCHAR *manufacturer, UINT *actual_length)
{
    struct qemu_WICMetadataReaderInfo_GetDeviceManufacturer call;
    struct qemu_wic_info *info = impl_from_IWICMetadataReaderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAREADERINFO_GETDEVICEMANUFACTURER);
    call.iface = (ULONG_PTR)info;
    call.length = length;
    call.manufacturer = (ULONG_PTR)manufacturer;
    call.actual_length = (ULONG_PTR)actual_length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataReaderInfo_GetDeviceManufacturer(struct qemu_syscall *call)
{
    struct qemu_WICMetadataReaderInfo_GetDeviceManufacturer *c = (struct qemu_WICMetadataReaderInfo_GetDeviceManufacturer *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataReaderInfo_GetDeviceManufacturer((IWICMetadataReaderInfo *)info->host, c->length, QEMU_G2H(c->manufacturer), QEMU_G2H(c->actual_length));
}

#endif

struct qemu_WICMetadataReaderInfo_GetDeviceModels
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t length;
    uint64_t models;
    uint64_t actual_length;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataReaderInfo_GetDeviceModels(IWICMetadataReaderInfo *iface, UINT length, WCHAR *models, UINT *actual_length)
{
    struct qemu_WICMetadataReaderInfo_GetDeviceModels call;
    struct qemu_wic_info *info = impl_from_IWICMetadataReaderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAREADERINFO_GETDEVICEMODELS);
    call.iface = (ULONG_PTR)info;
    call.length = length;
    call.models = (ULONG_PTR)models;
    call.actual_length = (ULONG_PTR)actual_length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataReaderInfo_GetDeviceModels(struct qemu_syscall *call)
{
    struct qemu_WICMetadataReaderInfo_GetDeviceModels *c = (struct qemu_WICMetadataReaderInfo_GetDeviceModels *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataReaderInfo_GetDeviceModels((IWICMetadataReaderInfo *)info->host, c->length, QEMU_G2H(c->models), QEMU_G2H(c->actual_length));
}

#endif

struct qemu_WICMetadataReaderInfo_DoesRequireFullStream
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataReaderInfo_DoesRequireFullStream(IWICMetadataReaderInfo *iface, BOOL *param)
{
    struct qemu_WICMetadataReaderInfo_DoesRequireFullStream call;
    struct qemu_wic_info *info = impl_from_IWICMetadataReaderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAREADERINFO_DOESREQUIREFULLSTREAM);
    call.iface = (ULONG_PTR)info;
    call.param = (ULONG_PTR)param;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataReaderInfo_DoesRequireFullStream(struct qemu_syscall *call)
{
    struct qemu_WICMetadataReaderInfo_DoesRequireFullStream *c = (struct qemu_WICMetadataReaderInfo_DoesRequireFullStream *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataReaderInfo_DoesRequireFullStream((IWICMetadataReaderInfo *)info->host, QEMU_G2H(c->param));
}

#endif

struct qemu_WICMetadataReaderInfo_DoesSupportPadding
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataReaderInfo_DoesSupportPadding(IWICMetadataReaderInfo *iface, BOOL *param)
{
    struct qemu_WICMetadataReaderInfo_DoesSupportPadding call;
    struct qemu_wic_info *info = impl_from_IWICMetadataReaderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAREADERINFO_DOESSUPPORTPADDING);
    call.iface = (ULONG_PTR)info;
    call.param = (ULONG_PTR)param;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataReaderInfo_DoesSupportPadding(struct qemu_syscall *call)
{
    struct qemu_WICMetadataReaderInfo_DoesSupportPadding *c = (struct qemu_WICMetadataReaderInfo_DoesSupportPadding *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataReaderInfo_DoesSupportPadding((IWICMetadataReaderInfo *)info->host, QEMU_G2H(c->param));
}

#endif

struct qemu_WICMetadataReaderInfo_DoesRequireFixedSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t param;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataReaderInfo_DoesRequireFixedSize(IWICMetadataReaderInfo *iface, BOOL *param)
{
    struct qemu_WICMetadataReaderInfo_DoesRequireFixedSize call;
    struct qemu_wic_info *info = impl_from_IWICMetadataReaderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAREADERINFO_DOESREQUIREFIXEDSIZE);
    call.iface = (ULONG_PTR)info;
    call.param = (ULONG_PTR)param;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataReaderInfo_DoesRequireFixedSize(struct qemu_syscall *call)
{
    struct qemu_WICMetadataReaderInfo_DoesRequireFixedSize *c = (struct qemu_WICMetadataReaderInfo_DoesRequireFixedSize *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataReaderInfo_DoesRequireFixedSize((IWICMetadataReaderInfo *)info->host, QEMU_G2H(c->param));
}

#endif

struct qemu_WICMetadataReaderInfo_GetPatterns
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t container_guid;
    uint64_t length;
    uint64_t patterns;
    uint64_t count;
    uint64_t actual_length;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataReaderInfo_GetPatterns(IWICMetadataReaderInfo *iface, REFGUID container_guid, UINT length, WICMetadataPattern *patterns, UINT *count, UINT *actual_length)
{
    struct qemu_WICMetadataReaderInfo_GetPatterns call;
    struct qemu_wic_info *info = impl_from_IWICMetadataReaderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAREADERINFO_GETPATTERNS);
    call.iface = (ULONG_PTR)info;
    call.container_guid = (ULONG_PTR)container_guid;
    call.length = length;
    call.patterns = (ULONG_PTR)patterns;
    call.count = (ULONG_PTR)count;
    call.actual_length = (ULONG_PTR)actual_length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataReaderInfo_GetPatterns(struct qemu_syscall *call)
{
    struct qemu_WICMetadataReaderInfo_GetPatterns *c = (struct qemu_WICMetadataReaderInfo_GetPatterns *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataReaderInfo_GetPatterns((IWICMetadataReaderInfo *)info->host, QEMU_G2H(c->container_guid), c->length, QEMU_G2H(c->patterns), QEMU_G2H(c->count), QEMU_G2H(c->actual_length));
}

#endif

struct qemu_WICMetadataReaderInfo_MatchesPattern
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t container_guid;
    uint64_t stream;
    uint64_t matches;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataReaderInfo_MatchesPattern(IWICMetadataReaderInfo *iface, REFGUID container_guid, IStream *stream, BOOL *matches)
{
    struct qemu_WICMetadataReaderInfo_MatchesPattern call;
    struct qemu_wic_info *info = impl_from_IWICMetadataReaderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAREADERINFO_MATCHESPATTERN);
    call.iface = (ULONG_PTR)info;
    call.container_guid = (ULONG_PTR)container_guid;
    call.stream = (ULONG_PTR)stream;
    call.matches = (ULONG_PTR)matches;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataReaderInfo_MatchesPattern(struct qemu_syscall *call)
{
    struct qemu_WICMetadataReaderInfo_MatchesPattern *c = (struct qemu_WICMetadataReaderInfo_MatchesPattern *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataReaderInfo_MatchesPattern((IWICMetadataReaderInfo *)info->host, QEMU_G2H(c->container_guid), QEMU_G2H(c->stream), QEMU_G2H(c->matches));
}

#endif

struct qemu_WICMetadataReaderInfo_CreateInstance
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t reader;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICMetadataReaderInfo_CreateInstance(IWICMetadataReaderInfo *iface, IWICMetadataReader **reader)
{
    struct qemu_WICMetadataReaderInfo_CreateInstance call;
    struct qemu_wic_info *info = impl_from_IWICMetadataReaderInfo(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICMETADATAREADERINFO_CREATEINSTANCE);
    call.iface = (ULONG_PTR)info;
    call.reader = (ULONG_PTR)reader;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICMetadataReaderInfo_CreateInstance(struct qemu_syscall *call)
{
    struct qemu_WICMetadataReaderInfo_CreateInstance *c = (struct qemu_WICMetadataReaderInfo_CreateInstance *)call;
    struct qemu_wic_info *info;

    WINE_FIXME("Unverified!\n");
    info = QEMU_G2H(c->iface);

    c->super.iret = IWICMetadataReaderInfo_CreateInstance((IWICMetadataReaderInfo *)info->host, QEMU_G2H(c->reader));
}

#endif

struct qemu_EnumUnknown_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_enum *impl_from_IEnumUnknown(IEnumUnknown *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_enum, IEnumUnknown_iface);
}

static HRESULT WINAPI EnumUnknown_QueryInterface(IEnumUnknown *iface, REFIID iid, void **ppv)
{
    struct qemu_EnumUnknown_QueryInterface call;
    struct qemu_wic_enum *wic_enum = impl_from_IEnumUnknown(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMUNKNOWN_QUERYINTERFACE);
    call.iface = (ULONG_PTR)wic_enum;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumUnknown_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_EnumUnknown_QueryInterface *c = (struct qemu_EnumUnknown_QueryInterface *)call;
    struct qemu_wic_enum *wic_enum;

    WINE_FIXME("Unverified!\n");
    wic_enum = QEMU_G2H(c->iface);

    c->super.iret = IEnumUnknown_QueryInterface(wic_enum->host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_EnumUnknown_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI EnumUnknown_AddRef(IEnumUnknown *iface)
{
    struct qemu_EnumUnknown_AddRef call;
    struct qemu_wic_enum *wic_enum = impl_from_IEnumUnknown(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMUNKNOWN_ADDREF);
    call.iface = (ULONG_PTR)wic_enum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumUnknown_AddRef(struct qemu_syscall *call)
{
    struct qemu_EnumUnknown_AddRef *c = (struct qemu_EnumUnknown_AddRef *)call;
    struct qemu_wic_enum *wic_enum;

    WINE_FIXME("Unverified!\n");
    wic_enum = QEMU_G2H(c->iface);

    c->super.iret = IEnumUnknown_AddRef(wic_enum->host);
}

#endif

struct qemu_EnumUnknown_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI EnumUnknown_Release(IEnumUnknown *iface)
{
    struct qemu_EnumUnknown_Release call;
    struct qemu_wic_enum *wic_enum = impl_from_IEnumUnknown(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMUNKNOWN_RELEASE);
    call.iface = (ULONG_PTR)wic_enum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumUnknown_Release(struct qemu_syscall *call)
{
    struct qemu_EnumUnknown_Release *c = (struct qemu_EnumUnknown_Release *)call;
    struct qemu_wic_enum *wic_enum;

    WINE_FIXME("Unverified!\n");
    wic_enum = QEMU_G2H(c->iface);

    c->super.iret = IEnumUnknown_Release(wic_enum->host);
}

#endif

struct qemu_EnumUnknown_Next
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t celt;
    uint64_t rgelt;
    uint64_t pceltFetched;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI EnumUnknown_Next(IEnumUnknown *iface, ULONG celt, IUnknown **rgelt, ULONG *pceltFetched)
{
    struct qemu_EnumUnknown_Next call;
    struct qemu_wic_enum *wic_enum = impl_from_IEnumUnknown(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMUNKNOWN_NEXT);
    call.iface = (ULONG_PTR)wic_enum;
    call.celt = celt;
    call.rgelt = (ULONG_PTR)rgelt;
    call.pceltFetched = (ULONG_PTR)pceltFetched;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumUnknown_Next(struct qemu_syscall *call)
{
    struct qemu_EnumUnknown_Next *c = (struct qemu_EnumUnknown_Next *)call;
    struct qemu_wic_enum *wic_enum;

    WINE_FIXME("Unverified!\n");
    wic_enum = QEMU_G2H(c->iface);

    c->super.iret = IEnumUnknown_Next(wic_enum->host, c->celt, QEMU_G2H(c->rgelt), QEMU_G2H(c->pceltFetched));
}

#endif

struct qemu_EnumUnknown_Skip
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t celt;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI EnumUnknown_Skip(IEnumUnknown *iface, ULONG celt)
{
    struct qemu_EnumUnknown_Skip call;
    struct qemu_wic_enum *wic_enum = impl_from_IEnumUnknown(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMUNKNOWN_SKIP);
    call.iface = (ULONG_PTR)wic_enum;
    call.celt = celt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumUnknown_Skip(struct qemu_syscall *call)
{
    struct qemu_EnumUnknown_Skip *c = (struct qemu_EnumUnknown_Skip *)call;
    struct qemu_wic_enum *wic_enum;

    WINE_FIXME("Unverified!\n");
    wic_enum = QEMU_G2H(c->iface);

    c->super.iret = IEnumUnknown_Skip(wic_enum->host, c->celt);
}

#endif

struct qemu_EnumUnknown_Reset
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI EnumUnknown_Reset(IEnumUnknown *iface)
{
    struct qemu_EnumUnknown_Reset call;
    struct qemu_wic_enum *wic_enum = impl_from_IEnumUnknown(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMUNKNOWN_RESET);
    call.iface = (ULONG_PTR)wic_enum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumUnknown_Reset(struct qemu_syscall *call)
{
    struct qemu_EnumUnknown_Reset *c = (struct qemu_EnumUnknown_Reset *)call;
    struct qemu_wic_enum *wic_enum;

    WINE_FIXME("Unverified!\n");
    wic_enum = QEMU_G2H(c->iface);

    c->super.iret = IEnumUnknown_Reset(wic_enum->host);
}

#endif

struct qemu_EnumUnknown_Clone
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppenum;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI EnumUnknown_Clone(IEnumUnknown *iface, IEnumUnknown **ppenum)
{
    struct qemu_EnumUnknown_Clone call;
    struct qemu_wic_enum *wic_enum = impl_from_IEnumUnknown(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMUNKNOWN_CLONE);
    call.iface = (ULONG_PTR)wic_enum;
    call.ppenum = (ULONG_PTR)ppenum;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumUnknown_Clone(struct qemu_syscall *call)
{
    struct qemu_EnumUnknown_Clone *c = (struct qemu_EnumUnknown_Clone *)call;
    struct qemu_wic_enum *wic_enum;

    WINE_FIXME("Unverified!\n");
    wic_enum = QEMU_G2H(c->iface);

    c->super.iret = IEnumUnknown_Clone(wic_enum->host, QEMU_G2H(c->ppenum));
}

#endif

struct qemu_WICConvertBitmapSource
{
    struct qemu_syscall super;
    uint64_t dstFormat;
    uint64_t bitmap, clipper, converter, custom;
    uint64_t ppIDst;
    uint64_t no_convert;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WICConvertBitmapSource(REFWICPixelFormatGUID dstFormat, IWICBitmapSource *pISrc,
        IWICBitmapSource **ppIDst)
{
    struct qemu_WICConvertBitmapSource call;
    struct qemu_wic_converter *converter;

    call.super.id = QEMU_SYSCALL_ID(CALL_WICCONVERTBITMAPSOURCE);
    call.dstFormat = (ULONG_PTR)dstFormat;

    if (!pISrc)
    {
        call.bitmap = call.clipper = call.custom = call.converter = 0;
    }
    else if (((IWICBitmap *)pISrc)->lpVtbl == &WICBitmap_Vtbl)
    {
        struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap((IWICBitmap *)pISrc);
        call.bitmap = (ULONG_PTR)bitmap;
        call.clipper = call.custom = call.converter = 0;
    }
    else if (((IWICBitmapClipper *)pISrc)->lpVtbl == &WICBitmapClipper_Vtbl)
    {
        struct qemu_wic_clipper *clipper = impl_from_IWICBitmapClipper((IWICBitmapClipper *)pISrc);
        call.clipper = (ULONG_PTR)clipper;
        call.bitmap = call.custom = call.converter = 0;
    }
    else if (((IWICFormatConverter *)pISrc)->lpVtbl == &WICFormatConverter_Vtbl)
    {
        struct qemu_wic_converter *other = impl_from_IWICFormatConverter((IWICFormatConverter *)pISrc);
        call.converter = (ULONG_PTR)other;
        call.clipper = call.bitmap = call.custom = 0;
    }
    else
    {
        call.bitmap = call.clipper = call.converter = 0;
        call.custom = (ULONG_PTR)pISrc;
    }
    call.ppIDst = (ULONG_PTR)ppIDst;

    qemu_syscall(&call.super);

    if (FAILED(call.super.iret))
    {
        return call.super.iret;
    }
    if (call.no_convert)
    {
        *ppIDst = pISrc;
        return call.super.iret;
    }

    converter = (struct qemu_wic_converter *)(ULONG_PTR)call.ppIDst;
    WICFormatConverter_init_guest(converter);
    *ppIDst = (IWICBitmapSource *)&converter->IWICFormatConverter_iface;

    return call.super.iret;
}

#else

void qemu_WICConvertBitmapSource(struct qemu_syscall *call)
{
    struct qemu_WICConvertBitmapSource *c = (struct qemu_WICConvertBitmapSource *)call;
    struct qemu_wic_converter *converter, *other = NULL;
    IWICBitmapSource *host;
    IWICBitmapSource *source;
    struct qemu_wic_bitmap *bitmap = NULL;
    struct qemu_wic_clipper *clipper = NULL;
    struct qemu_bitmap_source *source_wrapper;

    WINE_TRACE("\n");
    if (c->bitmap)
    {
        bitmap = QEMU_G2H(c->bitmap);
        source = (IWICBitmapSource *)bitmap->bitmap_host;
        WINE_TRACE("Found our bitmap %p, passing host %p.\n", bitmap, source);
        IWICBitmapSource_AddRef(source);
    }
    else if (c->clipper)
    {
        clipper = QEMU_G2H(c->clipper);
        source = (IWICBitmapSource *)clipper->host;
        WINE_TRACE("Found our clipper %p, passing host %p.\n", clipper, source);
        IWICBitmapSource_AddRef(source);
    }
    else if (c->converter)
    {
        other = QEMU_G2H(c->converter);
        source = (IWICBitmapSource *)other->host;
        WINE_TRACE("Found our converter %p, passing host %p.\n", other, source);
        IWICBitmapSource_AddRef(source);
    }
    else if (c->custom)
    {
        WINE_TRACE("Creating a wrapper for unrecognized source %p.\n", (void *)c->custom);
        source_wrapper = bitmap_source_wrapper_create(c->custom);
        if (!source_wrapper)
        {
            WINE_WARN("Out of memory.\n");
            c->super.iret = E_OUTOFMEMORY;
            return;
        }
        source = &source_wrapper->IWICBitmapSource_iface;
    }
    else
    {
        source = NULL;
    }

    c->no_convert = 1;
    c->super.iret = WICConvertBitmapSource(QEMU_G2H(c->dstFormat), source, c->ppIDst ? &host : NULL);

    /* Release our ref, the host converter has its own if it wants one. */
    if (source)
        IWICBitmapSource_Release(source);

    if (FAILED(c->super.iret))
        return;

    if (host == source)
    {
        WINE_TRACE("The source has been returned, no conversion is needed.\n");
        /* If the interface was a custom provided interface, we now have a wrapper hanging around that
         * won't be needed. It holds a reference to the guest interface, which is good because we need
         * to AddRef the guest. Just HeapFree the wrapper, and the guest side will return the app's
         * interface back to the app, without the wrapper being needed.
         *
         * Not exactly pretty though. */
        if (source_wrapper)
        {
            WINE_TRACE("Stealing the guest reference from the bitmap source wrapper.\n");
            HeapFree(GetProcessHeap(), 0, source_wrapper);
        }

        return;
    }

    c->no_convert = 0;
    converter = WICFormatConverter_create_host(host);

    converter->source_bitmap = bitmap;
    converter->source_converter = other;
    converter->source_clipper = clipper;

    c->ppIDst = QEMU_H2G(converter);
}

#endif

#ifdef QEMU_DLL_GUEST

static const IWICBitmapDecoderInfoVtbl WICBitmapDecoderInfo_Vtbl =
{
    (void *)WICComponentInfo_QueryInterface,
    (void *)WICComponentInfo_AddRef,
    (void *)WICComponentInfo_Release,
    (void *)WICComponentInfo_GetComponentType,
    (void *)WICComponentInfo_GetCLSID,
    (void *)WICComponentInfo_GetSigningStatus,
    (void *)WICComponentInfo_GetAuthor,
    (void *)WICComponentInfo_GetVendorGUID,
    (void *)WICComponentInfo_GetVersion,
    (void *)WICComponentInfo_GetSpecVersion,
    (void *)WICComponentInfo_GetFriendlyName,
    WICBitmapDecoderInfo_GetContainerFormat,
    WICBitmapDecoderInfo_GetPixelFormats,
    WICBitmapDecoderInfo_GetColorManagementVersion,
    WICBitmapDecoderInfo_GetDeviceManufacturer,
    WICBitmapDecoderInfo_GetDeviceModels,
    WICBitmapDecoderInfo_GetMimeTypes,
    WICBitmapDecoderInfo_GetFileExtensions,
    WICBitmapDecoderInfo_DoesSupportAnimation,
    WICBitmapDecoderInfo_DoesSupportChromaKey,
    WICBitmapDecoderInfo_DoesSupportLossless,
    WICBitmapDecoderInfo_DoesSupportMultiframe,
    WICBitmapDecoderInfo_MatchesMimeType,
    WICBitmapDecoderInfo_GetPatterns,
    WICBitmapDecoderInfo_MatchesPattern,
    WICBitmapDecoderInfo_CreateInstance
};

static const IWICBitmapEncoderInfoVtbl WICBitmapEncoderInfo_Vtbl = {
    (void *)WICComponentInfo_QueryInterface,
    (void *)WICComponentInfo_AddRef,
    (void *)WICComponentInfo_Release,
    (void *)WICComponentInfo_GetComponentType,
    (void *)WICComponentInfo_GetCLSID,
    (void *)WICComponentInfo_GetSigningStatus,
    (void *)WICComponentInfo_GetAuthor,
    (void *)WICComponentInfo_GetVendorGUID,
    (void *)WICComponentInfo_GetVersion,
    (void *)WICComponentInfo_GetSpecVersion,
    (void *)WICComponentInfo_GetFriendlyName,
    WICBitmapEncoderInfo_GetContainerFormat,
    WICBitmapEncoderInfo_GetPixelFormats,
    WICBitmapEncoderInfo_GetColorManagementVersion,
    WICBitmapEncoderInfo_GetDeviceManufacturer,
    WICBitmapEncoderInfo_GetDeviceModels,
    WICBitmapEncoderInfo_GetMimeTypes,
    WICBitmapEncoderInfo_GetFileExtensions,
    WICBitmapEncoderInfo_DoesSupportAnimation,
    WICBitmapEncoderInfo_DoesSupportChromaKey,
    WICBitmapEncoderInfo_DoesSupportLossless,
    WICBitmapEncoderInfo_DoesSupportMultiframe,
    WICBitmapEncoderInfo_MatchesMimeType,
    WICBitmapEncoderInfo_CreateInstance
};

static const IWICFormatConverterInfoVtbl WICFormatConverterInfo_Vtbl =
{
    (void *)WICComponentInfo_QueryInterface,
    (void *)WICComponentInfo_AddRef,
    (void *)WICComponentInfo_Release,
    (void *)WICComponentInfo_GetComponentType,
    (void *)WICComponentInfo_GetCLSID,
    (void *)WICComponentInfo_GetSigningStatus,
    (void *)WICComponentInfo_GetAuthor,
    (void *)WICComponentInfo_GetVendorGUID,
    (void *)WICComponentInfo_GetVersion,
    (void *)WICComponentInfo_GetSpecVersion,
    (void *)WICComponentInfo_GetFriendlyName,
    WICFormatConverterInfo_GetPixelFormats,
    WICFormatConverterInfo_CreateInstance
};

static const IWICPixelFormatInfo2Vtbl WICPixelFormatInfo2_Vtbl = {
    (void *)WICComponentInfo_QueryInterface,
    (void *)WICComponentInfo_AddRef,
    (void *)WICComponentInfo_Release,
    (void *)WICComponentInfo_GetComponentType,
    (void *)WICComponentInfo_GetCLSID,
    (void *)WICComponentInfo_GetSigningStatus,
    (void *)WICComponentInfo_GetAuthor,
    (void *)WICComponentInfo_GetVendorGUID,
    (void *)WICComponentInfo_GetVersion,
    (void *)WICComponentInfo_GetSpecVersion,
    (void *)WICComponentInfo_GetFriendlyName,
    WICPixelFormatInfo2_GetFormatGUID,
    WICPixelFormatInfo2_GetColorContext,
    WICPixelFormatInfo2_GetBitsPerPixel,
    WICPixelFormatInfo2_GetChannelCount,
    WICPixelFormatInfo2_GetChannelMask,
    WICPixelFormatInfo2_SupportsTransparency,
    WICPixelFormatInfo2_GetNumericRepresentation
};

static const IWICMetadataReaderInfoVtbl WICMetadataReaderInfo_Vtbl = {
    (void *)WICComponentInfo_QueryInterface,
    (void *)WICComponentInfo_AddRef,
    (void *)WICComponentInfo_Release,
    (void *)WICComponentInfo_GetComponentType,
    (void *)WICComponentInfo_GetCLSID,
    (void *)WICComponentInfo_GetSigningStatus,
    (void *)WICComponentInfo_GetAuthor,
    (void *)WICComponentInfo_GetVendorGUID,
    (void *)WICComponentInfo_GetVersion,
    (void *)WICComponentInfo_GetSpecVersion,
    (void *)WICComponentInfo_GetFriendlyName,
    WICMetadataReaderInfo_GetMetadataFormat,
    WICMetadataReaderInfo_GetContainerFormats,
    WICMetadataReaderInfo_GetDeviceManufacturer,
    WICMetadataReaderInfo_GetDeviceModels,
    WICMetadataReaderInfo_DoesRequireFullStream,
    WICMetadataReaderInfo_DoesSupportPadding,
    WICMetadataReaderInfo_DoesRequireFixedSize,
    WICMetadataReaderInfo_GetPatterns,
    WICMetadataReaderInfo_MatchesPattern,
    WICMetadataReaderInfo_CreateInstance
};

void WICComponentInfo_init_guest(struct qemu_wic_info *info, enum component_info_type type)
{
    switch (type)
    {
        case BITMAPDECODER_INFO:
            info->IWICComponentInfo_iface.lpVtbl = (IWICComponentInfoVtbl *)&WICBitmapDecoderInfo_Vtbl;
            break;

        case BITMAPENCODER_INFO:
            info->IWICComponentInfo_iface.lpVtbl = (IWICComponentInfoVtbl *)&WICBitmapEncoderInfo_Vtbl;
            break;

        case CONVERTER_INFO:
            info->IWICComponentInfo_iface.lpVtbl = (IWICComponentInfoVtbl *)&WICFormatConverterInfo_Vtbl;
            break;

        case FORMAT_INFO:
            info->IWICComponentInfo_iface.lpVtbl = (IWICComponentInfoVtbl *)&WICPixelFormatInfo2_Vtbl;
            break;

        case METADATA_INFO:
            info->IWICComponentInfo_iface.lpVtbl = (IWICComponentInfoVtbl *)&WICMetadataReaderInfo_Vtbl;
            break;
    }
}

#else

struct qemu_wic_info *WICComponentInfo_create_host(IWICComponentInfo *host, enum component_info_type *type)
{
    IUnknown *unk = NULL;
    struct qemu_wic_info *ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));

    if (!ret)
    {
        WINE_WARN("Out of memory\n");
        return NULL;
    }

    /* FIXME: The host library caches info objects, so we need to do this too. Otherwise if we create
     * a 2nd wrapper for the same objects one of them won't be released properly. The tests also
     * check for this. */

    if (SUCCEEDED(IWICComponentInfo_QueryInterface(host, &IID_IWICBitmapDecoderInfo, (void **)&unk)))
        *type = BITMAPDECODER_INFO;
    else if (SUCCEEDED(IWICComponentInfo_QueryInterface(host, &IID_IWICBitmapEncoderInfo, (void **)&unk)))
        *type = BITMAPENCODER_INFO;
    else if (SUCCEEDED(IWICComponentInfo_QueryInterface(host, &IID_IWICFormatConverterInfo, (void **)&unk)))
        *type = CONVERTER_INFO;
    else if (SUCCEEDED(IWICComponentInfo_QueryInterface(host, &IID_IWICPixelFormatInfo2, (void **)&unk)))
        *type = FORMAT_INFO;
    else if (SUCCEEDED(IWICComponentInfo_QueryInterface(host, &IID_IWICMetadataReaderInfo, (void **)&unk)))
        *type = METADATA_INFO;
    else
        WINE_ERR("Got an unknown component info interface.\n");

    IUnknown_Release(unk);

    ret->host = host;
    return ret;
}

#endif
