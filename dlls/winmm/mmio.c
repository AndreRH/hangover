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

/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */

#include <windows.h>
#include <stdio.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_winmm.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_winmm);
#endif

struct qemu_mmioOpen
{
    struct qemu_syscall super;
    uint64_t szFileName;
    uint64_t lpmmioinfo;
    uint64_t dwOpenFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HMMIO WINAPI mmioOpenW(LPWSTR szFileName, MMIOINFO* lpmmioinfo, DWORD dwOpenFlags)
{
    struct qemu_mmioOpen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOOPENW);
    call.szFileName = (ULONG_PTR)szFileName;
    call.lpmmioinfo = (ULONG_PTR)lpmmioinfo;
    call.dwOpenFlags = (ULONG_PTR)dwOpenFlags;

    qemu_syscall(&call.super);

    return (HMMIO)(ULONG_PTR)call.super.iret;
}

WINBASEAPI HMMIO WINAPI mmioOpenA(LPSTR szFileName, MMIOINFO* lpmmioinfo, DWORD dwOpenFlags)
{
    struct qemu_mmioOpen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOOPENA);
    call.szFileName = (ULONG_PTR)szFileName;
    call.lpmmioinfo = (ULONG_PTR)lpmmioinfo;
    call.dwOpenFlags = (ULONG_PTR)dwOpenFlags;

    qemu_syscall(&call.super);

    return (HMMIO)(ULONG_PTR)call.super.iret;
}

#else

void qemu_mmioOpen(struct qemu_syscall *call)
{
    struct qemu_mmioOpen *c = (struct qemu_mmioOpen *)call;
    MMIOINFO stack, *info = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->lpmmioinfo);
#else
    if (c->lpmmioinfo)
        MMIOINFO_g2h(info, QEMU_G2H(c->lpmmioinfo));
    else
        info = NULL;
#endif

    if (info && info->pIOProc)
        WINE_FIXME("pIOProc not handled, expect problems.\n");

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_MMIOOPENA):
            c->super.iret = (ULONG_PTR)mmioOpenA(QEMU_G2H(c->szFileName), info, c->dwOpenFlags);
            break;

        case QEMU_SYSCALL_ID(CALL_MMIOOPENW):
            c->super.iret = (ULONG_PTR)mmioOpenW(QEMU_G2H(c->szFileName), info, c->dwOpenFlags);
            break;
    }

#if GUEST_BIT != HOST_BIT
    /* Note that this function also writes on error. */
    if (info)
        MMIOINFO_h2g(QEMU_G2H(c->lpmmioinfo), info);
#endif
}

#endif

