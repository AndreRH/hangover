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

struct qemu_D3D11_INPUT_ELEMENT_DESC
{
    qemu_ptr SemanticName;
    UINT SemanticIndex;
    DXGI_FORMAT Format;
    UINT InputSlot;
    UINT AlignedByteOffset;
    D3D11_INPUT_CLASSIFICATION InputSlotClass;
    UINT InstanceDataStepRate;
};

static inline void D3D11_INPUT_ELEMENT_DESC_g2h(D3D11_INPUT_ELEMENT_DESC *host,
        const struct qemu_D3D11_INPUT_ELEMENT_DESC *guest)
{
    host->SemanticName = (const char *)(ULONG_PTR)guest->SemanticName;
    host->SemanticIndex = guest->SemanticIndex;
    host->Format = guest->Format;
    host->InputSlot = guest->InputSlot;
    host->AlignedByteOffset = guest->AlignedByteOffset;
    host->InputSlotClass = guest->InputSlotClass;
    host->InstanceDataStepRate = guest->InstanceDataStepRate;
}

#endif
