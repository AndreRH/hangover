#ifndef HAVE_QEMU_THUNK_WINCODEC_H
#define HAVE_QEMU_THUNK_WINCODEC_H

#include "thunk/qemu_ocidl.h"

struct qemu_WICBitmapPattern
{
    ULARGE_INTEGER Position;
    ULONG Length;
    qemu_ptr Pattern;
    qemu_ptr Mask;
    BOOL EndOfStream;
};

static inline void WICBitmapPattern_h2g(struct qemu_WICBitmapPattern *guest, const WICBitmapPattern *host)
{
    guest->Position = host->Position;
    guest->Length = host->Length;
    guest->Pattern = (ULONG_PTR)host->Pattern;
    guest->Mask = (ULONG_PTR)host->Mask;
    guest->EndOfStream = host->EndOfStream;
}

#endif
