#ifndef KERNEL32_H
#define KERNEL32_H

enum kernel32_calls
{
    CALL_DELETECRITICALSECTION = 0,
    CALL_ENTERCRITICALSECTION,
    CALL_EXITPROCESS,
    CALL_GETCURRENTPROCESS,
    CALL_GETCURRENTPROCESSID,
    CALL_GETCURRENTTHREADID,
    CALL_GETLASTERROR,
    CALL_GETMODULEHANDLEA,
    CALL_GETMODULEHANDLEEXA,
    CALL_GETPROCADDRESS,
    CALL_GETSTARTUPINFOA,
    CALL_GETSTDHANDLE,
    CALL_GETSYSTEMTIMEASFILETIME,
    CALL_GETTICKCOUNT,
    CALL_INITIALIZECRITICALSECTION,
    CALL_LEAVECRITICALSECTION,
    CALL_QUERYPERFORMANCECOUNTER,
    CALL_SETLASTERROR,
    CALL_SLEEP,
    CALL_WRITEFILE,
};

#ifndef QEMU_DLL_GUEST
extern const struct qemu_ops *qemu_ops;

void qemu_DeleteCriticalSection(struct qemu_syscall *call);
void qemu_EnterCriticalSection(struct qemu_syscall *call);
void qemu_ExitProcess(struct qemu_syscall *call);
void qemu_GetCurrentProcess(struct qemu_syscall *call);
void qemu_GetCurrentProcessId(struct qemu_syscall *call);
void qemu_GetCurrentThreadId(struct qemu_syscall *call);
void qemu_GetLastError(struct qemu_syscall *call);
void qemu_GetModuleHandleA(struct qemu_syscall *call);
void qemu_GetModuleHandleExA(struct qemu_syscall *call);
void qemu_GetStartupInfoA(struct qemu_syscall *call);
void qemu_GetStdHandle(struct qemu_syscall *call);
void qemu_GetSystemTimeAsFileTime(struct qemu_syscall *call);
void qemu_GetTickCount(struct qemu_syscall *call);
void qemu_GetProcAddress(struct qemu_syscall *call);
void qemu_InitializeCriticalSection(struct qemu_syscall *call);
void qemu_LeaveCriticalSection(struct qemu_syscall *call);
void qemu_QueryPerformanceCounter(struct qemu_syscall *call);
void qemu_SetLastError(struct qemu_syscall *call);
void qemu_Sleep(struct qemu_syscall *call);
void qemu_WriteFile(struct qemu_syscall *call);
#endif

#endif
