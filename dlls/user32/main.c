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
#include "user32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_AddClipboardFormatListener,
    qemu_ChangeClipboardChain,
    qemu_ClipCursor,
    qemu_CloseClipboard,
    qemu_CopyIcon,
    qemu_CopyImage,
    qemu_CountClipboardFormats,
    qemu_CreateCaret,
    qemu_CreateCursor,
    qemu_CreateIconIndirect,
    qemu_DefDlgProcA,
    qemu_DefDlgProcW,
    qemu_DestroyCaret,
    qemu_DestroyCursor,
    qemu_DestroyIcon,
    qemu_DrawIcon,
    qemu_DrawIconEx,
    qemu_EmptyClipboard,
    qemu_EnumClipboardFormats,
    qemu_GetCaretBlinkTime,
    qemu_GetCaretPos,
    qemu_GetClassInfoA,
    qemu_GetClassInfoExA,
    qemu_GetClassInfoExW,
    qemu_GetClassInfoW,
    qemu_GetClassLongA,
    qemu_GetClassLongPtrA,
    qemu_GetClassLongPtrW,
    qemu_GetClassLongW,
    qemu_GetClassNameA,
    qemu_GetClassNameW,
    qemu_GetClassWord,
    qemu_GetClipboardData,
    qemu_GetClipboardFormatNameA,
    qemu_GetClipboardFormatNameW,
    qemu_GetClipboardOwner,
    qemu_GetClipboardSequenceNumber,
    qemu_GetClipboardViewer,
    qemu_GetClipCursor,
    qemu_GetComboBoxInfo,
    qemu_GetCursor,
    qemu_GetCursorFrameInfo,
    qemu_GetIconInfo,
    qemu_GetOpenClipboardWindow,
    qemu_GetPriorityClipboardFormat,
    qemu_GetUpdatedClipboardFormats,
    qemu_HideCaret,
    qemu_IsClipboardFormatAvailable,
    qemu_LoadBitmapA,
    qemu_LoadBitmapW,
    qemu_LoadCursorA,
    qemu_LoadCursorFromFileA,
    qemu_LoadCursorFromFileW,
    qemu_LoadCursorW,
    qemu_LoadIconA,
    qemu_LoadIconW,
    qemu_LoadImageA,
    qemu_LoadImageW,
    qemu_LookupIconIdFromDirectory,
    qemu_LookupIconIdFromDirectoryEx,
    qemu_OemToCharA,
    qemu_OpenClipboard,
    qemu_RealGetWindowClassA,
    qemu_RealGetWindowClassW,
    qemu_RegisterClassA,
    qemu_RegisterClassExA,
    qemu_RegisterClassExW,
    qemu_RegisterClassW,
    qemu_RegisterClipboardFormatA,
    qemu_RegisterClipboardFormatW,
    qemu_RemoveClipboardFormatListener,
    qemu_SetCaretBlinkTime,
    qemu_SetCaretPos,
    qemu_SetClassLongA,
    qemu_SetClassLongPtrA,
    qemu_SetClassLongPtrW,
    qemu_SetClassLongW,
    qemu_SetClassWord,
    qemu_SetClipboardData,
    qemu_SetClipboardViewer,
    qemu_SetCursor,
    qemu_SetSystemCursor,
    qemu_ShowCaret,
    qemu_ShowCursor,
    qemu_UnregisterClassA,
    qemu_UnregisterClassW,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side user32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
