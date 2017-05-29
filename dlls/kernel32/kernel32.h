#ifndef KERNEL32_H
#define KERNEL32_H

#define CALL_EXITPROCESS 0ULL

#ifndef QEMU_DLL_GUEST
extern const struct qemu_op *qemu_op;

void qemu_ExitProcess(struct qemu_syscall *call);
#endif

#endif
