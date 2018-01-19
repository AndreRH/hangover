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

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <winsock.h>
#include <ws2tcpip.h>
#include <ws2spi.h>
#include <mswsock.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ws2_32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ws2_32);
#endif


struct qemu_WSAAsyncGetHostByAddr
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t uMsg;
    uint64_t addr;
    uint64_t len;
    uint64_t type;
    uint64_t sbuf;
    uint64_t buflen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI WSAAsyncGetHostByAddr(HWND hWnd, UINT uMsg, LPCSTR addr, INT len, INT type, LPSTR sbuf, INT buflen)
{
    struct qemu_WSAAsyncGetHostByAddr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAASYNCGETHOSTBYADDR);
    call.hWnd = (ULONG_PTR)hWnd;
    call.uMsg = (ULONG_PTR)uMsg;
    call.addr = (ULONG_PTR)addr;
    call.len = (ULONG_PTR)len;
    call.type = (ULONG_PTR)type;
    call.sbuf = (ULONG_PTR)sbuf;
    call.buflen = (ULONG_PTR)buflen;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WSAAsyncGetHostByAddr(struct qemu_syscall *call)
{
    struct qemu_WSAAsyncGetHostByAddr *c = (struct qemu_WSAAsyncGetHostByAddr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)WSAAsyncGetHostByAddr(QEMU_G2H(c->hWnd), c->uMsg, QEMU_G2H(c->addr), c->len, c->type, QEMU_G2H(c->sbuf), c->buflen);
}

#endif

struct qemu_WSAAsyncGetHostByName
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t uMsg;
    uint64_t name;
    uint64_t sbuf;
    uint64_t buflen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI WSAAsyncGetHostByName(HWND hWnd, UINT uMsg, LPCSTR name, LPSTR sbuf, INT buflen)
{
    struct qemu_WSAAsyncGetHostByName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAASYNCGETHOSTBYNAME);
    call.hWnd = (ULONG_PTR)hWnd;
    call.uMsg = (ULONG_PTR)uMsg;
    call.name = (ULONG_PTR)name;
    call.sbuf = (ULONG_PTR)sbuf;
    call.buflen = (ULONG_PTR)buflen;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WSAAsyncGetHostByName(struct qemu_syscall *call)
{
    struct qemu_WSAAsyncGetHostByName *c = (struct qemu_WSAAsyncGetHostByName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)WSAAsyncGetHostByName(QEMU_G2H(c->hWnd), c->uMsg, QEMU_G2H(c->name), QEMU_G2H(c->sbuf), c->buflen);
}

#endif

struct qemu_WSAAsyncGetProtoByName
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t uMsg;
    uint64_t name;
    uint64_t sbuf;
    uint64_t buflen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI WSAAsyncGetProtoByName(HWND hWnd, UINT uMsg, LPCSTR name, LPSTR sbuf, INT buflen)
{
    struct qemu_WSAAsyncGetProtoByName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAASYNCGETPROTOBYNAME);
    call.hWnd = (ULONG_PTR)hWnd;
    call.uMsg = (ULONG_PTR)uMsg;
    call.name = (ULONG_PTR)name;
    call.sbuf = (ULONG_PTR)sbuf;
    call.buflen = (ULONG_PTR)buflen;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WSAAsyncGetProtoByName(struct qemu_syscall *call)
{
    struct qemu_WSAAsyncGetProtoByName *c = (struct qemu_WSAAsyncGetProtoByName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)WSAAsyncGetProtoByName(QEMU_G2H(c->hWnd), c->uMsg, QEMU_G2H(c->name), QEMU_G2H(c->sbuf), c->buflen);
}

#endif

struct qemu_WSAAsyncGetProtoByNumber
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t uMsg;
    uint64_t number;
    uint64_t sbuf;
    uint64_t buflen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI WSAAsyncGetProtoByNumber(HWND hWnd, UINT uMsg, INT number, LPSTR sbuf, INT buflen)
{
    struct qemu_WSAAsyncGetProtoByNumber call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAASYNCGETPROTOBYNUMBER);
    call.hWnd = (ULONG_PTR)hWnd;
    call.uMsg = (ULONG_PTR)uMsg;
    call.number = (ULONG_PTR)number;
    call.sbuf = (ULONG_PTR)sbuf;
    call.buflen = (ULONG_PTR)buflen;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WSAAsyncGetProtoByNumber(struct qemu_syscall *call)
{
    struct qemu_WSAAsyncGetProtoByNumber *c = (struct qemu_WSAAsyncGetProtoByNumber *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)WSAAsyncGetProtoByNumber(QEMU_G2H(c->hWnd), c->uMsg, c->number, QEMU_G2H(c->sbuf), c->buflen);
}

#endif

