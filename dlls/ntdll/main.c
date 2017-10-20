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
#include "qemu_ntdll.h"

struct qemu_set_callbacks
{
    struct qemu_syscall super;
    uint64_t exception_handler;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_set_callbacks call;
    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            call.super.id = QEMU_SYSCALL_ID(CALL_SET_CALLBACKS);
            call.exception_handler = (ULONG_PTR)qemu_exception_handler;
            qemu_syscall(&call.super);
            break;
    }
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

const struct qemu_ops *qemu_ops;

static void qemu_set_callbacks(struct qemu_syscall *call)
{
    struct qemu_set_callbacks *c = (struct qemu_set_callbacks *)call;
    qemu_ops->qemu_set_except_handler(c->exception_handler);
}

static const syscall_handler dll_functions[] =
{
    qemu___C_specific_handler,
    qemu___isascii,
    qemu___iscsym,
    qemu___iscsymf,
    qemu___toascii,
    qemu__atoi64,
    qemu__i64toa,
    qemu__i64tow,
    qemu__itoa,
    qemu__itow,
    qemu__local_unwind,
    qemu__ltoa,
    qemu__ltow,
    qemu__memccpy,
    qemu__memicmp,
    qemu__splitpath,
    qemu__stricmp,
    qemu__strlwr,
    qemu__strnicmp,
    qemu__strupr,
    qemu__tolower,
    qemu__toupper,
    qemu__ui64toa,
    qemu__ui64tow,
    qemu__ultoa,
    qemu__ultow,
    qemu__wcsicmp,
    qemu__wcslwr,
    qemu__wcsnicmp,
    qemu__wcsupr,
    qemu__wtoi,
    qemu__wtoi64,
    qemu__wtol,
    qemu_atoi,
    qemu_atol,
    qemu_EtwEventEnabled,
    qemu_EtwEventRegister,
    qemu_EtwEventSetInformation,
    qemu_EtwEventUnregister,
    qemu_EtwEventWrite,
    qemu_EtwRegisterTraceGuidsA,
    qemu_EtwRegisterTraceGuidsW,
    qemu_EtwUnregisterTraceGuids,
    qemu_isalnum,
    qemu_isalpha,
    qemu_iscntrl,
    qemu_isdigit,
    qemu_isgraph,
    qemu_islower,
    qemu_isprint,
    qemu_ispunct,
    qemu_isspace,
    qemu_isupper,
    qemu_iswalpha,
    qemu_iswctype,
    qemu_iswdigit,
    qemu_iswlower,
    qemu_iswspace,
    qemu_iswxdigit,
    qemu_isxdigit,
    qemu_LdrFindEntryForAddress,
    qemu_mbstowcs,
    qemu_memchr,
    qemu_memcmp,
    qemu_memcpy,
    qemu_memmove,
    qemu_memset,
    qemu_NtAcceptConnectPort,
    qemu_NtAccessCheckAndAuditAlarm,
    qemu_NtAdjustGroupsToken,
    qemu_NtAdjustPrivilegesToken,
    qemu_NtAlertResumeThread,
    qemu_NtAlertThread,
    qemu_NtAllocateLocallyUniqueId,
    qemu_NtAllocateUuids,
    qemu_NtAssignProcessToJobObject,
    qemu_NtCancelIoFile,
    qemu_NtCancelIoFileEx,
    qemu_NtCancelTimer,
    qemu_NtClearEvent,
    qemu_NtClose,
    qemu_NtCompleteConnectPort,
    qemu_NtConnectPort,
    qemu_NtCreateDirectoryObject,
    qemu_NtCreateEvent,
    qemu_NtCreateFile,
    qemu_NtCreateIoCompletion,
    qemu_NtCreateJobObject,
    qemu_NtCreateKey,
    qemu_NtCreateKeyedEvent,
    qemu_NtCreateKeyTransacted,
    qemu_NtCreateMailslotFile,
    qemu_NtCreateMutant,
    qemu_NtCreateNamedPipeFile,
    qemu_NtCreatePagingFile,
    qemu_NtCreatePort,
    qemu_NtCreateSemaphore,
    qemu_NtCreateSymbolicLinkObject,
    qemu_NtCreateTimer,
    qemu_NtDelayExecution,
    qemu_NtDeleteFile,
    qemu_NtDeleteKey,
    qemu_NtDeleteValueKey,
    qemu_NtDeviceIoControlFile,
    qemu_NtDisplayString,
    qemu_NtDuplicateObject,
    qemu_NtDuplicateToken,
    qemu_NtEnumerateKey,
    qemu_NtEnumerateValueKey,
    qemu_NtFlushBuffersFile,
    qemu_NtFlushInstructionCache,
    qemu_NtFlushKey,
    qemu_NtFsControlFile,
    qemu_NtGetCurrentProcessorNumber,
    qemu_NtInitiatePowerAction,
    qemu_NtIsProcessInJob,
    qemu_NtListenPort,
    qemu_NtLoadKey,
    qemu_NtLoadKey2,
    qemu_NtLockFile,
    qemu_NtMakeTemporaryObject,
    qemu_NtNotifyChangeDirectoryFile,
    qemu_NtNotifyChangeKey,
    qemu_NtNotifyChangeMultipleKeys,
    qemu_NtOpenDirectoryObject,
    qemu_NtOpenEvent,
    qemu_NtOpenFile,
    qemu_NtOpenIoCompletion,
    qemu_NtOpenJobObject,
    qemu_NtOpenKey,
    qemu_NtOpenKeyedEvent,
    qemu_NtOpenKeyEx,
    qemu_NtOpenKeyTransacted,
    qemu_NtOpenKeyTransactedEx,
    qemu_NtOpenMutant,
    qemu_NtOpenProcess,
    qemu_NtOpenProcessToken,
    qemu_NtOpenProcessTokenEx,
    qemu_NtOpenSemaphore,
    qemu_NtOpenSymbolicLinkObject,
    qemu_NtOpenThread,
    qemu_NtOpenThreadToken,
    qemu_NtOpenThreadTokenEx,
    qemu_NtOpenTimer,
    qemu_NtPowerInformation,
    qemu_NtPrivilegeCheck,
    qemu_NtPulseEvent,
    qemu_NtQueryAttributesFile,
    qemu_NtQueryDirectoryObject,
    qemu_NtQueryEaFile,
    qemu_NtQueryEvent,
    qemu_NtQueryFullAttributesFile,
    qemu_NtQueryInformationFile,
    qemu_NtQueryInformationJobObject,
    qemu_NtQueryInformationProcess,
    qemu_NtQueryInformationThread,
    qemu_NtQueryInformationToken,
    qemu_NtQueryIoCompletion,
    qemu_NtQueryKey,
    qemu_NtQueryLicenseValue,
    qemu_NtQueryMultipleValueKey,
    qemu_NtQueryMutant,
    qemu_NtQueryObject,
    qemu_NtQuerySecurityObject,
    qemu_NtQuerySemaphore,
    qemu_NtQuerySymbolicLinkObject,
    qemu_NtQuerySystemInformation,
    qemu_NtQuerySystemInformationEx,
    qemu_NtQueryTimer,
    qemu_NtQueryTimerResolution,
    qemu_NtQueryValueKey,
    qemu_NtQueryVolumeInformationFile,
    qemu_NtQueueApcThread,
    qemu_NtRaiseException,
    qemu_NtRaiseHardError,
    qemu_NtReadFile,
    qemu_NtReadFileScatter,
    qemu_NtRegisterThreadTerminatePort,
    qemu_NtReleaseKeyedEvent,
    qemu_NtReleaseMutant,
    qemu_NtReleaseSemaphore,
    qemu_NtRemoveIoCompletion,
    qemu_NtRenameKey,
    qemu_NtReplaceKey,
    qemu_NtReplyWaitReceivePort,
    qemu_NtRequestWaitReplyPort,
    qemu_NtResetEvent,
    qemu_NtRestoreKey,
    qemu_NtResumeProcess,
    qemu_NtResumeThread,
    qemu_NtSaveKey,
    qemu_NtSecureConnectPort,
    qemu_NtSetEaFile,
    qemu_NtSetEvent,
    qemu_NtSetInformationFile,
    qemu_NtSetInformationJobObject,
    qemu_NtSetInformationKey,
    qemu_NtSetInformationObject,
    qemu_NtSetInformationProcess,
    qemu_NtSetInformationThread,
    qemu_NtSetInformationToken,
    qemu_NtSetIntervalProfile,
    qemu_NtSetIoCompletion,
    qemu_NtSetLdtEntries,
    qemu_NtSetSystemInformation,
    qemu_NtSetTimer,
    qemu_NtSetTimerResolution,
    qemu_NtSetValueKey,
    qemu_NtSetVolumeInformationFile,
    qemu_NtShutdownSystem,
    qemu_NtSignalAndWaitForSingleObject,
    qemu_NtSuspendProcess,
    qemu_NtSuspendThread,
    qemu_NtSystemDebugControl,
    qemu_NtTerminateJobObject,
    qemu_NtTerminateProcess,
    qemu_NtTerminateThread,
    qemu_NtUnloadKey,
    qemu_NtUnlockFile,
    qemu_NtWaitForKeyedEvent,
    qemu_NtWaitForMultipleObjects,
    qemu_NtWaitForSingleObject,
    qemu_NtWriteFile,
    qemu_NtWriteFileGather,
    qemu_NtYieldExecution,
    qemu_RtlAcquirePebLock,
    qemu_RtlAcquireResourceExclusive,
    qemu_RtlAcquireResourceShared,
    qemu_RtlAcquireSRWLockExclusive,
    qemu_RtlAcquireSRWLockShared,
    qemu_RtlActivateActivationContext,
    qemu_RtlAddFunctionTable,
    qemu_RtlAddRefActivationContext,
    qemu_RtlAddVectoredContinueHandler,
    qemu_RtlAddVectoredExceptionHandler,
    qemu_RtlAllocateHeap,
    qemu_RtlAnsiCharToUnicodeChar,
    qemu_RtlAnsiStringToUnicodeSize,
    qemu_RtlAnsiStringToUnicodeString,
    qemu_RtlAppendAsciizToString,
    qemu_RtlAppendStringToString,
    qemu_RtlAppendUnicodeStringToString,
    qemu_RtlAppendUnicodeToString,
    qemu_RtlAreAllAccessesGranted,
    qemu_RtlAreAnyAccessesGranted,
    qemu_RtlAssert,
    qemu_RtlCaptureStackBackTrace,
    qemu_RtlCharToInteger,
    qemu_RtlCheckRegistryKey,
    qemu_RtlCompactHeap,
    qemu_RtlCompareMemory,
    qemu_RtlCompareMemoryUlong,
    qemu_RtlCompareString,
    qemu_RtlCompareUnicodeString,
    qemu_RtlCompareUnicodeStrings,
    qemu_RtlCompressBuffer,
    qemu_RtlComputeCrc32,
    qemu_RtlCopyLuid,
    qemu_RtlCopyLuidAndAttributesArray,
    qemu_RtlCopyMemory,
    qemu_RtlCopyString,
    qemu_RtlCopyUnicodeString,
    qemu_RtlCreateActivationContext,
    qemu_RtlCreateHeap,
    qemu_RtlCreateTimer,
    qemu_RtlCreateTimerQueue,
    qemu_RtlCreateUnicodeString,
    qemu_RtlCreateUnicodeStringFromAsciiz,
    qemu_RtlCreateUserProcess,
    qemu_RtlCreateUserThread,
    qemu_RtlDeactivateActivationContext,
    qemu_RtlDecodePointer,
    qemu_RtlDecompressBuffer,
    qemu_RtlDecompressFragment,
    qemu_RtlDeleteCriticalSection,
    qemu_RtlDeleteFunctionTable,
    qemu_RtlDeleteRegistryValue,
    qemu_RtlDeleteResource,
    qemu_RtlDeleteSecurityObject,
    qemu_RtlDeleteTimer,
    qemu_RtlDeleteTimerQueueEx,
    qemu_RtlDeregisterWait,
    qemu_RtlDeregisterWaitEx,
    qemu_RtlDestroyHeap,
    qemu_RtlDetermineDosPathNameType_U,
    qemu_RtlDosPathNameToNtPathName_U,
    qemu_RtlDosSearchPath_U,
    qemu_RtlDowncaseUnicodeChar,
    qemu_RtlDowncaseUnicodeString,
    qemu_RtlDumpResource,
    qemu_RtlDuplicateUnicodeString,
    qemu_RtlEncodePointer,
    qemu_RtlEnterCriticalSection,
    qemu_RtlEqualComputerName,
    qemu_RtlEqualDomainName,
    qemu_RtlEqualLuid,
    qemu_RtlEqualString,
    qemu_RtlEqualUnicodeString,
    qemu_RtlEraseUnicodeString,
    qemu_RtlFillMemory,
    qemu_RtlFillMemoryUlong,
    qemu_RtlFindActivationContextSectionGuid,
    qemu_RtlFindActivationContextSectionString,
    qemu_RtlFindCharInUnicodeString,
    qemu_RtlFirstEntrySList,
    qemu_RtlFormatCurrentUserKeyPath,
    qemu_RtlFreeAnsiString,
    qemu_RtlFreeHeap,
    qemu_RtlFreeOemString,
    qemu_RtlFreeThreadActivationContextStack,
    qemu_RtlFreeUnicodeString,
    qemu_RtlGetActiveActivationContext,
    qemu_RtlGetCompressionWorkSpaceSize,
    qemu_RtlGetCurrentDirectory_U,
    qemu_RtlGetCurrentPeb,
    qemu_RtlGetCurrentProcessorNumberEx,
    qemu_RtlGetCurrentTransaction,
    qemu_RtlGetFullPathName_U,
    qemu_RtlGetLastNtStatus,
    qemu_RtlGetLastWin32Error,
    qemu_RtlGetLongestNtPathLength,
    qemu_RtlGetNtGlobalFlags,
    qemu_RtlGetNtProductType,
    qemu_RtlGetNtVersionNumbers,
    qemu_RtlGetProcessHeaps,
    qemu_RtlGetProductInfo,
    qemu_RtlGetThreadErrorMode,
    qemu_RtlGetVersion,
    qemu_RtlGUIDFromString,
    qemu_RtlHashUnicodeString,
    qemu_RtlInitAnsiString,
    qemu_RtlInitAnsiStringEx,
    qemu_RtlInitializeConditionVariable,
    qemu_RtlInitializeCriticalSection,
    qemu_RtlInitializeCriticalSectionAndSpinCount,
    qemu_RtlInitializeCriticalSectionEx,
    qemu_RtlInitializeGenericTable,
    qemu_RtlInitializeGenericTableAvl,
    qemu_RtlInitializeResource,
    qemu_RtlInitializeSListHead,
    qemu_RtlInitializeSRWLock,
    qemu_RtlInitString,
    qemu_RtlInitUnicodeString,
    qemu_RtlInitUnicodeStringEx,
    qemu_RtlInsertElementGenericTableAvl,
    qemu_RtlIntegerToChar,
    qemu_RtlIntegerToUnicodeString,
    qemu_RtlInterlockedFlushSList,
    qemu_RtlInterlockedPopEntrySList,
    qemu_RtlInterlockedPushEntrySList,
    qemu_RtlInterlockedPushListSList,
    qemu_RtlInterlockedPushListSListEx,
    qemu_RtlIpv4AddressToStringA,
    qemu_RtlIpv4AddressToStringExA,
    qemu_RtlIpv4AddressToStringExW,
    qemu_RtlIpv4AddressToStringW,
    qemu_RtlIpv4StringToAddressExW,
    qemu_RtlIsActivationContextActive,
    qemu_RtlIsCriticalSectionLocked,
    qemu_RtlIsCriticalSectionLockedByThread,
    qemu_RtlIsDosDeviceName_U,
    qemu_RtlIsNameLegalDOS8Dot3,
    qemu_RtlIsTextUnicode,
    qemu_RtlLeaveCriticalSection,
    qemu_RtlLockHeap,
    qemu_RtlLookupFunctionEntry,
    qemu_RtlMapGenericMask,
    qemu_RtlMoveMemory,
    qemu_RtlMultiByteToUnicodeN,
    qemu_RtlMultiByteToUnicodeSize,
    qemu_RtlNewSecurityObject,
    qemu_RtlNtStatusToDosError,
    qemu_RtlNtStatusToDosErrorNoTeb,
    qemu_RtlOemStringToUnicodeSize,
    qemu_RtlOemStringToUnicodeString,
    qemu_RtlOemToUnicodeN,
    qemu_RtlOpenCurrentUser,
    qemu_RtlPcToFileHeader,
    qemu_RtlpNtCreateKey,
    qemu_RtlpNtEnumerateSubKey,
    qemu_RtlpNtMakeTemporaryKey,
    qemu_RtlpNtOpenKey,
    qemu_RtlpNtQueryValueKey,
    qemu_RtlpNtSetValueKey,
    qemu_RtlPrefixString,
    qemu_RtlPrefixUnicodeString,
    qemu_RtlpUnWaitCriticalSection,
    qemu_RtlpWaitForCriticalSection,
    qemu_RtlQueryDepthSList,
    qemu_RtlQueryHeapInformation,
    qemu_RtlQueryInformationActivationContext,
    qemu_RtlQueryRegistryValues,
    qemu_RtlQueueWorkItem,
    qemu_RtlRaiseStatus,
    qemu_RtlRandom,
    qemu_RtlReAllocateHeap,
    qemu_RtlRegisterWait,
    qemu_RtlReleaseActivationContext,
    qemu_RtlReleasePebLock,
    qemu_RtlReleaseResource,
    qemu_RtlReleaseSRWLockExclusive,
    qemu_RtlReleaseSRWLockShared,
    qemu_RtlRemoveVectoredContinueHandler,
    qemu_RtlRemoveVectoredExceptionHandler,
    qemu_RtlRestoreContext,
    qemu_RtlRunOnceBeginInitialize,
    qemu_RtlRunOnceComplete,
    qemu_RtlRunOnceExecuteOnce,
    qemu_RtlRunOnceInitialize,
    qemu_RtlSetCriticalSectionSpinCount,
    qemu_RtlSetCurrentDirectory_U,
    qemu_RtlSetCurrentTransaction,
    qemu_RtlSetHeapInformation,
    qemu_RtlSetIoCompletionCallback,
    qemu_RtlSetLastWin32Error,
    qemu_RtlSetLastWin32ErrorAndNtStatusFromNtStatus,
    qemu_RtlSetThreadErrorMode,
    qemu_RtlSizeHeap,
    qemu_RtlSleepConditionVariableCS,
    qemu_RtlSleepConditionVariableSRW,
    qemu_RtlStringFromGUID,
    qemu_RtlTryAcquireSRWLockExclusive,
    qemu_RtlTryAcquireSRWLockShared,
    qemu_RtlTryEnterCriticalSection,
    qemu_RtlUnicodeStringToAnsiSize,
    qemu_RtlUnicodeStringToAnsiString,
    qemu_RtlUnicodeStringToInteger,
    qemu_RtlUnicodeStringToOemSize,
    qemu_RtlUnicodeStringToOemString,
    qemu_RtlUnicodeToMultiByteN,
    qemu_RtlUnicodeToMultiByteSize,
    qemu_RtlUnicodeToOemN,
    qemu_RtlUniform,
    qemu_RtlUnlockHeap,
    qemu_RtlUnwindEx,
    qemu_RtlUpcaseUnicodeChar,
    qemu_RtlUpcaseUnicodeString,
    qemu_RtlUpcaseUnicodeStringToAnsiString,
    qemu_RtlUpcaseUnicodeStringToCountedOemString,
    qemu_RtlUpcaseUnicodeStringToOemString,
    qemu_RtlUpcaseUnicodeToMultiByteN,
    qemu_RtlUpcaseUnicodeToOemN,
    qemu_RtlUpdateTimer,
    qemu_RtlUpperChar,
    qemu_RtlUpperString,
    qemu_RtlValidateHeap,
    qemu_RtlVerifyVersionInfo,
    qemu_RtlVirtualUnwind,
    qemu_RtlWakeAllConditionVariable,
    qemu_RtlWakeConditionVariable,
    qemu_RtlWalkHeap,
    qemu_RtlWriteRegistryValue,
    qemu_RtlZeroMemory,
    qemu_RtlZombifyActivationContext,
    qemu_set_callbacks,
    qemu_strcat,
    qemu_strchr,
    qemu_strcmp,
    qemu_strcpy,
    qemu_strcspn,
    qemu_strlen,
    qemu_strncat,
    qemu_strncmp,
    qemu_strncpy,
    qemu_strpbrk,
    qemu_strrchr,
    qemu_strspn,
    qemu_strstr,
    qemu_strtol,
    qemu_strtoul,
    qemu_tolower,
    qemu_toupper,
    qemu_towlower,
    qemu_towupper,
    qemu_TpAllocCleanupGroup,
    qemu_TpAllocPool,
    qemu_TpAllocTimer,
    qemu_TpAllocWait,
    qemu_TpAllocWork,
    qemu_TpCallbackLeaveCriticalSectionOnCompletion,
    qemu_TpCallbackMayRunLong,
    qemu_TpCallbackReleaseMutexOnCompletion,
    qemu_TpCallbackReleaseSemaphoreOnCompletion,
    qemu_TpCallbackSetEventOnCompletion,
    qemu_TpCallbackUnloadDllOnCompletion,
    qemu_TpDisassociateCallback,
    qemu_TpIsTimerSet,
    qemu_TpPostWork,
    qemu_TpReleaseCleanupGroup,
    qemu_TpReleaseCleanupGroupMembers,
    qemu_TpReleasePool,
    qemu_TpReleaseTimer,
    qemu_TpReleaseWait,
    qemu_TpReleaseWork,
    qemu_TpSetPoolMaxThreads,
    qemu_TpSetPoolMinThreads,
    qemu_TpSetTimer,
    qemu_TpSetWait,
    qemu_TpSimpleTryPost,
    qemu_TpWaitForTimer,
    qemu_TpWaitForWait,
    qemu_TpWaitForWork,
    qemu_VerSetConditionMask,
    qemu_wcscat,
    qemu_wcschr,
    qemu_wcscmp,
    qemu_wcscpy,
    qemu_wcscspn,
    qemu_wcslen,
    qemu_wcsncat,
    qemu_wcsncmp,
    qemu_wcsncpy,
    qemu_wcspbrk,
    qemu_wcsrchr,
    qemu_wcsrchr,
    qemu_wcsspn,
    qemu_wcsstr,
    qemu_wcstok,
    qemu_wcstol,
    qemu_wcstombs,
    qemu_wcstoul,
    qemu_WinSqmEndSession,
    qemu_WinSqmIsOptedIn,
    qemu_WinSqmStartSession,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE ntdll;

    WINE_TRACE("Loading host-side ntdll wrapper.\n");

    ntdll = GetModuleHandleA("ntdll.dll");
    if (!ntdll)
        WINE_ERR("ntdll.dll not loaded\n");

    p___isascii = (void *)GetProcAddress(ntdll, "__isascii");
    if (!p___isascii)
        WINE_ERR("Could not find \"__isascii\" in ntdll\n");

    p___iscsym = (void *)GetProcAddress(ntdll, "__iscsym");
    if (!p___iscsym)
        WINE_ERR("Could not find \"__iscsym\" in ntdll\n");

    p___iscsymf = (void *)GetProcAddress(ntdll, "__iscsymf");
    if (!p___iscsymf)
        WINE_ERR("Could not find \"__iscsymf\" in ntdll\n");

    p___toascii = (void *)GetProcAddress(ntdll, "__toascii");
    if (!p___toascii)
        WINE_ERR("Could not find \"__toascii\" in ntdll\n");

    p__atoi64 = (void *)GetProcAddress(ntdll, "_atoi64");
    if (!p__atoi64)
        WINE_ERR("Could not find \"_atoi64\" in ntdll\n");

    p__i64toa = (void *)GetProcAddress(ntdll, "_i64toa");
    if (!p__i64toa)
        WINE_ERR("Could not find \"_i64toa\" in ntdll\n");

    p__i64tow = (void *)GetProcAddress(ntdll, "_i64tow");
    if (!p__i64tow)
        WINE_ERR("Could not find \"_i64tow\" in ntdll\n");

    p__itoa = (void *)GetProcAddress(ntdll, "_itoa");
    if (!p__itoa)
        WINE_ERR("Could not find \"_itoa\" in ntdll\n");

    p__itow = (void *)GetProcAddress(ntdll, "_itow");
    if (!p__itow)
        WINE_ERR("Could not find \"_itow\" in ntdll\n");

    p__ltoa = (void *)GetProcAddress(ntdll, "_ltoa");
    if (!p__ltoa)
        WINE_ERR("Could not find \"_ltoa\" in ntdll\n");

    p__ltow = (void *)GetProcAddress(ntdll, "_ltow");
    if (!p__ltow)
        WINE_ERR("Could not find \"_ltow\" in ntdll\n");

    p__memccpy = (void *)GetProcAddress(ntdll, "_memccpy");
    if (!p__memccpy)
        WINE_ERR("Could not find \"_memccpy\" in ntdll\n");

    p__memicmp = (void *)GetProcAddress(ntdll, "_memicmp");
    if (!p__memicmp)
        WINE_ERR("Could not find \"_memicmp\" in ntdll\n");

    p__splitpath = (void *)GetProcAddress(ntdll, "_splitpath");
    if (!p__splitpath)
        WINE_ERR("Could not find \"_splitpath\" in ntdll\n");

    p__stricmp = (void *)GetProcAddress(ntdll, "_stricmp");
    if (!p__stricmp)
        WINE_ERR("Could not find \"_stricmp\" in ntdll\n");

    p__strlwr = (void *)GetProcAddress(ntdll, "_strlwr");
    if (!p__strlwr)
        WINE_ERR("Could not find \"_strlwr\" in ntdll\n");

    p__strnicmp = (void *)GetProcAddress(ntdll, "_strnicmp");
    if (!p__strnicmp)
        WINE_ERR("Could not find \"_strnicmp\" in ntdll\n");

    p__strupr = (void *)GetProcAddress(ntdll, "_strupr");
    if (!p__strupr)
        WINE_ERR("Could not find \"_strupr\" in ntdll\n");

    p__tolower = (void *)GetProcAddress(ntdll, "_tolower");
    if (!p__tolower)
        WINE_ERR("Could not find \"_tolower\" in ntdll\n");

    p__toupper = (void *)GetProcAddress(ntdll, "_toupper");
    if (!p__toupper)
        WINE_ERR("Could not find \"_toupper\" in ntdll\n");

    p__ui64toa = (void *)GetProcAddress(ntdll, "_ui64toa");
    if (!p__ui64toa)
        WINE_ERR("Could not find \"_ui64toa\" in ntdll\n");

    p__ui64tow = (void *)GetProcAddress(ntdll, "_ui64tow");
    if (!p__ui64tow)
        WINE_ERR("Could not find \"_ui64tow\" in ntdll\n");

    p__ultoa = (void *)GetProcAddress(ntdll, "_ultoa");
    if (!p__ultoa)
        WINE_ERR("Could not find \"_ultoa\" in ntdll\n");

    p__ultow = (void *)GetProcAddress(ntdll, "_ultow");
    if (!p__ultow)
        WINE_ERR("Could not find \"_ultow\" in ntdll\n");

    p__wcsicmp = (void *)GetProcAddress(ntdll, "_wcsicmp");
    if (!p__wcsicmp)
        WINE_ERR("Could not find \"_wcsicmp\" in ntdll\n");

    p__wcslwr = (void *)GetProcAddress(ntdll, "_wcslwr");
    if (!p__wcslwr)
        WINE_ERR("Could not find \"_wcslwr\" in ntdll\n");

    p__wcsnicmp = (void *)GetProcAddress(ntdll, "_wcsnicmp");
    if (!p__wcsnicmp)
        WINE_ERR("Could not find \"_wcsnicmp\" in ntdll\n");

    p__wcsupr = (void *)GetProcAddress(ntdll, "_wcsupr");
    if (!p__wcsupr)
        WINE_ERR("Could not find \"_wcsupr\" in ntdll\n");

    p__wtoi = (void *)GetProcAddress(ntdll, "_wtoi");
    if (!p__wtoi)
        WINE_ERR("Could not find \"_wtoi\" in ntdll\n");

    p__wtoi64 = (void *)GetProcAddress(ntdll, "_wtoi64");
    if (!p__wtoi64)
        WINE_ERR("Could not find \"_wtoi64\" in ntdll\n");

    p__wtol = (void *)GetProcAddress(ntdll, "_wtol");
    if (!p__wtol)
        WINE_ERR("Could not find \"_wtol\" in ntdll\n");

    p_atoi = (void *)GetProcAddress(ntdll, "atoi");
    if (!p_atoi)
        WINE_ERR("Could not find \"atoi\" in ntdll\n");

    p_atol = (void *)GetProcAddress(ntdll, "atol");
    if (!p_atol)
        WINE_ERR("Could not find \"atol\" in ntdll\n");

    p_isalnum = (void *)GetProcAddress(ntdll, "isalnum");
    if (!p_isalnum)
        WINE_ERR("Could not find \"isalnum\" in ntdll\n");

    p_isalpha = (void *)GetProcAddress(ntdll, "isalpha");
    if (!p_isalpha)
        WINE_ERR("Could not find \"isalpha\" in ntdll\n");

    p_iscntrl = (void *)GetProcAddress(ntdll, "iscntrl");
    if (!p_iscntrl)
        WINE_ERR("Could not find \"iscntrl\" in ntdll\n");

    p_isdigit = (void *)GetProcAddress(ntdll, "isdigit");
    if (!p_isdigit)
        WINE_ERR("Could not find \"isdigit\" in ntdll\n");

    p_isgraph = (void *)GetProcAddress(ntdll, "isgraph");
    if (!p_isgraph)
        WINE_ERR("Could not find \"isgraph\" in ntdll\n");

    p_islower = (void *)GetProcAddress(ntdll, "islower");
    if (!p_islower)
        WINE_ERR("Could not find \"islower\" in ntdll\n");

    p_isprint = (void *)GetProcAddress(ntdll, "isprint");
    if (!p_isprint)
        WINE_ERR("Could not find \"isprint\" in ntdll\n");

    p_ispunct = (void *)GetProcAddress(ntdll, "ispunct");
    if (!p_ispunct)
        WINE_ERR("Could not find \"ispunct\" in ntdll\n");

    p_isspace = (void *)GetProcAddress(ntdll, "isspace");
    if (!p_isspace)
        WINE_ERR("Could not find \"isspace\" in ntdll\n");

    p_isupper = (void *)GetProcAddress(ntdll, "isupper");
    if (!p_isupper)
        WINE_ERR("Could not find \"isupper\" in ntdll\n");

    p_iswalpha = (void *)GetProcAddress(ntdll, "iswalpha");
    if (!p_iswalpha)
        WINE_ERR("Could not find \"iswalpha\" in ntdll\n");

    p_iswctype = (void *)GetProcAddress(ntdll, "iswctype");
    if (!p_iswctype)
        WINE_ERR("Could not find \"iswctype\" in ntdll\n");

    p_iswdigit = (void *)GetProcAddress(ntdll, "iswdigit");
    if (!p_iswdigit)
        WINE_ERR("Could not find \"iswdigit\" in ntdll\n");

    p_iswlower = (void *)GetProcAddress(ntdll, "iswlower");
    if (!p_iswlower)
        WINE_ERR("Could not find \"iswlower\" in ntdll\n");

    p_iswspace = (void *)GetProcAddress(ntdll, "iswspace");
    if (!p_iswspace)
        WINE_ERR("Could not find \"iswspace\" in ntdll\n");

    p_iswxdigit = (void *)GetProcAddress(ntdll, "iswxdigit");
    if (!p_iswxdigit)
        WINE_ERR("Could not find \"iswxdigit\" in ntdll\n");

    p_isxdigit = (void *)GetProcAddress(ntdll, "isxdigit");
    if (!p_isxdigit)
        WINE_ERR("Could not find \"isxdigit\" in ntdll\n");

    p_mbstowcs = (void *)GetProcAddress(ntdll, "mbstowcs");
    if (!p_mbstowcs)
        WINE_ERR("Could not find \"mbstowcs\" in ntdll\n");

    p_memchr = (void *)GetProcAddress(ntdll, "memchr");
    if (!p_memchr)
        WINE_ERR("Could not find \"memchr\" in ntdll\n");

    p_memcmp = (void *)GetProcAddress(ntdll, "memcmp");
    if (!p_memcmp)
        WINE_ERR("Could not find \"memcmp\" in ntdll\n");

    p_memcpy = (void *)GetProcAddress(ntdll, "memcpy");
    if (!p_memcpy)
        WINE_ERR("Could not find \"memcpy\" in ntdll\n");

    p_memmove = (void *)GetProcAddress(ntdll, "memmove");
    if (!p_memmove)
        WINE_ERR("Could not find \"memmove\" in ntdll\n");

    p_memset = (void *)GetProcAddress(ntdll, "memset");
    if (!p_memset)
        WINE_ERR("Could not find \"memset\" in ntdll\n");

    p_strcat = (void *)GetProcAddress(ntdll, "strcat");
    if (!p_strcat)
        WINE_ERR("Could not find \"strcat\" in ntdll\n");

    p_strchr = (void *)GetProcAddress(ntdll, "strchr");
    if (!p_strchr)
        WINE_ERR("Could not find \"strchr\" in ntdll\n");

    p_strcmp = (void *)GetProcAddress(ntdll, "strcmp");
    if (!p_strcmp)
        WINE_ERR("Could not find \"strcmp\" in ntdll\n");

    p_strcpy = (void *)GetProcAddress(ntdll, "strcpy");
    if (!p_strcpy)
        WINE_ERR("Could not find \"strcpy\" in ntdll\n");

    p_strcspn = (void *)GetProcAddress(ntdll, "strcspn");
    if (!p_strcspn)
        WINE_ERR("Could not find \"strcspn\" in ntdll\n");

    p_strlen = (void *)GetProcAddress(ntdll, "strlen");
    if (!p_strlen)
        WINE_ERR("Could not find \"strlen\" in ntdll\n");

    p_strncat = (void *)GetProcAddress(ntdll, "strncat");
    if (!p_strncat)
        WINE_ERR("Could not find \"strncat\" in ntdll\n");

    p_strncmp = (void *)GetProcAddress(ntdll, "strncmp");
    if (!p_strncmp)
        WINE_ERR("Could not find \"strncmp\" in ntdll\n");

    p_strncpy = (void *)GetProcAddress(ntdll, "strncpy");
    if (!p_strncpy)
        WINE_ERR("Could not find \"strncpy\" in ntdll\n");

    p_strpbrk = (void *)GetProcAddress(ntdll, "strpbrk");
    if (!p_strpbrk)
        WINE_ERR("Could not find \"strpbrk\" in ntdll\n");

    p_strrchr = (void *)GetProcAddress(ntdll, "strrchr");
    if (!p_strrchr)
        WINE_ERR("Could not find \"strrchr\" in ntdll\n");

    p_strspn = (void *)GetProcAddress(ntdll, "strspn");
    if (!p_strspn)
        WINE_ERR("Could not find \"strspn\" in ntdll\n");

    p_strstr = (void *)GetProcAddress(ntdll, "strstr");
    if (!p_strstr)
        WINE_ERR("Could not find \"strstr\" in ntdll\n");

    p_strtol = (void *)GetProcAddress(ntdll, "strtol");
    if (!p_strtol)
        WINE_ERR("Could not find \"strtol\" in ntdll\n");

    p_strtoul = (void *)GetProcAddress(ntdll, "strtoul");
    if (!p_strtoul)
        WINE_ERR("Could not find \"strtoul\" in ntdll\n");

    p_tolower = (void *)GetProcAddress(ntdll, "tolower");
    if (!p_tolower)
        WINE_ERR("Could not find \"tolower\" in ntdll\n");

    p_toupper = (void *)GetProcAddress(ntdll, "toupper");
    if (!p_toupper)
        WINE_ERR("Could not find \"toupper\" in ntdll\n");

    p_towlower = (void *)GetProcAddress(ntdll, "towlower");
    if (!p_towlower)
        WINE_ERR("Could not find \"towlower\" in ntdll\n");

    p_towupper = (void *)GetProcAddress(ntdll, "towupper");
    if (!p_towupper)
        WINE_ERR("Could not find \"towupper\" in ntdll\n");

    p_wcscat = (void *)GetProcAddress(ntdll, "wcscat");
    if (!p_wcscat)
        WINE_ERR("Could not find \"wcscat\" in ntdll\n");

    p_wcschr = (void *)GetProcAddress(ntdll, "wcschr");
    if (!p_wcschr)
        WINE_ERR("Could not find \"wcschr\" in ntdll\n");

    p_wcscmp = (void *)GetProcAddress(ntdll, "wcscmp");
    if (!p_wcscmp)
        WINE_ERR("Could not find \"wcscmp\" in ntdll\n");

    p_wcscpy = (void *)GetProcAddress(ntdll, "wcscpy");
    if (!p_wcscpy)
        WINE_ERR("Could not find \"wcscpy\" in ntdll\n");

    p_wcscspn = (void *)GetProcAddress(ntdll, "wcscspn");
    if (!p_wcscspn)
        WINE_ERR("Could not find \"wcscspn\" in ntdll\n");

    p_wcslen = (void *)GetProcAddress(ntdll, "wcslen");
    if (!p_wcslen)
        WINE_ERR("Could not find \"wcslen\" in ntdll\n");

    p_wcsncat = (void *)GetProcAddress(ntdll, "wcsncat");
    if (!p_wcsncat)
        WINE_ERR("Could not find \"wcsncat\" in ntdll\n");

    p_wcsncmp = (void *)GetProcAddress(ntdll, "wcsncmp");
    if (!p_wcsncmp)
        WINE_ERR("Could not find \"wcsncmp\" in ntdll\n");

    p_wcsncpy = (void *)GetProcAddress(ntdll, "wcsncpy");
    if (!p_wcsncpy)
        WINE_ERR("Could not find \"wcsncpy\" in ntdll\n");

    p_wcspbrk = (void *)GetProcAddress(ntdll, "wcspbrk");
    if (!p_wcspbrk)
        WINE_ERR("Could not find \"wcspbrk\" in ntdll\n");

    p_wcsrchr = (void *)GetProcAddress(ntdll, "wcsrchr");
    if (!p_wcsrchr)
        WINE_ERR("Could not find \"wcsrchr\" in ntdll\n");

    p_wcsspn = (void *)GetProcAddress(ntdll, "wcsspn");
    if (!p_wcsspn)
        WINE_ERR("Could not find \"wcsspn\" in ntdll\n");

    p_wcsstr = (void *)GetProcAddress(ntdll, "wcsstr");
    if (!p_wcsstr)
        WINE_ERR("Could not find \"wcsstr\" in ntdll\n");

    p_wcstok = (void *)GetProcAddress(ntdll, "wcstok");
    if (!p_wcstok)
        WINE_ERR("Could not find \"wcstok\" in ntdll\n");

    p_wcstol = (void *)GetProcAddress(ntdll, "wcstol");
    if (!p_wcstol)
        WINE_ERR("Could not find \"wcstol\" in ntdll\n");

    p_wcstombs = (void *)GetProcAddress(ntdll, "wcstombs");
    if (!p_wcstombs)
        WINE_ERR("Could not find \"wcstombs\" in ntdll\n");

    p_wcstoul = (void *)GetProcAddress(ntdll, "wcstoul");
    if (!p_wcstoul)
        WINE_ERR("Could not find \"wcstoul\" in ntdll\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    WINE_TRACE("Host ntdll DllMain(%p, %u, %p)\n", mod, reason, reserved);
    if (!qemu_ops)
        return TRUE;

    return qemu_ops->qemu_DllMain(reason, reserved);
}

#endif
