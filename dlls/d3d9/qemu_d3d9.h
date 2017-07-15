#ifndef QEMU_D3D9_H
#define QEMU_D3D9_H

#include <stdlib.h>

enum comdlg32_calls
{
    CALL_DIRECT3DCREATE9 = 0,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_Direct3DCreate9(struct qemu_syscall *call);

#endif

#endif
