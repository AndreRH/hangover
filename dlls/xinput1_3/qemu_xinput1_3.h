#ifndef QEMU_XINPUT_H
#define QEMU_XINPUT_H

#include <stdlib.h>

enum xinput1_3_calls
{
    CALL_XINPUTENABLE = 0,
    CALL_XINPUTGETBATTERYINFORMATION,
    CALL_XINPUTGETCAPABILITIES,
    CALL_XINPUTGETDSOUNDAUDIODEVICEGUIDS,
    CALL_XINPUTGETKEYSTROKE,
    CALL_XINPUTGETSTATE,
    CALL_XINPUTGETSTATEEX,
    CALL_XINPUTSETSTATE,
    CALL_XXX,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_XInputEnable(struct qemu_syscall *call);
void qemu_XInputGetBatteryInformation(struct qemu_syscall *call);
void qemu_XInputGetCapabilities(struct qemu_syscall *call);
void qemu_XInputGetDSoundAudioDeviceGuids(struct qemu_syscall *call);
void qemu_XInputGetKeystroke(struct qemu_syscall *call);
void qemu_XInputGetState(struct qemu_syscall *call);
void qemu_XInputGetStateEx(struct qemu_syscall *call);
void qemu_XInputSetState(struct qemu_syscall *call);

#endif

#endif
