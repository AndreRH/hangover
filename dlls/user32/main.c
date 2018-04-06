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
#include <excpt.h>
#include <commctrl.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_commctrl.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_user32.h"

struct qemu_set_callbacks
{
    struct qemu_syscall super;
    uint64_t rev_wndproc_wrapper;
    uint64_t wndproc_wrapper;
    uint64_t guest_mod;
    uint64_t guest_win_event_wrapper;
    uint64_t LVM_SORTITEMS_guest_cb;
};

struct wndproc_call
{
    uint64_t wndproc;
    uint64_t win, msg, wparam, lparam;
};

struct LVM_SORTITEMS_cb_data
{
    uint64_t func;
    uint64_t p1, p2, param;
};

#ifdef QEMU_DLL_GUEST

long CALLBACK wndproc_except_handler(EXCEPTION_POINTERS *pointers, ULONG64 frame)
{
    return EXCEPTION_EXECUTE_HANDLER;
}

static LRESULT __fastcall wndproc_wrapper(const struct wndproc_call *call)
{
    WNDPROC proc = (WNDPROC)(ULONG_PTR)call->wndproc;
    LRESULT ret = 0;

    /* TODO: It would be nicer to re-throw the exception to the host so Wine can
     * decide what to do with it. See if the 'frame' parameter can be used to pass
     * a pointer to store exception info to the handler. */
    if (call->msg == WM_TIMER || call->msg == WM_SYSTIMER)
    {
        __try1(wndproc_except_handler)
        {
            ret = proc((HWND)(ULONG_PTR)call->win, call->msg, call->wparam, call->lparam);
        }
        __except1
        {
        }
    }
    else
    {
        ret = proc((HWND)(ULONG_PTR)call->win, call->msg, call->wparam, call->lparam);
    }

    return ret;
}

INT __fastcall LVM_SORTITEMS_guest_cb(void *data)
{
    struct LVM_SORTITEMS_cb_data *d = data;
    PFNLVCOMPARE func = (PFNLVCOMPARE)(ULONG_PTR)d->func;
    return func(d->p1, d->p2, d->param);
}

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_set_callbacks call;

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            call.super.id = QEMU_SYSCALL_ID(CALL_SET_CALLBACKS);
            call.rev_wndproc_wrapper = (ULONG_PTR)reverse_wndproc_func;
            call.wndproc_wrapper = (ULONG_PTR)wndproc_wrapper;
            call.guest_mod = (ULONG_PTR)mod;
            call.guest_win_event_wrapper = (ULONG_PTR)guest_win_event_wrapper;
            call.LVM_SORTITEMS_guest_cb = (ULONG_PTR)LVM_SORTITEMS_guest_cb;
            qemu_syscall(&call.super);
            break;
    }
    return TRUE;
}

#else

#include <wine/debug.h>
#include <wine/unicode.h>
#include <assert.h>

#include "callback_helper_impl.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_user32);

uint64_t reverse_wndproc_func;

#define REVERSE_WNDPROC_WRAPPER_COUNT 1024
static struct reverse_wndproc_wrapper *reverse_wndproc_wrappers;

void init_reverse_wndproc(struct reverse_wndproc_wrapper *wrapper)
{
    /* This is a bit more complicated than the ARM counterpart because we do not
     * have a spare argument in register to put our self pointer in. This means we
     * have to shuffle push the argument on the stack and do an actual call on top
     * of it, and then clean up the stack on return.
     *
     * The 64 bit code is generated from this C code:
     * LRESULT WINAPI wndproc(HWND wnd, UINT msg, WPARAM wp, LPARAM lp)
     * {
     *     LRESULT (* WINAPI wndproc2)(HWND wnd, UINT msg, WPARAM wp, LPARAM lp, void *extra);
     *     wndproc2 = *(void **)((ULONG_PTR)wndproc + 0x28);
     *     return wndproc2(wnd, msg, wp, lp, wndproc);
     * }
     *
     * For 32 I decided to put the absolute call address and the self pointer directly
     * into the code at runtime.
     **/
#if HOST_BIT == GUEST_BIT

static const char wrapper_code[] =
    {
        /* 27 bytes */
        0x48, 0x83, 0xec, 0x38,                     /* sub    $0x38,%rsp        - Reserve stack space   */
        0x48, 0x8d, 0x05, 0xf5, 0xff, 0xff, 0xff,   /* lea    -0xb(%rip),%rax   - Get self ptr          */
        0x48, 0x89, 0x44, 0x24, 0x20,               /* mov    %rax,0x20(%rsp)   - push self ptr         */
        0xff, 0x15, 0x0a, 0x00, 0x00, 0x00,         /* callq  *0xa(%rip)        - Call guest func       */
        0x48, 0x83, 0xc4, 0x38,                     /* add    $0x38,%rsp        - Clean up stack        */
        0xc3,                                       /* retq                     - return                */
    };

    memset(wrapper->code, 0xcc, sizeof(wrapper->code));
    memcpy(wrapper->code, wrapper_code, sizeof(wrapper_code));

#else

    /* FIXME: Where does this get the self ptr? */
    static const char wrapper_code[] =
    {
        0x83, 0xec, 0x2c,                               /* sub    $0x2c,%esp                            */
        0x8b, 0x44, 0x24, 0x3c,                         /* mov    0x3c(%esp),%eax                       */
        0xc7, 0x44, 0x24, 0x10, 0xef, 0xcd, 0xab, 0x89, /* movl   $0x89abcdef,0x10(%esp) selfptr        */
        0x89, 0x44, 0x24, 0x0c,                         /* mov    %eax,0xc(%esp)                        */
        0x8b, 0x44, 0x24, 0x38,                         /* mov    0x38(%esp),%eax                       */
        0x89, 0x44, 0x24, 0x08,                         /* mov    %eax,0x8(%esp)                        */
        0x8b, 0x44, 0x24, 0x34,                         /* mov    0x34(%esp),%eax                       */
        0x89, 0x44, 0x24, 0x04,                         /* mov    %eax,0x4(%esp)                        */
        0x8b, 0x44, 0x24, 0x30,                         /* mov    0x30(%esp),%eax                       */
        0x89, 0x04, 0x24,                               /* mov    %eax,(%esp)                           */
        0xb8, 0x78, 0x56, 0x34, 0x12,                   /* mov    $0x12345678,%eax - call address here  */
        0xff, 0xd0,                                     /* call   *%eax                                 */
        0x83, 0xec, 0x14,                               /* sub    $0x14,%esp                            */
        0x83, 0xc4, 0x2c,                               /* add    $0x2c,%esp                            */
        0xc2, 0x10, 0x00,                               /* ret    $0x10                                 */
    };

    memset(wrapper->code, 0xcc, sizeof(wrapper->code));
    memcpy(wrapper->code, wrapper_code, sizeof(wrapper_code));
    *(DWORD *)&wrapper->code[0x0b] = (ULONG_PTR)wrapper;
    *(DWORD *)&wrapper->code[0x2b] = reverse_wndproc_func;

#endif
}

