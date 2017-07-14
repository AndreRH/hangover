#ifndef COMCTL32_H
#define COMCTL32_H

#include <stdlib.h>

enum comdlg32_calls
{
    CALL_INITCOMMONCONTROLS = 0,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_InitCommonControls(struct qemu_syscall *call);

#endif

#endif