struct qemu_WSAAsyncGetServByName
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t uMsg;
    uint64_t name;
    uint64_t proto;
    uint64_t sbuf;
    uint64_t buflen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI WSAAsyncGetServByName(HWND hWnd, UINT uMsg, LPCSTR name, LPCSTR proto, LPSTR sbuf, INT buflen)
{
    struct qemu_WSAAsyncGetServByName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAASYNCGETSERVBYNAME);
    call.hWnd = (ULONG_PTR)hWnd;
    call.uMsg = (ULONG_PTR)uMsg;
    call.name = (ULONG_PTR)name;
    call.proto = (ULONG_PTR)proto;
    call.sbuf = (ULONG_PTR)sbuf;
    call.buflen = (ULONG_PTR)buflen;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WSAAsyncGetServByName(struct qemu_syscall *call)
{
    struct qemu_WSAAsyncGetServByName *c = (struct qemu_WSAAsyncGetServByName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)WSAAsyncGetServByName(QEMU_G2H(c->hWnd), c->uMsg, QEMU_G2H(c->name), QEMU_G2H(c->proto), QEMU_G2H(c->sbuf), c->buflen);
}

#endif

struct qemu_WSAAsyncGetServByPort
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t uMsg;
    uint64_t port;
    uint64_t proto;
    uint64_t sbuf;
    uint64_t buflen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI WSAAsyncGetServByPort(HWND hWnd, UINT uMsg, INT port, LPCSTR proto, LPSTR sbuf, INT buflen)
{
    struct qemu_WSAAsyncGetServByPort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAASYNCGETSERVBYPORT);
    call.hWnd = (ULONG_PTR)hWnd;
    call.uMsg = (ULONG_PTR)uMsg;
    call.port = (ULONG_PTR)port;
    call.proto = (ULONG_PTR)proto;
    call.sbuf = (ULONG_PTR)sbuf;
    call.buflen = (ULONG_PTR)buflen;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WSAAsyncGetServByPort(struct qemu_syscall *call)
{
    struct qemu_WSAAsyncGetServByPort *c = (struct qemu_WSAAsyncGetServByPort *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)WSAAsyncGetServByPort(QEMU_G2H(c->hWnd), c->uMsg, c->port, QEMU_G2H(c->proto), QEMU_G2H(c->sbuf), c->buflen);
}

#endif

struct qemu_WSACancelAsyncRequest
{
    struct qemu_syscall super;
    uint64_t hAsyncTaskHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSACancelAsyncRequest(HANDLE hAsyncTaskHandle)
{
    struct qemu_WSACancelAsyncRequest call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSACANCELASYNCREQUEST);
    call.hAsyncTaskHandle = (ULONG_PTR)hAsyncTaskHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSACancelAsyncRequest(struct qemu_syscall *call)
{
    struct qemu_WSACancelAsyncRequest *c = (struct qemu_WSACancelAsyncRequest *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSACancelAsyncRequest(QEMU_G2H(c->hAsyncTaskHandle));
}

#endif

struct qemu_WSApSetPostRoutine
{
    struct qemu_syscall super;
    uint64_t lpPostRoutine;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSApSetPostRoutine(LPWPUPOSTMESSAGE lpPostRoutine)
{
    struct qemu_WSApSetPostRoutine call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAPSETPOSTROUTINE);
    call.lpPostRoutine = (ULONG_PTR)lpPostRoutine;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add WSApSetPostRoutine to Wine headers? */
extern INT WINAPI WSApSetPostRoutine(LPWPUPOSTMESSAGE lpPostRoutine);
void qemu_WSApSetPostRoutine(struct qemu_syscall *call)
{
    struct qemu_WSApSetPostRoutine *c = (struct qemu_WSApSetPostRoutine *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSApSetPostRoutine(QEMU_G2H(c->lpPostRoutine));
}

#endif

struct qemu_WPUCompleteOverlappedRequest
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t overlapped;
    uint64_t error;
    uint64_t transferred;
    uint64_t errcode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WPUCompleteOverlappedRequest(SOCKET s, LPWSAOVERLAPPED overlapped, DWORD error, DWORD transferred, LPINT errcode)
{
    struct qemu_WPUCompleteOverlappedRequest call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WPUCOMPLETEOVERLAPPEDREQUEST);
    call.s = (ULONG_PTR)s;
    call.overlapped = (ULONG_PTR)overlapped;
    call.error = (ULONG_PTR)error;
    call.transferred = (ULONG_PTR)transferred;
    call.errcode = (ULONG_PTR)errcode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WPUCompleteOverlappedRequest(struct qemu_syscall *call)
{
    struct qemu_WPUCompleteOverlappedRequest *c = (struct qemu_WPUCompleteOverlappedRequest *)call;
    WINE_FIXME("Unverified!\n");
    /* FIXME: Wine defines the return value as WSAEVENT, aka void *, mingw as int. */
    c->super.iret = (ULONG_PTR)WPUCompleteOverlappedRequest(c->s, QEMU_G2H(c->overlapped), c->error, c->transferred, QEMU_G2H(c->errcode));
}

#endif

