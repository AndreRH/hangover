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

extern void (WINAPI *pXInputEnable)(BOOL enable);
extern DWORD (WINAPI *pXInputSetState)(DWORD index, XINPUT_VIBRATION* vibration);
extern DWORD (WINAPI *pXInputGetState)(DWORD index, XINPUT_STATE* state);
extern DWORD (WINAPI *pXInputGetStateEx)(DWORD index, void* state_ex);
extern DWORD (WINAPI *pXInputGetKeystroke)(DWORD index, DWORD reserved, PXINPUT_KEYSTROKE keystroke);
extern DWORD (WINAPI *pXInputGetCapabilities)(DWORD index, DWORD flags, XINPUT_CAPABILITIES* capabilities);
extern DWORD (WINAPI *pXInputGetDSoundAudioDeviceGuids)(DWORD index, GUID* render_guid, GUID* capture_guid);
extern DWORD (WINAPI *pXInputGetBatteryInformation)(DWORD index, BYTE type, XINPUT_BATTERY_INFORMATION* battery);

#endif

#endif
