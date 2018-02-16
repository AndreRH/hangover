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
#include <assert.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_comctl32.h"

struct qemu_set_callbacks
{
    struct qemu_syscall super;
    uint64_t wndproc_wrapper;
};

struct wndproc_call
{
    uint64_t wndproc;
    uint64_t win, msg, wparam, lparam;
};

#ifdef QEMU_DLL_GUEST

static LRESULT __fastcall wndproc_wrapper(const struct wndproc_call *call)
{
    WNDPROC proc = (WNDPROC)(ULONG_PTR)call->wndproc;
    LRESULT ret = 0;

    ret = proc((HWND)(ULONG_PTR)call->win, call->msg, call->wparam, call->lparam);

    return ret;
}

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_set_callbacks call;

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            call.super.id = QEMU_SYSCALL_ID(CALL_SET_CALLBACKS);
            call.wndproc_wrapper = (ULONG_PTR)wndproc_wrapper;
            qemu_syscall(&call.super);
            break;

        case DLL_PROCESS_DETACH:
            call.super.id = QEMU_SYSCALL_ID(CALL_SET_CALLBACKS);
            call.wndproc_wrapper = 0;
            qemu_syscall(&call.super);
            break;
    }
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comctl32);

#include "callback_helper_impl.h"

const struct qemu_ops *qemu_ops;
static uint64_t guest_wndproc_wrapper;
static HMODULE comctl32;

