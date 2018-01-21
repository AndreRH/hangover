#ifndef HAVE_QEMU_DSOUND_H
#define HAVE_QEMU_DSOUND_H

struct qemu_DSBUFFERDESC
{
    DWORD       dwSize;
    DWORD       dwFlags;
    DWORD       dwBufferBytes;
    DWORD       dwReserved;
    qemu_ptr    lpwfxFormat;
    GUID        guid3DAlgorithm;
};

struct qemu_DSBUFFERDESC1
{
    DWORD       dwSize;
    DWORD       dwFlags;
    DWORD       dwBufferBytes;
    DWORD       dwReserved;
    qemu_ptr    lpwfxFormat;
};

static inline void DSBUFFERDESC_g2h(DSBUFFERDESC *host, const struct qemu_DSBUFFERDESC *guest)
{
    host->dwSize = sizeof(*host);
    host->dwFlags = guest->dwFlags;
    host->dwBufferBytes = guest->dwBufferBytes;
    host->dwReserved = guest->dwReserved;
    host->lpwfxFormat = (WAVEFORMATEX *)(ULONG_PTR)guest->lpwfxFormat;
    if (guest->dwSize >= sizeof(*guest))
        host->guid3DAlgorithm = guest->guid3DAlgorithm;
    else
        memset(&host->guid3DAlgorithm, 0, sizeof(host));
}

#endif
