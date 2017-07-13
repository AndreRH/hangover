#ifndef SHLWAPI_H
#define SHLWAPI_H

#include <stdlib.h>

enum shlwapi_calls
{
    CALL_STRCMPNIW = 0,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_StrCmpNIW(struct qemu_syscall *call);

#endif

#endif
