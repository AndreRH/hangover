/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef QEMU_MMDEVAPI_H
#define QEMU_MMDEVAPI_H

/* Mingw's strmif.h spams plenty of warnings about things in the header being incorrect, so just declare
 * IID_IBaseFilter manually. */
DEFINE_GUID(IID_IBaseFilter, 0x56a86895, 0x0ad4, 0x11ce, 0xb0,0x3a, 0x00,0x20,0xaf,0x0b,0xa7,0x70);

enum mmdevapi_calls
{
    CALL_AUDIOCAPTURECLIENT_ADDREF = 0,
    CALL_AUDIOCAPTURECLIENT_GETBUFFER,
    CALL_AUDIOCAPTURECLIENT_GETNEXTPACKETSIZE,
    CALL_AUDIOCAPTURECLIENT_QUERYINTERFACE,
    CALL_AUDIOCAPTURECLIENT_RELEASE,
    CALL_AUDIOCAPTURECLIENT_RELEASEBUFFER,
    CALL_AUDIOCLIENT_ADDREF,
    CALL_AUDIOCLIENT_GETBUFFERSIZE,
    CALL_AUDIOCLIENT_GETCURRENTPADDING,
    CALL_AUDIOCLIENT_GETDEVICEPERIOD,
    CALL_AUDIOCLIENT_GETMIXFORMAT,
    CALL_AUDIOCLIENT_GETSERVICE,
    CALL_AUDIOCLIENT_GETSTREAMLATENCY,
    CALL_AUDIOCLIENT_INITIALIZE,
    CALL_AUDIOCLIENT_ISFORMATSUPPORTED,
    CALL_AUDIOCLIENT_QUERYINTERFACE,
    CALL_AUDIOCLIENT_RELEASE,
    CALL_AUDIOCLIENT_RESET,
    CALL_AUDIOCLIENT_SETEVENTHANDLE,
    CALL_AUDIOCLIENT_START,
    CALL_AUDIOCLIENT_STOP,
    CALL_AUDIOCLOCK2_ADDREF,
    CALL_AUDIOCLOCK2_GETDEVICEPOSITION,
    CALL_AUDIOCLOCK2_QUERYINTERFACE,
    CALL_AUDIOCLOCK2_RELEASE,
    CALL_AUDIOCLOCK_ADDREF,
    CALL_AUDIOCLOCK_GETCHARACTERISTICS,
    CALL_AUDIOCLOCK_GETFREQUENCY,
    CALL_AUDIOCLOCK_GETPOSITION,
    CALL_AUDIOCLOCK_QUERYINTERFACE,
    CALL_AUDIOCLOCK_RELEASE,
    CALL_AUDIORENDERCLIENT_ADDREF,
    CALL_AUDIORENDERCLIENT_GETBUFFER,
    CALL_AUDIORENDERCLIENT_QUERYINTERFACE,
    CALL_AUDIORENDERCLIENT_RELEASE,
    CALL_AUDIORENDERCLIENT_RELEASEBUFFER,
    CALL_AUDIOSESSIONCONTROL_ADDREF,
    CALL_AUDIOSESSIONCONTROL_GETDISPLAYNAME,
    CALL_AUDIOSESSIONCONTROL_GETGROUPINGPARAM,
    CALL_AUDIOSESSIONCONTROL_GETICONPATH,
    CALL_AUDIOSESSIONCONTROL_GETPROCESSID,
    CALL_AUDIOSESSIONCONTROL_GETSESSIONIDENTIFIER,
    CALL_AUDIOSESSIONCONTROL_GETSESSIONINSTANCEIDENTIFIER,
    CALL_AUDIOSESSIONCONTROL_GETSTATE,
    CALL_AUDIOSESSIONCONTROL_ISSYSTEMSOUNDSSESSION,
    CALL_AUDIOSESSIONCONTROL_QUERYINTERFACE,
    CALL_AUDIOSESSIONCONTROL_REGISTERAUDIOSESSIONNOTIFICATION,
    CALL_AUDIOSESSIONCONTROL_RELEASE,
    CALL_AUDIOSESSIONCONTROL_SETDISPLAYNAME,
    CALL_AUDIOSESSIONCONTROL_SETDUCKINGPREFERENCE,
    CALL_AUDIOSESSIONCONTROL_SETGROUPINGPARAM,
    CALL_AUDIOSESSIONCONTROL_SETICONPATH,
    CALL_AUDIOSESSIONCONTROL_UNREGISTERAUDIOSESSIONNOTIFICATION,
    CALL_AUDIOSESSIONMANAGER_ADDREF,
    CALL_AUDIOSESSIONMANAGER_GETAUDIOSESSIONCONTROL,
    CALL_AUDIOSESSIONMANAGER_GETSESSIONENUMERATOR,
    CALL_AUDIOSESSIONMANAGER_GETSIMPLEAUDIOVOLUME,
    CALL_AUDIOSESSIONMANAGER_QUERYINTERFACE,
    CALL_AUDIOSESSIONMANAGER_REGISTERDUCKNOTIFICATION,
    CALL_AUDIOSESSIONMANAGER_REGISTERSESSIONNOTIFICATION,
    CALL_AUDIOSESSIONMANAGER_RELEASE,
    CALL_AUDIOSESSIONMANAGER_UNREGISTERDUCKNOTIFICATION,
    CALL_AUDIOSESSIONMANAGER_UNREGISTERSESSIONNOTIFICATION,
    CALL_AUDIOSTREAMVOLUME_ADDREF,
    CALL_AUDIOSTREAMVOLUME_GETALLVOLUMES,
    CALL_AUDIOSTREAMVOLUME_GETCHANNELCOUNT,
    CALL_AUDIOSTREAMVOLUME_GETCHANNELVOLUME,
    CALL_AUDIOSTREAMVOLUME_QUERYINTERFACE,
    CALL_AUDIOSTREAMVOLUME_RELEASE,
    CALL_AUDIOSTREAMVOLUME_SETALLVOLUMES,
    CALL_AUDIOSTREAMVOLUME_SETCHANNELVOLUME,
    CALL_CHANNELAUDIOVOLUME_ADDREF,
    CALL_CHANNELAUDIOVOLUME_GETALLVOLUMES,
    CALL_CHANNELAUDIOVOLUME_GETCHANNELCOUNT,
    CALL_CHANNELAUDIOVOLUME_GETCHANNELVOLUME,
    CALL_CHANNELAUDIOVOLUME_QUERYINTERFACE,
    CALL_CHANNELAUDIOVOLUME_RELEASE,
    CALL_CHANNELAUDIOVOLUME_SETALLVOLUMES,
    CALL_CHANNELAUDIOVOLUME_SETCHANNELVOLUME,
    CALL_INIT_DLL,
    CALL_MMDEVCOL_ADDREF,
    CALL_MMDEVCOL_GETCOUNT,
    CALL_MMDEVCOL_ITEM,
    CALL_MMDEVCOL_QUERYINTERFACE,
    CALL_MMDEVCOL_RELEASE,
    CALL_MMDEVENUM_ADDREF,
    CALL_MMDEVENUM_CREATE,
    CALL_MMDEVENUM_ENUMAUDIOENDPOINTS,
    CALL_MMDEVENUM_GETDEFAULTAUDIOENDPOINT,
    CALL_MMDEVENUM_GETDEVICE,
    CALL_MMDEVENUM_QUERYINTERFACE,
    CALL_MMDEVENUM_REGISTERENDPOINTNOTIFICATIONCALLBACK,
    CALL_MMDEVENUM_RELEASE,
    CALL_MMDEVENUM_UNREGISTERENDPOINTNOTIFICATIONCALLBACK,
    CALL_MMDEVICE_ACTIVATE,
    CALL_MMDEVICE_ADDREF,
    CALL_MMDEVICE_GETID,
    CALL_MMDEVICE_GETSTATE,
    CALL_MMDEVICE_OPENPROPERTYSTORE,
    CALL_MMDEVICE_QUERYINTERFACE,
    CALL_MMDEVICE_RELEASE,
    CALL_MMDEVPROPSTORE_ADDREF,
    CALL_MMDEVPROPSTORE_COMMIT,
    CALL_MMDEVPROPSTORE_GETAT,
    CALL_MMDEVPROPSTORE_GETCOUNT,
    CALL_MMDEVPROPSTORE_GETVALUE,
    CALL_MMDEVPROPSTORE_QUERYINTERFACE,
    CALL_MMDEVPROPSTORE_RELEASE,
    CALL_MMDEVPROPSTORE_SETVALUE,
    CALL_MMENDPOINT_ADDREF,
    CALL_MMENDPOINT_GETDATAFLOW,
    CALL_MMENDPOINT_QUERYINTERFACE,
    CALL_MMENDPOINT_RELEASE,
    CALL_SIMPLEAUDIOVOLUME_ADDREF,
    CALL_SIMPLEAUDIOVOLUME_GETMASTERVOLUME,
    CALL_SIMPLEAUDIOVOLUME_GETMUTE,
    CALL_SIMPLEAUDIOVOLUME_QUERYINTERFACE,
    CALL_SIMPLEAUDIOVOLUME_RELEASE,
    CALL_SIMPLEAUDIOVOLUME_SETMASTERVOLUME,
    CALL_SIMPLEAUDIOVOLUME_SETMUTE,
};

