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
#include <mswsock.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "wsock32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_wsock32);
#endif


struct qemu_WS1_setsockopt
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t level;
    uint64_t optname;
    uint64_t optval;
    uint64_t optlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WS1_setsockopt(SOCKET s, INT level, INT optname, char *optval, INT optlen)
{
    struct qemu_WS1_setsockopt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS1_SETSOCKOPT);
    call.s = (uint64_t)s;
    call.level = (uint64_t)level;
    call.optname = (uint64_t)optname;
    call.optval = (uint64_t)optval;
    call.optlen = (uint64_t)optlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS1_setsockopt(struct qemu_syscall *call)
{
    struct qemu_WS1_setsockopt *c = (struct qemu_WS1_setsockopt *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_setsockopt(c->s, c->level, c->optname, QEMU_G2H(c->optval), c->optlen);
}

#endif

struct qemu_WS1_getsockopt
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t level;
    uint64_t optname;
    uint64_t optval;
    uint64_t optlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WS1_getsockopt(SOCKET s, INT level, INT optname, char *optval, INT *optlen)
{
    struct qemu_WS1_getsockopt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS1_GETSOCKOPT);
    call.s = (uint64_t)s;
    call.level = (uint64_t)level;
    call.optname = (uint64_t)optname;
    call.optval = (uint64_t)optval;
    call.optlen = (uint64_t)optlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS1_getsockopt(struct qemu_syscall *call)
{
    struct qemu_WS1_getsockopt *c = (struct qemu_WS1_getsockopt *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_getsockopt(c->s, c->level, c->optname, QEMU_G2H(c->optval), QEMU_G2H(c->optlen));
}

#endif

struct qemu_WsControl
{
    struct qemu_syscall super;
    uint64_t protocol;
    uint64_t action;
    uint64_t pRequestInfo;
    uint64_t pcbRequestInfoLen;
    uint64_t pResponseInfo;
    uint64_t pcbResponseInfoLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI WsControl(DWORD protocol, DWORD action, LPVOID pRequestInfo, LPDWORD pcbRequestInfoLen, LPVOID pResponseInfo, LPDWORD pcbResponseInfoLen)
{
    struct qemu_WsControl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSCONTROL);
    call.protocol = (uint64_t)protocol;
    call.action = (uint64_t)action;
    call.pRequestInfo = (uint64_t)pRequestInfo;
    call.pcbRequestInfoLen = (uint64_t)pcbRequestInfoLen;
    call.pResponseInfo = (uint64_t)pResponseInfo;
    call.pcbResponseInfoLen = (uint64_t)pcbResponseInfoLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WsControl(struct qemu_syscall *call)
{
    struct qemu_WsControl *c = (struct qemu_WsControl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_WsControl(c->protocol, c->action, QEMU_G2H(c->pRequestInfo), QEMU_G2H(c->pcbRequestInfoLen), QEMU_G2H(c->pResponseInfo), QEMU_G2H(c->pcbResponseInfoLen));
}

#endif

struct qemu_WSARecvEx
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t buf;
    uint64_t len;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSARecvEx(SOCKET s, char *buf, INT len, INT *flags)
{
    struct qemu_WSARecvEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSARECVEX);
    call.s = (uint64_t)s;
    call.buf = (uint64_t)buf;
    call.len = (uint64_t)len;
    call.flags = (uint64_t)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add WSARecvEx to Wine headers? */
// extern INT WINAPI WSARecvEx(SOCKET s, char *buf, INT len, INT *flags);
void qemu_WSARecvEx(struct qemu_syscall *call)
{
    struct qemu_WSARecvEx *c = (struct qemu_WSARecvEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSARecvEx(c->s, QEMU_G2H(c->buf), c->len, QEMU_G2H(c->flags));
}

#endif

struct qemu_s_perror
{
    struct qemu_syscall super;
    uint64_t message;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI s_perror(LPCSTR message)
{
    struct qemu_s_perror call;
    call.super.id = QEMU_SYSCALL_ID(CALL_S_PERROR);
    call.message = (uint64_t)message;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add s_perror to Wine headers? */
// extern void WINAPI s_perror(LPCSTR message);
void qemu_s_perror(struct qemu_syscall *call)
{
    struct qemu_s_perror *c = (struct qemu_s_perror *)call;
    WINE_FIXME("Unverified!\n");
    s_perror(QEMU_G2H(c->message));
}

#endif