static void qemu_set_callbacks(struct qemu_syscall *call)
{
    struct qemu_set_callbacks *c = (struct qemu_set_callbacks *)call;

    guest_wndproc_wrapper = c->wndproc_wrapper;

    if (c->wndproc_wrapper)
    {
        /* We have to delay loading the host comctl32 until the client loads the client library
         * to ensure that comctl32 registers the controls with class names that match the requested
         * version in the activation context manifest. Reloading the library with a different
         * manifest is also required for the comctl32 tests. */
        WINE_TRACE("Loading comctl32.dll\n");

        /* Of course this means that I have to load any library that links to comctl32 at runtime too,
         * e.g. comdlg32. This DllMain function should be called first by the loader. */
        comctl32 = GetModuleHandleA("comctl32");
        if (comctl32)
            WINE_ERR("Comctl32 already loaded!\n");

        comctl32 = LoadLibraryA("comctl32");

        if (!comctl32)
            WINE_ERR("Failed to load host comctl32.\n");

        hook_wndprocs();

        p_ImageList_SetColorTable = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(390));
        if (!p_ImageList_SetColorTable)
            WINE_ERR("Cannot resolve comctl32.390 (ImageList_SetColorTable).\n");

        p_DllGetVersion = (void *)GetProcAddress(comctl32, "DllGetVersion");
        if (!p_DllGetVersion)
            WINE_ERR("Cannot resolve comctl32.DllGetVersion.\n");

        p_Alloc = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(71));
        if (!p_Alloc)
            WINE_ERR("Could not load Alloc from comctl32.dll.\n");

        p_ReAlloc = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(72));
        if (!p_ReAlloc)
            WINE_ERR("Could not load ReAlloc from comctl32.dll.\n");

        p_Free = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(73));
        if (!p_Free)
            WINE_ERR("Could not load Free from comctl32.dll.\n");

        p_GetSize = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(74));
        if (!p_GetSize)
            WINE_ERR("Could not load GetSize from comctl32.dll.\n");

        p_FreeMRUList = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(152));
        if (!p_FreeMRUList)
            WINE_ERR("Could not load FreeMRUList from comctl32.dll.\n");

        p_FindMRUData = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(169));
        if (!p_FindMRUData)
            WINE_ERR("Could not load FindMRUData from comctl32.dll.\n");

        p_AddMRUData = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(167));
        if (!p_AddMRUData)
            WINE_ERR("Could not load AddMRUData from comctl32.dll.\n");

        p_AddMRUStringW = (void *)GetProcAddress(comctl32, "AddMRUStringW");
        if (!p_AddMRUStringW)
            WINE_ERR("Could not load AddMRUStringW from comctl32.dll.\n");

        p_AddMRUStringA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(153));
        if (!p_AddMRUStringA)
            WINE_ERR("Could not load AddMRUStringA from comctl32.dll.\n");

        p_DelMRUString = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(156));
        if (!p_DelMRUString)
            WINE_ERR("Could not load DelMRUString from comctl32.dll.\n");

        p_FindMRUStringW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(402));
        if (!p_FindMRUStringW)
            WINE_ERR("Could not load FindMRUStringW from comctl32.dll.\n");

        p_FindMRUStringA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(155));
        if (!p_FindMRUStringA)
            WINE_ERR("Could not load FindMRUStringA from comctl32.dll.\n");

        p_CreateMRUListLazyW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(404));
        if (!p_CreateMRUListLazyW)
            WINE_ERR("Could not load CreateMRUListLazyW from comctl32.dll.\n");

        p_CreateMRUListLazyA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(157));
        if (!p_CreateMRUListLazyA)
            WINE_ERR("Could not load CreateMRUListLazyA from comctl32.dll.\n");

        p_CreateMRUListW = (void *)GetProcAddress(comctl32, "CreateMRUListW");
        if (!p_CreateMRUListW)
            WINE_ERR("Could not load CreateMRUListW from comctl32.dll.\n");

        p_CreateMRUListA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(151));
        if (!p_CreateMRUListA)
            WINE_ERR("Could not load CreateMRUListA from comctl32.dll.\n");

        p_EnumMRUListW = (void *)GetProcAddress(comctl32, "EnumMRUListW");
        if (!p_EnumMRUListW)
            WINE_ERR("Could not load EnumMRUListW from comctl32.dll.\n");

        p_EnumMRUListA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(154));
        if (!p_EnumMRUListA)
            WINE_ERR("Could not load EnumMRUListA from comctl32.dll.\n");

        p_SendNotify = (void *)GetProcAddress(comctl32,MAKEINTRESOURCE(341));
        if (!p_SendNotify)
            WINE_ERR("Could not load SendNotify from comctl32.dll.\n");

        p_SendNotifyEx = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(342));
        if (!p_SendNotifyEx)
            WINE_ERR("Could not load SendNotifyEx from comctl32.dll.\n");

        p_MenuHelp = (void *)GetProcAddress(comctl32, "MenuHelp");
        if (!p_MenuHelp)
            WINE_ERR("Could not load MenuHelp from comctl32.dll.\n");

        p_ShowHideMenuCtl = (void *)GetProcAddress(comctl32, "ShowHideMenuCtl");
        if (!p_ShowHideMenuCtl)
            WINE_ERR("Could not load ShowHideMenuCtl from comctl32.dll.\n");

        p_GetEffectiveClientRect = (void *)GetProcAddress(comctl32, "GetEffectiveClientRect");
        if (!p_GetEffectiveClientRect)
            WINE_ERR("Could not load GetEffectiveClientRect from comctl32.dll.\n");

        p_DrawStatusTextW = (void *)GetProcAddress(comctl32, "DrawStatusTextW");
        if (!p_DrawStatusTextW)
            WINE_ERR("Could not load DrawStatusTextW from comctl32.dll.\n");

        p_DrawStatusTextA = (void *)GetProcAddress(comctl32, "DrawStatusTextA");
        if (!p_DrawStatusTextA)
            WINE_ERR("Could not load DrawStatusTextA from comctl32.dll.\n");

        p_CreateStatusWindowA = (void *)GetProcAddress(comctl32, "CreateStatusWindowA");
        if (!p_CreateStatusWindowA)
            WINE_ERR("Could not load CreateStatusWindowA from comctl32.dll.\n");

        p_CreateStatusWindowW = (void *)GetProcAddress(comctl32, "CreateStatusWindowW");
        if (!p_CreateStatusWindowW)
            WINE_ERR("Could not load CreateStatusWindowW from comctl32.dll.\n");

        p_CreateUpDownControl = (void *)GetProcAddress(comctl32, "CreateUpDownControl");
        if (!p_CreateUpDownControl)
            WINE_ERR("Could not load CreateUpDownControl from comctl32.dll.\n");

        p_InitCommonControls = (void *)GetProcAddress(comctl32, "InitCommonControls");
        if (!p_InitCommonControls)
            WINE_ERR("Could not load InitCommonControls from comctl32.dll.\n");

        p_InitCommonControlsEx = (void *)GetProcAddress(comctl32, "InitCommonControlsEx");
        if (!p_InitCommonControlsEx)
            WINE_ERR("Could not load InitCommonControlsEx from comctl32.dll.\n");

        p_CreateToolbarEx = (void *)GetProcAddress(comctl32, "CreateToolbarEx");
        if (!p_CreateToolbarEx)
            WINE_ERR("Could not load CreateToolbarEx from comctl32.dll.\n");

        p_CreateMappedBitmap = (void *)GetProcAddress(comctl32, "CreateMappedBitmap");
        if (!p_CreateMappedBitmap)
            WINE_ERR("Could not load CreateMappedBitmap from comctl32.dll.\n");

        p_CreateToolbar = (void *)GetProcAddress(comctl32, "CreateToolbar");
        if (!p_CreateToolbar)
            WINE_ERR("Could not load CreateToolbar from comctl32.dll.\n");

        p_DllGetVersion = (void *)GetProcAddress(comctl32, "DllGetVersion");
        if (!p_DllGetVersion)
            WINE_ERR("Could not load DllGetVersion from comctl32.dll.\n");

        p_DllInstall = (void *)GetProcAddress(comctl32, "DllInstall");
        if (!p_DllInstall)
            WINE_ERR("Could not load DllInstall from comctl32.dll.\n");

        p__TrackMouseEvent = (void *)GetProcAddress(comctl32, "_TrackMouseEvent");
        if (!p__TrackMouseEvent)
            WINE_ERR("Could not load _TrackMouseEvent from comctl32.dll.\n");

        p_GetMUILanguage = (void *)GetProcAddress(comctl32, "GetMUILanguage");
        if (!p_GetMUILanguage)
            WINE_ERR("Could not load GetMUILanguage from comctl32.dll.\n");

        p_InitMUILanguage = (void *)GetProcAddress(comctl32, "InitMUILanguage");
        if (!p_InitMUILanguage)
            WINE_ERR("Could not load InitMUILanguage from comctl32.dll.\n");

        p_SetWindowSubclass = (void *)GetProcAddress(comctl32, "SetWindowSubclass");
        if (!p_SetWindowSubclass)
            WINE_ERR("Could not load SetWindowSubclass from comctl32.dll.\n");

        p_GetWindowSubclass = (void *)GetProcAddress(comctl32, "GetWindowSubclass");
        if (!p_GetWindowSubclass)
            WINE_ERR("Could not load GetWindowSubclass from comctl32.dll.\n");

        p_RemoveWindowSubclass = (void *)GetProcAddress(comctl32, "RemoveWindowSubclass");
        if (!p_RemoveWindowSubclass)
            WINE_ERR("Could not load RemoveWindowSubclass from comctl32.dll.\n");

        p_DefSubclassProc = (void *)GetProcAddress(comctl32, "DefSubclassProc");
        if (!p_DefSubclassProc)
            WINE_ERR("Could not load DefSubclassProc from comctl32.dll.\n");

        p_MirrorIcon = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(414));
        if (!p_MirrorIcon)
            WINE_ERR("Could not load MirrorIcon from comctl32.dll.\n");

        p_SetPathWordBreakProc = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(384));
        if (!p_SetPathWordBreakProc)
            WINE_ERR("Could not load SetPathWordBreakProc from comctl32.dll.\n");

        p_DrawShadowText = (void *)GetProcAddress(comctl32, "DrawShadowText");
        if (!p_DrawShadowText)
            WINE_ERR("Could not load DrawShadowText from comctl32.dll.\n");

        p_LoadIconWithScaleDown = (void *)GetProcAddress(comctl32, "LoadIconWithScaleDown");
        if (!p_LoadIconWithScaleDown)
            WINE_ERR("Could not load LoadIconWithScaleDown from comctl32.dll.\n");

        p_LoadIconMetric = (void *)GetProcAddress(comctl32, "LoadIconMetric");
        if (!p_LoadIconMetric)
            WINE_ERR("Could not load LoadIconMetric from comctl32.dll.\n");

        p_DPA_LoadStream = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(9));
        if (!p_DPA_LoadStream)
            WINE_ERR("Could not load DPA_LoadStream from comctl32.dll.\n");

        p_DPA_SaveStream = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(10));
        if (!p_DPA_SaveStream)
            WINE_ERR("Could not load DPA_SaveStream from comctl32.dll.\n");

        p_DPA_Merge = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(11));
        if (!p_DPA_Merge)
            WINE_ERR("Could not load DPA_Merge from comctl32.dll.\n");

        p_DPA_Destroy = (void *)GetProcAddress(comctl32, "DPA_Destroy");
        if (!p_DPA_Destroy)
            WINE_ERR("Could not load DPA_Destroy from comctl32.dll.\n");

        p_DPA_Grow = (void *)GetProcAddress(comctl32, "DPA_Grow");
        if (!p_DPA_Grow)
            WINE_ERR("Could not load DPA_Grow from comctl32.dll.\n");

        p_DPA_Clone = (void *)GetProcAddress(comctl32, "DPA_Clone");
        if (!p_DPA_Clone)
            WINE_ERR("Could not load DPA_Clone from comctl32.dll.\n");

        p_DPA_GetPtr = (void *)GetProcAddress(comctl32, "DPA_GetPtr");
        if (!p_DPA_GetPtr)
            WINE_ERR("Could not load DPA_GetPtr from comctl32.dll.\n");

        p_DPA_GetPtrIndex = (void *)GetProcAddress(comctl32, "DPA_GetPtrIndex");
        if (!p_DPA_GetPtrIndex)
            WINE_ERR("Could not load DPA_GetPtrIndex from comctl32.dll.\n");

        p_DPA_InsertPtr = (void *)GetProcAddress(comctl32, "DPA_InsertPtr");
        if (!p_DPA_InsertPtr)
            WINE_ERR("Could not load DPA_InsertPtr from comctl32.dll.\n");

        p_DPA_SetPtr = (void *)GetProcAddress(comctl32, "DPA_SetPtr");
        if (!p_DPA_SetPtr)
            WINE_ERR("Could not load DPA_SetPtr from comctl32.dll.\n");

        p_DPA_DeletePtr = (void *)GetProcAddress(comctl32, "DPA_DeletePtr");
        if (!p_DPA_DeletePtr)
            WINE_ERR("Could not load DPA_DeletePtr from comctl32.dll.\n");

        p_DPA_DeleteAllPtrs = (void *)GetProcAddress(comctl32, "DPA_DeleteAllPtrs");
        if (!p_DPA_DeleteAllPtrs)
            WINE_ERR("Could not load DPA_DeleteAllPtrs from comctl32.dll.\n");

        p_DPA_Sort = (void *)GetProcAddress(comctl32, "DPA_Sort");
        if (!p_DPA_Sort)
            WINE_ERR("Could not load DPA_Sort from comctl32.dll.\n");

        p_DPA_Search = (void *)GetProcAddress(comctl32, "DPA_Search");
        if (!p_DPA_Search)
            WINE_ERR("Could not load DPA_Search from comctl32.dll.\n");

        p_DPA_CreateEx = (void *)GetProcAddress(comctl32, "DPA_CreateEx");
        if (!p_DPA_CreateEx)
            WINE_ERR("Could not load DPA_CreateEx from comctl32.dll.\n");

        p_DPA_Create = (void *)GetProcAddress(comctl32, "DPA_Create");
        if (!p_DPA_Create)
            WINE_ERR("Could not load DPA_Create from comctl32.dll.\n");

        p_DPA_EnumCallback = (void *)GetProcAddress(comctl32, "DPA_EnumCallback");
        if (!p_DPA_EnumCallback)
            WINE_ERR("Could not load DPA_EnumCallback from comctl32.dll.\n");

        p_DPA_DestroyCallback = (void *)GetProcAddress(comctl32, "DPA_DestroyCallback");
        if (!p_DPA_DestroyCallback)
            WINE_ERR("Could not load DPA_DestroyCallback from comctl32.dll.\n");

        p_DPA_GetSize = (void *)GetProcAddress(comctl32, "DPA_GetSize");
        if (!p_DPA_GetSize)
            WINE_ERR("Could not load DPA_GetSize from comctl32.dll.\n");

        p_MakeDragList = (void *)GetProcAddress(comctl32, "MakeDragList");
        if (!p_MakeDragList)
            WINE_ERR("Could not load MakeDragList from comctl32.dll.\n");

        p_DrawInsert = (void *)GetProcAddress(comctl32, "DrawInsert");
        if (!p_DrawInsert)
            WINE_ERR("Could not load DrawInsert from comctl32.dll.\n");

        p_LBItemFromPt = (void *)GetProcAddress(comctl32, "LBItemFromPt");
        if (!p_LBItemFromPt)
            WINE_ERR("Could not load LBItemFromPt from comctl32.dll.\n");

        p_DSA_Create = (void *)GetProcAddress(comctl32, "DSA_Create");
        if (!p_DSA_Create)
            WINE_ERR("Could not load DSA_Create from comctl32.dll.\n");

        p_DSA_Destroy = (void *)GetProcAddress(comctl32, "DSA_Destroy");
        if (!p_DSA_Destroy)
            WINE_ERR("Could not load DSA_Destroy from comctl32.dll.\n");

        p_DSA_GetItem = (void *)GetProcAddress(comctl32, "DSA_GetItem");
        if (!p_DSA_GetItem)
            WINE_ERR("Could not load DSA_GetItem from comctl32.dll.\n");

        p_DSA_GetItemPtr = (void *)GetProcAddress(comctl32, "DSA_GetItemPtr");
        if (!p_DSA_GetItemPtr)
            WINE_ERR("Could not load DSA_GetItemPtr from comctl32.dll.\n");

        p_DSA_SetItem = (void *)GetProcAddress(comctl32, "DSA_SetItem");
        if (!p_DSA_SetItem)
            WINE_ERR("Could not load DSA_SetItem from comctl32.dll.\n");

        p_DSA_InsertItem = (void *)GetProcAddress(comctl32, "DSA_InsertItem");
        if (!p_DSA_InsertItem)
            WINE_ERR("Could not load DSA_InsertItem from comctl32.dll.\n");

        p_DSA_DeleteItem = (void *)GetProcAddress(comctl32, "DSA_DeleteItem");
        if (!p_DSA_DeleteItem)
            WINE_ERR("Could not load DSA_DeleteItem from comctl32.dll.\n");

        p_DSA_DeleteAllItems = (void *)GetProcAddress(comctl32, "DSA_DeleteAllItems");
        if (!p_DSA_DeleteAllItems)
            WINE_ERR("Could not load DSA_DeleteAllItems from comctl32.dll.\n");

        p_DSA_EnumCallback = (void *)GetProcAddress(comctl32, "DSA_EnumCallback");
        if (!p_DSA_EnumCallback)
            WINE_ERR("Could not load DSA_EnumCallback from comctl32.dll.\n");

        p_DSA_DestroyCallback = (void *)GetProcAddress(comctl32, "DSA_DestroyCallback");
        if (!p_DSA_DestroyCallback)
            WINE_ERR("Could not load DSA_DestroyCallback from comctl32.dll.\n");

        p_DSA_Clone = (void *)GetProcAddress(comctl32, "DSA_Clone");
        if (!p_DSA_Clone)
            WINE_ERR("Could not load DSA_Clone from comctl32.dll.\n");

        p_DSA_GetSize = (void *)GetProcAddress(comctl32, "DSA_GetSize");
        if (!p_DSA_GetSize)
            WINE_ERR("Could not load DSA_GetSize from comctl32.dll.\n");

        p_InitializeFlatSB = (void *)GetProcAddress(comctl32, "InitializeFlatSB");
        if (!p_InitializeFlatSB)
            WINE_ERR("Could not load InitializeFlatSB from comctl32.dll.\n");

        p_UninitializeFlatSB = (void *)GetProcAddress(comctl32, "UninitializeFlatSB");
        if (!p_UninitializeFlatSB)
            WINE_ERR("Could not load UninitializeFlatSB from comctl32.dll.\n");

        p_FlatSB_GetScrollProp = (void *)GetProcAddress(comctl32, "FlatSB_GetScrollProp");
        if (!p_FlatSB_GetScrollProp)
            WINE_ERR("Could not load FlatSB_GetScrollProp from comctl32.dll.\n");

        p_FlatSB_SetScrollProp = (void *)GetProcAddress(comctl32, "FlatSB_SetScrollProp");
        if (!p_FlatSB_SetScrollProp)
            WINE_ERR("Could not load FlatSB_SetScrollProp from comctl32.dll.\n");

        p_FlatSB_EnableScrollBar = (void *)GetProcAddress(comctl32, "FlatSB_EnableScrollBar");
        if (!p_FlatSB_EnableScrollBar)
            WINE_ERR("Could not load FlatSB_EnableScrollBar from comctl32.dll.\n");

        p_FlatSB_ShowScrollBar = (void *)GetProcAddress(comctl32, "FlatSB_ShowScrollBar");
        if (!p_FlatSB_ShowScrollBar)
            WINE_ERR("Could not load FlatSB_ShowScrollBar from comctl32.dll.\n");

        p_FlatSB_GetScrollRange = (void *)GetProcAddress(comctl32, "FlatSB_GetScrollRange");
        if (!p_FlatSB_GetScrollRange)
            WINE_ERR("Could not load FlatSB_GetScrollRange from comctl32.dll.\n");

        p_FlatSB_GetScrollInfo = (void *)GetProcAddress(comctl32, "FlatSB_GetScrollInfo");
        if (!p_FlatSB_GetScrollInfo)
            WINE_ERR("Could not load FlatSB_GetScrollInfo from comctl32.dll.\n");

        p_FlatSB_GetScrollPos = (void *)GetProcAddress(comctl32, "FlatSB_GetScrollPos");
        if (!p_FlatSB_GetScrollPos)
            WINE_ERR("Could not load FlatSB_GetScrollPos from comctl32.dll.\n");

        p_FlatSB_SetScrollPos = (void *)GetProcAddress(comctl32, "FlatSB_SetScrollPos");
        if (!p_FlatSB_SetScrollPos)
            WINE_ERR("Could not load FlatSB_SetScrollPos from comctl32.dll.\n");

        p_FlatSB_SetScrollInfo = (void *)GetProcAddress(comctl32, "FlatSB_SetScrollInfo");
        if (!p_FlatSB_SetScrollInfo)
            WINE_ERR("Could not load FlatSB_SetScrollInfo from comctl32.dll.\n");

        p_FlatSB_SetScrollRange = (void *)GetProcAddress(comctl32, "FlatSB_SetScrollRange");
        if (!p_FlatSB_SetScrollRange)
            WINE_ERR("Could not load FlatSB_SetScrollRange from comctl32.dll.\n");

        p_ImageList_Add = (void *)GetProcAddress(comctl32, "ImageList_Add");
        if (!p_ImageList_Add)
            WINE_ERR("Could not load ImageList_Add from comctl32.dll.\n");

        p_ImageList_AddIcon = (void *)GetProcAddress(comctl32, "ImageList_AddIcon");
        if (!p_ImageList_AddIcon)
            WINE_ERR("Could not load ImageList_AddIcon from comctl32.dll.\n");

        p_ImageList_AddMasked = (void *)GetProcAddress(comctl32, "ImageList_AddMasked");
        if (!p_ImageList_AddMasked)
            WINE_ERR("Could not load ImageList_AddMasked from comctl32.dll.\n");

        p_ImageList_BeginDrag = (void *)GetProcAddress(comctl32, "ImageList_BeginDrag");
        if (!p_ImageList_BeginDrag)
            WINE_ERR("Could not load ImageList_BeginDrag from comctl32.dll.\n");

        p_ImageList_Copy = (void *)GetProcAddress(comctl32, "ImageList_Copy");
        if (!p_ImageList_Copy)
            WINE_ERR("Could not load ImageList_Copy from comctl32.dll.\n");

        p_ImageList_Create = (void *)GetProcAddress(comctl32, "ImageList_Create");
        if (!p_ImageList_Create)
            WINE_ERR("Could not load ImageList_Create from comctl32.dll.\n");

        p_ImageList_Destroy = (void *)GetProcAddress(comctl32, "ImageList_Destroy");
        if (!p_ImageList_Destroy)
            WINE_ERR("Could not load ImageList_Destroy from comctl32.dll.\n");

        p_ImageList_DragEnter = (void *)GetProcAddress(comctl32, "ImageList_DragEnter");
        if (!p_ImageList_DragEnter)
            WINE_ERR("Could not load ImageList_DragEnter from comctl32.dll.\n");

        p_ImageList_DragLeave = (void *)GetProcAddress(comctl32, "ImageList_DragLeave");
        if (!p_ImageList_DragLeave)
            WINE_ERR("Could not load ImageList_DragLeave from comctl32.dll.\n");

        p_ImageList_DragMove = (void *)GetProcAddress(comctl32, "ImageList_DragMove");
        if (!p_ImageList_DragMove)
            WINE_ERR("Could not load ImageList_DragMove from comctl32.dll.\n");

        p_ImageList_DragShowNolock = (void *)GetProcAddress(comctl32, "ImageList_DragShowNolock");
        if (!p_ImageList_DragShowNolock)
            WINE_ERR("Could not load ImageList_DragShowNolock from comctl32.dll.\n");

        p_ImageList_Draw = (void *)GetProcAddress(comctl32, "ImageList_Draw");
        if (!p_ImageList_Draw)
            WINE_ERR("Could not load ImageList_Draw from comctl32.dll.\n");

        p_ImageList_DrawEx = (void *)GetProcAddress(comctl32, "ImageList_DrawEx");
        if (!p_ImageList_DrawEx)
            WINE_ERR("Could not load ImageList_DrawEx from comctl32.dll.\n");

        p_ImageList_DrawIndirect = (void *)GetProcAddress(comctl32, "ImageList_DrawIndirect");
        if (!p_ImageList_DrawIndirect)
            WINE_ERR("Could not load ImageList_DrawIndirect from comctl32.dll.\n");

        p_ImageList_Duplicate = (void *)GetProcAddress(comctl32, "ImageList_Duplicate");
        if (!p_ImageList_Duplicate)
            WINE_ERR("Could not load ImageList_Duplicate from comctl32.dll.\n");

        p_ImageList_EndDrag = (void *)GetProcAddress(comctl32, "ImageList_EndDrag");
        if (!p_ImageList_EndDrag)
            WINE_ERR("Could not load ImageList_EndDrag from comctl32.dll.\n");

        p_ImageList_GetBkColor = (void *)GetProcAddress(comctl32, "ImageList_GetBkColor");
        if (!p_ImageList_GetBkColor)
            WINE_ERR("Could not load ImageList_GetBkColor from comctl32.dll.\n");

        p_ImageList_GetDragImage = (void *)GetProcAddress(comctl32, "ImageList_GetDragImage");
        if (!p_ImageList_GetDragImage)
            WINE_ERR("Could not load ImageList_GetDragImage from comctl32.dll.\n");

        p_ImageList_GetFlags = (void *)GetProcAddress(comctl32, "ImageList_GetFlags");
        if (!p_ImageList_GetFlags)
            WINE_ERR("Could not load ImageList_GetFlags from comctl32.dll.\n");

        p_ImageList_GetIcon = (void *)GetProcAddress(comctl32, "ImageList_GetIcon");
        if (!p_ImageList_GetIcon)
            WINE_ERR("Could not load ImageList_GetIcon from comctl32.dll.\n");

        p_ImageList_GetIconSize = (void *)GetProcAddress(comctl32, "ImageList_GetIconSize");
        if (!p_ImageList_GetIconSize)
            WINE_ERR("Could not load ImageList_GetIconSize from comctl32.dll.\n");

        p_ImageList_GetImageCount = (void *)GetProcAddress(comctl32, "ImageList_GetImageCount");
        if (!p_ImageList_GetImageCount)
            WINE_ERR("Could not load ImageList_GetImageCount from comctl32.dll.\n");

        p_ImageList_GetImageInfo = (void *)GetProcAddress(comctl32, "ImageList_GetImageInfo");
        if (!p_ImageList_GetImageInfo)
            WINE_ERR("Could not load ImageList_GetImageInfo from comctl32.dll.\n");

        p_ImageList_GetImageRect = (void *)GetProcAddress(comctl32, "ImageList_GetImageRect");
        if (!p_ImageList_GetImageRect)
            WINE_ERR("Could not load ImageList_GetImageRect from comctl32.dll.\n");

        p_ImageList_LoadImageA = (void *)GetProcAddress(comctl32, "ImageList_LoadImageA");
        if (!p_ImageList_LoadImageA)
            WINE_ERR("Could not load ImageList_LoadImageA from comctl32.dll.\n");

        p_ImageList_LoadImageW = (void *)GetProcAddress(comctl32, "ImageList_LoadImageW");
        if (!p_ImageList_LoadImageW)
            WINE_ERR("Could not load ImageList_LoadImageW from comctl32.dll.\n");

        p_ImageList_Merge = (void *)GetProcAddress(comctl32, "ImageList_Merge");
        if (!p_ImageList_Merge)
            WINE_ERR("Could not load ImageList_Merge from comctl32.dll.\n");

        p_ImageList_Read = (void *)GetProcAddress(comctl32, "ImageList_Read");
        if (!p_ImageList_Read)
            WINE_ERR("Could not load ImageList_Read from comctl32.dll.\n");

        p_ImageList_Remove = (void *)GetProcAddress(comctl32, "ImageList_Remove");
        if (!p_ImageList_Remove)
            WINE_ERR("Could not load ImageList_Remove from comctl32.dll.\n");

        p_ImageList_Replace = (void *)GetProcAddress(comctl32, "ImageList_Replace");
        if (!p_ImageList_Replace)
            WINE_ERR("Could not load ImageList_Replace from comctl32.dll.\n");

        p_ImageList_ReplaceIcon = (void *)GetProcAddress(comctl32, "ImageList_ReplaceIcon");
        if (!p_ImageList_ReplaceIcon)
            WINE_ERR("Could not load ImageList_ReplaceIcon from comctl32.dll.\n");

        p_ImageList_SetBkColor = (void *)GetProcAddress(comctl32, "ImageList_SetBkColor");
        if (!p_ImageList_SetBkColor)
            WINE_ERR("Could not load ImageList_SetBkColor from comctl32.dll.\n");

        p_ImageList_SetDragCursorImage = (void *)GetProcAddress(comctl32, "ImageList_SetDragCursorImage");
        if (!p_ImageList_SetDragCursorImage)
            WINE_ERR("Could not load ImageList_SetDragCursorImage from comctl32.dll.\n");

        p_ImageList_SetFilter = (void *)GetProcAddress(comctl32, "ImageList_SetFilter");
        if (!p_ImageList_SetFilter)
            WINE_ERR("Could not load ImageList_SetFilter from comctl32.dll.\n");

        p_ImageList_SetFlags = (void *)GetProcAddress(comctl32, "ImageList_SetFlags");
        if (!p_ImageList_SetFlags)
            WINE_ERR("Could not load ImageList_SetFlags from comctl32.dll.\n");

        p_ImageList_SetIconSize = (void *)GetProcAddress(comctl32, "ImageList_SetIconSize");
        if (!p_ImageList_SetIconSize)
            WINE_ERR("Could not load ImageList_SetIconSize from comctl32.dll.\n");

        p_ImageList_SetImageCount = (void *)GetProcAddress(comctl32, "ImageList_SetImageCount");
        if (!p_ImageList_SetImageCount)
            WINE_ERR("Could not load ImageList_SetImageCount from comctl32.dll.\n");

        p_ImageList_SetOverlayImage = (void *)GetProcAddress(comctl32, "ImageList_SetOverlayImage");
        if (!p_ImageList_SetOverlayImage)
            WINE_ERR("Could not load ImageList_SetOverlayImage from comctl32.dll.\n");

        p_ImageList_Write = (void *)GetProcAddress(comctl32, "ImageList_Write");
        if (!p_ImageList_Write)
            WINE_ERR("Could not load ImageList_Write from comctl32.dll.\n");

        p_ImageList_CoCreateInstance = (void *)GetProcAddress(comctl32, "ImageList_CoCreateInstance");
        if (!p_ImageList_CoCreateInstance)
            WINE_ERR("Could not load ImageList_CoCreateInstance from comctl32.dll.\n");

        p_HIMAGELIST_QueryInterface = (void *)GetProcAddress(comctl32, "HIMAGELIST_QueryInterface");
        if (!p_HIMAGELIST_QueryInterface)
            WINE_ERR("Could not load HIMAGELIST_QueryInterface from comctl32.dll.\n");

        p_PropertySheetA = (void *)GetProcAddress(comctl32, "PropertySheetA");
        if (!p_PropertySheetA)
            WINE_ERR("Could not load PropertySheetA from comctl32.dll.\n");

        p_PropertySheetW = (void *)GetProcAddress(comctl32, "PropertySheetW");
        if (!p_PropertySheetW)
            WINE_ERR("Could not load PropertySheetW from comctl32.dll.\n");

        p_CreatePropertySheetPageA = (void *)GetProcAddress(comctl32, "CreatePropertySheetPageA");
        if (!p_CreatePropertySheetPageA)
            WINE_ERR("Could not load CreatePropertySheetPageA from comctl32.dll.\n");

        p_CreatePropertySheetPageW = (void *)GetProcAddress(comctl32, "CreatePropertySheetPageW");
        if (!p_CreatePropertySheetPageW)
            WINE_ERR("Could not load CreatePropertySheetPageW from comctl32.dll.\n");

        p_DestroyPropertySheetPage = (void *)GetProcAddress(comctl32, "DestroyPropertySheetPage");
        if (!p_DestroyPropertySheetPage)
            WINE_ERR("Could not load DestroyPropertySheetPage from comctl32.dll.\n");

        p_SmoothScrollWindow = (void *)GetProcAddress(comctl32,  MAKEINTRESOURCE(382));
        if (!p_SmoothScrollWindow)
            WINE_ERR("Could not load SmoothScrollWindow from comctl32.dll.\n");

        p_Str_GetPtrA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(233));
        if (!p_Str_GetPtrA)
            WINE_ERR("Could not load Str_GetPtrA from comctl32.dll.\n");

        p_Str_SetPtrA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(234));
        if (!p_Str_SetPtrA)
            WINE_ERR("Could not load Str_SetPtrA from comctl32.dll.\n");

        p_Str_GetPtrW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(235));
        if (!p_Str_GetPtrW)
            WINE_ERR("Could not load Str_GetPtrW from comctl32.dll.\n");

        p_Str_SetPtrW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(236));
        if (!p_Str_SetPtrW)
            WINE_ERR("Could not load Str_SetPtrW from comctl32.dll.\n");

        p_StrChrA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(350));
        if (!p_StrChrA)
            WINE_ERR("Could not load StrChrA from comctl32.dll.\n");

        p_StrCmpNIA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(353));
        if (!p_StrCmpNIA)
            WINE_ERR("Could not load StrCmpNIA from comctl32.dll.\n");

        p_StrCmpNIW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(361));
        if (!p_StrCmpNIW)
            WINE_ERR("Could not load StrCmpNIW from comctl32.dll.\n");

        p_StrStrIA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(355));
        if (!p_StrStrIA)
            WINE_ERR("Could not load StrStrIA from comctl32.dll.\n");

        p_StrToIntA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(357));
        if (!p_StrToIntA)
            WINE_ERR("Could not load StrToIntA from comctl32.dll.\n");

        p_StrStrIW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(363));
        if (!p_StrStrIW)
            WINE_ERR("Could not load StrStrIW from comctl32.dll.\n");

        p_StrToIntW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(365));
        if (!p_StrToIntW)
            WINE_ERR("Could not load StrToIntW from comctl32.dll.\n");

        p_StrCSpnA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(356));
        if (!p_StrCSpnA)
            WINE_ERR("Could not load StrCSpnA from comctl32.dll.\n");

        p_StrChrW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(358));
        if (!p_StrChrW)
            WINE_ERR("Could not load StrChrW from comctl32.dll.\n");

        p_StrCmpNA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(352));
        if (!p_StrCmpNA)
            WINE_ERR("Could not load StrCmpNA from comctl32.dll.\n");

        p_StrCmpNW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(360));
        if (!p_StrCmpNW)
            WINE_ERR("Could not load StrCmpNW from comctl32.dll.\n");

        p_StrRChrA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(351));
        if (!p_StrRChrA)
            WINE_ERR("Could not load StrRChrA from comctl32.dll.\n");

        p_StrRChrW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(359));
        if (!p_StrRChrW)
            WINE_ERR("Could not load StrRChrW from comctl32.dll.\n");

        p_StrStrA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(354));
        if (!p_StrStrA)
            WINE_ERR("Could not load StrStrA from comctl32.dll.\n");

        p_StrStrW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(362));
        if (!p_StrStrW)
            WINE_ERR("Could not load StrStrW from comctl32.dll.\n");

        p_StrChrIA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(366));
        if (!p_StrChrIA)
            WINE_ERR("Could not load StrChrIA from comctl32.dll.\n");

        p_StrChrIW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(367));
        if (!p_StrChrIW)
            WINE_ERR("Could not load StrChrIW from comctl32.dll.\n");

        p_StrRStrIA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(372));
        if (!p_StrRStrIA)
            WINE_ERR("Could not load StrRStrIA from comctl32.dll.\n");

        p_StrRStrIW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(373));
        if (!p_StrRStrIW)
            WINE_ERR("Could not load StrRStrIW from comctl32.dll.\n");

        p_StrCSpnIA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(374));
        if (!p_StrCSpnIA)
            WINE_ERR("Could not load StrCSpnIA from comctl32.dll.\n");

        p_StrCSpnIW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(375));
        if (!p_StrCSpnIW)
            WINE_ERR("Could not load StrCSpnIW from comctl32.dll.\n");

        p_StrRChrIA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(368));
        if (!p_StrRChrIA)
            WINE_ERR("Could not load StrRChrIA from comctl32.dll.\n");

        p_StrRChrIW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(369));
        if (!p_StrRChrIW)
            WINE_ERR("Could not load StrRChrIW from comctl32.dll.\n");

        p_StrCSpnW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(364));
        if (!p_StrCSpnW)
            WINE_ERR("Could not load StrCSpnW from comctl32.dll.\n");

        p_IntlStrEqWorkerA = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(366));
        if (!p_IntlStrEqWorkerA)
            WINE_ERR("Could not load IntlStrEqWorkerA from comctl32.dll.\n");

        p_IntlStrEqWorkerW = (void *)GetProcAddress(comctl32, MAKEINTRESOURCE(367));
        if (!p_IntlStrEqWorkerW)
            WINE_ERR("Could not load IntlStrEqWorkerW from comctl32.dll.\n");

        p_TaskDialogIndirect = (void *)GetProcAddress(comctl32, "TaskDialogIndirect");
        if (!p_TaskDialogIndirect)
            WINE_ERR("Could not load TaskDialogIndirect from comctl32.dll.\n");

        p_TaskDialog = (void *)GetProcAddress(comctl32, "TaskDialog");
        if (!p_TaskDialog)
            WINE_ERR("Could not load TaskDialog from comctl32.dll.\n");
    }
    else
    {
        WINE_TRACE("Unloading comctl32\n");
        FreeLibrary(comctl32);
    }


    register_notify_callbacks();
}

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
    qemu_PropertySheet,
    qemu_PropertySheet,
    qemu_ReAlloc,
    qemu_RemoveWindowSubclass,
    qemu_SendNotify,
    qemu_SendNotifyEx,
    qemu_set_callbacks,
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

