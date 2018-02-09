/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_winmm.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_winmm);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_auxGetDevCapsA,
    qemu_auxGetDevCapsW,
    qemu_auxGetNumDevs,
    qemu_auxGetVolume,
    qemu_auxOutMessage,
    qemu_auxSetVolume,
    qemu_CloseDriver,
    qemu_DefDriverProc,
    qemu_DriverCallback,
    qemu_GetDriverFlags,
    qemu_GetDriverModuleHandle,
    qemu_joyConfigChanged,
    qemu_joyGetDevCapsA,
    qemu_joyGetDevCapsW,
    qemu_joyGetNumDevs,
    qemu_joyGetPos,
    qemu_joyGetPosEx,
    qemu_joyGetThreshold,
    qemu_joyReleaseCapture,
    qemu_joySetCapture,
    qemu_joySetThreshold,
    qemu_mciDriverNotify,
    qemu_mciDriverYield,
    qemu_mciExecute,
    qemu_mciFreeCommandResource,
    qemu_mciGetCreatorTask,
    qemu_mciGetDeviceIDA,
    qemu_mciGetDeviceIDFromElementIDA,
    qemu_mciGetDeviceIDFromElementIDW,
    qemu_mciGetDeviceIDW,
    qemu_mciGetDriverData,
    qemu_mciGetErrorStringA,
    qemu_mciGetErrorStringW,
    qemu_mciGetYieldProc,
    qemu_mciLoadCommandResource,
    qemu_mciSendCommandA,
    qemu_mciSendCommandW,
    qemu_mciSendStringA,
    qemu_mciSendStringW,
    qemu_mciSetDriverData,
    qemu_mciSetYieldProc,
    qemu_midiConnect,
    qemu_midiDisconnect,
    qemu_midiInAddBuffer,
    qemu_midiInClose,
    qemu_midiInGetDevCapsA,
    qemu_midiInGetDevCapsW,
    qemu_midiInGetID,
    qemu_midiInGetNumDevs,
    qemu_midiInMessage,
    qemu_midiInOpen,
    qemu_midiInPrepareHeader,
    qemu_midiInReset,
    qemu_midiInStart,
    qemu_midiInStop,
    qemu_midiInUnprepareHeader,
    qemu_midiOutCacheDrumPatches,
    qemu_midiOutCachePatches,
    qemu_midiOutClose,
    qemu_midiOutGetDevCapsA,
    qemu_midiOutGetDevCapsW,
    qemu_midiOutGetErrorTextA,
    qemu_midiOutGetErrorTextW,
    qemu_midiOutGetID,
    qemu_midiOutGetNumDevs,
    qemu_midiOutGetVolume,
    qemu_midiOutLongMsg,
    qemu_midiOutMessage,
    qemu_midiOutOpen,
    qemu_midiOutPrepareHeader,
    qemu_midiOutReset,
    qemu_midiOutSetVolume,
    qemu_midiOutShortMsg,
    qemu_midiOutUnprepareHeader,
    qemu_midiStreamClose,
    qemu_midiStreamOpen,
    qemu_midiStreamOut,
    qemu_midiStreamPause,
    qemu_midiStreamPosition,
    qemu_midiStreamProperty,
    qemu_midiStreamRestart,
    qemu_midiStreamStop,
    qemu_mixerClose,
    qemu_mixerGetControlDetails,
    qemu_mixerGetControlDetails,
    qemu_mixerGetDevCapsA,
    qemu_mixerGetDevCapsW,
    qemu_mixerGetID,
    qemu_mixerGetLineControls,
    qemu_mixerGetLineControls,
    qemu_mixerGetLineInfoA,
    qemu_mixerGetLineInfoW,
    qemu_mixerGetNumDevs,
    qemu_mixerMessage,
    qemu_mixerOpen,
    qemu_mixerSetControlDetails,
    qemu_mmGetCurrentTask,
    qemu_mmioAdvance,
    qemu_mmioAscend,
    qemu_mmioClose,
    qemu_mmioCreateChunk,
    qemu_mmioDescend,
    qemu_mmioFlush,
    qemu_mmioGetInfo,
    qemu_mmioInstallIOProcA,
    qemu_mmioInstallIOProcW,
    qemu_mmioOpen,
    qemu_mmioOpen,
    qemu_mmioRead,
    qemu_mmioRenameA,
    qemu_mmioRenameW,
    qemu_mmioSeek,
    qemu_mmioSendMessage,
    qemu_mmioSetBuffer,
    qemu_mmioSetInfo,
    qemu_mmioStringToFOURCCA,
    qemu_mmioStringToFOURCCW,
    qemu_mmioWrite,
    qemu_mmsystemGetVersion,
    qemu_mmTaskBlock,
    qemu_mmTaskCreate,
    qemu_mmTaskSignal,
    qemu_mmTaskYield,
    qemu_OpenDriver,
    qemu_OpenDriverA,
    qemu_PlaySoundA,
    qemu_PlaySoundW,
    qemu_SendDriverMessage,
    qemu_sndPlaySoundA,
    qemu_sndPlaySoundW,
    qemu_timeBeginPeriod,
    qemu_timeEndPeriod,
    qemu_timeGetDevCaps,
    qemu_timeGetSystemTime,
    qemu_timeKillEvent,
    qemu_timeSetEvent,
    qemu_waveInAddBuffer,
    qemu_waveInClose,
    qemu_waveInGetDevCapsA,
    qemu_waveInGetDevCapsW,
    qemu_waveInGetID,
    qemu_waveInGetNumDevs,
    qemu_waveInGetPosition,
    qemu_waveInMessage,
    qemu_waveInOpen,
    qemu_waveHeaderOp,
    qemu_waveInReset,
    qemu_waveInStart,
    qemu_waveInStop,
    qemu_waveHeaderOp,
    qemu_waveOutBreakLoop,
    qemu_waveOutClose,
    qemu_waveOutGetDevCapsA,
    qemu_waveOutGetDevCapsW,
    qemu_waveOutGetErrorTextA,
    qemu_waveOutGetErrorTextW,
    qemu_waveOutGetID,
    qemu_waveOutGetNumDevs,
    qemu_waveOutGetPitch,
    qemu_waveOutGetPlaybackRate,
    qemu_waveOutGetPosition,
    qemu_waveOutGetVolume,
    qemu_waveOutMessage,
    qemu_waveOutOpen,
    qemu_waveOutPause,
    qemu_waveHeaderOp,
    qemu_waveOutReset,
    qemu_waveOutRestart,
    qemu_waveOutSetPitch,
    qemu_waveOutSetPlaybackRate,
    qemu_waveOutSetVolume,
    qemu_waveHeaderOp,
    qemu_waveHeaderOp,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side winmm wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
