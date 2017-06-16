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
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_CloseHandle,
    qemu_CompareStringW,
    qemu_CreateEventW,
    qemu_CreateFileW,
    qemu_ExitProcess,
    qemu_FindClose,
    qemu_FindFirstFileW,
    qemu_FormatMessageW,
    qemu_GetCPInfoExW,
    qemu_GetCurrentProcess,
    qemu_GetCurrentProcessId,
    qemu_GetCurrentThreadId,
    qemu_GetLastError,
    qemu_GetModuleHandleA,
    qemu_GetModuleHandleExA,
    qemu_GetProcAddress,
    qemu_GetStartupInfoA,
    qemu_GetStdHandle,
    qemu_GetSystemTimeAsFileTime,
    qemu_GetTickCount,
    qemu_GetVersion,
    qemu_GetVersionExA,
    qemu_GetVersionExW,
    qemu_InitializeCriticalSection,
    qemu_LoadLibraryA,
    qemu_LocalFree,
    qemu_QueryPerformanceCounter,
    qemu_SetConsoleCtrlHandler,
    qemu_SetLastError,
    qemu_SetUnhandledExceptionFilter,
    qemu_Sleep,
    qemu_TerminateProcess,
    qemu_TlsGetValue,
    qemu_UnhandledExceptionFilter,
    qemu_VerifyVersionInfoA,
    qemu_VerifyVersionInfoW,
    qemu_VirtualQuery,
    qemu_VirtualProtect,
    qemu_WriteFile,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side kernel32 wrapper.\n");
    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;
    return dll_functions;
}

#endif
