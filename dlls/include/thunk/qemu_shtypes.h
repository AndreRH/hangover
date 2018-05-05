#ifndef HAVE_QEMU_SHTYPES_H
#define HAVE_QEMU_SHTYPES_H

#include "thunk/qemu_windows.h"

#include <pshpack8.h>
struct qemu_STRRET
{
    UINT uType;
    union
    {
        qemu_ptr pOleStr;
        UINT uOffset;
        char cStr[260];
    } u1;
};
#include <poppack.h>

static inline void STRRET_g2h(STRRET *host, const struct qemu_STRRET *guest)
{
    host->uType = guest->uType;
    switch (host->uType)
    {
        case STRRET_WSTR:
            host->pOleStr = (WCHAR *)(ULONG_PTR)guest->u1.pOleStr;
            break;

        case STRRET_OFFSET:
            host->uOffset = guest->u1.uOffset;
            break;

        case STRRET_CSTR:
            memcpy(host->cStr, guest->u1.cStr, sizeof(host->cStr));
            break;
    }
}

static inline void STRRET_h2g(struct qemu_STRRET *guest, const STRRET *host)
{
    guest->uType = host->uType;
    switch (host->uType)
    {
        case STRRET_WSTR:
            guest->u1.pOleStr = (ULONG_PTR)host->pOleStr;
            break;

        case STRRET_OFFSET:
            guest->u1.uOffset = host->uOffset;
            break;

        case STRRET_CSTR:
            memcpy(guest->u1.cStr, host->cStr, sizeof(guest->u1.cStr));
            break;
    }
}

#endif
