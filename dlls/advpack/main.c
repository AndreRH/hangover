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

#ifdef QEMU_DLL_GUEST

#else

#endif

#include "windows-user-services.h"
#include "dll_list.h"
#include "advpack.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advpack);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_AddDelBackupEntryA,
    qemu_AddDelBackupEntryW,
    qemu_AdvInstallFileA,
    qemu_AdvInstallFileW,
    qemu_CloseINFEngine,
    qemu_DelNodeA,
    qemu_DelNodeRunDLL32A,
    qemu_DelNodeRunDLL32W,
    qemu_DelNodeW,
    qemu_DoInfInstall,
    qemu_ExecuteCabA,
    qemu_ExecuteCabW,
    qemu_ExtractFilesA,
    qemu_ExtractFilesW,
    qemu_FileSaveMarkNotExistA,
    qemu_FileSaveMarkNotExistW,
    qemu_FileSaveRestoreA,
    qemu_FileSaveRestoreOnINFA,
    qemu_FileSaveRestoreOnINFW,
    qemu_FileSaveRestoreW,
    qemu_GetVersionFromFileA,
    qemu_GetVersionFromFileExA,
    qemu_GetVersionFromFileExW,
    qemu_GetVersionFromFileW,
    qemu_IsNTAdmin,
    qemu_LaunchINFSectionA,
    qemu_LaunchINFSectionExA,
    qemu_LaunchINFSectionExW,
    qemu_LaunchINFSectionW,
    qemu_NeedReboot,
    qemu_NeedRebootInit,
    qemu_OpenINFEngineA,
    qemu_OpenINFEngineW,
    qemu_RebootCheckOnInstallA,
    qemu_RebootCheckOnInstallW,
    qemu_RegInstallA,
    qemu_RegInstallW,
    qemu_RegisterOCX,
    qemu_RegRestoreAllA,
    qemu_RegRestoreAllW,
    qemu_RegSaveRestoreA,
    qemu_RegSaveRestoreOnINFA,
    qemu_RegSaveRestoreOnINFW,
    qemu_RegSaveRestoreW,
    qemu_RunSetupCommandA,
    qemu_RunSetupCommandW,
    qemu_SetPerUserSecValuesA,
    qemu_SetPerUserSecValuesW,
    qemu_TranslateInfStringA,
    qemu_TranslateInfStringExA,
    qemu_TranslateInfStringExW,
    qemu_TranslateInfStringW,
    qemu_UserInstStubWrapperA,
    qemu_UserInstStubWrapperW,
    qemu_UserUnInstStubWrapperA,
    qemu_UserUnInstStubWrapperW,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side advpack wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
