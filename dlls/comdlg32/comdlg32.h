#ifndef COMDLG32_H
#define COMDLG32_H

#include <stdlib.h>

enum comdlg32_calls
{
    CALL_GETFILETITLEW = 0,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_GetFileTitleW(struct qemu_syscall *call);

#endif

#endif