static void qemu_set_callbacks(struct qemu_syscall *call)
{
    struct qemu_set_callbacks *c = (struct qemu_set_callbacks *)call;
    unsigned int i;

    reverse_wndproc_func = c->rev_wndproc_wrapper;
    guest_wndproc_wrapper = c->wndproc_wrapper;
    guest_mod = (HMODULE)c->guest_mod;
    guest_win_event_wrapper = c->guest_win_event_wrapper;
    LVM_SORTITEMS_guest_cb = c->LVM_SORTITEMS_guest_cb;

    /* This needs to be guest accessible, so delay allocation until the address space
     * is set up. */
    reverse_wndproc_wrappers = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
            sizeof(*reverse_wndproc_wrappers) * REVERSE_WNDPROC_WRAPPER_COUNT);
    for (i = 0; i < REVERSE_WNDPROC_WRAPPER_COUNT; ++i)
        init_reverse_wndproc(&reverse_wndproc_wrappers[i]);

}

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_ActivateKeyboardLayout,
    qemu_AddClipboardFormatListener,
    qemu_AdjustWindowRect,
    qemu_AdjustWindowRectEx,
    qemu_AlignRects,
    qemu_AllowSetForegroundWindow,
    qemu_AnimateWindow,
    qemu_AnyPopup,
    qemu_AppendMenuA,
    qemu_AppendMenuW,
    qemu_ArrangeIconicWindows,
    qemu_AttachThreadInput,
    qemu_BeginDeferWindowPos,
    qemu_BeginPaint,
    qemu_BlockInput,
    qemu_BringWindowToTop,
    qemu_BroadcastSystemMessageA,
    qemu_BroadcastSystemMessageExA,
    qemu_BroadcastSystemMessageExW,
    qemu_BroadcastSystemMessageW,
    qemu_CalcChildScroll,
    qemu_CalcMenuBar,
    qemu_call_wndproc,
    qemu_CallMsgFilterA,
    qemu_CallMsgFilterW,
    qemu_CallNextHookEx,
    qemu_CallWindowProcA,
    qemu_CallWindowProcW,
    qemu_CascadeChildWindows,
    qemu_CascadeWindows,
    qemu_ChangeClipboardChain,
    qemu_ChangeDisplaySettingsA,
    qemu_ChangeDisplaySettingsExA,
    qemu_ChangeDisplaySettingsExW,
    qemu_ChangeDisplaySettingsW,
    qemu_ChangeMenuA,
    qemu_ChangeMenuW,
    qemu_ChangeWindowMessageFilter,
    qemu_ChangeWindowMessageFilterEx,
    qemu_CharLowerA,
    qemu_CharLowerBuffA,
    qemu_CharLowerBuffW,
    qemu_CharLowerW,
    qemu_CharNextA,
    qemu_CharNextExA,
    qemu_CharNextExW,
    qemu_CharNextW,
    qemu_CharPrevA,
    qemu_CharPrevExA,
    qemu_CharPrevExW,
    qemu_CharPrevW,
    qemu_CharToOemA,
    qemu_CharToOemBuffA,
    qemu_CharToOemBuffW,
    qemu_CharToOemW,
    qemu_CharUpperA,
    qemu_CharUpperBuffA,
    qemu_CharUpperBuffW,
    qemu_CharUpperW,
    qemu_CheckDlgButton,
    qemu_CheckMenuItem,
    qemu_CheckMenuRadioItem,
    qemu_CheckRadioButton,
    qemu_ChildWindowFromPoint,
    qemu_ChildWindowFromPointEx,
    qemu_ClientToScreen,
    qemu_ClipCursor,
    qemu_CloseClipboard,
    qemu_CloseDesktop,
    qemu_CloseTouchInputHandle,
    qemu_CloseWindow,
    qemu_CloseWindowStation,
    qemu_CopyAcceleratorTableA,
    qemu_CopyAcceleratorTableW,
    qemu_CopyIcon,
    qemu_CopyImage,
    qemu_CopyRect,
    qemu_CountClipboardFormats,
    qemu_CreateAcceleratorTableA,
    qemu_CreateAcceleratorTableW,
    qemu_CreateCaret,
    qemu_CreateCursor,
    qemu_CreateDesktopA,
    qemu_CreateDesktopW,
    qemu_CreateDialogIndirectParamA,
    qemu_CreateDialogIndirectParamAorW,
    qemu_CreateDialogIndirectParamW,
    qemu_CreateDialogParamA,
    qemu_CreateDialogParamW,
    qemu_CreateIcon,
    qemu_CreateIconFromResource,
    qemu_CreateIconFromResourceEx,
    qemu_CreateIconIndirect,
    qemu_CreateMDIWindowA,
    qemu_CreateMDIWindowW,
    qemu_CreateMenu,
    qemu_CreatePopupMenu,
    qemu_CreateWindowExA,
    qemu_CreateWindowExW,
    qemu_CreateWindowStationA,
    qemu_CreateWindowStationW,
    qemu_DdeAbandonTransaction,
    qemu_DdeAccessData,
    qemu_DdeAddData,
    qemu_DdeClientTransaction,
    qemu_DdeCmpStringHandles,
    qemu_DdeConnect,
    qemu_DdeConnectList,
    qemu_DdeCreateDataHandle,
    qemu_DdeCreateStringHandleA,
    qemu_DdeCreateStringHandleW,
    qemu_DdeDisconnect,
    qemu_DdeDisconnectList,
    qemu_DdeEnableCallback,
    qemu_DdeFreeDataHandle,
    qemu_DdeFreeStringHandle,
    qemu_DdeGetData,
    qemu_DdeGetLastError,
    qemu_DdeImpersonateClient,
    qemu_DdeInitializeA,
    qemu_DdeInitializeW,
    qemu_DdeKeepStringHandle,
    qemu_DdeNameService,
    qemu_DdePostAdvise,
    qemu_DdeQueryConvInfo,
    qemu_DdeQueryNextServer,
    qemu_DdeQueryStringA,
    qemu_DdeQueryStringW,
    qemu_DdeReconnect,
    qemu_DdeSetQualityOfService,
    qemu_DdeSetUserHandle,
    qemu_DdeUnaccessData,
    qemu_DdeUninitialize,
    qemu_DefDlgProcA,
    qemu_DefDlgProcW,
    qemu_DeferWindowPos,
    qemu_DefFrameProcA,
    qemu_DefFrameProcW,
    qemu_DefMDIChildProcA,
    qemu_DefMDIChildProcW,
    qemu_DefRawInputProc,
    qemu_DefWindowProcA,
    qemu_DefWindowProcW,
    qemu_DeleteMenu,
    qemu_DeregisterShellHookWindow,
    qemu_DestroyAcceleratorTable,
    qemu_DestroyCaret,
    qemu_DestroyCursor,
    qemu_DestroyIcon,
    qemu_DestroyMenu,
    qemu_DestroyWindow,
    qemu_DialogBoxIndirectParam,
    qemu_DialogBoxIndirectParam,
    qemu_DialogBoxIndirectParamAorW,
    qemu_DialogBoxParam,
    qemu_DialogBoxParam,
    qemu_DisableProcessWindowsGhosting,
    qemu_DispatchMessageA,
    qemu_DispatchMessageW,
    qemu_DisplayConfigGetDeviceInfo,
    qemu_DlgDirListA,
    qemu_DlgDirListComboBoxA,
    qemu_DlgDirListComboBoxW,
    qemu_DlgDirListW,
    qemu_DlgDirSelectComboBoxExA,
    qemu_DlgDirSelectComboBoxExW,
    qemu_DlgDirSelectExA,
    qemu_DlgDirSelectExW,
    qemu_DragDetect,
    qemu_DrawAnimatedRects,
    qemu_DrawCaption,
    qemu_DrawCaptionTempA,
    qemu_DrawCaptionTempW,
    qemu_DrawEdge,
    qemu_DrawFocusRect,
    qemu_DrawFrameControl,
    qemu_DrawIcon,
    qemu_DrawIconEx,
    qemu_DrawMenuBar,
    qemu_DrawMenuBarTemp,
    qemu_DrawStateA,
    qemu_DrawStateW,
    qemu_DrawTextA,
    qemu_DrawTextExA,
    qemu_DrawTextExW,
    qemu_DrawTextW,
    qemu_EditWndProcA,
    qemu_EmptyClipboard,
    qemu_EnableMenuItem,
    qemu_EnableScrollBar,
    qemu_EnableWindow,
    qemu_EndDeferWindowPos,
    qemu_EndDialog,
    qemu_EndMenu,
    qemu_EndPaint,
    qemu_EnumChildWindows,
    qemu_EnumClipboardFormats,
    qemu_EnumDesktopsA,
    qemu_EnumDesktopsW,
    qemu_EnumDesktopWindows,
    qemu_EnumDisplayDevicesA,
    qemu_EnumDisplayDevicesW,
    qemu_EnumDisplayMonitors,
    qemu_EnumDisplaySettingsA,
    qemu_EnumDisplaySettingsExA,
    qemu_EnumDisplaySettingsExW,
    qemu_EnumDisplaySettingsW,
    qemu_EnumPropsA,
    qemu_EnumPropsExA,
    qemu_EnumPropsExW,
    qemu_EnumPropsW,
    qemu_EnumThreadWindows,
    qemu_EnumWindows,
    qemu_EnumWindowStationsA,
    qemu_EnumWindowStationsW,
    qemu_EqualRect,
    qemu_ExcludeUpdateRgn,
    qemu_ExitWindowsEx,
    qemu_FillRect,
    qemu_FindWindowA,
    qemu_FindWindowExA,
    qemu_FindWindowExW,
    qemu_FindWindowW,
    qemu_FlashWindow,
    qemu_FlashWindowEx,
    qemu_FrameRect,
    qemu_FreeDDElParam,
    qemu_GetActiveWindow,
    qemu_GetAltTabInfoA,
    qemu_GetAltTabInfoW,
    qemu_GetAncestor,
    qemu_GetAppCompatFlags,
    qemu_GetAppCompatFlags2,
    qemu_GetAsyncKeyState,
    qemu_GetAutoRotationState,
    qemu_GetCapture,
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
    qemu_GetClientRect,
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
    qemu_GetCursorInfo,
    qemu_GetCursorPos,
    qemu_GetDC,
    qemu_GetDCEx,
    qemu_GetDesktopWindow,
    qemu_GetDialogBaseUnits,
    qemu_GetDisplayAutoRotationPreferences,
    qemu_GetDisplayConfigBufferSizes,
    qemu_GetDlgCtrlID,
    qemu_GetDlgItem,
    qemu_GetDlgItemInt,
    qemu_GetDlgItemTextA,
    qemu_GetDlgItemTextW,
    qemu_GetDoubleClickTime,
    qemu_GetFocus,
    qemu_GetForegroundWindow,
    qemu_GetGestureConfig,
    qemu_GetGestureInfo,
    qemu_GetGuiResources,
    qemu_GetGUIThreadInfo,
    qemu_GetIconInfo,
    qemu_GetIconInfoExA,
    qemu_GetIconInfoExW,
    qemu_GetInputState,
    qemu_GetInternalWindowPos,
    qemu_GetKBCodePage,
    qemu_GetKeyboardLayout,
    qemu_GetKeyboardLayoutList,
    qemu_GetKeyboardLayoutNameA,
    qemu_GetKeyboardLayoutNameW,
    qemu_GetKeyboardState,
    qemu_GetKeyboardType,
    qemu_GetKeyNameTextA,
    qemu_GetKeyNameTextW,
    qemu_GetKeyState,
    qemu_GetLastActivePopup,
    qemu_GetLastInputInfo,
    qemu_GetLayeredWindowAttributes,
    qemu_GetListBoxInfo,
    qemu_GetMenu,
    qemu_GetMenuBarInfo,
    qemu_GetMenuCheckMarkDimensions,
    qemu_GetMenuContextHelpId,
    qemu_GetMenuDefaultItem,
    qemu_GetMenuInfo,
    qemu_GetMenuItemCount,
    qemu_GetMenuItemID,
    qemu_GetMenuItemInfoA,
    qemu_GetMenuItemInfoW,
    qemu_GetMenuItemRect,
    qemu_GetMenuState,
    qemu_GetMenuStringA,
    qemu_GetMenuStringW,
    qemu_GetMessageA,
    qemu_GetMessageExtraInfo,
    qemu_GetMessagePos,
    qemu_GetMessageTime,
    qemu_GetMessageW,
    qemu_GetMonitorInfoA,
    qemu_GetMonitorInfoW,
    qemu_GetMouseMovePointsEx,
    qemu_GetNextDlgGroupItem,
    qemu_GetNextDlgTabItem,
    qemu_GetOpenClipboardWindow,
    qemu_GetParent,
    qemu_GetPhysicalCursorPos,
    qemu_GetPriorityClipboardFormat,
    qemu_GetProcessDefaultLayout,
    qemu_GetProcessWindowStation,
    qemu_GetProgmanWindow,
    qemu_GetPropA,
    qemu_GetPropW,
    qemu_GetQueueStatus,
    qemu_GetRawInputBuffer,
    qemu_GetRawInputData,
    qemu_GetRawInputDeviceInfoA,
    qemu_GetRawInputDeviceInfoW,
    qemu_GetRawInputDeviceList,
    qemu_GetRegisteredRawInputDevices,
    qemu_GetScrollBarInfo,
    qemu_GetScrollInfo,
    qemu_GetScrollPos,
    qemu_GetScrollRange,
    qemu_GetShellWindow,
    qemu_GetSubMenu,
    qemu_GetSysColor,
    qemu_GetSysColorBrush,
    qemu_GetSystemMenu,
    qemu_GetSystemMetrics,
    qemu_GetTabbedTextExtentA,
    qemu_GetTabbedTextExtentW,
    qemu_GetTaskmanWindow,
    qemu_GetThreadDesktop,
    qemu_GetTitleBarInfo,
    qemu_GetTopWindow,
    qemu_GetTouchInputInfo,
    qemu_GetUpdatedClipboardFormats,
    qemu_GetUpdateRect,
    qemu_GetUpdateRgn,
    qemu_GetUserObjectInformationA,
    qemu_GetUserObjectInformationW,
    qemu_GetUserObjectSecurity,
    qemu_GetWindow,
    qemu_GetWindowContextHelpId,
    qemu_GetWindowDC,
    qemu_GetWindowInfo,
    qemu_GetWindowLongA,
    qemu_GetWindowLongPtrA,
    qemu_GetWindowLongPtrW,
    qemu_GetWindowLongW,
    qemu_GetWindowModuleFileNameA,
    qemu_GetWindowModuleFileNameW,
    qemu_GetWindowPlacement,
    qemu_GetWindowRect,
    qemu_GetWindowRgn,
    qemu_GetWindowRgnBox,
    qemu_GetWindowTextA,
    qemu_GetWindowTextLengthA,
    qemu_GetWindowTextLengthW,
    qemu_GetWindowTextW,
    qemu_GetWindowThreadProcessId,
    qemu_GetWindowWord,
    qemu_GrayStringA,
    qemu_GrayStringW,
    qemu_HideCaret,
    qemu_HiliteMenuItem,
    qemu_ImpersonateDdeClientWindow,
    qemu_InflateRect,
    qemu_InSendMessage,
    qemu_InSendMessageEx,
    qemu_InsertMenuA,
    qemu_InsertMenuItemA,
    qemu_InsertMenuItemW,
    qemu_InsertMenuW,
    qemu_InternalGetWindowText,
    qemu_IntersectRect,
    qemu_InvalidateRect,
    qemu_InvalidateRgn,
    qemu_InvertRect,
    qemu_IsCharAlphaA,
    qemu_IsCharAlphaNumericA,
    qemu_IsCharAlphaNumericW,
    qemu_IsCharAlphaW,
    qemu_IsCharLowerA,
    qemu_IsCharLowerW,
    qemu_IsCharUpperA,
    qemu_IsCharUpperW,
    qemu_IsChild,
    qemu_IsClipboardFormatAvailable,
    qemu_IsDialogMessageA,
    qemu_IsDialogMessageW,
    qemu_IsDlgButtonChecked,
    qemu_IsGUIThread,
    qemu_IsHungAppWindow,
    qemu_IsIconic,
    qemu_IsMenu,
    qemu_IsProcessDPIAware,
    qemu_IsRectEmpty,
    qemu_IsTouchWindow,
    qemu_IsWindow,
    qemu_IsWindowEnabled,
    qemu_IsWindowRedirectedForPrint,
    qemu_IsWindowUnicode,
    qemu_IsWindowVisible,
    qemu_IsWinEventHookInstalled,
    qemu_IsZoomed,
    qemu_keybd_event,
    qemu_KillSystemTimer,
    qemu_KillTimer,
    qemu_LoadAcceleratorsA,
    qemu_LoadAcceleratorsW,
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
    qemu_LoadKeyboardLayoutA,
    qemu_LoadKeyboardLayoutW,
    qemu_LoadLocalFonts,
    qemu_LoadMenuA,
    qemu_LoadMenuIndirectA,
    qemu_LoadMenuIndirectW,
    qemu_LoadMenuW,
    qemu_LoadStringA,
    qemu_LoadStringW,
    qemu_LockSetForegroundWindow,
    qemu_LockWindowUpdate,
    qemu_LockWorkStation,
    qemu_LogicalToPhysicalPoint,
    qemu_LookupIconIdFromDirectory,
    qemu_LookupIconIdFromDirectoryEx,
    qemu_MapDialogRect,
    qemu_MapVirtualKeyA,
    qemu_MapVirtualKeyExA,
    qemu_MapVirtualKeyExW,
    qemu_MapVirtualKeyW,
    qemu_MapWindowPoints,
    qemu_MenuItemFromPoint,
    qemu_MessageBeep,
    qemu_MessageBoxA,
    qemu_MessageBoxExA,
    qemu_MessageBoxExW,
    qemu_MessageBoxIndirectA,
    qemu_MessageBoxIndirectW,
    qemu_MessageBoxTimeoutA,
    qemu_MessageBoxTimeoutW,
    qemu_MessageBoxW,
    qemu_ModifyMenuA,
    qemu_ModifyMenuW,
    qemu_MonitorFromPoint,
    qemu_MonitorFromRect,
    qemu_MonitorFromWindow,
    qemu_mouse_event,
    qemu_MoveWindow,
    qemu_MsgWaitForMultipleObjects,
    qemu_MsgWaitForMultipleObjectsEx,
    qemu_NotifyWinEvent,
    qemu_OemKeyScan,
    qemu_OemToCharA,
    qemu_OemToCharBuffA,
    qemu_OemToCharBuffW,
    qemu_OemToCharW,
    qemu_OffsetRect,
    qemu_OpenClipboard,
    qemu_OpenDesktopA,
    qemu_OpenDesktopW,
    qemu_OpenIcon,
    qemu_OpenInputDesktop,
    qemu_OpenWindowStationA,
    qemu_OpenWindowStationW,
    qemu_PackDDElParam,
    qemu_PaintDesktop,
    qemu_PeekMessageA,
    qemu_PeekMessageW,
    qemu_PhysicalToLogicalPoint,
    qemu_PostMessageA,
    qemu_PostMessageW,
    qemu_PostQuitMessage,
    qemu_PostThreadMessageA,
    qemu_PostThreadMessageW,
    qemu_PrintWindow,
    qemu_PrivateExtractIconExA,
    qemu_PrivateExtractIconExW,
    qemu_PrivateExtractIconsA,
    qemu_PrivateExtractIconsW,
    qemu_PtInRect,
    qemu_QueryDisplayConfig,
    qemu_RealChildWindowFromPoint,
    qemu_RealGetWindowClassA,
    qemu_RealGetWindowClassW,
    qemu_RedrawWindow,
    qemu_RegisterClassEx,
    qemu_RegisterClassEx,
    qemu_RegisterClipboardFormatA,
    qemu_RegisterClipboardFormatW,
    qemu_RegisterDeviceNotificationA,
    qemu_RegisterDeviceNotificationW,
    qemu_RegisterHotKey,
    qemu_RegisterLogonProcess,
    qemu_RegisterPowerSettingNotification,
    qemu_RegisterRawInputDevices,
    qemu_RegisterServicesProcess,
    qemu_RegisterShellHookWindow,
    qemu_RegisterSystemThread,
    qemu_RegisterTasklist,
    qemu_RegisterTouchWindow,
    qemu_RegisterWindowMessageA,
    qemu_RegisterWindowMessageW,
    qemu_ReleaseCapture,
    qemu_ReleaseDC,
    qemu_RemoveClipboardFormatListener,
    qemu_RemoveMenu,
    qemu_RemovePropA,
    qemu_RemovePropW,
    qemu_ReplyMessage,
    qemu_ReuseDDElParam,
    qemu_ScreenToClient,
    qemu_ScrollChildren,
    qemu_ScrollDC,
    qemu_ScrollWindow,
    qemu_ScrollWindowEx,
    qemu_SendDlgItemMessageA,
    qemu_SendDlgItemMessageW,
    qemu_SendIMEMessageExA,
    qemu_SendIMEMessageExW,
    qemu_SendInput,
    qemu_SendMessageA,
    qemu_SendMessageCallback,
    qemu_SendMessageCallback,
    qemu_SendMessageTimeoutA,
    qemu_SendMessageTimeoutW,
    qemu_SendMessageW,
    qemu_SendNotifyMessageA,
    qemu_SendNotifyMessageW,
    qemu_set_callbacks,
    qemu_SetActiveWindow,
    qemu_SetCapture,
    qemu_SetCaretBlinkTime,
    qemu_SetCaretPos,
    qemu_SetClassLongA,
    qemu_SetClassLongPtrA,
    qemu_SetClassLongPtrW,
    qemu_SetClassLongW,
    qemu_SetClassWord,
    qemu_SetClipboardData,
    qemu_SetClipboardViewer,
    qemu_SetCoalescableTimer,
    qemu_SetCursor,
    qemu_SetCursorPos,
    qemu_SetDebugErrorLevel,
    qemu_SetDeskWallPaper,
    qemu_SetDlgItemInt,
    qemu_SetDlgItemTextA,
    qemu_SetDlgItemTextW,
    qemu_SetDoubleClickTime,
    qemu_SetFocus,
    qemu_SetForegroundWindow,
    qemu_SetGestureConfig,
    qemu_SetInternalWindowPos,
    qemu_SetKeyboardState,
    qemu_SetLastErrorEx,
    qemu_SetLayeredWindowAttributes,
    qemu_SetLogonNotifyWindow,
    qemu_SetMenu,
    qemu_SetMenuContextHelpId,
    qemu_SetMenuDefaultItem,
    qemu_SetMenuInfo,
    qemu_SetMenuItemBitmaps,
    qemu_SetMenuItemInfoA,
    qemu_SetMenuItemInfoW,
    qemu_SetMessageExtraInfo,
    qemu_SetMessageQueue,
    qemu_SetParent,
    qemu_SetPhysicalCursorPos,
    qemu_SetProcessDefaultLayout,
    qemu_SetProcessDPIAware,
    qemu_SetProcessWindowStation,
    qemu_SetProgmanWindow,
    qemu_SetPropA,
    qemu_SetPropW,
    qemu_SetRect,
    qemu_SetRectEmpty,
    qemu_SetScrollInfo,
    qemu_SetScrollPos,
    qemu_SetScrollRange,
    qemu_SetShellWindow,
    qemu_SetShellWindowEx,
    qemu_SetSysColors,
    qemu_SetSysColorsTemp,
    qemu_SetSystemCursor,
    qemu_SetSystemMenu,
    qemu_SetSystemTimer,
    qemu_SetTaskmanWindow,
    qemu_SetThreadDesktop,
    qemu_SetTimer,
    qemu_SetUserObjectInformationA,
    qemu_SetUserObjectInformationW,
    qemu_SetUserObjectSecurity,
    qemu_SetWindowContextHelpId,
    qemu_SetWindowLongA,
    qemu_SetWindowLongPtrA,
    qemu_SetWindowLongPtrW,
    qemu_SetWindowLongW,
    qemu_SetWindowPlacement,
    qemu_SetWindowPos,
    qemu_SetWindowRgn,
    qemu_SetWindowsHookA,
    qemu_SetWindowsHookExA,
    qemu_SetWindowsHookExW,
    qemu_SetWindowsHookW,
    qemu_SetWindowStationUser,
    qemu_SetWindowTextA,
    qemu_SetWindowTextW,
    qemu_SetWindowWord,
    qemu_SetWinEventHook,
    qemu_ShowCaret,
    qemu_ShowCursor,
    qemu_ShowOwnedPopups,
    qemu_ShowScrollBar,
    qemu_ShowWindow,
    qemu_ShowWindowAsync,
    qemu_ShutdownBlockReasonCreate,
    qemu_ShutdownBlockReasonDestroy,
    qemu_SubtractRect,
    qemu_SwapMouseButton,
    qemu_SwitchDesktop,
    qemu_SwitchToThisWindow,
    qemu_SystemParametersInfo,
    qemu_SystemParametersInfo,
    qemu_TabbedTextOutA,
    qemu_TabbedTextOutW,
    qemu_TileChildWindows,
    qemu_TileWindows,
    qemu_ToAscii,
    qemu_ToAsciiEx,
    qemu_ToUnicode,
    qemu_ToUnicodeEx,
    qemu_TrackMouseEvent,
    qemu_TrackPopupMenu,
    qemu_TrackPopupMenuEx,
    qemu_TranslateAcceleratorA,
    qemu_TranslateAcceleratorW,
    qemu_TranslateMDISysAccel,
    qemu_TranslateMessage,
    qemu_UnhookWindowsHook,
    qemu_UnhookWindowsHookEx,
    qemu_UnhookWinEvent,
    qemu_UnionRect,
    qemu_UnloadKeyboardLayout,
    qemu_UnpackDDElParam,
    qemu_UnregisterClass,
    qemu_UnregisterClass,
    qemu_UnregisterDeviceNotification,
    qemu_UnregisterHotKey,
    qemu_UnregisterPowerSettingNotification,
    qemu_UnregisterTouchWindow,
    qemu_UpdateLayeredWindow,
    qemu_UpdateLayeredWindowIndirect,
    qemu_UpdateWindow,
    qemu_User32InitializeImmEntryTable,
    qemu_UserHandleGrantAccess,
    qemu_UserRealizePalette,
    qemu_UserRegisterWowHandlers,
    qemu_UserSignalProc,
    qemu_ValidateRect,
    qemu_ValidateRgn,
    qemu_VkKeyScanA,
    qemu_VkKeyScanExA,
    qemu_VkKeyScanExW,
    qemu_VkKeyScanW,
    qemu_WaitForInputIdle,
    qemu_WaitMessage,
    qemu_WindowFromDC,
    qemu_WindowFromPoint,
    qemu_WinHelpA,
    qemu_WinHelpW,
    qemu_WINNLSEnableIME,
    qemu_WINNLSGetEnableStatus,
    qemu_WINNLSGetIMEHotkey,
};

