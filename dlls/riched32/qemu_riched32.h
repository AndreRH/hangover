#ifndef QEMU_RICHED32_H
#define QEMU_RICHED32_H

enum riched32_calls
{
    CALL_DLLGETVERSION = 0,
    CALL_INIT_DLL,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

#endif

#endif
