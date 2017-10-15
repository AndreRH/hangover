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
#include "qemu_gdi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);
#endif

struct qemu_GdiGetSpoolMessage
{
    struct qemu_syscall super;
    uint64_t ptr1;
    uint64_t data2;
    uint64_t ptr3;
    uint64_t data4;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GdiGetSpoolMessage(LPVOID ptr1, DWORD data2, LPVOID ptr3, DWORD data4)
{
    struct qemu_GdiGetSpoolMessage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIGETSPOOLMESSAGE);
    call.ptr1 = (ULONG_PTR)ptr1;
    call.data2 = (ULONG_PTR)data2;
    call.ptr3 = (ULONG_PTR)ptr3;
    call.data4 = (ULONG_PTR)data4;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GdiGetSpoolMessage to Wine headers? */
extern DWORD WINAPI GdiGetSpoolMessage(LPVOID ptr1, DWORD data2, LPVOID ptr3, DWORD data4);
void qemu_GdiGetSpoolMessage(struct qemu_syscall *call)
{
    struct qemu_GdiGetSpoolMessage *c = (struct qemu_GdiGetSpoolMessage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GdiGetSpoolMessage(QEMU_G2H(c->ptr1), c->data2, QEMU_G2H(c->ptr3), c->data4);
}

#endif

struct qemu_GdiInitSpool
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI DWORD WINAPI GdiInitSpool(void)
{
    struct qemu_GdiInitSpool call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDIINITSPOOL);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add GdiInitSpool to Wine headers? */
extern DWORD WINAPI GdiInitSpool(void);
void qemu_GdiInitSpool(struct qemu_syscall *call)
{
    struct qemu_GdiInitSpool *c = (struct qemu_GdiInitSpool *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GdiInitSpool();
}

#endif

struct qemu_StartDocW
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t doc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI StartDocW(HDC hdc, const DOCINFOW* doc)
{
    struct qemu_StartDocW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTDOCW);
    call.hdc = (ULONG_PTR)hdc;
    call.doc = (ULONG_PTR)doc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StartDocW(struct qemu_syscall *call)
{
    struct qemu_StartDocW *c = (struct qemu_StartDocW *)call;
    DOCINFOW stack, *ptr = &stack;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    ptr = QEMU_G2H(c->doc);
#else
    DOCINFO_g2h(ptr, QEMU_G2H(c->doc));
#endif

    c->super.iret = StartDocW(QEMU_G2H(c->hdc), ptr);
}

#endif

struct qemu_StartDocA
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t doc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI StartDocA(HDC hdc, const DOCINFOA* doc)
{
    struct qemu_StartDocA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTDOCA);
    call.hdc = (ULONG_PTR)hdc;
    call.doc = (ULONG_PTR)doc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StartDocA(struct qemu_syscall *call)
{
    struct qemu_StartDocA *c = (struct qemu_StartDocA *)call;
    DOCINFOA stack, *ptr = &stack;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    ptr = QEMU_G2H(c->doc);
#else
    DOCINFO_g2h((DOCINFOW *)ptr, QEMU_G2H(c->doc));
#endif

    c->super.iret = StartDocA(QEMU_G2H(c->hdc), ptr);
}

#endif

struct qemu_EndDoc
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI EndDoc(HDC hdc)
{
    struct qemu_EndDoc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENDDOC);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EndDoc(struct qemu_syscall *call)
{
    struct qemu_EndDoc *c = (struct qemu_EndDoc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EndDoc(QEMU_G2H(c->hdc));
}

#endif

struct qemu_StartPage
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI StartPage(HDC hdc)
{
    struct qemu_StartPage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_STARTPAGE);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_StartPage(struct qemu_syscall *call)
{
    struct qemu_StartPage *c = (struct qemu_StartPage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = StartPage(QEMU_G2H(c->hdc));
}

#endif

struct qemu_EndPage
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI EndPage(HDC hdc)
{
    struct qemu_EndPage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENDPAGE);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EndPage(struct qemu_syscall *call)
{
    struct qemu_EndPage *c = (struct qemu_EndPage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EndPage(QEMU_G2H(c->hdc));
}

#endif

struct qemu_AbortDoc
{
    struct qemu_syscall super;
    uint64_t hdc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI AbortDoc(HDC hdc)
{
    struct qemu_AbortDoc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ABORTDOC);
    call.hdc = (ULONG_PTR)hdc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_AbortDoc(struct qemu_syscall *call)
{
    struct qemu_AbortDoc *c = (struct qemu_AbortDoc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = AbortDoc(QEMU_G2H(c->hdc));
}

#endif

struct qemu_SetAbortProc
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t abrtprc;
};

#ifdef QEMU_DLL_GUEST

WINGDIAPI INT WINAPI SetAbortProc(HDC hdc, ABORTPROC abrtprc)
{
    struct qemu_SetAbortProc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SETABORTPROC);
    call.hdc = (ULONG_PTR)hdc;
    call.abrtprc = (ULONG_PTR)abrtprc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SetAbortProc(struct qemu_syscall *call)
{
    struct qemu_SetAbortProc *c = (struct qemu_SetAbortProc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SetAbortProc(QEMU_G2H(c->hdc), QEMU_G2H(c->abrtprc));
}

#endif

