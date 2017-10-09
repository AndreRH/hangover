#ifndef QEMU_D3D9_H
#define QEMU_D3D9_H

#include <stdlib.h>

enum version_calls
{
    CALL_GETFILEVERSIONINFOA = 0,
    CALL_GETFILEVERSIONINFOEXA,
    CALL_GETFILEVERSIONINFOEXW,
    CALL_GETFILEVERSIONINFOSIZEA,
    CALL_GETFILEVERSIONINFOSIZEEXA,
    CALL_GETFILEVERSIONINFOSIZEEXW,
    CALL_GETFILEVERSIONINFOSIZEW,
    CALL_GETFILEVERSIONINFOW,
    CALL_VERFINDFILEA,
    CALL_VERFINDFILEW,
    CALL_VERINSTALLFILEA,
    CALL_VERINSTALLFILEW,
    CALL_VERQUERYVALUEA,
    CALL_VERQUERYVALUEW,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_GetFileVersionInfoA(struct qemu_syscall *call);
void qemu_GetFileVersionInfoExA(struct qemu_syscall *call);
void qemu_GetFileVersionInfoExW(struct qemu_syscall *call);
void qemu_GetFileVersionInfoSizeA(struct qemu_syscall *call);
void qemu_GetFileVersionInfoSizeExA(struct qemu_syscall *call);
void qemu_GetFileVersionInfoSizeExW(struct qemu_syscall *call);
void qemu_GetFileVersionInfoSizeW(struct qemu_syscall *call);
void qemu_GetFileVersionInfoW(struct qemu_syscall *call);
void qemu_VerFindFileA(struct qemu_syscall *call);
void qemu_VerFindFileW(struct qemu_syscall *call);
void qemu_VerInstallFileA(struct qemu_syscall *call);
void qemu_VerInstallFileW(struct qemu_syscall *call);
void qemu_VerQueryValueA(struct qemu_syscall *call);
void qemu_VerQueryValueW(struct qemu_syscall *call);

#endif

#endif
