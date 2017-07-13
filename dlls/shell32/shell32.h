#ifndef SHELL32_H
#define SHELL32_H

#include <stdlib.h>

enum shell32_calls
{
    CALL_SHELLABOUTW = 0,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_ShellAboutW(struct qemu_syscall *call);

#endif

#endif
