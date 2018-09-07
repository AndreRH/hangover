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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

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

struct qemu_WICBitmapLock_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

/* WARNING: .NET Media Integration Layer (MIL) directly dereferences
 * BitmapImpl members and depends on its exact layout.
 *
 * TODO: I just copied the struct from Wine, most of the fields are
 * not used by the wrapper. They'll probably need syncing between
 * host and guest when methods are called. Note that they can only
 * be written by the guest as the host might have an incompatible
 * view on them. */
struct qemu_wic_bitmap
{
    /* Guest fields */
    IMILUnknown1 IMILUnknown1_iface;
    LONG ref;
    IMILBitmapSource IMILBitmapSource_iface;
    IWICBitmap IWICBitmap_iface;
    IMILUnknown2 IMILUnknown2_iface;
    IWICPalette *palette;
    int palette_set;
    LONG lock; /* 0 if not locked, -1 if locked for writing, count if locked for reading */
    BYTE *data;
    void *view; /* used if data is a section created by an application */
    UINT offset; /* offset into view */
    UINT width, height;
    UINT stride;
    UINT bpp;
    WICPixelFormatGUID pixelformat;
    double dpix, dpiy;
    CRITICAL_SECTION cs;

    /* Host fields */
    IMILUnknown1 *unk1_host;
    IMILBitmapSource *source_host;
    IWICBitmap *bitmap_host;
    IMILUnknown2 *unk2_host;
};

/* Is there Windows software that depends on the implementation here too? Not sure,
 * hope not for now. */
struct qemu_wic_lock
{
    /* Guest fields */
    IWICBitmapLock IWICBitmapLock_iface;

    /* Host fields */
    IWICBitmapLock *host;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_wic_bitmap *impl_from_IWICBitmap(IWICBitmap *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_bitmap, IWICBitmap_iface);
}

static inline struct qemu_wic_bitmap *impl_from_IMILBitmapSource(IMILBitmapSource *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_bitmap, IMILBitmapSource_iface);
}

static inline struct qemu_wic_bitmap *impl_from_IMILUnknown1(IMILUnknown1 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_bitmap, IMILUnknown1_iface);
}

static inline struct qemu_wic_bitmap *impl_from_IMILUnknown2(IMILUnknown2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_bitmap, IMILUnknown2_iface);
}

static inline struct qemu_wic_lock *impl_from_IWICBitmapLock(IWICBitmapLock *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_wic_lock, IWICBitmapLock_iface);
}

