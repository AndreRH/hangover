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

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "gdi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_CopyEnhMetaFileA,
    qemu_CopyEnhMetaFileW,
    qemu_CopyMetaFileA,
    qemu_CopyMetaFileW,
    qemu_DeleteEnhMetaFile,
    qemu_DeleteMetaFile,
    qemu_DPtoLP,
    qemu_EnumEnhMetaFile,
    qemu_EnumMetaFile,
    qemu_GetDeviceCaps,
    qemu_GetEnhMetaFileA,
    qemu_GetEnhMetaFileBits,
    qemu_GetEnhMetaFileDescriptionA,
    qemu_GetEnhMetaFileDescriptionW,
    qemu_GetEnhMetaFileHeader,
    qemu_GetEnhMetaFilePaletteEntries,
    qemu_GetEnhMetaFileW,
    qemu_GetMetaFileA,
    qemu_GetMetaFileBitsEx,
    qemu_GetMetaFileW,
    qemu_GetWinMetaFileBits,
    qemu_LPtoDP,
    qemu_ModifyWorldTransform,
    qemu_OffsetViewportOrgEx,
    qemu_OffsetWindowOrgEx,
    qemu_PlayEnhMetaFile,
    qemu_PlayEnhMetaFileRecord,
    qemu_PlayMetaFile,
    qemu_PlayMetaFileRecord,
    qemu_ScaleViewportExtEx,
    qemu_ScaleWindowExtEx,
    qemu_SetEnhMetaFileBits,
    qemu_SetMapMode,
    qemu_SetMetaFileBitsEx,
    qemu_SetViewportExtEx,
    qemu_SetViewportOrgEx,
    qemu_SetVirtualResolution,
    qemu_SetWindowExtEx,
    qemu_SetWindowOrgEx,
    qemu_SetWinMetaFileBits,
    qemu_SetWorldTransform,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side gdi32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
