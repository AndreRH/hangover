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

struct qemu_WICConvertBitmapSource
{
    struct qemu_syscall super;
    uint64_t dstFormat;
    uint64_t pISrc;
    uint64_t ppIDst;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI WICConvertBitmapSource(REFWICPixelFormatGUID dstFormat, IWICBitmapSource *pISrc,
        IWICBitmapSource **ppIDst)
{
    struct qemu_WICConvertBitmapSource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WICCONVERTBITMAPSOURCE);
    call.dstFormat = (ULONG_PTR)dstFormat;
    call.pISrc = (ULONG_PTR)pISrc;
    call.ppIDst = (ULONG_PTR)ppIDst;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WICConvertBitmapSource(struct qemu_syscall *call)
{
    struct qemu_WICConvertBitmapSource *c = (struct qemu_WICConvertBitmapSource *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WICConvertBitmapSource(QEMU_G2H(c->dstFormat), QEMU_G2H(c->pISrc), QEMU_G2H(c->ppIDst));
}

#endif
