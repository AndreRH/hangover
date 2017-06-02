#ifndef KERNEL32_H
#define KERNEL32_H

#define CALL_EXITPROCESS        0ULL
#define CALL_GETMODULEHANDLEA   1ULL
#define CALL_GETMODULEHANDLEEXA 2ULL
#define CALL_GETPROCADDRESS     3ULL
#define CALL_GETSTDHANDLE       4ULL
#define CALL_WRITEFILE          5ULL

#ifndef QEMU_DLL_GUEST
extern const struct qemu_ops *qemu_ops;

void qemu_ExitProcess(struct qemu_syscall *call);
void qemu_GetModuleHandleA(struct qemu_syscall *call);
void qemu_GetModuleHandleExA(struct qemu_syscall *call);
void qemu_GetStdHandle(struct qemu_syscall *call);
void qemu_GetProcAddress(struct qemu_syscall *call);
void qemu_WriteFile(struct qemu_syscall *call);
#endif

#endif
