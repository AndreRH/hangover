/*
 * Copyright 2017 André Hentschel
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

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
#include <wine/list.h>
#include <mmddk.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_winmm);
#endif


struct qemu_waveOutGetNumDevs
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutGetNumDevs(void)
{
    struct qemu_waveOutGetNumDevs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTGETNUMDEVS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutGetNumDevs(struct qemu_syscall *call)
{
    struct qemu_waveOutGetNumDevs *c = (struct qemu_waveOutGetNumDevs *)call;
    WINE_TRACE("\n");
    c->super.iret = waveOutGetNumDevs();
}

#endif

struct qemu_waveOutGetDevCapsA
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpCaps;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutGetDevCapsA(UINT_PTR uDeviceID, LPWAVEOUTCAPSA lpCaps, UINT uSize)
{
    struct qemu_waveOutGetDevCapsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTGETDEVCAPSA);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpCaps = (ULONG_PTR)lpCaps;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutGetDevCapsA(struct qemu_syscall *call)
{
    struct qemu_waveOutGetDevCapsA *c = (struct qemu_waveOutGetDevCapsA *)call;
    WINE_TRACE("\n");

    /* WAVEOUTCAPSA has the same size on 32 and 64 bit. */
    c->super.iret = waveOutGetDevCapsA(c->uDeviceID, QEMU_G2H(c->lpCaps), c->uSize);
}

#endif

struct qemu_waveOutGetDevCapsW
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpCaps;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutGetDevCapsW(UINT_PTR uDeviceID, LPWAVEOUTCAPSW lpCaps, UINT uSize)
{
    struct qemu_waveOutGetDevCapsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTGETDEVCAPSW);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpCaps = (ULONG_PTR)lpCaps;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutGetDevCapsW(struct qemu_syscall *call)
{
    struct qemu_waveOutGetDevCapsW *c = (struct qemu_waveOutGetDevCapsW *)call;
    WINE_TRACE("\n");

    /* WAVEOUTCAPSW has the same size on 32 and 64 bit. */
    c->super.iret = waveOutGetDevCapsW(c->uDeviceID, QEMU_G2H(c->lpCaps), c->uSize);
}

#endif

