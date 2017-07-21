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
#include "shell32.h"

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
    qemu_CommandLineToArgvW,
    qemu_DllCanUnloadNow,
    qemu_DllGetClassObject,
    qemu_DllGetVersion,
    qemu_DllInstall,
    qemu_DllRegisterServer,
    qemu_DllUnregisterServer,
    qemu_DragAcceptFiles,
    qemu_DragFinish,
    qemu_DragQueryFileA,
    qemu_DragQueryFileW,
    qemu_DragQueryPoint,
    qemu_DuplicateIcon,
    qemu_ExtractIconA,
    qemu_ExtractIconW,
    qemu_ExtractVersionResource16W,
    qemu_FindExecutableA,
    qemu_FindExecutableW,
    qemu_FreeIconList,
    qemu_GetCurrentProcessExplicitAppUserModelID,
    qemu_InitNetworkAddressControl,
    qemu_IsLFNDriveA,
    qemu_IsLFNDriveW,
    qemu_OpenAs_RunDLLA,
    qemu_OpenAs_RunDLLW,
    qemu_PathYetAnotherMakeUniqueName,
    qemu_Printer_LoadIconsW,
    qemu_Printers_RegisterWindowW,
    qemu_Printers_UnregisterWindow,
    qemu_RegenerateUserEnvironment,
    qemu_SetCurrentProcessExplicitAppUserModelID,
    qemu_SHAlloc,
    qemu_SHCLSIDFromString,
    qemu_SHCoCreateInstance,
    qemu_SHCreateFileExtractIconW,
    qemu_SHCreateQueryCancelAutoPlayMoniker,
    qemu_ShellAboutA,
    qemu_ShellAboutW,
    qemu_ShellExecuteA,
    qemu_ShellExecuteExA,
    qemu_ShellExecuteExW,
    qemu_ShellExecuteW,
    qemu_SHEnumerateUnreadMailAccountsW,
    qemu_SHFree,
    qemu_SHGetFileInfoA,
    qemu_SHGetFileInfoW,
    qemu_SHGetFolderLocation,
    qemu_SHGetFolderPathA,
    qemu_SHGetFolderPathAndSubDirA,
    qemu_SHGetFolderPathAndSubDirW,
    qemu_SHGetFolderPathEx,
    qemu_SHGetFolderPathW,
    qemu_SHGetKnownFolderIDList,
    qemu_SHGetKnownFolderItem,
    qemu_SHGetKnownFolderPath,
    qemu_SHGetLocalizedName,
    qemu_SHGetMalloc,
    qemu_SHGetPropertyStoreForWindow,
    qemu_SHGetSpecialFolderLocation,
    qemu_SHGetSpecialFolderPathA,
    qemu_SHGetSpecialFolderPathW,
    qemu_SHHelpShortcuts_RunDLLA,
    qemu_SHHelpShortcuts_RunDLLW,
    qemu_SHLoadInProc,
    qemu_SHLoadNonloadedIconOverlayIdentifiers,
    qemu_SHPropStgCreate,
    qemu_SHPropStgReadMultiple,
    qemu_SHPropStgWriteMultiple,
    qemu_SHQueryUserNotificationState,
    qemu_SHSetUnreadMailCountW,
    qemu_WOWShellExecute,
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

    return dll_functions;
}

#endif