struct qemu_mmdevice
{
    /* Guest fields */
    IMMDevice IMMDevice_iface;
    IMMEndpoint IMMEndpoint_iface;

    /* Host fields */
    IMMDevice *host_device;
    IMMEndpoint *host_endpoint;
    struct list entry;
};

struct qemu_audioclient
{
    /* Guest fields */
    IAudioClient IAudioClient_iface;
    IAudioRenderClient IAudioRenderClient_iface;
    IAudioCaptureClient IAudioCaptureClient_iface;
    IAudioClock IAudioClock_iface;
    IAudioClock2 IAudioClock2_iface;
    IAudioStreamVolume IAudioStreamVolume_iface;

    /* Host fields */
    IAudioClient *host_client;
    IAudioRenderClient *host_render;
    IAudioCaptureClient *host_capture;
    IAudioClock *host_clock;
    IAudioClock2 *host_clock2;
    IAudioStreamVolume *host_volume;
};

struct qemu_audiosession
{
    /* Guest fields */
    IAudioSessionControl2 IAudioSessionControl2_iface;
    IChannelAudioVolume IChannelAudioVolume_iface;
    ISimpleAudioVolume ISimpleAudioVolume_iface;

    /* Host fields */
    IAudioSessionControl2 *host_control;
    IChannelAudioVolume *host_chan_vol;
    ISimpleAudioVolume *host_simple_vol;
};