struct callback_entry_table *wndproc_wrappers;
unsigned int wndproc_wrapper_count;
uint64_t guest_wndproc_wrapper;

LRESULT WINAPI wndproc_wrapper(HWND win, UINT msg, WPARAM wparam, LPARAM lparam, struct callback_entry *wrapper)
{
    struct wndproc_call stack_call, *call = &stack_call;
    MSG msg_struct = {win, msg, wparam, lparam}, msg_conv;
    LRESULT ret;

    /* When the WM_TIMER callback is actually invoked by DispatchMessage, the lparam callback pointer is
     * replaced with the value of GetTickCount(). Do not translate it. */
    if (msg == WM_TIMER || msg == WM_SYSTIMER)
        msg_conv = msg_struct;
    else
        msg_host_to_guest(&msg_conv, &msg_struct);

#if HOST_BIT != GUEST_BIT
    call = HeapAlloc(GetProcessHeap(), 0, sizeof(*call));
#endif

    call->wndproc = wrapper->guest_proc;
    call->win = (ULONG_PTR)msg_conv.hwnd;
    call->msg = msg_conv.message;
    call->wparam = msg_conv.wParam;
    call->lparam = msg_conv.lParam;

    WINE_TRACE("Calling guest wndproc 0x%lx(%p, 0x%x, 0x%lx, 0x%lx)\n", (unsigned long)wrapper->guest_proc,
            msg_conv.hwnd, msg_conv.message, msg_conv.wParam, msg_conv.lParam);
    WINE_TRACE("wrapper at %p, param struct at %p\n", wrapper, call);

    ret = qemu_ops->qemu_execute(QEMU_G2H(guest_wndproc_wrapper), QEMU_H2G(call));

    WINE_TRACE("Guest returned %lx.\n", ret);

    msg_host_to_guest_return(&msg_struct, &msg_conv);
    if (call != &stack_call)
        HeapFree(GetProcessHeap(), 0, call);

    return ret;
}

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    unsigned int i;
    LRESULT ret;

    WINE_TRACE("Loading host-side user32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    /* Wine has 16384 WNDPROC slots and if those are full it falls back to calling the
     * function pointer directly. The tests exercise the fallback code, so allocate more
     * slots than Wine has handles.
     *
     * WNDPROC wrappers are never freed, just as WNDPROC handles are never freed. The
     * basic idea is that an application may create and destroy many Windows, but it won't
     * have an infinite supply of code to use as possible WNDPROCs. WNDPROC handles are
     * expected to be valid after the Window that 'created' them was destroyed.
     *
     * This array uses 800 kilobytes of memory :-\ . */
    wndproc_wrapper_count = 20 * 1024;
    if (!callback_alloc_table(&wndproc_wrappers, 20 * 1024, sizeof(struct callback_entry),
            wndproc_wrapper, 4))
    {
        WINE_ERR("Failed to allocate memory for class wndproc wrappers.\n");
        return NULL;
    }

    user32_tls = TlsAlloc();
    if (user32_tls == TLS_OUT_OF_INDEXES)
        WINE_ERR("Out of TLS indices\n");

    return dll_functions;
}

