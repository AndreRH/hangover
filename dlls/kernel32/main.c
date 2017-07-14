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

#ifdef QEMU_DLL_GUEST

/* Copypyasted from Wine. */
WINBASEAPI INT WINAPI MulDiv( INT nMultiplicand, INT nMultiplier, INT nDivisor)
{
    LONGLONG ret;

    if (!nDivisor) return -1;

    /* We want to deal with a positive divisor to simplify the logic. */
    if (nDivisor < 0)
    {
        nMultiplicand = - nMultiplicand;
        nDivisor = -nDivisor;
    }

    /* If the result is positive, we "add" to round. else, we subtract to round. */
    if ( ( (nMultiplicand <  0) && (nMultiplier <  0) ) ||
         ( (nMultiplicand >= 0) && (nMultiplier >= 0) ) )
      ret = (((LONGLONG)nMultiplicand * nMultiplier) + (nDivisor/2)) / nDivisor;
    else
      ret = (((LONGLONG)nMultiplicand * nMultiplier) - (nDivisor/2)) / nDivisor;

    if ((ret > 2147483647) || (ret < -2147483647)) return -1;
    return ret;
}

#endif

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
#include "va_helper_impl.h"
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu__hread,
    qemu__hwrite,
    qemu__lclose,
    qemu__lcreat,
    qemu__llseek,
    qemu__lopen,
    qemu__lread,
    qemu__lwrite,
    qemu_AreFileApisANSI,
    qemu_BuildCommDCBA,
    qemu_BuildCommDCBAndTimeoutsA,
    qemu_BuildCommDCBAndTimeoutsW,
    qemu_BuildCommDCBW,
    qemu_CancelIo,
    qemu_CancelIoEx,
    qemu_CancelSynchronousIo,
    qemu_CheckRemoteDebuggerPresent,
    qemu_ClearCommBreak,
    qemu_ClearCommError,
    qemu_CloseHandle,
    qemu_CommConfigDialogA,
    qemu_CommConfigDialogW,
    qemu_CompareStringW,
    qemu_ContinueDebugEvent,
    qemu_CreateEventW,
    qemu_CreateFile2,
    qemu_CreateFileA,
    qemu_CreateFileW,
    qemu_DebugActiveProcess,
    qemu_DebugActiveProcessStop,
    qemu_DebugBreak,
    qemu_DebugBreakProcess,
    qemu_DebugSetProcessKillOnExit,
    qemu_DeleteFileA,
    qemu_DeleteFileW,
    qemu_DeviceIoControl,
    qemu_EscapeCommFunction,
    qemu_ExitProcess,
    qemu_ExpandEnvironmentStringsA,
    qemu_ExpandEnvironmentStringsW,
    qemu_FindClose,
    qemu_FindFirstFileA,
    qemu_FindFirstFileExA,
    qemu_FindFirstFileExW,
    qemu_FindFirstFileW,
    qemu_FindNextFileA,
    qemu_FindNextFileW,
    qemu_FlushFileBuffers,
    qemu_FormatMessageW,
    qemu_FreeEnvironmentStringsA,
    qemu_FreeEnvironmentStringsW,
    qemu_GetActiveProcessorCount,
    qemu_GetActiveProcessorGroupCount,
    qemu_GetCommandLineA,
    qemu_GetCommandLineW,
    qemu_GetCommConfig,
    qemu_GetCommMask,
    qemu_GetCommModemStatus,
    qemu_GetCommProperties,
    qemu_GetCommState,
    qemu_GetCommTimeouts,
    qemu_GetCompressedFileSizeA,
    qemu_GetCompressedFileSizeW,
    qemu_GetCPInfoExW,
    qemu_GetCurrentProcess,
    qemu_GetCurrentProcessId,
    qemu_GetCurrentThreadId,
    qemu_GetDateFormatA,
    qemu_GetDateFormatW,
    qemu_GetDefaultCommConfigA,
    qemu_GetDefaultCommConfigW,
    qemu_GetDevicePowerState,
    qemu_GetEnvironmentStringsA,
    qemu_GetEnvironmentStringsW,
    qemu_GetEnvironmentVariableA,
    qemu_GetEnvironmentVariableW,
    qemu_GetFileAttributesA,
    qemu_GetFileAttributesExA,
    qemu_GetFileAttributesExW,
    qemu_GetFileAttributesW,
    qemu_GetFileInformationByHandle,
    qemu_GetFileInformationByHandleEx,
    qemu_GetFileSize,
    qemu_GetFileSizeEx,
    qemu_GetFileTime,
    qemu_GetFileType,
    qemu_GetFinalPathNameByHandleA,
    qemu_GetFinalPathNameByHandleW,
    qemu_GetFirmwareEnvironmentVariableA,
    qemu_GetFirmwareEnvironmentVariableW,
    qemu_GetLargePageMinimum,
    qemu_GetLastError,
    qemu_GetLocalTime,
    qemu_GetModuleFileNameA,
    qemu_GetModuleFileNameW,
    qemu_GetModuleHandleA,
    qemu_GetModuleHandleExA,
    qemu_GetModuleHandleW,
    qemu_GetNativeSystemInfo,
    qemu_GetOverlappedResult,
    qemu_GetProcAddress,
    qemu_GetProcessHeap,
    qemu_GetStartupInfoA,
    qemu_GetStartupInfoW,
    qemu_GetStdHandle,
    qemu_GetSystemInfo,
    qemu_GetSystemPowerStatus,
    qemu_GetSystemTimeAsFileTime,
    qemu_GetTickCount,
    qemu_GetTimeFormatA,
    qemu_GetTimeFormatW,
    qemu_GetVersion,
    qemu_GetVersionExA,
    qemu_GetVersionExW,
    qemu_GlobalAlloc,
    qemu_GlobalFree,
    qemu_HeapAlloc,
    qemu_HeapFree,
    qemu_InitializeCriticalSection,
    qemu_IsDebuggerPresent,
    qemu_IsProcessorFeaturePresent,
    qemu_IsSystemResumeAutomatic,
    qemu_K32EnumDeviceDrivers,
    qemu_K32GetDeviceDriverBaseNameA,
    qemu_K32GetDeviceDriverBaseNameW,
    qemu_K32GetDeviceDriverFileNameA,
    qemu_K32GetDeviceDriverFileNameW,
    qemu_K32GetPerformanceInfo,
    qemu_LoadLibraryA,
    qemu_LocalFree,
    qemu_LockFile,
    qemu_LockFileEx,
    qemu_lstrcatA,
    qemu_lstrcatW,
    qemu_lstrcmpW,
    qemu_lstrcpyA,
    qemu_lstrcpynA,
    qemu_lstrcpynW,
    qemu_lstrcpyW,
    qemu_lstrlenA,
    qemu_lstrlenW,
    qemu_MultiByteToWideChar,
    qemu_OpenFile,
    qemu_OpenFileById,
    qemu_OpenVxDHandle,
    qemu_OutputDebugStringA,
    qemu_OutputDebugStringW,
    qemu_PowerClearRequest,
    qemu_PowerCreateRequest,
    qemu_PowerSetRequest,
    qemu_PurgeComm,
    qemu_QueryPerformanceCounter,
    qemu_QueryPerformanceFrequency,
    qemu_ReadFile,
    qemu_ReadFileEx,
    qemu_ReadFileScatter,
    qemu_ReplaceFileA,
    qemu_ReplaceFileW,
    qemu_RequestWakeupLatency,
    qemu_SetCommBreak,
    qemu_SetCommConfig,
    qemu_SetCommMask,
    qemu_SetCommState,
    qemu_SetCommTimeouts,
    qemu_SetConsoleCtrlHandler,
    qemu_SetDefaultCommConfigA,
    qemu_SetDefaultCommConfigW,
    qemu_SetEndOfFile,
    qemu_SetEnvironmentVariableA,
    qemu_SetEnvironmentVariableW,
    qemu_SetFileApisToANSI,
    qemu_SetFileApisToOEM,
    qemu_SetFileAttributesA,
    qemu_SetFileAttributesW,
    qemu_SetFileCompletionNotificationModes,
    qemu_SetFileInformationByHandle,
    qemu_SetFilePointer,
    qemu_SetFilePointerEx,
    qemu_SetFileTime,
    qemu_SetFileValidData,
    qemu_SetHandleCount,
    qemu_SetLastError,
    qemu_SetStdHandle,
    qemu_SetSystemPowerState,
    qemu_SetThreadExecutionState,
    qemu_SetUnhandledExceptionFilter,
    qemu_SetupComm,
    qemu_Sleep,
    qemu_TerminateProcess,
    qemu_TlsGetValue,
    qemu_TransmitCommChar,
    qemu_UnhandledExceptionFilter,
    qemu_UnlockFile,
    qemu_UnlockFileEx,
    qemu_VerifyVersionInfoA,
    qemu_VerifyVersionInfoW,
    qemu_VirtualProtect,
    qemu_VirtualQuery,
    qemu_WaitCommEvent,
    qemu_WaitForDebugEvent,
    qemu_WideCharToMultiByte,
    qemu_WriteFile,
    qemu_WriteFileEx,
    qemu_WriteFileGather,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side kernel32 wrapper.\n");
    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
