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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <excpt.h>
#include <winternl.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_winsock2.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_kernel32.h"

struct qemu_set_callbacks
{
    struct qemu_syscall super;
    uint64_t call_entry;
    uint64_t guest_completion_cb;
    uint64_t guest_register_class_wrapper;
    uint64_t guest_load_comctl32;
};

struct qemu_GetSystemRegistryQuota
{
    struct qemu_syscall super;
    uint64_t pdwQuotaAllowed;
    uint64_t pdwQuotaUsed;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall guest_completion_cb(struct qemu_completion_cb *data)
{
    LPOVERLAPPED_COMPLETION_ROUTINE completion = (LPOVERLAPPED_COMPLETION_ROUTINE)(ULONG_PTR)data->func;
    LPWSAOVERLAPPED_COMPLETION_ROUTINE wsa_completion = (LPWSAOVERLAPPED_COMPLETION_ROUTINE)(ULONG_PTR)data->wsa_func;
    if (completion)
        completion(data->error, data->len, (OVERLAPPED *)(ULONG_PTR)data->ov);
    else
        wsa_completion(data->error, data->len, (WSAOVERLAPPED *)(ULONG_PTR)data->ov, data->flags);
    return 0;
}

#ifndef _WIN64

#define EH_UNWINDING        0x02
#define EH_EXIT_UNWIND      0x04
#define EH_NESTED_CALL      0x10

/* Copypasted and adapted from __wine_exception_handler. */
static EXCEPTION_DISPOSITION NTAPI x86_exception_handler(EXCEPTION_RECORD *record,
        void *frame, CONTEXT *context, void *pdispatcher)
{
    EXCEPTION_POINTERS ptrs;

    if (record->ExceptionFlags & (EH_UNWINDING | EH_EXIT_UNWIND | EH_NESTED_CALL))
        return ExceptionContinueSearch;

    ptrs.ExceptionRecord = record;
    ptrs.ContextRecord = context;
    switch(kernel32_UnhandledExceptionFilter( &ptrs ))
    {
        case EXCEPTION_CONTINUE_SEARCH:
            return ExceptionContinueSearch;
        case EXCEPTION_CONTINUE_EXECUTION:
            return ExceptionContinueExecution;
        case EXCEPTION_EXECUTE_HANDLER:
            break;
    }
    /* FIXME: We should unwind properly, but how do I find the unwind target? Mingw's exception frame
     * does not store it. (Wine's exception helper macros store a longjmp buffer). */
    kernel32_ExitProcess(kernel32_GetLastError());
}
#endif

static void __fastcall kernel32_call_process_main(LPTHREAD_START_ROUTINE entry)
{
#ifdef _WIN64
    __try1(kernel32_UnhandledExceptionFilter)
    {
        entry(NULL);
    }
    __except1
    {
    }
#else
    /* Don't use __try1 on 32 bit, gcc does not allocate stack space for the exception record
     * correctly. */
    NT_TIB *tib = (NT_TIB *)NtCurrentTeb();
    EXCEPTION_REGISTRATION_RECORD except;

    except.prev = tib->ExceptionList;
    except.handler = x86_exception_handler;
    tib->ExceptionList = &except;

    entry(NULL);

    tib->ExceptionList = except.prev;
#endif
    kernel32_ExitProcess(kernel32_GetLastError());
}

static BOOL __fastcall guest_register_class_wrapper(WCHAR *name)
{
    static const WCHAR comctl32W[] = {'c','o','m','c','t','l','3','2','.','d','l','l',0};
    HMODULE comctl32;
    BOOL (* WINAPI p_RegisterClassNameW)(const WCHAR *class);

    /* The user32 class tests unload comctl32.dll after user32 loads it, so don't assume
     * that RegisterClassNameW stays in the same place. */
    comctl32 = kernel32_GetModuleHandleW(comctl32W);
    if (!comctl32)
        return FALSE;
    p_RegisterClassNameW = kernel32_GetProcAddress(comctl32, "RegisterClassNameW");
    if (!p_RegisterClassNameW)
        return FALSE;

    return p_RegisterClassNameW(name);
}

static BOOL __fastcall guest_load_comctl32(void *dummy)
{
    return !!kernel32_LoadLibraryA("comctl32.dll");
}

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_set_callbacks call;
    HMODULE ntdll;
    static const WCHAR ntdllW[] = {'n','t','d','l','l',0};

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            call.super.id = QEMU_SYSCALL_ID(CALL_SET_CALLBACKS);
            call.call_entry = (ULONG_PTR)kernel32_call_process_main;
            call.guest_completion_cb = (ULONG_PTR)guest_completion_cb;
            call.guest_register_class_wrapper = (ULONG_PTR)guest_register_class_wrapper;
            call.guest_load_comctl32 = (ULONG_PTR)guest_load_comctl32;
            qemu_syscall(&call.super);

            ntdll = kernel32_GetModuleHandleW(ntdllW);
            pRtlRaiseException = (void *)kernel32_GetProcAddress(ntdll, "RtlRaiseException");
            break;
    }
    return TRUE;
}

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

