#ifndef HAVE_QEMU_WINTERNL_H
#define HAVE_QEMU_WINTERNL_H

#include "thunk/qemu_windef.h"

struct qemu_UNICODE_STRING
{
  USHORT Length;        /* bytes */
  USHORT MaximumLength; /* bytes */
  qemu_ptr  Buffer;
};

static inline void UNICODE_STRING_g2h(UNICODE_STRING *host, const struct qemu_UNICODE_STRING *guest)
{
    host->Length = guest->Length;
    host->MaximumLength = guest->MaximumLength;
    host->Buffer = (WCHAR *)(ULONG_PTR)guest->Buffer;
}

static inline void UNICODE_STRING_h2g(struct qemu_UNICODE_STRING *guest, const UNICODE_STRING *host)
{
    guest->Length = host->Length;
    guest->MaximumLength = host->MaximumLength;
    guest->Buffer = (ULONG_PTR)host->Buffer;
}

struct qemu_OBJECT_NAME_INFORMATION
{
    struct qemu_UNICODE_STRING Name;
};

static inline void OBJECT_NAME_INFORMATION_g2h(OBJECT_NAME_INFORMATION *host, const struct qemu_OBJECT_NAME_INFORMATION *guest)
{
    UNICODE_STRING_g2h(&host->Name, &guest->Name);
}

static inline void OBJECT_NAME_INFORMATION_h2g(struct qemu_OBJECT_NAME_INFORMATION *guest, const OBJECT_NAME_INFORMATION *host)
{
    UNICODE_STRING_h2g(&guest->Name, &host->Name);
}

#endif
