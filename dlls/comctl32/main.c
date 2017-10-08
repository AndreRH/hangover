/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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
#include <commctrl.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_comctl32.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comctl32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu__TrackMouseEvent,
    qemu_CreateMappedBitmap,
    qemu_CreatePropertySheetPageA,
    qemu_CreatePropertySheetPageW,
    qemu_CreateStatusWindowA,
    qemu_CreateStatusWindowW,
    qemu_CreateToolbar,
    qemu_CreateToolbarEx,
    qemu_CreateUpDownControl,
    qemu_DefSubclassProc,
    qemu_DestroyPropertySheetPage,
    qemu_DllGetVersion,
    qemu_DllInstall,
    qemu_DrawShadowText,
    qemu_DrawStatusTextA,
    qemu_DrawStatusTextW,
    qemu_GetEffectiveClientRect,
    qemu_GetMUILanguage,
    qemu_GetWindowSubclass,
    qemu_HIMAGELIST_QueryInterface,
    qemu_ImageList_Add,
    qemu_ImageList_AddIcon,
    qemu_ImageList_AddMasked,
    qemu_ImageList_BeginDrag,
    qemu_ImageList_CoCreateInstance,
    qemu_ImageList_Copy,
    qemu_ImageList_Create,
    qemu_ImageList_Destroy,
    qemu_ImageList_DragEnter,
    qemu_ImageList_DragLeave,
    qemu_ImageList_DragMove,
    qemu_ImageList_DragShowNolock,
    qemu_ImageList_Draw,
    qemu_ImageList_DrawEx,
    qemu_ImageList_DrawIndirect,
    qemu_ImageList_Duplicate,
    qemu_ImageList_EndDrag,
    qemu_ImageList_GetBkColor,
    qemu_ImageList_GetDragImage,
    qemu_ImageList_GetFlags,
    qemu_ImageList_GetIcon,
    qemu_ImageList_GetIconSize,
    qemu_ImageList_GetImageCount,
    qemu_ImageList_GetImageInfo,
    qemu_ImageList_GetImageRect,
    qemu_ImageList_LoadImageA,
    qemu_ImageList_LoadImageW,
    qemu_ImageList_Merge,
    qemu_ImageList_Read,
    qemu_ImageList_Remove,
    qemu_ImageList_Replace,
    qemu_ImageList_ReplaceIcon,
    qemu_ImageList_SetBkColor,
    qemu_ImageList_SetColorTable,
    qemu_ImageList_SetDragCursorImage,
    qemu_ImageList_SetFilter,
    qemu_ImageList_SetFlags,
    qemu_ImageList_SetIconSize,
    qemu_ImageList_SetImageCount,
    qemu_ImageList_SetOverlayImage,
    qemu_ImageList_Write,
    qemu_InitCommonControls,
    qemu_InitCommonControlsEx,
    qemu_InitMUILanguage,
    qemu_LoadIconMetric,
    qemu_LoadIconWithScaleDown,
    qemu_MenuHelp,
    qemu_MirrorIcon,
    qemu_PropertySheetA,
    qemu_PropertySheetW,
    qemu_RemoveWindowSubclass,
    qemu_SetPathWordBreakProc,
    qemu_SetWindowSubclass,
    qemu_ShowHideMenuCtl,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE comctl32;

    WINE_TRACE("Loading host-side comctl32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    comctl32 = GetModuleHandleA("comctl32");
    p_ImageList_SetColorTable = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(390));
    if (!p_ImageList_SetColorTable)
        WINE_ERR("Cannot resolve comctl32.390 (ImageList_SetColorTable).\n");
    p_DllGetVersion = (void *)GetProcAddress(comctl32, "DllGetVersion");
    if (!p_DllGetVersion)
        WINE_ERR("Cannot resolve comctl32.DllGetVersion.\n");

    return dll_functions;
}

#endif