WNDPROC wndproc_guest_to_host(uint64_t guest_proc)
{
    unsigned int i;
    struct callback_entry *entry;
    BOOL is_new;

    if (!guest_proc || wndproc_is_handle(guest_proc))
        return (WNDPROC)guest_proc;

    if (guest_proc >= (ULONG_PTR)&reverse_wndproc_wrappers[0]
            && guest_proc <= (ULONG_PTR)&reverse_wndproc_wrappers[REVERSE_WNDPROC_WRAPPER_COUNT])
    {
        struct reverse_wndproc_wrapper *rev_wrapper = (struct reverse_wndproc_wrapper *)guest_proc;

        WINE_TRACE("Guest passed in reverse wrapper %p, returning host function %p.\n",
                rev_wrapper, rev_wrapper->host_proc);
        return rev_wrapper->host_proc;
    }

    entry = callback_get(wndproc_wrappers, guest_proc, &is_new);
    if (!entry)
    {
        WINE_FIXME("Out of guest -> host WNDPROC wrappers.\n");
        assert(0);
    }
    if (is_new)
    {
        WINE_TRACE("Creating host WNDPROC %p for guest func 0x%lx.\n",
                entry, (unsigned long)guest_proc);
    }
    return (WNDPROC)entry;
}

uint64_t wndproc_host_to_guest(WNDPROC host_proc)
{
    unsigned int i;

    if (!host_proc || wndproc_is_handle((ULONG_PTR)host_proc))
        return (ULONG_PTR)host_proc;

    if (callback_is_in_table(wndproc_wrappers, (struct callback_entry *)host_proc))
    {
        uint64_t ret = callback_get_guest_proc((struct callback_entry *)host_proc);
        WINE_TRACE("Host wndproc %p is a wrapper function. Returning guest wndproc 0x%lx.\n",
                host_proc, (unsigned long)ret);
        return ret;
    }

    for (i = 0; i < REVERSE_WNDPROC_WRAPPER_COUNT; ++i)
    {
        if (reverse_wndproc_wrappers[i].host_proc == host_proc)
        {
            return QEMU_H2G(&reverse_wndproc_wrappers[i]);
        }
        if (!reverse_wndproc_wrappers[i].host_proc)
        {
            WINE_TRACE("Allocated reverse WNDPROC wrapper %p for host func %p, index %u.\n",
                    &reverse_wndproc_wrappers[i], host_proc, i);
            reverse_wndproc_wrappers[i].host_proc = host_proc;
            reverse_wndproc_wrappers[i].guest_proc = reverse_wndproc_func;
            return QEMU_H2G(&reverse_wndproc_wrappers[i]);
        }
    }

    /* Out of reverse wrappers. */
    assert(0);
}

uint64_t LVM_SORTITEMS_guest_cb;