WINBASEAPI BOOL WINAPI GetSystemRegistryQuota(PDWORD pdwQuotaAllowed, PDWORD pdwQuotaUsed)
{
    struct qemu_GetSystemRegistryQuota call;

    call.super.id = QEMU_SYSCALL_ID(CALL_GETSYSTEMREGISTRYQUOTA);
    call.pdwQuotaAllowed = (ULONG_PTR)pdwQuotaAllowed;
    call.pdwQuotaUsed = (ULONG_PTR)pdwQuotaUsed;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

#include <wine/debug.h>
#include <wine/unicode.h>
#include "va_helper_impl.h"
#include "callback_helper_impl.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);

const struct qemu_ops *qemu_ops;

uint64_t guest_completion_cb;
uint64_t guest_register_class_wrapper;
uint64_t guest_load_comctl32;

static void qemu_set_callbacks(struct qemu_syscall *call)
{
    struct qemu_set_callbacks *c = (struct qemu_set_callbacks *)call;
    qemu_ops->qemu_set_call_entry(c->call_entry);
    guest_completion_cb = c->guest_completion_cb;
    guest_register_class_wrapper = c->guest_register_class_wrapper;
    guest_load_comctl32 = c->guest_load_comctl32;
}

/* We cannot use the OVERLAPPED structure as a context pointer to add our data because it is passed to
 * other functions too, so we'd have to modify it in the same way all the time. The lifetime of the
 * OVERLAPPED structure is more complicated than the lifetime of the callback. */
static void CALLBACK host_completion_cb(DWORD error, DWORD len, OVERLAPPED *ov, struct callback_entry *wrapper)
{
    struct qemu_completion_cb call;

    call.func = callback_get_guest_proc(wrapper);
    call.wsa_func = 0;
    call.error = error;
    call.len = len;
    call.ov = QEMU_H2G(ov);

    WINE_TRACE("Calling guest callback 0x%lx(%x, %u, 0x%lx).\n", (unsigned long)call.func, error, len,
            (unsigned long)call.ov);
    qemu_ops->qemu_execute(QEMU_G2H(guest_completion_cb), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned.\n");
}

static void qemu_GetSystemRegistryQuota(struct qemu_syscall *call)
{
    struct qemu_GetSystemRegistryQuota *c = (struct qemu_GetSystemRegistryQuota *)call;
    WINE_TRACE("\n");
    c->super.iret = GetSystemRegistryQuota(QEMU_G2H(c->pdwQuotaAllowed), QEMU_G2H(c->pdwQuotaUsed));
}

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
    qemu_ActivateActCtx,
    qemu_AddAtomA,
    qemu_AddAtomW,
    qemu_AddConsoleAliasA,
    qemu_AddConsoleAliasW,
    qemu_AddDllDirectory,
    qemu_AddRefActCtx,
    qemu_AllocateUserPhysicalPages,
    qemu_AllocConsole,
    qemu_ApplicationRecoveryFinished,
    qemu_ApplicationRecoveryInProgress,
    qemu_AreFileApisANSI,
    qemu_AssignProcessToJobObject,
    qemu_AttachConsole,
    qemu_BackupRead,
    qemu_BackupSeek,
    qemu_BackupWrite,
    qemu_BaseFlushAppcompatCache,
    qemu_Beep,
    qemu_BeginUpdateResourceA,
    qemu_BeginUpdateResourceW,
    qemu_BindIoCompletionCallback,
    qemu_BuildCommDCBA,
    qemu_BuildCommDCBAndTimeoutsA,
    qemu_BuildCommDCBAndTimeoutsW,
    qemu_BuildCommDCBW,
    qemu_CallbackMayRunLong,
    qemu_CallNamedPipeA,
    qemu_CallNamedPipeW,
    qemu_CancelIo,
    qemu_CancelIoEx,
    qemu_CancelSynchronousIo,
    qemu_CancelTimerQueueTimer,
    qemu_CancelWaitableTimer,
    qemu_ChangeTimerQueueTimer,
    qemu_CheckNameLegalDOS8Dot3A,
    qemu_CheckNameLegalDOS8Dot3W,
    qemu_CheckRemoteDebuggerPresent,
    qemu_ClearCommBreak,
    qemu_ClearCommError,
    qemu_CloseConsoleHandle,
    qemu_CloseHandle,
    qemu_CloseProfileUserMapping,
    qemu_CmdBatNotification,
    qemu_CommConfigDialogA,
    qemu_CommConfigDialogW,
    qemu_CompareFileTime,
    qemu_CompareStringA,
    qemu_CompareStringEx,
    qemu_CompareStringOrdinal,
    qemu_CompareStringW,
    qemu_ConnectNamedPipe,
    qemu_ContinueDebugEvent,
    qemu_ConvertDefaultLocale,
    qemu_ConvertFiberToThread,
    qemu_ConvertThreadToFiber,
    qemu_ConvertThreadToFiberEx,
    qemu_ConvertToGlobalHandle,
    qemu_CopyFileA,
    qemu_CopyFileExA,
    qemu_CopyFileExW,
    qemu_CopyFileW,
    qemu_CreateActCtxA,
    qemu_CreateActCtxW,
    qemu_CreateConsoleScreenBuffer,
    qemu_CreateDirectoryA,
    qemu_CreateDirectoryExA,
    qemu_CreateDirectoryExW,
    qemu_CreateDirectoryW,
    qemu_CreateEventA,
    qemu_CreateEventEx,
    qemu_CreateEventEx,
    qemu_CreateEventW,
    qemu_CreateFiber,
    qemu_CreateFiberEx,
    qemu_CreateFile2,
    qemu_CreateFileA,
    qemu_CreateFileMappingA,
    qemu_CreateFileMappingW,
    qemu_CreateFileW,
    qemu_CreateHardLinkA,
    qemu_CreateHardLinkTransactedA,
    qemu_CreateHardLinkTransactedW,
    qemu_CreateHardLinkW,
    qemu_CreateIoCompletionPort,
    qemu_CreateJobObjectA,
    qemu_CreateJobObjectW,
    qemu_CreateMailslotA,
    qemu_CreateMailslotW,
    qemu_CreateMemoryResourceNotification,
    qemu_CreateMutexA,
    qemu_CreateMutexExA,
    qemu_CreateMutexExW,
    qemu_CreateMutexW,
    qemu_CreateNamedPipeA,
    qemu_CreateNamedPipeW,
    qemu_CreatePipe,
    qemu_CreateProcessA,
    qemu_CreateProcessW,
    qemu_CreateRemoteThread,
    qemu_CreateSemaphoreA,
    qemu_CreateSemaphoreExA,
    qemu_CreateSemaphoreExW,
    qemu_CreateSemaphoreW,
    qemu_CreateSocketHandle,
    qemu_CreateSymbolicLinkA,
    qemu_CreateSymbolicLinkW,
    qemu_CreateTapePartition,
    qemu_CreateThread,
    qemu_CreateThreadpool,
    qemu_CreateThreadpoolCleanupGroup,
    qemu_CreateThreadpoolIo,
    qemu_CreateThreadpoolTimer,
    qemu_CreateThreadpoolWait,
    qemu_CreateThreadpoolWork,
    qemu_CreateTimerQueue,
    qemu_CreateTimerQueueTimer,
    qemu_CreateToolhelp32Snapshot,
    qemu_CreateWaitableTimerA,
    qemu_CreateWaitableTimerExA,
    qemu_CreateWaitableTimerExW,
    qemu_CreateWaitableTimerW,
    qemu_DeactivateActCtx,
    qemu_DebugActiveProcess,
    qemu_DebugActiveProcessStop,
    qemu_DebugBreak,
    qemu_DebugBreakProcess,
    qemu_DebugSetProcessKillOnExit,
    qemu_DefineDosDeviceA,
    qemu_DefineDosDeviceW,
    qemu_DelayLoadFailureHook,
    qemu_DeleteAtom,
    qemu_DeleteFiber,
    qemu_DeleteFileA,
    qemu_DeleteFileW,
    qemu_DeleteProcThreadAttributeList,
    qemu_DeleteTimerQueue,
    qemu_DeleteTimerQueueEx,
    qemu_DeleteTimerQueueTimer,
    qemu_DeleteVolumeMountPointA,
    qemu_DeleteVolumeMountPointW,
    qemu_DeviceIoControl,
    qemu_DisableThreadLibraryCalls,
    qemu_DisconnectNamedPipe,
    qemu_DnsHostnameToComputerNameA,
    qemu_DnsHostnameToComputerNameW,
    qemu_DosDateTimeToFileTime,
    qemu_DuplicateConsoleHandle,
    qemu_DuplicateHandle,
    qemu_EndUpdateResourceA,
    qemu_EndUpdateResourceW,
    qemu_EnumCalendarInfoA,
    qemu_EnumCalendarInfoExA,
    qemu_EnumCalendarInfoExEx,
    qemu_EnumCalendarInfoExW,
    qemu_EnumCalendarInfoW,
    qemu_EnumDateFormatsA,
    qemu_EnumDateFormatsExA,
    qemu_EnumDateFormatsExEx,
    qemu_EnumDateFormatsExW,
    qemu_EnumDateFormatsW,
    qemu_EnumLanguageGroupLocalesA,
    qemu_EnumLanguageGroupLocalesW,
    qemu_EnumResourceLanguagesA,
    qemu_EnumResourceLanguagesExA,
    qemu_EnumResourceLanguagesExW,
    qemu_EnumResourceLanguagesW,
    qemu_EnumResourceNamesA,
    qemu_EnumResourceNamesW,
    qemu_EnumResourceTypesA,
    qemu_EnumResourceTypesW,
    qemu_EnumSystemCodePagesA,
    qemu_EnumSystemCodePagesW,
    qemu_EnumSystemGeoID,
    qemu_EnumSystemLanguageGroupsA,
    qemu_EnumSystemLanguageGroupsW,
    qemu_EnumSystemLocalesA,
    qemu_EnumSystemLocalesEx,
    qemu_EnumSystemLocalesW,
    qemu_EnumTimeFormatsA,
    qemu_EnumTimeFormatsEx,
    qemu_EnumTimeFormatsW,
    qemu_EnumUILanguagesA,
    qemu_EnumUILanguagesW,
    qemu_EraseTape,
    qemu_EscapeCommFunction,
    qemu_ExitProcess,
    qemu_ExitThread,
    qemu_ExpandEnvironmentStringsA,
    qemu_ExpandEnvironmentStringsW,
    qemu_ExpungeConsoleCommandHistoryA,
    qemu_ExpungeConsoleCommandHistoryW,
    qemu_FatalAppExitA,
    qemu_FatalAppExitW,
    qemu_FatalExit,
    qemu_FileTimeToDosDateTime,
    qemu_FileTimeToLocalFileTime,
    qemu_FileTimeToSystemTime,
    qemu_FillConsoleOutputAttribute,
    qemu_FillConsoleOutputCharacterA,
    qemu_FillConsoleOutputCharacterW,
    qemu_FindActCtxSectionGuid,
    qemu_FindActCtxSectionString,
    qemu_FindActCtxSectionString,
    qemu_FindAtomA,
    qemu_FindAtomW,
    qemu_FindClose,
    qemu_FindCloseChangeNotification,
    qemu_FindFirstChangeNotificationA,
    qemu_FindFirstChangeNotificationW,
    qemu_FindFirstFileA,
    qemu_FindFirstFileExA,
    qemu_FindFirstFileExW,
    qemu_FindFirstFileW,
    qemu_FindFirstVolumeA,
    qemu_FindFirstVolumeMountPointA,
    qemu_FindFirstVolumeMountPointW,
    qemu_FindFirstVolumeW,
    qemu_FindNextChangeNotification,
    qemu_FindNextFileA,
    qemu_FindNextFileW,
    qemu_FindNextVolumeA,
    qemu_FindNextVolumeW,
    qemu_FindResourceA,
    qemu_FindResourceExA,
    qemu_FindResourceExW,
    qemu_FindResourceW,
    qemu_FindVolumeClose,
    qemu_FindVolumeMountPointClose,
    qemu_FlsAlloc,
    qemu_FlsFree,
    qemu_FlsGetValue,
    qemu_FlsSetValue,
    qemu_FlushConsoleInputBuffer,
    qemu_FlushFileBuffers,
    qemu_FlushInstructionCache,
    qemu_FlushProcessWriteBuffers,
    qemu_FlushViewOfFile,
    qemu_FoldStringA,
    qemu_FoldStringW,
    qemu_FormatMessage,
    qemu_FormatMessage,
    qemu_FreeConsole,
    qemu_FreeEnvironmentStringsA,
    qemu_FreeEnvironmentStringsW,
    qemu_FreeLibrary,
    qemu_FreeLibraryAndExitThread,
    qemu_FreeResource,
    qemu_FreeUserPhysicalPages,
    qemu_GenerateConsoleCtrlEvent,
    qemu_GetACP,
    qemu_GetActiveProcessorCount,
    qemu_GetActiveProcessorGroupCount,
    qemu_GetAtomNameA,
    qemu_GetAtomNameW,
    qemu_GetBinaryTypeA,
    qemu_GetBinaryTypeW,
    qemu_GetCalendarInfoA,
    qemu_GetCalendarInfoEx,
    qemu_GetCalendarInfoW,
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
    qemu_GetComputerNameA,
    qemu_GetComputerNameExA,
    qemu_GetComputerNameExW,
    qemu_GetComputerNameW,
    qemu_GetConsoleAliasesLengthA,
    qemu_GetConsoleAliasesLengthW,
    qemu_GetConsoleAliasExesLengthA,
    qemu_GetConsoleAliasExesLengthW,
    qemu_GetConsoleAliasW,
    qemu_GetConsoleCommandHistoryA,
    qemu_GetConsoleCommandHistoryLengthA,
    qemu_GetConsoleCommandHistoryLengthW,
    qemu_GetConsoleCommandHistoryW,
    qemu_GetConsoleCP,
    qemu_GetConsoleCursorInfo,
    qemu_GetConsoleDisplayMode,
    qemu_GetConsoleFontInfo,
    qemu_GetConsoleFontSize,
    qemu_GetConsoleInputExeNameA,
    qemu_GetConsoleInputExeNameW,
    qemu_GetConsoleInputWaitHandle,
    qemu_GetConsoleKeyboardLayoutNameA,
    qemu_GetConsoleKeyboardLayoutNameW,
    qemu_GetConsoleMode,
    qemu_GetConsoleOutputCP,
    qemu_GetConsoleProcessList,
    qemu_GetConsoleScreenBufferInfo,
    qemu_GetConsoleScreenBufferInfoEx,
    qemu_GetConsoleTitleA,
    qemu_GetConsoleTitleW,
    qemu_GetConsoleWindow,
    qemu_GetCPInfo,
    qemu_GetCPInfoExA,
    qemu_GetCPInfoExW,
    qemu_GetCurrencyFormatA,
    qemu_GetCurrencyFormatW,
    qemu_GetCurrentActCtx,
    qemu_GetCurrentConsoleFont,
    qemu_GetCurrentDirectoryA,
    qemu_GetCurrentDirectoryW,
    qemu_GetCurrentPackageFamilyName,
    qemu_GetCurrentPackageFullName,
    qemu_GetCurrentPackageId,
    qemu_GetCurrentProcess,
    qemu_GetCurrentProcessId,
    qemu_GetCurrentThread,
    qemu_GetDateFormatA,
    qemu_GetDateFormatEx,
    qemu_GetDateFormatW,
    qemu_GetDaylightFlag,
    qemu_GetDefaultCommConfigA,
    qemu_GetDefaultCommConfigW,
    qemu_GetDevicePowerState,
    qemu_GetDiskFreeSpaceA,
    qemu_GetDiskFreeSpaceExA,
    qemu_GetDiskFreeSpaceExW,
    qemu_GetDiskFreeSpaceW,
    qemu_GetDllDirectoryA,
    qemu_GetDllDirectoryW,
    qemu_GetDriveTypeA,
    qemu_GetDriveTypeW,
    qemu_GetDynamicTimeZoneInformation,
    qemu_GetEnvironmentStringsA,
    qemu_GetEnvironmentStringsW,
    qemu_GetEnvironmentVariableA,
    qemu_GetEnvironmentVariableW,
    qemu_GetErrorMode,
    qemu_GetExitCodeProcess,
    qemu_GetExitCodeThread,
    qemu_GetExpandedNameA,
    qemu_GetExpandedNameW,
    qemu_GetFileAttributesA,
    qemu_GetFileAttributesExA,
    qemu_GetFileAttributesExW,
    qemu_GetFileAttributesW,
    qemu_GetFileInformationByHandle,
    qemu_GetFileInformationByHandleEx,
    qemu_GetFileMUIInfo,
    qemu_GetFileMUIPath,
    qemu_GetFileSize,
    qemu_GetFileSizeEx,
    qemu_GetFileTime,
    qemu_GetFileType,
    qemu_GetFinalPathNameByHandleA,
    qemu_GetFinalPathNameByHandleW,
    qemu_GetFirmwareEnvironmentVariableA,
    qemu_GetFirmwareEnvironmentVariableW,
    qemu_GetFullPathNameA,
    qemu_GetFullPathNameW,
    qemu_GetGeoInfoA,
    qemu_GetGeoInfoW,
    qemu_GetHandleContext,
    qemu_GetHandleInformation,
    qemu_GetLargePageMinimum,
    qemu_GetLargestConsoleWindowSize,
    qemu_GetLocaleInfoA,
    qemu_GetLocaleInfoEx,
    qemu_GetLocaleInfoW,
    qemu_GetLocalTime,
    qemu_GetLogicalDrives,
    qemu_GetLogicalDriveStringsA,
    qemu_GetLogicalDriveStringsW,
    qemu_GetLogicalProcessorInformation,
    qemu_GetLogicalProcessorInformationEx,
    qemu_GetLongPathNameA,
    qemu_GetLongPathNameW,
    qemu_GetMailslotInfo,
    qemu_GetModuleFileNameA,
    qemu_GetModuleFileNameW,
    qemu_GetModuleHandleA,
    qemu_GetModuleHandleExA,
    qemu_GetModuleHandleExW,
    qemu_GetModuleHandleW,
    qemu_GetNamedPipeHandleStateA,
    qemu_GetNamedPipeHandleStateW,
    qemu_GetNamedPipeInfo,
    qemu_GetNativeSystemInfo,
    qemu_GetNumaAvailableMemoryNode,
    qemu_GetNumaHighestNodeNumber,
    qemu_GetNumaNodeProcessorMask,
    qemu_GetNumaProcessorNode,
    qemu_GetNumberFormatA,
    qemu_GetNumberFormatEx,
    qemu_GetNumberFormatW,
    qemu_GetNumberOfConsoleFonts,
    qemu_GetNumberOfConsoleInputEvents,
    qemu_GetNumberOfConsoleMouseButtons,
    qemu_GetOEMCP,
    qemu_GetOverlappedResult,
    qemu_GetPackageFullName,
    qemu_GetPhysicallyInstalledSystemMemory,
    qemu_GetPriorityClass,
    qemu_GetPrivateProfileIntA,
    qemu_GetPrivateProfileIntW,
    qemu_GetPrivateProfileSectionA,
    qemu_GetPrivateProfileSectionNamesA,
    qemu_GetPrivateProfileSectionNamesW,
    qemu_GetPrivateProfileSectionW,
    qemu_GetPrivateProfileStringA,
    qemu_GetPrivateProfileStringW,
    qemu_GetPrivateProfileStructA,
    qemu_GetPrivateProfileStructW,
    qemu_GetProcAddress,
    qemu_GetProcessAffinityMask,
    qemu_GetProcessDEPPolicy,
    qemu_GetProcessFlags,
    qemu_GetProcessHandleCount,
    qemu_GetProcessHeap,
    qemu_GetProcessHeaps,
    qemu_GetProcessId,
    qemu_GetProcessIdOfThread,
    qemu_GetProcessIoCounters,
    qemu_GetProcessPriorityBoost,
    qemu_GetProcessShutdownParameters,
    qemu_GetProcessTimes,
    qemu_GetProcessVersion,
    qemu_GetProcessWorkingSetSize,
    qemu_GetProcessWorkingSetSizeEx,
    qemu_GetProductInfo,
    qemu_GetProfileIntA,
    qemu_GetProfileIntW,
    qemu_GetProfileSectionA,
    qemu_GetProfileSectionW,
    qemu_GetProfileStringA,
    qemu_GetProfileStringW,
    qemu_GetQueuedCompletionStatus,
    qemu_GetShortPathNameA,
    qemu_GetShortPathNameW,
    qemu_GetStartupInfoA,
    qemu_GetStartupInfoW,
    qemu_GetStdHandle,
    qemu_GetStringTypeA,
    qemu_GetStringTypeExA,
    qemu_GetStringTypeExW,
    qemu_GetStringTypeW,
    qemu_GetSystemDefaultLangID,
    qemu_GetSystemDefaultLCID,
    qemu_GetSystemDefaultLocaleName,
    qemu_GetSystemDefaultUILanguage,
    qemu_GetSystemDEPPolicy,
    qemu_GetSystemDirectoryA,
    qemu_GetSystemDirectoryW,
    qemu_GetSystemFileCacheSize,
    qemu_GetSystemFirmwareTable,
    qemu_GetSystemInfo,
    qemu_GetSystemPowerStatus,
    qemu_GetSystemPreferredUILanguages,
    qemu_GetSystemRegistryQuota,
    qemu_GetSystemTime,
    qemu_GetSystemTimeAdjustment,
    qemu_GetSystemTimeAsFileTime,
    qemu_GetSystemTimePreciseAsFileTime,
    qemu_GetSystemTimes,
    qemu_GetSystemWindowsDirectoryA,
    qemu_GetSystemWindowsDirectoryW,
    qemu_GetSystemWow64DirectoryA,
    qemu_GetSystemWow64DirectoryW,
    qemu_GetTapeParameters,
    qemu_GetTapePosition,
    qemu_GetTapeStatus,
    qemu_GetTempFileNameA,
    qemu_GetTempFileNameW,
    qemu_GetTempPathA,
    qemu_GetTempPathW,
    qemu_GetThreadContext,
    qemu_GetThreadErrorMode,
    qemu_GetThreadGroupAffinity,
    qemu_GetThreadId,
    qemu_GetThreadIOPendingFlag,
    qemu_GetThreadLocale,
    qemu_GetThreadPreferredUILanguages,
    qemu_GetThreadPriority,
    qemu_GetThreadPriorityBoost,
    qemu_GetThreadSelectorEntry,
    qemu_GetThreadTimes,
    qemu_GetThreadUILanguage,
    qemu_GetTickCount,
    qemu_GetTickCount64,
    qemu_GetTimeFormatA,
    qemu_GetTimeFormatEx,
    qemu_GetTimeFormatW,
    qemu_GetTimeZoneInformation,
    qemu_GetTimeZoneInformationForYear,
    qemu_GetUserDefaultLangID,
    qemu_GetUserDefaultLCID,
    qemu_GetUserDefaultLocaleName,
    qemu_GetUserDefaultUILanguage,
    qemu_GetUserGeoID,
    qemu_GetUserPreferredUILanguages,
    qemu_GetVersion,
    qemu_GetVersionExA,
    qemu_GetVersionExW,
    qemu_GetVolumeInformationA,
    qemu_GetVolumeInformationByHandleW,
    qemu_GetVolumeInformationW,
    qemu_GetVolumeNameForVolumeMountPointA,
    qemu_GetVolumeNameForVolumeMountPointW,
    qemu_GetVolumePathNameA,
    qemu_GetVolumePathNamesForVolumeNameA,
    qemu_GetVolumePathNamesForVolumeNameW,
    qemu_GetVolumePathNameW,
    qemu_GetWindowsDirectoryA,
    qemu_GetWindowsDirectoryW,
    qemu_GetWriteWatch,
    qemu_GlobalAddAtomA,
    qemu_GlobalAddAtomW,
    qemu_GlobalAlloc,
    qemu_GlobalCompact,
    qemu_GlobalDeleteAtom,
    qemu_GlobalFindAtomA,
    qemu_GlobalFindAtomW,
    qemu_GlobalFix,
    qemu_GlobalFlags,
    qemu_GlobalFree,
    qemu_GlobalGetAtomNameA,
    qemu_GlobalGetAtomNameW,
    qemu_GlobalHandle,
    qemu_GlobalLock,
    qemu_GlobalMemoryStatus,
    qemu_GlobalMemoryStatusEx,
    qemu_GlobalReAlloc,
    qemu_GlobalSize,
    qemu_GlobalUnfix,
    qemu_GlobalUnlock,
    qemu_GlobalUnWire,
    qemu_GlobalWire,
    qemu_Heap32ListFirst,
    qemu_HeapAlloc,
    qemu_HeapCompact,
    qemu_HeapCreate,
    qemu_HeapDestroy,
    qemu_HeapFree,
    qemu_HeapLock,
    qemu_HeapQueryInformation,
    qemu_HeapReAlloc,
    qemu_HeapSetInformation,
    qemu_HeapSize,
    qemu_HeapUnlock,
    qemu_HeapValidate,
    qemu_HeapWalk,
    qemu_IdnToAscii,
    qemu_IdnToNameprepUnicode,
    qemu_IdnToUnicode,
    qemu_InitAtomTable,
    qemu_InitializeProcThreadAttributeList,
    qemu_InitOnceBeginInitialize,
    qemu_InitOnceComplete,
    qemu_InitOnceExecuteOnce,
    qemu_InvalidateNLSCache,
    qemu_IsBadCodePtr,
    qemu_IsBadHugeReadPtr,
    qemu_IsBadHugeWritePtr,
    qemu_IsBadReadPtr,
    qemu_IsBadStringPtrA,
    qemu_IsBadStringPtrW,
    qemu_IsBadWritePtr,
    qemu_IsDBCSLeadByte,
    qemu_IsDBCSLeadByteEx,
    qemu_IsDebuggerPresent,
    qemu_IsNormalizedString,
    qemu_IsProcessInJob,
    qemu_IsProcessorFeaturePresent,
    qemu_IsSystemResumeAutomatic,
    qemu_IsThreadAFiber,
    qemu_IsValidCodePage,
    qemu_IsValidLanguageGroup,
    qemu_IsValidLocale,
    qemu_IsValidLocaleName,
    qemu_IsWow64Process,
    qemu_K32EmptyWorkingSet,
    qemu_K32EnumDeviceDrivers,
    qemu_K32EnumPageFilesA,
    qemu_K32EnumPageFilesW,
    qemu_K32EnumProcesses,
    qemu_K32EnumProcessModules,
    qemu_K32EnumProcessModulesEx,
    qemu_K32GetDeviceDriverBaseNameA,
    qemu_K32GetDeviceDriverBaseNameW,
    qemu_K32GetDeviceDriverFileNameA,
    qemu_K32GetDeviceDriverFileNameW,
    qemu_K32GetMappedFileNameA,
    qemu_K32GetMappedFileNameW,
    qemu_K32GetModuleBaseNameA,
    qemu_K32GetModuleBaseNameW,
    qemu_K32GetModuleFileNameExA,
    qemu_K32GetModuleFileNameExW,
    qemu_K32GetModuleInformation,
    qemu_K32GetPerformanceInfo,
    qemu_K32GetProcessImageFileNameA,
    qemu_K32GetProcessImageFileNameW,
    qemu_K32GetProcessMemoryInfo,
    qemu_K32GetWsChanges,
    qemu_K32InitializeProcessForWsWatch,
    qemu_K32QueryWorkingSet,
    qemu_K32QueryWorkingSetEx,
    qemu_LCIDToLocaleName,
    qemu_LCMapStringA,
    qemu_LCMapStringEx,
    qemu_LCMapStringW,
    qemu_LoadLibraryA,
    qemu_LoadLibraryExA,
    qemu_LoadLibraryExW,
    qemu_LoadLibraryW,
    qemu_LoadModule,
    qemu_LoadResource,
    qemu_LocalAlloc,
    qemu_LocalCompact,
    qemu_LocaleNameToLCID,
    qemu_LocalFileTimeToFileTime,
    qemu_LocalFlags,
    qemu_LocalFree,
    qemu_LocalHandle,
    qemu_LocalLock,
    qemu_LocalReAlloc,
    qemu_LocalShrink,
    qemu_LocalSize,
    qemu_LocalUnlock,
    qemu_LockFile,
    qemu_LockFileEx,
    qemu_LockResource,
    qemu_lstrcatA,
    qemu_lstrcatW,
    qemu_lstrcmpA,
    qemu_lstrcmpiA,
    qemu_lstrcmpiW,
    qemu_lstrcmpW,
    qemu_lstrcpyA,
    qemu_lstrcpynA,
    qemu_lstrcpynW,
    qemu_lstrcpyW,
    qemu_lstrlenA,
    qemu_lstrlenW,
    qemu_LZClose,
    qemu_LZCopy,
    qemu_LZDone,
    qemu_LZInit,
    qemu_LZOpenFileA,
    qemu_LZOpenFileW,
    qemu_LZRead,
    qemu_LZSeek,
    qemu_LZStart,
    qemu_MakeCriticalSectionGlobal,
    qemu_MapViewOfFile,
    qemu_MapViewOfFileEx,
    qemu_Module32Iteration,
    qemu_Module32Iteration,
    qemu_Module32Iteration,
    qemu_Module32Iteration,
    qemu_MoveFileA,
    qemu_MoveFileExA,
    qemu_MoveFileExW,
    qemu_MoveFileW,
    qemu_MoveFileWithProgressA,
    qemu_MoveFileWithProgressW,
    qemu_MultiByteToWideChar,
    qemu_NeedCurrentDirectoryForExePathA,
    qemu_NeedCurrentDirectoryForExePathW,
    qemu_NormalizeString,
    qemu_OpenConsoleW,
    qemu_OpenEventA,
    qemu_OpenEventW,
    qemu_OpenFile,
    qemu_OpenFileById,
    qemu_OpenFileMappingA,
    qemu_OpenFileMappingW,
    qemu_OpenJobObjectA,
    qemu_OpenJobObjectW,
    qemu_OpenMutexA,
    qemu_OpenMutexW,
    qemu_OpenProcess,
    qemu_OpenProfileUserMapping,
    qemu_OpenSemaphoreA,
    qemu_OpenSemaphoreW,
    qemu_OpenThread,
    qemu_OpenVxDHandle,
    qemu_OpenWaitableTimerA,
    qemu_OpenWaitableTimerW,
    qemu_OutputDebugStringA,
    qemu_OutputDebugStringW,
    qemu_PeekConsoleInputA,
    qemu_PeekConsoleInputW,
    qemu_PeekNamedPipe,
    qemu_PostQueuedCompletionStatus,
    qemu_PowerClearRequest,
    qemu_PowerCreateRequest,
    qemu_PowerSetRequest,
    qemu_PrepareTape,
    qemu_Process32First,
    qemu_Process32FirstW,
    qemu_Process32Next,
    qemu_Process32NextW,
    qemu_ProcessIdToSessionId,
    qemu_PulseEvent,
    qemu_PurgeComm,
    qemu_QueryActCtxW,
    qemu_QueryDosDeviceA,
    qemu_QueryDosDeviceW,
    qemu_QueryFullProcessImageNameA,
    qemu_QueryFullProcessImageNameW,
    qemu_QueryInformationJobObject,
    qemu_QueryMemoryResourceNotification,
    qemu_QueryPerformanceCounter,
    qemu_QueryPerformanceFrequency,
    qemu_QueryThreadCycleTime,
    qemu_QueryUnbiasedInterruptTime,
    qemu_QueueUserAPC,
    qemu_QueueUserWorkItem,
    qemu_RaiseException,
    qemu_ReadConsoleA,
    qemu_ReadConsoleInputA,
    qemu_ReadConsoleInputW,
    qemu_ReadConsoleOutputA,
    qemu_ReadConsoleOutputAttribute,
    qemu_ReadConsoleOutputCharacterA,
    qemu_ReadConsoleOutputCharacterW,
    qemu_ReadConsoleOutputW,
    qemu_ReadConsoleW,
    qemu_ReadDirectoryChangesW,
    qemu_ReadFile,
    qemu_ReadFileEx,
    qemu_ReadFileScatter,
    qemu_ReadProcessMemory,
    qemu_RegisterApplicationRecoveryCallback,
    qemu_RegisterApplicationRestart,
    qemu_RegisterServiceProcess,
    qemu_RegisterWaitForSingleObject,
    qemu_RegisterWaitForSingleObjectEx,
    qemu_ReinitializeCriticalSection,
    qemu_ReleaseActCtx,
    qemu_ReleaseMutex,
    qemu_ReleaseSemaphore,
    qemu_RemoveDirectoryA,
    qemu_RemoveDirectoryW,
    qemu_RemoveDllDirectory,
    qemu_ReplaceFileA,
    qemu_ReplaceFileW,
    qemu_RequestWakeupLatency,
    qemu_ResetEvent,
    qemu_ResetWriteWatch,
    qemu_ResolveLocaleName,
    qemu_ResumeThread,
    qemu_ScrollConsoleScreenBufferA,
    qemu_ScrollConsoleScreenBufferW,
    qemu_SearchPathA,
    qemu_SearchPathW,
    qemu_set_callbacks,
    qemu_SetCalendarInfoA,
    qemu_SetCalendarInfoW,
    qemu_SetCommBreak,
    qemu_SetCommConfig,
    qemu_SetCommMask,
    qemu_SetCommState,
    qemu_SetCommTimeouts,
    qemu_SetComputerNameA,
    qemu_SetComputerNameExA,
    qemu_SetComputerNameExW,
    qemu_SetComputerNameW,
    qemu_SetConsoleActiveScreenBuffer,
    qemu_SetConsoleCP,
    qemu_SetConsoleCtrlHandler,
    qemu_SetConsoleCursorInfo,
    qemu_SetConsoleCursorPosition,
    qemu_SetConsoleDisplayMode,
    qemu_SetConsoleFont,
    qemu_SetConsoleIcon,
    qemu_SetConsoleInputExeNameA,
    qemu_SetConsoleInputExeNameW,
    qemu_SetConsoleKeyShortcuts,
    qemu_SetConsoleMode,
    qemu_SetConsoleOutputCP,
    qemu_SetConsoleScreenBufferInfoEx,
    qemu_SetConsoleScreenBufferSize,
    qemu_SetConsoleTextAttribute,
    qemu_SetConsoleTitleA,
    qemu_SetConsoleTitleW,
    qemu_SetConsoleWindowInfo,
    qemu_SetCPGlobal,
    qemu_SetCurrentConsoleFontEx,
    qemu_SetCurrentDirectoryA,
    qemu_SetCurrentDirectoryW,
    qemu_SetDefaultCommConfigA,
    qemu_SetDefaultCommConfigW,
    qemu_SetDefaultDllDirectories,
    qemu_SetDllDirectoryA,
    qemu_SetDllDirectoryW,
    qemu_SetEndOfFile,
    qemu_SetEnvironmentVariableA,
    qemu_SetEnvironmentVariableW,
    qemu_SetErrorMode,
    qemu_SetEvent,
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
    qemu_SetHandleContext,
    qemu_SetHandleCount,
    qemu_SetHandleInformation,
    qemu_SetInformationJobObject,
    qemu_SetLocaleInfoA,
    qemu_SetLocaleInfoW,
    qemu_SetLocalTime,
    qemu_SetMailslotInfo,
    qemu_SetNamedPipeHandleState,
    qemu_SetPriorityClass,
    qemu_SetProcessAffinityMask,
    qemu_SetProcessDEPPolicy,
    qemu_SetProcessPriorityBoost,
    qemu_SetProcessShutdownParameters,
    qemu_SetProcessWorkingSetSize,
    qemu_SetSearchPathMode,
    qemu_SetStdHandle,
    qemu_SetSystemFileCacheSize,
    qemu_SetSystemPowerState,
    qemu_SetSystemTime,
    qemu_SetSystemTimeAdjustment,
    qemu_SetTapeParameters,
    qemu_SetTapePosition,
    qemu_SetTermsrvAppInstallMode,
    qemu_SetThreadAffinityMask,
    qemu_SetThreadContext,
    qemu_SetThreadErrorMode,
    qemu_SetThreadExecutionState,
    qemu_SetThreadGroupAffinity,
    qemu_SetThreadIdealProcessor,
    qemu_SetThreadIdealProcessorEx,
    qemu_SetThreadLocale,
    qemu_SetThreadpoolTimer,
    qemu_SetThreadpoolWait,
    qemu_SetThreadPreferredUILanguages,
    qemu_SetThreadPriority,
    qemu_SetThreadPriorityBoost,
    qemu_SetThreadStackGuarantee,
    qemu_SetThreadUILanguage,
    qemu_SetTimeZoneInformation,
    qemu_SetUnhandledExceptionFilter,
    qemu_SetupComm,
    qemu_SetUserGeoID,
    qemu_SetVolumeLabelA,
    qemu_SetVolumeLabelW,
    qemu_SetVolumeMountPointA,
    qemu_SetVolumeMountPointW,
    qemu_SetWaitableTimer,
    qemu_SetWaitableTimerEx,
    qemu_SignalObjectAndWait,
    qemu_SizeofResource,
    qemu_Sleep,
    qemu_SleepConditionVariableSRW,
    qemu_SleepEx,
    qemu_SuspendThread,
    qemu_SwitchToFiber,
    qemu_SwitchToThread,
    qemu_SystemTimeToFileTime,
    qemu_SystemTimeToTzSpecificLocalTime,
    qemu_TerminateJobObject,
    qemu_TerminateProcess,
    qemu_TerminateThread,
    qemu_TermsrvAppInstallMode,
    qemu_Thread32First,
    qemu_Thread32Next,
    qemu_TlsAlloc,
    qemu_TlsFree,
    qemu_TlsGetValue,
    qemu_TlsSetValue,
    qemu_Toolhelp32ReadProcessMemory,
    qemu_TransactNamedPipe,
    qemu_TransmitCommChar,
    qemu_TrySubmitThreadpoolCallback,
    qemu_TzSpecificLocalTimeToSystemTime,
    qemu_UnhandledExceptionFilter,
    qemu_UnlockFile,
    qemu_UnlockFileEx,
    qemu_UnmapViewOfFile,
    qemu_UnregisterApplicationRestart,
    qemu_UnregisterWait,
    qemu_UnregisterWaitEx,
    qemu_UpdateProcThreadAttribute,
    qemu_UpdateResourceA,
    qemu_UpdateResourceW,
    qemu_VerifyConsoleIoHandle,
    qemu_VerifyVersionInfoA,
    qemu_VerifyVersionInfoW,
    qemu_VerLanguageNameA,
    qemu_VerLanguageNameW,
    qemu_VirtualAlloc,
    qemu_VirtualAllocEx,
    qemu_VirtualFree,
    qemu_VirtualFreeEx,
    qemu_VirtualLock,
    qemu_VirtualProtect,
    qemu_VirtualProtectEx,
    qemu_VirtualQuery,
    qemu_VirtualQueryEx,
    qemu_VirtualUnlock,
    qemu_WaitCommEvent,
    qemu_WaitForDebugEvent,
    qemu_WaitForMultipleObjects,
    qemu_WaitForMultipleObjectsEx,
    qemu_WaitForSingleObject,
    qemu_WaitForSingleObjectEx,
    qemu_WaitNamedPipeA,
    qemu_WaitNamedPipeW,
    qemu_WerRegisterFile,
    qemu_WerRegisterMemoryBlock,
    qemu_WerRegisterRuntimeExceptionModule,
    qemu_WerSetFlags,
    qemu_WerUnregisterMemoryBlock,
    qemu_WideCharToMultiByte,
    qemu_wine_get_dos_file_name,
    qemu_wine_get_unix_file_name,
    qemu_WinExec,
    qemu_Wow64DisableWow64FsRedirection,
    qemu_Wow64EnableWow64FsRedirection,
    qemu_Wow64RevertWow64FsRedirection,
    qemu_WriteConsoleA,
    qemu_WriteConsoleInputA,
    qemu_WriteConsoleInputW,
    qemu_WriteConsoleOutputA,
    qemu_WriteConsoleOutputAttribute,
    qemu_WriteConsoleOutputCharacterA,
    qemu_WriteConsoleOutputCharacterW,
    qemu_WriteConsoleOutputW,
    qemu_WriteConsoleW,
    qemu_WriteFile,
    qemu_WriteFileEx,
    qemu_WriteFileGather,
    qemu_WritePrivateProfileSectionA,
    qemu_WritePrivateProfileSectionW,
    qemu_WritePrivateProfileStringA,
    qemu_WritePrivateProfileStringW,
    qemu_WritePrivateProfileStructA,
    qemu_WritePrivateProfileStructW,
    qemu_WriteProcessMemory,
    qemu_WriteProfileSectionA,
    qemu_WriteProfileSectionW,
    qemu_WriteProfileStringA,
    qemu_WriteProfileStringW,
    qemu_WriteTapemark,
    qemu_WTSGetActiveConsoleSessionId,
    qemu_ZombifyActCtx,
};

/* Wine's TEB access is slow because it doesn't store it in a CPU register yet.
 * Cache it using ELF TLS for now. Yeah, it's ugly. */
__thread TEB *teb;

/* RtlSetCurrentDirectory_U is non-trivial and I'd have to use an
 * actual hook that keeps the function callable. SetCurrentDirectoryA/W
 * is its only caller in Wine, so hook it to fix up the guest TEB,
 * and special-case the RtlSetCurrentDirectory_U wrapper in our ntdll. */
static BOOL WINAPI hook_SetCurrentDirectoryW(const WCHAR *dir)
{
    UNICODE_STRING dirW;
    NTSTATUS status;

    RtlInitUnicodeString( &dirW, dir );
    status = RtlSetCurrentDirectory_U( &dirW );
    if (status != STATUS_SUCCESS)
    {
        SetLastError( RtlNtStatusToDosError(status) );
    }
    else
    {
        TEB *qemu_teb = qemu_ops->qemu_getTEB();
        TEB32 *qemu_teb32 = qemu_ops->qemu_getTEB32();

        if (!teb)
            teb = NtCurrentTeb();

        /* No need to update dosPath, it always points to the same place anyway. */
        qemu_teb->Peb->ProcessParameters->CurrentDirectory.Handle =
                teb->Peb->ProcessParameters->CurrentDirectory.Handle;
        if (qemu_teb32)
        {
            PEB32 *peb32 = (PEB32 *)(ULONG_PTR)qemu_teb32->Peb;
            RTL_USER_PROCESS_PARAMETERS32 *pp32 = (RTL_USER_PROCESS_PARAMETERS32 *)(ULONG_PTR)peb32->ProcessParameters;
            pp32->CurrentDirectory.Handle = (ULONG_PTR)teb->Peb->ProcessParameters->CurrentDirectory.Handle;
            memcpy((void *)(ULONG_PTR)pp32->CurrentDirectory.DosPath.Buffer,
                    teb->Peb->ProcessParameters->CurrentDirectory.DosPath.Buffer,
                    pp32->CurrentDirectory.DosPath.MaximumLength);
        }
    }
    return !status;
}

static WCHAR *FILE_name_AtoW( LPCSTR name, BOOL alloc )
{
    ANSI_STRING str;
    UNICODE_STRING strW, *pstrW;
    NTSTATUS status;

    RtlInitAnsiString( &str, name );
    pstrW = alloc ? &strW : &teb->StaticUnicodeString;
    if (!AreFileApisANSI())
        status = RtlOemStringToUnicodeString( pstrW, &str, alloc );
    else
        status = RtlAnsiStringToUnicodeString( pstrW, &str, alloc );
    if (status == STATUS_SUCCESS) return pstrW->Buffer;

    if (status == STATUS_BUFFER_OVERFLOW)
        SetLastError( ERROR_FILENAME_EXCED_RANGE );
    else
        SetLastError( RtlNtStatusToDosError(status) );
    return NULL;
}

static BOOL WINAPI hook_SetCurrentDirectoryA(const CHAR *dir)
{
    WCHAR *dirW;
    UNICODE_STRING strW;
    NTSTATUS status;

    if (!teb)
        teb = NtCurrentTeb();

    if (!(dirW = FILE_name_AtoW( dir, FALSE ))) return FALSE;
    RtlInitUnicodeString( &strW, dirW );
    status = RtlSetCurrentDirectory_U( &strW );
    if (status != STATUS_SUCCESS)
    {
        SetLastError( RtlNtStatusToDosError(status) );
    }
    else
    {
        TEB *qemu_teb = qemu_ops->qemu_getTEB();

        /* No need to update dosPath, it always points to the same place anyway. */
        qemu_teb->Peb->ProcessParameters->CurrentDirectory.Handle =
                teb->Peb->ProcessParameters->CurrentDirectory.Handle;
    }
    return !status;
}

static void hook(void *to_hook, const void *replace)
{
    DWORD old_protect;
    size_t offset;
#ifdef __aarch64__
    struct hooked_function
    {
        DWORD ldr, br;
        const void *dst;
    } *hooked_function = to_hook;

    if(!VirtualProtect(hooked_function, sizeof(*hooked_function), PAGE_EXECUTE_READWRITE, &old_protect))
        WINE_ERR("Failed to make hooked function writeable.\n");

    offset = offsetof(struct hooked_function, dst) - offsetof(struct hooked_function, ldr);
    hooked_function->ldr = 0x58000005 | (offset << 3);   /* ldr x5, offset */;
    hooked_function->br = 0xd61f00a0; /* br x5 */;
    hooked_function->dst = replace;

    __clear_cache(hooked_function, (char *)hooked_function + sizeof(*hooked_function));
#elif defined(__x86_64__)
    struct hooked_function
    {
        char jmp[8];
        const void *dst;
    } *hooked_function = to_hook;

    if(!VirtualProtect(hooked_function, sizeof(*hooked_function), PAGE_EXECUTE_READWRITE, &old_protect))
        WINE_ERR("Failed to make hooked function writeable.\n");

    /* The offset is from the end of the jmp instruction (6 bytes) to the start of the destination. */
    offset = offsetof(struct hooked_function, dst) - offsetof(struct hooked_function, jmp) - 0x6;

    /* jmp *(rip + offset) */
    hooked_function->jmp[0] = 0xff;
    hooked_function->jmp[1] = 0x25;
    hooked_function->jmp[2] = offset;
    hooked_function->jmp[3] = 0x00;
    hooked_function->jmp[4] = 0x00;
    hooked_function->jmp[5] = 0x00;
    /* Filler */
    hooked_function->jmp[6] = 0xcc;
    hooked_function->jmp[7] = 0xcc;
    /* Dest address absolute */
    hooked_function->dst = replace;
#else
#error Implement hooks for your platform
#endif

    VirtualProtect(hooked_function, sizeof(*hooked_function), old_protect, &old_protect);
}

static BOOL WINAPI hook_RegisterClassNameW(const WCHAR *class)
{
    BOOL ret;

    WINE_TRACE("Called for %s %lx\n", wine_dbgstr_w(class), guest_register_class_wrapper);
    ret = qemu_ops->qemu_execute(QEMU_G2H(guest_register_class_wrapper), QEMU_H2G(class));
    WINE_TRACE("Guest returned %x.\n", ret);

    return ret;
}

/* Wine's user32 loads comctl32 if the application attempts to access known comctl32 classes
 * that aren't registered yet. We want the guest comctl32.dll to register those classes, not
 * the host. Interecept the load and hook the register callback.
 *
 * Note that we can't just load comctl32.dll to access RegisterClassNameW because comctl32's
 * DllMain registers some classes as well. */
static HMODULE WINAPI hook_LoadLibraryW(const WCHAR *name)
{
    static const WCHAR comctl32W[] = {'c','o','m','c','t','l','3','2','.','d','l','l',0};

    if (!strcmpW(name, comctl32W))
    {
        HMODULE kernel32, ret, old_lib = GetModuleHandleW(name);
        BOOL guest_load_ret;

        WINE_TRACE("Loading host comctl32.\n");
        if (old_lib)
            WINE_ERR("Hot comctl32.dll already loaded.\n");

        WINE_TRACE("Calling guest to load comctl32.\n");
        guest_load_ret = qemu_ops->qemu_execute(QEMU_G2H(guest_load_comctl32), 0);
        WINE_TRACE("Guest returned %u.\n", guest_load_ret);
        if (!guest_load_ret)
            return NULL;

        ret = LoadLibraryExW(name, 0, 0);
        if (ret)
            hook(GetProcAddress(ret, "RegisterClassNameW"), hook_RegisterClassNameW);

        return ret;
    }

    return LoadLibraryExW(name, 0, 0);

}

struct callback_entry_table *overlapped_wrappers;

static CRITICAL_SECTION ov_cs = {0, -1, 0, 0, 0, 0};
static struct list ov_free_list = LIST_INIT(ov_free_list);
static struct wine_rb_tree ov_rbtree;
unsigned int free_list_space = 1024;

void free_OVERLAPPED(struct OVERLAPPED_data *ov)
{
    EnterCriticalSection(&ov_cs);
    if (ov->in_tree)
        wine_rb_remove(&ov_rbtree, &ov->rbtree_entry);

    if (free_list_space)
    {
        free_list_space--;
        list_add_tail(&ov_free_list, &ov->free_list_entry);
    }
    else
    {
        HeapFree(GetProcessHeap(), 0, ov);
    }
    LeaveCriticalSection(&ov_cs);
}

void CALLBACK apc_callback_func(ULONG_PTR ctx)
{
    struct OVERLAPPED_data *ov = (struct OVERLAPPED_data *)ctx;
    struct qemu_completion_cb call;

    WINE_TRACE("APC callback queued\n");
    if (ov->wsa)
    {
        call.func = 0;
        call.wsa_func = ov->guest_cb;
    }
    else
    {
        call.wsa_func = 0;
        call.func = ov->guest_cb;
    }
    call.error = ov->ov.Internal;
    call.len = ov->ov.InternalHigh;
    call.ov = QEMU_H2G(ov->guest_ov);
    call.flags = ov->wsa_flags;

    WINE_TRACE("Calling guest callback 0x%lx(%lx, %lu, 0x%lx).\n", (unsigned long)call.func, (unsigned long)call.error,
            (unsigned long)call.len, (unsigned long)call.ov);
    qemu_ops->qemu_execute(QEMU_G2H(guest_completion_cb), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned.\n");

    free_OVERLAPPED(ov);
}

DWORD CALLBACK overlapped32_wait_func(void *ctx)
{
    struct OVERLAPPED_data *ov = ctx;

    WINE_TRACE("Work item started %p\n", ov);

    /* FIXME: This proxy event breaks the kernel32 pipe.c tests because ReadFile (on a pipe)
     * returns to the application before the WriteFile event that was previously waiting gets
     * signalled. Either this is just an unlucky race, or there is a guarantee that IO ops
     * that depend on each other finish in order. The WriteFile is started before the ReadFile,
     * but the ReadFile ends up finishing first due to the delay here. */
    WaitForSingleObjectEx(ov->ov.hEvent, INFINITE, TRUE);
    WINE_TRACE("Event wait finished %p\n", ov);
    ov->ov.hEvent = HANDLE_g2h(ov->guest_ov->hEvent);
    OVERLAPPED_h2g(ov->guest_ov, &ov->ov);

    if (ov->msg)
    {
        ULONG_PTR guest_buffers = ov->guest_msg->lpBuffers;
        WSAMSG_h2g(ov->guest_msg, ov->msg);
        ov->guest_msg->lpBuffers = guest_buffers;
        HeapFree(GetProcessHeap(), 0, ov->msg->lpBuffers);
        HeapFree(GetProcessHeap(), 0, ov->msg);
    }
    HeapFree(GetProcessHeap(), 0, ov->buffers);

    WINE_TRACE("Signalling event %p\n", ov->ov.hEvent);
    /* ws2_32 does not signal the event if there is a callback. */
    if ((!ov->wsa || !ov->guest_cb) && ov->ov.hEvent && ov->ov.hEvent != INVALID_HANDLE_VALUE)
        SetEvent(ov->ov.hEvent);

    /* FIXME: How does the event relate to the callback and how do both of them relate to
     * GetQueuedCompletionStatus? Freeing data here or in the callback may break
     * GetQueuedCompletionStatus because it reads the pointer it retrieved from Wine. Maybe
     * I shouldn't free ov here if an IO completion port is used and the event queued to it?
     * (low bit on the event is not set). How do I find out if the file handle has an IOCP
     * associated to it?.
     *
     * It seems NtQueryInformationFile(FileCompletionInformation) can tell me if there's an
     * IOCP associated with the handle, but it requires a Wine server call. A different
     * approach, if possible, may be a good idea.
     *
     * This NtQueryInformationFile(FileCompletionInformation) is not implemented in Wine.
     * So do something broken and delay destruction of the OVERLAPPED entries... */
    if (ov->guest_cb)
    {
        HANDLE t = OpenThread(THREAD_SET_CONTEXT, FALSE, ov->cb_thread);
        /* FIXME: Set the event first, or queue the APC first? */
        WINE_TRACE("Queing APC in thread %x handle %p\n", ov->cb_thread, t);
        if (!QueueUserAPC(apc_callback_func, t, (ULONG_PTR)ov))
            WINE_ERR("Failed to queue APC\n");
        CloseHandle(t);
    }
    else
    {
        WINE_TRACE("Just freeing data %p, guest data %p\n", ov, ov->guest_ov);
        free_OVERLAPPED(ov);
    }

    return 0;
}

struct OVERLAPPED_data * WINAPI alloc_OVERLAPPED_data(void *ov32, uint64_t guest_completion_cb, BOOL event)
{
    struct OVERLAPPED_data *ret;

    EnterCriticalSection(&ov_cs);

    if (!free_list_space)
    {
        struct list *reuse;
        free_list_space++;
        reuse = list_tail(&ov_free_list);
        list_remove(reuse);
        ret = LIST_ENTRY(reuse, struct OVERLAPPED_data, free_list_entry);
        memset(ret, 0, sizeof(*ret));
    }
    else
    {
        ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    }
    OVERLAPPED_g2h(&ret->ov, ov32);
    ret->guest_ov = ov32;
    ret->guest_cb = guest_completion_cb;
    if (event)
        ret->ov.hEvent = CreateEventW(NULL, 0, 0, NULL);

    LeaveCriticalSection(&ov_cs);

    return ret;
}

void queue_OVERLAPPED(struct OVERLAPPED_data *data)
{
    EnterCriticalSection(&ov_cs);
    if (wine_rb_put(&ov_rbtree, data->guest_ov, &data->rbtree_entry))
    {
        /* This gets hit by ws2_32's test_WSARecv(). And yes, the test does perform two async operations
         * with the same OVERLAPPED structure.
         *
         * This is also pretty common in Warhammer 40k: Dawn of war and presumably many other applications.
         * Don't be too upset about it. */
        WINE_WARN("Cannot place OVERLAPPED wrapper in tree. Did the application reuse the pointer?\n");
    }
    else
    {
        data->in_tree = TRUE;
    }
    LeaveCriticalSection(&ov_cs);
}

void WINAPI process_OVERLAPPED_data(uint64_t retval, struct OVERLAPPED_data *data)
{
    if (!retval && GetLastError() == ERROR_IO_PENDING)
    {
        struct qemu_OVERLAPPED *ov32 = data->guest_ov;

        queue_OVERLAPPED(data);

        if (ov32->hEvent && ov32->hEvent != (qemu_handle)(LONG_PTR)INVALID_HANDLE_VALUE)
            ResetEvent(HANDLE_g2h(ov32->hEvent));

        data->cb_thread = GetCurrentThreadId();

        WINE_TRACE("Async return, starting wait thread.\n");
        if (!QueueUserWorkItem(overlapped32_wait_func, data, 0))
            WINE_ERR("Failed to queue work item\n");
    }
    else
    {
        WINE_TRACE("Synchonous return return, host ptr %p, guest ptr %p.\n", data, data->guest_ov);
        CloseHandle(data->ov.hEvent);
        if (data->msg)
        {
            HeapFree(GetProcessHeap(), 0, data->msg->lpBuffers);
            HeapFree(GetProcessHeap(), 0, data->msg);
        }
        HeapFree(GetProcessHeap(), 0, data->buffers);

        if (retval)
            free_OVERLAPPED(data); /* Might be queued in a completion port to report the success. */
        else
            HeapFree(GetProcessHeap(), 0, data); /* Won't be needed any more. */
    }
}

static int ov_tree_compare(const void *key, const struct wine_rb_entry *entry)
{
    struct OVERLAPPED_data *data = WINE_RB_ENTRY_VALUE(entry, struct OVERLAPPED_data, rbtree_entry);

    if ((ULONG_PTR)key == (ULONG_PTR)data->guest_ov)
        return 0;
    return (ULONG_PTR)key > (ULONG_PTR)data->guest_ov;
}

struct OVERLAPPED_data *get_OVERLAPPED_data(void *guest)
{
    struct wine_rb_entry *entry;

    EnterCriticalSection(&ov_cs);
    entry = wine_rb_get(&ov_rbtree, guest);
    LeaveCriticalSection(&ov_cs);

    if (!entry)
        return NULL;
    return WINE_RB_ENTRY_VALUE(entry, struct OVERLAPPED_data, rbtree_entry);
}

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HANDLE kernel32;

    WINE_TRACE("Loading host-side kernel32 wrapper.\n");
    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    kernel32_tls = TlsAlloc();
    if (kernel32_tls == TLS_OUT_OF_INDEXES)
        WINE_ERR("Out of TLS indices\n");

    /* The function pointers provided by the linker point into the IAT, not the actual function. */
    kernel32 = GetModuleHandleA("kernel32");
    hook(GetProcAddress(kernel32, "SetCurrentDirectoryA"), hook_SetCurrentDirectoryA);
    hook(GetProcAddress(kernel32, "SetCurrentDirectoryW"), hook_SetCurrentDirectoryW);
    hook(GetProcAddress(kernel32, "LoadLibraryW"), hook_LoadLibraryW);

    /* We're searching through this array every time there's an IO request. If 32 entries are not enough for
     * an application, then the linear search isn't good enough. Before growing this array find a way to do
     * improve the search speed. */
    if (!callback_alloc_table(&overlapped_wrappers, 32, sizeof(struct callback_entry), host_completion_cb, 3))
        WINE_ERR("Failed to allocate overlapped wrappers.\n");

    wine_rb_init(&ov_rbtree, ov_tree_compare);

    return dll_functions;
}

#endif
