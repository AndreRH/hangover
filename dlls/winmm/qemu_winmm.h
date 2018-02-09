#ifndef QEMU_WINMM_H
#define QEMU_WINMM_H

#include <stdlib.h>

enum winmm_calls
{
    CALL_AUXGETDEVCAPSA = 0,
    CALL_AUXGETDEVCAPSW,
    CALL_AUXGETNUMDEVS,
    CALL_AUXGETVOLUME,
    CALL_AUXOUTMESSAGE,
    CALL_AUXSETVOLUME,
    CALL_CLOSEDRIVER,
    CALL_DEFDRIVERPROC,
    CALL_DRIVERCALLBACK,
    CALL_GETDRIVERFLAGS,
    CALL_GETDRIVERMODULEHANDLE,
    CALL_JOYCONFIGCHANGED,
    CALL_JOYGETDEVCAPSA,
    CALL_JOYGETDEVCAPSW,
    CALL_JOYGETNUMDEVS,
    CALL_JOYGETPOS,
    CALL_JOYGETPOSEX,
    CALL_JOYGETTHRESHOLD,
    CALL_JOYRELEASECAPTURE,
    CALL_JOYSETCAPTURE,
    CALL_JOYSETTHRESHOLD,
    CALL_MCIDRIVERNOTIFY,
    CALL_MCIDRIVERYIELD,
    CALL_MCIEXECUTE,
    CALL_MCIFREECOMMANDRESOURCE,
    CALL_MCIGETCREATORTASK,
    CALL_MCIGETDEVICEIDA,
    CALL_MCIGETDEVICEIDFROMELEMENTIDA,
    CALL_MCIGETDEVICEIDFROMELEMENTIDW,
    CALL_MCIGETDEVICEIDW,
    CALL_MCIGETDRIVERDATA,
    CALL_MCIGETERRORSTRINGA,
    CALL_MCIGETERRORSTRINGW,
    CALL_MCIGETYIELDPROC,
    CALL_MCILOADCOMMANDRESOURCE,
    CALL_MCISENDCOMMANDA,
    CALL_MCISENDCOMMANDW,
    CALL_MCISENDSTRINGA,
    CALL_MCISENDSTRINGW,
    CALL_MCISETDRIVERDATA,
    CALL_MCISETYIELDPROC,
    CALL_MIDICONNECT,
    CALL_MIDIDISCONNECT,
    CALL_MIDIINADDBUFFER,
    CALL_MIDIINCLOSE,
    CALL_MIDIINGETDEVCAPSA,
    CALL_MIDIINGETDEVCAPSW,
    CALL_MIDIINGETID,
    CALL_MIDIINGETNUMDEVS,
    CALL_MIDIINMESSAGE,
    CALL_MIDIINOPEN,
    CALL_MIDIINPREPAREHEADER,
    CALL_MIDIINRESET,
    CALL_MIDIINSTART,
    CALL_MIDIINSTOP,
    CALL_MIDIINUNPREPAREHEADER,
    CALL_MIDIOUTCACHEDRUMPATCHES,
    CALL_MIDIOUTCACHEPATCHES,
    CALL_MIDIOUTCLOSE,
    CALL_MIDIOUTGETDEVCAPSA,
    CALL_MIDIOUTGETDEVCAPSW,
    CALL_MIDIOUTGETERRORTEXTA,
    CALL_MIDIOUTGETERRORTEXTW,
    CALL_MIDIOUTGETID,
    CALL_MIDIOUTGETNUMDEVS,
    CALL_MIDIOUTGETVOLUME,
    CALL_MIDIOUTLONGMSG,
    CALL_MIDIOUTMESSAGE,
    CALL_MIDIOUTOPEN,
    CALL_MIDIOUTPREPAREHEADER,
    CALL_MIDIOUTRESET,
    CALL_MIDIOUTSETVOLUME,
    CALL_MIDIOUTSHORTMSG,
    CALL_MIDIOUTUNPREPAREHEADER,
    CALL_MIDISTREAMCLOSE,
    CALL_MIDISTREAMOPEN,
    CALL_MIDISTREAMOUT,
    CALL_MIDISTREAMPAUSE,
    CALL_MIDISTREAMPOSITION,
    CALL_MIDISTREAMPROPERTY,
    CALL_MIDISTREAMRESTART,
    CALL_MIDISTREAMSTOP,
    CALL_MIXERCLOSE,
    CALL_MIXERGETCONTROLDETAILSA,
    CALL_MIXERGETCONTROLDETAILSW,
    CALL_MIXERGETDEVCAPSA,
    CALL_MIXERGETDEVCAPSW,
    CALL_MIXERGETID,
    CALL_MIXERGETLINECONTROLSA,
    CALL_MIXERGETLINECONTROLSW,
    CALL_MIXERGETLINEINFOA,
    CALL_MIXERGETLINEINFOW,
    CALL_MIXERGETNUMDEVS,
    CALL_MIXERMESSAGE,
    CALL_MIXEROPEN,
    CALL_MIXERSETCONTROLDETAILS,
    CALL_MMGETCURRENTTASK,
    CALL_MMIOADVANCE,
    CALL_MMIOASCEND,
    CALL_MMIOCLOSE,
    CALL_MMIOCREATECHUNK,
    CALL_MMIODESCEND,
    CALL_MMIOFLUSH,
    CALL_MMIOGETINFO,
    CALL_MMIOINSTALLIOPROCA,
    CALL_MMIOINSTALLIOPROCW,
    CALL_MMIOOPENA,
    CALL_MMIOOPENW,
    CALL_MMIOREAD,
    CALL_MMIORENAMEA,
    CALL_MMIORENAMEW,
    CALL_MMIOSEEK,
    CALL_MMIOSENDMESSAGE,
    CALL_MMIOSETBUFFER,
    CALL_MMIOSETINFO,
    CALL_MMIOSTRINGTOFOURCCA,
    CALL_MMIOSTRINGTOFOURCCW,
    CALL_MMIOWRITE,
    CALL_MMSYSTEMGETVERSION,
    CALL_MMTASKBLOCK,
    CALL_MMTASKCREATE,
    CALL_MMTASKSIGNAL,
    CALL_MMTASKYIELD,
    CALL_OPENDRIVER,
    CALL_OPENDRIVERA,
    CALL_PLAYSOUNDA,
    CALL_PLAYSOUNDW,
    CALL_SENDDRIVERMESSAGE,
    CALL_SNDPLAYSOUNDA,
    CALL_SNDPLAYSOUNDW,
    CALL_TIMEBEGINPERIOD,
    CALL_TIMEENDPERIOD,
    CALL_TIMEGETDEVCAPS,
    CALL_TIMEGETSYSTEMTIME,
    CALL_TIMEKILLEVENT,
    CALL_TIMESETEVENT,
    CALL_WAVEINADDBUFFER,
    CALL_WAVEINCLOSE,
    CALL_WAVEINGETDEVCAPSA,
    CALL_WAVEINGETDEVCAPSW,
    CALL_WAVEINGETID,
    CALL_WAVEINGETNUMDEVS,
    CALL_WAVEINGETPOSITION,
    CALL_WAVEINMESSAGE,
    CALL_WAVEINOPEN,
    CALL_WAVEINPREPAREHEADER,
    CALL_WAVEINRESET,
    CALL_WAVEINSTART,
    CALL_WAVEINSTOP,
    CALL_WAVEINUNPREPAREHEADER,
    CALL_WAVEOUTBREAKLOOP,
    CALL_WAVEOUTCLOSE,
    CALL_WAVEOUTGETDEVCAPSA,
    CALL_WAVEOUTGETDEVCAPSW,
    CALL_WAVEOUTGETERRORTEXTA,
    CALL_WAVEOUTGETERRORTEXTW,
    CALL_WAVEOUTGETID,
    CALL_WAVEOUTGETNUMDEVS,
    CALL_WAVEOUTGETPITCH,
    CALL_WAVEOUTGETPLAYBACKRATE,
    CALL_WAVEOUTGETPOSITION,
    CALL_WAVEOUTGETVOLUME,
    CALL_WAVEOUTMESSAGE,
    CALL_WAVEOUTOPEN,
    CALL_WAVEOUTPAUSE,
    CALL_WAVEOUTPREPAREHEADER,
    CALL_WAVEOUTRESET,
    CALL_WAVEOUTRESTART,
    CALL_WAVEOUTSETPITCH,
    CALL_WAVEOUTSETPLAYBACKRATE,
    CALL_WAVEOUTSETVOLUME,
    CALL_WAVEOUTUNPREPAREHEADER,
    CALL_WAVEOUTWRITE,
};

