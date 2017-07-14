#ifndef KERNEL32_H
#define KERNEL32_H

enum kernel32_calls
{
    CALL__HREAD = 0,
    CALL__HWRITE,
    CALL__LCLOSE,
    CALL__LCREAT,
    CALL__LLSEEK,
    CALL__LOPEN,
    CALL__LREAD,
    CALL__LWRITE,
    CALL_AREFILEAPISANSI,
    CALL_ASSIGNPROCESSTOJOBOBJECT,
    CALL_BINDIOCOMPLETIONCALLBACK,
    CALL_BUILDCOMMDCBA,
    CALL_BUILDCOMMDCBANDTIMEOUTSA,
    CALL_BUILDCOMMDCBANDTIMEOUTSW,
    CALL_BUILDCOMMDCBW,
    CALL_CALLNAMEDPIPEA,
    CALL_CALLNAMEDPIPEW,
    CALL_CANCELIO,
    CALL_CANCELIOEX,
    CALL_CANCELSYNCHRONOUSIO,
    CALL_CANCELTIMERQUEUETIMER,
    CALL_CANCELWAITABLETIMER,
    CALL_CHANGETIMERQUEUETIMER,
    CALL_CHECKREMOTEDEBUGGERPRESENT,
    CALL_CLEARCOMMBREAK,
    CALL_CLEARCOMMERROR,
    CALL_CLOSEHANDLE,
    CALL_COMMCONFIGDIALOGA,
    CALL_COMMCONFIGDIALOGW,
    CALL_COMPARESTRINGW,
    CALL_CONNECTNAMEDPIPE,
    CALL_CONTINUEDEBUGEVENT,
    CALL_CREATEEVENTA,
    CALL_CREATEEVENTEXA,
    CALL_CREATEEVENTEXW,
    CALL_CREATEEVENTW,
    CALL_CREATEFILE2,
    CALL_CREATEFILEA,
    CALL_CREATEFILEW,
    CALL_CREATEIOCOMPLETIONPORT,
    CALL_CREATEJOBOBJECTA,
    CALL_CREATEJOBOBJECTW,
    CALL_CREATEMAILSLOTA,
    CALL_CREATEMAILSLOTW,
    CALL_CREATEMEMORYRESOURCENOTIFICATION,
    CALL_CREATEMUTEXA,
    CALL_CREATEMUTEXEXA,
    CALL_CREATEMUTEXEXW,
    CALL_CREATEMUTEXW,
    CALL_CREATENAMEDPIPEA,
    CALL_CREATENAMEDPIPEW,
    CALL_CREATEPIPE,
    CALL_CREATESEMAPHOREA,
    CALL_CREATESEMAPHOREEXA,
    CALL_CREATESEMAPHOREEXW,
    CALL_CREATESEMAPHOREW,
    CALL_CREATETIMERQUEUE,
    CALL_CREATETIMERQUEUETIMER,
    CALL_CREATEWAITABLETIMERA,
    CALL_CREATEWAITABLETIMEREXA,
    CALL_CREATEWAITABLETIMEREXW,
    CALL_CREATEWAITABLETIMERW,
    CALL_DEBUGACTIVEPROCESS,
    CALL_DEBUGACTIVEPROCESSSTOP,
    CALL_DEBUGBREAK,
    CALL_DEBUGBREAKPROCESS,
    CALL_DEBUGSETPROCESSKILLONEXIT,
    CALL_DELETEFILEA,
    CALL_DELETEFILEW,
    CALL_DELETETIMERQUEUE,
    CALL_DELETETIMERQUEUEEX,
    CALL_DELETETIMERQUEUETIMER,
    CALL_DEVICEIOCONTROL,
    CALL_DISCONNECTNAMEDPIPE,
    CALL_ESCAPECOMMFUNCTION,
    CALL_EXITPROCESS,
    CALL_EXPANDENVIRONMENTSTRINGSA,
    CALL_EXPANDENVIRONMENTSTRINGSW,
    CALL_FINDCLOSE,
    CALL_FINDFIRSTFILEA,
    CALL_FINDFIRSTFILEEXA,
    CALL_FINDFIRSTFILEEXW,
    CALL_FINDFIRSTFILEW,
    CALL_FINDNEXTFILEA,
    CALL_FINDNEXTFILEW,
    CALL_FLUSHFILEBUFFERS,
    CALL_FORMATMESSAGEW,
    CALL_FREEENVIRONMENTSTRINGSA,
    CALL_FREEENVIRONMENTSTRINGSW,
    CALL_FREELIBRARY,
    CALL_GETACTIVEPROCESSORCOUNT,
    CALL_GETACTIVEPROCESSORGROUPCOUNT,
    CALL_GETCOMMANDLINEA,
    CALL_GETCOMMANDLINEW,
    CALL_GETCOMMCONFIG,
    CALL_GETCOMMMASK,
    CALL_GETCOMMMODEMSTATUS,
    CALL_GETCOMMPROPERTIES,
    CALL_GETCOMMSTATE,
    CALL_GETCOMMTIMEOUTS,
    CALL_GETCOMPRESSEDFILESIZEA,
    CALL_GETCOMPRESSEDFILESIZEW,
    CALL_GETCPINFOEXW,
    CALL_GETCURRENTPROCESS,
    CALL_GETCURRENTPROCESSID,
    CALL_GETCURRENTTHREADID,
    CALL_GETDATEFORMATA,
    CALL_GETDATEFORMATW,
    CALL_GETDEFAULTCOMMCONFIGA,
    CALL_GETDEFAULTCOMMCONFIGW,
    CALL_GETDEVICEPOWERSTATE,
    CALL_GETENVIRONMENTSTRINGSA,
    CALL_GETENVIRONMENTSTRINGSW,
    CALL_GETENVIRONMENTVARIABLEA,
    CALL_GETENVIRONMENTVARIABLEW,
    CALL_GETFILEATTRIBUTESA,
    CALL_GETFILEATTRIBUTESEXA,
    CALL_GETFILEATTRIBUTESEXW,
    CALL_GETFILEATTRIBUTESW,
    CALL_GETFILEINFORMATIONBYHANDLE,
    CALL_GETFILEINFORMATIONBYHANDLEEX,
    CALL_GETFILESIZE,
    CALL_GETFILESIZEEX,
    CALL_GETFILETIME,
    CALL_GETFILETYPE,
    CALL_GETFINALPATHNAMEBYHANDLEA,
    CALL_GETFINALPATHNAMEBYHANDLEW,
    CALL_GETFIRMWAREENVIRONMENTVARIABLEA,
    CALL_GETFIRMWAREENVIRONMENTVARIABLEW,
    CALL_GETLARGEPAGEMINIMUM,
    CALL_GETLASTERROR,
    CALL_GETLOCALTIME,
    CALL_GETMAILSLOTINFO,
    CALL_GETMODULEFILENAMEA,
    CALL_GETMODULEFILENAMEW,
    CALL_GETMODULEHANDLEA,
    CALL_GETMODULEHANDLEEXA,
    CALL_GETMODULEHANDLEW,
    CALL_GETNAMEDPIPEHANDLESTATEA,
    CALL_GETNAMEDPIPEHANDLESTATEW,
    CALL_GETNAMEDPIPEINFO,
    CALL_GETNATIVESYSTEMINFO,
    CALL_GETOVERLAPPEDRESULT,
    CALL_GETPROCADDRESS,
    CALL_GETPROCESSHEAP,
    CALL_GETQUEUEDCOMPLETIONSTATUS,
    CALL_GETSTARTUPINFOA,
    CALL_GETSTARTUPINFOW,
    CALL_GETSTDHANDLE,
    CALL_GETSYSTEMINFO,
    CALL_GETSYSTEMPOWERSTATUS,
    CALL_GETSYSTEMTIMEASFILETIME,
    CALL_GETTICKCOUNT,
    CALL_GETTIMEFORMATA,
    CALL_GETTIMEFORMATW,
    CALL_GETVERSION,
    CALL_GETVERSIONEXA,
    CALL_GETVERSIONEXW,
    CALL_GLOBALALLOC,
    CALL_GLOBALFREE,
    CALL_HEAPALLOC,
    CALL_HEAPFREE,
    CALL_INITIALIZECRITICALSECTION,
    CALL_INITIALIZECRITICALSECTIONANDSPINCOUNT,
    CALL_INITONCEBEGININITIALIZE,
    CALL_INITONCECOMPLETE,
    CALL_INITONCEEXECUTEONCE,
    CALL_ISDEBUGGERPRESENT,
    CALL_ISPROCESSINJOB,
    CALL_ISPROCESSORFEATUREPRESENT,
    CALL_ISSYSTEMRESUMEAUTOMATIC,
    CALL_K32ENUMDEVICEDRIVERS,
    CALL_K32GETDEVICEDRIVERBASENAMEA,
    CALL_K32GETDEVICEDRIVERBASENAMEW,
    CALL_K32GETDEVICEDRIVERFILENAMEA,
    CALL_K32GETDEVICEDRIVERFILENAMEW,
    CALL_K32GETPERFORMANCEINFO,
    CALL_LOADLIBRARYA,
    CALL_LOADLIBRARYW,
    CALL_LOCALFREE,
    CALL_LOCKFILE,
    CALL_LOCKFILEEX,
    CALL_LSTRCATA,
    CALL_LSTRCATW,
    CALL_LSTRCMPW,
    CALL_LSTRCPYA,
    CALL_LSTRCPYNA,
    CALL_LSTRCPYNW,
    CALL_LSTRCPYW,
    CALL_LSTRLENA,
    CALL_LSTRLENW,
    CALL_MAKECRITICALSECTIONGLOBAL,
    CALL_MULTIBYTETOWIDECHAR,
    CALL_OPENEVENTA,
    CALL_OPENEVENTW,
    CALL_OPENFILE,
    CALL_OPENFILEBYID,
    CALL_OPENJOBOBJECTA,
    CALL_OPENJOBOBJECTW,
    CALL_OPENMUTEXA,
    CALL_OPENMUTEXW,
    CALL_OPENSEMAPHOREA,
    CALL_OPENSEMAPHOREW,
    CALL_OPENVXDHANDLE,
    CALL_OPENWAITABLETIMERA,
    CALL_OPENWAITABLETIMERW,
    CALL_OUTPUTDEBUGSTRINGA,
    CALL_OUTPUTDEBUGSTRINGW,
    CALL_PEEKNAMEDPIPE,
    CALL_POSTQUEUEDCOMPLETIONSTATUS,
    CALL_POWERCLEARREQUEST,
    CALL_POWERCREATEREQUEST,
    CALL_POWERSETREQUEST,
    CALL_PULSEEVENT,
    CALL_PURGECOMM,
    CALL_QUERYINFORMATIONJOBOBJECT,
    CALL_QUERYMEMORYRESOURCENOTIFICATION,
    CALL_QUERYPERFORMANCECOUNTER,
    CALL_QUERYPERFORMANCEFREQUENCY,
    CALL_READFILE,
    CALL_READFILEEX,
    CALL_READFILESCATTER,
    CALL_REGISTERWAITFORSINGLEOBJECT,
    CALL_REGISTERWAITFORSINGLEOBJECTEX,
    CALL_REINITIALIZECRITICALSECTION,
    CALL_RELEASEMUTEX,
    CALL_RELEASESEMAPHORE,
    CALL_REPLACEFILEA,
    CALL_REPLACEFILEW,
    CALL_REQUESTWAKEUPLATENCY,
    CALL_RESETEVENT,
    CALL_SETCOMMBREAK,
    CALL_SETCOMMCONFIG,
    CALL_SETCOMMMASK,
    CALL_SETCOMMSTATE,
    CALL_SETCOMMTIMEOUTS,
    CALL_SETCONSOLECTRLHANDLER,
    CALL_SETDEFAULTCOMMCONFIGA,
    CALL_SETDEFAULTCOMMCONFIGW,
    CALL_SETENDOFFILE,
    CALL_SETENVIRONMENTVARIABLEA,
    CALL_SETENVIRONMENTVARIABLEW,
    CALL_SETEVENT,
    CALL_SETFILEAPISTOANSI,
    CALL_SETFILEAPISTOOEM,
    CALL_SETFILEATTRIBUTESA,
    CALL_SETFILEATTRIBUTESW,
    CALL_SETFILECOMPLETIONNOTIFICATIONMODES,
    CALL_SETFILEINFORMATIONBYHANDLE,
    CALL_SETFILEPOINTER,
    CALL_SETFILEPOINTEREX,
    CALL_SETFILETIME,
    CALL_SETFILEVALIDDATA,
    CALL_SETHANDLECOUNT,
    CALL_SETINFORMATIONJOBOBJECT,
    CALL_SETLASTERROR,
    CALL_SETMAILSLOTINFO,
    CALL_SETNAMEDPIPEHANDLESTATE,
    CALL_SETSTDHANDLE,
    CALL_SETSYSTEMPOWERSTATE,
    CALL_SETTHREADEXECUTIONSTATE,
    CALL_SETUNHANDLEDEXCEPTIONFILTER,
    CALL_SETUPCOMM,
    CALL_SETWAITABLETIMER,
    CALL_SETWAITABLETIMEREX,
    CALL_SIGNALOBJECTANDWAIT,
    CALL_SLEEP,
    CALL_SLEEPCONDITIONVARIABLECS,
    CALL_SLEEPCONDITIONVARIABLESRW,
    CALL_SLEEPEX,
    CALL_SWITCHTOTHREAD,
    CALL_TERMINATEJOBOBJECT,
    CALL_TERMINATEPROCESS,
    CALL_TLSGETVALUE,
    CALL_TRANSACTNAMEDPIPE,
    CALL_TRANSMITCOMMCHAR,
    CALL_UNHANDLEDEXCEPTIONFILTER,
    CALL_UNINITIALIZECRITICALSECTION,
    CALL_UNLOCKFILE,
    CALL_UNLOCKFILEEX,
    CALL_UNREGISTERWAIT,
    CALL_UNREGISTERWAITEX,
    CALL_VERIFYVERSIONINFOA,
    CALL_VERIFYVERSIONINFOW,
    CALL_VIRTUALPROTECT,
    CALL_VIRTUALQUERY,
    CALL_WAITCOMMEVENT,
    CALL_WAITFORDEBUGEVENT,
    CALL_WAITFORMULTIPLEOBJECTS,
    CALL_WAITFORMULTIPLEOBJECTSEX,
    CALL_WAITFORSINGLEOBJECT,
    CALL_WAITFORSINGLEOBJECTEX,
    CALL_WAITNAMEDPIPEA,
    CALL_WAITNAMEDPIPEW,
    CALL_WIDECHARTOMULTIBYTE,
    CALL_WRITEFILE,
    CALL_WRITEFILEEX,
    CALL_WRITEFILEGATHER,
};

