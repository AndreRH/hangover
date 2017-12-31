#ifndef HAVE_QEMU_D3D9TYPES_H
#define HAVE_QEMU_D3D9TYPES_H

#include "thunk/qemu_defines.h"

struct qemu_D3DPRESENT_PARAMETERS
{
    UINT                    BackBufferWidth;
    UINT                    BackBufferHeight;
    D3DFORMAT               BackBufferFormat;
    UINT                    BackBufferCount;

    D3DMULTISAMPLE_TYPE     MultiSampleType;
    DWORD                   MultiSampleQuality;

    D3DSWAPEFFECT           SwapEffect;
    qemu_handle             hDeviceWindow;
    BOOL                    Windowed;
    BOOL                    EnableAutoDepthStencil;
    D3DFORMAT               AutoDepthStencilFormat;
    DWORD                   Flags;

    UINT                    FullScreen_RefreshRateInHz;
    UINT                    PresentationInterval;

};

static inline void D3DPRESENT_PARAMETERS_g2h(D3DPRESENT_PARAMETERS *host, const struct qemu_D3DPRESENT_PARAMETERS *guest)
{
    host->BackBufferWidth = guest->BackBufferWidth;
    host->BackBufferHeight = guest->BackBufferHeight;
    host->BackBufferFormat = guest->BackBufferFormat;
    host->BackBufferCount = guest->BackBufferCount;
    host->MultiSampleType = guest->MultiSampleType;
    host->MultiSampleQuality = guest->MultiSampleQuality;
    host->SwapEffect = guest->SwapEffect;
    host->hDeviceWindow = (HWND)(ULONG_PTR)guest->hDeviceWindow;
    host->Windowed = guest->Windowed;
    host->EnableAutoDepthStencil = guest->EnableAutoDepthStencil;
    host->AutoDepthStencilFormat = guest->AutoDepthStencilFormat;
    host->Flags = guest->Flags;
    host->FullScreen_RefreshRateInHz = guest->FullScreen_RefreshRateInHz;
    host->PresentationInterval = guest->PresentationInterval;
}

static inline void D3DPRESENT_PARAMETERS_h2g(struct qemu_D3DPRESENT_PARAMETERS *guest, const D3DPRESENT_PARAMETERS *host)
{
    guest->BackBufferWidth = host->BackBufferWidth;
    guest->BackBufferHeight = host->BackBufferHeight;
    guest->BackBufferFormat = host->BackBufferFormat;
    guest->BackBufferCount = host->BackBufferCount;
    guest->MultiSampleType = host->MultiSampleType;
    guest->MultiSampleQuality = host->MultiSampleQuality;
    guest->SwapEffect = host->SwapEffect;
    guest->hDeviceWindow = (ULONG_PTR)host->hDeviceWindow;
    guest->Windowed = host->Windowed;
    guest->EnableAutoDepthStencil = host->EnableAutoDepthStencil;
    guest->AutoDepthStencilFormat = host->AutoDepthStencilFormat;
    guest->Flags = host->Flags;
    guest->FullScreen_RefreshRateInHz = host->FullScreen_RefreshRateInHz;
    guest->PresentationInterval = host->PresentationInterval;
}

struct qemu_D3DDEVICE_CREATION_PARAMETERS
{
    UINT          AdapterOrdinal;
    D3DDEVTYPE    DeviceType;
    qemu_handle   hFocusWindow;
    DWORD         BehaviorFlags;
};

static inline void D3DDEVICE_CREATION_PARAMETERS_h2g(struct qemu_D3DDEVICE_CREATION_PARAMETERS *guest, const D3DDEVICE_CREATION_PARAMETERS *host)
{
    guest->AdapterOrdinal = host->AdapterOrdinal;
    guest->DeviceType = host->DeviceType;
    guest->hFocusWindow = (ULONG_PTR)host->hFocusWindow;
    guest->BehaviorFlags = host->BehaviorFlags;
}

struct qemu_D3DLOCKED_RECT
{
    INT                 Pitch;
    qemu_ptr            pBits;
};

static inline void D3DLOCKED_RECT_h2g(struct qemu_D3DLOCKED_RECT *guest, const D3DLOCKED_RECT *host)
{
    guest->Pitch = host->Pitch;
    guest->pBits = (ULONG_PTR)host->pBits;
}

struct qemu_D3DLOCKED_BOX
{
    INT                 RowPitch;
    INT                 SlicePitch;
    qemu_ptr            pBits;
};

static inline void D3DLOCKED_BOX_h2g(struct qemu_D3DLOCKED_BOX *guest, const D3DLOCKED_BOX *host)
{
    guest->RowPitch = host->RowPitch;
    guest->SlicePitch = host->SlicePitch;
    guest->pBits = (ULONG_PTR)host->pBits;
}

/* There are no pointers in here, but alignment differs. */
#include <pshpack4.h>
struct qemu_D3DADAPTER_IDENTIFIER9
{
    char            Driver[MAX_DEVICE_IDENTIFIER_STRING];
    char            Description[MAX_DEVICE_IDENTIFIER_STRING];
    char            DeviceName[32];
    LARGE_INTEGER   DriverVersion;

    DWORD           VendorId;
    DWORD           DeviceId;
    DWORD           SubSysId;
    DWORD           Revision;

    GUID            DeviceIdentifier;

    DWORD           WHQLLevel;
};
#include <poppack.h>

static inline void D3DADAPTER_IDENTIFIER9_h2g(struct qemu_D3DADAPTER_IDENTIFIER9 *guest, const D3DADAPTER_IDENTIFIER9 *host)
{
    /* The structures is the same on 32 and 64 bit, except for the extra 4 byte padding added behind WHQLLevel on 64. */
    memcpy(guest, host, sizeof(*guest));
}

#endif