struct qemu_mmioClose
{
    struct qemu_syscall super;
    uint64_t hmmio;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI mmioClose(HMMIO hmmio, UINT uFlags)
{
    struct qemu_mmioClose call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOCLOSE);
    call.hmmio = (ULONG_PTR)hmmio;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioClose(struct qemu_syscall *call)
{
    struct qemu_mmioClose *c = (struct qemu_mmioClose *)call;
    WINE_TRACE("\n");
    c->super.iret = mmioClose(QEMU_G2H(c->hmmio), c->uFlags);
}

#endif

struct qemu_mmioRead
{
    struct qemu_syscall super;
    uint64_t hmmio;
    uint64_t pch;
    uint64_t cch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI mmioRead(HMMIO hmmio, HPSTR pch, LONG cch)
{
    struct qemu_mmioRead call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOREAD);
    call.hmmio = (ULONG_PTR)hmmio;
    call.pch = (ULONG_PTR)pch;
    call.cch = (ULONG_PTR)cch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioRead(struct qemu_syscall *call)
{
    struct qemu_mmioRead *c = (struct qemu_mmioRead *)call;
    WINE_TRACE("\n");
    c->super.iret = mmioRead(QEMU_G2H(c->hmmio), QEMU_G2H(c->pch), c->cch);
}

#endif

struct qemu_mmioWrite
{
    struct qemu_syscall super;
    uint64_t hmmio;
    uint64_t pch;
    uint64_t cch;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI mmioWrite(HMMIO hmmio, LPCSTR pch, LONG cch)
{
    struct qemu_mmioWrite call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOWRITE);
    call.hmmio = (ULONG_PTR)hmmio;
    call.pch = (ULONG_PTR)pch;
    call.cch = (ULONG_PTR)cch;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioWrite(struct qemu_syscall *call)
{
    struct qemu_mmioWrite *c = (struct qemu_mmioWrite *)call;
    WINE_TRACE("\n");
    c->super.iret = mmioWrite(QEMU_G2H(c->hmmio), QEMU_G2H(c->pch), c->cch);
}

#endif

struct qemu_mmioSeek
{
    struct qemu_syscall super;
    uint64_t hmmio;
    uint64_t lOffset;
    uint64_t iOrigin;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LONG WINAPI mmioSeek(HMMIO hmmio, LONG lOffset, INT iOrigin)
{
    struct qemu_mmioSeek call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOSEEK);
    call.hmmio = (ULONG_PTR)hmmio;
    call.lOffset = (ULONG_PTR)lOffset;
    call.iOrigin = (ULONG_PTR)iOrigin;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioSeek(struct qemu_syscall *call)
{
    struct qemu_mmioSeek *c = (struct qemu_mmioSeek *)call;
    WINE_TRACE("\n");
    c->super.iret = mmioSeek(QEMU_G2H(c->hmmio), c->lOffset, c->iOrigin);
}

#endif

struct qemu_mmioGetInfo
{
    struct qemu_syscall super;
    uint64_t hmmio;
    uint64_t lpmmioinfo;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI mmioGetInfo(HMMIO hmmio, MMIOINFO* lpmmioinfo, UINT uFlags)
{
    struct qemu_mmioGetInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOGETINFO);
    call.hmmio = (ULONG_PTR)hmmio;
    call.lpmmioinfo = (ULONG_PTR)lpmmioinfo;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioGetInfo(struct qemu_syscall *call)
{
    struct qemu_mmioGetInfo *c = (struct qemu_mmioGetInfo *)call;
    MMIOINFO stack, *info = &stack;

    WINE_TRACE("\n");
#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->lpmmioinfo);
#else
    if (c->lpmmioinfo)
        MMIOINFO_g2h(info, QEMU_G2H(c->lpmmioinfo));
    else
        info = NULL;
#endif

    c->super.iret = mmioGetInfo(QEMU_G2H(c->hmmio), info, c->uFlags);

#if GUEST_BIT != HOST_BIT
    if (c->super.iret == MMSYSERR_NOERROR)
        MMIOINFO_h2g(QEMU_G2H(c->lpmmioinfo), info);
#endif
}

#endif

struct qemu_mmioSetInfo
{
    struct qemu_syscall super;
    uint64_t hmmio;
    uint64_t lpmmioinfo;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI mmioSetInfo(HMMIO hmmio, const MMIOINFO* lpmmioinfo, UINT uFlags)
{
    struct qemu_mmioSetInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOSETINFO);
    call.hmmio = (ULONG_PTR)hmmio;
    call.lpmmioinfo = (ULONG_PTR)lpmmioinfo;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioSetInfo(struct qemu_syscall *call)
{
    struct qemu_mmioSetInfo *c = (struct qemu_mmioSetInfo *)call;
    MMIOINFO stack, *info = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->lpmmioinfo);
#else
    if (c->lpmmioinfo)
        MMIOINFO_g2h(info, QEMU_G2H(c->lpmmioinfo));
    else
        info = NULL;
#endif

