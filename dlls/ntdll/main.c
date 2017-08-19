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
#include "ntdll.h"

struct qemu_set_callbacks
{
    struct qemu_syscall super;
    uint64_t exception_handler;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_set_callbacks call;
    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            call.super.id = QEMU_SYSCALL_ID(CALL_SET_CALLBACKS);
            call.exception_handler = (uint64_t)qemu_exception_handler;
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
    qemu__itoa,
    qemu__ltoa,
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
    qemu__ultoa,
    qemu_atoi,
    qemu_atol,
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
    qemu_isxdigit,
    qemu_LdrFindEntryForAddress,
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
    qemu_RtlCreateUnicodeString,
    qemu_RtlCreateUnicodeStringFromAsciiz,
    qemu_RtlCreateUserProcess,
    qemu_RtlCreateUserThread,
    qemu_RtlDeactivateActivationContext,
    qemu_RtlDecodePointer,
    qemu_RtlDecompressBuffer,
    qemu_RtlDecompressFragment,
    qemu_RtlDeleteCriticalSection,
    qemu_RtlDeleteRegistryValue,
    qemu_RtlDeleteResource,
    qemu_RtlDeleteSecurityObject,
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
    qemu_RtlRandom,
    qemu_RtlReAllocateHeap,
    qemu_RtlReleaseActivationContext,
    qemu_RtlReleasePebLock,
    qemu_RtlReleaseResource,
    qemu_RtlReleaseSRWLockExclusive,
    qemu_RtlReleaseSRWLockShared,
    qemu_RtlRestoreContext,
    qemu_RtlRunOnceBeginInitialize,
    qemu_RtlRunOnceComplete,
    qemu_RtlRunOnceExecuteOnce,
    qemu_RtlRunOnceInitialize,
    qemu_RtlSetCriticalSectionSpinCount,
    qemu_RtlSetCurrentDirectory_U,
    qemu_RtlSetCurrentTransaction,
    qemu_RtlSetHeapInformation,
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
    qemu_RtlUpcaseUnicodeChar,
    qemu_RtlUpcaseUnicodeString,
    qemu_RtlUpcaseUnicodeStringToAnsiString,
    qemu_RtlUpcaseUnicodeStringToCountedOemString,
    qemu_RtlUpcaseUnicodeStringToOemString,
    qemu_RtlUpcaseUnicodeToMultiByteN,
    qemu_RtlUpcaseUnicodeToOemN,
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
    qemu_VerSetConditionMask,
    qemu_wcsrchr,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE ntdll;

    WINE_TRACE("Loading host-side ntdll wrapper.\n");

    ntdll = GetModuleHandleA("ntdll.dll");
    if (!ntdll)
        WINE_ERR("ntdll.dll not loaded\n");

    p___isascii = (void *)GetProcAddress(ntdll, "__isascii");
    p___iscsym = (void *)GetProcAddress(ntdll, "__iscsym");
    p___iscsymf = (void *)GetProcAddress(ntdll, "__iscsymf");
    p___toascii = (void *)GetProcAddress(ntdll, "__toascii");
    p__atoi64 = (void *)GetProcAddress(ntdll, "_atoi64");
    p__i64toa = (void *)GetProcAddress(ntdll, "_i64toa");
    p__itoa = (void *)GetProcAddress(ntdll, "_itoa");
    p__ltoa = (void *)GetProcAddress(ntdll, "_ltoa");
    p__memccpy = (void *)GetProcAddress(ntdll, "_memccpy");
    p__memicmp = (void *)GetProcAddress(ntdll, "_memicmp");
    p__splitpath = (void *)GetProcAddress(ntdll, "_splitpath");
    p__stricmp = (void *)GetProcAddress(ntdll, "_stricmp");
    p__strlwr = (void *)GetProcAddress(ntdll, "_strlwr");
    p__strnicmp = (void *)GetProcAddress(ntdll, "_strnicmp");
    p__strupr = (void *)GetProcAddress(ntdll, "_strupr");
    p__tolower = (void *)GetProcAddress(ntdll, "_tolower");
    p__toupper = (void *)GetProcAddress(ntdll, "_toupper");
    p__ui64toa = (void *)GetProcAddress(ntdll, "_ui64toa");
    p__ultoa = (void *)GetProcAddress(ntdll, "_ultoa");
    p_atoi = (void *)GetProcAddress(ntdll, "atoi");
    p_atol = (void *)GetProcAddress(ntdll, "atol");
    p_isalnum = (void *)GetProcAddress(ntdll, "isalnum");
    p_isalpha = (void *)GetProcAddress(ntdll, "isalpha");
    p_iscntrl = (void *)GetProcAddress(ntdll, "iscntrl");
    p_isdigit = (void *)GetProcAddress(ntdll, "isdigit");
    p_isgraph = (void *)GetProcAddress(ntdll, "isgraph");
    p_islower = (void *)GetProcAddress(ntdll, "islower");
    p_isprint = (void *)GetProcAddress(ntdll, "isprint");
    p_ispunct = (void *)GetProcAddress(ntdll, "ispunct");
    p_isspace = (void *)GetProcAddress(ntdll, "isspace");
    p_isupper = (void *)GetProcAddress(ntdll, "isupper");
    p_isxdigit = (void *)GetProcAddress(ntdll, "isxdigit");
    p_memchr = (void *)GetProcAddress(ntdll, "memchr");
    p_memcmp = (void *)GetProcAddress(ntdll, "memcmp");
    p_memcpy = (void *)GetProcAddress(ntdll, "memcpy");
    p_memmove = (void *)GetProcAddress(ntdll, "memmove");
    p_memset = (void *)GetProcAddress(ntdll, "memset");
    p_strcat = (void *)GetProcAddress(ntdll, "strcat");
    p_strchr = (void *)GetProcAddress(ntdll, "strchr");
    p_strcmp = (void *)GetProcAddress(ntdll, "strcmp");
    p_strcpy = (void *)GetProcAddress(ntdll, "strcpy");
    p_strcspn = (void *)GetProcAddress(ntdll, "strcspn");
    p_strlen = (void *)GetProcAddress(ntdll, "strlen");
    p_strncat = (void *)GetProcAddress(ntdll, "strncat");
    p_strncmp = (void *)GetProcAddress(ntdll, "strncmp");
    p_strncpy = (void *)GetProcAddress(ntdll, "strncpy");
    p_strpbrk = (void *)GetProcAddress(ntdll, "strpbrk");
    p_strrchr = (void *)GetProcAddress(ntdll, "strrchr");
    p_strspn = (void *)GetProcAddress(ntdll, "strspn");
    p_strstr = (void *)GetProcAddress(ntdll, "strstr");
    p_strtol = (void *)GetProcAddress(ntdll, "strtol");
    p_strtoul = (void *)GetProcAddress(ntdll, "strtoul");
    p_tolower = (void *)GetProcAddress(ntdll, "tolower");
    p_toupper = (void *)GetProcAddress(ntdll, "toupper");
    p_wcsrchr = (void *)GetProcAddress(ntdll, "wcsrchr");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
