#ifndef QEMU_DDRAW_H
#define QEMU_DDRAW_H

enum ddraw_calls
{
    CALL_XXX = 0,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

#endif

#endif
