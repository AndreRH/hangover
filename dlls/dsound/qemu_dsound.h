#ifndef QEMU_DSOUND_H
#define QEMU_DSOUND_H

enum dsound_calls
{
    CALL_DIRECTSOUNDCAPTURECREATE = 0,
    CALL_DIRECTSOUNDCAPTURECREATE8,
    CALL_DIRECTSOUNDCAPTUREENUMERATEA,
    CALL_DIRECTSOUNDCAPTUREENUMERATEW,
    CALL_DIRECTSOUNDCREATE,
    CALL_DIRECTSOUNDCREATE8,
    CALL_DIRECTSOUNDENUMERATEA,
    CALL_DIRECTSOUNDENUMERATEW,
    CALL_DLLCANUNLOADNOW,
    CALL_DLLGETCLASSOBJECT,
    CALL_DLLREGISTERSERVER,
    CALL_DLLUNREGISTERSERVER,
    CALL_GETDEVICEID,
};

#ifdef QEMU_DLL_GUEST

#else


void qemu_DirectSoundCaptureCreate(struct qemu_syscall *call);
void qemu_DirectSoundCaptureCreate8(struct qemu_syscall *call);
void qemu_DirectSoundCaptureEnumerateA(struct qemu_syscall *call);
void qemu_DirectSoundCaptureEnumerateW(struct qemu_syscall *call);
void qemu_DirectSoundCreate(struct qemu_syscall *call);
void qemu_DirectSoundCreate8(struct qemu_syscall *call);
void qemu_DirectSoundEnumerateA(struct qemu_syscall *call);
void qemu_DirectSoundEnumerateW(struct qemu_syscall *call);
void qemu_DllCanUnloadNow(struct qemu_syscall *call);
void qemu_DllGetClassObject(struct qemu_syscall *call);
void qemu_DllRegisterServer(struct qemu_syscall *call);
void qemu_DllUnregisterServer(struct qemu_syscall *call);
void qemu_GetDeviceID(struct qemu_syscall *call);

extern const struct qemu_ops *qemu_ops;

#endif

#endif
