#ifndef KERNEL32_H
#define KERNEL32_H

enum kernel32_calls
{
    CALL_CLOSEHANDLE = 0,
    CALL_COMPARESTRINGW,
    CALL_CREATEEVENTW,
    CALL_CREATEFILEW,
    CALL_EXITPROCESS,
    CALL_FINDCLOSE,
    CALL_FINDFIRSTFILEW,
    CALL_FORMATMESSAGEW,
    CALL_GETCOMMANDLINEA,
    CALL_GETCOMMANDLINEW,
    CALL_GETCPINFOEXW,
    CALL_GETCURRENTPROCESS,
    CALL_GETCURRENTPROCESSID,
    CALL_GETCURRENTTHREADID,
    CALL_GETDATEFORMATA,
    CALL_GETDATEFORMATW,
    CALL_GETFILESIZE,
    CALL_GETLOCALTIME,
    CALL_GETLASTERROR,
    CALL_GETMODULEFILENAMEA,
    CALL_GETMODULEFILENAMEW,
    CALL_GETMODULEHANDLEA,
    CALL_GETMODULEHANDLEEXA,
    CALL_GETPROCADDRESS,
    CALL_GETPROCESSHEAP,
    CALL_GETSTARTUPINFOA,
    CALL_GETSTDHANDLE,
    CALL_GETSYSTEMTIMEASFILETIME,
    CALL_GETTICKCOUNT,
    CALL_GETTIMEFORMATA,
    CALL_GETTIMEFORMATW,
    CALL_GETVERSION,
    CALL_GETVERSIONEXA,
    CALL_GETVERSIONEXW,
    CALL_HEAPALLOC,
    CALL_HEAPFREE,
    CALL_INITIALIZECRITICALSECTION,
    CALL_LOADLIBRARYA,
    CALL_LOCALFREE,
    CALL_QUERYPERFORMANCECOUNTER,
    CALL_SETCONSOLECTRLHANDLER,
    CALL_SETLASTERROR,
    CALL_SETUNHANDLEDEXCEPTIONFILTER,
    CALL_SLEEP,
    CALL_TERMINATEPROCESS,
    CALL_TLSGETVALUE,
    CALL_UNHANDLEDEXCEPTIONFILTER,
    CALL_VERIFYVERSIONINFOA,
    CALL_VERIFYVERSIONINFOW,
    CALL_VIRTUALQUERY,
    CALL_VIRTUALPROTECT,
    CALL_WRITEFILE,
};

#ifndef QEMU_DLL_GUEST
extern const struct qemu_ops *qemu_ops;

void qemu_CloseHandle(struct qemu_syscall *call);
void qemu_CompareStringW(struct qemu_syscall *call);
void qemu_CreateEventW(struct qemu_syscall *call);
void qemu_CreateFileW(struct qemu_syscall *call);
void qemu_ExitProcess(struct qemu_syscall *call);
void qemu_FindClose(struct qemu_syscall *call);
void qemu_FindFirstFileW(struct qemu_syscall *call);
void qemu_FormatMessageW(struct qemu_syscall *call);
void qemu_GetCommandLineA(struct qemu_syscall *c);
void qemu_GetCommandLineW(struct qemu_syscall *c);
void qemu_GetCPInfoExW(struct qemu_syscall *call);
void qemu_GetCurrentProcess(struct qemu_syscall *call);
void qemu_GetCurrentProcessId(struct qemu_syscall *call);
void qemu_GetCurrentThreadId(struct qemu_syscall *call);
void qemu_GetDateFormatA(struct qemu_syscall *call);
void qemu_GetDateFormatW(struct qemu_syscall *call);
void qemu_GetFileSize(struct qemu_syscall *call);
void qemu_GetLocalTime(struct qemu_syscall *call);
void qemu_GetLastError(struct qemu_syscall *call);
void qemu_GetModuleFileNameA(struct qemu_syscall *call);
void qemu_GetModuleFileNameW(struct qemu_syscall *call);
void qemu_GetModuleHandleA(struct qemu_syscall *call);
void qemu_GetModuleHandleExA(struct qemu_syscall *call);
void qemu_GetStartupInfoA(struct qemu_syscall *call);
void qemu_GetStdHandle(struct qemu_syscall *call);
void qemu_GetSystemTimeAsFileTime(struct qemu_syscall *call);
void qemu_GetTickCount(struct qemu_syscall *call);
void qemu_GetTimeFormatA(struct qemu_syscall *call);
void qemu_GetTimeFormatW(struct qemu_syscall *call);
void qemu_GetProcAddress(struct qemu_syscall *call);
void qemu_GetProcessHeap(struct qemu_syscall *call);
void qemu_GetVersion(struct qemu_syscall *call);
void qemu_GetVersionExA(struct qemu_syscall *call);
void qemu_GetVersionExW(struct qemu_syscall *call);
void qemu_HeapAlloc(struct qemu_syscall *call);
void qemu_HeapFree(struct qemu_syscall *call);
void qemu_InitializeCriticalSection(struct qemu_syscall *call);
void qemu_LoadLibraryA(struct qemu_syscall *call);
void qemu_LocalFree(struct qemu_syscall *call);
void qemu_QueryPerformanceCounter(struct qemu_syscall *call);
void qemu_SetConsoleCtrlHandler(struct qemu_syscall *call);
void qemu_SetLastError(struct qemu_syscall *call);
void qemu_SetUnhandledExceptionFilter(struct qemu_syscall *call);
void qemu_Sleep(struct qemu_syscall *call);
void qemu_TerminateProcess(struct qemu_syscall *call);
void qemu_TlsGetValue(struct qemu_syscall *call);
void qemu_UnhandledExceptionFilter(struct qemu_syscall *call);
void qemu_VerifyVersionInfoA(struct qemu_syscall *call);
void qemu_VerifyVersionInfoW(struct qemu_syscall *call);
void qemu_VirtualQuery(struct qemu_syscall *call);
void qemu_VirtualProtect(struct qemu_syscall *call);
void qemu_WriteFile(struct qemu_syscall *call);
#endif

#endif
