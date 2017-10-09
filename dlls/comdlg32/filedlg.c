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
#include "qemu_comdlg32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comdlg32);
#endif

struct qemu_GetOpenSaveFileName
{
    struct qemu_syscall super;
    uint64_t ofn;
    uint64_t guest_wrapper;
};

struct qemu_GetOpenSaveFileName_cb
{
    uint64_t guest_proc;
    uint64_t dlg, msg, wp, lp;
};

#ifdef QEMU_DLL_GUEST

static uint64_t guest_wrapper(const struct qemu_GetOpenSaveFileName_cb *cb)
{
    LPOFNHOOKPROC guest_proc = (LPOFNHOOKPROC)cb->guest_proc;
    return guest_proc((HWND)cb->dlg, cb->msg, cb->wp, cb->lp);
}

WINBASEAPI BOOL WINAPI GetOpenFileNameA(OPENFILENAMEA *ofn)
{
    struct qemu_GetOpenSaveFileName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOPENFILENAMEA);
    call.ofn = (uint64_t)ofn;
    call.guest_wrapper = (uint64_t)guest_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI BOOL WINAPI GetOpenFileNameW(OPENFILENAMEW *ofn)
{
    struct qemu_GetOpenSaveFileName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETOPENFILENAMEW);
    call.ofn = (uint64_t)ofn;
    call.guest_wrapper = (uint64_t)guest_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI BOOL WINAPI GetSaveFileNameA(OPENFILENAMEA *ofn)
{
    struct qemu_GetOpenSaveFileName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSAVEFILENAMEA);
    call.ofn = (uint64_t)ofn;
    call.guest_wrapper = (uint64_t)guest_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI BOOL WINAPI GetSaveFileNameW(LPOPENFILENAMEW ofn)
{
    struct qemu_GetOpenSaveFileName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSAVEFILENAMEW);
    call.ofn = (uint64_t)ofn;
    call.guest_wrapper = (uint64_t)guest_wrapper;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static uint64_t guest_wrapper;

static UINT_PTR CALLBACK hook_proc_wrapper(HWND dlg, UINT msg, WPARAM wp, LPARAM lp)
{
    struct qemu_GetOpenSaveFileName_cb call;
    uint64_t *guest_proc = TlsGetValue(comdlg32_tls);
    UINT_PTR ret;

    WINE_TRACE("Calling guest proc 0x%lx(%p, %u, %lu, %lu).\n", *guest_proc, dlg, msg, wp, lp);
    call.guest_proc = *guest_proc;
    call.dlg = (uint64_t)dlg;
    call.msg = msg;
    call.wp = wp;
    call.lp = lp;

    ret = qemu_ops->qemu_execute(QEMU_G2H(guest_wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest proc returned %lu\n", ret);
    return ret;
}

void qemu_GetOpenSaveFileName(struct qemu_syscall *call)
{
    OPENFILENAMEA a;
    OPENFILENAMEW w;
    struct qemu_GetOpenSaveFileName *c = (struct qemu_GetOpenSaveFileName *)call;
    uint64_t guest_proc;
    WINE_TRACE("\n");

    /* This is easier than the user32 variant because the lifetime of the callback is limited until
     * Get{Open/Save}FileName returns. */

    if (c->super.id == QEMU_SYSCALL_ID(CALL_GETOPENFILENAMEA)
            || c->super.id == QEMU_SYSCALL_ID(CALL_GETSAVEFILENAMEA))
    {
        a = *(OPENFILENAMEA *)QEMU_G2H(c->ofn);
        guest_proc = (uint64_t)a.lpfnHook;
        a.lpfnHook = hook_proc_wrapper;
    }
    else
    {
        w = *(OPENFILENAMEW *)QEMU_G2H(c->ofn);
        guest_proc = (uint64_t)w.lpfnHook;
        w.lpfnHook = hook_proc_wrapper;
    }

    TlsSetValue(comdlg32_tls, &guest_proc);
    guest_wrapper = c->guest_wrapper;

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_GETOPENFILENAMEA):
            c->super.iret = GetOpenFileNameA(&a);
            break;

        case QEMU_SYSCALL_ID(CALL_GETOPENFILENAMEW):
            c->super.iret = GetOpenFileNameW(&w);
            break;

        case QEMU_SYSCALL_ID(CALL_GETSAVEFILENAMEA):
            c->super.iret = GetSaveFileNameA(&a);
            break;

        case QEMU_SYSCALL_ID(CALL_GETSAVEFILENAMEW):
            c->super.iret = GetSaveFileNameW(&w);
            break;
    }
}

#endif

struct qemu_GetSaveFileNameW
{
    struct qemu_syscall super;
    uint64_t ofn;
};

#ifdef QEMU_DLL_GUEST


#else


#endif

struct qemu_GetFileTitleA
{
    struct qemu_syscall super;
    uint64_t lpFile;
    uint64_t lpTitle;
    uint64_t cbBuf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI short WINAPI GetFileTitleA(LPCSTR lpFile, LPSTR lpTitle, WORD cbBuf)
{
    struct qemu_GetFileTitleA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILETITLEA);
    call.lpFile = (uint64_t)lpFile;
    call.lpTitle = (uint64_t)lpTitle;
    call.cbBuf = (uint64_t)cbBuf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileTitleA(struct qemu_syscall *call)
{
    struct qemu_GetFileTitleA *c = (struct qemu_GetFileTitleA *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFileTitleA(QEMU_G2H(c->lpFile), QEMU_G2H(c->lpTitle), c->cbBuf);
}

#endif

struct qemu_GetFileTitleW
{
    struct qemu_syscall super;
    uint64_t lpFile;
    uint64_t lpTitle;
    uint64_t cbBuf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI short WINAPI GetFileTitleW(LPCWSTR lpFile, LPWSTR lpTitle, WORD cbBuf)
{
    struct qemu_GetFileTitleW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETFILETITLEW);
    call.lpFile = (uint64_t)lpFile;
    call.lpTitle = (uint64_t)lpTitle;
    call.cbBuf = (uint64_t)cbBuf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetFileTitleW(struct qemu_syscall *call)
{
    struct qemu_GetFileTitleW *c = (struct qemu_GetFileTitleW *)call;
    WINE_TRACE("\n");
    c->super.iret = GetFileTitleW(QEMU_G2H(c->lpFile), QEMU_G2H(c->lpTitle), c->cbBuf);
}

#endif