static INT CALLBACK LVM_SORTITEMS_host_cb(LPARAM first, LPARAM second, LPARAM lParam)
{
    struct LVM_SORTITEMS_cb_data call;
    uint64_t *guest_func = TlsGetValue(user32_tls);
    INT ret;

    call.func = *guest_func;
    call.p1 = first;
    call.p2 = second;
    call.param = lParam;

    WINE_TRACE("Calling guest callback %p(%p, %p, %p).\n", (void *)call.func, (void *)call.p1,
            (void *)call.p2, (void *)call.param);
    ret = qemu_ops->qemu_execute(QEMU_G2H(LVM_SORTITEMS_guest_cb), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned %d.\n", ret);

    return ret;
}

uint64_t *LVM_SORTITEMS_old_tls;

void msg_guest_to_host(MSG *msg_out, const MSG *msg_in)
{
    *msg_out = *msg_in;
    WCHAR class[256];
    int len, count;

    switch (msg_in->message)
    {
        case WM_NULL:
            break;

        case WM_TIMER:
        case WM_SYSTIMER:
            msg_out->lParam = (LPARAM)wndproc_guest_to_host(msg_in->lParam);
            break;

        case LVM_SORTITEMS:
        case LVM_SORTITEMSEX:
        {
            WINE_TRACE("Wrapping callback of LVM_SORTITEMS.\n");
            LVM_SORTITEMS_old_tls = TlsGetValue(user32_tls);
#if HOST_BIT == GUEST_BIT
            if (msg_in->lParam == (uint64_t)LVM_SORTITEMS_host_cb)
#else
            if ((msg_in->lParam & ~0U) == (((uint64_t)LVM_SORTITEMS_host_cb) & ~0U))
#endif
            {
                WINE_ERR("Found my own callback. Subclassing gone bad?\n");
            }
            TlsSetValue(user32_tls, (uint64_t *)&msg_in->lParam);
            msg_out->lParam = (LPARAM)LVM_SORTITEMS_host_cb;
            break;
        }

#if HOST_BIT != GUEST_BIT
        case WM_CREATE:
        case WM_NCCREATE:
        {
            struct qemu_CREATESTRUCT *guest = (struct qemu_CREATESTRUCT *)msg_in->lParam;
            CREATESTRUCTW *host = HeapAlloc(GetProcessHeap(), 0, sizeof(*host));

            CREATESTRUCT_g2h(host, guest);

            if (host->dwExStyle & WS_EX_MDICHILD)
            {
                struct qemu_MDICREATESTRUCT *guest_mdi = host->lpCreateParams;
                MDICREATESTRUCTW *host_mdi = HeapAlloc(GetProcessHeap(), 0, sizeof(*host_mdi));
                MDICREATESTRUCT_g2h(host_mdi, guest_mdi);
                host->lpCreateParams = host_mdi;
            }

            msg_out->lParam = (LPARAM)host;
            break;
        }

        case WM_MDICREATE:
        {
            struct qemu_MDICREATESTRUCT *guest_mdi = (struct qemu_MDICREATESTRUCT *)msg_in->lParam;
            MDICREATESTRUCTW *host_mdi = HeapAlloc(GetProcessHeap(), 0, sizeof(*host_mdi));
            MDICREATESTRUCT_g2h(host_mdi, guest_mdi);
            msg_out->lParam = (LPARAM)host_mdi;
            break;
        }

        case WM_WINDOWPOSCHANGING:
        case WM_WINDOWPOSCHANGED:
        {
            struct qemu_WINDOWPOS *guest = (struct qemu_WINDOWPOS *)msg_in->lParam;
            WINDOWPOS *host = HeapAlloc(GetProcessHeap(), 0, sizeof(*host));
            WINDOWPOS_g2h(host, guest);
            msg_out->lParam = (LPARAM)host;
            break;
        }

        case WM_DRAWITEM:
        {
            struct qemu_DRAWITEMSTRUCT *guest = (struct qemu_DRAWITEMSTRUCT *)msg_in->lParam;
            DRAWITEMSTRUCT *host = HeapAlloc(GetProcessHeap(), 0, sizeof(*host));
            DRAWITEMSTRUCT_g2h(host, guest);
            msg_out->lParam = (LPARAM)host;
            break;
        }

        case WM_COMPAREITEM:
        {
            struct qemu_COMPAREITEMSTRUCT *guest = (struct qemu_COMPAREITEMSTRUCT *)msg_in->lParam;
            COMPAREITEMSTRUCT *host = HeapAlloc(GetProcessHeap(), 0, sizeof(*host));
            COMPAREITEMSTRUCT_g2h(host, guest);
            msg_out->lParam = (LPARAM)host;
            break;
        }

        case WM_STYLECHANGING:
        case WM_STYLECHANGED:
            /* The generic code expanded the (most likely) negative numbers wrong. Fix it up!. */
            msg_out->wParam = (LONG)msg_in->wParam;
            break;

        case WM_NOTIFY:
        {
            /* We do not want to convert NMHDRs in general. The guest controls will send WM_NOTIFY messages
             * between each other. If we don't touch them here, the host->guest code won't recognize the
             * notify code and not touch them.
             *
             * Keep in mind that all messages go through the host because the guest side doesn't know how
             * to route them. Also beware of subclassing... */
            len = GetClassNameW(msg_in->hwnd, class, sizeof(class) / sizeof(*class));
            if (len < 0 || len == 256)
                break;

            /* As soon as a second class is added add callbacks similarly to the host->guest case... */
            if (!strcmpW(class, WC_LISTVIEWW))
            {
                struct qemu_NMHEADER *guest = (struct qemu_NMHEADER *)msg_in->lParam;
                NMHEADERW *host = HeapAlloc(GetProcessHeap(), 0, sizeof(*host));
                NMHEADER_g2h(host, guest);
                msg_out->lParam = (LPARAM)host;
            }
            break;
        }

        case CB_GETCOMBOBOXINFO:
        {
            struct qemu_COMBOBOXINFO *guest = (struct qemu_COMBOBOXINFO *)msg_in->lParam;
            COMBOBOXINFO *host = HeapAlloc(GetProcessHeap(), 0, sizeof(*host));
            COMBOBOXINFO_g2h(host, guest);
            msg_out->lParam = (LPARAM)host;
            break;
        }

        /* If a message can come from the guest or the host user32 has to translate it
         * when it is passed out of the VM. Otherwise other DLLs translate it before it reaches
         * the original WNDPROC. */
        case WM_USER+19:
            /* Possible TB_ADDBITMAP */
            len = GetClassNameW(msg_in->hwnd, class, sizeof(class) / sizeof(*class));
            if (len < 0 || len == 256)
                break;

            if (!strcmpW(class, TOOLBARCLASSNAMEW))
            {
                struct qemu_TBADDBITMAP *guest_ab;
                TBADDBITMAP *host_ab;
                WINE_TRACE("Translating TB_ADDBITMAP message.\n");

                guest_ab = (struct qemu_TBADDBITMAP *)msg_in->lParam;
                host_ab = HeapAlloc(GetProcessHeap(), 0, sizeof(*host_ab));
                TBADDBITMAP_g2h(host_ab, guest_ab);
                msg_out->lParam = (LPARAM)host_ab;
            }
            break;

        case WM_USER+20: /* Possible TB_ADDBUTTONSA */
        case WM_USER+21: /* Possible TB_INSERTBUTTONA */
        case WM_USER+23: /* Possible TB_GETBUTTON */
        case WM_USER+68: /* Possible TB_ADDBUTTONSW */

            len = GetClassNameW(msg_in->hwnd, class, sizeof(class) / sizeof(*class));
            if (len < 0 || len == 256)
                break;

            msg_out->wParam = (LONG)msg_in->wParam;
            if (msg_in->message == TB_ADDBUTTONSA || msg_in->message == TB_ADDBUTTONSW)
                count = msg_out->wParam;
            else
                count = 1;

            if (!strcmpW(class, TOOLBARCLASSNAMEW))
            {
                struct qemu_TBBUTTON *guest_button;
                TBBUTTON *host_button;
                WINE_TRACE("Translating TB_ADDBUTTONS message, %d buttons at %p.\n",
                        count, (void *)msg_in->lParam);

                guest_button = (struct qemu_TBBUTTON *)msg_in->lParam;
                host_button = HeapAlloc(GetProcessHeap(), 0, sizeof(*host_button) * count);
                for (len = 0; len < count; ++len)
                    TBBUTTON_g2h(&host_button[len], &guest_button[len]);
                msg_out->lParam = (LPARAM)host_button;
            }
            break;

        case WM_USER+26: /* Possible TB_SAVERESTOREA */
        case WM_USER+76: /* Possible TB_SAVERESTOREW*/
            len = GetClassNameW(msg_in->hwnd, class, sizeof(class) / sizeof(*class));
            if (len < 0 || len == 256)
                break;

            if (!strcmpW(class, TOOLBARCLASSNAMEW))
            {
                struct qemu_TBSAVEPARAMS *guest_save;
                TBSAVEPARAMSW *host_save;
                WINE_TRACE("Translating TB_SAVERESTORE message, info at %p.\n",
                        (void *)msg_in->lParam);

                guest_save = (struct qemu_TBSAVEPARAMS *)msg_in->lParam;
                host_save = HeapAlloc(GetProcessHeap(), 0, sizeof(*host_save));
                TBSAVEPARAMS_g2h(host_save, guest_save);
                msg_out->lParam = (LPARAM)host_save;
            }
            break;

        case WM_USER+63: /* Possible TB_GETBUTTONINFOW */
        case WM_USER+64: /* Possible TB_SETBUTTONINFO */
        case WM_USER+65: /* Possible TB_GETBUTTONINFOA */
        case WM_USER+66:
            len = GetClassNameW(msg_in->hwnd, class, sizeof(class) / sizeof(*class));
            if (len < 0 || len == 256)
                break;

            if (!strcmpW(class, TOOLBARCLASSNAMEW))
            {
                struct qemu_TBBUTTONINFO *guest_info;
                TBBUTTONINFOW *host_info;
                WINE_TRACE("Translating TB_SETBUTTONINFO message, info at %p.\n",
                        (void *)msg_in->lParam);

                guest_info = (struct qemu_TBBUTTONINFO *)msg_in->lParam;
                host_info = HeapAlloc(GetProcessHeap(), 0, sizeof(*host_info));
                if (guest_info->cbSize == sizeof(*guest_info))
                    TBBUTTONINFO_g2h(host_info, guest_info);
                else
                    host_info->cbSize = 0;
                msg_out->lParam = (LPARAM)host_info;
            }
            break;

        case TCM_GETITEMA:
        case TCM_GETITEMW:
        case TCM_SETITEMA:
        case TCM_SETITEMW:
        case TCM_INSERTITEMA:
        case TCM_INSERTITEMW:
        {
            struct qemu_TCITEM *guest_item = (struct qemu_TCITEM *)msg_in->lParam;
            struct
            {
                TCITEMW item;
                DWORD pad; /* See TCM_SETITEMEXTRA. */
            } *host_item;
            WINE_TRACE("Translating TCM_*ITEM message at %p.\n", guest_item);
            host_item = HeapAlloc(GetProcessHeap(), 0, sizeof(*host_item));
            TCITEM_g2h(&host_item->item, guest_item);
            msg_out->lParam = (LPARAM)host_item;
            break;
        }

        case TCM_SETITEMEXTRA:
        {
            /* The handling of DRAWITEMSTRUCT.itemData differs betweeen a data size that fits in an LPARAM
             * and a data size that does not. If the data does not fit, comctl32 will store a pointer to the
             * data in itemData. Otherwise, it will store the data itself.
             *
             * If we are in this range (I am looking at you, comctl32/tab.c test) increase the size to trigger
             * the > 4 byte behavior the 32 bit app expects. Pad the struct allocation in TCM_*ITEM to make sure
             * comctl32 can read the extra padding.
             *
             * Still this feels rather nasty and it might break, so write a FIXME. */
            if (msg_in->wParam > sizeof(qemu_ptr) && msg_in->wParam <= sizeof(void *))
            {
                WINE_FIXME("Extra data size is %ld bytes, cheating...\n", msg_in->wParam);
                msg_out->wParam = sizeof(void *) + 1;
            }
            else if(msg_in->wParam > sizeof(void *))
            {
                /* The TCM_*ITEM wrapper code above has no idea about the size we're setting here, so it cannot
                 * allocate the right amount of data and copy it from the guest struct to the host struct. If
                 * we need to support this we either need to find a way to store this info in the tab control
                 * itself (e.g. by having a wrapper extra data struct) or store the property in an external
                 * table.
                 *
                 * A wrapper struct sounds nice, but WM_DRAWITEM will have to find out if the msg was sent by
                 * a tab control or not. Or all WM_DRAWITEM senders need a wrapper. */
                WINE_FIXME("Extra data size is %ld bytes, this will not work right.\n", msg_in->wParam);
            }
            break;
        }

        case LVM_SETITEMSTATE:
        case LVM_SETITEMA:
        case LVM_SETITEMW:
        case LVM_GETITEMA:
        case LVM_GETITEMW:
        case LVM_INSERTITEMA:
        case LVM_INSERTITEMW:
        case LVM_SETITEMTEXTA:
        case LVM_SETITEMTEXTW:
        case LVM_GETITEMTEXTA:
        case LVM_GETITEMTEXTW:
            if (msg_in->lParam)
            {
                struct qemu_LVITEM *guest_item = (struct qemu_LVITEM *)msg_in->lParam;
                LVITEMW *host_item;
                WINE_TRACE("Translating LVM_*ITEM message at %p.\n", guest_item);
                host_item = HeapAlloc(GetProcessHeap(), 0, sizeof(*host_item));
                LVITEM_g2h(host_item, guest_item);
                msg_out->lParam = (LPARAM)host_item;
            }
            break;

        case LVM_INSERTCOLUMNA:
        case LVM_INSERTCOLUMNW:
        case LVM_GETCOLUMNA:
        case LVM_GETCOLUMNW:
        case LVM_SETCOLUMNA:
        case LVM_SETCOLUMNW:
            if (msg_in->lParam)
            {
                struct qemu_LVCOLUMN *guest_item = (struct qemu_LVCOLUMN *)msg_in->lParam;
                LVCOLUMNW *host_item;
                WINE_TRACE("Translating LVM_*COLUMN message at %p.\n", guest_item);
                host_item = HeapAlloc(GetProcessHeap(), 0, sizeof(*host_item));
                LVCOLUMN_g2h(host_item, guest_item);
                msg_out->lParam = (LPARAM)host_item;
            }
            break;

        case LVM_FINDITEMA:
        case LVM_FINDITEMW:
            if (msg_in->lParam)
            {
                struct qemu_LVFINDINFO *guest_item = (struct qemu_LVFINDINFO *)msg_in->lParam;
                LVFINDINFOW *host_item;
                WINE_TRACE("Translating LVM_FINDITEM message at %p.\n", guest_item);
                host_item = HeapAlloc(GetProcessHeap(), 0, sizeof(*host_item));
                LVFINDINFO_g2h(host_item, guest_item);
                msg_out->lParam = (LPARAM)host_item;
            }
            break;

        case LVM_SETICONSPACING:
            /* The generic code expanded the (most likely) negative numbers wrong. Fix it up!. */
            msg_out->lParam = (LONG)msg_in->lParam;
            break;

        case HDM_LAYOUT:
            if (msg_in->lParam)
            {
                struct qemu_HD_LAYOUT *guest_item = (struct qemu_HD_LAYOUT *)msg_in->lParam;
                struct
                {
                    HD_LAYOUT layout;
                    WINDOWPOS wp;
                } *host;
                WINE_TRACE("Translating HDM_LAYOUT message at %p.\n", guest_item);
                host = HeapAlloc(GetProcessHeap(), 0, sizeof(*host));
                HD_LAYOUT_g2h(&host->layout, &host->wp, guest_item);
                msg_out->lParam = (LPARAM)host;
            }
            break;

        case HDM_INSERTITEMA:
        case HDM_INSERTITEMW:
        case HDM_GETITEMA:
        case HDM_GETITEMW:
        case HDM_SETITEMA:
        case HDM_SETITEMW:
            if (msg_in->lParam)
            {
                struct qemu_HDITEM *guest_item = (struct qemu_HDITEM *)msg_in->lParam;
                HDITEMW *host_item;
                WINE_TRACE("Translating HDM_*ITEM message at %p.\n", guest_item);
                host_item = HeapAlloc(GetProcessHeap(), 0, sizeof(*host_item));
                HDITEM_g2h(host_item, guest_item);
                msg_out->lParam = (LPARAM)host_item;
            }
            break;

        case PSM_ISDIALOGMESSAGE:
        case TTM_RELAYEVENT:
            if (msg_in->lParam)
            {
                struct qemu_MSG *guest_msg = (struct qemu_MSG *)msg_in->lParam;
                MSG *host_msg, copy;
                WINE_TRACE("Translating PSM_ISDIALOGMESSAGE message at %p.\n", guest_msg);
                host_msg = HeapAlloc(GetProcessHeap(), 0, sizeof(*host_msg));
                MSG_g2h(&copy, guest_msg);

                msg_guest_to_host(host_msg, &copy);

                msg_out->lParam = (LPARAM)host_msg;
            }
            break;

#endif

        default:
            /* Not constant numbers */
            if (msg_in->message == msg_FINDMSGSTRING)
            {
                WINE_FIXME("Did not expect MSG_FINDMSGSTRING to be passed back to the host\n");
                break;
            }
    }
}

void msg_guest_to_host_return(MSG *orig, MSG *conv)
{
    switch (conv->message)
    {
        case LVM_SORTITEMS:
        case LVM_SORTITEMSEX:
            TlsSetValue(user32_tls, LVM_SORTITEMS_old_tls);
            break;

#if HOST_BIT != GUEST_BIT
        case WM_NULL:
            break;

        case WM_CREATE:
        case WM_NCCREATE:
        {
            CREATESTRUCTW *host = (CREATESTRUCTW *)conv->lParam;

            if (host->dwExStyle & WS_EX_MDICHILD)
                HeapFree(GetProcessHeap(), 0, host->lpCreateParams);
            HeapFree(GetProcessHeap(), 0, host);

            break;
        }

        case WM_MDICREATE:
            HeapFree(GetProcessHeap(), 0, (void *)conv->lParam);
            break;

        case WM_WINDOWPOSCHANGING:
        case WM_WINDOWPOSCHANGED:
        {
            struct qemu_WINDOWPOS *guest = (struct qemu_WINDOWPOS *)orig->lParam;
            WINDOWPOS *host = (WINDOWPOS *)conv->lParam;

            WINDOWPOS_h2g(guest, host);

            HeapFree(GetProcessHeap(), 0, (void *)conv->lParam);
            break;
        }

        case WM_DRAWITEM:
        case WM_COMPAREITEM:
            HeapFree(GetProcessHeap(), 0, (void *)conv->lParam);
            break;

        case WM_NOTIFY:
            if (conv->lParam != orig->lParam)
            {
                struct qemu_NMHEADER *guest = (struct qemu_NMHEADER *)orig->lParam;
                NMHEADERW *host = (NMHEADERW *)conv->lParam;

                NMHEADER_h2g(guest, host);
                HeapFree(GetProcessHeap(), 0, (void *)conv->lParam);
            }
            break;

        case CB_GETCOMBOBOXINFO:
        {
            struct qemu_COMBOBOXINFO *guest = (struct qemu_COMBOBOXINFO *)orig->lParam;
            COMBOBOXINFO *host = (COMBOBOXINFO *)conv->lParam;

            COMBOBOXINFO_h2g(guest, host);

            HeapFree(GetProcessHeap(), 0, (void *)conv->lParam);
            break;
        }

        case WM_USER+63:
        case WM_USER+65:
            if (conv->lParam != orig->lParam)
            {
                struct qemu_TBBUTTONINFO *guest = (struct qemu_TBBUTTONINFO *)orig->lParam;
                TBBUTTONINFOW *host = (TBBUTTONINFOW *)conv->lParam;
                WINE_TRACE("Reverse translating TB_GETBUTTONINFO.\n");

                if (host->cbSize == sizeof(*host))
                    TBBUTTONINFO_h2g(guest, host);
                HeapFree(GetProcessHeap(), 0, host);
            }
            break;

        case WM_USER+23:
            if (conv->lParam != orig->lParam)
            {
                struct qemu_TBBUTTON *guest = (struct qemu_TBBUTTON *)orig->lParam;
                TBBUTTON *host = (TBBUTTON *)conv->lParam;
                WINE_TRACE("Reverse translating TBBUTTON.\n");
                TBBUTTON_h2g(guest, host);
                HeapFree(GetProcessHeap(), 0, host);
            }
            break;

        case WM_USER+19:
        case WM_USER+20:
        case WM_USER+21:
        case WM_USER+64:
        case WM_USER+66:
        case WM_USER+68:
        case WM_USER+26:
        case WM_USER+76:
            if (conv->lParam != orig->lParam)
                HeapFree(GetProcessHeap(), 0, (void *)conv->lParam);
            break;

        case TCM_GETITEMA:
        case TCM_GETITEMW:
        case TCM_SETITEMA:
        case TCM_SETITEMW:
        case TCM_INSERTITEMA:
        case TCM_INSERTITEMW:
            if (conv->lParam != orig->lParam)
            {
                struct qemu_TCITEM *guest_item = (struct qemu_TCITEM *)orig->lParam;
                TCITEMW *host_item = (TCITEMW *)conv->lParam;
                WINE_TRACE("Reverse translating TCM_*ITEM message.\n");

                TCITEM_h2g(guest_item, host_item);

                HeapFree(GetProcessHeap(), 0, host_item);
            }
            break;

        case LVM_SETITEMSTATE:
        case LVM_SETITEMA:
        case LVM_SETITEMW:
        case LVM_GETITEMA:
        case LVM_GETITEMW:
        case LVM_INSERTITEMA:
        case LVM_INSERTITEMW:
        case LVM_SETITEMTEXTA:
        case LVM_SETITEMTEXTW:
        case LVM_GETITEMTEXTA:
        case LVM_GETITEMTEXTW:
            if (conv->lParam != orig->lParam)
            {
                struct qemu_LVITEM *guest_item = (struct qemu_LVITEM *)orig->lParam;
                LVITEMW *host_item = (LVITEMW *)conv->lParam;
                WINE_TRACE("Reverse translating LVM_*ITEM message.\n");

                LVITEM_h2g(guest_item, host_item);

                HeapFree(GetProcessHeap(), 0, host_item);
            }
            break;

        case LVM_INSERTCOLUMNA:
        case LVM_INSERTCOLUMNW:
        case LVM_GETCOLUMNA:
        case LVM_GETCOLUMNW:
        case LVM_SETCOLUMNA:
        case LVM_SETCOLUMNW:
            if (conv->lParam != orig->lParam)
            {
                struct qemu_LVCOLUMN *guest_item = (struct qemu_LVCOLUMN *)orig->lParam;
                LVCOLUMNW *host_item = (LVCOLUMNW *)conv->lParam;
                WINE_TRACE("Reverse translating LVM_*COLUMN message.\n");

                LVCOLUMN_h2g(guest_item, host_item);

                HeapFree(GetProcessHeap(), 0, host_item);
            }
            break;

        case LVM_FINDITEMA:
        case LVM_FINDITEMW:
            if (conv->lParam != orig->lParam)
            {
                struct qemu_LVFINDINFO *guest_item = (struct qemu_LVFINDINFO *)orig->lParam;
                LVFINDINFOW *host_item = (LVFINDINFOW *)conv->lParam;
                WINE_TRACE("Reverse translating LVM_FINDITEM message.\n");

                LVFINDINFO_h2g(guest_item, host_item);

                HeapFree(GetProcessHeap(), 0, host_item);
            }
            break;

        case HDM_LAYOUT:
            if (conv->lParam != orig->lParam)
            {
                struct qemu_HD_LAYOUT *guest = (struct qemu_HD_LAYOUT *)orig->lParam;
                HD_LAYOUT *host = (HD_LAYOUT *)conv->lParam;
                WINE_TRACE("Reverse translating HDM_LAYOUT message.\n");

                HD_LAYOUT_h2g(guest, (struct qemu_WINDOWPOS *)(ULONG_PTR)guest->pwpos, host);

                HeapFree(GetProcessHeap(), 0, host);
            }
            break;

        case HDM_INSERTITEMA:
        case HDM_INSERTITEMW:
        case HDM_GETITEMA:
        case HDM_GETITEMW:
        case HDM_SETITEMA:
        case HDM_SETITEMW:
            if (conv->lParam != orig->lParam)
            {
                struct qemu_HDITEM *guest_item = (struct qemu_HDITEM *)orig->lParam;
                HDITEMW *host_item = (HDITEMW *)conv->lParam;
                WINE_TRACE("Reverse translating HDM_*ITEM message.\n");

                HDITEM_h2g(guest_item, host_item);

                HeapFree(GetProcessHeap(), 0, host_item);
            }
            break;

        case PSM_ISDIALOGMESSAGE:
        case TTM_RELAYEVENT:
            if (conv->lParam != orig->lParam)
            {
                struct qemu_MSG *guest_msg = (struct qemu_MSG *)orig->lParam;
                MSG *host_msg = (MSG *)conv->lParam, copy;

                MSG_g2h(&copy, guest_msg);
                msg_host_to_guest_return(&copy, host_msg);

                HeapFree(GetProcessHeap(), 0, host_msg);
                MSG_h2g(guest_msg, &copy);
            }
            break;

        default:
            if (conv->message == msg_FINDMSGSTRING)
            {
                break;
            }
            break;
#endif
    }
}

struct notify_record
{
    WCHAR *name;
    void (*translate)(MSG *guest, MSG *host, BOOL ret);
};

static struct notify_record notify_callbacks[64];

void msg_host_to_guest(MSG *msg_out, MSG *msg_in)
{
    *msg_out = *msg_in;

    switch (msg_in->message)
    {
        case WM_NULL:
            break;

        case WM_TIMER:
        case WM_SYSTIMER:
            msg_out->lParam = wndproc_host_to_guest((WNDPROC)msg_in->lParam);
            break;

        case LVM_SORTITEMS:
        case LVM_SORTITEMSEX:
            if (msg_in->lParam != (LPARAM)LVM_SORTITEMS_host_cb)
            {
                WINE_FIXME("LVM_SORTITEMS message is converted from host to guest.\n");
            }
            else
            {
                uint64_t *guest_cb = TlsGetValue(user32_tls);
                if (!guest_cb)
                    WINE_ERR("Converting a LVM_SORTITEMS back, but user32_tls is NULL?\n");
                msg_out->lParam = *guest_cb;
            }
            break;

#if HOST_BIT != GUEST_BIT
        case WM_CREATE:
        case WM_NCCREATE:
        {
            struct qemu_CREATESTRUCT *guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest));
            CREATESTRUCTW *host = (CREATESTRUCTW *)msg_in->lParam;
            CREATESTRUCT_h2g(guest, host);
            msg_out->lParam = (LPARAM)guest;

            /* The lovely Warhammer40k: Dawn of War graphics config utility sets a WH_CBT hook and hooks the
             * wndprocs of *all* windows that are created. Among other things it hooks WineD3D's hidden window
             * to initialize GPU caps. This window has a string that's in wined3d.dll.so's constant data
             * segment, so usually above 4 GB. We can't communicate it through the guest structure. Be noisy
             * and set it to 0.
             *
             * Creating a HeapAlloc'ed copy here is not trivial because we do not know if this is an A or W
             * call. The other alternative would be to hide some Wine internal windows from the application. */
            if ((ULONG_PTR)host->lpszName > ~0U)
            {
                WINE_FIXME("Static Wine window name at %p is sent through a guest function, setting to 0\n",
                        host->lpszName);
                guest->lpszName = 0;
            }

            if (host->dwExStyle & WS_EX_MDICHILD)
            {
                MDICREATESTRUCTW *mdi_cs = host->lpCreateParams;
                struct qemu_MDICREATESTRUCT *mdi_cs_guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*mdi_cs_guest));

                WINE_TRACE("Converting MDICREATESTRUCTW, lp %lx\n", mdi_cs->lParam);
                MDICREATESTRUCT_h2g(mdi_cs_guest, mdi_cs);
                guest->lpCreateParams = (ULONG_PTR)mdi_cs_guest;
            }
            break;
        }

        case WM_MDICREATE:
        {
            MDICREATESTRUCTW *mdi_cs = (MDICREATESTRUCTW *)msg_in->lParam;
            struct qemu_MDICREATESTRUCT *mdi_cs_guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*mdi_cs_guest));
            MDICREATESTRUCT_h2g(mdi_cs_guest, mdi_cs);
            msg_out->lParam = (ULONG_PTR)mdi_cs_guest;
            break;
        }

        case WM_NCCALCSIZE:
        {
            /* FIXME: This should not be necessary if we restriced the host stack to < 4 GB. */
            RECT *copy = HeapAlloc(GetProcessHeap(), 0, sizeof(*copy));
            *copy = *(RECT *)msg_in->lParam;
            msg_out->lParam = (LPARAM)copy;
            break;
        }

        case WM_WINDOWPOSCHANGING:
        case WM_WINDOWPOSCHANGED:
        {
            WINDOWPOS *host = (WINDOWPOS *)msg_in->lParam;
            struct qemu_WINDOWPOS *guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*host));

            WINDOWPOS_h2g(guest, host);

            msg_out->lParam = (LPARAM)guest;
            break;
        }

        case WM_DRAWITEM:
        {
            DRAWITEMSTRUCT *host = (DRAWITEMSTRUCT *)msg_in->lParam;
            struct qemu_DRAWITEMSTRUCT *guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest));
            DRAWITEMSTRUCT_h2g(guest, host);
            msg_out->lParam = (LPARAM)guest;
            break;
        }

        case WM_COMPAREITEM:
        {
            COMPAREITEMSTRUCT *host = (COMPAREITEMSTRUCT *)msg_in->lParam;
            struct qemu_COMPAREITEMSTRUCT *guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest));
            COMPAREITEMSTRUCT_h2g(guest, host);
            msg_out->lParam = (LPARAM)guest;
            break;
        }

        case WM_NOTIFY:
        {
            int i;
            WCHAR class[256];
            NMHDR *hdr = (NMHDR *)msg_in->lParam;

            /* We can't get WM_NOTIFY messages right :-( . They can be sent from Wine controls in comctl32
             * and other DLLs, and in this case we have to convert them in a message-specific way. This
             * library gives the comctl32 wrapper a way to register callbacks for WM_NOTIFY messages with
             * a hwndFrom that matches a given class name.
             *
             * However, WM_NOTIFY messages can also be sent from the application to itself, and there is
             * no guarantee that lParam points to a valid NMHDR structure. The user32/msg.c tests are an
             * example of that. So before we try to read hwndFrom, make sure the pointer can be read.
             *
             * And to make matters more complicated, even if we have a valid NMHDR we are never converting
             * it from guest to host. The reason is that NMHDR is usually part of a larger structure, and
             * we have no way of knowing how big it is. So SendMessage won't touch a WM_NOTIFY's lParam
             * before feeding the message to Wine. Commonly these messages later get send back to us and
             * end up in this function, where we try to treat it as a host NMHDR and try to convert it to
             * a guest NMHDR.
             *
             * If we get an "impossible" (> 32 bit) HWND value we're probably reading a qemu_NMHDR instead
             * of a NMHDR. Ignore it. If it is from an unknown class ignore it. If it is from a subclassed
             * Wine dialog hope that it doesn't match the filter criteria from a known Wine->Guest NMHDR.
             *
             * Furthermore, when the application subclasses a control by registering its own class and using
             * the wndproc of the registered class we won't be able to recognize that the message is from
             * the host side or which message it actually is. */
            if (IsBadReadPtr(hdr, sizeof(*hdr)))
                break;

            if ((ULONG_PTR)hdr->hwndFrom > ~0U)
            {
                struct qemu_NMHDR *guest_hdr = (struct qemu_NMHDR *)msg_in->lParam;
                WINE_WARN("WM_NOTIFY message probably sent from guest (hwndFrom=%p/0x%08x), not touching it.\n",
                        hdr->hwndFrom, guest_hdr->hwndFrom);
                break;
            }

            i = GetClassNameW(hdr->hwndFrom, class, sizeof(class) / sizeof(*class));
            if (i < 0 || i == 256)
                break;

            for (i = 0; notify_callbacks[i].name; ++i)
            {
                if (strcmpW(class, notify_callbacks[i].name))
                    continue;
                notify_callbacks[i].translate(msg_out, msg_in, FALSE);
                return;
            }
            WINE_WARN("WM_NOTIFY from unregistered class %s.\n", wine_dbgstr_w(class));
            break;
        }

        case CB_GETCOMBOBOXINFO:
        {
            COMBOBOXINFO *host = (COMBOBOXINFO *)msg_in->lParam;
            struct qemu_COMBOBOXINFO *guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest));
            COMBOBOXINFO_h2g(guest, host);
            msg_out->lParam = (LPARAM)guest;
            break;
        }

        case TCM_GETITEMA:
        case TCM_GETITEMW:
        case TCM_SETITEMA:
        case TCM_SETITEMW:
        case TCM_INSERTITEMA:
        case TCM_INSERTITEMW:
        {
            /* TODO: Are these message numbers guaranteed to be unique?
             *
             * FIXME: The struct has a dynamic size, and the size is stored in the tab control,
             * not in the struct itself :-( */
            TCITEMW *host = (TCITEMW *)msg_in->lParam;
            struct qemu_TCITEM *guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest));
            TCITEM_h2g(guest, host);
            msg_out->lParam = (LPARAM)guest;
            break;
        }

        case LVM_SETITEMSTATE:
        case LVM_SETITEMA:
        case LVM_SETITEMW:
        case LVM_GETITEMA:
        case LVM_GETITEMW:
        case LVM_INSERTITEMA:
        case LVM_INSERTITEMW:
        case LVM_SETITEMTEXTA:
        case LVM_SETITEMTEXTW:
        case LVM_GETITEMTEXTA:
        case LVM_GETITEMTEXTW:
            if (msg_in->lParam)
            {
                LVITEMW *host = (LVITEMW *)msg_in->lParam;
                struct qemu_LVITEM *guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest));
                LVITEM_h2g(guest, host);
                msg_out->lParam = (LPARAM)guest;
            }
            break;

        case LVM_INSERTCOLUMNA:
        case LVM_INSERTCOLUMNW:
        case LVM_GETCOLUMNA:
        case LVM_GETCOLUMNW:
        case LVM_SETCOLUMNA:
        case LVM_SETCOLUMNW:
            if (msg_in->lParam)
            {
                LVCOLUMNW *host = (LVCOLUMNW *)msg_in->lParam;
                struct qemu_LVCOLUMN *guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest));
                LVCOLUMN_h2g(guest, host);
                msg_out->lParam = (LPARAM)guest;
            }
            break;

        case LVM_FINDITEMA:
        case LVM_FINDITEMW:
            if (msg_in->lParam)
            {
                LVFINDINFOW *host = (LVFINDINFOW *)msg_in->lParam;
                struct qemu_LVFINDINFO *guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest));
                LVFINDINFO_h2g(guest, host);
                msg_out->lParam = (LPARAM)guest;
            }
            break;

        case HDM_LAYOUT:
            if (msg_in->lParam)
            {
                HD_LAYOUT *host = (HD_LAYOUT *)msg_in->lParam;
                struct
                {
                    struct qemu_HD_LAYOUT layout;
                    struct qemu_WINDOWPOS wp;
                } *guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest));
                HD_LAYOUT_h2g(&guest->layout, &guest->wp, host);
                msg_out->lParam = (LPARAM)&guest->layout;
            }
            break;

        case HDM_INSERTITEMA:
        case HDM_INSERTITEMW:
        case HDM_GETITEMA:
        case HDM_GETITEMW:
        case HDM_SETITEMA:
        case HDM_SETITEMW:
            if (msg_in->lParam)
            {
                HDITEMW *host = (HDITEMW *)msg_in->lParam;
                struct qemu_HDITEM *guest = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest));
                HDITEM_h2g(guest, host);
                msg_out->lParam = (LPARAM)guest;
            }
            break;

        case PSM_ISDIALOGMESSAGE:
        case TTM_RELAYEVENT:
            /* Probably subclassing shenanigans. Just convert if this is ever hit. */
            WINE_FIXME("PSM_ISDIALOGMESSAGE or TTM_RELAYEVENT sent from host to guest.\n");
            break;

        default:
            /* Not constant numbers */
            if (msg_in->message == msg_FINDMSGSTRING)
            {
                FINDREPLACEW *host = (FINDREPLACEW *)msg_in->lParam;
                struct qemu_FINDREPLACE *guest = (struct qemu_FINDREPLACE *)host->lCustData;

                FINDREPLACE_h2g(guest, host);

                msg_out->lParam = (LPARAM)guest;
            }
            break;
