#ifndef QEMU_XINPUT_H
#define QEMU_XINPUT_H

#include <stdlib.h>

enum xinput1_3_calls
{
    CALL_XXX = 0,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

#endif

#endif
