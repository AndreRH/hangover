#ifndef HAVE_QEMU_THUNK_MMSYSTEM_H
#define HAVE_QEMU_THUNK_MMSYSTEM_H

struct qemu_WAVEHDR
{
    qemu_ptr    lpData;
    DWORD       dwBufferLength;
    DWORD       dwBytesRecorded;
    qemu_ptr    dwUser;
    DWORD       dwFlags;
    DWORD       dwLoops;
    qemu_ptr    lpNext;
    qemu_ptr    reserved;
};

static inline void WAVEHDR_g2h(WAVEHDR *host, const struct qemu_WAVEHDR *guest)
{
    host->lpData = (char *)(ULONG_PTR)guest->lpData;
    host->dwBufferLength = guest->dwBufferLength;
    host->dwBytesRecorded = guest->dwBytesRecorded;
    host->dwUser = guest->dwUser;
    host->dwFlags = guest->dwFlags;
    host->dwLoops = guest->dwLoops;
    host->lpNext = (WAVEHDR *)(ULONG_PTR)guest->lpNext; /* Note: MSDN says "reserved" */
    host->reserved = guest->reserved;
}

static inline void WAVEHDR_h2g(struct qemu_WAVEHDR *guest, const WAVEHDR *host)
{
    guest->lpData = (ULONG_PTR)host->lpData;
    guest->dwBufferLength = host->dwBufferLength;
    guest->dwBytesRecorded = host->dwBytesRecorded;
    guest->dwUser = host->dwUser;
    guest->dwFlags = host->dwFlags;
    guest->dwLoops = host->dwLoops;
    guest->lpNext = (ULONG_PTR)host->lpNext; /* Note: MSDN says "reserved" */
    guest->reserved = host->reserved;
}

#endif
