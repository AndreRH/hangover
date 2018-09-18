#ifndef HAVE_QEMU_THUNK_WTYPES_H
#define HAVE_QEMU_THUNK_WTYPES_H

#include "thunk/qemu_rpc.h"
#include "thunk/qemu_windows.h"

struct qemu_BLOB
{
    ULONG cbSize;
    qemu_ptr pBlobData;
};

#endif
