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
#include <wininet.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_wininet.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_wininet);
#endif


struct qemu_InternetErrorDlg
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t hRequest;
    uint64_t dwError;
    uint64_t dwFlags;
    uint64_t lppvData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI InternetErrorDlg(HWND hWnd, HINTERNET hRequest, DWORD dwError, DWORD dwFlags, LPVOID* lppvData)
{
    struct qemu_InternetErrorDlg call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETERRORDLG);
    call.hWnd = (ULONG_PTR)hWnd;
    call.hRequest = (ULONG_PTR)hRequest;
    call.dwError = (ULONG_PTR)dwError;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.lppvData = (ULONG_PTR)lppvData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InternetErrorDlg(struct qemu_syscall *call)
{
    struct qemu_InternetErrorDlg *c = (struct qemu_InternetErrorDlg *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetErrorDlg(QEMU_G2H(c->hWnd), QEMU_G2H(c->hRequest), c->dwError, c->dwFlags, QEMU_G2H(c->lppvData));
}

#endif

struct qemu_InternetShowSecurityInfoByURLA
{
    struct qemu_syscall super;
    uint64_t url;
    uint64_t window;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetShowSecurityInfoByURLA(LPCSTR url, HWND window)
{
    struct qemu_InternetShowSecurityInfoByURLA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSHOWSECURITYINFOBYURLA);
    call.url = (ULONG_PTR)url;
    call.window = (ULONG_PTR)window;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add InternetShowSecurityInfoByURLA to Wine headers? */
extern BOOL WINAPI InternetShowSecurityInfoByURLA(LPCSTR url, HWND window);
void qemu_InternetShowSecurityInfoByURLA(struct qemu_syscall *call)
{
    struct qemu_InternetShowSecurityInfoByURLA *c = (struct qemu_InternetShowSecurityInfoByURLA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetShowSecurityInfoByURLA(QEMU_G2H(c->url), QEMU_G2H(c->window));
}

#endif

struct qemu_InternetShowSecurityInfoByURLW
{
    struct qemu_syscall super;
    uint64_t url;
    uint64_t window;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI InternetShowSecurityInfoByURLW(LPCWSTR url, HWND window)
{
    struct qemu_InternetShowSecurityInfoByURLW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INTERNETSHOWSECURITYINFOBYURLW);
    call.url = (ULONG_PTR)url;
    call.window = (ULONG_PTR)window;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add InternetShowSecurityInfoByURLW to Wine headers? */
extern BOOL WINAPI InternetShowSecurityInfoByURLW(LPCWSTR url, HWND window);
void qemu_InternetShowSecurityInfoByURLW(struct qemu_syscall *call)
{
    struct qemu_InternetShowSecurityInfoByURLW *c = (struct qemu_InternetShowSecurityInfoByURLW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = InternetShowSecurityInfoByURLW(QEMU_G2H(c->url), QEMU_G2H(c->window));
}

#endif

struct qemu_ShowX509EncodedCertificate
{
    struct qemu_syscall super;
    uint64_t parent;
    uint64_t cert;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI ShowX509EncodedCertificate(HWND parent, LPBYTE cert, DWORD len)
{
    struct qemu_ShowX509EncodedCertificate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHOWX509ENCODEDCERTIFICATE);
    call.parent = (ULONG_PTR)parent;
    call.cert = (ULONG_PTR)cert;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ShowX509EncodedCertificate to Wine headers? */
extern DWORD WINAPI ShowX509EncodedCertificate(HWND parent, LPBYTE cert, DWORD len);
void qemu_ShowX509EncodedCertificate(struct qemu_syscall *call)
{
    struct qemu_ShowX509EncodedCertificate *c = (struct qemu_ShowX509EncodedCertificate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ShowX509EncodedCertificate(QEMU_G2H(c->parent), QEMU_G2H(c->cert), c->len);
}

#endif