#ifdef QEMU_DLL_GUEST

#else

extern const struct qemu_ops *qemu_ops;

void qemu_CloseDriver(struct qemu_syscall *call);
void qemu_DefDriverProc(struct qemu_syscall *call);
void qemu_DriverCallback(struct qemu_syscall *call);
void qemu_GetDriverFlags(struct qemu_syscall *call);
void qemu_GetDriverModuleHandle(struct qemu_syscall *call);
void qemu_OpenDriver(struct qemu_syscall *call);
void qemu_OpenDriverA(struct qemu_syscall *call);
void qemu_PlaySoundA(struct qemu_syscall *call);
void qemu_PlaySoundW(struct qemu_syscall *call);
void qemu_SendDriverMessage(struct qemu_syscall *call);
void qemu_auxGetDevCapsA(struct qemu_syscall *call);
void qemu_auxGetDevCapsW(struct qemu_syscall *call);
void qemu_auxGetNumDevs(struct qemu_syscall *call);
void qemu_auxGetVolume(struct qemu_syscall *call);
void qemu_auxOutMessage(struct qemu_syscall *call);
void qemu_auxSetVolume(struct qemu_syscall *call);
void qemu_joyConfigChanged(struct qemu_syscall *call);
void qemu_joyGetDevCapsA(struct qemu_syscall *call);
void qemu_joyGetDevCapsW(struct qemu_syscall *call);
void qemu_joyGetNumDevs(struct qemu_syscall *call);
void qemu_joyGetPos(struct qemu_syscall *call);
void qemu_joyGetPosEx(struct qemu_syscall *call);
void qemu_joyGetThreshold(struct qemu_syscall *call);
void qemu_joyReleaseCapture(struct qemu_syscall *call);
void qemu_joySetCapture(struct qemu_syscall *call);
void qemu_joySetThreshold(struct qemu_syscall *call);
void qemu_mciDriverNotify(struct qemu_syscall *call);
void qemu_mciDriverYield(struct qemu_syscall *call);
void qemu_mciExecute(struct qemu_syscall *call);
void qemu_mciFreeCommandResource(struct qemu_syscall *call);
void qemu_mciGetCreatorTask(struct qemu_syscall *call);
void qemu_mciGetDeviceIDA(struct qemu_syscall *call);
void qemu_mciGetDeviceIDFromElementIDA(struct qemu_syscall *call);
void qemu_mciGetDeviceIDFromElementIDW(struct qemu_syscall *call);
void qemu_mciGetDeviceIDW(struct qemu_syscall *call);
void qemu_mciGetDriverData(struct qemu_syscall *call);
void qemu_mciGetErrorStringA(struct qemu_syscall *call);
void qemu_mciGetErrorStringW(struct qemu_syscall *call);
void qemu_mciGetYieldProc(struct qemu_syscall *call);
void qemu_mciLoadCommandResource(struct qemu_syscall *call);
void qemu_mciSendCommandA(struct qemu_syscall *call);
void qemu_mciSendCommandW(struct qemu_syscall *call);
void qemu_mciSendStringA(struct qemu_syscall *call);
void qemu_mciSendStringW(struct qemu_syscall *call);
void qemu_mciSetDriverData(struct qemu_syscall *call);
void qemu_mciSetYieldProc(struct qemu_syscall *call);
void qemu_midiConnect(struct qemu_syscall *call);
void qemu_midiDisconnect(struct qemu_syscall *call);
void qemu_midiInAddBuffer(struct qemu_syscall *call);
void qemu_midiInClose(struct qemu_syscall *call);
void qemu_midiInGetDevCapsA(struct qemu_syscall *call);
void qemu_midiInGetDevCapsW(struct qemu_syscall *call);
void qemu_midiInGetID(struct qemu_syscall *call);
void qemu_midiInGetNumDevs(struct qemu_syscall *call);
void qemu_midiInMessage(struct qemu_syscall *call);
void qemu_midiInOpen(struct qemu_syscall *call);
void qemu_midiInPrepareHeader(struct qemu_syscall *call);
void qemu_midiInReset(struct qemu_syscall *call);
void qemu_midiInStart(struct qemu_syscall *call);
void qemu_midiInStop(struct qemu_syscall *call);
void qemu_midiInUnprepareHeader(struct qemu_syscall *call);
void qemu_midiOutCacheDrumPatches(struct qemu_syscall *call);
void qemu_midiOutCachePatches(struct qemu_syscall *call);
void qemu_midiOutClose(struct qemu_syscall *call);
void qemu_midiOutGetDevCapsA(struct qemu_syscall *call);
void qemu_midiOutGetDevCapsW(struct qemu_syscall *call);
void qemu_midiOutGetErrorTextA(struct qemu_syscall *call);
void qemu_midiOutGetErrorTextW(struct qemu_syscall *call);
void qemu_midiOutGetID(struct qemu_syscall *call);
void qemu_midiOutGetNumDevs(struct qemu_syscall *call);
void qemu_midiOutGetVolume(struct qemu_syscall *call);
void qemu_midiOutLongMsg(struct qemu_syscall *call);
void qemu_midiOutMessage(struct qemu_syscall *call);
void qemu_midiOutOpen(struct qemu_syscall *call);
void qemu_midiOutPrepareHeader(struct qemu_syscall *call);
void qemu_midiOutReset(struct qemu_syscall *call);
void qemu_midiOutSetVolume(struct qemu_syscall *call);
void qemu_midiOutShortMsg(struct qemu_syscall *call);
void qemu_midiOutUnprepareHeader(struct qemu_syscall *call);
void qemu_midiStreamClose(struct qemu_syscall *call);
void qemu_midiStreamOpen(struct qemu_syscall *call);
void qemu_midiStreamOut(struct qemu_syscall *call);
void qemu_midiStreamPause(struct qemu_syscall *call);
void qemu_midiStreamPosition(struct qemu_syscall *call);
void qemu_midiStreamProperty(struct qemu_syscall *call);
void qemu_midiStreamRestart(struct qemu_syscall *call);
void qemu_midiStreamStop(struct qemu_syscall *call);
void qemu_mixerClose(struct qemu_syscall *call);
void qemu_mixerGetControlDetails(struct qemu_syscall *call);
void qemu_mixerGetControlDetails(struct qemu_syscall *call);
void qemu_mixerGetDevCapsA(struct qemu_syscall *call);
void qemu_mixerGetDevCapsW(struct qemu_syscall *call);
void qemu_mixerGetID(struct qemu_syscall *call);
void qemu_mixerGetLineControls(struct qemu_syscall *call);
void qemu_mixerGetLineInfoA(struct qemu_syscall *call);
void qemu_mixerGetLineInfoW(struct qemu_syscall *call);
void qemu_mixerGetNumDevs(struct qemu_syscall *call);
void qemu_mixerMessage(struct qemu_syscall *call);
void qemu_mixerOpen(struct qemu_syscall *call);
void qemu_mixerSetControlDetails(struct qemu_syscall *call);
void qemu_mmGetCurrentTask(struct qemu_syscall *call);
void qemu_mmTaskBlock(struct qemu_syscall *call);
void qemu_mmTaskCreate(struct qemu_syscall *call);
void qemu_mmTaskSignal(struct qemu_syscall *call);
void qemu_mmTaskYield(struct qemu_syscall *call);
void qemu_mmioAdvance(struct qemu_syscall *call);
void qemu_mmioAscend(struct qemu_syscall *call);
void qemu_mmioClose(struct qemu_syscall *call);
void qemu_mmioCreateChunk(struct qemu_syscall *call);
void qemu_mmioDescend(struct qemu_syscall *call);
void qemu_mmioFlush(struct qemu_syscall *call);
void qemu_mmioGetInfo(struct qemu_syscall *call);
void qemu_mmioInstallIOProcA(struct qemu_syscall *call);
void qemu_mmioInstallIOProcW(struct qemu_syscall *call);
void qemu_mmioOpen(struct qemu_syscall *call);
void qemu_mmioRead(struct qemu_syscall *call);
void qemu_mmioRenameA(struct qemu_syscall *call);
void qemu_mmioRenameW(struct qemu_syscall *call);
void qemu_mmioSeek(struct qemu_syscall *call);
void qemu_mmioSendMessage(struct qemu_syscall *call);
void qemu_mmioSetBuffer(struct qemu_syscall *call);
void qemu_mmioSetInfo(struct qemu_syscall *call);
void qemu_mmioStringToFOURCCA(struct qemu_syscall *call);
void qemu_mmioStringToFOURCCW(struct qemu_syscall *call);
void qemu_mmioWrite(struct qemu_syscall *call);
void qemu_mmsystemGetVersion(struct qemu_syscall *call);
void qemu_sndPlaySoundA(struct qemu_syscall *call);
void qemu_sndPlaySoundW(struct qemu_syscall *call);
void qemu_timeBeginPeriod(struct qemu_syscall *call);
void qemu_timeEndPeriod(struct qemu_syscall *call);
void qemu_timeGetDevCaps(struct qemu_syscall *call);
void qemu_timeGetSystemTime(struct qemu_syscall *call);
void qemu_timeKillEvent(struct qemu_syscall *call);
void qemu_timeSetEvent(struct qemu_syscall *call);
void qemu_waveHeaderOp(struct qemu_syscall *call);
void qemu_waveInAddBuffer(struct qemu_syscall *call);
void qemu_waveInClose(struct qemu_syscall *call);
void qemu_waveInGetDevCapsA(struct qemu_syscall *call);
void qemu_waveInGetDevCapsW(struct qemu_syscall *call);
void qemu_waveInGetID(struct qemu_syscall *call);
void qemu_waveInGetNumDevs(struct qemu_syscall *call);
void qemu_waveInGetPosition(struct qemu_syscall *call);
void qemu_waveInMessage(struct qemu_syscall *call);
void qemu_waveInOpen(struct qemu_syscall *call);
void qemu_waveInReset(struct qemu_syscall *call);
void qemu_waveInStart(struct qemu_syscall *call);
void qemu_waveInStop(struct qemu_syscall *call);
void qemu_waveOutBreakLoop(struct qemu_syscall *call);
void qemu_waveOutClose(struct qemu_syscall *call);
void qemu_waveOutGetDevCapsA(struct qemu_syscall *call);
void qemu_waveOutGetDevCapsW(struct qemu_syscall *call);
void qemu_waveOutGetErrorTextA(struct qemu_syscall *call);
void qemu_waveOutGetErrorTextW(struct qemu_syscall *call);
void qemu_waveOutGetID(struct qemu_syscall *call);
void qemu_waveOutGetNumDevs(struct qemu_syscall *call);
void qemu_waveOutGetPitch(struct qemu_syscall *call);
void qemu_waveOutGetPlaybackRate(struct qemu_syscall *call);
void qemu_waveOutGetPosition(struct qemu_syscall *call);
void qemu_waveOutGetVolume(struct qemu_syscall *call);
void qemu_waveOutMessage(struct qemu_syscall *call);
void qemu_waveOutOpen(struct qemu_syscall *call);
void qemu_waveOutPause(struct qemu_syscall *call);
void qemu_waveOutReset(struct qemu_syscall *call);
void qemu_waveOutRestart(struct qemu_syscall *call);
void qemu_waveOutSetPitch(struct qemu_syscall *call);
void qemu_waveOutSetPlaybackRate(struct qemu_syscall *call);
void qemu_waveOutSetVolume(struct qemu_syscall *call);

#endif

#endif
