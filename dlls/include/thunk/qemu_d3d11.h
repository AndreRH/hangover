#ifndef HAVE_QEMU_THUNK_D3D11_H
#define HAVE_QEMU_THUNK_D3D11_H

#include "thunk/qemu_dxgi.h"

struct qemu_D3D11_SUBRESOURCE_DATA
{
    qemu_ptr pSysMem;
    UINT SysMemPitch;
    UINT SysMemSlicePitch;
};

static inline void D3D11_SUBRESOURCE_DATA_g2h(D3D11_SUBRESOURCE_DATA *host,
            const struct qemu_D3D11_SUBRESOURCE_DATA *guest)
{
    host->pSysMem = (void *)(ULONG_PTR)guest->pSysMem;
    host->SysMemPitch = guest->SysMemPitch;
    host->SysMemSlicePitch = guest->SysMemSlicePitch;
}

#endif
