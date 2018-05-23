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

#endif
