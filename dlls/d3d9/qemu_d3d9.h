#ifndef QEMU_D3D9_H
#define QEMU_D3D9_H

#include <stdlib.h>

#include "d3d9_wrapper.h"

enum d3d9_calls
{
    CALL_D3D9_ADDREF = 0,
    CALL_D3D9_CHECKDEPTHSTENCILMATCH,
    CALL_D3D9_CHECKDEVICEFORMAT,
    CALL_D3D9_CHECKDEVICEFORMATCONVERSION,
    CALL_D3D9_CHECKDEVICEMULTISAMPLETYPE,
    CALL_D3D9_CHECKDEVICETYPE,
    CALL_D3D9_CREATEDEVICE,
    CALL_D3D9_CREATEDEVICEEX,
    CALL_D3D9_ENUMADAPTERMODES,
    CALL_D3D9_ENUMADAPTERMODESEX,
    CALL_D3D9_GETADAPTERCOUNT,
    CALL_D3D9_GETADAPTERDISPLAYMODE,
    CALL_D3D9_GETADAPTERDISPLAYMODEEX,
    CALL_D3D9_GETADAPTERIDENTIFIER,
    CALL_D3D9_GETADAPTERLUID,
    CALL_D3D9_GETADAPTERMODECOUNT,
    CALL_D3D9_GETADAPTERMODECOUNTEX,
    CALL_D3D9_GETADAPTERMONITOR,
    CALL_D3D9_GETDEVICECAPS,
    CALL_D3D9_QUERYINTERFACE,
    CALL_D3D9_REGISTERSOFTWAREDEVICE,
    CALL_D3D9_RELEASE,
    CALL_D3DPERF_BEGINEVENT,
    CALL_D3DPERF_ENDEVENT,
    CALL_D3DPERF_GETSTATUS,
    CALL_D3DPERF_QUERYREPEATFRAME,
    CALL_D3DPERF_SETMARKER,
    CALL_D3DPERF_SETOPTIONS,
    CALL_D3DPERF_SETREGION,
    CALL_DEBUGSETMUTE,
    CALL_DIRECT3DCREATE9,
    CALL_DIRECT3DCREATE9EX,
    CALL_DIRECT3DSHADERVALIDATORCREATE9,
};

#ifdef QEMU_DLL_GUEST

extern const struct IDirect3D9ExVtbl d3d9_vtbl;

#else

extern const struct qemu_ops *qemu_ops;

void qemu_d3d9_AddRef(struct qemu_syscall *call);
void qemu_d3d9_CheckDepthStencilMatch(struct qemu_syscall *call);
void qemu_d3d9_CheckDeviceFormat(struct qemu_syscall *call);
void qemu_d3d9_CheckDeviceFormatConversion(struct qemu_syscall *call);
void qemu_d3d9_CheckDeviceMultiSampleType(struct qemu_syscall *call);
void qemu_d3d9_CheckDeviceType(struct qemu_syscall *call);
void qemu_d3d9_CreateDevice(struct qemu_syscall *call);
void qemu_d3d9_CreateDeviceEx(struct qemu_syscall *call);
void qemu_d3d9_EnumAdapterModes(struct qemu_syscall *call);
void qemu_d3d9_EnumAdapterModesEx(struct qemu_syscall *call);
void qemu_d3d9_GetAdapterCount(struct qemu_syscall *call);
void qemu_d3d9_GetAdapterDisplayMode(struct qemu_syscall *call);
void qemu_d3d9_GetAdapterDisplayModeEx(struct qemu_syscall *call);
void qemu_d3d9_GetAdapterIdentifier(struct qemu_syscall *call);
void qemu_d3d9_GetAdapterLUID(struct qemu_syscall *call);
void qemu_d3d9_GetAdapterModeCount(struct qemu_syscall *call);
void qemu_d3d9_GetAdapterModeCountEx(struct qemu_syscall *call);
void qemu_d3d9_GetAdapterMonitor(struct qemu_syscall *call);
void qemu_d3d9_GetDeviceCaps(struct qemu_syscall *call);
void qemu_d3d9_QueryInterface(struct qemu_syscall *call);
void qemu_d3d9_RegisterSoftwareDevice(struct qemu_syscall *call);
void qemu_d3d9_Release(struct qemu_syscall *call);
void qemu_D3DPERF_BeginEvent(struct qemu_syscall *call);
void qemu_D3DPERF_EndEvent(struct qemu_syscall *call);
void qemu_D3DPERF_GetStatus(struct qemu_syscall *call);
void qemu_D3DPERF_QueryRepeatFrame(struct qemu_syscall *call);
void qemu_D3DPERF_SetMarker(struct qemu_syscall *call);
void qemu_D3DPERF_SetOptions(struct qemu_syscall *call);
void qemu_D3DPERF_SetRegion(struct qemu_syscall *call);
void qemu_DebugSetMute(struct qemu_syscall *call);
void qemu_Direct3DCreate9(struct qemu_syscall *call);
void qemu_Direct3DCreate9Ex(struct qemu_syscall *call);
void qemu_Direct3DShaderValidatorCreate9(struct qemu_syscall *call);

#endif

#endif
