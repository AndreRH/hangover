/*
 * Copyright 2017 André Hentschel
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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#define COBJMACROS

#include <initguid.h>
#include <windows.h>
#include <wincodec.h>

#include "windows-user-services.h"
#include "dll_list.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#include <list.h>
#else
#include <wine/debug.h>
#include <wine/list.h>
#endif

#include "qemu_windowscodecs.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_wic);

struct qemu_dll_init
{
    struct qemu_syscall super;
    uint64_t reason;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_dll_init call;
    HMODULE dxgi;

    if (reason == DLL_PROCESS_ATTACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        call.reason = DLL_PROCESS_ATTACH;
        qemu_syscall(&call.super);
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        call.reason = DLL_PROCESS_DETACH;
        qemu_syscall(&call.super);
    }

    return TRUE;
}

HRESULT WINAPI DllCanUnloadNow(void)
{
    WINE_FIXME("Stub\n");
    return S_FALSE;
}

HRESULT WINAPI DllRegisterServer(void)
{
    WINE_ERR("Should not be called on the wrapper.\n");
    return E_FAIL;
}

HRESULT WINAPI DllUnregisterServer(void)
{
    WINE_ERR("Should not be called on the wrapper.\n");
    return E_FAIL;
}

#else

static void qemu_init_dll(struct qemu_syscall *call)
{
    struct qemu_dll_init *c = (struct qemu_dll_init *)call;

    switch (c->reason)
    {
        case DLL_PROCESS_ATTACH:
            break;

        case DLL_PROCESS_DETACH:
            break;
    }
}

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_init_dll,
    qemu_WICBitmapDecoder_AddRef,
    qemu_WICBitmapDecoder_CopyPalette,
    qemu_WICBitmapDecoder_GetColorContexts,
    qemu_WICBitmapDecoder_GetContainerFormat,
    qemu_WICBitmapDecoder_GetDecoderInfo,
    qemu_WICBitmapDecoder_GetFrame,
    qemu_WICBitmapDecoder_GetFrameCount,
    qemu_WICBitmapDecoder_GetMetadataQueryReader,
    qemu_WICBitmapDecoder_GetPreview,
    qemu_WICBitmapDecoder_GetThumbnail,
    qemu_WICBitmapDecoder_Initialize,
    qemu_WICBitmapDecoder_QueryCapability,
    qemu_WICBitmapDecoder_QueryInterface,
    qemu_WICBitmapDecoder_Release,
    qemu_WICBitmapEncoder_AddRef,
    qemu_WICBitmapEncoder_Commit,
    qemu_WICBitmapEncoder_CreateNewFrame,
    qemu_WICBitmapEncoder_GetContainerFormat,
    qemu_WICBitmapEncoder_GetEncoderInfo,
    qemu_WICBitmapEncoder_GetMetadataQueryWriter,
    qemu_WICBitmapEncoder_Initialize,
    qemu_WICBitmapEncoder_QueryInterface,
    qemu_WICBitmapEncoder_Release,
    qemu_WICBitmapEncoder_SetColorContexts,
    qemu_WICBitmapEncoder_SetPalette,
    qemu_WICBitmapEncoder_SetPreview,
    qemu_WICBitmapEncoder_SetThumbnail,
    qemu_WICBitmapFrameDecode_AddRef,
    qemu_WICBitmapFrameDecode_CopyPalette,
    qemu_WICBitmapFrameDecode_CopyPixels,
    qemu_WICBitmapFrameDecode_GetColorContexts,
    qemu_WICBitmapFrameDecode_GetMetadataQueryReader,
    qemu_WICBitmapFrameDecode_GetPixelFormat,
    qemu_WICBitmapFrameDecode_GetResolution,
    qemu_WICBitmapFrameDecode_GetSize,
    qemu_WICBitmapFrameDecode_GetThumbnail,
    qemu_WICBitmapFrameDecode_QueryInterface,
    qemu_WICBitmapFrameDecode_Release,
    qemu_WICBitmapFrameEncode_AddRef,
    qemu_WICBitmapFrameEncode_Commit,
    qemu_WICBitmapFrameEncode_GetMetadataQueryWriter,
    qemu_WICBitmapFrameEncode_Initialize,
    qemu_WICBitmapFrameEncode_QueryInterface,
    qemu_WICBitmapFrameEncode_Release,
    qemu_WICBitmapFrameEncode_SetColorContexts,
    qemu_WICBitmapFrameEncode_SetPalette,
    qemu_WICBitmapFrameEncode_SetPixelFormat,
    qemu_WICBitmapFrameEncode_SetResolution,
    qemu_WICBitmapFrameEncode_SetSize,
    qemu_WICBitmapFrameEncode_SetThumbnail,
    qemu_WICBitmapFrameEncode_WritePixels,
    qemu_WICBitmapFrameEncode_WriteSource,
    qemu_WICConvertBitmapSource,
    qemu_WICCreateBitmapFromSection,
    qemu_WICCreateBitmapFromSectionEx,
    qemu_WICMapGuidToShortName,
    qemu_WICMapSchemaToName,
    qemu_WICMapShortNameToGuid,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side windowscodecs wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