struct qemu_waveOutGetErrorTextA
{
    struct qemu_syscall super;
    uint64_t uError;
    uint64_t lpText;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutGetErrorTextA(UINT uError, LPSTR lpText, UINT uSize)
{
    struct qemu_waveOutGetErrorTextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTGETERRORTEXTA);
    call.uError = (ULONG_PTR)uError;
    call.lpText = (ULONG_PTR)lpText;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutGetErrorTextA(struct qemu_syscall *call)
{
    struct qemu_waveOutGetErrorTextA *c = (struct qemu_waveOutGetErrorTextA *)call;
    WINE_TRACE("\n");
    c->super.iret = waveOutGetErrorTextA(c->uError, QEMU_G2H(c->lpText), c->uSize);
}

#endif

struct qemu_waveOutGetErrorTextW
{
    struct qemu_syscall super;
    uint64_t uError;
    uint64_t lpText;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutGetErrorTextW(UINT uError, LPWSTR lpText, UINT uSize)
{
    struct qemu_waveOutGetErrorTextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTGETERRORTEXTW);
    call.uError = (ULONG_PTR)uError;
    call.lpText = (ULONG_PTR)lpText;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutGetErrorTextW(struct qemu_syscall *call)
{
    struct qemu_waveOutGetErrorTextW *c = (struct qemu_waveOutGetErrorTextW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = waveOutGetErrorTextW(c->uError, QEMU_G2H(c->lpText), c->uSize);
}

#endif

struct qemu_waveOutOpen
{
    struct qemu_syscall super;
    uint64_t lphWaveOut;
    uint64_t uDeviceID;
    uint64_t lpFormat;
    uint64_t dwCallback;
    uint64_t dwInstance;
    uint64_t dwFlags;
    uint64_t wrapper;
};

struct wave_guest_cb_data
{
    uint64_t func;
    uint64_t wave;
    uint64_t msg;
    uint64_t user;
    uint64_t param1, param2;
};

#ifdef QEMU_DLL_GUEST

static void __fastcall wave_guest_cb(struct wave_guest_cb_data *data)
{
    LPWAVECALLBACK func = (LPWAVECALLBACK)(ULONG_PTR)data->func;
    func((void *)(ULONG_PTR)data->wave, data->msg, data->user, data->param1, data->param2);
}

WINBASEAPI MMRESULT WINAPI waveOutOpen(LPHWAVEOUT lphWaveOut, UINT uDeviceID, LPCWAVEFORMATEX lpFormat,
        DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD dwFlags)
{
    struct qemu_waveOutOpen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTOPEN);
    call.lphWaveOut = (ULONG_PTR)lphWaveOut;
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpFormat = (ULONG_PTR)lpFormat;
    call.dwCallback = (ULONG_PTR)dwCallback;
    call.dwInstance = (ULONG_PTR)dwInstance;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.wrapper = (ULONG_PTR)wave_guest_cb;

    qemu_syscall(&call.super);
    if (call.super.iret == MMSYSERR_NOERROR && !(dwFlags & WAVE_FORMAT_QUERY))
        *lphWaveOut = (HWAVEOUT)(ULONG_PTR)call.lphWaveOut;

    return call.super.iret;
}

#else

struct qemu_wave_host
{
    HWAVEOUT wave;
    uint64_t guest_cb, guest_instance, wrapper;
    DWORD guest_flags;
    struct list entry;
};

static CRITICAL_SECTION wave_out_list_cs = {0, -1, 0, 0, 0, 0};
static struct list wave_out_list = LIST_INIT(wave_out_list);

struct extended_WAVEHDR
{
    WAVEHDR super;
    struct qemu_WAVEHDR *hdr32;
};

static void CALLBACK qemu_wave_host_cb(HWAVEOUT wave, UINT msg,
        DWORD_PTR user, DWORD_PTR param1, DWORD_PTR param2)
{
    struct qemu_wave_host *wrapper = (struct qemu_wave_host *)user;
    struct extended_WAVEHDR *hdr;
    HANDLE event;
    struct wave_guest_cb_data call;

#if HOST_BIT != GUEST_BIT
    switch (msg)
    {
        case WOM_DONE:
            hdr = (struct extended_WAVEHDR *)param1;
            WAVEHDR_h2g(hdr->hdr32, &hdr->super);
            param1 = (DWORD_PTR)hdr->hdr32;
            HeapFree(GetProcessHeap(), 0, hdr);
            break;
    }
#endif

    switch (wrapper->guest_flags & CALLBACK_TYPEMASK)
    {
        case CALLBACK_NULL:
            break;

        case CALLBACK_WINDOW:
            WINE_FIXME("Unimplemented callback type CALLBACK_WINDOW.\n");
            break;

        case CALLBACK_TASK: /* == CALLBACK_THREAD. */
            WINE_TRACE("Posting a message to thread %lx.\n", wrapper->guest_cb);
            PostThreadMessageA(wrapper->guest_cb, msg, (WPARAM)wave, param1);
            break;

        case CALLBACK_FUNCTION:
            call.func = wrapper->guest_cb;
            call.wave = QEMU_H2G(wave);
            call.msg = msg;
            call.user = wrapper->guest_instance;
            call.param1 = param1;
            call.param2 = param2;

            WINE_TRACE("Calling guest callback 0x%lx.\n", call.func);
            qemu_ops->qemu_execute(QEMU_G2H(wrapper->wrapper), QEMU_H2G(&call));
            WINE_TRACE("Guest callback returned.\n");

            break;

        case CALLBACK_EVENT:
            event = (HANDLE)wrapper->guest_cb;
            WINE_TRACE("Setting event %p.\n", event);
            SetEvent(event);
            break;
    }
}

void qemu_waveOutOpen(struct qemu_syscall *call)
{
    struct qemu_waveOutOpen *c = (struct qemu_waveOutOpen *)call;
    HWAVEOUT handle;
    struct qemu_wave_host *wrapper;
    DWORD flags;
    WINE_TRACE("\n");

    if (c->dwFlags & WAVE_FORMAT_QUERY)
    {
        c->super.iret = waveOutOpen(c->lphWaveOut ? &handle : NULL, c->uDeviceID, QEMU_G2H(c->lpFormat),
                c->dwCallback, c->dwInstance, c->dwFlags);
        return;
    }

    wrapper = HeapAlloc(GetProcessHeap(), 0, sizeof(*wrapper));
    if (!wrapper)
    {
        WINE_WARN("Out of memory\n");
        c->super.iret = MMSYSERR_ERROR;
        return;
    }

    wrapper->guest_cb = c->dwCallback;
    wrapper->guest_instance = c->dwInstance;
    wrapper->guest_flags = c->dwFlags;
    wrapper->wrapper = c->wrapper;

    flags = c->dwFlags;
    flags &= ~CALLBACK_TYPEMASK;
    flags |= CALLBACK_FUNCTION;

    c->super.iret = waveOutOpen(c->lphWaveOut ? &handle : NULL, c->uDeviceID, QEMU_G2H(c->lpFormat),
            (DWORD_PTR)qemu_wave_host_cb, (ULONG_PTR)wrapper, flags);

    if (c->super.iret == MMSYSERR_NOERROR)
    {
        c->lphWaveOut = QEMU_H2G(handle);
        wrapper->wave = handle;
        EnterCriticalSection(&wave_out_list_cs);
        list_add_head(&wave_out_list, &wrapper->entry);
        LeaveCriticalSection(&wave_out_list_cs);
    }
    else
    {
        HeapFree(GetProcessHeap(), 0, wrapper);
    }
}

#endif

struct qemu_waveOutClose
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutClose(HWAVEOUT hWaveOut)
{
    struct qemu_waveOutClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTCLOSE);
    call.hWaveOut = (ULONG_PTR)hWaveOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutClose(struct qemu_syscall *call)
{
    struct qemu_waveOutClose *c = (struct qemu_waveOutClose *)call;
    struct qemu_wave_host *wrapper;
    HWAVEOUT wave;

    WINE_TRACE("\n");
    wave = QEMU_G2H(c->hWaveOut);

    EnterCriticalSection(&wave_out_list_cs);
    c->super.iret = waveOutClose(wave);

    if (c->super.iret != MMSYSERR_NOERROR)
        goto done;

    LIST_FOR_EACH_ENTRY(wrapper, &wave_out_list, struct qemu_wave_host, entry)
    {
        if (wrapper->wave == wave)
        {
            WINE_TRACE("Deleting wrapper struct of HWAVEOUT handle %p.\n", wrapper, wave);
            list_remove(&wrapper->entry);
            HeapFree(GetProcessHeap(), 0, wrapper);
            goto done;
        }
    }
    WINE_ERR("Could not find wrapper structure for successfully closed HWAVEOUT %p.\n", wave);

done:
    LeaveCriticalSection(&wave_out_list_cs);
}

#endif

struct qemu_waveHeaderOp
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t header;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutPrepareHeader(HWAVEOUT hWaveOut, WAVEHDR* lpWaveOutHdr, UINT uSize)
{
    struct qemu_waveHeaderOp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTPREPAREHEADER);
    call.handle = (ULONG_PTR)hWaveOut;
    call.header = (ULONG_PTR)lpWaveOutHdr;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI UINT WINAPI waveInPrepareHeader(HWAVEIN hWaveIn, WAVEHDR* lpWaveInHdr, UINT uSize)
{
    struct qemu_waveHeaderOp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINPREPAREHEADER);
    call.handle = (ULONG_PTR)hWaveIn;
    call.header = (ULONG_PTR)lpWaveInHdr;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI UINT WINAPI waveInUnprepareHeader(HWAVEIN hWaveIn, WAVEHDR* lpWaveInHdr, UINT uSize)
{
    struct qemu_waveHeaderOp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINUNPREPAREHEADER);
    call.handle = (ULONG_PTR)hWaveIn;
    call.header = (ULONG_PTR)lpWaveInHdr;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI UINT WINAPI waveOutWrite(HWAVEOUT hWaveOut, WAVEHDR *header, UINT uSize)
{
    struct qemu_waveHeaderOp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTWRITE);
    call.handle = (ULONG_PTR)hWaveOut;
    call.header = (ULONG_PTR)header;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI UINT WINAPI waveOutUnprepareHeader(HWAVEOUT hWaveOut, LPWAVEHDR lpWaveOutHdr, UINT uSize)
{
    struct qemu_waveHeaderOp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTUNPREPAREHEADER);
    call.handle = (ULONG_PTR)hWaveOut;
    call.header = (ULONG_PTR)lpWaveOutHdr;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveHeaderOp(struct qemu_syscall *call)
{
    struct qemu_waveHeaderOp *c = (struct qemu_waveHeaderOp *)call;
    WAVEHDR stack, *hdr = &stack;
    struct qemu_WAVEHDR *hdr32;
    UINT size;
    WINE_TRACE("\n");

    size = c->uSize;
#if GUEST_BIT == HOST_BIT
    hdr = QEMU_G2H(c->header);
#else
    hdr32 = QEMU_G2H(c->header);
    if (!hdr32)
        hdr = NULL;
    else if (size < sizeof(*hdr32))
        size = 0;
    else if (c->super.id == QEMU_SYSCALL_ID(CALL_WAVEOUTWRITE))
    {
        struct extended_WAVEHDR *hdrex = HeapAlloc(GetProcessHeap(), 0, sizeof(*hdrex));
        hdr = &hdrex->super;
        WAVEHDR_g2h(hdr, hdr32);
        size = sizeof(*hdr);
        hdrex->hdr32 = hdr32;
    }
    else
    {
        WAVEHDR_g2h(hdr, hdr32);
        size = sizeof(*hdr);
    }
#endif

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_WAVEOUTPREPAREHEADER):
            WINE_TRACE("waveOutPrepareHeader\n");
            c->super.iret = waveOutPrepareHeader(QEMU_G2H(c->handle), hdr, size);
            break;

