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
    CALL_IDIRECTSOUNDBUFFERIMPL_ACQUIRERESOURCES,
    CALL_IDIRECTSOUNDBUFFERIMPL_GETCAPS,
    CALL_IDIRECTSOUNDBUFFERIMPL_GETCURRENTPOSITION,
    CALL_IDIRECTSOUNDBUFFERIMPL_GETFORMAT,
    CALL_IDIRECTSOUNDBUFFERIMPL_GETFREQUENCY,
    CALL_IDIRECTSOUNDBUFFERIMPL_GETOBJECTINPATH,
    CALL_IDIRECTSOUNDBUFFERIMPL_GETPAN,
    CALL_IDIRECTSOUNDBUFFERIMPL_GETSTATUS,
    CALL_IDIRECTSOUNDBUFFERIMPL_GETVOLUME,
    CALL_IDIRECTSOUNDBUFFERIMPL_INITIALIZE,
    CALL_IDIRECTSOUNDBUFFERIMPL_LOCK,
    CALL_IDIRECTSOUNDBUFFERIMPL_PLAY,
    CALL_IDIRECTSOUNDBUFFERIMPL_RELEASE,
    CALL_IDIRECTSOUNDBUFFERIMPL_RESTORE,
    CALL_IDIRECTSOUNDBUFFERIMPL_SETCURRENTPOSITION,
    CALL_IDIRECTSOUNDBUFFERIMPL_SETFORMAT,
    CALL_IDIRECTSOUNDBUFFERIMPL_SETFREQUENCY,
    CALL_IDIRECTSOUNDBUFFERIMPL_SETFX,
    CALL_IDIRECTSOUNDBUFFERIMPL_SETPAN,
    CALL_IDIRECTSOUNDBUFFERIMPL_SETVOLUME,
    CALL_IDIRECTSOUNDBUFFERIMPL_STOP,
    CALL_IDIRECTSOUNDBUFFERIMPL_UNLOCK,
    CALL_IDIRECTSOUNDNOTIFYIMPL_SETNOTIFICATIONPOSITIONS,
    CALL_IKSPROPERTYSETIMPL_GET,
    CALL_IKSPROPERTYSETIMPL_QUERYSUPPORT,
    CALL_IKSPROPERTYSETIMPL_SET,
};

struct qemu_dsound_buffer
{
    /* Guest fields. */
    IDirectSoundBuffer8         IDirectSoundBuffer8_iface;
    IDirectSoundNotify          IDirectSoundNotify_iface;
    IDirectSound3DListener      IDirectSound3DListener_iface;
    IDirectSound3DBuffer        IDirectSound3DBuffer_iface;
    IKsPropertySet              IKsPropertySet_iface;

    LONG                        iface_count;
    LONG                        ref, refn, ref_3d, refiks;
    DWORD                       flags;

    /* Host fields. */
    IDirectSoundBuffer8         *host_buffer;
    IDirectSoundNotify          *host_notify;
    IDirectSound3DListener      *host_3d_listener;
    IDirectSound3DBuffer        *host_3d_buffer;
    IKsPropertySet              *host_property;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_dsound_buffer *impl_from_IDirectSoundNotify(IDirectSoundNotify *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dsound_buffer, IDirectSoundNotify_iface);
}

static inline struct qemu_dsound_buffer *impl_from_IDirectSoundBuffer8(IDirectSoundBuffer8 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dsound_buffer, IDirectSoundBuffer8_iface);
}

static inline struct qemu_dsound_buffer *impl_from_IKsPropertySet(IKsPropertySet *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dsound_buffer, IKsPropertySet_iface);
}

HRESULT DSOUND_Create(REFIID riid, void **ppv);
HRESULT DSOUND_Create8(REFIID riid, void **ppv);
HRESULT DSOUND_CaptureCreate(REFIID riid, void **ppv);
HRESULT DSOUND_CaptureCreate8(REFIID riid, void **ppv);
HRESULT DSOUND_FullDuplexCreate(REFIID riid, void **ppv);
HRESULT IKsPrivatePropertySetImpl_Create(REFIID riid, void **ppv);

void buffer_init_guest(struct qemu_dsound_buffer *buffer, DWORD flags);

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
void qemu_IDirectSoundBufferImpl_AcquireResources(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_GetCaps(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_GetCurrentPosition(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_GetFormat(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_GetFrequency(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_GetObjectInPath(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_GetPan(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_GetStatus(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_GetVolume(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_Initialize(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_Lock(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_Play(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_Release(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_Restore(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_SetCurrentPosition(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_SetFX(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_SetFormat(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_SetFrequency(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_SetPan(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_SetVolume(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_Stop(struct qemu_syscall *call);
void qemu_IDirectSoundBufferImpl_Unlock(struct qemu_syscall *call);
void qemu_IDirectSoundNotifyImpl_SetNotificationPositions(struct qemu_syscall *call);
void qemu_IKsPropertySetImpl_Get(struct qemu_syscall *call);
void qemu_IKsPropertySetImpl_QuerySupport(struct qemu_syscall *call);
void qemu_IKsPropertySetImpl_Set(struct qemu_syscall *call);

extern const struct qemu_ops *qemu_ops;

#endif

#endif
