#ifndef HAVE_QEMU_WINNT_H
#define HAVE_QEMU_WINNT_H

#include "thunk/qemu_defines.h"

struct qemu_MEMORY_BASIC_INFORMATION
{
    qemu_ptr    BaseAddress;
    qemu_ptr    AllocationBase;
    DWORD       AllocationProtect;
    qemu_size_t RegionSize;
    DWORD       State;
    DWORD       Protect;
    DWORD       Type;
};

#endif
