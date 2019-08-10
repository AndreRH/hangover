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

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_winmm.h"

struct qemu_dll_init
{
    struct qemu_syscall super;
    uint64_t ioproc_guest_wrapper;
};

struct ioproc_callback
{
    uint64_t func;
    uint64_t info;
    uint64_t msg;
    uint64_t param1, param2;
};

#ifdef QEMU_DLL_GUEST

static LRESULT __fastcall ioproc_guest_wrapper(struct ioproc_callback *data)
{
    LPMMIOPROC func = (LPMMIOPROC)(ULONG_PTR)data->func;
    return func((char *)(ULONG_PTR)data->info, data->msg, data->param1, data->param2);
}

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_dll_init call;

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            call.super.id = QEMU_SYSCALL_ID(CALL_DLL_INIT);
            call.ioproc_guest_wrapper = (ULONG_PTR)ioproc_guest_wrapper;
            qemu_syscall(&call.super);
            break;
    }
    return TRUE;
}

#else

#include <wine/debug.h>
#include <assert.h>

#include "callback_helper_impl.h"

WINE_DEFAULT_DEBUG_CHANNEL(qemu_winmm);

const struct qemu_ops *qemu_ops;

static uint64_t ioproc_guest_wrapper;

static void qemu_dll_init(struct qemu_syscall *call)
{
    struct qemu_dll_init *c = (struct qemu_dll_init *)call;
    ioproc_guest_wrapper = c->ioproc_guest_wrapper;
}

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
    qemu_dll_init,
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
    qemu_mciSendCommand,
    qemu_mciSendCommand,
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

struct callback_entry_table *ioproc_wrappers;
unsigned int ioproc_wrapper_count;

LRESULT WINAPI ioproc_wrapper(LPSTR info, UINT msg, LPARAM param1, LPARAM param2, struct callback_entry *wrapper)
{
    struct ioproc_callback call;
    LRESULT ret;
    struct qemu_MMIOINFO info32;

    call.func = callback_get_guest_proc(wrapper);
#if GUEST_BIT == HOST_BIT
    call.info = QEMU_H2G(info);
#else
    MMIOINFO_h2g(&info32, (MMIOINFO *)info);
    call.info = QEMU_H2G(&info32);
#endif
    call.msg = msg;
    call.param1 = param1;
    call.param2 = param2;

    WINE_TRACE("Calling guest function %p(%p, 0x%x, 0x%lx, 0x%lx).\n", (void *)call.func,
               (void *)call.info, msg, param1, param2);
    qemu_ops->qemu_execute(QEMU_G2H(ioproc_guest_wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned %ld\n", ret);

#if GUEST_BIT != HOST_BIT
    MMIOINFO_g2h((MMIOINFO *)info, &info32);
#endif

    return ret;
}

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side winmm wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    ioproc_wrapper_count = 128;
    if (!callback_alloc_table(&ioproc_wrappers, ioproc_wrapper_count, sizeof(struct callback_entry),
            ioproc_wrapper, 4))
    {
        WINE_ERR("Failed to allocate memory for class ioproc wrappers.\n");
        return NULL;
    }

    return dll_functions;
}

LPMMIOPROC ioproc_guest_to_host(uint64_t guest_proc)
{
    unsigned int i;
    struct callback_entry *entry;
    BOOL is_new;

    if (!guest_proc)
        return (LPMMIOPROC)guest_proc;

    entry = callback_get(ioproc_wrappers, guest_proc, &is_new);
    if (!entry)
    {
        WINE_FIXME("Out of guest -> host IOPROC wrappers.\n");
        assert(0);
    }
    if (is_new)
    {
        WINE_TRACE("Creating host IOPROC %p for guest func 0x%lx.\n",
                entry, (unsigned long)guest_proc);
    }
    return (LPMMIOPROC)entry;
}

uint64_t ioproc_host_to_guest(LPMMIOPROC host_proc)
{
    unsigned int i;

    if (!host_proc)
        return (ULONG_PTR)host_proc;

    if (callback_is_in_table(ioproc_wrappers, (struct callback_entry *)host_proc))
    {
        uint64_t ret = callback_get_guest_proc((struct callback_entry *)host_proc);
        WINE_TRACE("Host wndproc %p is a wrapper function. Returning guest wndproc 0x%lx.\n",
                host_proc, (unsigned long)ret);
        return ret;
    }

    WINE_ERR("Did not expect a host-provided IO proc.\n");

    /* Out of reverse wrappers. */
    assert(0);
}

#endif
