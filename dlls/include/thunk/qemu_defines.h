#ifndef HAVE_QEMU_DEFINES_H
#define HAVE_QEMU_DEFINES_H

#include <stdint.h>

typedef DWORD qemu_ptr;
typedef INT qemu_sptr, qemu_handle;
typedef DWORD qemu_size_t;

static inline HANDLE HANDLE_g2h(qemu_handle h)
{
    return (HANDLE)(LONG_PTR)h;
}

#endif
