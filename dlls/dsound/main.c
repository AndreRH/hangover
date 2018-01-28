/*
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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>
#include <dsound.h>
#include <dsconf.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_dsound.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_dsound);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_DirectSoundCaptureCreate,
    qemu_DirectSoundCaptureCreate8,
    qemu_DirectSoundCaptureEnumerateA,
    qemu_DirectSoundCaptureEnumerateW,
    qemu_DirectSoundCreate,
    qemu_DirectSoundEnumerate,
    qemu_DirectSoundEnumerate,
    qemu_DirectSoundFullDuplexCreate,
    qemu_DllCanUnloadNow,
    qemu_DllRegisterServer,
    qemu_DllUnregisterServer,
    qemu_GetDeviceID,
    qemu_IDirectSound3DBufferImpl_GetAllParameters,
    qemu_IDirectSound3DBufferImpl_GetConeAngles,
    qemu_IDirectSound3DBufferImpl_GetConeOrientation,
    qemu_IDirectSound3DBufferImpl_GetConeOutsideVolume,
    qemu_IDirectSound3DBufferImpl_GetMaxDistance,
    qemu_IDirectSound3DBufferImpl_GetMinDistance,
    qemu_IDirectSound3DBufferImpl_GetMode,
    qemu_IDirectSound3DBufferImpl_GetPosition,
    qemu_IDirectSound3DBufferImpl_GetVelocity,
    qemu_IDirectSound3DBufferImpl_SetAllParameters,
    qemu_IDirectSound3DBufferImpl_SetConeAngles,
    qemu_IDirectSound3DBufferImpl_SetConeOrientation,
    qemu_IDirectSound3DBufferImpl_SetConeOutsideVolume,
    qemu_IDirectSound3DBufferImpl_SetMaxDistance,
    qemu_IDirectSound3DBufferImpl_SetMinDistance,
    qemu_IDirectSound3DBufferImpl_SetMode,
    qemu_IDirectSound3DBufferImpl_SetPosition,
    qemu_IDirectSound3DBufferImpl_SetVelocity,
    qemu_IDirectSound3DListenerImpl_CommitDeferredSettings,
    qemu_IDirectSound3DListenerImpl_GetAllParameter,
    qemu_IDirectSound3DListenerImpl_GetDistanceFactor,
    qemu_IDirectSound3DListenerImpl_GetDopplerFactor,
    qemu_IDirectSound3DListenerImpl_GetOrientation,
    qemu_IDirectSound3DListenerImpl_GetPosition,
    qemu_IDirectSound3DListenerImpl_GetRolloffFactor,
    qemu_IDirectSound3DListenerImpl_GetVelocity,
    qemu_IDirectSound3DListenerImpl_SetAllParameters,
    qemu_IDirectSound3DListenerImpl_SetDistanceFactor,
    qemu_IDirectSound3DListenerImpl_SetDopplerFactor,
    qemu_IDirectSound3DListenerImpl_SetOrientation,
    qemu_IDirectSound3DListenerImpl_SetPosition,
    qemu_IDirectSound3DListenerImpl_SetRolloffFactor,
    qemu_IDirectSound3DListenerImpl_SetVelocity,
    qemu_IDirectSound8Impl_Compact,
    qemu_IDirectSound8Impl_CreateSoundBuffer,
    qemu_IDirectSound8Impl_DuplicateSoundBuffer,
    qemu_IDirectSound8Impl_GetCaps,
    qemu_IDirectSound8Impl_GetSpeakerConfig,
    qemu_IDirectSound8Impl_Initialize,
    qemu_IDirectSound8Impl_Release,
    qemu_IDirectSound8Impl_SetCooperativeLevel,
    qemu_IDirectSound8Impl_SetSpeakerConfig,
    qemu_IDirectSound8Impl_VerifyCertification,
    qemu_IDirectSoundBufferImpl_AcquireResources,
    qemu_IDirectSoundBufferImpl_GetCaps,
    qemu_IDirectSoundBufferImpl_GetCurrentPosition,
    qemu_IDirectSoundBufferImpl_GetFormat,
    qemu_IDirectSoundBufferImpl_GetFrequency,
    qemu_IDirectSoundBufferImpl_GetObjectInPath,
    qemu_IDirectSoundBufferImpl_GetPan,
    qemu_IDirectSoundBufferImpl_GetStatus,
    qemu_IDirectSoundBufferImpl_GetVolume,
    qemu_IDirectSoundBufferImpl_Initialize,
    qemu_IDirectSoundBufferImpl_Lock,
    qemu_IDirectSoundBufferImpl_Play,
    qemu_IDirectSoundBufferImpl_Release,
    qemu_IDirectSoundBufferImpl_Restore,
    qemu_IDirectSoundBufferImpl_SetCurrentPosition,
    qemu_IDirectSoundBufferImpl_SetFormat,
    qemu_IDirectSoundBufferImpl_SetFrequency,
    qemu_IDirectSoundBufferImpl_SetFX,
    qemu_IDirectSoundBufferImpl_SetPan,
    qemu_IDirectSoundBufferImpl_SetVolume,
    qemu_IDirectSoundBufferImpl_Stop,
    qemu_IDirectSoundBufferImpl_Unlock,
    qemu_IDirectSoundNotifyImpl_SetNotificationPositions,
    qemu_IKsPrivatePropertySetImpl_Create,
    qemu_IKsPrivatePropertySetImpl_Get,
    qemu_IKsPrivatePropertySetImpl_QuerySupport,
    qemu_IKsPrivatePropertySetImpl_Release,
    qemu_IKsPrivatePropertySetImpl_Set,
    qemu_IKsPropertySetImpl_Get,
    qemu_IKsPropertySetImpl_QuerySupport,
    qemu_IKsPropertySetImpl_Set,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side dsound wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
