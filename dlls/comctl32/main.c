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
    qemu_AddMRUData,
    qemu_AddMRUStringA,
    qemu_AddMRUStringW,
    qemu_Alloc,
    qemu_CreateMappedBitmap,
    qemu_CreateMRUListA,
    qemu_CreateMRUListLazyA,
    qemu_CreateMRUListLazyW,
    qemu_CreateMRUListW,
    qemu_CreatePropertySheetPageA,
    qemu_CreatePropertySheetPageW,
    qemu_CreateStatusWindowA,
    qemu_CreateStatusWindowW,
    qemu_CreateToolbar,
    qemu_CreateToolbarEx,
    qemu_CreateUpDownControl,
    qemu_DefSubclassProc,
    qemu_DelMRUString,
    qemu_DestroyPropertySheetPage,
    qemu_DllGetVersion,
    qemu_DllInstall,
    qemu_DPA_Clone,
    qemu_DPA_Create,
    qemu_DPA_CreateEx,
    qemu_DPA_DeleteAllPtrs,
    qemu_DPA_DeletePtr,
    qemu_DPA_Destroy,
    qemu_DPA_DestroyCallback,
    qemu_DPA_EnumCallback,
    qemu_DPA_GetPtr,
    qemu_DPA_GetPtrIndex,
    qemu_DPA_GetSize,
    qemu_DPA_Grow,
    qemu_DPA_InsertPtr,
    qemu_DPA_LoadStream,
    qemu_DPA_Merge,
    qemu_DPA_SaveStream,
    qemu_DPA_Search,
    qemu_DPA_SetPtr,
    qemu_DPA_Sort,
    qemu_DrawInsert,
    qemu_DrawShadowText,
    qemu_DrawStatusTextA,
    qemu_DrawStatusTextW,
    qemu_DSA_Clone,
    qemu_DSA_Create,
    qemu_DSA_DeleteAllItems,
    qemu_DSA_DeleteItem,
    qemu_DSA_Destroy,
    qemu_DSA_DestroyCallback,
    qemu_DSA_EnumCallback,
    qemu_DSA_GetItem,
    qemu_DSA_GetItemPtr,
    qemu_DSA_GetSize,
    qemu_DSA_InsertItem,
    qemu_DSA_SetItem,
    qemu_EnumMRUListA,
    qemu_EnumMRUListW,
    qemu_FindMRUData,
    qemu_FindMRUStringA,
    qemu_FindMRUStringW,
    qemu_FlatSB_EnableScrollBar,
    qemu_FlatSB_GetScrollInfo,
    qemu_FlatSB_GetScrollPos,
    qemu_FlatSB_GetScrollProp,
    qemu_FlatSB_GetScrollRange,
    qemu_FlatSB_SetScrollInfo,
    qemu_FlatSB_SetScrollPos,
    qemu_FlatSB_SetScrollProp,
    qemu_FlatSB_SetScrollRange,
    qemu_FlatSB_ShowScrollBar,
    qemu_Free,
    qemu_FreeMRUList,
    qemu_GetEffectiveClientRect,
    qemu_GetMUILanguage,
    qemu_GetSize,
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
    qemu_InitializeFlatSB,
    qemu_InitMUILanguage,
    qemu_IntlStrEqWorkerA,
    qemu_IntlStrEqWorkerW,
    qemu_LBItemFromPt,
    qemu_LoadIconMetric,
    qemu_LoadIconWithScaleDown,
    qemu_MakeDragList,
    qemu_MenuHelp,
    qemu_MirrorIcon,
    qemu_PropertySheetA,
    qemu_PropertySheetW,
    qemu_ReAlloc,
    qemu_RemoveWindowSubclass,
    qemu_SendNotify,
    qemu_SendNotifyEx,
    qemu_SetPathWordBreakProc,
    qemu_SetWindowSubclass,
    qemu_ShowHideMenuCtl,
    qemu_SmoothScrollWindow,
    qemu_Str_GetPtrA,
    qemu_Str_GetPtrW,
    qemu_Str_SetPtrA,
    qemu_Str_SetPtrW,
    qemu_StrChrA,
    qemu_StrChrIA,
    qemu_StrChrIW,
    qemu_StrChrW,
    qemu_StrCmpNA,
    qemu_StrCmpNIA,
    qemu_StrCmpNIW,
    qemu_StrCmpNW,
    qemu_StrCSpnA,
    qemu_StrCSpnIA,
    qemu_StrCSpnIW,
    qemu_StrCSpnW,
    qemu_StrRChrA,
    qemu_StrRChrIA,
    qemu_StrRChrIW,
    qemu_StrRChrW,
    qemu_StrRStrIA,
    qemu_StrRStrIW,
    qemu_StrStrA,
    qemu_StrStrIA,
    qemu_StrStrIW,
    qemu_StrStrW,
    qemu_StrToIntA,
    qemu_StrToIntW,
    qemu_TaskDialog,
    qemu_TaskDialogIndirect,
    qemu_UninitializeFlatSB,
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
