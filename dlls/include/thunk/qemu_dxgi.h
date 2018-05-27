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

struct qemu_DXGI_SWAP_CHAIN_DESC
{
    DXGI_MODE_DESC BufferDesc;
    DXGI_SAMPLE_DESC SampleDesc;
    DXGI_USAGE BufferUsage;
    UINT BufferCount;
    qemu_ptr OutputWindow;
    BOOL Windowed;
    DXGI_SWAP_EFFECT SwapEffect;
    UINT Flags;
};

static void DXGI_SWAP_CHAIN_DESC_g2h(struct DXGI_SWAP_CHAIN_DESC *host, const struct qemu_DXGI_SWAP_CHAIN_DESC *guest)
{
    host->BufferDesc = guest->BufferDesc;
    host->SampleDesc = guest->SampleDesc;
    host->BufferUsage = guest->BufferUsage;
    host->BufferCount = guest->BufferCount;
    host->OutputWindow = (HWND)(ULONG_PTR)guest->OutputWindow;
    host->Windowed = guest->Windowed;
    host->SwapEffect = guest->SwapEffect;
    host->Flags = guest->Flags;
}

static void DXGI_SWAP_CHAIN_DESC_h2g(struct qemu_DXGI_SWAP_CHAIN_DESC *guest, const struct DXGI_SWAP_CHAIN_DESC *host)
{
    guest->BufferDesc = host->BufferDesc;
    guest->SampleDesc = host->SampleDesc;
    guest->BufferUsage = host->BufferUsage;
    guest->BufferCount = host->BufferCount;
    guest->OutputWindow = (ULONG_PTR)host->OutputWindow;
    guest->Windowed = host->Windowed;
    guest->SwapEffect = host->SwapEffect;
    guest->Flags = host->Flags;
}

#endif