struct callback_entry_table *wndproc_wrappers;

/* FIXME: Taken from user32 for propsheet wrappers. De-duplicate this... */
LRESULT WINAPI wndproc_wrapper(HWND win, UINT msg, WPARAM wparam, LPARAM lparam, struct callback_entry *wrapper)
{
    struct wndproc_call stack_call, *call = &stack_call;
    LRESULT ret;
    LPARAM orig_param;
    PROPSHEETPAGEW *page;
    PROPSHEETPAGEW stack_copy, *page_copy = &stack_copy;

    WINE_TRACE("Processing meesage %x.\n", msg);

#if HOST_BIT != GUEST_BIT
    call = HeapAlloc(GetProcessHeap(), 0, sizeof(*call));
#endif

    call->wndproc = wrapper->guest_proc;
    call->win = (ULONG_PTR)win;
    call->msg = msg;
    call->wparam = wparam;
    call->lparam = lparam;

    /* FIXME: This currently assumes we're dealing with property sheet dialogs. If a different
     * control needs to run through this function store the control type in struct wndproc_wrapper */
    if (msg == WM_INITDIALOG)
    {
        struct page_data *page_data;
        page = (PROPSHEETPAGEW *)lparam;
        page_data = (struct page_data *)page->lParam;

#if HOST_BIT != GUEST_BIT
        page_copy = HeapAlloc(GetProcessHeap(), 0, sizeof(*page_copy));
#endif

        *page_copy = *page;
        orig_param = page_copy->lParam;
        page_copy->lParam = page_data->guest_lparam;
        call->lparam = QEMU_H2G(page_copy);
    }
#if HOST_BIT != GUEST_BIT
    else if (msg == WM_NCCREATE)
    {
        struct qemu_CREATESTRUCT *guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest));
        CREATESTRUCTW *host = (CREATESTRUCTW *)call->lparam;

        guest->lpCreateParams = (ULONG_PTR)host->lpCreateParams;
        guest->hInstance = (ULONG_PTR)host->hInstance;
        guest->hMenu = (ULONG_PTR)host->hMenu;
        guest->hwndParent = (ULONG_PTR)host->hwndParent;
        guest->cy = host->cy;
        guest->cx = host->cx;
        guest->y = host->y;
        guest->x = host->x;
        guest->style = host->style;
        guest->lpszName = (ULONG_PTR)host->lpszName;
        guest->lpszClass = (ULONG_PTR)host->lpszClass;
        guest->dwExStyle = host->dwExStyle;

        orig_param = call->lparam;
        call->lparam = (LPARAM)guest;
    }
    else if (msg == WM_NCCALCSIZE)
    {
        /* FIXME: This should not be necessary if we restriced the host stack to < 4 GB. */
        RECT *copy = HeapAlloc(GetProcessHeap(), 0, sizeof(*copy));
        *copy = *(RECT *)call->lparam;
        orig_param = call->lparam;
        call->lparam = (LPARAM)copy;
    }
    else if (msg == WM_WINDOWPOSCHANGING || msg == WM_WINDOWPOSCHANGED)
    {
        WINDOWPOS *host = (WINDOWPOS *)call->lparam;
        struct qemu_WINDOWPOS *guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*host));

        WINDOWPOS_h2g(guest, host);

        orig_param = call->lparam;
        call->lparam = (LPARAM)guest;
    }
    else if (msg == WM_NOTIFY)
    {
        orig_param = call->lparam;
        call->lparam = (LPARAM)propsheet_notify_h2g((NMHDR *)call->lparam);
    }