    c->super.iret = mmioSetInfo(QEMU_G2H(c->hmmio), info, c->uFlags);
}

#endif

struct qemu_mmioSetBuffer
{
    struct qemu_syscall super;
    uint64_t hmmio;
    uint64_t pchBuffer;
    uint64_t cchBuffer;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI mmioSetBuffer(HMMIO hmmio, LPSTR pchBuffer, LONG cchBuffer, UINT uFlags)
{
    struct qemu_mmioSetBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOSETBUFFER);
    call.hmmio = (ULONG_PTR)hmmio;
    call.pchBuffer = (ULONG_PTR)pchBuffer;
    call.cchBuffer = (ULONG_PTR)cchBuffer;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioSetBuffer(struct qemu_syscall *call)
{
    struct qemu_mmioSetBuffer *c = (struct qemu_mmioSetBuffer *)call;
    WINE_TRACE("\n");
    c->super.iret = mmioSetBuffer(QEMU_G2H(c->hmmio), QEMU_G2H(c->pchBuffer), c->cchBuffer, c->uFlags);
}

#endif

struct qemu_mmioFlush
{
    struct qemu_syscall super;
    uint64_t hmmio;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI mmioFlush(HMMIO hmmio, UINT uFlags)
{
    struct qemu_mmioFlush call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOFLUSH);
    call.hmmio = (ULONG_PTR)hmmio;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioFlush(struct qemu_syscall *call)
{
    struct qemu_mmioFlush *c = (struct qemu_mmioFlush *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mmioFlush(QEMU_G2H(c->hmmio), c->uFlags);
}

#endif

struct qemu_mmioAdvance
{
    struct qemu_syscall super;
    uint64_t hmmio;
    uint64_t lpmmioinfo;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI mmioAdvance(HMMIO hmmio, MMIOINFO* lpmmioinfo, UINT uFlags)
{
    struct qemu_mmioAdvance call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOADVANCE);
    call.hmmio = (ULONG_PTR)hmmio;
    call.lpmmioinfo = (ULONG_PTR)lpmmioinfo;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioAdvance(struct qemu_syscall *call)
{
    struct qemu_mmioAdvance *c = (struct qemu_mmioAdvance *)call;
    MMIOINFO stack, *info = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    info = QEMU_G2H(c->lpmmioinfo);
#else
    if (c->lpmmioinfo)
        MMIOINFO_g2h(info, QEMU_G2H(c->lpmmioinfo));
    else
        info = NULL;
#endif

    c->super.iret = mmioAdvance(QEMU_G2H(c->hmmio), info, c->uFlags);

#if GUEST_BIT != HOST_BIT
    if (c->super.iret == MMSYSERR_NOERROR)
        MMIOINFO_h2g(QEMU_G2H(c->lpmmioinfo), info);
#endif
}

#endif

struct qemu_mmioStringToFOURCCA
{
    struct qemu_syscall super;
    uint64_t sz;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FOURCC WINAPI mmioStringToFOURCCA(LPCSTR sz, UINT uFlags)
{
    struct qemu_mmioStringToFOURCCA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOSTRINGTOFOURCCA);
    call.sz = (ULONG_PTR)sz;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioStringToFOURCCA(struct qemu_syscall *call)
{
    struct qemu_mmioStringToFOURCCA *c = (struct qemu_mmioStringToFOURCCA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mmioStringToFOURCCA(QEMU_G2H(c->sz), c->uFlags);
}

#endif

struct qemu_mmioStringToFOURCCW
{
    struct qemu_syscall super;
    uint64_t sz;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FOURCC WINAPI mmioStringToFOURCCW(LPCWSTR sz, UINT uFlags)
{
    struct qemu_mmioStringToFOURCCW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOSTRINGTOFOURCCW);
    call.sz = (ULONG_PTR)sz;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioStringToFOURCCW(struct qemu_syscall *call)
{
    struct qemu_mmioStringToFOURCCW *c = (struct qemu_mmioStringToFOURCCW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mmioStringToFOURCCW(QEMU_G2H(c->sz), c->uFlags);
}

#endif

struct qemu_mmioInstallIOProcA
{
    struct qemu_syscall super;
    uint64_t fccIOProc;
    uint64_t pIOProc;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPMMIOPROC WINAPI mmioInstallIOProcA(FOURCC fccIOProc, LPMMIOPROC pIOProc, DWORD dwFlags)
{
    struct qemu_mmioInstallIOProcA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOINSTALLIOPROCA);
    call.fccIOProc = (ULONG_PTR)fccIOProc;
    call.pIOProc = (ULONG_PTR)pIOProc;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return (LPMMIOPROC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_mmioInstallIOProcA(struct qemu_syscall *call)
{
    struct qemu_mmioInstallIOProcA *c = (struct qemu_mmioInstallIOProcA *)call;
    LPMMIOPROC host_proc;

    WINE_TRACE("\n");
    host_proc = ioproc_guest_to_host(c->pIOProc);
    host_proc = mmioInstallIOProcA(c->fccIOProc, host_proc, c->dwFlags);
    c->super.iret = ioproc_host_to_guest(host_proc);
}

#endif

struct qemu_mmioInstallIOProcW
{
    struct qemu_syscall super;
    uint64_t fccIOProc;
    uint64_t pIOProc;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPMMIOPROC WINAPI mmioInstallIOProcW(FOURCC fccIOProc, LPMMIOPROC pIOProc, DWORD dwFlags)
{
    struct qemu_mmioInstallIOProcW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOINSTALLIOPROCW);
    call.fccIOProc = (ULONG_PTR)fccIOProc;
    call.pIOProc = (ULONG_PTR)pIOProc;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return (LPMMIOPROC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_mmioInstallIOProcW(struct qemu_syscall *call)
{
    struct qemu_mmioInstallIOProcW *c = (struct qemu_mmioInstallIOProcW *)call;
    LPMMIOPROC host_proc;

    WINE_TRACE("\n");
    host_proc = ioproc_guest_to_host(c->pIOProc);
    host_proc = mmioInstallIOProcW(c->fccIOProc, host_proc, c->dwFlags);
    c->super.iret = ioproc_host_to_guest(host_proc);
}

#endif

struct qemu_mmioSendMessage
{
    struct qemu_syscall super;
    uint64_t hmmio;
    uint64_t uMessage;
    uint64_t lParam1;
    uint64_t lParam2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LRESULT WINAPI mmioSendMessage(HMMIO hmmio, UINT uMessage, LPARAM lParam1, LPARAM lParam2)
{
    struct qemu_mmioSendMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOSENDMESSAGE);
    call.hmmio = (ULONG_PTR)hmmio;
    call.uMessage = (ULONG_PTR)uMessage;
    call.lParam1 = (ULONG_PTR)lParam1;
    call.lParam2 = (ULONG_PTR)lParam2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioSendMessage(struct qemu_syscall *call)
{
    struct qemu_mmioSendMessage *c = (struct qemu_mmioSendMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mmioSendMessage(QEMU_G2H(c->hmmio), c->uMessage, c->lParam1, c->lParam2);
}

#endif

struct qemu_mmioDescend
{
    struct qemu_syscall super;
    uint64_t hmmio;
    uint64_t lpck;
    uint64_t lpckParent;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI mmioDescend(HMMIO hmmio, LPMMCKINFO lpck, const MMCKINFO* lpckParent, UINT uFlags)
{
    struct qemu_mmioDescend call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIODESCEND);
    call.hmmio = (ULONG_PTR)hmmio;
    call.lpck = (ULONG_PTR)lpck;
    call.lpckParent = (ULONG_PTR)lpckParent;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioDescend(struct qemu_syscall *call)
{
    struct qemu_mmioDescend *c = (struct qemu_mmioDescend *)call;
    WINE_TRACE("\n");
    /* MMCKINFO has the same size in 32 and 64 bit. */
    c->super.iret = mmioDescend(QEMU_G2H(c->hmmio), QEMU_G2H(c->lpck), QEMU_G2H(c->lpckParent), c->uFlags);
}

#endif

struct qemu_mmioAscend
{
    struct qemu_syscall super;
    uint64_t hmmio;
    uint64_t lpck;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI mmioAscend(HMMIO hmmio, LPMMCKINFO lpck, UINT uFlags)
{
    struct qemu_mmioAscend call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOASCEND);
    call.hmmio = (ULONG_PTR)hmmio;
    call.lpck = (ULONG_PTR)lpck;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioAscend(struct qemu_syscall *call)
{
    struct qemu_mmioAscend *c = (struct qemu_mmioAscend *)call;
    WINE_TRACE("\n");
    /* MMCKINFO has the same size on 32 and 64 bit. */
    c->super.iret = mmioAscend(QEMU_G2H(c->hmmio), QEMU_G2H(c->lpck), c->uFlags);
}

#endif

struct qemu_mmioCreateChunk
{
    struct qemu_syscall super;
    uint64_t hmmio;
    uint64_t lpck;
    uint64_t uFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI mmioCreateChunk(HMMIO hmmio, MMCKINFO* lpck, UINT uFlags)
{
    struct qemu_mmioCreateChunk call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIOCREATECHUNK);
    call.hmmio = (ULONG_PTR)hmmio;
    call.lpck = (ULONG_PTR)lpck;
    call.uFlags = (ULONG_PTR)uFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioCreateChunk(struct qemu_syscall *call)
{
    struct qemu_mmioCreateChunk *c = (struct qemu_mmioCreateChunk *)call;
    WINE_TRACE("\n");
    /* MMCKINFO has the same size on 32 and 64 bit. */
    c->super.iret = mmioCreateChunk(QEMU_G2H(c->hmmio), QEMU_G2H(c->lpck), c->uFlags);
}

#endif

struct qemu_mmioRenameA
{
    struct qemu_syscall super;
    uint64_t szFileName;
    uint64_t szNewFileName;
    uint64_t lpmmioinfo;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI mmioRenameA(LPCSTR szFileName, LPCSTR szNewFileName, const MMIOINFO* lpmmioinfo, DWORD dwFlags)
{
    struct qemu_mmioRenameA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIORENAMEA);
    call.szFileName = (ULONG_PTR)szFileName;
    call.szNewFileName = (ULONG_PTR)szNewFileName;
    call.lpmmioinfo = (ULONG_PTR)lpmmioinfo;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioRenameA(struct qemu_syscall *call)
{
    struct qemu_mmioRenameA *c = (struct qemu_mmioRenameA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mmioRenameA(QEMU_G2H(c->szFileName), QEMU_G2H(c->szNewFileName), QEMU_G2H(c->lpmmioinfo), c->dwFlags);
}

#endif

struct qemu_mmioRenameW
{
    struct qemu_syscall super;
    uint64_t szFileName;
    uint64_t szNewFileName;
    uint64_t lpmmioinfo;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI MMRESULT WINAPI mmioRenameW(LPCWSTR szFileName, LPCWSTR szNewFileName, const MMIOINFO* lpmmioinfo, DWORD dwFlags)
{
    struct qemu_mmioRenameW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_MMIORENAMEW);
    call.szFileName = (ULONG_PTR)szFileName;
    call.szNewFileName = (ULONG_PTR)szNewFileName;
    call.lpmmioinfo = (ULONG_PTR)lpmmioinfo;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_mmioRenameW(struct qemu_syscall *call)
{
    struct qemu_mmioRenameW *c = (struct qemu_mmioRenameW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = mmioRenameW(QEMU_G2H(c->szFileName), QEMU_G2H(c->szNewFileName), QEMU_G2H(c->lpmmioinfo), c->dwFlags);
}

#endif