struct qemu_sessmgr
{
    /* Guest fields */
    IAudioSessionManager2 IAudioSessionManager2_iface;

    /* Host fields */
    IAudioSessionManager2 *host;
};

#ifdef QEMU_DLL_GUEST

HRESULT MMDevEnum_Create(const IID *iid, void **ppv);

#else

HMODULE mmdevapi_mod;
extern const struct qemu_ops *qemu_ops;

void qemu_AudioCaptureClient_AddRef(struct qemu_syscall *call);
void qemu_AudioCaptureClient_GetBuffer(struct qemu_syscall *call);
void qemu_AudioCaptureClient_GetNextPacketSize(struct qemu_syscall *call);
void qemu_AudioCaptureClient_QueryInterface(struct qemu_syscall *call);
void qemu_AudioCaptureClient_Release(struct qemu_syscall *call);
void qemu_AudioCaptureClient_ReleaseBuffer(struct qemu_syscall *call);
void qemu_AudioClient_AddRef(struct qemu_syscall *call);
void qemu_AudioClient_GetBufferSize(struct qemu_syscall *call);
void qemu_AudioClient_GetCurrentPadding(struct qemu_syscall *call);
void qemu_AudioClient_GetDevicePeriod(struct qemu_syscall *call);
void qemu_AudioClient_GetMixFormat(struct qemu_syscall *call);
void qemu_AudioClient_GetService(struct qemu_syscall *call);
void qemu_AudioClient_GetStreamLatency(struct qemu_syscall *call);
void qemu_AudioClient_Initialize(struct qemu_syscall *call);
void qemu_AudioClient_IsFormatSupported(struct qemu_syscall *call);
void qemu_AudioClient_QueryInterface(struct qemu_syscall *call);
void qemu_AudioClient_Release(struct qemu_syscall *call);
void qemu_AudioClient_Reset(struct qemu_syscall *call);
void qemu_AudioClient_SetEventHandle(struct qemu_syscall *call);
void qemu_AudioClient_Start(struct qemu_syscall *call);
void qemu_AudioClient_Stop(struct qemu_syscall *call);
void qemu_AudioClock2_AddRef(struct qemu_syscall *call);
void qemu_AudioClock2_GetDevicePosition(struct qemu_syscall *call);
void qemu_AudioClock2_QueryInterface(struct qemu_syscall *call);
void qemu_AudioClock2_Release(struct qemu_syscall *call);
void qemu_AudioClock_AddRef(struct qemu_syscall *call);
void qemu_AudioClock_GetCharacteristics(struct qemu_syscall *call);
void qemu_AudioClock_GetFrequency(struct qemu_syscall *call);
void qemu_AudioClock_GetPosition(struct qemu_syscall *call);
void qemu_AudioClock_QueryInterface(struct qemu_syscall *call);
void qemu_AudioClock_Release(struct qemu_syscall *call);
void qemu_AudioRenderClient_AddRef(struct qemu_syscall *call);
void qemu_AudioRenderClient_GetBuffer(struct qemu_syscall *call);
void qemu_AudioRenderClient_QueryInterface(struct qemu_syscall *call);
void qemu_AudioRenderClient_Release(struct qemu_syscall *call);
void qemu_AudioRenderClient_ReleaseBuffer(struct qemu_syscall *call);
void qemu_AudioSessionControl_AddRef(struct qemu_syscall *call);
void qemu_AudioSessionControl_GetDisplayName(struct qemu_syscall *call);
void qemu_AudioSessionControl_GetGroupingParam(struct qemu_syscall *call);
void qemu_AudioSessionControl_GetIconPath(struct qemu_syscall *call);
void qemu_AudioSessionControl_GetProcessId(struct qemu_syscall *call);
void qemu_AudioSessionControl_GetSessionIdentifier(struct qemu_syscall *call);
void qemu_AudioSessionControl_GetSessionInstanceIdentifier(struct qemu_syscall *call);
void qemu_AudioSessionControl_GetState(struct qemu_syscall *call);
void qemu_AudioSessionControl_IsSystemSoundsSession(struct qemu_syscall *call);
void qemu_AudioSessionControl_QueryInterface(struct qemu_syscall *call);
void qemu_AudioSessionControl_RegisterAudioSessionNotification(struct qemu_syscall *call);
void qemu_AudioSessionControl_Release(struct qemu_syscall *call);
void qemu_AudioSessionControl_SetDisplayName(struct qemu_syscall *call);
void qemu_AudioSessionControl_SetDuckingPreference(struct qemu_syscall *call);
void qemu_AudioSessionControl_SetGroupingParam(struct qemu_syscall *call);
void qemu_AudioSessionControl_SetIconPath(struct qemu_syscall *call);
void qemu_AudioSessionControl_UnregisterAudioSessionNotification(struct qemu_syscall *call);
void qemu_AudioSessionManager_AddRef(struct qemu_syscall *call);
void qemu_AudioSessionManager_GetAudioSessionControl(struct qemu_syscall *call);
void qemu_AudioSessionManager_GetSessionEnumerator(struct qemu_syscall *call);
void qemu_AudioSessionManager_GetSimpleAudioVolume(struct qemu_syscall *call);
void qemu_AudioSessionManager_QueryInterface(struct qemu_syscall *call);
void qemu_AudioSessionManager_RegisterDuckNotification(struct qemu_syscall *call);
void qemu_AudioSessionManager_RegisterSessionNotification(struct qemu_syscall *call);
void qemu_AudioSessionManager_Release(struct qemu_syscall *call);
void qemu_AudioSessionManager_UnregisterDuckNotification(struct qemu_syscall *call);
void qemu_AudioSessionManager_UnregisterSessionNotification(struct qemu_syscall *call);
void qemu_AudioStreamVolume_AddRef(struct qemu_syscall *call);
void qemu_AudioStreamVolume_GetAllVolumes(struct qemu_syscall *call);
void qemu_AudioStreamVolume_GetChannelCount(struct qemu_syscall *call);
void qemu_AudioStreamVolume_GetChannelVolume(struct qemu_syscall *call);
void qemu_AudioStreamVolume_QueryInterface(struct qemu_syscall *call);
void qemu_AudioStreamVolume_Release(struct qemu_syscall *call);
void qemu_AudioStreamVolume_SetAllVolumes(struct qemu_syscall *call);
void qemu_AudioStreamVolume_SetChannelVolume(struct qemu_syscall *call);
void qemu_ChannelAudioVolume_AddRef(struct qemu_syscall *call);
void qemu_ChannelAudioVolume_GetAllVolumes(struct qemu_syscall *call);
void qemu_ChannelAudioVolume_GetChannelCount(struct qemu_syscall *call);
void qemu_ChannelAudioVolume_GetChannelVolume(struct qemu_syscall *call);
void qemu_ChannelAudioVolume_QueryInterface(struct qemu_syscall *call);
void qemu_ChannelAudioVolume_Release(struct qemu_syscall *call);
void qemu_ChannelAudioVolume_SetAllVolumes(struct qemu_syscall *call);
void qemu_ChannelAudioVolume_SetChannelVolume(struct qemu_syscall *call);
void qemu_MMDevCol_AddRef(struct qemu_syscall *call);
void qemu_MMDevCol_GetCount(struct qemu_syscall *call);
void qemu_MMDevCol_Item(struct qemu_syscall *call);
void qemu_MMDevCol_QueryInterface(struct qemu_syscall *call);
void qemu_MMDevCol_Release(struct qemu_syscall *call);
void qemu_MMDevEnum_AddRef(struct qemu_syscall *call);
void qemu_MMDevEnum_Create(struct qemu_syscall *call);
void qemu_MMDevEnum_EnumAudioEndpoints(struct qemu_syscall *call);
void qemu_MMDevEnum_GetDefaultAudioEndpoint(struct qemu_syscall *call);
void qemu_MMDevEnum_GetDevice(struct qemu_syscall *call);
void qemu_MMDevEnum_QueryInterface(struct qemu_syscall *call);
void qemu_MMDevEnum_RegisterEndpointNotificationCallback(struct qemu_syscall *call);
void qemu_MMDevEnum_Release(struct qemu_syscall *call);
void qemu_MMDevEnum_UnregisterEndpointNotificationCallback(struct qemu_syscall *call);
void qemu_MMDevPropStore_AddRef(struct qemu_syscall *call);
void qemu_MMDevPropStore_Commit(struct qemu_syscall *call);
void qemu_MMDevPropStore_GetAt(struct qemu_syscall *call);
void qemu_MMDevPropStore_GetCount(struct qemu_syscall *call);
void qemu_MMDevPropStore_GetValue(struct qemu_syscall *call);
void qemu_MMDevPropStore_QueryInterface(struct qemu_syscall *call);
void qemu_MMDevPropStore_Release(struct qemu_syscall *call);
void qemu_MMDevPropStore_SetValue(struct qemu_syscall *call);
void qemu_MMDevice_Activate(struct qemu_syscall *call);
void qemu_MMDevice_AddRef(struct qemu_syscall *call);
void qemu_MMDevice_GetId(struct qemu_syscall *call);
void qemu_MMDevice_GetState(struct qemu_syscall *call);
void qemu_MMDevice_OpenPropertyStore(struct qemu_syscall *call);
void qemu_MMDevice_QueryInterface(struct qemu_syscall *call);
void qemu_MMDevice_Release(struct qemu_syscall *call);
void qemu_MMEndpoint_AddRef(struct qemu_syscall *call);
void qemu_MMEndpoint_GetDataFlow(struct qemu_syscall *call);
void qemu_MMEndpoint_QueryInterface(struct qemu_syscall *call);
void qemu_MMEndpoint_Release(struct qemu_syscall *call);
void qemu_SimpleAudioVolume_AddRef(struct qemu_syscall *call);
void qemu_SimpleAudioVolume_GetMasterVolume(struct qemu_syscall *call);
void qemu_SimpleAudioVolume_GetMute(struct qemu_syscall *call);
void qemu_SimpleAudioVolume_QueryInterface(struct qemu_syscall *call);
void qemu_SimpleAudioVolume_Release(struct qemu_syscall *call);
void qemu_SimpleAudioVolume_SetMasterVolume(struct qemu_syscall *call);
void qemu_SimpleAudioVolume_SetMute(struct qemu_syscall *call);

#endif

#endif
