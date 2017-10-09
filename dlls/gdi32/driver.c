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
#include "qemu_gdi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_gdi32);
#endif


struct qemu_GdiConvertToDevmodeW
{
    struct qemu_syscall super;
    uint64_t dmA;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DEVMODEW * WINAPI GdiConvertToDevmodeW(const DEVMODEA *dmA)
{
    struct qemu_GdiConvertToDevmodeW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GDICONVERTTODEVMODEW);
    call.dmA = (ULONG_PTR)dmA;

    qemu_syscall(&call.super);

    return (DEVMODEW *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_GdiConvertToDevmodeW(struct qemu_syscall *call)
{
    struct qemu_GdiConvertToDevmodeW *c = (struct qemu_GdiConvertToDevmodeW *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(GdiConvertToDevmodeW(QEMU_G2H(c->dmA)));
}

#endif

struct qemu_Escape
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t escape;
    uint64_t in_count;
    uint64_t in_data;
    uint64_t out_data;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI Escape(HDC hdc, INT escape, INT in_count, LPCSTR in_data, LPVOID out_data)
{
    struct qemu_Escape call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ESCAPE);
    call.hdc = (ULONG_PTR)hdc;
    call.escape = (ULONG_PTR)escape;
    call.in_count = (ULONG_PTR)in_count;
    call.in_data = (ULONG_PTR)in_data;
    call.out_data = (ULONG_PTR)out_data;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Escape(struct qemu_syscall *call)
{
    struct qemu_Escape *c = (struct qemu_Escape *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Escape(QEMU_G2H(c->hdc), c->escape, c->in_count, QEMU_G2H(c->in_data), QEMU_G2H(c->out_data));
}

#endif

struct qemu_ExtEscape
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t nEscape;
    uint64_t cbInput;
    uint64_t lpszInData;
    uint64_t cbOutput;
    uint64_t lpszOutData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI ExtEscape(HDC hdc, INT nEscape, INT cbInput, LPCSTR lpszInData, INT cbOutput, LPSTR lpszOutData)
{
    struct qemu_ExtEscape call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTESCAPE);
    call.hdc = (ULONG_PTR)hdc;
    call.nEscape = (ULONG_PTR)nEscape;
    call.cbInput = (ULONG_PTR)cbInput;
    call.lpszInData = (ULONG_PTR)lpszInData;
    call.cbOutput = (ULONG_PTR)cbOutput;
    call.lpszOutData = (ULONG_PTR)lpszOutData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExtEscape(struct qemu_syscall *call)
{
    struct qemu_ExtEscape *c = (struct qemu_ExtEscape *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ExtEscape(QEMU_G2H(c->hdc), c->nEscape, c->cbInput, QEMU_G2H(c->lpszInData), c->cbOutput, QEMU_G2H(c->lpszOutData));
}

#endif

struct qemu_DrawEscape
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t nEscape;
    uint64_t cbInput;
    uint64_t lpszInData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI DrawEscape(HDC hdc, INT nEscape, INT cbInput, LPCSTR lpszInData)
{
    struct qemu_DrawEscape call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAWESCAPE);
    call.hdc = (ULONG_PTR)hdc;
    call.nEscape = (ULONG_PTR)nEscape;
    call.cbInput = (ULONG_PTR)cbInput;
    call.lpszInData = (ULONG_PTR)lpszInData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DrawEscape(struct qemu_syscall *call)
{
    struct qemu_DrawEscape *c = (struct qemu_DrawEscape *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DrawEscape(QEMU_G2H(c->hdc), c->nEscape, c->cbInput, QEMU_G2H(c->lpszInData));
}

#endif

struct qemu_NamedEscape
{
    struct qemu_syscall super;
    uint64_t hdc;
    uint64_t pDriver;
    uint64_t nEscape;
    uint64_t cbInput;
    uint64_t lpszInData;
    uint64_t cbOutput;
    uint64_t lpszOutData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI NamedEscape(HDC hdc, LPCWSTR pDriver, INT nEscape, INT cbInput, LPCSTR lpszInData, INT cbOutput, LPSTR lpszOutData)
{
    struct qemu_NamedEscape call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NAMEDESCAPE);
    call.hdc = (ULONG_PTR)hdc;
    call.pDriver = (ULONG_PTR)pDriver;
    call.nEscape = (ULONG_PTR)nEscape;
    call.cbInput = (ULONG_PTR)cbInput;
    call.lpszInData = (ULONG_PTR)lpszInData;
    call.cbOutput = (ULONG_PTR)cbOutput;
    call.lpszOutData = (ULONG_PTR)lpszOutData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add NamedEscape to Wine headers? */
extern INT WINAPI NamedEscape(HDC hdc, LPCWSTR pDriver, INT nEscape, INT cbInput, LPCSTR lpszInData, INT cbOutput, LPSTR lpszOutData);
void qemu_NamedEscape(struct qemu_syscall *call)
{
    struct qemu_NamedEscape *c = (struct qemu_NamedEscape *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NamedEscape(QEMU_G2H(c->hdc), QEMU_G2H(c->pDriver), c->nEscape, c->cbInput, QEMU_G2H(c->lpszInData), c->cbOutput, QEMU_G2H(c->lpszOutData));
}

#endif

struct qemu_D3DKMTOpenAdapterFromHdc
{
    struct qemu_syscall super;
    uint64_t pData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI D3DKMTOpenAdapterFromHdc(void *pData)
{
    struct qemu_D3DKMTOpenAdapterFromHdc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DKMTOPENADAPTERFROMHDC);
    call.pData = (ULONG_PTR)pData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add D3DKMTOpenAdapterFromHdc to Wine headers? */
extern NTSTATUS WINAPI D3DKMTOpenAdapterFromHdc(void *pData);
void qemu_D3DKMTOpenAdapterFromHdc(struct qemu_syscall *call)
{
    struct qemu_D3DKMTOpenAdapterFromHdc *c = (struct qemu_D3DKMTOpenAdapterFromHdc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = D3DKMTOpenAdapterFromHdc(QEMU_G2H(c->pData));
}

#endif

struct qemu_D3DKMTEscape
{
    struct qemu_syscall super;
    uint64_t pData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI D3DKMTEscape(const void *pData)
{
    struct qemu_D3DKMTEscape call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DKMTESCAPE);
    call.pData = (ULONG_PTR)pData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add D3DKMTEscape to Wine headers? */
extern NTSTATUS WINAPI D3DKMTEscape(const void *pData);
void qemu_D3DKMTEscape(struct qemu_syscall *call)
{
    struct qemu_D3DKMTEscape *c = (struct qemu_D3DKMTEscape *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = D3DKMTEscape(QEMU_G2H(c->pData));
}

#endif

