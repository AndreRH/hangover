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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_winmm.h"

#ifndef QEMU_DLL_GUEST
#include <mmddk.h>
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_winmm);
#endif


struct qemu_auxGetNumDevs
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI auxGetNumDevs(void)
{
    struct qemu_auxGetNumDevs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_AUXGETNUMDEVS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_auxGetNumDevs(struct qemu_syscall *call)
{
    struct qemu_auxGetNumDevs *c = (struct qemu_auxGetNumDevs *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = auxGetNumDevs();
}

#endif

struct qemu_auxGetDevCapsW
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpCaps;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI auxGetDevCapsW(UINT_PTR uDeviceID, LPAUXCAPSW lpCaps, UINT uSize)
{
    struct qemu_auxGetDevCapsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_AUXGETDEVCAPSW);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpCaps = (ULONG_PTR)lpCaps;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_auxGetDevCapsW(struct qemu_syscall *call)
{
    struct qemu_auxGetDevCapsW *c = (struct qemu_auxGetDevCapsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = auxGetDevCapsW(c->uDeviceID, QEMU_G2H(c->lpCaps), c->uSize);
}

#endif

struct qemu_auxGetDevCapsA
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpCaps;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI auxGetDevCapsA(UINT_PTR uDeviceID, LPAUXCAPSA lpCaps, UINT uSize)
{
    struct qemu_auxGetDevCapsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_AUXGETDEVCAPSA);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpCaps = (ULONG_PTR)lpCaps;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_auxGetDevCapsA(struct qemu_syscall *call)
{
    struct qemu_auxGetDevCapsA *c = (struct qemu_auxGetDevCapsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = auxGetDevCapsA(c->uDeviceID, QEMU_G2H(c->lpCaps), c->uSize);
}

#endif

struct qemu_auxGetVolume
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpdwVolume;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI auxGetVolume(UINT uDeviceID, DWORD* lpdwVolume)
{
    struct qemu_auxGetVolume call;
    call.super.id = QEMU_SYSCALL_ID(CALL_AUXGETVOLUME);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpdwVolume = (ULONG_PTR)lpdwVolume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_auxGetVolume(struct qemu_syscall *call)
{
    struct qemu_auxGetVolume *c = (struct qemu_auxGetVolume *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = auxGetVolume(c->uDeviceID, QEMU_G2H(c->lpdwVolume));
}

#endif

struct qemu_auxSetVolume
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t dwVolume;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI auxSetVolume(UINT uDeviceID, DWORD dwVolume)
{
    struct qemu_auxSetVolume call;
    call.super.id = QEMU_SYSCALL_ID(CALL_AUXSETVOLUME);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.dwVolume = (ULONG_PTR)dwVolume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_auxSetVolume(struct qemu_syscall *call)
{
    struct qemu_auxSetVolume *c = (struct qemu_auxSetVolume *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = auxSetVolume(c->uDeviceID, c->dwVolume);
}

#endif

struct qemu_auxOutMessage
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t uMessage;
    uint64_t dw1;
    uint64_t dw2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI auxOutMessage(UINT uDeviceID, UINT uMessage, DWORD_PTR dw1, DWORD_PTR dw2)
{
    struct qemu_auxOutMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_AUXOUTMESSAGE);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.uMessage = (ULONG_PTR)uMessage;
    call.dw1 = (ULONG_PTR)dw1;
    call.dw2 = (ULONG_PTR)dw2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_auxOutMessage(struct qemu_syscall *call)
{
    struct qemu_auxOutMessage *c = (struct qemu_auxOutMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = auxOutMessage(c->uDeviceID, c->uMessage, c->dw1, c->dw2);
}

#endif

struct qemu_midiOutGetNumDevs
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutGetNumDevs(void)
{
    struct qemu_midiOutGetNumDevs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTGETNUMDEVS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutGetNumDevs(struct qemu_syscall *call)
{
    struct qemu_midiOutGetNumDevs *c = (struct qemu_midiOutGetNumDevs *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutGetNumDevs();
}

#endif

struct qemu_midiOutGetDevCapsW
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpCaps;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutGetDevCapsW(UINT_PTR uDeviceID, LPMIDIOUTCAPSW lpCaps, UINT uSize)
{
    struct qemu_midiOutGetDevCapsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTGETDEVCAPSW);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpCaps = (ULONG_PTR)lpCaps;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutGetDevCapsW(struct qemu_syscall *call)
{
    struct qemu_midiOutGetDevCapsW *c = (struct qemu_midiOutGetDevCapsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutGetDevCapsW(c->uDeviceID, QEMU_G2H(c->lpCaps), c->uSize);
}

#endif

struct qemu_midiOutGetDevCapsA
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpCaps;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutGetDevCapsA(UINT_PTR uDeviceID, LPMIDIOUTCAPSA lpCaps, UINT uSize)
{
    struct qemu_midiOutGetDevCapsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTGETDEVCAPSA);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpCaps = (ULONG_PTR)lpCaps;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutGetDevCapsA(struct qemu_syscall *call)
{
    struct qemu_midiOutGetDevCapsA *c = (struct qemu_midiOutGetDevCapsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutGetDevCapsA(c->uDeviceID, QEMU_G2H(c->lpCaps), c->uSize);
}

#endif

struct qemu_midiOutGetErrorTextA
{
    struct qemu_syscall super;
    uint64_t uError;
    uint64_t lpText;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutGetErrorTextA(UINT uError, LPSTR lpText, UINT uSize)
{
    struct qemu_midiOutGetErrorTextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTGETERRORTEXTA);
    call.uError = (ULONG_PTR)uError;
    call.lpText = (ULONG_PTR)lpText;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutGetErrorTextA(struct qemu_syscall *call)
{
    struct qemu_midiOutGetErrorTextA *c = (struct qemu_midiOutGetErrorTextA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutGetErrorTextA(c->uError, QEMU_G2H(c->lpText), c->uSize);
}

#endif

struct qemu_midiOutGetErrorTextW
{
    struct qemu_syscall super;
    uint64_t uError;
    uint64_t lpText;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutGetErrorTextW(UINT uError, LPWSTR lpText, UINT uSize)
{
    struct qemu_midiOutGetErrorTextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTGETERRORTEXTW);
    call.uError = (ULONG_PTR)uError;
    call.lpText = (ULONG_PTR)lpText;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutGetErrorTextW(struct qemu_syscall *call)
{
    struct qemu_midiOutGetErrorTextW *c = (struct qemu_midiOutGetErrorTextW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutGetErrorTextW(c->uError, QEMU_G2H(c->lpText), c->uSize);
}

#endif

struct qemu_midiOutOpen
{
    struct qemu_syscall super;
    uint64_t lphMidiOut;
    uint64_t uDeviceID;
    uint64_t dwCallback;
    uint64_t dwInstance;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI midiOutOpen(LPHMIDIOUT lphMidiOut, UINT uDeviceID, DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD dwFlags)
{
    struct qemu_midiOutOpen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTOPEN);
    call.lphMidiOut = (ULONG_PTR)lphMidiOut;
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.dwCallback = (ULONG_PTR)dwCallback;
    call.dwInstance = (ULONG_PTR)dwInstance;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutOpen(struct qemu_syscall *call)
{
    struct qemu_midiOutOpen *c = (struct qemu_midiOutOpen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutOpen(QEMU_G2H(c->lphMidiOut), c->uDeviceID, c->dwCallback, c->dwInstance, c->dwFlags);
}

#endif

struct qemu_midiOutClose
{
    struct qemu_syscall super;
    uint64_t hMidiOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutClose(HMIDIOUT hMidiOut)
{
    struct qemu_midiOutClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTCLOSE);
    call.hMidiOut = (ULONG_PTR)hMidiOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutClose(struct qemu_syscall *call)
{
    struct qemu_midiOutClose *c = (struct qemu_midiOutClose *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutClose(QEMU_G2H(c->hMidiOut));
}

#endif

struct qemu_midiOutPrepareHeader
{
    struct qemu_syscall super;
    uint64_t hMidiOut;
    uint64_t lpMidiOutHdr;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutPrepareHeader(HMIDIOUT hMidiOut, MIDIHDR* lpMidiOutHdr, UINT uSize)
{
    struct qemu_midiOutPrepareHeader call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTPREPAREHEADER);
    call.hMidiOut = (ULONG_PTR)hMidiOut;
    call.lpMidiOutHdr = (ULONG_PTR)lpMidiOutHdr;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutPrepareHeader(struct qemu_syscall *call)
{
    struct qemu_midiOutPrepareHeader *c = (struct qemu_midiOutPrepareHeader *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutPrepareHeader(QEMU_G2H(c->hMidiOut), QEMU_G2H(c->lpMidiOutHdr), c->uSize);
}

#endif

struct qemu_midiOutUnprepareHeader
{
    struct qemu_syscall super;
    uint64_t hMidiOut;
    uint64_t lpMidiOutHdr;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutUnprepareHeader(HMIDIOUT hMidiOut, MIDIHDR* lpMidiOutHdr, UINT uSize)
{
    struct qemu_midiOutUnprepareHeader call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTUNPREPAREHEADER);
    call.hMidiOut = (ULONG_PTR)hMidiOut;
    call.lpMidiOutHdr = (ULONG_PTR)lpMidiOutHdr;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutUnprepareHeader(struct qemu_syscall *call)
{
    struct qemu_midiOutUnprepareHeader *c = (struct qemu_midiOutUnprepareHeader *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutUnprepareHeader(QEMU_G2H(c->hMidiOut), QEMU_G2H(c->lpMidiOutHdr), c->uSize);
}

#endif

struct qemu_midiOutShortMsg
{
    struct qemu_syscall super;
    uint64_t hMidiOut;
    uint64_t dwMsg;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutShortMsg(HMIDIOUT hMidiOut, DWORD dwMsg)
{
    struct qemu_midiOutShortMsg call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTSHORTMSG);
    call.hMidiOut = (ULONG_PTR)hMidiOut;
    call.dwMsg = (ULONG_PTR)dwMsg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutShortMsg(struct qemu_syscall *call)
{
    struct qemu_midiOutShortMsg *c = (struct qemu_midiOutShortMsg *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutShortMsg(QEMU_G2H(c->hMidiOut), c->dwMsg);
}

#endif

struct qemu_midiOutLongMsg
{
    struct qemu_syscall super;
    uint64_t hMidiOut;
    uint64_t lpMidiOutHdr;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutLongMsg(HMIDIOUT hMidiOut, MIDIHDR* lpMidiOutHdr, UINT uSize)
{
    struct qemu_midiOutLongMsg call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTLONGMSG);
    call.hMidiOut = (ULONG_PTR)hMidiOut;
    call.lpMidiOutHdr = (ULONG_PTR)lpMidiOutHdr;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutLongMsg(struct qemu_syscall *call)
{
    struct qemu_midiOutLongMsg *c = (struct qemu_midiOutLongMsg *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutLongMsg(QEMU_G2H(c->hMidiOut), QEMU_G2H(c->lpMidiOutHdr), c->uSize);
}

#endif

struct qemu_midiOutReset
{
    struct qemu_syscall super;
    uint64_t hMidiOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutReset(HMIDIOUT hMidiOut)
{
    struct qemu_midiOutReset call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTRESET);
    call.hMidiOut = (ULONG_PTR)hMidiOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutReset(struct qemu_syscall *call)
{
    struct qemu_midiOutReset *c = (struct qemu_midiOutReset *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutReset(QEMU_G2H(c->hMidiOut));
}

#endif

struct qemu_midiOutGetVolume
{
    struct qemu_syscall super;
    uint64_t hMidiOut;
    uint64_t lpdwVolume;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutGetVolume(HMIDIOUT hMidiOut, DWORD* lpdwVolume)
{
    struct qemu_midiOutGetVolume call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTGETVOLUME);
    call.hMidiOut = (ULONG_PTR)hMidiOut;
    call.lpdwVolume = (ULONG_PTR)lpdwVolume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutGetVolume(struct qemu_syscall *call)
{
    struct qemu_midiOutGetVolume *c = (struct qemu_midiOutGetVolume *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutGetVolume(QEMU_G2H(c->hMidiOut), QEMU_G2H(c->lpdwVolume));
}

#endif

struct qemu_midiOutSetVolume
{
    struct qemu_syscall super;
    uint64_t hMidiOut;
    uint64_t dwVolume;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutSetVolume(HMIDIOUT hMidiOut, DWORD dwVolume)
{
    struct qemu_midiOutSetVolume call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTSETVOLUME);
    call.hMidiOut = (ULONG_PTR)hMidiOut;
    call.dwVolume = (ULONG_PTR)dwVolume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutSetVolume(struct qemu_syscall *call)
{
    struct qemu_midiOutSetVolume *c = (struct qemu_midiOutSetVolume *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutSetVolume(QEMU_G2H(c->hMidiOut), c->dwVolume);
}

#endif

struct qemu_midiOutCachePatches
{
    struct qemu_syscall super;
    uint64_t hMidiOut;
    uint64_t uBank;
    uint64_t lpwPatchArray;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutCachePatches(HMIDIOUT hMidiOut, UINT uBank, WORD* lpwPatchArray, UINT uFlags)
{
    struct qemu_midiOutCachePatches call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTCACHEPATCHES);
    call.hMidiOut = (ULONG_PTR)hMidiOut;
    call.uBank = (ULONG_PTR)uBank;
    call.lpwPatchArray = (ULONG_PTR)lpwPatchArray;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutCachePatches(struct qemu_syscall *call)
{
    struct qemu_midiOutCachePatches *c = (struct qemu_midiOutCachePatches *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutCachePatches(QEMU_G2H(c->hMidiOut), c->uBank, QEMU_G2H(c->lpwPatchArray), c->uFlags);
}

#endif

struct qemu_midiOutCacheDrumPatches
{
    struct qemu_syscall super;
    uint64_t hMidiOut;
    uint64_t uPatch;
    uint64_t lpwKeyArray;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutCacheDrumPatches(HMIDIOUT hMidiOut, UINT uPatch, WORD* lpwKeyArray, UINT uFlags)
{
    struct qemu_midiOutCacheDrumPatches call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTCACHEDRUMPATCHES);
    call.hMidiOut = (ULONG_PTR)hMidiOut;
    call.uPatch = (ULONG_PTR)uPatch;
    call.lpwKeyArray = (ULONG_PTR)lpwKeyArray;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutCacheDrumPatches(struct qemu_syscall *call)
{
    struct qemu_midiOutCacheDrumPatches *c = (struct qemu_midiOutCacheDrumPatches *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutCacheDrumPatches(QEMU_G2H(c->hMidiOut), c->uPatch, QEMU_G2H(c->lpwKeyArray), c->uFlags);
}

#endif

struct qemu_midiOutGetID
{
    struct qemu_syscall super;
    uint64_t hMidiOut;
    uint64_t lpuDeviceID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutGetID(HMIDIOUT hMidiOut, UINT* lpuDeviceID)
{
    struct qemu_midiOutGetID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTGETID);
    call.hMidiOut = (ULONG_PTR)hMidiOut;
    call.lpuDeviceID = (ULONG_PTR)lpuDeviceID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutGetID(struct qemu_syscall *call)
{
    struct qemu_midiOutGetID *c = (struct qemu_midiOutGetID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutGetID(QEMU_G2H(c->hMidiOut), QEMU_G2H(c->lpuDeviceID));
}

#endif

struct qemu_midiOutMessage
{
    struct qemu_syscall super;
    uint64_t hMidiOut;
    uint64_t uMessage;
    uint64_t dwParam1;
    uint64_t dwParam2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiOutMessage(HMIDIOUT hMidiOut, UINT uMessage, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    struct qemu_midiOutMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIOUTMESSAGE);
    call.hMidiOut = (ULONG_PTR)hMidiOut;
    call.uMessage = (ULONG_PTR)uMessage;
    call.dwParam1 = (ULONG_PTR)dwParam1;
    call.dwParam2 = (ULONG_PTR)dwParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiOutMessage(struct qemu_syscall *call)
{
    struct qemu_midiOutMessage *c = (struct qemu_midiOutMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiOutMessage(QEMU_G2H(c->hMidiOut), c->uMessage, c->dwParam1, c->dwParam2);
}

#endif

struct qemu_midiInGetNumDevs
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiInGetNumDevs(void)
{
    struct qemu_midiInGetNumDevs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIINGETNUMDEVS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiInGetNumDevs(struct qemu_syscall *call)
{
    struct qemu_midiInGetNumDevs *c = (struct qemu_midiInGetNumDevs *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiInGetNumDevs();
}

#endif

struct qemu_midiInGetDevCapsW
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpCaps;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiInGetDevCapsW(UINT_PTR uDeviceID, LPMIDIINCAPSW lpCaps, UINT uSize)
{
    struct qemu_midiInGetDevCapsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIINGETDEVCAPSW);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpCaps = (ULONG_PTR)lpCaps;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiInGetDevCapsW(struct qemu_syscall *call)
{
    struct qemu_midiInGetDevCapsW *c = (struct qemu_midiInGetDevCapsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiInGetDevCapsW(c->uDeviceID, QEMU_G2H(c->lpCaps), c->uSize);
}

#endif

struct qemu_midiInGetDevCapsA
{
    struct qemu_syscall super;
    uint64_t uDeviceID;
    uint64_t lpCaps;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiInGetDevCapsA(UINT_PTR uDeviceID, LPMIDIINCAPSA lpCaps, UINT uSize)
{
    struct qemu_midiInGetDevCapsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIINGETDEVCAPSA);
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.lpCaps = (ULONG_PTR)lpCaps;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiInGetDevCapsA(struct qemu_syscall *call)
{
    struct qemu_midiInGetDevCapsA *c = (struct qemu_midiInGetDevCapsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiInGetDevCapsA(c->uDeviceID, QEMU_G2H(c->lpCaps), c->uSize);
}

#endif

struct qemu_midiInOpen
{
    struct qemu_syscall super;
    uint64_t lphMidiIn;
    uint64_t uDeviceID;
    uint64_t dwCallback;
    uint64_t dwInstance;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI midiInOpen(HMIDIIN* lphMidiIn, UINT uDeviceID, DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD dwFlags)
{
    struct qemu_midiInOpen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIINOPEN);
    call.lphMidiIn = (ULONG_PTR)lphMidiIn;
    call.uDeviceID = (ULONG_PTR)uDeviceID;
    call.dwCallback = (ULONG_PTR)dwCallback;
    call.dwInstance = (ULONG_PTR)dwInstance;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiInOpen(struct qemu_syscall *call)
{
    struct qemu_midiInOpen *c = (struct qemu_midiInOpen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiInOpen(QEMU_G2H(c->lphMidiIn), c->uDeviceID, c->dwCallback, c->dwInstance, c->dwFlags);
}

#endif

struct qemu_midiInClose
{
    struct qemu_syscall super;
    uint64_t hMidiIn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiInClose(HMIDIIN hMidiIn)
{
    struct qemu_midiInClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIINCLOSE);
    call.hMidiIn = (ULONG_PTR)hMidiIn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiInClose(struct qemu_syscall *call)
{
    struct qemu_midiInClose *c = (struct qemu_midiInClose *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiInClose(QEMU_G2H(c->hMidiIn));
}

#endif

struct qemu_midiInPrepareHeader
{
    struct qemu_syscall super;
    uint64_t hMidiIn;
    uint64_t lpMidiInHdr;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiInPrepareHeader(HMIDIIN hMidiIn, MIDIHDR* lpMidiInHdr, UINT uSize)
{
    struct qemu_midiInPrepareHeader call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIINPREPAREHEADER);
    call.hMidiIn = (ULONG_PTR)hMidiIn;
    call.lpMidiInHdr = (ULONG_PTR)lpMidiInHdr;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiInPrepareHeader(struct qemu_syscall *call)
{
    struct qemu_midiInPrepareHeader *c = (struct qemu_midiInPrepareHeader *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiInPrepareHeader(QEMU_G2H(c->hMidiIn), QEMU_G2H(c->lpMidiInHdr), c->uSize);
}

#endif

struct qemu_midiInUnprepareHeader
{
    struct qemu_syscall super;
    uint64_t hMidiIn;
    uint64_t lpMidiInHdr;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiInUnprepareHeader(HMIDIIN hMidiIn, MIDIHDR* lpMidiInHdr, UINT uSize)
{
    struct qemu_midiInUnprepareHeader call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIINUNPREPAREHEADER);
    call.hMidiIn = (ULONG_PTR)hMidiIn;
    call.lpMidiInHdr = (ULONG_PTR)lpMidiInHdr;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiInUnprepareHeader(struct qemu_syscall *call)
{
    struct qemu_midiInUnprepareHeader *c = (struct qemu_midiInUnprepareHeader *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiInUnprepareHeader(QEMU_G2H(c->hMidiIn), QEMU_G2H(c->lpMidiInHdr), c->uSize);
}

#endif

struct qemu_midiInAddBuffer
{
    struct qemu_syscall super;
    uint64_t hMidiIn;
    uint64_t lpMidiInHdr;
    uint64_t uSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiInAddBuffer(HMIDIIN hMidiIn, MIDIHDR* lpMidiInHdr, UINT uSize)
{
    struct qemu_midiInAddBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIINADDBUFFER);
    call.hMidiIn = (ULONG_PTR)hMidiIn;
    call.lpMidiInHdr = (ULONG_PTR)lpMidiInHdr;
    call.uSize = (ULONG_PTR)uSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiInAddBuffer(struct qemu_syscall *call)
{
    struct qemu_midiInAddBuffer *c = (struct qemu_midiInAddBuffer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiInAddBuffer(QEMU_G2H(c->hMidiIn), QEMU_G2H(c->lpMidiInHdr), c->uSize);
}

#endif

struct qemu_midiInStart
{
    struct qemu_syscall super;
    uint64_t hMidiIn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiInStart(HMIDIIN hMidiIn)
{
    struct qemu_midiInStart call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIINSTART);
    call.hMidiIn = (ULONG_PTR)hMidiIn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiInStart(struct qemu_syscall *call)
{
    struct qemu_midiInStart *c = (struct qemu_midiInStart *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiInStart(QEMU_G2H(c->hMidiIn));
}

#endif

struct qemu_midiInStop
{
    struct qemu_syscall super;
    uint64_t hMidiIn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiInStop(HMIDIIN hMidiIn)
{
    struct qemu_midiInStop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIINSTOP);
    call.hMidiIn = (ULONG_PTR)hMidiIn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiInStop(struct qemu_syscall *call)
{
    struct qemu_midiInStop *c = (struct qemu_midiInStop *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiInStop(QEMU_G2H(c->hMidiIn));
}

#endif

struct qemu_midiInReset
{
    struct qemu_syscall super;
    uint64_t hMidiIn;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiInReset(HMIDIIN hMidiIn)
{
    struct qemu_midiInReset call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIINRESET);
    call.hMidiIn = (ULONG_PTR)hMidiIn;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiInReset(struct qemu_syscall *call)
{
    struct qemu_midiInReset *c = (struct qemu_midiInReset *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiInReset(QEMU_G2H(c->hMidiIn));
}

#endif

struct qemu_midiInGetID
{
    struct qemu_syscall super;
    uint64_t hMidiIn;
    uint64_t lpuDeviceID;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiInGetID(HMIDIIN hMidiIn, UINT* lpuDeviceID)
{
    struct qemu_midiInGetID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIINGETID);
    call.hMidiIn = (ULONG_PTR)hMidiIn;
    call.lpuDeviceID = (ULONG_PTR)lpuDeviceID;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiInGetID(struct qemu_syscall *call)
{
    struct qemu_midiInGetID *c = (struct qemu_midiInGetID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiInGetID(QEMU_G2H(c->hMidiIn), QEMU_G2H(c->lpuDeviceID));
}

#endif

struct qemu_midiInMessage
{
    struct qemu_syscall super;
    uint64_t hMidiIn;
    uint64_t uMessage;
    uint64_t dwParam1;
    uint64_t dwParam2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI midiInMessage(HMIDIIN hMidiIn, UINT uMessage, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    struct qemu_midiInMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIINMESSAGE);
    call.hMidiIn = (ULONG_PTR)hMidiIn;
    call.uMessage = (ULONG_PTR)uMessage;
    call.dwParam1 = (ULONG_PTR)dwParam1;
    call.dwParam2 = (ULONG_PTR)dwParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiInMessage(struct qemu_syscall *call)
{
    struct qemu_midiInMessage *c = (struct qemu_midiInMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiInMessage(QEMU_G2H(c->hMidiIn), c->uMessage, c->dwParam1, c->dwParam2);
}

#endif

struct qemu_midiConnect
{
    struct qemu_syscall super;
    uint64_t hMidi;
    uint64_t hmo;
    uint64_t pReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI midiConnect(HMIDI hMidi, HMIDIOUT hmo, LPVOID pReserved)
{
    struct qemu_midiConnect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDICONNECT);
    call.hMidi = (ULONG_PTR)hMidi;
    call.hmo = (ULONG_PTR)hmo;
    call.pReserved = (ULONG_PTR)pReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add midiConnect to Wine headers? */
extern MMRESULT WINAPI midiConnect(HMIDI hMidi, HMIDIOUT hmo, LPVOID pReserved);
void qemu_midiConnect(struct qemu_syscall *call)
{
    struct qemu_midiConnect *c = (struct qemu_midiConnect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiConnect(QEMU_G2H(c->hMidi), QEMU_G2H(c->hmo), QEMU_G2H(c->pReserved));
}

#endif

struct qemu_midiDisconnect
{
    struct qemu_syscall super;
    uint64_t hMidi;
    uint64_t hmo;
    uint64_t pReserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI midiDisconnect(HMIDI hMidi, HMIDIOUT hmo, LPVOID pReserved)
{
    struct qemu_midiDisconnect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDIDISCONNECT);
    call.hMidi = (ULONG_PTR)hMidi;
    call.hmo = (ULONG_PTR)hmo;
    call.pReserved = (ULONG_PTR)pReserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add midiDisconnect to Wine headers? */
extern MMRESULT WINAPI midiDisconnect(HMIDI hMidi, HMIDIOUT hmo, LPVOID pReserved);
void qemu_midiDisconnect(struct qemu_syscall *call)
{
    struct qemu_midiDisconnect *c = (struct qemu_midiDisconnect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiDisconnect(QEMU_G2H(c->hMidi), QEMU_G2H(c->hmo), QEMU_G2H(c->pReserved));
}

#endif

struct qemu_midiStreamClose
{
    struct qemu_syscall super;
    uint64_t hMidiStrm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI midiStreamClose(HMIDISTRM hMidiStrm)
{
    struct qemu_midiStreamClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDISTREAMCLOSE);
    call.hMidiStrm = (ULONG_PTR)hMidiStrm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiStreamClose(struct qemu_syscall *call)
{
    struct qemu_midiStreamClose *c = (struct qemu_midiStreamClose *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiStreamClose(QEMU_G2H(c->hMidiStrm));
}

#endif

struct qemu_midiStreamOpen
{
    struct qemu_syscall super;
    uint64_t lphMidiStrm;
    uint64_t lpuDeviceID;
    uint64_t cMidi;
    uint64_t dwCallback;
    uint64_t dwInstance;
    uint64_t fdwOpen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI midiStreamOpen(HMIDISTRM* lphMidiStrm, LPUINT lpuDeviceID, DWORD cMidi, DWORD_PTR dwCallback, DWORD_PTR dwInstance, DWORD fdwOpen)
{
    struct qemu_midiStreamOpen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDISTREAMOPEN);
    call.lphMidiStrm = (ULONG_PTR)lphMidiStrm;
    call.lpuDeviceID = (ULONG_PTR)lpuDeviceID;
    call.cMidi = (ULONG_PTR)cMidi;
    call.dwCallback = (ULONG_PTR)dwCallback;
    call.dwInstance = (ULONG_PTR)dwInstance;
    call.fdwOpen = (ULONG_PTR)fdwOpen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiStreamOpen(struct qemu_syscall *call)
{
    struct qemu_midiStreamOpen *c = (struct qemu_midiStreamOpen *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiStreamOpen(QEMU_G2H(c->lphMidiStrm), QEMU_G2H(c->lpuDeviceID), c->cMidi, c->dwCallback, c->dwInstance, c->fdwOpen);
}

#endif

struct qemu_midiStreamOut
{
    struct qemu_syscall super;
    uint64_t hMidiStrm;
    uint64_t lpMidiHdr;
    uint64_t cbMidiHdr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI midiStreamOut(HMIDISTRM hMidiStrm, LPMIDIHDR lpMidiHdr, UINT cbMidiHdr)
{
    struct qemu_midiStreamOut call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDISTREAMOUT);
    call.hMidiStrm = (ULONG_PTR)hMidiStrm;
    call.lpMidiHdr = (ULONG_PTR)lpMidiHdr;
    call.cbMidiHdr = (ULONG_PTR)cbMidiHdr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiStreamOut(struct qemu_syscall *call)
{
    struct qemu_midiStreamOut *c = (struct qemu_midiStreamOut *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiStreamOut(QEMU_G2H(c->hMidiStrm), QEMU_G2H(c->lpMidiHdr), c->cbMidiHdr);
}

#endif

struct qemu_midiStreamPause
{
    struct qemu_syscall super;
    uint64_t hMidiStrm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI midiStreamPause(HMIDISTRM hMidiStrm)
{
    struct qemu_midiStreamPause call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDISTREAMPAUSE);
    call.hMidiStrm = (ULONG_PTR)hMidiStrm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiStreamPause(struct qemu_syscall *call)
{
    struct qemu_midiStreamPause *c = (struct qemu_midiStreamPause *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiStreamPause(QEMU_G2H(c->hMidiStrm));
}

#endif

struct qemu_midiStreamPosition
{
    struct qemu_syscall super;
    uint64_t hMidiStrm;
    uint64_t lpMMT;
    uint64_t cbmmt;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI midiStreamPosition(HMIDISTRM hMidiStrm, LPMMTIME lpMMT, UINT cbmmt)
{
    struct qemu_midiStreamPosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDISTREAMPOSITION);
    call.hMidiStrm = (ULONG_PTR)hMidiStrm;
    call.lpMMT = (ULONG_PTR)lpMMT;
    call.cbmmt = (ULONG_PTR)cbmmt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiStreamPosition(struct qemu_syscall *call)
{
    struct qemu_midiStreamPosition *c = (struct qemu_midiStreamPosition *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiStreamPosition(QEMU_G2H(c->hMidiStrm), QEMU_G2H(c->lpMMT), c->cbmmt);
}

#endif

struct qemu_midiStreamProperty
{
    struct qemu_syscall super;
    uint64_t hMidiStrm;
    uint64_t lpPropData;
    uint64_t dwProperty;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI midiStreamProperty(HMIDISTRM hMidiStrm, LPBYTE lpPropData, DWORD dwProperty)
{
    struct qemu_midiStreamProperty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDISTREAMPROPERTY);
    call.hMidiStrm = (ULONG_PTR)hMidiStrm;
    call.lpPropData = (ULONG_PTR)lpPropData;
    call.dwProperty = (ULONG_PTR)dwProperty;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiStreamProperty(struct qemu_syscall *call)
{
    struct qemu_midiStreamProperty *c = (struct qemu_midiStreamProperty *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiStreamProperty(QEMU_G2H(c->hMidiStrm), QEMU_G2H(c->lpPropData), c->dwProperty);
}

#endif

struct qemu_midiStreamRestart
{
    struct qemu_syscall super;
    uint64_t hMidiStrm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI midiStreamRestart(HMIDISTRM hMidiStrm)
{
    struct qemu_midiStreamRestart call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDISTREAMRESTART);
    call.hMidiStrm = (ULONG_PTR)hMidiStrm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiStreamRestart(struct qemu_syscall *call)
{
    struct qemu_midiStreamRestart *c = (struct qemu_midiStreamRestart *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiStreamRestart(QEMU_G2H(c->hMidiStrm));
}

#endif

struct qemu_midiStreamStop
{
    struct qemu_syscall super;
    uint64_t hMidiStrm;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI midiStreamStop(HMIDISTRM hMidiStrm)
{
    struct qemu_midiStreamStop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MIDISTREAMSTOP);
    call.hMidiStrm = (ULONG_PTR)hMidiStrm;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_midiStreamStop(struct qemu_syscall *call)
{
    struct qemu_midiStreamStop *c = (struct qemu_midiStreamStop *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = midiStreamStop(QEMU_G2H(c->hMidiStrm));
}

#endif

struct qemu_mmTaskCreate
{
    struct qemu_syscall super;
    uint64_t cb;
    uint64_t ph;
    uint64_t client;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI mmTaskCreate(void *cb, HANDLE* ph, DWORD_PTR client)
{
    struct qemu_mmTaskCreate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMTASKCREATE);
    call.cb = (ULONG_PTR)cb;
    call.ph = (ULONG_PTR)ph;
    call.client = (ULONG_PTR)client;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmTaskCreate(struct qemu_syscall *call)
{
    struct qemu_mmTaskCreate *c = (struct qemu_mmTaskCreate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mmTaskCreate(QEMU_G2H(c->cb), QEMU_G2H(c->ph), c->client);
}

#endif

struct qemu_mmTaskBlock
{
    struct qemu_syscall super;
    uint64_t tid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI mmTaskBlock(DWORD tid)
{
    struct qemu_mmTaskBlock call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMTASKBLOCK);
    call.tid = (ULONG_PTR)tid;

    qemu_syscall(&call.super);
}

#else

void qemu_mmTaskBlock(struct qemu_syscall *call)
{
    struct qemu_mmTaskBlock *c = (struct qemu_mmTaskBlock *)call;
    WINE_FIXME("Unverified!\n");
    mmTaskBlock(c->tid);
}

#endif

struct qemu_mmTaskSignal
{
    struct qemu_syscall super;
    uint64_t tid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI mmTaskSignal(DWORD tid)
{
    struct qemu_mmTaskSignal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMTASKSIGNAL);
    call.tid = (ULONG_PTR)tid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmTaskSignal(struct qemu_syscall *call)
{
    struct qemu_mmTaskSignal *c = (struct qemu_mmTaskSignal *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mmTaskSignal(c->tid);
}

#endif

struct qemu_mmTaskYield
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI mmTaskYield(VOID)
{
    struct qemu_mmTaskYield call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMTASKYIELD);

    qemu_syscall(&call.super);
}

#else

void qemu_mmTaskYield(struct qemu_syscall *call)
{
    struct qemu_mmTaskYield *c = (struct qemu_mmTaskYield *)call;
    WINE_FIXME("Unverified!\n");
    mmTaskYield();
}

#endif

struct qemu_mmGetCurrentTask
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI mmGetCurrentTask(VOID)
{
    struct qemu_mmGetCurrentTask call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMGETCURRENTTASK);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmGetCurrentTask(struct qemu_syscall *call)
{
    struct qemu_mmGetCurrentTask *c = (struct qemu_mmGetCurrentTask *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mmGetCurrentTask();
}

#endif

