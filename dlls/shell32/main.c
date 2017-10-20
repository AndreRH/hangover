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
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);

#endif

#ifndef QEMU_DLL_GUEST
const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_ArrangeWindows,
    qemu_CallCPLEntry16,
    qemu_CDefFolderMenu_Create2,
    qemu_CheckEscapesA,
    qemu_CheckEscapesW,
    qemu_CIDLData_CreateFromIDArray,
    qemu_CommandLineToArgvW,
    qemu_Control_FillCache_RunDLLA,
    qemu_Control_FillCache_RunDLLW,
    qemu_Control_RunDLLA,
    qemu_Control_RunDLLW,
    qemu_DAD_AutoScroll,
    qemu_DAD_DragEnter,
    qemu_DAD_DragEnterEx,
    qemu_DAD_DragLeave,
    qemu_DAD_DragMove,
    qemu_DAD_SetDragImage,
    qemu_DAD_ShowDragImage,
    qemu_DllCanUnloadNow,
    qemu_DllGetClassObject,
    qemu_DllGetVersion,
    qemu_DllInstall,
    qemu_DllRegisterServer,
    qemu_DllUnregisterServer,
    qemu_DoEnvironmentSubst,
    qemu_DoEnvironmentSubstA,
    qemu_DoEnvironmentSubstW,
    qemu_DragAcceptFiles,
    qemu_DragFinish,
    qemu_DragQueryFileA,
    qemu_DragQueryFileW,
    qemu_DragQueryPoint,
    qemu_DriveType,
    qemu_DuplicateIcon,
    qemu_ExitWindowsDialog,
    qemu_ExtractAssociatedIconA,
    qemu_ExtractAssociatedIconExA,
    qemu_ExtractAssociatedIconExW,
    qemu_ExtractAssociatedIconW,
    qemu_ExtractIconA,
    qemu_ExtractIconExA,
    qemu_ExtractIconExW,
    qemu_ExtractIconW,
    qemu_ExtractVersionResource16W,
    qemu_FileIconInit,
    qemu_FileMenu_AbortInitMenu,
    qemu_FileMenu_AddFilesForPidl,
    qemu_FileMenu_AppendFilesForPidl,
    qemu_FileMenu_AppendItemAW,
    qemu_FileMenu_Create,
    qemu_FileMenu_DeleteAllItems,
    qemu_FileMenu_DeleteItemByCmd,
    qemu_FileMenu_DeleteItemByFirstID,
    qemu_FileMenu_DeleteItemByIndex,
    qemu_FileMenu_DeleteSeparator,
    qemu_FileMenu_Destroy,
    qemu_FileMenu_DrawItem,
    qemu_FileMenu_EnableItemByCmd,
    qemu_FileMenu_FindSubMenuByPidl,
    qemu_FileMenu_GetItemExtent,
    qemu_FileMenu_GetLastSelectedItemPidls,
    qemu_FileMenu_HandleMenuChar,
    qemu_FileMenu_InitMenuPopup,
    qemu_FileMenu_InsertUsingPidl,
    qemu_FileMenu_Invalidate,
    qemu_FileMenu_MeasureItem,
    qemu_FileMenu_ReplaceUsingPidl,
    qemu_FileMenu_TrackPopupMenuEx,
    qemu_FindExecutableA,
    qemu_FindExecutableW,
    qemu_FreeIconList,
    qemu_GetCurrentProcessExplicitAppUserModelID,
    qemu_GetFileNameFromBrowse,
    qemu_GUIDFromStringW,
    qemu_ILAppendID,
    qemu_ILClone,
    qemu_ILCloneFirst,
    qemu_ILCombine,
    qemu_ILCreateFromPathA,
    qemu_ILCreateFromPathW,
    qemu_ILFindChild,
    qemu_ILFindLastID,
    qemu_ILFree,
    qemu_ILGetDisplayName,
    qemu_ILGetDisplayNameEx,
    qemu_ILGetNext,
    qemu_ILGetSize,
    qemu_ILGlobalClone,
    qemu_ILGlobalFree,
    qemu_ILIsEqual,
    qemu_ILIsParent,
    qemu_ILLoadFromStream,
    qemu_ILRemoveLastID,
    qemu_ILSaveToStream,
    qemu_InitNetworkAddressControl,
    qemu_InvalidateDriveType,
    qemu_IsLFNDriveA,
    qemu_IsLFNDriveW,
    qemu_IsNetDrive,
    qemu_IsUserAnAdmin,
    qemu_LinkWindow_RegisterClass,
    qemu_LinkWindow_UnregisterClass,
    qemu_NTSHChangeNotifyDeregister,
    qemu_NTSHChangeNotifyRegister,
    qemu_OleStrToStrNAW,
    qemu_OpenAs_RunDLLA,
    qemu_OpenAs_RunDLLW,
    qemu_ParseField,
    qemu_PathYetAnotherMakeUniqueName,
    qemu_PickIconDlg,
    qemu_Printer_LoadIconsW,
    qemu_Printers_RegisterWindowW,
    qemu_Printers_UnregisterWindow,
    qemu_ReadCabinetState,
    qemu_RealDriveType,
    qemu_RegenerateUserEnvironment,
    qemu_RegisterShellHook,
    qemu_RestartDialog,
    qemu_RestartDialogEx,
    qemu_RLBuildListOfPaths,
    qemu_RunFileDlgAW,
    qemu_SetAppStartingCursor,
    qemu_SetCurrentProcessExplicitAppUserModelID,
    qemu_SHAbortInvokeCommand,
    qemu_SHAddFromPropSheetExtArray,
    qemu_SHAddToRecentDocs,
    qemu_SHAlloc,
    qemu_SHAllocShared,
    qemu_SHAppBarMessage,
    qemu_SHAssocEnumHandlers,
    qemu_SHBindToParent,
    qemu_SHBrowseForFolderA,
    qemu_SHBrowseForFolderW,
    qemu_SHChangeNotification_Lock,
    qemu_SHChangeNotification_Unlock,
    qemu_SHChangeNotify,
    qemu_SHChangeNotifyDeregister,
    qemu_SHChangeNotifyRegister,
    qemu_SHChangeNotifyUpdateEntryList,
    qemu_SHCloneSpecialIDList,
    qemu_SHCLSIDFromString,
    qemu_SHCoCreateInstance,
    qemu_SHCreateDefaultContextMenu,
    qemu_SHCreateDirectory,
    qemu_SHCreateDirectoryExA,
    qemu_SHCreateDirectoryExW,
    qemu_SHCreateFileExtractIconW,
    qemu_SHCreateItemFromIDList,
    qemu_SHCreateItemFromParsingName,
    qemu_SHCreateLinks,
    qemu_SHCreatePropSheetExtArray,
    qemu_SHCreatePropSheetExtArrayEx,
    qemu_SHCreateQueryCancelAutoPlayMoniker,
    qemu_SHCreateSessionKey,
    qemu_SHCreateShellFolderView,
    qemu_SHCreateShellFolderViewEx,
    qemu_SHCreateShellItem,
    qemu_SHCreateShellItemArray,
    qemu_SHCreateShellItemArrayFromDataObject,
    qemu_SHCreateShellItemArrayFromIDLists,
    qemu_SHCreateShellItemArrayFromShellItem,
    qemu_SHCreateStdEnumFmtEtc,
    qemu_SHDefExtractIconA,
    qemu_SHDefExtractIconW,
    qemu_SHDestroyPropSheetExtArray,
    qemu_SHDoDragDrop,
    qemu_SheChangeDirA,
    qemu_SheChangeDirW,
    qemu_SheGetDirA,
    qemu_SheGetDirW,
    qemu_shell32_243,
    qemu_Shell_GetCachedImageIndexAW,
    qemu_Shell_GetImageLists,
    qemu_Shell_MergeMenus,
    qemu_Shell_NotifyIconA,
    qemu_Shell_NotifyIconW,
    qemu_ShellAboutA,
    qemu_ShellAboutW,
    qemu_ShellDDEInit,
    qemu_ShellExecuteA,
    qemu_ShellExecuteExA,
    qemu_ShellExecuteExW,
    qemu_ShellExecuteW,
    qemu_ShellHookProc,
    qemu_ShellMessageBox,
    qemu_SHEmptyRecycleBinA,
    qemu_SHEmptyRecycleBinW,
    qemu_SHEnumerateUnreadMailAccountsW,
    qemu_SHFileOperationA,
    qemu_SHFileOperationW,
    qemu_SHFind_InitMenuPopup,
    qemu_SHFindFiles,
    qemu_SHFlushClipboard,
    qemu_SHFlushSFCache,
    qemu_SHFormatDrive,
    qemu_SHFree,
    qemu_SHFreeNameMappings,
    qemu_SHFreeShared,
    qemu_SHFreeUnusedLibraries,
    qemu_SHGetDataFromIDListA,
    qemu_SHGetDataFromIDListW,
    qemu_SHGetFileInfoA,
    qemu_SHGetFileInfoW,
    qemu_SHGetFolderLocation,
    qemu_SHGetFolderPathA,
    qemu_SHGetFolderPathAndSubDirA,
    qemu_SHGetFolderPathAndSubDirW,
    qemu_SHGetFolderPathEx,
    qemu_SHGetFolderPathW,
    qemu_SHGetIconOverlayIndexA,
    qemu_SHGetIconOverlayIndexW,
    qemu_SHGetIDListFromObject,
    qemu_SHGetImageList,
    qemu_SHGetInstanceExplorer,
    qemu_SHGetItemFromDataObject,
    qemu_SHGetItemFromObject,
    qemu_SHGetKnownFolderIDList,
    qemu_SHGetKnownFolderItem,
    qemu_SHGetKnownFolderPath,
    qemu_SHGetLocalizedName,
    qemu_SHGetMalloc,
    qemu_SHGetNameFromIDList,
    qemu_SHGetNewLinkInfoA,
    qemu_SHGetNewLinkInfoW,
    qemu_SHGetPathFromIDListA,
    qemu_SHGetPathFromIDListEx,
    qemu_SHGetPathFromIDListW,
    qemu_SHGetPropertyStoreForWindow,
    qemu_SHGetPropertyStoreFromParsingName,
    qemu_SHGetRealIDL,
    qemu_SHGetSetFolderCustomSettings,
    qemu_SHGetSetSettings,
    qemu_SHGetSettings,
    qemu_SHGetSpecialFolderLocation,
    qemu_SHGetSpecialFolderPathA,
    qemu_SHGetSpecialFolderPathW,
    qemu_SHGetStockIconInfo,
    qemu_SHHandleUpdateImage,
    qemu_SHHelpShortcuts_RunDLLA,
    qemu_SHHelpShortcuts_RunDLLW,
    qemu_SHILCreateFromPathAW,
    qemu_SHInitRestricted,
    qemu_SHIsFileAvailableOffline,
    qemu_SHLimitInputEdit,
    qemu_SHLoadInProc,
    qemu_SHLoadNonloadedIconOverlayIdentifiers,
    qemu_SHLoadOLE,
    qemu_SHLockShared,
    qemu_SHLogILFromFSIL,
    qemu_SHMapIDListToImageListIndexAsync,
    qemu_SHMapPIDLToSystemImageListIndex,
    qemu_SHObjectProperties,
    qemu_SHOpenFolderAndSelectItems,
    qemu_SHOpenWithDialog,
    qemu_SHOutOfMemoryMessageBox,
    qemu_SHParseDisplayName,
    qemu_SHPathPrepareForWriteA,
    qemu_SHPathPrepareForWriteW,
    qemu_SHPropStgCreate,
    qemu_SHPropStgReadMultiple,
    qemu_SHPropStgWriteMultiple,
    qemu_SHQueryRecycleBinA,
    qemu_SHQueryRecycleBinW,
    qemu_SHQueryUserNotificationState,
    qemu_SHRegCloseKey,
    qemu_SHRegDeleteKeyW,
    qemu_SHRegisterDragDrop,
    qemu_SHRegOpenKeyA,
    qemu_SHRegOpenKeyW,
    qemu_SHRegQueryValueA,
    qemu_SHRegQueryValueExA,
    qemu_SHRegQueryValueExW,
    qemu_SHRegQueryValueW,
    qemu_SHRemoveLocalizedName,
    qemu_SHReplaceFromPropSheetExtArray,
    qemu_SHRestricted,
    qemu_SHRevokeDragDrop,
    qemu_SHRunControlPanel,
    qemu_SHSetInstanceExplorer,
    qemu_SHSetLocalizedName,
    qemu_SHSetUnreadMailCountW,
    qemu_SHShellFolderView_Message,
    qemu_SHSimpleIDListFromPathAW,
    qemu_SHStartNetConnectionDialog,
    qemu_SHUnlockShared,
    qemu_SHUpdateImageA,
    qemu_SHUpdateImageW,
    qemu_SHUpdateRecycleBinIcon,
    qemu_SHValidateUNC,
    qemu_SHWaitForFileToOpen,
    qemu_SHWinHelp,
    qemu_SignalFileOpen,
    qemu_StrRetToStrNAW,
    qemu_StrToOleStrAW,
    qemu_StrToOleStrNAW,
    qemu_Win32CreateDirectory,
    qemu_Win32DeleteFile,
    qemu_Win32RemoveDirectory,
    qemu_WOWShellExecute,
    qemu_WriteCabinetState,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE shell32;

    WINE_TRACE("Loading host-side shell32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    shell32 = LoadLibraryA("shell32.dll");
    if (!shell32)
        WINE_ERR("Cannot find shell32.dll\n");

    p_DllGetClassObject = (void *)GetProcAddress(shell32, "DllGetClassObject");
    if (!p_DllGetClassObject)
        WINE_ERR("Failed to load shell32.DllGetClassObject.\n");
    p_ExitWindowsDialog = (void *)GetProcAddress(shell32, MAKEINTRESOURCE(60));
    if (!p_ExitWindowsDialog)
        WINE_ERR("Failed to load shell32.ExitWindowsDialog (#60).\n");
    p_RunFileDlgAW = (void *)GetProcAddress(shell32, MAKEINTRESOURCE(61));
    if (!p_RunFileDlgAW)
        WINE_ERR("Failed to load shell32.RunFileDlgAW (#61).\n");
    p_SHCLSIDFromString = (void *)GetProcAddress(shell32, MAKEINTRESOURCE(147));
    if (!p_SHCLSIDFromString)
        WINE_ERR("Failed to load shell32.SHCLSIDFromString (#147).\n");
    p_Shell_GetCachedImageIndexAW = (void *)GetProcAddress(shell32, "Shell_GetCachedImageIndex");
    if (!p_Shell_GetCachedImageIndexAW)
        WINE_ERR("Failed to load shell32.Shell_GetCachedImageIndex.\n");
    p_SHMapIDListToImageListIndexAsync = (void *)GetProcAddress(shell32, MAKEINTRESOURCE(148));
    if (!p_SHMapIDListToImageListIndexAsync)
        WINE_ERR("Failed to load shell32.SHMapIDListToImageListIndexAsync (#148).\n");
    p_StrRetToStrNAW = (void *)GetProcAddress(shell32, MAKEINTRESOURCE(96));
    if (!p_StrRetToStrNAW)
        WINE_ERR("Failed to load shell32.StrRetToStrNAW (96).\n");
    p_StrToOleStrAW = (void *)GetProcAddress(shell32, MAKEINTRESOURCE(163));
    if (!p_StrToOleStrAW)
        WINE_ERR("Failed to load shell32.StrToOleStrAW (163).\n");
    p_StrToOleStrNAW = (void *)GetProcAddress(shell32, MAKEINTRESOURCE(79));
    if (!p_StrToOleStrNAW)
        WINE_ERR("Failed to load shell32.StrToOleStrNAW (79).\n");
    p_OleStrToStrNAW = (void *)GetProcAddress(shell32, MAKEINTRESOURCE(78));
    if (!p_OleStrToStrNAW)
        WINE_ERR("Failed to load shell32.OleStrToStrNAW (78).\n");

    return dll_functions;
}

#endif