#ifndef QEMU_DLL_GUEST
extern const struct qemu_ops *qemu_ops;

void qemu__hread(struct qemu_syscall *call);
void qemu__hwrite(struct qemu_syscall *call);
void qemu__lclose(struct qemu_syscall *call);
void qemu__lcreat(struct qemu_syscall *call);
void qemu__llseek(struct qemu_syscall *call);
void qemu__lopen(struct qemu_syscall *call);
void qemu__lread(struct qemu_syscall *call);
void qemu__lwrite(struct qemu_syscall *call);
void qemu_AreFileApisANSI(struct qemu_syscall *call);
void qemu_AssignProcessToJobObject(struct qemu_syscall *call);
void qemu_BindIoCompletionCallback(struct qemu_syscall *call);
void qemu_BuildCommDCBA(struct qemu_syscall *call);
void qemu_BuildCommDCBAndTimeoutsA(struct qemu_syscall *call);
void qemu_BuildCommDCBAndTimeoutsW(struct qemu_syscall *call);
void qemu_BuildCommDCBW(struct qemu_syscall *call);
void qemu_CallNamedPipeA(struct qemu_syscall *call);
void qemu_CallNamedPipeW(struct qemu_syscall *call);
void qemu_CancelIo(struct qemu_syscall *call);
void qemu_CancelIoEx(struct qemu_syscall *call);
void qemu_CancelSynchronousIo(struct qemu_syscall *call);
void qemu_CancelTimerQueueTimer(struct qemu_syscall *call);
void qemu_CancelWaitableTimer(struct qemu_syscall *call);
void qemu_ChangeTimerQueueTimer(struct qemu_syscall *call);
void qemu_CheckRemoteDebuggerPresent(struct qemu_syscall *call);
void qemu_ClearCommBreak(struct qemu_syscall *call);
void qemu_ClearCommError(struct qemu_syscall *call);
void qemu_CloseHandle(struct qemu_syscall *call);
void qemu_CommConfigDialogA(struct qemu_syscall *call);
void qemu_CommConfigDialogW(struct qemu_syscall *call);
void qemu_CompareStringW(struct qemu_syscall *call);
void qemu_ConnectNamedPipe(struct qemu_syscall *call);
void qemu_ContinueDebugEvent(struct qemu_syscall *call);
void qemu_CreateEventA(struct qemu_syscall *call);
void qemu_CreateEventExA(struct qemu_syscall *call);
void qemu_CreateEventExW(struct qemu_syscall *call);
void qemu_CreateEventW(struct qemu_syscall *call);
void qemu_CreateFile2(struct qemu_syscall *call);
void qemu_CreateFileA(struct qemu_syscall *call);
void qemu_CreateFileW(struct qemu_syscall *call);
void qemu_CreateIoCompletionPort(struct qemu_syscall *call);
void qemu_CreateJobObjectA(struct qemu_syscall *call);
void qemu_CreateJobObjectW(struct qemu_syscall *call);
void qemu_CreateMailslotA(struct qemu_syscall *call);
void qemu_CreateMailslotW(struct qemu_syscall *call);
void qemu_CreateMemoryResourceNotification(struct qemu_syscall *call);
void qemu_CreateMutexA(struct qemu_syscall *call);
void qemu_CreateMutexExA(struct qemu_syscall *call);
void qemu_CreateMutexExW(struct qemu_syscall *call);
void qemu_CreateMutexW(struct qemu_syscall *call);
void qemu_CreateNamedPipeA(struct qemu_syscall *call);
void qemu_CreateNamedPipeW(struct qemu_syscall *call);
void qemu_CreatePipe(struct qemu_syscall *call);
void qemu_CreateSemaphoreA(struct qemu_syscall *call);
void qemu_CreateSemaphoreExA(struct qemu_syscall *call);
void qemu_CreateSemaphoreExW(struct qemu_syscall *call);
void qemu_CreateSemaphoreW(struct qemu_syscall *call);
void qemu_CreateTimerQueue(struct qemu_syscall *call);
void qemu_CreateTimerQueueTimer(struct qemu_syscall *call);
void qemu_CreateWaitableTimerA(struct qemu_syscall *call);
void qemu_CreateWaitableTimerExA(struct qemu_syscall *call);
void qemu_CreateWaitableTimerExW(struct qemu_syscall *call);
void qemu_CreateWaitableTimerW(struct qemu_syscall *call);
void qemu_DebugActiveProcess(struct qemu_syscall *call);
void qemu_DebugActiveProcessStop(struct qemu_syscall *call);
void qemu_DebugBreak(struct qemu_syscall *call);
void qemu_DebugBreakProcess(struct qemu_syscall *call);
void qemu_DebugSetProcessKillOnExit(struct qemu_syscall *call);
void qemu_DeleteFileA(struct qemu_syscall *call);
void qemu_DeleteFileW(struct qemu_syscall *call);
void qemu_DeleteTimerQueue(struct qemu_syscall *call);
void qemu_DeleteTimerQueueEx(struct qemu_syscall *call);
void qemu_DeleteTimerQueueTimer(struct qemu_syscall *call);
void qemu_DeviceIoControl(struct qemu_syscall *call);
void qemu_DisconnectNamedPipe(struct qemu_syscall *call);
void qemu_EscapeCommFunction(struct qemu_syscall *call);
void qemu_ExitProcess(struct qemu_syscall *call);
void qemu_ExpandEnvironmentStringsA(struct qemu_syscall *call);
void qemu_ExpandEnvironmentStringsW(struct qemu_syscall *call);
void qemu_FindClose(struct qemu_syscall *call);
void qemu_FindFirstFileA(struct qemu_syscall *call);
void qemu_FindFirstFileExA(struct qemu_syscall *call);
void qemu_FindFirstFileExW(struct qemu_syscall *call);
void qemu_FindFirstFileW(struct qemu_syscall *call);
void qemu_FindNextFileA(struct qemu_syscall *call);
void qemu_FindNextFileW(struct qemu_syscall *call);
void qemu_FlushFileBuffers(struct qemu_syscall *call);
void qemu_FormatMessageW(struct qemu_syscall *call);
void qemu_FreeEnvironmentStringsA(struct qemu_syscall *call);
void qemu_FreeEnvironmentStringsW(struct qemu_syscall *call);
void qemu_FreeLibrary(struct qemu_syscall *call);
void qemu_GetActiveProcessorCount(struct qemu_syscall *call);
void qemu_GetActiveProcessorGroupCount(struct qemu_syscall *call);
void qemu_GetCommandLineA(struct qemu_syscall *c);
void qemu_GetCommandLineA(struct qemu_syscall *call);
void qemu_GetCommandLineW(struct qemu_syscall *c);
void qemu_GetCommandLineW(struct qemu_syscall *call);
void qemu_GetCommConfig(struct qemu_syscall *call);
void qemu_GetCommMask(struct qemu_syscall *call);
void qemu_GetCommModemStatus(struct qemu_syscall *call);
void qemu_GetCommProperties(struct qemu_syscall *call);
void qemu_GetCommState(struct qemu_syscall *call);
void qemu_GetCommTimeouts(struct qemu_syscall *call);
void qemu_GetCompressedFileSizeA(struct qemu_syscall *call);
void qemu_GetCompressedFileSizeW(struct qemu_syscall *call);
void qemu_GetCPInfoExW(struct qemu_syscall *call);
void qemu_GetCurrentProcess(struct qemu_syscall *call);
void qemu_GetCurrentProcessId(struct qemu_syscall *call);
void qemu_GetCurrentThreadId(struct qemu_syscall *call);
void qemu_GetDateFormatA(struct qemu_syscall *call);
void qemu_GetDateFormatW(struct qemu_syscall *call);
void qemu_GetDefaultCommConfigA(struct qemu_syscall *call);
void qemu_GetDefaultCommConfigW(struct qemu_syscall *call);
void qemu_GetDevicePowerState(struct qemu_syscall *call);
void qemu_GetEnvironmentStringsA(struct qemu_syscall *call);
void qemu_GetEnvironmentStringsW(struct qemu_syscall *call);
void qemu_GetEnvironmentVariableA(struct qemu_syscall *call);
void qemu_GetEnvironmentVariableW(struct qemu_syscall *call);
void qemu_GetFileAttributesA(struct qemu_syscall *call);
void qemu_GetFileAttributesExA(struct qemu_syscall *call);
void qemu_GetFileAttributesExW(struct qemu_syscall *call);
void qemu_GetFileAttributesW(struct qemu_syscall *call);
void qemu_GetFileInformationByHandle(struct qemu_syscall *call);
void qemu_GetFileInformationByHandleEx(struct qemu_syscall *call);
void qemu_GetFileSize(struct qemu_syscall *call);
void qemu_GetFileSizeEx(struct qemu_syscall *call);
void qemu_GetFileTime(struct qemu_syscall *call);
void qemu_GetFileType(struct qemu_syscall *call);
void qemu_GetFinalPathNameByHandleA(struct qemu_syscall *call);
void qemu_GetFinalPathNameByHandleW(struct qemu_syscall *call);
void qemu_GetFirmwareEnvironmentVariableA(struct qemu_syscall *call);
void qemu_GetFirmwareEnvironmentVariableW(struct qemu_syscall *call);
void qemu_GetLargePageMinimum(struct qemu_syscall *call);
void qemu_GetLastError(struct qemu_syscall *call);
void qemu_GetLocalTime(struct qemu_syscall *call);
void qemu_GetMailslotInfo(struct qemu_syscall *call);
void qemu_GetModuleFileNameA(struct qemu_syscall *call);
void qemu_GetModuleFileNameW(struct qemu_syscall *call);
void qemu_GetModuleHandleA(struct qemu_syscall *call);
void qemu_GetModuleHandleExA(struct qemu_syscall *call);
void qemu_GetModuleHandleW(struct qemu_syscall *call);
void qemu_GetNamedPipeHandleStateA(struct qemu_syscall *call);
void qemu_GetNamedPipeHandleStateW(struct qemu_syscall *call);
void qemu_GetNamedPipeInfo(struct qemu_syscall *call);
void qemu_GetNativeSystemInfo(struct qemu_syscall *call);
void qemu_GetOverlappedResult(struct qemu_syscall *call);
void qemu_GetProcAddress(struct qemu_syscall *call);
void qemu_GetProcessHeap(struct qemu_syscall *call);
void qemu_GetQueuedCompletionStatus(struct qemu_syscall *call);
void qemu_GetStartupInfoA(struct qemu_syscall *call);
void qemu_GetStartupInfoW(struct qemu_syscall *call);
void qemu_GetStdHandle(struct qemu_syscall *call);
void qemu_GetSystemInfo(struct qemu_syscall *call);
void qemu_GetSystemPowerStatus(struct qemu_syscall *call);
void qemu_GetSystemTimeAsFileTime(struct qemu_syscall *call);
void qemu_GetTickCount(struct qemu_syscall *call);
void qemu_GetTimeFormatA(struct qemu_syscall *call);
void qemu_GetTimeFormatW(struct qemu_syscall *call);
void qemu_GetVersion(struct qemu_syscall *call);
void qemu_GetVersionExA(struct qemu_syscall *call);
void qemu_GetVersionExW(struct qemu_syscall *call);
void qemu_GlobalAlloc(struct qemu_syscall *call);
void qemu_GlobalFree(struct qemu_syscall *call);
void qemu_HeapAlloc(struct qemu_syscall *call);
void qemu_HeapFree(struct qemu_syscall *call);
void qemu_InitializeCriticalSection(struct qemu_syscall *call);
void qemu_InitializeCriticalSectionAndSpinCount(struct qemu_syscall *call);
void qemu_InitOnceBeginInitialize(struct qemu_syscall *call);
void qemu_InitOnceComplete(struct qemu_syscall *call);
void qemu_InitOnceExecuteOnce(struct qemu_syscall *call);
void qemu_IsDebuggerPresent(struct qemu_syscall *call);
void qemu_IsProcessInJob(struct qemu_syscall *call);
void qemu_IsProcessorFeaturePresent(struct qemu_syscall *call);
void qemu_IsSystemResumeAutomatic(struct qemu_syscall *call);
void qemu_K32EnumDeviceDrivers(struct qemu_syscall *call);
void qemu_K32GetDeviceDriverBaseNameA(struct qemu_syscall *call);
void qemu_K32GetDeviceDriverBaseNameW(struct qemu_syscall *call);
void qemu_K32GetDeviceDriverFileNameA(struct qemu_syscall *call);
void qemu_K32GetDeviceDriverFileNameW(struct qemu_syscall *call);
void qemu_K32GetPerformanceInfo(struct qemu_syscall *call);
void qemu_LoadLibraryA(struct qemu_syscall *call);
void qemu_LoadLibraryW(struct qemu_syscall *call);
void qemu_LocalFree(struct qemu_syscall *call);
void qemu_LockFile(struct qemu_syscall *call);
void qemu_LockFileEx(struct qemu_syscall *call);
void qemu_lstrcatA(struct qemu_syscall *call);
void qemu_lstrcatW(struct qemu_syscall *call);
void qemu_lstrcmpW(struct qemu_syscall *call);
void qemu_lstrcpyA(struct qemu_syscall *call);
void qemu_lstrcpynA(struct qemu_syscall *call);
void qemu_lstrcpynW(struct qemu_syscall *call);
void qemu_lstrcpyW(struct qemu_syscall *call);
void qemu_lstrlenA(struct qemu_syscall *call);
void qemu_lstrlenW(struct qemu_syscall *call);
void qemu_MakeCriticalSectionGlobal(struct qemu_syscall *call);
void qemu_MultiByteToWideChar(struct qemu_syscall *call);
void qemu_OpenEventA(struct qemu_syscall *call);
void qemu_OpenEventW(struct qemu_syscall *call);
void qemu_OpenFile(struct qemu_syscall *call);
void qemu_OpenFileById(struct qemu_syscall *call);
void qemu_OpenJobObjectA(struct qemu_syscall *call);
void qemu_OpenJobObjectW(struct qemu_syscall *call);
void qemu_OpenMutexA(struct qemu_syscall *call);
void qemu_OpenMutexW(struct qemu_syscall *call);
void qemu_OpenSemaphoreA(struct qemu_syscall *call);
void qemu_OpenSemaphoreW(struct qemu_syscall *call);
void qemu_OpenVxDHandle(struct qemu_syscall *call);
void qemu_OpenWaitableTimerA(struct qemu_syscall *call);
void qemu_OpenWaitableTimerW(struct qemu_syscall *call);
void qemu_OutputDebugStringA(struct qemu_syscall *call);
void qemu_OutputDebugStringW(struct qemu_syscall *call);
void qemu_PeekNamedPipe(struct qemu_syscall *call);
void qemu_PostQueuedCompletionStatus(struct qemu_syscall *call);
void qemu_PowerClearRequest(struct qemu_syscall *call);
void qemu_PowerCreateRequest(struct qemu_syscall *call);
void qemu_PowerSetRequest(struct qemu_syscall *call);
void qemu_PulseEvent(struct qemu_syscall *call);
void qemu_PurgeComm(struct qemu_syscall *call);
void qemu_QueryInformationJobObject(struct qemu_syscall *call);
void qemu_QueryMemoryResourceNotification(struct qemu_syscall *call);
void qemu_QueryPerformanceCounter(struct qemu_syscall *call);
void qemu_QueryPerformanceFrequency(struct qemu_syscall *call);
void qemu_ReadFile(struct qemu_syscall *call);
void qemu_ReadFileEx(struct qemu_syscall *call);
void qemu_ReadFileScatter(struct qemu_syscall *call);
void qemu_RegisterWaitForSingleObject(struct qemu_syscall *call);
void qemu_RegisterWaitForSingleObjectEx(struct qemu_syscall *call);
void qemu_ReinitializeCriticalSection(struct qemu_syscall *call);
void qemu_ReleaseMutex(struct qemu_syscall *call);
void qemu_ReleaseSemaphore(struct qemu_syscall *call);
void qemu_ReplaceFileA(struct qemu_syscall *call);
void qemu_ReplaceFileW(struct qemu_syscall *call);
void qemu_RequestWakeupLatency(struct qemu_syscall *call);
void qemu_ResetEvent(struct qemu_syscall *call);
void qemu_SetCommBreak(struct qemu_syscall *call);
void qemu_SetCommConfig(struct qemu_syscall *call);
void qemu_SetCommMask(struct qemu_syscall *call);
void qemu_SetCommState(struct qemu_syscall *call);
void qemu_SetCommTimeouts(struct qemu_syscall *call);
void qemu_SetConsoleCtrlHandler(struct qemu_syscall *call);
void qemu_SetDefaultCommConfigA(struct qemu_syscall *call);
void qemu_SetDefaultCommConfigW(struct qemu_syscall *call);
void qemu_SetEndOfFile(struct qemu_syscall *call);
void qemu_SetEnvironmentVariableA(struct qemu_syscall *call);
void qemu_SetEnvironmentVariableW(struct qemu_syscall *call);
void qemu_SetEvent(struct qemu_syscall *call);
void qemu_SetFileApisToANSI(struct qemu_syscall *call);
void qemu_SetFileApisToOEM(struct qemu_syscall *call);
void qemu_SetFileAttributesA(struct qemu_syscall *call);
void qemu_SetFileAttributesW(struct qemu_syscall *call);
void qemu_SetFileCompletionNotificationModes(struct qemu_syscall *call);
void qemu_SetFileInformationByHandle(struct qemu_syscall *call);
void qemu_SetFilePointer(struct qemu_syscall *call);
void qemu_SetFilePointerEx(struct qemu_syscall *call);
void qemu_SetFileTime(struct qemu_syscall *call);
void qemu_SetFileValidData(struct qemu_syscall *call);
void qemu_SetHandleCount(struct qemu_syscall *call);
void qemu_SetInformationJobObject(struct qemu_syscall *call);
void qemu_SetLastError(struct qemu_syscall *call);
void qemu_SetMailslotInfo(struct qemu_syscall *call);
void qemu_SetNamedPipeHandleState(struct qemu_syscall *call);
void qemu_SetStdHandle(struct qemu_syscall *call);
void qemu_SetSystemPowerState(struct qemu_syscall *call);
void qemu_SetThreadExecutionState(struct qemu_syscall *call);
void qemu_SetUnhandledExceptionFilter(struct qemu_syscall *call);
void qemu_SetupComm(struct qemu_syscall *call);
void qemu_SetWaitableTimer(struct qemu_syscall *call);
void qemu_SetWaitableTimerEx(struct qemu_syscall *call);
void qemu_SignalObjectAndWait(struct qemu_syscall *call);
void qemu_Sleep(struct qemu_syscall *call);
void qemu_SleepConditionVariableCS(struct qemu_syscall *call);
void qemu_SleepConditionVariableSRW(struct qemu_syscall *call);
void qemu_SleepEx(struct qemu_syscall *call);
void qemu_SwitchToThread(struct qemu_syscall *call);
void qemu_TerminateJobObject(struct qemu_syscall *call);
void qemu_TerminateProcess(struct qemu_syscall *call);
void qemu_TlsGetValue(struct qemu_syscall *call);
void qemu_TransactNamedPipe(struct qemu_syscall *call);
void qemu_TransmitCommChar(struct qemu_syscall *call);
void qemu_UnhandledExceptionFilter(struct qemu_syscall *call);
void qemu_UninitializeCriticalSection(struct qemu_syscall *call);
void qemu_UnlockFile(struct qemu_syscall *call);
void qemu_UnlockFileEx(struct qemu_syscall *call);
void qemu_UnregisterWait(struct qemu_syscall *call);
void qemu_UnregisterWaitEx(struct qemu_syscall *call);
void qemu_VerifyVersionInfoA(struct qemu_syscall *call);
void qemu_VerifyVersionInfoW(struct qemu_syscall *call);
void qemu_VirtualProtect(struct qemu_syscall *call);
void qemu_VirtualQuery(struct qemu_syscall *call);
void qemu_WaitCommEvent(struct qemu_syscall *call);
void qemu_WaitForDebugEvent(struct qemu_syscall *call);
void qemu_WaitForMultipleObjects(struct qemu_syscall *call);
void qemu_WaitForMultipleObjectsEx(struct qemu_syscall *call);
void qemu_WaitForSingleObject(struct qemu_syscall *call);
void qemu_WaitForSingleObjectEx(struct qemu_syscall *call);
void qemu_WaitNamedPipeA(struct qemu_syscall *call);
void qemu_WaitNamedPipeW(struct qemu_syscall *call);
void qemu_WideCharToMultiByte(struct qemu_syscall *call);
void qemu_WriteFile(struct qemu_syscall *call);
void qemu_WriteFileEx(struct qemu_syscall *call);
void qemu_WriteFileGather(struct qemu_syscall *call);

#endif

#endif