#endif

    WINE_TRACE("Calling guest wndproc 0x%lx(%p, %lx, %lx, %lx)\n", (unsigned long)wrapper->guest_proc,
            win, (unsigned long)call->msg, (unsigned long)call->wparam, (unsigned long)call->lparam);
    WINE_TRACE("wrapper at %p, param struct at %p\n", wrapper, call);

    ret = qemu_ops->qemu_execute(QEMU_G2H(guest_wndproc_wrapper), QEMU_H2G(call));

    WINE_TRACE("Guest returned %lu.\n", ret);

    if (msg == WM_INITDIALOG)
    {
        *page = *page_copy;
        page->lParam = orig_param;
    }
#if HOST_BIT != GUEST_BIT
    else if (msg == WM_NCCREATE)
    {
        HeapFree(GetProcessHeap(), 0, (void *)call->lparam);
    }
    else if (msg == WM_NCCALCSIZE)
    {
        /* FIXME: This should not be necessary if we restriced the host stack to < 4 GB. */
        *(RECT *)orig_param = *(RECT *)call->lparam;
        HeapFree(GetProcessHeap(), 0, (void *)call->lparam);
    }
    else if (msg == WM_WINDOWPOSCHANGING || msg == WM_WINDOWPOSCHANGED)
    {
        struct qemu_WINDOWPOS *guest = (struct qemu_WINDOWPOS *)call->lparam;
        WINDOWPOS *host = (WINDOWPOS *)orig_param;

        WINDOWPOS_g2h(host, guest);

        HeapFree(GetProcessHeap(), 0, (void *)call->lparam);
    }
    else if (msg == WM_NOTIFY)
    {
        propsheet_notify_g2h((NMHDR *)orig_param, (NMHDR *)call->lparam);
    }
