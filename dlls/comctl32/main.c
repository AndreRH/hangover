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
    }
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comctl32);

const struct qemu_ops *qemu_ops;
static uint64_t guest_wndproc_wrapper;

static void qemu_set_callbacks(struct qemu_syscall *call)
{
    struct qemu_set_callbacks *c = (struct qemu_set_callbacks *)call;
    guest_wndproc_wrapper = c->wndproc_wrapper;
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

struct wndproc_wrapper *wndproc_wrappers;
unsigned int wndproc_wrapper_count;

/* FIXME: Taken from user32 for propsheet wrappers. De-duplicate this... */
LRESULT WINAPI wndproc_wrapper(HWND win, UINT msg, WPARAM wparam, LPARAM lparam, struct wndproc_wrapper *wrapper)
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

    WINE_TRACE("Calling guest wndproc 0x%lx(%p, %lx, %lx, %lx)\n", wrapper->guest_proc,
            win, call->msg, call->wparam, call->lparam);
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

static void init_wndproc(struct wndproc_wrapper *wrapper)
{
    size_t offset;

    offset = offsetof(struct wndproc_wrapper, selfptr) - offsetof(struct wndproc_wrapper, ldrx4);
    /* The load offset is stored in bits 5-24. The stored offset is left-shifted by 2 to generate the 21
     * bit real offset. So to place it in the right place we need our offset (multiple of 4, unless the
     * compiler screwed up terribly) shifted by another 3 bits. */
    wrapper->ldrx4 = 0x58000004 | (offset << 3); /* ldr x4, offset */

    offset = offsetof(struct wndproc_wrapper, host_proc) - offsetof(struct wndproc_wrapper, ldrx5);
    wrapper->ldrx5 = 0x58000005 | (offset << 3);   /* ldr x5, offset */

    wrapper->br = 0xd61f00a0; /* br x5 */

    wrapper->selfptr = wrapper;
    wrapper->host_proc = wndproc_wrapper;
    wrapper->guest_proc = 0;

    __clear_cache(&wrapper->ldrx4, &wrapper->br + 1);
}

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE comctl32;
    unsigned int i;

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

    /* Comctl32 probably doesn't need as many wrappers as user32... */
    wndproc_wrapper_count = 64;
    wndproc_wrappers = VirtualAlloc(NULL, sizeof(*wndproc_wrappers) * wndproc_wrapper_count,
            MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!wndproc_wrappers)
    {
        WINE_ERR("Failed to allocate memory for class wndproc wrappers.\n");
        return NULL;
    }

    for (i = 0; i < wndproc_wrapper_count; ++i)
        init_wndproc(&wndproc_wrappers[i]);

    hook_wndprocs();

    return dll_functions;
}

WNDPROC wndproc_guest_to_host(uint64_t guest_proc)
{
    unsigned int i;

    /* Assume we never get a WNDPROC handle in comctl32. */
    if (!guest_proc)
        return (WNDPROC)guest_proc;

    for (i = 0; i < wndproc_wrapper_count; i++)
    {
        if (wndproc_wrappers[i].guest_proc == guest_proc)
            return (WNDPROC)&wndproc_wrappers[i];
        if (!wndproc_wrappers[i].guest_proc)
        {
            WINE_TRACE("Creating host WNDPROC %p for guest func 0x%lx.\n",
                    &wndproc_wrappers[i], guest_proc);
            wndproc_wrappers[i].guest_proc = guest_proc;
            return (WNDPROC)&wndproc_wrappers[i];
        }
    }

    WINE_FIXME("Out of guest -> host WNDPROC wrappers.\n");
    assert(0);
}

#endif
