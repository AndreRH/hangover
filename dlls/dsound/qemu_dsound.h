#ifndef QEMU_DSOUND_H
#define QEMU_DSOUND_H

enum dsound_calls
{
    CALL_DIRECTSOUNDCAPTURECREATE = 0,
    CALL_DIRECTSOUNDCAPTURECREATE8,
    CALL_DIRECTSOUNDCAPTUREENUMERATEA,
    CALL_DIRECTSOUNDCAPTUREENUMERATEW,
    CALL_DIRECTSOUNDCREATE,
    CALL_DIRECTSOUNDENUMERATEA,
    CALL_DIRECTSOUNDENUMERATEW,
    CALL_DIRECTSOUNDFULLDUPLEXCREATE,
    CALL_DLLCANUNLOADNOW,
    CALL_DLLREGISTERSERVER,
    CALL_DLLUNREGISTERSERVER,
    CALL_GETDEVICEID,
    CALL_IDIRECTSOUND8IMPL_COMPACT,
    CALL_IDIRECTSOUND8IMPL_CREATESOUNDBUFFER,
    CALL_IDIRECTSOUND8IMPL_DUPLICATESOUNDBUFFER,
    CALL_IDIRECTSOUND8IMPL_GETCAPS,
    CALL_IDIRECTSOUND8IMPL_GETSPEAKERCONFIG,
    CALL_IDIRECTSOUND8IMPL_INITIALIZE,
    CALL_IDIRECTSOUND8IMPL_RELEASE,
    CALL_IDIRECTSOUND8IMPL_SETCOOPERATIVELEVEL,
    CALL_IDIRECTSOUND8IMPL_SETSPEAKERCONFIG,
    CALL_IDIRECTSOUND8IMPL_VERIFYCERTIFICATION,
};

#ifdef QEMU_DLL_GUEST

HRESULT DSOUND_Create(REFIID riid, void **ppv);
HRESULT DSOUND_Create8(REFIID riid, void **ppv);
HRESULT DSOUND_CaptureCreate(REFIID riid, void **ppv);
HRESULT DSOUND_CaptureCreate8(REFIID riid, void **ppv);
HRESULT DSOUND_FullDuplexCreate(REFIID riid, void **ppv);
HRESULT IKsPrivatePropertySetImpl_Create(REFIID riid, void **ppv);

#else



void qemu_DirectSoundCaptureCreate(struct qemu_syscall *call);
void qemu_DirectSoundCaptureCreate8(struct qemu_syscall *call);
void qemu_DirectSoundCaptureEnumerateA(struct qemu_syscall *call);
void qemu_DirectSoundCaptureEnumerateW(struct qemu_syscall *call);
void qemu_DirectSoundCreate(struct qemu_syscall *call);
void qemu_DirectSoundEnumerateA(struct qemu_syscall *call);
void qemu_DirectSoundEnumerateW(struct qemu_syscall *call);
void qemu_DirectSoundFullDuplexCreate(struct qemu_syscall *call);
void qemu_DllCanUnloadNow(struct qemu_syscall *call);
void qemu_DllRegisterServer(struct qemu_syscall *call);
void qemu_DllUnregisterServer(struct qemu_syscall *call);
void qemu_GetDeviceID(struct qemu_syscall *call);
void qemu_IDirectSound8Impl_Compact(struct qemu_syscall *call);
void qemu_IDirectSound8Impl_CreateSoundBuffer(struct qemu_syscall *call);
void qemu_IDirectSound8Impl_DuplicateSoundBuffer(struct qemu_syscall *call);
void qemu_IDirectSound8Impl_GetCaps(struct qemu_syscall *call);
void qemu_IDirectSound8Impl_GetSpeakerConfig(struct qemu_syscall *call);
void qemu_IDirectSound8Impl_Initialize(struct qemu_syscall *call);
void qemu_IDirectSound8Impl_Release(struct qemu_syscall *call);
void qemu_IDirectSound8Impl_SetCooperativeLevel(struct qemu_syscall *call);
void qemu_IDirectSound8Impl_SetSpeakerConfig(struct qemu_syscall *call);
void qemu_IDirectSound8Impl_VerifyCertification(struct qemu_syscall *call);

extern const struct qemu_ops *qemu_ops;

#endif

#endif
