#ifndef QEMU_DSOUND_H
#define QEMU_DSOUND_H

enum advpack_calls
{
    CALL_XXX = 0,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

#endif

#endif
