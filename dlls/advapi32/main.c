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
#include "advapi32.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_IsTextUnicode,
    qemu_RegCloseKey,
    qemu_RegConnectRegistryA,
    qemu_RegConnectRegistryW,
    qemu_RegCopyTreeA,
    qemu_RegCopyTreeW,
    qemu_RegCreateKeyA,
    qemu_RegCreateKeyExA,
    qemu_RegCreateKeyExW,
    qemu_RegCreateKeyTransactedA,
    qemu_RegCreateKeyTransactedW,
    qemu_RegCreateKeyW,
    qemu_RegDeleteKeyA,
    qemu_RegDeleteKeyExA,
    qemu_RegDeleteKeyExW,
    qemu_RegDeleteKeyValueA,
    qemu_RegDeleteKeyValueW,
    qemu_RegDeleteKeyW,
    qemu_RegDeleteTreeA,
    qemu_RegDeleteTreeW,
    qemu_RegDeleteValueA,
    qemu_RegDeleteValueW,
    qemu_RegDisablePredefinedCache,
    qemu_RegDisableReflectionKey,
    qemu_RegEnumKeyA,
    qemu_RegEnumKeyExA,
    qemu_RegEnumKeyExW,
    qemu_RegEnumKeyW,
    qemu_RegEnumValueA,
    qemu_RegEnumValueW,
    qemu_RegFlushKey,
    qemu_RegGetKeySecurity,
    qemu_RegGetValueA,
    qemu_RegGetValueW,
    qemu_RegLoadKeyA,
    qemu_RegLoadKeyW,
    qemu_RegLoadMUIStringA,
    qemu_RegLoadMUIStringW,
    qemu_RegNotifyChangeKeyValue,
    qemu_RegOpenCurrentUser,
    qemu_RegOpenKeyA,
    qemu_RegOpenKeyExA,
    qemu_RegOpenKeyExW,
    qemu_RegOpenKeyW,
    qemu_RegOpenUserClassesRoot,
    qemu_RegOverridePredefKey,
    qemu_RegQueryInfoKeyA,
    qemu_RegQueryInfoKeyW,
    qemu_RegQueryMultipleValuesA,
    qemu_RegQueryMultipleValuesW,
    qemu_RegQueryValueA,
    qemu_RegQueryValueExA,
    qemu_RegQueryValueExW,
    qemu_RegQueryValueW,
    qemu_RegReplaceKeyA,
    qemu_RegReplaceKeyW,
    qemu_RegRestoreKeyA,
    qemu_RegRestoreKeyW,
    qemu_RegSaveKeyA,
    qemu_RegSaveKeyExA,
    qemu_RegSaveKeyExW,
    qemu_RegSaveKeyW,
    qemu_RegSetKeySecurity,
    qemu_RegSetKeyValueA,
    qemu_RegSetKeyValueW,
    qemu_RegSetValueA,
    qemu_RegSetValueExA,
    qemu_RegSetValueExW,
    qemu_RegSetValueW,
    qemu_RegUnLoadKeyA,
    qemu_RegUnLoadKeyW,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side advapi32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
