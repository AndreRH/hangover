#ifndef HAVE_QEMU_THUNK_DXGI_H
#define HAVE_QEMU_THUNK_DXGI_H

#include "thunk/qemu_windows.h"

struct qemu_DXGI_OUTPUT_DESC
{
    WCHAR DeviceName[32];
    RECT DesktopCoordinates;
    BOOL AttachedToDesktop;
    DXGI_MODE_ROTATION Rotation;
    qemu_ptr Monitor;
};

static void DXGI_OUTPUT_DESC_h2g(struct qemu_DXGI_OUTPUT_DESC *guest, const struct DXGI_OUTPUT_DESC *host)
{
    memcpy(guest->DeviceName, host->DeviceName, sizeof(guest->DeviceName));
    guest->DesktopCoordinates = host->DesktopCoordinates;
    guest->AttachedToDesktop = host->AttachedToDesktop;
    guest->Rotation = host->Rotation;
    guest->Monitor = (ULONG_PTR)host->Monitor;
}

struct qemu_DXGI_ADAPTER_DESC1
{
    WCHAR  Description[128];
    UINT   VendorId;
    UINT   DeviceId;
    UINT   SubSysId;
    UINT   Revision;
    qemu_ptr DedicatedVideoMemory;
    qemu_ptr DedicatedSystemMemory;
    qemu_ptr SharedSystemMemory;
    LUID   AdapterLuid;
    UINT   Flags;
};

struct qemu_DXGI_ADAPTER_DESC
{
    WCHAR  Description[128];
    UINT   VendorId;
    UINT   DeviceId;
    UINT   SubSysId;
    UINT   Revision;
    qemu_ptr DedicatedVideoMemory;
    qemu_ptr DedicatedSystemMemory;
    qemu_ptr SharedSystemMemory;
    LUID   AdapterLuid;
};

static void DXGI_ADAPTER_DESC_h2g(struct qemu_DXGI_ADAPTER_DESC *guest, const struct DXGI_ADAPTER_DESC *host)
{
    memcpy(guest->Description, host->Description, sizeof(guest->Description));
    guest->VendorId = host->VendorId;
    guest->DeviceId = host->DeviceId;
    guest->SubSysId = host->SubSysId;
    guest->Revision = host->Revision;
    
    if (host->DedicatedVideoMemory > ~0U)
        guest->DedicatedVideoMemory = ~0U;
    else
        guest->DedicatedVideoMemory = host->DedicatedVideoMemory;
    
    if (host->DedicatedSystemMemory > ~0U)
        guest->DedicatedSystemMemory = ~0U;
    else
        guest->DedicatedSystemMemory = host->DedicatedSystemMemory;
    
    if (host->SharedSystemMemory > ~0U)
        guest->SharedSystemMemory = ~0U;
    else
        guest->SharedSystemMemory = host->SharedSystemMemory;
    
    guest->AdapterLuid = host->AdapterLuid;
}

static void DXGI_ADAPTER_DESC1_h2g(struct qemu_DXGI_ADAPTER_DESC1 *guest, const struct DXGI_ADAPTER_DESC1 *host)
{
    DXGI_ADAPTER_DESC_h2g((struct qemu_DXGI_ADAPTER_DESC *)guest, (DXGI_ADAPTER_DESC *)host);
    guest->Flags = host->Flags;
}

#endif
