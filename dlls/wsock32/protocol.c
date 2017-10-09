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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_wsock32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_wsock32);
#endif


struct qemu_WSOCK32_inet_network
{
    struct qemu_syscall super;
    uint64_t cp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI WSOCK32_inet_network(const char *cp)
{
    struct qemu_WSOCK32_inet_network call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSOCK32_INET_NETWORK);
    call.cp = (uint64_t)cp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSOCK32_inet_network(struct qemu_syscall *call)
{
    struct qemu_WSOCK32_inet_network *c = (struct qemu_WSOCK32_inet_network *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_inet_network(QEMU_G2H(c->cp));
}

#endif

struct qemu_WSOCK32_getnetbyname
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct netent * WINAPI WSOCK32_getnetbyname(const char *name)
{
    struct qemu_WSOCK32_getnetbyname call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSOCK32_GETNETBYNAME);
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return (struct netent *)call.super.iret;
}

#else

void qemu_WSOCK32_getnetbyname(struct qemu_syscall *call)
{
    struct qemu_WSOCK32_getnetbyname *c = (struct qemu_WSOCK32_getnetbyname *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_getnetbyname(QEMU_G2H(c->name)));
}

#endif

struct qemu_EnumProtocolsA
{
    struct qemu_syscall super;
    uint64_t protocols;
    uint64_t buffer;
    uint64_t buflen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI EnumProtocolsA(LPINT protocols, LPVOID buffer, LPDWORD buflen)
{
    struct qemu_EnumProtocolsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPROTOCOLSA);
    call.protocols = (uint64_t)protocols;
    call.buffer = (uint64_t)buffer;
    call.buflen = (uint64_t)buflen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumProtocolsA(struct qemu_syscall *call)
{
    struct qemu_EnumProtocolsA *c = (struct qemu_EnumProtocolsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_EnumProtocolsA(QEMU_G2H(c->protocols), QEMU_G2H(c->buffer), QEMU_G2H(c->buflen));
}

#endif

struct qemu_EnumProtocolsW
{
    struct qemu_syscall super;
    uint64_t protocols;
    uint64_t buffer;
    uint64_t buflen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI EnumProtocolsW(LPINT protocols, LPVOID buffer, LPDWORD buflen)
{
    struct qemu_EnumProtocolsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMPROTOCOLSW);
    call.protocols = (uint64_t)protocols;
    call.buffer = (uint64_t)buffer;
    call.buflen = (uint64_t)buflen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumProtocolsW(struct qemu_syscall *call)
{
    struct qemu_EnumProtocolsW *c = (struct qemu_EnumProtocolsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_EnumProtocolsW(QEMU_G2H(c->protocols), QEMU_G2H(c->buffer), QEMU_G2H(c->buflen));
}

#endif

