#ifndef QEMU_D3D9_H
#define QEMU_D3D9_H

#include <stdlib.h>

enum imm32_calls
{
    CALL_XXX,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_xxx(struct qemu_syscall *call);

#endif

#endif
