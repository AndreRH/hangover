#ifndef KERNEL32_H
#define KERNEL32_H

#define CALL_EXITPROCESS        0ULL
#define CALL_GETSTDHANDLE       1ULL
#define CALL_WRITEFILE          2ULL

#ifndef QEMU_DLL_GUEST
extern const struct qemu_op *qemu_op;

void qemu_ExitProcess(struct qemu_syscall *call);
void qemu_GetStdHandle(struct qemu_syscall *call);
void qemu_WriteFile(struct qemu_syscall *call);
#endif

#endif
