#ifndef HAVE_QEMU_THUNK_DINPUT_H
#define HAVE_QEMU_THUNK_DINPUT_H

struct qemu_DIOBJECTDATAFORMAT
{
    qemu_ptr    pguid; /* const GUID * */
    DWORD       dwOfs;
    DWORD       dwType;
    DWORD       dwFlags;
};

static inline void DIOBJECTDATAFORMAT_g2h(DIOBJECTDATAFORMAT *host, const struct qemu_DIOBJECTDATAFORMAT *guest)
{
    host->pguid = (const GUID *)(ULONG_PTR)guest->pguid;
    host->dwOfs = guest->dwOfs;
    host->dwType = guest->dwType;
    host->dwFlags = guest->dwFlags;
}

static inline void DIOBJECTDATAFORMAT_h2g(struct qemu_DIOBJECTDATAFORMAT *guest, const DIOBJECTDATAFORMAT *host)
{
    guest->pguid = (ULONG_PTR)host->pguid;
    guest->dwOfs = host->dwOfs;
    guest->dwType = host->dwType;
    guest->dwFlags = host->dwFlags;
}

struct qemu_DIDATAFORMAT
{
    DWORD                   dwSize;
    DWORD                   dwObjSize;
    DWORD                   dwFlags;
    DWORD                   dwDataSize;
    DWORD                   dwNumObjs;
    qemu_ptr                rgodf; /* DIOBJECTDATAFORMAT * */
};

static inline void DIDATAFORMAT_g2h(DIDATAFORMAT *host, const struct qemu_DIDATAFORMAT *guest)
{
    host->dwSize = sizeof(*host);
    host->dwObjSize = sizeof(DIOBJECTDATAFORMAT);
    host->dwFlags = guest->dwFlags;
    host->dwDataSize = guest->dwDataSize;
    host->dwNumObjs = guest->dwNumObjs;
    /* This is an array, the caller has to convert it. */
    host->rgodf = (DIOBJECTDATAFORMAT *)(ULONG_PTR)guest->rgodf;
}

static inline void DIDATAFORMAT_h2g(struct qemu_DIDATAFORMAT *guest, const DIDATAFORMAT *host)
{
    guest->dwSize = host->dwSize;
    guest->dwObjSize = host->dwObjSize;
    guest->dwFlags = host->dwFlags;
    guest->dwDataSize = host->dwDataSize;
    guest->dwNumObjs = host->dwNumObjs;
    /* This is an array, the caller has to convert it. */
    guest->rgodf = (ULONG_PTR)host->rgodf;
}

#endif
