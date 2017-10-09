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
    qemu_CIDLData_CreateFromIDArray,
    qemu_CommandLineToArgvW,
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
    qemu_DragAcceptFiles,
    qemu_DragFinish,
    qemu_DragQueryFileA,
    qemu_DragQueryFileW,
    qemu_DragQueryPoint,
    qemu_DriveType,
    qemu_DuplicateIcon,
    qemu_ExtractIconA,
    qemu_ExtractIconW,
    qemu_ExtractVersionResource16W,
    qemu_FileIconInit,
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
    qemu_OpenAs_RunDLLA,
    qemu_OpenAs_RunDLLW,
    qemu_ParseField,
    qemu_PathYetAnotherMakeUniqueName,
    qemu_Printer_LoadIconsW,
    qemu_Printers_RegisterWindowW,
    qemu_Printers_UnregisterWindow,
    qemu_ReadCabinetState,
    qemu_RealDriveType,
    qemu_RegenerateUserEnvironment,
    qemu_RegisterShellHook,
    qemu_RLBuildListOfPaths,
    qemu_SetAppStartingCursor,
    qemu_SetCurrentProcessExplicitAppUserModelID,
    qemu_SHAbortInvokeCommand,
    qemu_SHAddFromPropSheetExtArray,
    qemu_SHAddToRecentDocs,
    qemu_SHAlloc,
    qemu_SHAllocShared,
    qemu_SHAppBarMessage,
    qemu_SHBindToParent,
    qemu_SHBrowseForFolderA,
    qemu_SHBrowseForFolderW,
    qemu_SHCloneSpecialIDList,
    qemu_SHCLSIDFromString,
    qemu_SHCoCreateInstance,
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
    qemu_SHCreateShellItem,
    qemu_SHCreateShellItemArray,
    qemu_SHCreateShellItemArrayFromDataObject,
    qemu_SHCreateShellItemArrayFromIDLists,
    qemu_SHCreateShellItemArrayFromShellItem,
    qemu_SHCreateStdEnumFmtEtc,
    qemu_SHDestroyPropSheetExtArray,
    qemu_SHDoDragDrop,
    qemu_SheChangeDirA,
    qemu_SheChangeDirW,
    qemu_SheGetDirA,
    qemu_SheGetDirW,
    qemu_shell32_243,
    qemu_Shell_NotifyIconA,
    qemu_Shell_NotifyIconW,
    qemu_ShellAboutA,
    qemu_ShellAboutW,
    qemu_ShellExecuteA,
    qemu_ShellExecuteExA,
    qemu_ShellExecuteExW,
    qemu_ShellExecuteW,
    qemu_SHEnumerateUnreadMailAccountsW,
    qemu_SHFileOperationA,
    qemu_SHFileOperationW,
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
    qemu_SHHandleUpdateImage,
    qemu_SHHelpShortcuts_RunDLLA,
    qemu_SHHelpShortcuts_RunDLLW,
    qemu_SHILCreateFromPathAW,
    qemu_SHIsFileAvailableOffline,
    qemu_SHLimitInputEdit,
    qemu_SHLoadInProc,
    qemu_SHLoadNonloadedIconOverlayIdentifiers,
    qemu_SHLoadOLE,
    qemu_SHLockShared,
    qemu_SHLogILFromFSIL,
    qemu_SHObjectProperties,
    qemu_SHOpenFolderAndSelectItems,
    qemu_SHOutOfMemoryMessageBox,
    qemu_SHParseDisplayName,
    qemu_SHPathPrepareForWriteA,
    qemu_SHPathPrepareForWriteW,
    qemu_SHPropStgCreate,
    qemu_SHPropStgReadMultiple,
    qemu_SHPropStgWriteMultiple,
    qemu_SHQueryUserNotificationState,
    qemu_SHRegisterDragDrop,
    qemu_SHRemoveLocalizedName,
    qemu_SHReplaceFromPropSheetExtArray,
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
    qemu_SHValidateUNC,
    qemu_SHWaitForFileToOpen,
    qemu_SHWinHelp,
    qemu_SignalFileOpen,
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

    p_SHCLSIDFromString = (void *)GetProcAddress(shell32, MAKEINTRESOURCE(147));
    p_DllGetClassObject = (void *)GetProcAddress(shell32, "DllGetClassObject");
    if (!p_DllGetClassObject)
        WINE_ERR("Failed to load shell32.DllGetClassObject.\n");

    return dll_functions;
}

#endif
