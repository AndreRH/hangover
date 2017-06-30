#ifndef COMDLG32_H
#define COMDLG32_H

#include <stdlib.h>

enum comdlg32_calls
{
    CALL_GETFILETITLEA = 0,
    CALL_GETFILETITLEW,
    CALL_GETOPENFILENAMEA,
    CALL_GETOPENFILENAMEW,
    CALL_GETSAVEFILENAMEA,
    CALL_GETSAVEFILENAMEW,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_GetFileTitleA(struct qemu_syscall *call);
void qemu_GetFileTitleW(struct qemu_syscall *call);
void qemu_GetOpenFileNameA(struct qemu_syscall *call);
void qemu_GetOpenFileNameW(struct qemu_syscall *call);
void qemu_GetSaveFileNameA(struct qemu_syscall *call);
void qemu_GetSaveFileNameW(struct qemu_syscall *call);

#endif

#endif
