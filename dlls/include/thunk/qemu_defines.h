#ifndef HAVE_QEMU_DEFINES_H
#define HAVE_QEMU_DEFINES_H

#include <stdint.h>

typedef DWORD qemu_ptr, qemu_handle;
typedef DWORD qemu_size_t;

static inline HANDLE HANDLE_g2h(uint64_t h)
{
#if GUEST_BIT != HOST_BIT
    if (h == ~((DWORD)0))
        return INVALID_HANDLE_VALUE;
#endif
    return (HANDLE)(ULONG_PTR)h;
}

#endif
