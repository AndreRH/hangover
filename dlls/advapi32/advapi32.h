#ifndef MSVCRT_H
#define MSVCRT_H

#include <stdlib.h>

enum msvcrt_calls
{
    CALL_ISTEXTUNICODE = 0,
    CALL_REGCLOSEKEY,
    CALL_REGOPENKEY,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_IsTextUnicode(struct qemu_syscall *call);
void qemu_RegCloseKey(struct qemu_syscall *call);
void qemu_RegOpenKeyW(struct qemu_syscall *call);


#endif

#endif