#endif

    if (call != &stack_call)
        HeapFree(GetProcessHeap(), 0, call);
    if (page_copy != &stack_copy)
        HeapFree(GetProcessHeap(), 0, page_copy);

    return ret;
}

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    unsigned int i;

    WINE_TRACE("Loading host-side comctl32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    /* Comctl32 probably doesn't need as many wrappers as user32... */
    if (!callback_alloc_table(&wndproc_wrappers, 64, sizeof(struct callback_entry), wndproc_wrapper, 4))
    {
        WINE_ERR("Failed to allocate memory for class wndproc wrappers.\n");
        return NULL;
    }

    return dll_functions;
}

WNDPROC wndproc_guest_to_host(uint64_t guest_proc)
{
    unsigned int i;
    struct callback_entry *wrapper;
    BOOL is_new;

    /* Assume we never get a WNDPROC handle in comctl32. */
    if (!guest_proc)
        return (WNDPROC)guest_proc;

    wrapper = callback_get(wndproc_wrappers, guest_proc, &is_new);
    if (!wrapper)
    {
        WINE_FIXME("Out of guest -> host WNDPROC wrappers.\n");
        assert(0);
    }

    if (is_new)
    {
        WINE_TRACE("Creating host WNDPROC %p for guest func 0x%lx.\n",
                wrapper, (unsigned long)guest_proc);
    }

    return (WNDPROC)wrapper;
}

#endif
