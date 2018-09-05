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

#include "windows-user-services.h"
#include "dll_list.h"

#include <wine/debug.h>
#include <wine/list.h>

#include "qemu_windowscodecs.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_wic);

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
        HANDLE section, UINT stride, UINT offset, DWORD wicaccess, IWICBitmap **bitmap)
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

