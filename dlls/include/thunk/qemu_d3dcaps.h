#ifndef HAVE_QEMU_THUNK_D3DCAPS_H
#define HAVE_QEMU_THUNK_D3DCAPS_H

struct qemu_D3DEXECUTEBUFFERDESC
{
    DWORD  dwSize;
    DWORD  dwFlags;
    DWORD  dwCaps;
    DWORD  dwBufferSize;
    qemu_ptr lpData;
};

static inline void D3DEXECUTEBUFFERDESC_g2h(D3DEXECUTEBUFFERDESC *host, const struct qemu_D3DEXECUTEBUFFERDESC *guest)
{
    host->dwSize = sizeof(*host);
    host->dwFlags = guest->dwFlags;
    host->dwCaps = guest->dwCaps;
    host->dwBufferSize = guest->dwBufferSize;
    host->lpData = (void *)(ULONG_PTR)guest->lpData;
}

#endif