static HRESULT WINAPI WICBitmapLock_QueryInterface(IWICBitmapLock *iface, REFIID iid, void **ppv)
{
    struct qemu_WICBitmapLock_QueryInterface call;
    struct qemu_wic_lock *lock = impl_from_IWICBitmapLock(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPLOCK_QUERYINTERFACE);
    call.iface = (ULONG_PTR)lock;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapLock_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICBitmapLock_QueryInterface *c = (struct qemu_WICBitmapLock_QueryInterface *)call;
    struct qemu_wic_lock *lock;

    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    lock = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapLock_QueryInterface(lock->host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_WICBitmapLock_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmapLock_AddRef(IWICBitmapLock *iface)
{
    struct qemu_WICBitmapLock_AddRef call;
    struct qemu_wic_lock *lock = impl_from_IWICBitmapLock(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPLOCK_ADDREF);
    call.iface = (ULONG_PTR)lock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapLock_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICBitmapLock_AddRef *c = (struct qemu_WICBitmapLock_AddRef *)call;
    struct qemu_wic_lock *lock;

    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    lock = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapLock_AddRef(lock->host);
}

#endif

struct qemu_WICBitmapLock_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmapLock_Release(IWICBitmapLock *iface)
{
    struct qemu_WICBitmapLock_Release call;
    struct qemu_wic_lock *lock = impl_from_IWICBitmapLock(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPLOCK_RELEASE);
    call.iface = (ULONG_PTR)lock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapLock_Release(struct qemu_syscall *call)
{
    struct qemu_WICBitmapLock_Release *c = (struct qemu_WICBitmapLock_Release *)call;
    struct qemu_wic_lock *lock;

    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    lock = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapLock_Release(lock->host);
}

#endif

struct qemu_WICBitmapLock_GetSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t puiWidth;
    uint64_t puiHeight;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapLock_GetSize(IWICBitmapLock *iface, UINT *puiWidth, UINT *puiHeight)
{
    struct qemu_WICBitmapLock_GetSize call;
    struct qemu_wic_lock *lock = impl_from_IWICBitmapLock(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPLOCK_GETSIZE);
    call.iface = (ULONG_PTR)lock;
    call.puiWidth = (ULONG_PTR)puiWidth;
    call.puiHeight = (ULONG_PTR)puiHeight;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapLock_GetSize(struct qemu_syscall *call)
{
    struct qemu_WICBitmapLock_GetSize *c = (struct qemu_WICBitmapLock_GetSize *)call;
    struct qemu_wic_lock *lock;

    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    lock = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapLock_GetSize(lock->host, QEMU_G2H(c->puiWidth), QEMU_G2H(c->puiHeight));
}

#endif

struct qemu_WICBitmapLock_GetStride
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pcbStride;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapLock_GetStride(IWICBitmapLock *iface, UINT *pcbStride)
{
    struct qemu_WICBitmapLock_GetStride call;
    struct qemu_wic_lock *lock = impl_from_IWICBitmapLock(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPLOCK_GETSTRIDE);
    call.iface = (ULONG_PTR)lock;
    call.pcbStride = (ULONG_PTR)pcbStride;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapLock_GetStride(struct qemu_syscall *call)
{
    struct qemu_WICBitmapLock_GetStride *c = (struct qemu_WICBitmapLock_GetStride *)call;
    struct qemu_wic_lock *lock;

    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    lock = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapLock_GetStride(lock->host, QEMU_G2H(c->pcbStride));
}

#endif

struct qemu_WICBitmapLock_GetDataPointer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pcbBufferSize;
    uint64_t ppbData;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapLock_GetDataPointer(IWICBitmapLock *iface, UINT *pcbBufferSize, BYTE **ppbData)
{
    struct qemu_WICBitmapLock_GetDataPointer call;
    struct qemu_wic_lock *lock = impl_from_IWICBitmapLock(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPLOCK_GETDATAPOINTER);
    call.iface = (ULONG_PTR)lock;
    call.pcbBufferSize = (ULONG_PTR)pcbBufferSize;
    call.ppbData = (ULONG_PTR)ppbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapLock_GetDataPointer(struct qemu_syscall *call)
{
    struct qemu_WICBitmapLock_GetDataPointer *c = (struct qemu_WICBitmapLock_GetDataPointer *)call;
    struct qemu_wic_lock *lock;

    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    lock = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapLock_GetDataPointer(lock->host, QEMU_G2H(c->pcbBufferSize), QEMU_G2H(c->ppbData));
}

#endif

struct qemu_WICBitmapLock_GetPixelFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pPixelFormat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmapLock_GetPixelFormat(IWICBitmapLock *iface, WICPixelFormatGUID *pPixelFormat)
{
    struct qemu_WICBitmapLock_GetPixelFormat call;
    struct qemu_wic_lock *lock = impl_from_IWICBitmapLock(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAPLOCK_GETPIXELFORMAT);
    call.iface = (ULONG_PTR)lock;
    call.pPixelFormat = (ULONG_PTR)pPixelFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmapLock_GetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_WICBitmapLock_GetPixelFormat *c = (struct qemu_WICBitmapLock_GetPixelFormat *)call;
    struct qemu_wic_lock *lock;

    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    lock = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmapLock_GetPixelFormat(lock->host, QEMU_G2H(c->pPixelFormat));
}

#endif

struct qemu_WICBitmap_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmap_QueryInterface(IWICBitmap *iface, REFIID iid, void **ppv)
{
    struct qemu_WICBitmap_QueryInterface call;
    struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAP_QUERYINTERFACE);
    call.iface = (ULONG_PTR)bitmap;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmap_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_WICBitmap_QueryInterface *c = (struct qemu_WICBitmap_QueryInterface *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmap_QueryInterface(bitmap->bitmap_host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_WICBitmap_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmap_AddRef(IWICBitmap *iface)
{
    struct qemu_WICBitmap_AddRef call;
    struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAP_ADDREF);
    call.iface = (ULONG_PTR)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmap_AddRef(struct qemu_syscall *call)
{
    struct qemu_WICBitmap_AddRef *c = (struct qemu_WICBitmap_AddRef *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmap_AddRef(bitmap->bitmap_host);
}

#endif

struct qemu_WICBitmap_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI WICBitmap_Release(IWICBitmap *iface)
{
    struct qemu_WICBitmap_Release call;
    struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAP_RELEASE);
    call.iface = (ULONG_PTR)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmap_Release(struct qemu_syscall *call)
{
    struct qemu_WICBitmap_Release *c = (struct qemu_WICBitmap_Release *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmap_Release(bitmap->bitmap_host);
}

#endif

struct qemu_WICBitmap_GetSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t puiWidth;
    uint64_t puiHeight;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmap_GetSize(IWICBitmap *iface, UINT *puiWidth, UINT *puiHeight)
{
    struct qemu_WICBitmap_GetSize call;
    struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAP_GETSIZE);
    call.iface = (ULONG_PTR)bitmap;
    call.puiWidth = (ULONG_PTR)puiWidth;
    call.puiHeight = (ULONG_PTR)puiHeight;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmap_GetSize(struct qemu_syscall *call)
{
    struct qemu_WICBitmap_GetSize *c = (struct qemu_WICBitmap_GetSize *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmap_GetSize(bitmap->bitmap_host, QEMU_G2H(c->puiWidth), QEMU_G2H(c->puiHeight));
}

#endif

struct qemu_WICBitmap_GetPixelFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pPixelFormat;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmap_GetPixelFormat(IWICBitmap *iface, WICPixelFormatGUID *pPixelFormat)
{
    struct qemu_WICBitmap_GetPixelFormat call;
    struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAP_GETPIXELFORMAT);
    call.iface = (ULONG_PTR)bitmap;
    call.pPixelFormat = (ULONG_PTR)pPixelFormat;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmap_GetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_WICBitmap_GetPixelFormat *c = (struct qemu_WICBitmap_GetPixelFormat *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmap_GetPixelFormat(bitmap->bitmap_host, QEMU_G2H(c->pPixelFormat));
}

#endif

struct qemu_WICBitmap_GetResolution
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pDpiX;
    uint64_t pDpiY;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmap_GetResolution(IWICBitmap *iface, double *pDpiX, double *pDpiY)
{
    struct qemu_WICBitmap_GetResolution call;
    struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAP_GETRESOLUTION);
    call.iface = (ULONG_PTR)bitmap;
    call.pDpiX = (ULONG_PTR)pDpiX;
    call.pDpiY = (ULONG_PTR)pDpiY;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmap_GetResolution(struct qemu_syscall *call)
{
    struct qemu_WICBitmap_GetResolution *c = (struct qemu_WICBitmap_GetResolution *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmap_GetResolution(bitmap->bitmap_host, QEMU_G2H(c->pDpiX), QEMU_G2H(c->pDpiY));
}

#endif

struct qemu_WICBitmap_CopyPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIPalette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmap_CopyPalette(IWICBitmap *iface, IWICPalette *pIPalette)
{
    struct qemu_WICBitmap_CopyPalette call;
    struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAP_COPYPALETTE);
    call.iface = (ULONG_PTR)bitmap;
    call.pIPalette = (ULONG_PTR)pIPalette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmap_CopyPalette(struct qemu_syscall *call)
{
    struct qemu_WICBitmap_CopyPalette *c = (struct qemu_WICBitmap_CopyPalette *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmap_CopyPalette(bitmap->bitmap_host, QEMU_G2H(c->pIPalette));
}

#endif

struct qemu_WICBitmap_CopyPixels
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t prc;
    uint64_t cbStride;
    uint64_t cbBufferSize;
    uint64_t pbBuffer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmap_CopyPixels(IWICBitmap *iface, const WICRect *prc, UINT cbStride, UINT cbBufferSize, BYTE *pbBuffer)
{
    struct qemu_WICBitmap_CopyPixels call;
    struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAP_COPYPIXELS);
    call.iface = (ULONG_PTR)bitmap;
    call.prc = (ULONG_PTR)prc;
    call.cbStride = cbStride;
    call.cbBufferSize = cbBufferSize;
    call.pbBuffer = (ULONG_PTR)pbBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmap_CopyPixels(struct qemu_syscall *call)
{
    struct qemu_WICBitmap_CopyPixels *c = (struct qemu_WICBitmap_CopyPixels *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmap_CopyPixels(bitmap->bitmap_host, QEMU_G2H(c->prc), c->cbStride, c->cbBufferSize, QEMU_G2H(c->pbBuffer));
}

#endif

struct qemu_WICBitmap_Lock
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t prcLock;
    uint64_t flags;
    uint64_t ppILock;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmap_Lock(IWICBitmap *iface, const WICRect *prcLock, DWORD flags, IWICBitmapLock **ppILock)
{
    struct qemu_WICBitmap_Lock call;
    struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAP_LOCK);
    call.iface = (ULONG_PTR)bitmap;
    call.prcLock = (ULONG_PTR)prcLock;
    call.flags = flags;
    call.ppILock = (ULONG_PTR)ppILock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmap_Lock(struct qemu_syscall *call)
{
    struct qemu_WICBitmap_Lock *c = (struct qemu_WICBitmap_Lock *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmap_Lock(bitmap->bitmap_host, QEMU_G2H(c->prcLock), c->flags, QEMU_G2H(c->ppILock));
}

#endif

struct qemu_WICBitmap_SetPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pIPalette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmap_SetPalette(IWICBitmap *iface, IWICPalette *pIPalette)
{
    struct qemu_WICBitmap_SetPalette call;
    struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAP_SETPALETTE);
    call.iface = (ULONG_PTR)bitmap;
    call.pIPalette = (ULONG_PTR)pIPalette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmap_SetPalette(struct qemu_syscall *call)
{
    struct qemu_WICBitmap_SetPalette *c = (struct qemu_WICBitmap_SetPalette *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmap_SetPalette(bitmap->bitmap_host, QEMU_G2H(c->pIPalette));
}

#endif

struct qemu_WICBitmap_SetResolution
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dpiX;
    uint64_t dpiY;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI WICBitmap_SetResolution(IWICBitmap *iface, double dpiX, double dpiY)
{
    struct qemu_WICBitmap_SetResolution call;
    struct qemu_wic_bitmap *bitmap = impl_from_IWICBitmap(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_WICBITMAP_SETRESOLUTION);
    call.iface = (ULONG_PTR)bitmap;
    call.dpiX = dpiX;
    call.dpiY = dpiY;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICBitmap_SetResolution(struct qemu_syscall *call)
{
    struct qemu_WICBitmap_SetResolution *c = (struct qemu_WICBitmap_SetResolution *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = IWICBitmap_SetResolution(bitmap->bitmap_host, c->dpiX, c->dpiY);
}

#endif

struct qemu_IMILBitmapImpl_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IMILBitmapImpl_QueryInterface(IMILBitmapSource *iface, REFIID iid, void **ppv)
{
    struct qemu_IMILBitmapImpl_QueryInterface call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILBitmapSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILBITMAPIMPL_QUERYINTERFACE);
    call.iface = (ULONG_PTR)bitmap;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILBitmapImpl_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_IMILBitmapImpl_QueryInterface *c = (struct qemu_IMILBitmapImpl_QueryInterface *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->source_host->lpVtbl->QueryInterface(bitmap->source_host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_IMILBitmapImpl_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IMILBitmapImpl_AddRef(IMILBitmapSource *iface)
{
    struct qemu_IMILBitmapImpl_AddRef call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILBitmapSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILBITMAPIMPL_ADDREF);
    call.iface = (ULONG_PTR)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILBitmapImpl_AddRef(struct qemu_syscall *call)
{
    struct qemu_IMILBitmapImpl_AddRef *c = (struct qemu_IMILBitmapImpl_AddRef *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->source_host->lpVtbl->AddRef(bitmap->source_host);
}

#endif

struct qemu_IMILBitmapImpl_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IMILBitmapImpl_Release(IMILBitmapSource *iface)
{
    struct qemu_IMILBitmapImpl_Release call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILBitmapSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILBITMAPIMPL_RELEASE);
    call.iface = (ULONG_PTR)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILBitmapImpl_Release(struct qemu_syscall *call)
{
    struct qemu_IMILBitmapImpl_Release *c = (struct qemu_IMILBitmapImpl_Release *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->source_host->lpVtbl->Release(bitmap->source_host);
}

#endif

struct qemu_IMILBitmapImpl_GetSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t width;
    uint64_t height;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IMILBitmapImpl_GetSize(IMILBitmapSource *iface, UINT *width, UINT *height)
{
    struct qemu_IMILBitmapImpl_GetSize call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILBitmapSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILBITMAPIMPL_GETSIZE);
    call.iface = (ULONG_PTR)bitmap;
    call.width = (ULONG_PTR)width;
    call.height = (ULONG_PTR)height;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILBitmapImpl_GetSize(struct qemu_syscall *call)
{
    struct qemu_IMILBitmapImpl_GetSize *c = (struct qemu_IMILBitmapImpl_GetSize *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->source_host->lpVtbl->GetSize(bitmap->source_host, QEMU_G2H(c->width), QEMU_G2H(c->height));
}

#endif

struct qemu_IMILBitmapImpl_GetPixelFormat
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t format;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IMILBitmapImpl_GetPixelFormat(IMILBitmapSource *iface, int *format)
{
    struct qemu_IMILBitmapImpl_GetPixelFormat call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILBitmapSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILBITMAPIMPL_GETPIXELFORMAT);
    call.iface = (ULONG_PTR)bitmap;
    call.format = (ULONG_PTR)format;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILBitmapImpl_GetPixelFormat(struct qemu_syscall *call)
{
    struct qemu_IMILBitmapImpl_GetPixelFormat *c = (struct qemu_IMILBitmapImpl_GetPixelFormat *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->source_host->lpVtbl->GetPixelFormat(bitmap->source_host, QEMU_G2H(c->format));
}

#endif

struct qemu_IMILBitmapImpl_GetResolution
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dpix;
    uint64_t dpiy;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IMILBitmapImpl_GetResolution(IMILBitmapSource *iface, double *dpix, double *dpiy)
{
    struct qemu_IMILBitmapImpl_GetResolution call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILBitmapSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILBITMAPIMPL_GETRESOLUTION);
    call.iface = (ULONG_PTR)bitmap;
    call.dpix = (ULONG_PTR)dpix;
    call.dpiy = (ULONG_PTR)dpiy;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILBitmapImpl_GetResolution(struct qemu_syscall *call)
{
    struct qemu_IMILBitmapImpl_GetResolution *c = (struct qemu_IMILBitmapImpl_GetResolution *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->source_host->lpVtbl->GetResolution(bitmap->source_host, QEMU_G2H(c->dpix), QEMU_G2H(c->dpiy));
}

#endif

struct qemu_IMILBitmapImpl_CopyPalette
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t palette;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IMILBitmapImpl_CopyPalette(IMILBitmapSource *iface, IWICPalette *palette)
{
    struct qemu_IMILBitmapImpl_CopyPalette call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILBitmapSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILBITMAPIMPL_COPYPALETTE);
    call.iface = (ULONG_PTR)bitmap;
    call.palette = (ULONG_PTR)palette;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILBitmapImpl_CopyPalette(struct qemu_syscall *call)
{
    struct qemu_IMILBitmapImpl_CopyPalette *c = (struct qemu_IMILBitmapImpl_CopyPalette *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->source_host->lpVtbl->CopyPalette(bitmap->source_host, QEMU_G2H(c->palette));
}

#endif

struct qemu_IMILBitmapImpl_CopyPixels
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t rc;
    uint64_t stride;
    uint64_t size;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IMILBitmapImpl_CopyPixels(IMILBitmapSource *iface, const WICRect *rc, UINT stride, UINT size, BYTE *buffer)
{
    struct qemu_IMILBitmapImpl_CopyPixels call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILBitmapSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILBITMAPIMPL_COPYPIXELS);
    call.iface = (ULONG_PTR)bitmap;
    call.rc = (ULONG_PTR)rc;
    call.stride = stride;
    call.size = size;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILBitmapImpl_CopyPixels(struct qemu_syscall *call)
{
    struct qemu_IMILBitmapImpl_CopyPixels *c = (struct qemu_IMILBitmapImpl_CopyPixels *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->source_host->lpVtbl->CopyPixels(bitmap->source_host, QEMU_G2H(c->rc), c->stride, c->size, QEMU_G2H(c->buffer));
}

#endif

struct qemu_IMILBitmapImpl_UnknownMethod1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IMILBitmapImpl_UnknownMethod1(IMILBitmapSource *iface, void **ppv)
{
    struct qemu_IMILBitmapImpl_UnknownMethod1 call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILBitmapSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILBITMAPIMPL_UNKNOWNMETHOD1);
    call.iface = (ULONG_PTR)bitmap;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILBitmapImpl_UnknownMethod1(struct qemu_syscall *call)
{
    struct qemu_IMILBitmapImpl_UnknownMethod1 *c = (struct qemu_IMILBitmapImpl_UnknownMethod1 *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->source_host->lpVtbl->UnknownMethod1(bitmap->source_host, QEMU_G2H(c->ppv));
}

#endif

struct qemu_IMILUnknown1Impl_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IMILUnknown1Impl_QueryInterface(IMILUnknown1 *iface, REFIID iid, void **ppv)
{
    struct qemu_IMILUnknown1Impl_QueryInterface call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILUnknown1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILUNKNOWN1IMPL_QUERYINTERFACE);
    call.iface = (ULONG_PTR)bitmap;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILUnknown1Impl_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_IMILUnknown1Impl_QueryInterface *c = (struct qemu_IMILUnknown1Impl_QueryInterface *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->unk1_host->lpVtbl->QueryInterface(bitmap->unk1_host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_IMILUnknown1Impl_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IMILUnknown1Impl_AddRef(IMILUnknown1 *iface)
{
    struct qemu_IMILUnknown1Impl_AddRef call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILUnknown1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILUNKNOWN1IMPL_ADDREF);
    call.iface = (ULONG_PTR)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILUnknown1Impl_AddRef(struct qemu_syscall *call)
{
    struct qemu_IMILUnknown1Impl_AddRef *c = (struct qemu_IMILUnknown1Impl_AddRef *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->unk1_host->lpVtbl->AddRef(bitmap->unk1_host);
}

#endif

struct qemu_IMILUnknown1Impl_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IMILUnknown1Impl_Release(IMILUnknown1 *iface)
{
    struct qemu_IMILUnknown1Impl_Release call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILUnknown1(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILUNKNOWN1IMPL_RELEASE);
    call.iface = (ULONG_PTR)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILUnknown1Impl_Release(struct qemu_syscall *call)
{
    struct qemu_IMILUnknown1Impl_Release *c = (struct qemu_IMILUnknown1Impl_Release *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->unk1_host->lpVtbl->Release(bitmap->unk1_host);
}

#endif

struct qemu_IMILUnknown2Impl_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IMILUnknown2Impl_QueryInterface(IMILUnknown2 *iface, REFIID iid, void **ppv)
{
    struct qemu_IMILUnknown2Impl_QueryInterface call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILUnknown2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILUNKNOWN2IMPL_QUERYINTERFACE);
    call.iface = (ULONG_PTR)bitmap;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILUnknown2Impl_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_IMILUnknown2Impl_QueryInterface *c = (struct qemu_IMILUnknown2Impl_QueryInterface *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->unk2_host->lpVtbl->QueryInterface(bitmap->unk2_host, QEMU_G2H(c->iid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_IMILUnknown2Impl_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IMILUnknown2Impl_AddRef(IMILUnknown2 *iface)
{
    struct qemu_IMILUnknown2Impl_AddRef call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILUnknown2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILUNKNOWN2IMPL_ADDREF);
    call.iface = (ULONG_PTR)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILUnknown2Impl_AddRef(struct qemu_syscall *call)
{
    struct qemu_IMILUnknown2Impl_AddRef *c = (struct qemu_IMILUnknown2Impl_AddRef *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->unk2_host->lpVtbl->AddRef(bitmap->unk2_host);
}

#endif

struct qemu_IMILUnknown2Impl_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IMILUnknown2Impl_Release(IMILUnknown2 *iface)
{
    struct qemu_IMILUnknown2Impl_Release call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILUnknown2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILUNKNOWN2IMPL_RELEASE);
    call.iface = (ULONG_PTR)bitmap;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILUnknown2Impl_Release(struct qemu_syscall *call)
{
    struct qemu_IMILUnknown2Impl_Release *c = (struct qemu_IMILUnknown2Impl_Release *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->unk2_host->lpVtbl->Release(bitmap->unk2_host);
}

#endif

struct qemu_IMILUnknown2Impl_UnknownMethod1
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t arg1;
    uint64_t arg2;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IMILUnknown2Impl_UnknownMethod1(IMILUnknown2 *iface, void *arg1, void *arg2)
{
    struct qemu_IMILUnknown2Impl_UnknownMethod1 call;
    struct qemu_wic_bitmap *bitmap = impl_from_IMILUnknown2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_IMILUNKNOWN2IMPL_UNKNOWNMETHOD1);
    call.iface = (ULONG_PTR)bitmap;
    call.arg1 = (ULONG_PTR)arg1;
    call.arg2 = (ULONG_PTR)arg2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IMILUnknown2Impl_UnknownMethod1(struct qemu_syscall *call)
{
    struct qemu_IMILUnknown2Impl_UnknownMethod1 *c = (struct qemu_IMILUnknown2Impl_UnknownMethod1 *)call;
    struct qemu_wic_bitmap *bitmap;

    WINE_FIXME("Unverified!\n");
    bitmap = QEMU_G2H(c->iface);

    c->super.iret = bitmap->unk2_host->lpVtbl->UnknownMethod1(bitmap->unk2_host, QEMU_G2H(c->arg1), QEMU_G2H(c->arg2));
}

#endif

#ifdef QEMU_DLL_GUEST

static const IWICBitmapVtbl WICBitmap_Vtbl =
{
    WICBitmap_QueryInterface,
    WICBitmap_AddRef,
    WICBitmap_Release,
    WICBitmap_GetSize,
    WICBitmap_GetPixelFormat,
    WICBitmap_GetResolution,
    WICBitmap_CopyPalette,
    WICBitmap_CopyPixels,
    WICBitmap_Lock,
    WICBitmap_SetPalette,
    WICBitmap_SetResolution
};

static const IMILBitmapSourceVtbl IMILBitmapImpl_Vtbl =
{
    IMILBitmapImpl_QueryInterface,
    IMILBitmapImpl_AddRef,
    IMILBitmapImpl_Release,
    IMILBitmapImpl_GetSize,
    IMILBitmapImpl_GetPixelFormat,
    IMILBitmapImpl_GetResolution,
    IMILBitmapImpl_CopyPalette,
    IMILBitmapImpl_CopyPixels,
    IMILBitmapImpl_UnknownMethod1,
};

static const IMILUnknown1Vtbl IMILUnknown1Impl_Vtbl =
{
    IMILUnknown1Impl_QueryInterface,
    IMILUnknown1Impl_AddRef,
    IMILUnknown1Impl_Release,
};

static const IMILUnknown2Vtbl IMILUnknown2Impl_Vtbl =
{
    IMILUnknown2Impl_QueryInterface,
    IMILUnknown2Impl_AddRef,
    IMILUnknown2Impl_Release,
    IMILUnknown2Impl_UnknownMethod1,
};

IWICBitmap *WICBitmap_init_guest(struct qemu_wic_bitmap *bitmap)
{
    bitmap->IWICBitmap_iface.lpVtbl = &WICBitmap_Vtbl;
    bitmap->IMILBitmapSource_iface.lpVtbl = &IMILBitmapImpl_Vtbl;
    bitmap->IMILUnknown1_iface.lpVtbl = &IMILUnknown1Impl_Vtbl;
    bitmap->IMILUnknown2_iface.lpVtbl = &IMILUnknown2Impl_Vtbl;

    /* TODO: Init the shadow copies of the other fields. */
    return &bitmap->IWICBitmap_iface;
}

#else

struct qemu_wic_bitmap *WICBitmap_create_host(IWICBitmap *host)
{
    struct qemu_wic_bitmap *ret;
    HRESULT hr;

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
    {
        WINE_WARN("Out of memory\n");
        return NULL;
    }

    ret->bitmap_host = host;

    hr = IWICBitmap_QueryInterface(host, &IID_IMILBitmapSource, (void **)&ret->source_host);
    if (FAILED(hr))
        WINE_ERR("Failed to get IMILBitmapSource interface.\n");
    ret->source_host->lpVtbl->Release(ret->source_host);

    hr = ret->source_host->lpVtbl->UnknownMethod1(ret->source_host, (void **)&ret->unk1_host);
    if (FAILED(hr))
        WINE_ERR("Failed to get IMILUnknown1 interface.\n");
    ret->unk1_host->lpVtbl->Release(ret->unk1_host);

    /* How do I get IMILUnknown2? There's nothing obvious in the Wine code, other than reading the magic
     * offset. */

    return ret;
}
#endif