#endif
    }
}

void msg_host_to_guest_return(MSG *orig, MSG *conv)
{
#if HOST_BIT != GUEST_BIT
    switch (conv->message)
    {
        case WM_NULL:
            break;

        case WM_CREATE:
        case WM_NCCREATE:
        {
            struct qemu_CREATESTRUCT *guest_cs = (struct qemu_CREATESTRUCT *)conv->lParam;
            if (guest_cs->dwExStyle & WS_EX_MDICHILD)
                HeapFree(GetProcessHeap(), 0, (void *)(ULONG_PTR)guest_cs->lpCreateParams);
            HeapFree(GetProcessHeap(), 0, guest_cs);
            break;
        }

        case WM_MDICREATE:
            HeapFree(GetProcessHeap(), 0, (void *)conv->lParam);
            break;

        case WM_NCCALCSIZE:
            /* FIXME: This should not be necessary if we restriced the host stack to < 4 GB. */
            *(RECT *)orig->lParam = *(RECT *)conv->lParam;
            HeapFree(GetProcessHeap(), 0, (void *)conv->lParam);
            break;

        case WM_WINDOWPOSCHANGING:
        case WM_WINDOWPOSCHANGED:
        {
            struct qemu_WINDOWPOS *guest = (struct qemu_WINDOWPOS *)conv->lParam;
            WINDOWPOS *host = (WINDOWPOS *)orig->lParam;

            WINDOWPOS_g2h(host, guest);

            HeapFree(GetProcessHeap(), 0, (void *)conv->lParam);
            break;
        }

        case WM_DRAWITEM:
        case WM_COMPAREITEM:
            HeapFree(GetProcessHeap(), 0, (void *)conv->lParam);
            break;

        case WM_NOTIFY:
        {
            int i;
            WCHAR class[256];
            NMHDR *hdr = (NMHDR *)orig->lParam;

            if (IsBadReadPtr(hdr, sizeof(*hdr)))
                break;

            i = GetClassNameW(hdr->hwndFrom, class, sizeof(class) / sizeof(*class));
            if (i < 0 || i == 256)
                break;

            for (i = 0; notify_callbacks[i].name; ++i)
            {
                if (strcmpW(class, notify_callbacks[i].name))
                    continue;
                notify_callbacks[i].translate(conv, orig, TRUE);
                return;
            }
            break;
        }

        case CB_GETCOMBOBOXINFO:
        {
            COMBOBOXINFO *host = (COMBOBOXINFO *)orig->lParam;
            struct qemu_COMBOBOXINFO *guest = (struct qemu_COMBOBOXINFO *)conv->lParam;

            COMBOBOXINFO_g2h(host, guest);

            HeapFree(GetProcessHeap(), 0, (void *)conv->lParam);
            break;
        }

        case TCM_GETITEMA:
        case TCM_GETITEMW:
        case TCM_SETITEMA:
        case TCM_SETITEMW:
        case TCM_INSERTITEMA:
        case TCM_INSERTITEMW:
        {
            TCITEMW *host = (TCITEMW *)orig->lParam;
            struct qemu_TCITEM *guest = (struct qemu_TCITEM *)conv->lParam;

            TCITEM_g2h(host, guest);

            HeapFree(GetProcessHeap(), 0, guest);
            break;
        }

        case LVM_SETITEMSTATE:
        case LVM_SETITEMA:
        case LVM_SETITEMW:
        case LVM_GETITEMA:
        case LVM_GETITEMW:
        case LVM_INSERTITEMA:
        case LVM_INSERTITEMW:
        case LVM_SETITEMTEXTA:
        case LVM_SETITEMTEXTW:
        case LVM_GETITEMTEXTA:
        case LVM_GETITEMTEXTW:
            if (orig->lParam)
            {
                LVITEMW *host = (LVITEMW *)orig->lParam;
                struct qemu_LVITEM *guest = (struct qemu_LVITEM *)conv->lParam;

                LVITEM_g2h(host, guest);

                HeapFree(GetProcessHeap(), 0, guest);
            }
            break;

        case LVM_INSERTCOLUMNA:
        case LVM_INSERTCOLUMNW:
        case LVM_GETCOLUMNA:
        case LVM_GETCOLUMNW:
        case LVM_SETCOLUMNA:
        case LVM_SETCOLUMNW:
            if (orig->lParam)
            {
                LVCOLUMNW *host = (LVCOLUMNW *)orig->lParam;
                struct qemu_LVCOLUMN *guest = (struct qemu_LVCOLUMN *)conv->lParam;

                LVCOLUMN_g2h(host, guest);

                HeapFree(GetProcessHeap(), 0, guest);
            }
            break;

        case LVM_FINDITEMA:
        case LVM_FINDITEMW:
            if (orig->lParam)
            {
                LVFINDINFOW *host = (LVFINDINFOW *)orig->lParam;
                struct qemu_LVFINDINFO *guest = (struct qemu_LVFINDINFO *)conv->lParam;

                LVFINDINFO_g2h(host, guest);

                HeapFree(GetProcessHeap(), 0, guest);
            }
            break;

        case HDM_LAYOUT:
            if (orig->lParam)
            {
                HD_LAYOUT *host = (HD_LAYOUT *)orig->lParam;
                struct qemu_HD_LAYOUT *guest = (struct qemu_HD_LAYOUT *)conv->lParam;

                HD_LAYOUT_g2h(host, host->pwpos, guest);

                HeapFree(GetProcessHeap(), 0, guest);
            }
            break;

        case HDM_INSERTITEMA:
        case HDM_INSERTITEMW:
        case HDM_GETITEMA:
        case HDM_GETITEMW:
        case HDM_SETITEMA:
        case HDM_SETITEMW:
            if (orig->lParam)
            {
                HDITEMW *host = (HDITEMW *)orig->lParam;
                struct qemu_HDITEM *guest = (struct qemu_HDITEM *)conv->lParam;

                HDITEM_g2h(host, guest);

                HeapFree(GetProcessHeap(), 0, guest);
            }
            break;

        default:
            if (conv->message == msg_FINDMSGSTRING)
            {
                FINDREPLACEW *host = (FINDREPLACEW *)orig->lParam;
                if (host->Flags & FR_DIALOGTERM)
                    HeapFree(GetProcessHeap(), 0, host);
                else
                    FINDREPLACE_g2h(host, (struct qemu_FINDREPLACE *)conv->lParam);
            }
            break;
    }
#endif
}

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            wrapper_mod = mod;
            host_mod = GetModuleHandleA("user32.dll");

            wine_rb_init(&win_event_tree, win_event_compare);
            break;

        default:
            break;
    }

    return TRUE;
}

BOOL WINAPI qemu_user32_notify(const WCHAR *class, void (*func)(MSG *guest, MSG *host, BOOL ret))
{
    unsigned int i;
    size_t len;

    for (i = 0; i < (sizeof(notify_callbacks) / sizeof(*notify_callbacks)) - 1; ++i)
    {
        if (notify_callbacks[i].name)
            continue;

        len = strlenW(class) + 1;
        notify_callbacks[i].name = HeapAlloc(GetProcessHeap(), 0, sizeof(*class) * len);
        memcpy(notify_callbacks[i].name, class, sizeof(*class) * len);
        notify_callbacks[i].translate = func;
        return TRUE;
    }

    WINE_ERR("Increase the notify callback array\n");
    return FALSE;
}

#endif