        case QEMU_SYSCALL_ID(CALL_WAVEOUTUNPREPAREHEADER):
            WINE_TRACE("waveOutUnprepareHeader\n");
            c->super.iret = waveOutUnprepareHeader(QEMU_G2H(c->handle), hdr, size);
            break;

        case QEMU_SYSCALL_ID(CALL_WAVEINPREPAREHEADER):
            WINE_TRACE("waveInPrepareHeader\n");
            c->super.iret = waveInPrepareHeader(QEMU_G2H(c->handle), hdr, size);
            break;

        case QEMU_SYSCALL_ID(CALL_WAVEINUNPREPAREHEADER):
            WINE_TRACE("waveInUnprepareHeader\n");
            c->super.iret = waveInUnprepareHeader(QEMU_G2H(c->handle), hdr, size);
            break;

        case QEMU_SYSCALL_ID(CALL_WAVEOUTWRITE):
            WINE_TRACE("waveOutWrite\n");
            c->super.iret = waveOutWrite(QEMU_G2H(c->handle), hdr, size);
            break;
   }

#if GUEST_BIT != HOST_BIT
    if (c->super.iret == MMSYSERR_NOERROR)
        WAVEHDR_h2g(hdr32, hdr);
#endif
}

#endif

struct qemu_waveOutBreakLoop
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutBreakLoop(HWAVEOUT hWaveOut)
{
    struct qemu_waveOutBreakLoop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTBREAKLOOP);
    call.hWaveOut = (ULONG_PTR)hWaveOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutBreakLoop(struct qemu_syscall *call)
{
    struct qemu_waveOutBreakLoop *c = (struct qemu_waveOutBreakLoop *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = waveOutBreakLoop(QEMU_G2H(c->hWaveOut));
}

#endif

struct qemu_waveOutPause
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutPause(HWAVEOUT hWaveOut)
{
    struct qemu_waveOutPause call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTPAUSE);
    call.hWaveOut = (ULONG_PTR)hWaveOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutPause(struct qemu_syscall *call)
{
    struct qemu_waveOutPause *c = (struct qemu_waveOutPause *)call;
    WINE_TRACE("\n");
    c->super.iret = waveOutPause(QEMU_G2H(c->hWaveOut));
}

#endif

struct qemu_waveOutReset
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutReset(HWAVEOUT hWaveOut)
{
    struct qemu_waveOutReset call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTRESET);
    call.hWaveOut = (ULONG_PTR)hWaveOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutReset(struct qemu_syscall *call)
{
    struct qemu_waveOutReset *c = (struct qemu_waveOutReset *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = waveOutReset(QEMU_G2H(c->hWaveOut));
}

#endif

struct qemu_waveOutRestart
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutRestart(HWAVEOUT hWaveOut)
{
    struct qemu_waveOutRestart call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTRESTART);
    call.hWaveOut = (ULONG_PTR)hWaveOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutRestart(struct qemu_syscall *call)
{
    struct qemu_waveOutRestart *c = (struct qemu_waveOutRestart *)call;
    WINE_TRACE("\n");
    c->super.iret = waveOutRestart(QEMU_G2H(c->hWaveOut));
}

#endif

struct qemu_waveOutGetPosition
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
    uint64_t lpTime;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutGetPosition(HWAVEOUT hWaveOut, LPMMTIME lpTime, UINT uSize)
{
    struct qemu_waveOutGetPosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTGETPOSITION);
    call.hWaveOut = (ULONG_PTR)hWaveOut;
    call.lpTime = (ULONG_PTR)lpTime;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutGetPosition(struct qemu_syscall *call)
{
    struct qemu_waveOutGetPosition *c = (struct qemu_waveOutGetPosition *)call;
    WINE_TRACE("\n");

    /* MMTIME has the same size on 32 and 64 bit. */
    c->super.iret = waveOutGetPosition(QEMU_G2H(c->hWaveOut), QEMU_G2H(c->lpTime), c->uSize);
}

#endif

struct qemu_waveOutGetPitch
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
    uint64_t lpdw;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutGetPitch(HWAVEOUT hWaveOut, LPDWORD lpdw)
{
    struct qemu_waveOutGetPitch call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTGETPITCH);
    call.hWaveOut = (ULONG_PTR)hWaveOut;
    call.lpdw = (ULONG_PTR)lpdw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutGetPitch(struct qemu_syscall *call)
{
    struct qemu_waveOutGetPitch *c = (struct qemu_waveOutGetPitch *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = waveOutGetPitch(QEMU_G2H(c->hWaveOut), QEMU_G2H(c->lpdw));
}

#endif

struct qemu_waveOutSetPitch
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
    uint64_t dw;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutSetPitch(HWAVEOUT hWaveOut, DWORD dw)
{
    struct qemu_waveOutSetPitch call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTSETPITCH);
    call.hWaveOut = (ULONG_PTR)hWaveOut;
    call.dw = (ULONG_PTR)dw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutSetPitch(struct qemu_syscall *call)
{
    struct qemu_waveOutSetPitch *c = (struct qemu_waveOutSetPitch *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = waveOutSetPitch(QEMU_G2H(c->hWaveOut), c->dw);
}

#endif

struct qemu_waveOutGetPlaybackRate
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
    uint64_t lpdw;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutGetPlaybackRate(HWAVEOUT hWaveOut, LPDWORD lpdw)
{
    struct qemu_waveOutGetPlaybackRate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTGETPLAYBACKRATE);
    call.hWaveOut = (ULONG_PTR)hWaveOut;
    call.lpdw = (ULONG_PTR)lpdw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutGetPlaybackRate(struct qemu_syscall *call)
{
    struct qemu_waveOutGetPlaybackRate *c = (struct qemu_waveOutGetPlaybackRate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = waveOutGetPlaybackRate(QEMU_G2H(c->hWaveOut), QEMU_G2H(c->lpdw));
}

#endif

struct qemu_waveOutSetPlaybackRate
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
    uint64_t dw;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutSetPlaybackRate(HWAVEOUT hWaveOut, DWORD dw)
{
    struct qemu_waveOutSetPlaybackRate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTSETPLAYBACKRATE);
    call.hWaveOut = (ULONG_PTR)hWaveOut;
    call.dw = (ULONG_PTR)dw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutSetPlaybackRate(struct qemu_syscall *call)
{
    struct qemu_waveOutSetPlaybackRate *c = (struct qemu_waveOutSetPlaybackRate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = waveOutSetPlaybackRate(QEMU_G2H(c->hWaveOut), c->dw);
}

#endif

struct qemu_waveOutGetVolume
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutGetVolume(HWAVEOUT hWaveOut, DWORD *out)
{
    struct qemu_waveOutGetVolume call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTGETVOLUME);
    call.hWaveOut = (ULONG_PTR)hWaveOut;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutGetVolume(struct qemu_syscall *call)
{
    struct qemu_waveOutGetVolume *c = (struct qemu_waveOutGetVolume *)call;
    WINE_TRACE("\n");
    c->super.iret = waveOutGetVolume(QEMU_G2H(c->hWaveOut), QEMU_G2H(c->out));
}

#endif

struct qemu_waveOutSetVolume
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
    uint64_t in;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutSetVolume(HWAVEOUT hWaveOut, DWORD in)
{
    struct qemu_waveOutSetVolume call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTSETVOLUME);
    call.hWaveOut = (ULONG_PTR)hWaveOut;
    call.in = (ULONG_PTR)in;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutSetVolume(struct qemu_syscall *call)
{
    struct qemu_waveOutSetVolume *c = (struct qemu_waveOutSetVolume *)call;
    WINE_TRACE("\n");
    c->super.iret = waveOutSetVolume(QEMU_G2H(c->hWaveOut), c->in);
}

#endif

struct qemu_waveOutGetID
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
    uint64_t lpuDeviceID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutGetID(HWAVEOUT hWaveOut, UINT* lpuDeviceID)
{
    struct qemu_waveOutGetID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTGETID);
    call.hWaveOut = (ULONG_PTR)hWaveOut;
    call.lpuDeviceID = (ULONG_PTR)lpuDeviceID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutGetID(struct qemu_syscall *call)
{
    struct qemu_waveOutGetID *c = (struct qemu_waveOutGetID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = waveOutGetID(QEMU_G2H(c->hWaveOut), QEMU_G2H(c->lpuDeviceID));
}

#endif

struct qemu_waveOutMessage
{
    struct qemu_syscall super;
    uint64_t hWaveOut;
    uint64_t uMessage;
    uint64_t dwParam1;
    uint64_t dwParam2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveOutMessage(HWAVEOUT hWaveOut, UINT uMessage, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    struct qemu_waveOutMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEOUTMESSAGE);
    call.hWaveOut = (ULONG_PTR)hWaveOut;
    call.uMessage = (ULONG_PTR)uMessage;
    call.dwParam1 = (ULONG_PTR)dwParam1;
    call.dwParam2 = (ULONG_PTR)dwParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveOutMessage(struct qemu_syscall *call)
{
    struct qemu_waveOutMessage *c = (struct qemu_waveOutMessage *)call;
    WINE_TRACE("\n");

#if GUEST_BIT != HOST_BIT
    /* There's a DWORD_PTR * in dwParam1. */
    if (c->uMessage == DRV_QUERYFUNCTIONINSTANCEIDSIZE)
        WINE_FIXME("DRV_QUERYFUNCTIONINSTANCEIDSIZE may need 32/64 bit conversion.\n");
#endif

    c->super.iret = waveOutMessage(QEMU_G2H(c->hWaveOut), c->uMessage, c->dwParam1, c->dwParam2);
}

#endif

struct qemu_waveInGetNumDevs
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveInGetNumDevs(void)
{
    struct qemu_waveInGetNumDevs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINGETNUMDEVS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveInGetNumDevs(struct qemu_syscall *call)
{
    struct qemu_waveInGetNumDevs *c = (struct qemu_waveInGetNumDevs *)call;
    WINE_TRACE("\n");
    c->super.iret = waveInGetNumDevs();
}

#endif

struct qemu_waveInGetDevCapsW
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpCaps;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveInGetDevCapsW(UINT_PTR uDeviceID, LPWAVEINCAPSW lpCaps, UINT uSize)
{
    struct qemu_waveInGetDevCapsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINGETDEVCAPSW);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpCaps = (ULONG_PTR)lpCaps;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveInGetDevCapsW(struct qemu_syscall *call)
{
    struct qemu_waveInGetDevCapsW *c = (struct qemu_waveInGetDevCapsW *)call;
    WINE_TRACE("\n");

    /* WAVEINCAPSW has the same size on 32 and 64 bit. */
    c->super.iret = waveInGetDevCapsW(c->uDeviceID, QEMU_G2H(c->lpCaps), c->uSize);
}

#endif

struct qemu_waveInGetDevCapsA
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpCaps;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveInGetDevCapsA(UINT_PTR uDeviceID, LPWAVEINCAPSA lpCaps, UINT uSize)
{
    struct qemu_waveInGetDevCapsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINGETDEVCAPSA);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpCaps = (ULONG_PTR)lpCaps;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveInGetDevCapsA(struct qemu_syscall *call)
{
    struct qemu_waveInGetDevCapsA *c = (struct qemu_waveInGetDevCapsA *)call;
    WINE_TRACE("\n");

    /* WAVEINCAPSA has the same size on 32 and 64 bit. */
    c->super.iret = waveInGetDevCapsA(c->uDeviceID, QEMU_G2H(c->lpCaps), c->uSize);
}

#endif

struct qemu_waveInOpen
{
    struct qemu_syscall super;
    uint64_t lphWaveIn;
    uint64_t uDeviceID;
    uint64_t lpFormat;
    uint64_t dwCallback;
    uint64_t dwInstance;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI waveInOpen(HWAVEIN* lphWaveIn, UINT uDeviceID, const WAVEFORMATEX *lpFormat,
        DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD dwFlags)
{
    struct qemu_waveInOpen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINOPEN);
    call.lphWaveIn = (ULONG_PTR)lphWaveIn;
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpFormat = (ULONG_PTR)lpFormat;
    call.dwCallback = (ULONG_PTR)dwCallback;
    call.dwInstance = (ULONG_PTR)dwInstance;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);
    if (call.super.iret == MMSYSERR_NOERROR)
        *lphWaveIn = (HWAVEIN)(ULONG_PTR)call.lphWaveIn;

    return call.super.iret;
}

#else

void qemu_waveInOpen(struct qemu_syscall *call)
{
    struct qemu_waveInOpen *c = (struct qemu_waveInOpen *)call;
    HWAVEIN h;

    /* FIXME: WaveOutOpen has code for some things that might be required here as well, but
     * Wine has no equivalent Wave In tests. Those things are:
     *
     * -> CALLBACK_FUNCTION
     * -> Keeping 32 bit wave out data structs alive until after they are done playing
     * -> WAVE_FORMAT_QUERY
     *
     * The second case may not be necessary depending on how waveInAddBuffer works. If that
     * is the case this would simplify wave in handling a bit. */
    WINE_TRACE("\n");
    if (c->dwCallback && ((c->dwFlags & CALLBACK_TYPEMASK) == CALLBACK_FUNCTION))
        WINE_FIXME("Wrap function callback 0x%lx!\n", c->dwCallback);

    c->super.iret = waveInOpen(c->lphWaveIn ? &h : NULL, c->uDeviceID,
            QEMU_G2H(c->lpFormat), c->dwCallback, c->dwInstance, c->dwFlags);
    c->lphWaveIn = QEMU_H2G(h);
}

#endif

struct qemu_waveInClose
{
    struct qemu_syscall super;
    uint64_t hWaveIn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveInClose(HWAVEIN hWaveIn)
{
    struct qemu_waveInClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINCLOSE);
    call.hWaveIn = (ULONG_PTR)hWaveIn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveInClose(struct qemu_syscall *call)
{
    struct qemu_waveInClose *c = (struct qemu_waveInClose *)call;
    WINE_TRACE("\n");
    c->super.iret = waveInClose(QEMU_G2H(c->hWaveIn));
}

#endif

struct qemu_waveInAddBuffer
{
    struct qemu_syscall super;
    uint64_t hWaveIn;
    uint64_t header;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveInAddBuffer(HWAVEIN hWaveIn, WAVEHDR *header, UINT uSize)
{
    struct qemu_waveInAddBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINADDBUFFER);
    call.hWaveIn = (ULONG_PTR)hWaveIn;
    call.header = (ULONG_PTR)header;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveInAddBuffer(struct qemu_syscall *call)
{
    struct qemu_waveInAddBuffer *c = (struct qemu_waveInAddBuffer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = waveInAddBuffer(QEMU_G2H(c->hWaveIn), QEMU_G2H(c->header), c->uSize);
}

#endif

struct qemu_waveInReset
{
    struct qemu_syscall super;
    uint64_t hWaveIn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveInReset(HWAVEIN hWaveIn)
{
    struct qemu_waveInReset call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINRESET);
    call.hWaveIn = (ULONG_PTR)hWaveIn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveInReset(struct qemu_syscall *call)
{
    struct qemu_waveInReset *c = (struct qemu_waveInReset *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = waveInReset(QEMU_G2H(c->hWaveIn));
}

#endif

struct qemu_waveInStart
{
    struct qemu_syscall super;
    uint64_t hWaveIn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveInStart(HWAVEIN hWaveIn)
{
    struct qemu_waveInStart call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINSTART);
    call.hWaveIn = (ULONG_PTR)hWaveIn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveInStart(struct qemu_syscall *call)
{
    struct qemu_waveInStart *c = (struct qemu_waveInStart *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = waveInStart(QEMU_G2H(c->hWaveIn));
}

#endif

struct qemu_waveInStop
{
    struct qemu_syscall super;
    uint64_t hWaveIn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveInStop(HWAVEIN hWaveIn)
{
    struct qemu_waveInStop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINSTOP);
    call.hWaveIn = (ULONG_PTR)hWaveIn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveInStop(struct qemu_syscall *call)
{
    struct qemu_waveInStop *c = (struct qemu_waveInStop *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = waveInStop(QEMU_G2H(c->hWaveIn));
}

#endif

struct qemu_waveInGetPosition
{
    struct qemu_syscall super;
    uint64_t hWaveIn;
    uint64_t lpTime;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveInGetPosition(HWAVEIN hWaveIn, LPMMTIME lpTime, UINT uSize)
{
    struct qemu_waveInGetPosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINGETPOSITION);
    call.hWaveIn = (ULONG_PTR)hWaveIn;
    call.lpTime = (ULONG_PTR)lpTime;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveInGetPosition(struct qemu_syscall *call)
{
    struct qemu_waveInGetPosition *c = (struct qemu_waveInGetPosition *)call;
    WINE_TRACE("\n");

    /* MMTIME has the same size on 32 and 64 bit. */
    c->super.iret = waveInGetPosition(QEMU_G2H(c->hWaveIn), QEMU_G2H(c->lpTime), c->uSize);
}

#endif

struct qemu_waveInGetID
{
    struct qemu_syscall super;
    uint64_t hWaveIn;
    uint64_t lpuDeviceID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveInGetID(HWAVEIN hWaveIn, UINT* lpuDeviceID)
{
    struct qemu_waveInGetID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINGETID);
    call.hWaveIn = (ULONG_PTR)hWaveIn;
    call.lpuDeviceID = (ULONG_PTR)lpuDeviceID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveInGetID(struct qemu_syscall *call)
{
    struct qemu_waveInGetID *c = (struct qemu_waveInGetID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = waveInGetID(QEMU_G2H(c->hWaveIn), QEMU_G2H(c->lpuDeviceID));
}

#endif

struct qemu_waveInMessage
{
    struct qemu_syscall super;
    uint64_t hWaveIn;
    uint64_t uMessage;
    uint64_t dwParam1;
    uint64_t dwParam2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI waveInMessage(HWAVEIN hWaveIn, UINT uMessage, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    struct qemu_waveInMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WAVEINMESSAGE);
    call.hWaveIn = (ULONG_PTR)hWaveIn;
    call.uMessage = (ULONG_PTR)uMessage;
    call.dwParam1 = dwParam1;
    call.dwParam2 = dwParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_waveInMessage(struct qemu_syscall *call)
{
    struct qemu_waveInMessage *c = (struct qemu_waveInMessage *)call;
    WINE_TRACE("\n");

#if GUEST_BIT != HOST_BIT
    /* DRV_QUERYFUNCTIONINSTANCEIDSIZE will need 32 / 64 translation, the others look OK */
    if (c->uMessage == DRV_QUERYFUNCTIONINSTANCEIDSIZE)
        WINE_FIXME("Handle DRV_QUERYFUNCTIONINSTANCEIDSIZE.\n");
#endif
    c->super.iret = waveInMessage(QEMU_G2H(c->hWaveIn), c->uMessage, c->dwParam1, c->dwParam2);
}

#endif

struct qemu_mixerGetNumDevs
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mixerGetNumDevs(void)
{
    struct qemu_mixerGetNumDevs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXERGETNUMDEVS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mixerGetNumDevs(struct qemu_syscall *call)
{
    struct qemu_mixerGetNumDevs *c = (struct qemu_mixerGetNumDevs *)call;
    WINE_TRACE("\n");
    c->super.iret = mixerGetNumDevs();
}

#endif

struct qemu_mixerGetDevCapsA
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpCaps;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mixerGetDevCapsA(UINT_PTR uDeviceID, LPMIXERCAPSA lpCaps, UINT uSize)
{
    struct qemu_mixerGetDevCapsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXERGETDEVCAPSA);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpCaps = (ULONG_PTR)lpCaps;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mixerGetDevCapsA(struct qemu_syscall *call)
{
    struct qemu_mixerGetDevCapsA *c = (struct qemu_mixerGetDevCapsA *)call;
    WINE_TRACE("\n");

    /* MIXERCAPSA has the same size in 32 and 64 bit. */
    c->super.iret = mixerGetDevCapsA(c->uDeviceID, QEMU_G2H(c->lpCaps), c->uSize);
}

#endif

struct qemu_mixerGetDevCapsW
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpCaps;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mixerGetDevCapsW(UINT_PTR uDeviceID, LPMIXERCAPSW lpCaps, UINT uSize)
{
    struct qemu_mixerGetDevCapsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXERGETDEVCAPSW);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpCaps = (ULONG_PTR)lpCaps;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mixerGetDevCapsW(struct qemu_syscall *call)
{
    struct qemu_mixerGetDevCapsW *c = (struct qemu_mixerGetDevCapsW *)call;
    WINE_TRACE("\n");

    /* MIXERCAPSW has the same size in 32 and 64 bit. */
    c->super.iret = mixerGetDevCapsW(c->uDeviceID, QEMU_G2H(c->lpCaps), c->uSize);
}

#endif

struct qemu_mixerOpen
{
    struct qemu_syscall super;
    uint64_t lphMix;
    uint64_t uDeviceID;
    uint64_t dwCallback;
    uint64_t dwInstance;
    uint64_t fdwOpen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mixerOpen(LPHMIXER lphMix, UINT uDeviceID, DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen)
{
    struct qemu_mixerOpen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXEROPEN);
    call.lphMix = (ULONG_PTR)lphMix;
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.dwCallback = (ULONG_PTR)dwCallback;
    call.dwInstance = (ULONG_PTR)dwInstance;
    call.fdwOpen = (ULONG_PTR)fdwOpen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mixerOpen(struct qemu_syscall *call)
{
    struct qemu_mixerOpen *c = (struct qemu_mixerOpen *)call;
    WINE_TRACE("\n");

    /* CALLBACK_FUNCTION is not valid for mixers. */
    c->super.iret = mixerOpen(QEMU_G2H(c->lphMix), c->uDeviceID, c->dwCallback, c->dwInstance, c->fdwOpen);
}

#endif

struct qemu_mixerClose
{
    struct qemu_syscall super;
    uint64_t hMix;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mixerClose(HMIXER hMix)
{
    struct qemu_mixerClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXERCLOSE);
    call.hMix = (ULONG_PTR)hMix;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mixerClose(struct qemu_syscall *call)
{
    struct qemu_mixerClose *c = (struct qemu_mixerClose *)call;
    WINE_TRACE("\n");
    c->super.iret = mixerClose(QEMU_G2H(c->hMix));
}

#endif

struct qemu_mixerGetID
{
    struct qemu_syscall super;
    uint64_t hmix;
    uint64_t lpid;
    uint64_t fdwID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mixerGetID(HMIXEROBJ hmix, LPUINT lpid, DWORD fdwID)
{
    struct qemu_mixerGetID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXERGETID);
    call.hmix = (ULONG_PTR)hmix;
    call.lpid = (ULONG_PTR)lpid;
    call.fdwID = (ULONG_PTR)fdwID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mixerGetID(struct qemu_syscall *call)
{
    struct qemu_mixerGetID *c = (struct qemu_mixerGetID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mixerGetID(QEMU_G2H(c->hmix), QEMU_G2H(c->lpid), c->fdwID);
}

#endif

struct qemu_mixerGetControlDetails
{
    struct qemu_syscall super;
    uint64_t hmix;
    uint64_t lpmcd;
    uint64_t fdwDetails;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mixerGetControlDetailsA(HMIXEROBJ hmix, LPMIXERCONTROLDETAILS lpmcdA, DWORD fdwDetails)
{
    struct qemu_mixerGetControlDetails call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXERGETCONTROLDETAILSA);
    call.hmix = (ULONG_PTR)hmix;
    call.lpmcd = (ULONG_PTR)lpmcdA;
    call.fdwDetails = (ULONG_PTR)fdwDetails;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI UINT WINAPI mixerGetControlDetailsW(HMIXEROBJ hmix, LPMIXERCONTROLDETAILS lpmcdW, DWORD fdwDetails)
{
    struct qemu_mixerGetControlDetails call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXERGETCONTROLDETAILSW);
    call.hmix = (ULONG_PTR)hmix;
    call.lpmcd = (ULONG_PTR)lpmcdW;
    call.fdwDetails = (ULONG_PTR)fdwDetails;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mixerGetControlDetails(struct qemu_syscall *call)
{
    struct qemu_mixerGetControlDetails *c = (struct qemu_mixerGetControlDetails *)call;
    struct qemu_MIXERCONTROLDETAILS *details32;
    MIXERCONTROLDETAILS stack, *details = &stack;

    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    details = QEMU_G2H(c->lpmcd);
#else
    details32 = QEMU_G2H(c->lpmcd);
    if (!details32)
        details = NULL;
    else if (details32->cbStruct != sizeof(*details32))
        details->cbStruct = 0;
    else
        MIXERCONTROLDETAILS_g2h(details, details32);
#endif

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_MIXERGETCONTROLDETAILSA):
            c->super.iret = mixerGetControlDetailsA(QEMU_G2H(c->hmix), details, c->fdwDetails);
            break;

        case QEMU_SYSCALL_ID(CALL_MIXERGETCONTROLDETAILSW):
            c->super.iret = mixerGetControlDetailsA(QEMU_G2H(c->hmix), details, c->fdwDetails);
            break;
    }

#if HOST_BIT != GUEST_BIT
    if (c->super.iret == MMSYSERR_NOERROR)
        MIXERCONTROLDETAILS_h2g(details32, details);
#endif
}

#endif

struct qemu_mixerGetControlDetailsA
{
    struct qemu_syscall super;
    uint64_t hmix;
    uint64_t lpmcdA;
    uint64_t fdwDetails;
};

struct qemu_mixerGetLineControls
{
    struct qemu_syscall super;
    uint64_t hmix;
    uint64_t lpmlc;
    uint64_t fdwControls;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mixerGetLineControlsA(HMIXEROBJ hmix, LPMIXERLINECONTROLSA lpmlcA, DWORD fdwControls)
{
    struct qemu_mixerGetLineControls call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXERGETLINECONTROLSA);
    call.hmix = (ULONG_PTR)hmix;
    call.lpmlc = (ULONG_PTR)lpmlcA;
    call.fdwControls = (ULONG_PTR)fdwControls;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI UINT WINAPI mixerGetLineControlsW(HMIXEROBJ hmix, LPMIXERLINECONTROLSW lpmlcW, DWORD fdwControls)
{
    struct qemu_mixerGetLineControls call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXERGETLINECONTROLSW);
    call.hmix = (ULONG_PTR)hmix;
    call.lpmlc = (ULONG_PTR)lpmlcW;
    call.fdwControls = (ULONG_PTR)fdwControls;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mixerGetLineControls(struct qemu_syscall *call)
{
    struct qemu_mixerGetLineControls *c = (struct qemu_mixerGetLineControls *)call;
    MIXERLINECONTROLSW stack, *ctrl = &stack;
    struct qemu_MIXERLINECONTROLS *ctrl32;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    ctrl = QEMU_G2H(c->lpmlc);
#else
    ctrl32 = QEMU_G2H(c->lpmlc);
    if (!ctrl32)
        ctrl = NULL;
    else if (ctrl32->cbStruct != sizeof(*ctrl32))
        ctrl->cbStruct = 0;
    else
        MIXERLINECONTROLS_g2h(ctrl, ctrl32);
#endif

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_MIXERGETLINECONTROLSA):
            c->super.iret = mixerGetLineControlsA(QEMU_G2H(c->hmix), (MIXERLINECONTROLSA *)ctrl, c->fdwControls);
            break;
        case QEMU_SYSCALL_ID(CALL_MIXERGETLINECONTROLSW):
            c->super.iret = mixerGetLineControlsW(QEMU_G2H(c->hmix), ctrl, c->fdwControls);
            break;
    }

#if GUEST_BIT != HOST_BIT
    if (c->super.iret == MMSYSERR_NOERROR)
        MIXERLINECONTROLS_h2g(ctrl32, ctrl);
#endif
}

#endif

struct qemu_mixerGetLineInfoW
{
    struct qemu_syscall super;
    uint64_t hmix;
    uint64_t lpmliW;
    uint64_t fdwInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mixerGetLineInfoW(HMIXEROBJ hmix, LPMIXERLINEW lpmliW, DWORD fdwInfo)
{
    struct qemu_mixerGetLineInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXERGETLINEINFOW);
    call.hmix = (ULONG_PTR)hmix;
    call.lpmliW = (ULONG_PTR)lpmliW;
    call.fdwInfo = (ULONG_PTR)fdwInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mixerGetLineInfoW(struct qemu_syscall *call)
{
    struct qemu_mixerGetLineInfoW *c = (struct qemu_mixerGetLineInfoW *)call;
    MIXERLINEW stack, *line = &stack;
    struct qemu_MIXERLINEW *line32;

    WINE_TRACE("\n");
#if HOST_BIT == GUEST_BIT
    line = QEMU_G2H(c->lpmliW);
#else
    line32 = QEMU_G2H(c->lpmliW);
    if (!line32)
        line = NULL;
    else if (line32->cbStruct != sizeof(*line32))
        line->cbStruct = 0;
    else
        MIXERLINEW_g2h(line, line32);
#endif

    c->super.iret = mixerGetLineInfoW(QEMU_G2H(c->hmix), line, c->fdwInfo);

#if HOST_BIT != GUEST_BIT
    if (c->super.iret == MMSYSERR_NOERROR)
        MIXERLINEW_h2g(line32, line);
#endif
}

#endif

struct qemu_mixerGetLineInfoA
{
    struct qemu_syscall super;
    uint64_t hmix;
    uint64_t lpmliA;
    uint64_t fdwInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mixerGetLineInfoA(HMIXEROBJ hmix, LPMIXERLINEA lpmliA, DWORD fdwInfo)
{
    struct qemu_mixerGetLineInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXERGETLINEINFOA);
    call.hmix = (ULONG_PTR)hmix;
    call.lpmliA = (ULONG_PTR)lpmliA;
    call.fdwInfo = (ULONG_PTR)fdwInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mixerGetLineInfoA(struct qemu_syscall *call)
{
    struct qemu_mixerGetLineInfoA *c = (struct qemu_mixerGetLineInfoA *)call;
    MIXERLINEA stack, *line = &stack;
    struct qemu_MIXERLINEA *line32;

    WINE_TRACE("\n");
#if HOST_BIT == GUEST_BIT
    line = QEMU_G2H(c->lpmliA);
#else
    line32 = QEMU_G2H(c->lpmliA);
    if (!line32)
        line = NULL;
    else if (line32->cbStruct != sizeof(*line32))
        line->cbStruct = 0;
    else
        MIXERLINEA_g2h(line, line32);
#endif

    c->super.iret = mixerGetLineInfoA(QEMU_G2H(c->hmix), line, c->fdwInfo);

#if HOST_BIT != GUEST_BIT
    if (c->super.iret == MMSYSERR_NOERROR)
        MIXERLINEA_h2g(line32, line);
#endif
}

#endif

struct qemu_mixerSetControlDetails
{
    struct qemu_syscall super;
    uint64_t hmix;
    uint64_t lpmcd;
    uint64_t fdwDetails;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mixerSetControlDetails(HMIXEROBJ hmix, LPMIXERCONTROLDETAILS lpmcd, DWORD fdwDetails)
{
    struct qemu_mixerSetControlDetails call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXERSETCONTROLDETAILS);
    call.hmix = (ULONG_PTR)hmix;
    call.lpmcd = (ULONG_PTR)lpmcd;
    call.fdwDetails = (ULONG_PTR)fdwDetails;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mixerSetControlDetails(struct qemu_syscall *call)
{
    struct qemu_mixerSetControlDetails *c = (struct qemu_mixerSetControlDetails *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mixerSetControlDetails(QEMU_G2H(c->hmix), QEMU_G2H(c->lpmcd), c->fdwDetails);
}

#endif

struct qemu_mixerMessage
{
    struct qemu_syscall super;
    uint64_t hmix;
    uint64_t uMsg;
    uint64_t dwParam1;
    uint64_t dwParam2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI mixerMessage(HMIXER hmix, UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    struct qemu_mixerMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIXERMESSAGE);
    call.hmix = (ULONG_PTR)hmix;
    call.uMsg = (ULONG_PTR)uMsg;
    call.dwParam1 = (ULONG_PTR)dwParam1;
    call.dwParam2 = (ULONG_PTR)dwParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mixerMessage(struct qemu_syscall *call)
{
    struct qemu_mixerMessage *c = (struct qemu_mixerMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mixerMessage(QEMU_G2H(c->hmix), c->uMsg, c->dwParam1, c->dwParam2);
}

#endif

