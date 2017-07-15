#ifndef QEMU_D3D9_H
#define QEMU_D3D9_H

#include <stdlib.h>

enum comdlg32_calls
{
    CALL_D3DPERF_BEGINEVENT = 0,
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

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

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
