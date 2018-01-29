#ifndef QEMU_DSOUND_H
#define QEMU_DSOUND_H

enum dsound_calls
{
    CALL_DIRECTSOUNDCAPTURECREATE = 0,
    CALL_DIRECTSOUNDCAPTUREENUMERATEA,
    CALL_DIRECTSOUNDCAPTUREENUMERATEW,
    CALL_DIRECTSOUNDCREATE,
    CALL_DIRECTSOUNDENUMERATEA,
    CALL_DIRECTSOUNDENUMERATEW,
    CALL_DIRECTSOUNDFULLDUPLEXCREATE,
    CALL_DIRECTSOUNDFULLDUPLEXRELEASE,
    CALL_DLLCANUNLOADNOW,
    CALL_DLLREGISTERSERVER,
    CALL_DLLUNREGISTERSERVER,
    CALL_GETDEVICEID,
    CALL_IDIRECTSOUND3DBUFFERIMPL_GETALLPARAMETERS,
    CALL_IDIRECTSOUND3DBUFFERIMPL_GETCONEANGLES,
    CALL_IDIRECTSOUND3DBUFFERIMPL_GETCONEORIENTATION,
    CALL_IDIRECTSOUND3DBUFFERIMPL_GETCONEOUTSIDEVOLUME,
    CALL_IDIRECTSOUND3DBUFFERIMPL_GETMAXDISTANCE,
    CALL_IDIRECTSOUND3DBUFFERIMPL_GETMINDISTANCE,
    CALL_IDIRECTSOUND3DBUFFERIMPL_GETMODE,
    CALL_IDIRECTSOUND3DBUFFERIMPL_GETPOSITION,
    CALL_IDIRECTSOUND3DBUFFERIMPL_GETVELOCITY,
    CALL_IDIRECTSOUND3DBUFFERIMPL_SETALLPARAMETERS,
    CALL_IDIRECTSOUND3DBUFFERIMPL_SETCONEANGLES,
    CALL_IDIRECTSOUND3DBUFFERIMPL_SETCONEORIENTATION,
    CALL_IDIRECTSOUND3DBUFFERIMPL_SETCONEOUTSIDEVOLUME,
    CALL_IDIRECTSOUND3DBUFFERIMPL_SETMAXDISTANCE,
    CALL_IDIRECTSOUND3DBUFFERIMPL_SETMINDISTANCE,
    CALL_IDIRECTSOUND3DBUFFERIMPL_SETMODE,
    CALL_IDIRECTSOUND3DBUFFERIMPL_SETPOSITION,
    CALL_IDIRECTSOUND3DBUFFERIMPL_SETVELOCITY,
    CALL_IDIRECTSOUND3DLISTENERIMPL_COMMITDEFERREDSETTINGS,
    CALL_IDIRECTSOUND3DLISTENERIMPL_GETALLPARAMETER,
    CALL_IDIRECTSOUND3DLISTENERIMPL_GETDISTANCEFACTOR,
    CALL_IDIRECTSOUND3DLISTENERIMPL_GETDOPPLERFACTOR,
    CALL_IDIRECTSOUND3DLISTENERIMPL_GETORIENTATION,
    CALL_IDIRECTSOUND3DLISTENERIMPL_GETPOSITION,
    CALL_IDIRECTSOUND3DLISTENERIMPL_GETROLLOFFFACTOR,
    CALL_IDIRECTSOUND3DLISTENERIMPL_GETVELOCITY,
    CALL_IDIRECTSOUND3DLISTENERIMPL_SETALLPARAMETERS,
    CALL_IDIRECTSOUND3DLISTENERIMPL_SETDISTANCEFACTOR,
    CALL_IDIRECTSOUND3DLISTENERIMPL_SETDOPPLERFACTOR,
    CALL_IDIRECTSOUND3DLISTENERIMPL_SETORIENTATION,
    CALL_IDIRECTSOUND3DLISTENERIMPL_SETPOSITION,
    CALL_IDIRECTSOUND3DLISTENERIMPL_SETROLLOFFFACTOR,
    CALL_IDIRECTSOUND3DLISTENERIMPL_SETVELOCITY,
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
    CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_GETCAPS,
    CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_GETCURRENTPOSITION,
    CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_GETFORMAT,
    CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_GETFXSTATUS,
    CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_GETOBJECTINPATH,
    CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_GETSTATUS,
    CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_INITIALIZE,
    CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_LOCK,
    CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_RELEASE,
    CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_START,
    CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_STOP,
    CALL_IDIRECTSOUNDCAPTUREBUFFERIMPL_UNLOCK,
    CALL_IDIRECTSOUNDCAPTUREIMPL_CREATECAPTUREBUFFER,
    CALL_IDIRECTSOUNDCAPTUREIMPL_GETCAPS,
    CALL_IDIRECTSOUNDCAPTUREIMPL_INITIALIZE,
    CALL_IDIRECTSOUNDCAPTUREIMPL_RELEASE,
    CALL_IDIRECTSOUNDNOTIFYIMPL_CAPTURE_SETNOTIFICATIONPOSITIONS,
    CALL_IDIRECTSOUNDNOTIFYIMPL_SETNOTIFICATIONPOSITIONS,
    CALL_IKSPRIVATEPROPERTYSETIMPL_CREATE,
    CALL_IKSPRIVATEPROPERTYSETIMPL_GET,
    CALL_IKSPRIVATEPROPERTYSETIMPL_QUERYSUPPORT,
    CALL_IKSPRIVATEPROPERTYSETIMPL_RELEASE,
    CALL_IKSPRIVATEPROPERTYSETIMPL_SET,
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

static inline struct qemu_dsound_buffer *impl_from_IDirectSound3DBuffer(IDirectSound3DBuffer *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dsound_buffer, IDirectSound3DBuffer_iface);
}

