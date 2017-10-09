#ifndef QEMU_D3DX10_H
#define QEMU_D3DX10_H

#include <stdlib.h>

enum d3dx10_43_calls
{
    CALL_XXX = 0,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

#endif

#endif
