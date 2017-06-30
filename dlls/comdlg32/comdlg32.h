#ifndef COMDLG32_H
#define COMDLG32_H

#include <stdlib.h>

enum comdlg32_calls
{
    CALL_FINDTEXTA = 0,
    CALL_FINDTEXTW,
    CALL_GETFILETITLEA,
    CALL_GETFILETITLEW,
    CALL_GETOPENFILENAMEA,
    CALL_GETOPENFILENAMEW,
    CALL_GETSAVEFILENAMEA,
    CALL_GETSAVEFILENAMEW,
    CALL_REPLACETEXTA,
    CALL_REPLACETEXTW,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_FindTextA(struct qemu_syscall *call);
void qemu_FindTextW(struct qemu_syscall *call);
void qemu_GetFileTitleA(struct qemu_syscall *call);
void qemu_GetFileTitleW(struct qemu_syscall *call);
void qemu_GetOpenFileNameA(struct qemu_syscall *call);
void qemu_GetOpenFileNameW(struct qemu_syscall *call);
void qemu_GetSaveFileNameA(struct qemu_syscall *call);
void qemu_GetSaveFileNameW(struct qemu_syscall *call);
void qemu_ReplaceTextA(struct qemu_syscall *call);
void qemu_ReplaceTextW(struct qemu_syscall *call);

#endif

#endif