static inline struct qemu_dsound_buffer *impl_from_IDirectSound3DListener(IDirectSound3DListener *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dsound_buffer, IDirectSound3DListener_iface);
}

static inline struct qemu_dsound_buffer *buffer_impl_from_IKsPropertySet(IKsPropertySet *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_dsound_buffer, IKsPropertySet_iface);
}

HRESULT DSOUND_Create(REFIID riid, void **ppv);
HRESULT DSOUND_Create8(REFIID riid, void **ppv);
HRESULT IDirectSoundImpl_Create(IUnknown *outer, REFIID riid, void **out, BOOL has_ds8);
HRESULT DSOUND_CaptureCreate(REFIID riid, void **ppv);
HRESULT DSOUND_CaptureCreate8(REFIID riid, void **ppv);
HRESULT IDirectSoundCaptureImpl_Create(IUnknown *outer_unk, REFIID riid, void **out, BOOL has_dsc8);
HRESULT DSOUND_FullDuplexCreate(REFIID riid, void **ppv);
HRESULT IKsPrivatePropertySetImpl_Create(REFIID riid, void **ppv);

extern const IDirectSound3DBufferVtbl buffer_3d_vtbl;
extern const IDirectSound3DListenerVtbl listener_3d_vtbl;
void buffer_init_guest(struct qemu_dsound_buffer *buffer, DWORD flags);
void secondarybuffer_destroy(struct qemu_dsound_buffer *buffer);
LONG capped_refcount_dec(LONG *out);

#else

void qemu_DirectSoundCaptureCreate(struct qemu_syscall *call);
void qemu_DirectSoundCreate(struct qemu_syscall *call);
void qemu_DirectSoundEnumerate(struct qemu_syscall *call);
void qemu_DirectSoundFullDuplexCreate(struct qemu_syscall *call);
void qemu_DirectSoundFullDuplexRelease(struct qemu_syscall *call);
void qemu_DllCanUnloadNow(struct qemu_syscall *call);
void qemu_DllRegisterServer(struct qemu_syscall *call);
void qemu_DllUnregisterServer(struct qemu_syscall *call);
void qemu_GetDeviceID(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_GetAllParameters(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_GetConeAngles(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_GetConeOrientation(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_GetConeOutsideVolume(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_GetMaxDistance(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_GetMinDistance(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_GetMode(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_GetPosition(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_GetVelocity(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_SetAllParameters(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_SetConeAngles(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_SetConeOrientation(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_SetConeOutsideVolume(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_SetMaxDistance(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_SetMinDistance(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_SetMode(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_SetPosition(struct qemu_syscall *call);
void qemu_IDirectSound3DBufferImpl_SetVelocity(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_CommitDeferredSettings(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_GetAllParameter(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_GetDistanceFactor(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_GetDopplerFactor(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_GetOrientation(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_GetPosition(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_GetRolloffFactor(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_GetVelocity(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_SetAllParameters(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_SetDistanceFactor(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_SetDopplerFactor(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_SetOrientation(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_SetPosition(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_SetRolloffFactor(struct qemu_syscall *call);
void qemu_IDirectSound3DListenerImpl_SetVelocity(struct qemu_syscall *call);
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
void qemu_IDirectSoundCaptureBufferImpl_GetCaps(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureBufferImpl_GetCurrentPosition(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureBufferImpl_GetFXStatus(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureBufferImpl_GetFormat(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureBufferImpl_GetObjectInPath(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureBufferImpl_GetStatus(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureBufferImpl_Initialize(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureBufferImpl_Lock(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureBufferImpl_Release(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureBufferImpl_Start(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureBufferImpl_Stop(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureBufferImpl_Unlock(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureImpl_CreateCaptureBuffer(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureImpl_GetCaps(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureImpl_Initialize(struct qemu_syscall *call);
void qemu_IDirectSoundCaptureImpl_Release(struct qemu_syscall *call);
void qemu_IDirectSoundNotifyImpl_Capture_SetNotificationPositions(struct qemu_syscall *call);
void qemu_IDirectSoundNotifyImpl_SetNotificationPositions(struct qemu_syscall *call);
void qemu_IKsPrivatePropertySetImpl_Create(struct qemu_syscall *call);
void qemu_IKsPrivatePropertySetImpl_Get(struct qemu_syscall *call);
void qemu_IKsPrivatePropertySetImpl_QuerySupport(struct qemu_syscall *call);
void qemu_IKsPrivatePropertySetImpl_Release(struct qemu_syscall *call);
void qemu_IKsPrivatePropertySetImpl_Set(struct qemu_syscall *call);
void qemu_IKsPropertySetImpl_Get(struct qemu_syscall *call);
void qemu_IKsPropertySetImpl_QuerySupport(struct qemu_syscall *call);
void qemu_IKsPropertySetImpl_Set(struct qemu_syscall *call);

extern const struct qemu_ops *qemu_ops;

#endif

#endif
