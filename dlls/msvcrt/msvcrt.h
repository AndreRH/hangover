#ifndef MSVCRT_H
#define MSVCRT_H

enum msvcrt_calls
{
    CALL_EXIT = 0,
};

#ifndef QEMU_DLL_GUEST
extern const struct qemu_ops *qemu_ops;

void qemu_exit(struct qemu_syscall *call);

/* Be careful not to call the Linux libc! */
void (*p_exit)(int code);
#endif

#endif
