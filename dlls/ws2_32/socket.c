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
#include <wsnwlink.h>
#include <mstcpip.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_winsock2.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ws2_32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ws2_32);
#endif


struct qemu_WSAStartup
{
    struct qemu_syscall super;
    uint64_t wVersionRequested;
    uint64_t lpWSAData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData)
{
    struct qemu_WSAStartup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSASTARTUP);
    call.wVersionRequested = wVersionRequested;
    call.lpWSAData = (ULONG_PTR)lpWSAData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAStartup(struct qemu_syscall *call)
{
    struct qemu_WSAStartup *c = (struct qemu_WSAStartup *)call;
    WSADATA stack, *data = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    data = QEMU_G2H(c->lpWSAData);
#else
    if (c->lpWSAData)
        WSADATA_g2h(data, QEMU_G2H(c->lpWSAData));
    else
        data = NULL;
#endif

    c->super.iret = WSAStartup(c->wVersionRequested, data);
}

#endif

struct qemu_WSACleanup
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSACleanup(void)
{
    struct qemu_WSACleanup call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSACLEANUP);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSACleanup(struct qemu_syscall *call)
{
    struct qemu_WSACleanup *c = (struct qemu_WSACleanup *)call;
    WINE_TRACE("\n");
    c->super.iret = WSACleanup();
}

#endif

struct qemu_WSAGetLastError
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAGetLastError(void)
{
    struct qemu_WSAGetLastError call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAGETLASTERROR);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAGetLastError(struct qemu_syscall *call)
{
    struct qemu_WSAGetLastError *c = (struct qemu_WSAGetLastError *)call;
    WINE_TRACE("\n");
    c->super.iret = WSAGetLastError();
}

#endif

struct qemu_WSASetLastError
{
    struct qemu_syscall super;
    uint64_t iError;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI WSASetLastError(INT iError)
{
    struct qemu_WSASetLastError call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSASETLASTERROR);
    call.iError = iError;

    qemu_syscall(&call.super);
}

#else

void qemu_WSASetLastError(struct qemu_syscall *call)
{
    struct qemu_WSASetLastError *c = (struct qemu_WSASetLastError *)call;
    WINE_TRACE("\n");
    WSASetLastError(c->iError);
}

#endif

struct qemu_WS_accept
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t addr;
    uint64_t addrlen32;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SOCKET WINAPI WS_accept(SOCKET s, struct sockaddr *addr, int *addrlen32)
{
    struct qemu_WS_accept call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_ACCEPT);
    call.s = guest_SOCKET_g2h(s);
    call.addr = (ULONG_PTR)addr;
    call.addrlen32 = (ULONG_PTR)addrlen32;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_accept(struct qemu_syscall *call)
{
    struct qemu_WS_accept *c = (struct qemu_WS_accept *)call;
    WINE_TRACE("\n");

    /* WS_sockaddr has the same size in 32 and 64 bit. */
    c->super.iret = p_accept(c->s, QEMU_G2H(c->addr), QEMU_G2H(c->addrlen32));
}

#endif

struct qemu_WS_bind
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t name;
    uint64_t namelen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_bind(SOCKET s, const struct sockaddr* name, int namelen)
{
    struct qemu_WS_bind call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_BIND);
    call.s = guest_SOCKET_g2h(s);
    call.name = (ULONG_PTR)name;
    call.namelen = namelen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_bind(struct qemu_syscall *call)
{
    struct qemu_WS_bind *c = (struct qemu_WS_bind *)call;
    WINE_TRACE("\n");

    /* WS_sockaddr has the same size in 32 and 64 bit. */
    c->super.iret = p_bind(c->s, QEMU_G2H(c->name), c->namelen);
}

#endif

struct qemu_WS_closesocket
{
    struct qemu_syscall super;
    uint64_t s;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_closesocket(SOCKET s)
{
    struct qemu_WS_closesocket call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_CLOSESOCKET);
    call.s = guest_SOCKET_g2h(s);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_closesocket(struct qemu_syscall *call)
{
    struct qemu_WS_closesocket *c = (struct qemu_WS_closesocket *)call;
    WINE_TRACE("\n");
    c->super.iret = p_closesocket(c->s);
}

#endif

struct qemu_WS_connect
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t name;
    uint64_t namelen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_connect(SOCKET s, const struct sockaddr* name, int namelen)
{
    struct qemu_WS_connect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_CONNECT);
    call.s = guest_SOCKET_g2h(s);
    call.name = (ULONG_PTR)name;
    call.namelen = namelen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_connect(struct qemu_syscall *call)
{
    struct qemu_WS_connect *c = (struct qemu_WS_connect *)call;
    WINE_TRACE("\n");

    /* WS_sockaddr has the same size in 32 and 64 bit. */
    c->super.iret = p_connect(c->s, QEMU_G2H(c->name), c->namelen);
}

#endif

struct qemu_WSAConnect
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t name;
    uint64_t namelen;
    uint64_t lpCallerData;
    uint64_t lpCalleeData;
    uint64_t lpSQOS;
    uint64_t lpGQOS;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WSAConnect(SOCKET s, const struct sockaddr* name, int namelen, LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS)
{
    struct qemu_WSAConnect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSACONNECT);
    call.s = guest_SOCKET_g2h(s);
    call.name = (ULONG_PTR)name;
    call.namelen = (ULONG_PTR)namelen;
    call.lpCallerData = (ULONG_PTR)lpCallerData;
    call.lpCalleeData = (ULONG_PTR)lpCalleeData;
    call.lpSQOS = (ULONG_PTR)lpSQOS;
    call.lpGQOS = (ULONG_PTR)lpGQOS;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAConnect(struct qemu_syscall *call)
{
    struct qemu_WSAConnect *c = (struct qemu_WSAConnect *)call;
    WINE_FIXME("Unverified!\n");

    /* WS_sockaddr has the same size in 32 and 64 bit. */
    c->super.iret = WSAConnect(c->s, QEMU_G2H(c->name), c->namelen, QEMU_G2H(c->lpCallerData), QEMU_G2H(c->lpCalleeData), QEMU_G2H(c->lpSQOS), QEMU_G2H(c->lpGQOS));
}

#endif

struct qemu_WS_getpeername
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t name;
    uint64_t namelen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_getpeername(SOCKET s, struct sockaddr *name, int *namelen)
{
    struct qemu_WS_getpeername call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_GETPEERNAME);
    call.s = guest_SOCKET_g2h(s);
    call.name = (ULONG_PTR)name;
    call.namelen = (ULONG_PTR)namelen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_getpeername(struct qemu_syscall *call)
{
    struct qemu_WS_getpeername *c = (struct qemu_WS_getpeername *)call;
    WINE_TRACE("\n");

    /* WS_sockaddr has the same size in 32 and 64 bit. */
    c->super.iret = p_getpeername(c->s, QEMU_G2H(c->name), QEMU_G2H(c->namelen));
}

#endif

struct qemu_WS_getsockname
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t name;
    uint64_t namelen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_getsockname(SOCKET s, struct sockaddr *name, int *namelen)
{
    struct qemu_WS_getsockname call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_GETSOCKNAME);
    call.s = guest_SOCKET_g2h(s);
    call.name = (ULONG_PTR)name;
    call.namelen = (ULONG_PTR)namelen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_getsockname(struct qemu_syscall *call)
{
    struct qemu_WS_getsockname *c = (struct qemu_WS_getsockname *)call;
    WINE_TRACE("\n");

    /* WS_sockaddr has the same size in 32 and 64 bit. */
    c->super.iret = p_getsockname(c->s, QEMU_G2H(c->name), QEMU_G2H(c->namelen));
}

#endif

struct qemu_WS_getsockopt
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t level;
    uint64_t optname;
    uint64_t optval;
    uint64_t optlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WS_getsockopt(SOCKET s, INT level, INT optname, char *optval, INT *optlen)
{
    struct qemu_WS_getsockopt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_GETSOCKOPT);
    call.s = guest_SOCKET_g2h(s);
    call.level = level;
    call.optname = optname;
    call.optval = (ULONG_PTR)optval;
    call.optlen = (ULONG_PTR)optlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_getsockopt(struct qemu_syscall *call)
{
    struct qemu_WS_getsockopt *c = (struct qemu_WS_getsockopt *)call;
    char *buf;
    INT *len, optname;
    WINE_TRACE("\n");

    buf = QEMU_G2H(c->optval);
    len = QEMU_G2H(c->optlen);
    optname = c->optname;
#if GUEST_BIT == HOST_BIT
    c->super.iret = p_getsockopt(c->s, c->level, optname, buf, len);
    return;
#endif

    switch (optname)
    {
        default:
            WINE_FIXME("Unknown option %d\n", optname);
            /* Drop through. */
        case WS_SO_OPENTYPE:
        case WS_SO_RCVTIMEO:
        case WS_SO_SNDTIMEO:
        case WS_SO_SNDBUF:
        case WS_SO_RCVBUF:
        case WS_SO_LINGER:
        case WS_SO_DONTLINGER:
        case WS_SO_ERROR:
        case WS_IP_MULTICAST_TTL:
        case WS_SO_PROTOCOL_INFOA:
        case WS_SO_PROTOCOL_INFOW:
        case WS_IP_DONTFRAGMENT:
        case WS_SO_REUSEADDR:
        case WS_SO_TYPE:
        case WS_IPX_PTYPE:
        case WS_SO_ACCEPTCONN:
        case WS_SO_MAX_MSG_SIZE:
        case WS_SO_OOBINLINE:
        case WS_IPV6_V6ONLY:
        case WS_SO_CONNECT_TIME:
        case WS_SO_EXCLUSIVEADDRUSE:
            c->super.iret = p_getsockopt(c->s, c->level, optname, buf, len);
            break;

        case WS_SO_BSP_STATE:
        {
            size_t extra;
            char *my_buf;
            int my_len;
            struct qemu_CSADDR_INFO *info = (struct qemu_CSADDR_INFO *)buf;

            WINE_TRACE("Handling SO_BSP_STATE.\n");
            if (!buf || !len)
            {
                c->super.iret = p_getsockopt(c->s, c->level, optname, buf, len);
                break;
            }

            extra = *len - sizeof(struct qemu_CSADDR_INFO);
            my_len = sizeof(CSADDR_INFO) + extra;
            my_buf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, my_len);

            c->super.iret = p_getsockopt(c->s, c->level, optname, my_buf, &my_len);
            if (!c->super.iret)
            {
                CSADDR_INFO_h2g(info, (CSADDR_INFO *)my_buf);

                memcpy(buf + sizeof(struct qemu_CSADDR_INFO), my_buf + sizeof(CSADDR_INFO), extra);
                extra = sizeof(CSADDR_INFO) - sizeof(struct qemu_CSADDR_INFO);
                if (info->LocalAddr.lpSockaddr)
                    info->LocalAddr.lpSockaddr += (ULONG_PTR)info - (ULONG_PTR)my_buf - extra;
                if (info->RemoteAddr.lpSockaddr)
                    info->RemoteAddr.lpSockaddr += (ULONG_PTR)info - (ULONG_PTR)my_buf - extra;
            }
            HeapFree(GetProcessHeap(), 0, my_buf);

            /* FIXME: Should I write something to *len? Wine does not. */
            break;
        }
    }
}

#endif

struct qemu_WS_htonl
{
    struct qemu_syscall super;
    uint64_t hostlong;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI u_long WINAPI WS_htonl(u_long hostlong)
{
    struct qemu_WS_htonl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_HTONL);
    call.hostlong = hostlong;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_htonl(struct qemu_syscall *call)
{
    struct qemu_WS_htonl *c = (struct qemu_WS_htonl *)call;
    WINE_TRACE("\n");
    c->super.iret = p_htonl(c->hostlong);
}

#endif

struct qemu_WS_htons
{
    struct qemu_syscall super;
    uint64_t hostshort;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI u_short WINAPI WS_htons(u_short hostshort)
{
    struct qemu_WS_htons call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_HTONS);
    call.hostshort = (ULONG_PTR)hostshort;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_htons(struct qemu_syscall *call)
{
    struct qemu_WS_htons *c = (struct qemu_WS_htons *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_htons(c->hostshort);
}

#endif

struct qemu_WSAHtonl
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t hostlong;
    uint64_t lpnetlong;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WSAHtonl(SOCKET s, u_long hostlong, u_long *lpnetlong)
{
    struct qemu_WSAHtonl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAHTONL);
    call.s = guest_SOCKET_g2h(s);
    call.hostlong = (ULONG_PTR)hostlong;
    call.lpnetlong = (ULONG_PTR)lpnetlong;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAHtonl(struct qemu_syscall *call)
{
    struct qemu_WSAHtonl *c = (struct qemu_WSAHtonl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAHtonl(c->s, c->hostlong, QEMU_G2H(c->lpnetlong));
}

#endif

struct qemu_WSAHtons
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t hostshort;
    uint64_t lpnetshort;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WSAHtons(SOCKET s, u_short hostshort, u_short *lpnetshort)
{
    struct qemu_WSAHtons call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAHTONS);
    call.s = guest_SOCKET_g2h(s);
    call.hostshort = (ULONG_PTR)hostshort;
    call.lpnetshort = (ULONG_PTR)lpnetshort;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAHtons(struct qemu_syscall *call)
{
    struct qemu_WSAHtons *c = (struct qemu_WSAHtons *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAHtons(c->s, c->hostshort, QEMU_G2H(c->lpnetshort));
}

#endif

struct qemu_WS_inet_addr
{
    struct qemu_syscall super;
    uint64_t cp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI u_long WINAPI WS_inet_addr(const char *cp)
{
    struct qemu_WS_inet_addr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_INET_ADDR);
    call.cp = (ULONG_PTR)cp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_inet_addr(struct qemu_syscall *call)
{
    struct qemu_WS_inet_addr *c = (struct qemu_WS_inet_addr *)call;
    WINE_TRACE("\n");
    c->super.iret = p_inet_addr(QEMU_G2H(c->cp));
}

#endif

struct qemu_WS_ntohl
{
    struct qemu_syscall super;
    uint64_t netlong;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI u_long WINAPI WS_ntohl(u_long netlong)
{
    struct qemu_WS_ntohl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_NTOHL);
    call.netlong = netlong;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_ntohl(struct qemu_syscall *call)
{
    struct qemu_WS_ntohl *c = (struct qemu_WS_ntohl *)call;
    WINE_TRACE("\n");
    c->super.iret = p_ntohl(c->netlong);
}

#endif

struct qemu_WS_ntohs
{
    struct qemu_syscall super;
    uint64_t netshort;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI u_short WINAPI WS_ntohs(u_short netshort)
{
    struct qemu_WS_ntohs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_NTOHS);
    call.netshort = (ULONG_PTR)netshort;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_ntohs(struct qemu_syscall *call)
{
    struct qemu_WS_ntohs *c = (struct qemu_WS_ntohs *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_ntohs(c->netshort);
}

#endif

struct qemu_WS_inet_ntoa
{
    struct qemu_syscall super;
    uint64_t in;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI char* WINAPI WS_inet_ntoa(struct in_addr in)
{
    struct qemu_WS_inet_ntoa call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_INET_NTOA);
    call.in = in.S_un.S_addr;

    qemu_syscall(&call.super);

    return (char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WS_inet_ntoa(struct qemu_syscall *call)
{
    struct qemu_WS_inet_ntoa *c = (struct qemu_WS_inet_ntoa *)call;
    struct WS_in_addr in;
    WINE_TRACE("\n");

    /* struct in_addr has the same size in 32 and 64 bit. */
    in.S_un.S_addr = c->in;
    c->super.iret = QEMU_H2G(p_inet_ntoa(in));
}

#endif

struct qemu_WS2_AcceptEx
{
    struct qemu_syscall super;
    uint64_t listener;
    uint64_t acceptor;
    uint64_t dest;
    uint64_t dest_len;
    uint64_t local_addr_len;
    uint64_t rem_addr_len;
    uint64_t received;
    uint64_t overlapped;
};

#ifdef QEMU_DLL_GUEST

static BOOL WINAPI WS2_AcceptEx(SOCKET listener, SOCKET acceptor, PVOID dest, DWORD dest_len, DWORD local_addr_len, DWORD rem_addr_len, LPDWORD received, LPOVERLAPPED overlapped)
{
    struct qemu_WS2_AcceptEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS2_ACCEPTEX);
    call.listener = guest_SOCKET_g2h(listener);
    call.acceptor = guest_SOCKET_g2h(acceptor);
    call.dest = (ULONG_PTR)dest;
    call.dest_len = dest_len;
    call.local_addr_len = local_addr_len;
    call.rem_addr_len = rem_addr_len;
    call.received = (ULONG_PTR)received;
    call.overlapped = (ULONG_PTR)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS2_AcceptEx(struct qemu_syscall *call)
{
    struct qemu_WS2_AcceptEx *c = (struct qemu_WS2_AcceptEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_AcceptEx(c->listener, c->acceptor, QEMU_G2H(c->dest), c->dest_len, c->local_addr_len, c->rem_addr_len, QEMU_G2H(c->received), QEMU_G2H(c->overlapped));
}

#endif

struct qemu_WS2_DisconnectEx
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t ov;
    uint64_t flags;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

static BOOL WINAPI WS2_DisconnectEx(SOCKET s, LPOVERLAPPED ov, DWORD flags, DWORD reserved)
{
    struct qemu_WS2_DisconnectEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS2_DISCONNECTEX);
    call.s = s;
    call.ov = (ULONG_PTR)ov;
    call.flags = flags;
    call.reserved = reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS2_DisconnectEx(struct qemu_syscall *call)
{
    struct qemu_WS2_DisconnectEx *c = (struct qemu_WS2_DisconnectEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DisconnectEx(c->s, QEMU_G2H(c->ov), c->flags, c->reserved);
}

#endif

struct qemu_WS2_ConnectEx
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t name;
    uint64_t namelen;
    uint64_t sendBuf;
    uint64_t sendBufLen;
    uint64_t sent;
    uint64_t ov;
};

#ifdef QEMU_DLL_GUEST

static BOOL WINAPI WS2_ConnectEx(SOCKET s, const struct sockaddr *name, int namelen, PVOID sendBuf, DWORD sendBufLen, LPDWORD sent, LPOVERLAPPED ov)
{
    struct qemu_WS2_ConnectEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS2_CONNECTEX);
    call.s = s;
    call.name = (ULONG_PTR)name;
    call.namelen = namelen;
    call.sendBuf = (ULONG_PTR)sendBuf;
    call.sendBufLen = sendBufLen;
    call.sent = (ULONG_PTR)sent;
    call.ov = (ULONG_PTR)ov;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS2_ConnectEx(struct qemu_syscall *call)
{
    struct qemu_WS2_ConnectEx *c = (struct qemu_WS2_ConnectEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_ConnectEx(c->s, QEMU_G2H(c->name), c->namelen, QEMU_G2H(c->sendBuf), c->sendBufLen, QEMU_G2H(c->sent), QEMU_G2H(c->ov));
}

#endif

struct qemu_WS2_GetAcceptExSockaddrs
{
    struct qemu_syscall super;
    uint64_t buffer;
    uint64_t data_size;
    uint64_t local_size;
    uint64_t remote_size;
    uint64_t local_addr;
    uint64_t local_addr_len;
    uint64_t remote_addr;
    uint64_t remote_addr_len;
};

#ifdef QEMU_DLL_GUEST

static void WINAPI WS2_GetAcceptExSockaddrs(PVOID buffer, DWORD data_size, DWORD local_size, DWORD remote_size, struct sockaddr **local_addr, LPINT local_addr_len, struct sockaddr **remote_addr, LPINT remote_addr_len)
{
    struct qemu_WS2_GetAcceptExSockaddrs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS2_GETACCEPTEXSOCKADDRS);
    call.buffer = (ULONG_PTR)buffer;
    call.data_size = data_size;
    call.local_size = local_size;
    call.remote_size = remote_size;
    call.local_addr = (ULONG_PTR)local_addr;
    call.local_addr_len = (ULONG_PTR)local_addr_len;
    call.remote_addr = (ULONG_PTR)remote_addr;
    call.remote_addr_len = (ULONG_PTR)remote_addr_len;

    qemu_syscall(&call.super);
}

#else

void qemu_WS2_GetAcceptExSockaddrs(struct qemu_syscall *call)
{
    struct qemu_WS2_GetAcceptExSockaddrs *c = (struct qemu_WS2_GetAcceptExSockaddrs *)call;
    WINE_FIXME("Unverified!\n");
    p_GetAcceptExSockaddrs(QEMU_G2H(c->buffer), c->data_size, c->local_size, c->remote_size, QEMU_G2H(c->local_addr), QEMU_G2H(c->local_addr_len), QEMU_G2H(c->remote_addr), QEMU_G2H(c->remote_addr_len));
}

#endif

struct qemu_WS2_TransmitFile
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t h;
    uint64_t file_bytes;
    uint64_t bytes_per_send;
    uint64_t overlapped;
    uint64_t buffers;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static BOOL WINAPI WS2_TransmitFile(SOCKET s, HANDLE h, DWORD file_bytes, DWORD bytes_per_send, LPOVERLAPPED overlapped, LPTRANSMIT_FILE_BUFFERS buffers, DWORD flags)
{
    struct qemu_WS2_TransmitFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS2_TRANSMITFILE);
    call.s = s;
    call.h = (ULONG_PTR)h;
    call.file_bytes = file_bytes;
    call.bytes_per_send = bytes_per_send;
    call.overlapped = (ULONG_PTR)overlapped;
    call.buffers = (ULONG_PTR)buffers;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS2_TransmitFile(struct qemu_syscall *call)
{
    struct qemu_WS2_TransmitFile *c = (struct qemu_WS2_TransmitFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_TransmitFile(c->s, QEMU_G2H(c->h), c->file_bytes, c->bytes_per_send, QEMU_G2H(c->overlapped), QEMU_G2H(c->buffers), c->flags);
}

#endif

struct qemu_WS2_WSASendRecvMsg
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t msg;
    uint64_t dwFlags;
    uint64_t lpNumberOfBytesXferedd;
    uint64_t lpOverlapped;
    uint64_t lpCompletionRoutine;
};

#ifdef QEMU_DLL_GUEST

static int WINAPI WS2_WSARecvMsg(SOCKET s, WSAMSG *msg, DWORD *lpNumberOfBytesRecvd, WSAOVERLAPPED *lpOverlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    struct qemu_WS2_WSASendRecvMsg call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS2_WSARECVMSG);
    call.s = s;
    call.msg = (ULONG_PTR)msg;
    call.lpNumberOfBytesXferedd = (ULONG_PTR)lpNumberOfBytesRecvd;
    call.lpOverlapped = (ULONG_PTR)lpOverlapped;
    call.lpCompletionRoutine = (ULONG_PTR)lpCompletionRoutine;
    call.dwFlags = 0;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI int WINAPI WSASendMsg(SOCKET s, WSAMSG *msg, DWORD dwFlags, DWORD *lpNumberOfBytesSent,
        WSAOVERLAPPED *lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    struct qemu_WS2_WSASendRecvMsg call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSASENDMSG);
    call.s = guest_SOCKET_g2h(s);
    call.msg = (ULONG_PTR)msg;
    call.dwFlags = dwFlags;
    call.lpNumberOfBytesXferedd = (ULONG_PTR)lpNumberOfBytesSent;
    call.lpOverlapped = (ULONG_PTR)lpOverlapped;
    call.lpCompletionRoutine = (ULONG_PTR)lpCompletionRoutine;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS2_WSASendRecvMsg(struct qemu_syscall *call)
{
    struct qemu_WS2_WSASendRecvMsg *c = (struct qemu_WS2_WSASendRecvMsg *)call;
    WSAMSG msg_stack, *msg;
    WSABUF stackbuf[10], *buffers;
    struct qemu_WSABUF *guest_buffers;
    struct qemu_WSAMSG *guest_msg;
    unsigned int i;
    struct OVERLAPPED_data *ov_wrapper;
    HANDLE guest_event;
    struct qemu_OVERLAPPED *ov32;
    WINE_TRACE("%s\n", c->super.id == QEMU_SYSCALL_ID(CALL_WSASENDMSG) ? "WSASendMsg" : "WSARecvMsg");

#if GUEST_BIT == HOST_BIT
    /* This can be done nicer than 32 bit, just export the completion routine wrapper table from kernel32. */
    if (c->lpCompletionRoutine)
        WINE_FIXME("Completion routine not handled yet in 64 bit.\n");

    if (c->super.id == QEMU_SYSCALL_ID(CALL_WSASENDMSG))
    {
        c->super.iret = p_WSASendMsg(c->s, QEMU_G2H(c->msg), c->dwFlags, QEMU_G2H(c->lpNumberOfBytesXferedd),
                QEMU_G2H(c->lpOverlapped), QEMU_G2H(c->lpCompletionRoutine));
    }
    else
    {
        c->super.iret = p_WSARecvMsg(c->s, QEMU_G2H(c->msg), QEMU_G2H(c->lpNumberOfBytesXferedd),
                QEMU_G2H(c->lpOverlapped), QEMU_G2H(c->lpCompletionRoutine));
    }
    return;
#endif

    ov32 = QEMU_G2H(c->lpOverlapped);
    if (ov32)
    {
        ov_wrapper = p_alloc_OVERLAPPED_data(ov32, c->lpCompletionRoutine, TRUE);
        ov_wrapper->wsa = TRUE;
        ov_wrapper->wsa_flags = c->dwFlags;
        guest_event = HANDLE_g2h(ov32->hEvent);
    }
    else
    {
        WINE_TRACE("Synchronous operation, easy...\n");
        ov_wrapper = NULL;
    }

    if (!c->msg)
    {
        WINE_WARN("Message is NULL.\n");
        buffers = stackbuf;
        if (c->super.id == QEMU_SYSCALL_ID(CALL_WSASENDMSG))
        {
            c->super.iret = p_WSASendMsg(c->s, NULL, c->dwFlags, QEMU_G2H(c->lpNumberOfBytesXferedd),
                    ov_wrapper ? &ov_wrapper->ov : NULL, NULL);
        }
        else
        {
            c->super.iret = p_WSARecvMsg(c->s, NULL, QEMU_G2H(c->lpNumberOfBytesXferedd),
                    ov_wrapper ? &ov_wrapper->ov : NULL, NULL);
        }
        goto done;
    }

    if (ov32)
        msg = HeapAlloc(GetProcessHeap(), 0, sizeof(*msg));
    else
        msg = &msg_stack;

    guest_msg = QEMU_G2H(c->msg);
    WSAMSG_g2h(msg, guest_msg);
    guest_buffers = (struct qemu_WSABUF *)msg->lpBuffers;
    if (!ov32 && msg->dwBufferCount < sizeof(stackbuf) / sizeof(*stackbuf))
        buffers = stackbuf;
    else
        buffers = HeapAlloc(GetProcessHeap(), 0, sizeof(*buffers) * msg->dwBufferCount);

    for (i = 0; i < msg->dwBufferCount; ++i)
        WSABUF_g2h(&buffers[i], &guest_buffers[i]);
    msg->lpBuffers = buffers;

    if (c->super.id == QEMU_SYSCALL_ID(CALL_WSASENDMSG))
    {
        c->super.iret = p_WSASendMsg(c->s, msg, c->dwFlags, QEMU_G2H(c->lpNumberOfBytesXferedd),
                ov_wrapper ? &ov_wrapper->ov: NULL, NULL);
    }
    else
    {
        c->super.iret = p_WSARecvMsg(c->s, msg, QEMU_G2H(c->lpNumberOfBytesXferedd),
                ov_wrapper ? &ov_wrapper->ov : NULL, NULL);
    }

    WSAMSG_h2g(guest_msg, msg);
    guest_msg->lpBuffers = (ULONG_PTR)guest_buffers;

done:
    if (ov32)
    {
        OVERLAPPED_h2g(ov32, &ov_wrapper->ov);
        ov_wrapper->msg = msg;
        ov_wrapper->guest_msg = guest_msg;
        ov32->hEvent = (ULONG_PTR)guest_event;
        p_process_OVERLAPPED_data(c->super.iret == SOCKET_ERROR ? 0 : 1, ov_wrapper);
    }
    else if (buffers != stackbuf)
    {
        HeapFree(GetProcessHeap(), 0, buffers);
    }

}

#endif

struct qemu_WSAIoctl
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t code;
    uint64_t in_buff;
    uint64_t in_size;
    uint64_t out_buff;
    uint64_t out_size;
    uint64_t ret_size;
    uint64_t overlapped;
    uint64_t completion;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAIoctl(SOCKET s, DWORD code, LPVOID in_buff, DWORD in_size, void *out_buff,
        DWORD out_size, DWORD *ret_size, WSAOVERLAPPED *overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completion)
{
    struct qemu_WSAIoctl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAIOCTL);
    call.s = guest_SOCKET_g2h(s);
    call.code = code;
    call.in_buff = (ULONG_PTR)in_buff;
    call.in_size = in_size;
    call.out_buff = (ULONG_PTR)out_buff;
    call.out_size = out_size;
    call.ret_size = (ULONG_PTR)ret_size;
    call.overlapped = (ULONG_PTR)overlapped;
    call.completion = (ULONG_PTR)completion;

    if (code == SIO_GET_EXTENSION_FUNCTION_POINTER)
    {
#define EXTENSION_FUNCTION(x, y) { x, y, #y },
        static const struct
        {
            GUID guid;
            void *func_ptr;
            const char *name;
        } guid_funcs[] = {
            EXTENSION_FUNCTION(WSAID_CONNECTEX, WS2_ConnectEx)
            EXTENSION_FUNCTION(WSAID_DISCONNECTEX, WS2_DisconnectEx)
            EXTENSION_FUNCTION(WSAID_ACCEPTEX, WS2_AcceptEx)
            EXTENSION_FUNCTION(WSAID_GETACCEPTEXSOCKADDRS, WS2_GetAcceptExSockaddrs)
            EXTENSION_FUNCTION(WSAID_TRANSMITFILE, WS2_TransmitFile)
            /* EXTENSION_FUNCTION(WSAID_TRANSMITPACKETS, WS2_TransmitPackets) */
            EXTENSION_FUNCTION(WSAID_WSARECVMSG, WS2_WSARecvMsg)
            EXTENSION_FUNCTION(WSAID_WSASENDMSG, WSASendMsg)
        };
#undef EXTENSION_FUNCTION
        BOOL found = FALSE;
        unsigned int i;

        for (i = 0; i < sizeof(guid_funcs) / sizeof(guid_funcs[0]); i++)
        {
            if (IsEqualGUID(&guid_funcs[i].guid, in_buff))
            {
                found = TRUE;
                break;
            }
        }

        if (found)
        {
            *(void **)out_buff = guid_funcs[i].func_ptr;
            call.out_buff = 1;
            if (ret_size)
                *ret_size = sizeof(void *);
        }
        else
        {
            call.out_buff = 0;
        }
    }

    qemu_syscall(&call.super);

    if (code == SIO_GET_EXTENSION_FUNCTION_POINTER && call.super.iret)
    {
        void **out = out_buff;
        *out = NULL;
    }

    return call.super.iret;
}

#else

void qemu_WSAIoctl(struct qemu_syscall *call)
{
    struct qemu_WSAIoctl *c = (struct qemu_WSAIoctl *)call;
    WINE_TRACE("Unverified!\n");

    /* Note that Wine cheats and handles most cases synchronously. Possibly those that go through the server might be
     * signalled asynchronously. Wine doesn't support the completion routine. */
    if (c->overlapped || c->completion)
        WINE_FIXME("Asynchronous operation not supported yet.\n");

    switch (c->code)
    {
        default:
            WINE_FIXME("Unknown Ioctl code 0x%lx.\n", c->code);
            /* Drop through */
        case 0x667e: /* Netscape tries hard to use bogus ioctl 0x667e */
        case WS_FIONBIO:
        case WS_FIONREAD:
        case WS_SIOCATMARK:
        case WS_FIOASYNC:
        case WS_SIO_FLUSH:
        case WS_SIO_KEEPALIVE_VALS:
        case WS_SIO_ROUTING_INTERFACE_QUERY:
        case WS_SIO_SET_COMPATIBILITY_MODE:
        case WS_SIO_UDP_CONNRESET:
#if GUEST_BIT == HOST_BIT
        case WS_SIO_GET_INTERFACE_LIST:
        case WS_SIO_ADDRESS_LIST_QUERY:
        case WS_SIO_ADDRESS_LIST_CHANGE:
#endif
            c->super.iret = WSAIoctl(c->s, c->code, QEMU_G2H(c->in_buff), c->in_size, QEMU_G2H(c->out_buff),
                    c->out_size, QEMU_G2H(c->ret_size), QEMU_G2H(c->overlapped), QEMU_G2H(c->completion));
            break;

#if GUEST_BIT != HOST_BIT
        case WS_SIO_GET_INTERFACE_LIST:  /* INTERFACE_INFO ??? */
            WINE_FIXME("Handle WS_SIO_GET_INTERFACE_LIST\n");
            c->super.iret = WSAIoctl(c->s, c->code, QEMU_G2H(c->in_buff), c->in_size, QEMU_G2H(c->out_buff),
                    c->out_size, QEMU_G2H(c->ret_size), QEMU_G2H(c->overlapped), QEMU_G2H(c->completion));
            break;
        case WS_SIO_ADDRESS_LIST_QUERY: /* SOCKET_ADDRESS_LIST */
            WINE_FIXME("Handle WS_SIO_ADDRESS_LIST_QUERY\n");
            c->super.iret = WSAIoctl(c->s, c->code, QEMU_G2H(c->in_buff), c->in_size, QEMU_G2H(c->out_buff),
                    c->out_size, QEMU_G2H(c->ret_size), QEMU_G2H(c->overlapped), QEMU_G2H(c->completion));
            break;

        case WS_SIO_ADDRESS_LIST_CHANGE:
            WINE_FIXME("Handle WS_SIO_ADDRESS_LIST_CHANGE\n");
            c->super.iret = WSAIoctl(c->s, c->code, QEMU_G2H(c->in_buff), c->in_size, QEMU_G2H(c->out_buff),
                    c->out_size, QEMU_G2H(c->ret_size), QEMU_G2H(c->overlapped), QEMU_G2H(c->completion));
            break;
#endif

        case WS_SIO_GET_EXTENSION_FUNCTION_POINTER:
        {
            void *out;
            DWORD ret_size;
            /* This is handled in the guest, the call here is mainly there to catch newly added functions
             * that we don't support yet. */
            c->super.iret = WSAIoctl(c->s, c->code, QEMU_G2H(c->in_buff), c->in_size, &out,
                    sizeof(out), &ret_size, NULL, NULL);
            if (out && !c->out_buff)
            {
                WINE_FIXME("Wine supports a WSA function this wrapper does not know about!\n");
            }
            break;
        }
    }
}

#endif

struct qemu_WS_ioctlsocket
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t cmd;
    uint64_t argp;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_ioctlsocket(SOCKET s, LONG cmd, u_long *argp)
{
    struct qemu_WS_ioctlsocket call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_IOCTLSOCKET);
    call.s = guest_SOCKET_g2h(s);
    call.cmd = cmd;
    call.argp = (ULONG_PTR)argp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_ioctlsocket(struct qemu_syscall *call)
{
    struct qemu_WS_ioctlsocket *c = (struct qemu_WS_ioctlsocket *)call;
    WINE_TRACE("\n");
    /* This function always has a data type of WS_u_long aka ULONG. */
    c->super.iret = p_ioctlsocket(c->s, c->cmd, QEMU_G2H(c->argp));
}

#endif

struct qemu_WS_listen
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t backlog;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_listen(SOCKET s, int backlog)
{
    struct qemu_WS_listen call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_LISTEN);
    call.s = guest_SOCKET_g2h(s);
    call.backlog = backlog;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_listen(struct qemu_syscall *call)
{
    struct qemu_WS_listen *c = (struct qemu_WS_listen *)call;
    WINE_TRACE("\n");
    c->super.iret = p_listen(c->s, c->backlog);
}

#endif

struct qemu_WS_recv
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t buf;
    uint64_t len;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_recv(SOCKET s, char *buf, int len, int flags)
{
    struct qemu_WS_recv call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_RECV);
    call.s = guest_SOCKET_g2h(s);
    call.buf = (ULONG_PTR)buf;
    call.len = len;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_recv(struct qemu_syscall *call)
{
    struct qemu_WS_recv *c = (struct qemu_WS_recv *)call;
    WINE_TRACE("\n");
    c->super.iret = p_recv(c->s, QEMU_G2H(c->buf), c->len, c->flags);
}

#endif

struct qemu_WS_recvfrom
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t buf;
    uint64_t len;
    uint64_t flags;
    uint64_t from;
    uint64_t fromlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_recvfrom(SOCKET s, char *buf, INT len, int flags, struct sockaddr *from, int *fromlen)
{
    struct qemu_WS_recvfrom call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_RECVFROM);
    call.s = guest_SOCKET_g2h(s);
    call.buf = (ULONG_PTR)buf;
    call.len = (ULONG_PTR)len;
    call.flags = (ULONG_PTR)flags;
    call.from = (ULONG_PTR)from;
    call.fromlen = (ULONG_PTR)fromlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_recvfrom(struct qemu_syscall *call)
{
    struct qemu_WS_recvfrom *c = (struct qemu_WS_recvfrom *)call;
    WINE_TRACE("\n");

    /* WS_sockaddr has the same size in 32 and 64 bit. */
    c->super.iret = p_recvfrom(c->s, QEMU_G2H(c->buf), c->len, c->flags, QEMU_G2H(c->from), QEMU_G2H(c->fromlen));
}

#endif

struct qemu_WS_select
{
    struct qemu_syscall super;
    uint64_t nfds;
    uint64_t ws_readfds;
    uint64_t ws_writefds;
    uint64_t ws_exceptfds;
    uint64_t ws_timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_select(int nfds, fd_set *ws_readfds, fd_set *ws_writefds, fd_set *ws_exceptfds, const struct timeval* ws_timeout)
{
    struct qemu_WS_select call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_SELECT);
    call.nfds = (ULONG_PTR)nfds;
    call.ws_readfds = (ULONG_PTR)ws_readfds;
    call.ws_writefds = (ULONG_PTR)ws_writefds;
    call.ws_exceptfds = (ULONG_PTR)ws_exceptfds;
    call.ws_timeout = (ULONG_PTR)ws_timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_select(struct qemu_syscall *call)
{
    struct qemu_WS_select *c = (struct qemu_WS_select *)call;
    WS_fd_set read, write, except;
    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    c->super.iret = p_select(c->nfds, QEMU_G2H(c->ws_readfds), QEMU_G2H(c->ws_writefds), QEMU_G2H(c->ws_exceptfds),
            QEMU_G2H(c->ws_timeout));
    return;
#endif

    if (c->ws_readfds)
        WS_fd_set_g2h(&read, QEMU_G2H(c->ws_readfds));
    if (c->ws_writefds)
        WS_fd_set_g2h(&write, QEMU_G2H(c->ws_writefds));
    if (c->ws_exceptfds)
        WS_fd_set_g2h(&except, QEMU_G2H(c->ws_exceptfds));

    c->super.iret = p_select(c->nfds, c->ws_readfds ? &read : NULL, c->ws_writefds ? &write : NULL,
            c->ws_exceptfds ? &except : NULL, QEMU_G2H(c->ws_timeout));

    if (c->ws_readfds)
        WS_fd_set_h2g(QEMU_G2H(c->ws_readfds), &read);
    if (c->ws_writefds)
        WS_fd_set_h2g(QEMU_G2H(c->ws_writefds), &write);
    if (c->ws_exceptfds)
        WS_fd_set_h2g(QEMU_G2H(c->ws_exceptfds), &except);
}

#endif

struct qemu_WSAPoll
{
    struct qemu_syscall super;
    uint64_t wfds;
    uint64_t count;
    uint64_t timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WSAPoll(WSAPOLLFD *wfds, ULONG count, int timeout)
{
    struct qemu_WSAPoll call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAPOLL);
    call.wfds = (ULONG_PTR)wfds;
    call.count = count;
    call.timeout = timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAPoll(struct qemu_syscall *call)
{
    struct qemu_WSAPoll *c = (struct qemu_WSAPoll *)call;
    WSAPOLLFD stack[10], *fds;
    ULONG count, i;
    struct qemu_WSAPOLLFD *guest_fds;
    WINE_TRACE("\n");

    count = c->count;
#if GUEST_BIT == HOST_BIT
    fds = QEMU_G2H(c->wfds);
#else
    guest_fds = QEMU_G2H(c->wfds);
    if (!guest_fds)
        fds = NULL;
    else if(count > sizeof(stack) / sizeof(*stack))
        fds = HeapAlloc(GetProcessHeap(), 0, sizeof(*fds) * count);
    else
        fds = stack;

    if (fds)
    {
        for (i = 0; i < count; ++i)
            WSAPOLLFD_g2h(&fds[i], &guest_fds[i]);
    }
#endif

    c->super.iret = WSAPoll(fds, count, c->timeout);

#if GUEST_BIT != HOST_BIT
    if (fds)
    {
        if (fds)
        {
            for (i = 0; i < count; ++i)
                WSAPOLLFD_h2g(&guest_fds[i], &fds[i]);
        }

        if (fds != stack)
            HeapFree(GetProcessHeap(), 0, fds);
    }
#endif

}

#endif

struct qemu_WS_send
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t buf;
    uint64_t len;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_send(SOCKET s, const char *buf, int len, int flags)
{
    struct qemu_WS_send call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_SEND);
    call.s = guest_SOCKET_g2h(s);
    call.buf = (ULONG_PTR)buf;
    call.len = len;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_send(struct qemu_syscall *call)
{
    struct qemu_WS_send *c = (struct qemu_WS_send *)call;
    WINE_TRACE("\n");
    c->super.iret = p_send(c->s, QEMU_G2H(c->buf), c->len, c->flags);
}

#endif

struct qemu_WSASendDisconnect
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t lpBuffers;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSASendDisconnect(SOCKET s, LPWSABUF lpBuffers)
{
    struct qemu_WSASendDisconnect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSASENDDISCONNECT);
    call.s = guest_SOCKET_g2h(s);
    call.lpBuffers = (ULONG_PTR)lpBuffers;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSASendDisconnect(struct qemu_syscall *call)
{
    struct qemu_WSASendDisconnect *c = (struct qemu_WSASendDisconnect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSASendDisconnect(c->s, QEMU_G2H(c->lpBuffers));
}

#endif

struct qemu_WS_sendto
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t buf;
    uint64_t len;
    uint64_t flags;
    uint64_t to;
    uint64_t tolen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_sendto(SOCKET s, const char *buf, int len, int flags, const struct sockaddr *to, int tolen)
{
    struct qemu_WS_sendto call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_SENDTO);
    call.s = guest_SOCKET_g2h(s);
    call.buf = (ULONG_PTR)buf;
    call.len = (ULONG_PTR)len;
    call.flags = (ULONG_PTR)flags;
    call.to = (ULONG_PTR)to;
    call.tolen = (ULONG_PTR)tolen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_sendto(struct qemu_syscall *call)
{
    struct qemu_WS_sendto *c = (struct qemu_WS_sendto *)call;
    WINE_TRACE("\n");

    /* WS_sockaddr has the same size in 32 and 64 bit. */
    c->super.iret = p_sendto(c->s, QEMU_G2H(c->buf), c->len, c->flags, QEMU_G2H(c->to), c->tolen);
}

#endif

struct qemu_WS_setsockopt
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t level;
    uint64_t optname;
    uint64_t optval;
    uint64_t optlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_setsockopt(SOCKET s, int level, int optname, const char *optval, int optlen)
{
    struct qemu_WS_setsockopt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_SETSOCKOPT);
    call.s = guest_SOCKET_g2h(s);
    call.level = level;
    call.optname = optname;
    call.optval = (ULONG_PTR)optval;
    call.optlen = optlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_setsockopt(struct qemu_syscall *call)
{
    struct qemu_WS_setsockopt *c = (struct qemu_WS_setsockopt *)call;
    char *buf;
    INT len, optname;
    WINE_TRACE("\n");

    buf = QEMU_G2H(c->optval);
    len = c->optlen;
    optname = c->optname;
#if GUEST_BIT == HOST_BIT
    c->super.iret = p_setsockopt(c->s, c->level, optname, buf, len);
    return;
#endif

    switch (optname)
    {
        default:
            WINE_FIXME("Unknown option %d\n", optname);
            /* Drop through. */
        case WS_SO_OPENTYPE:
        case WS_SO_RCVTIMEO:
        case WS_SO_SNDTIMEO:
        case WS_SO_SNDBUF:
        case WS_SO_RCVBUF:
        case WS_SO_LINGER:
        case WS_SO_DONTLINGER:
        case WS_SO_ERROR:
        case WS_IP_MULTICAST_TTL:
        case WS_SO_PROTOCOL_INFOA:
        case WS_SO_PROTOCOL_INFOW:
        case WS_IP_DONTFRAGMENT:
        case WS_SO_REUSEADDR:
        case WS_SO_TYPE:
        case WS_IPX_PTYPE:
        case WS_SO_ACCEPTCONN:
        case WS_SO_MAX_MSG_SIZE:
        case WS_SO_OOBINLINE:
        case WS_IPV6_V6ONLY:
        case WS_SO_CONNECT_TIME:
        case WS_IP_PKTINFO:
        case WS_SO_EXCLUSIVEADDRUSE:
            c->super.iret = p_setsockopt(c->s, c->level, optname, buf, len);
            break;

        case WS_SO_BSP_STATE:
        {
            /* This is easier than the getter because we do not have to shift around
             * any extra data. */
            struct qemu_CSADDR_INFO *guest_in = (struct qemu_CSADDR_INFO *)buf;
            CSADDR_INFO host_out;

            WINE_TRACE("Handling SO_BSP_STATE.\n");
            if (!buf)
            {
                c->super.iret = p_setsockopt(c->s, c->level, optname, buf, len);
                break;
            }

            CSADDR_INFO_g2h(&host_out, guest_in);
            c->super.iret = p_setsockopt(c->s, c->level, optname, (char *)&host_out, sizeof(host_out));
            break;
        }
    }
}

#endif

struct qemu_WS_shutdown
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t how;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_shutdown(SOCKET s, int how)
{
    struct qemu_WS_shutdown call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_SHUTDOWN);
    call.s = guest_SOCKET_g2h(s);
    call.how = how;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_shutdown(struct qemu_syscall *call)
{
    struct qemu_WS_shutdown *c = (struct qemu_WS_shutdown *)call;
    WINE_TRACE("\n");
    c->super.iret = p_shutdown(c->s, c->how);
}

#endif

struct qemu_WS_socket
{
    struct qemu_syscall super;
    uint64_t af;
    uint64_t type;
    uint64_t protocol;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SOCKET WINAPI WS_socket(int af, int type, int protocol)
{
    struct qemu_WS_socket call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_SOCKET);
    call.af = af;
    call.type = type;
    call.protocol = protocol;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_socket(struct qemu_syscall *call)
{
    struct qemu_WS_socket *c = (struct qemu_WS_socket *)call;
    WINE_TRACE("\n");
    c->super.iret = p_socket(c->af, c->type, c->protocol);
}

#endif

struct qemu_WS_gethostbyaddr
{
    struct qemu_syscall super;
    uint64_t addr;
    uint64_t len;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct WS_hostent* WINAPI WS_gethostbyaddr(const char *addr, int len, int type)
{
    struct qemu_WS_gethostbyaddr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_GETHOSTBYADDR);
    call.addr = (ULONG_PTR)addr;
    call.len = (ULONG_PTR)len;
    call.type = (ULONG_PTR)type;

    qemu_syscall(&call.super);

    return (struct WS_hostent *)(ULONG_PTR)call.super.iret;
}

#else

/* Well, for the sake of the tests stick to the allocation rules that Wine uses and copy
 * data where we could actually just point into the host struct. */
static struct qemu_WS_hostent *check_buffer_he(int size)
{
    struct per_thread_data * ptb = get_per_thread_data();
    if (ptb->he_buffer)
    {
        if (ptb->he_len >= size ) return ptb->he_buffer;
        HeapFree( GetProcessHeap(), 0, ptb->he_buffer );
    }
    ptb->he_buffer = HeapAlloc( GetProcessHeap(), 0, (ptb->he_len = size) );
    if (!ptb->he_buffer) SetLastError(WSAENOBUFS);
    return ptb->he_buffer;
}

static struct qemu_WS_hostent *WS_create_he(char *name, int aliases, int aliases_size, int addresses, int address_length)
{
    struct qemu_WS_hostent *p_to;
    char *p;
    qemu_ptr *addr_list;
    int size = (sizeof(struct qemu_WS_hostent) +
                strlen(name) + 1 +
                sizeof(qemu_ptr) * aliases +
                aliases_size +
                sizeof(qemu_ptr) * addresses +
                address_length * (addresses - 1)), i;

    if (!(p_to = check_buffer_he(size))) return NULL;
    memset(p_to, 0, size);

    /* Use the memory in the same way winsock does.
     * First set the pointer for aliases, second set the pointers for addresses.
     * Third fill the addresses indexes, fourth jump aliases names size.
     * Fifth fill the hostname.
     * NOTE: This method is valid for OS version's >= XP.
     */
    p = (char *)(p_to + 1);
    p_to->h_aliases = (ULONG_PTR)p;
    p += sizeof(qemu_ptr)*aliases;

    p_to->h_addr_list = (ULONG_PTR)p;
    p += sizeof(qemu_ptr)*addresses;

    addr_list = (qemu_ptr *)(ULONG_PTR)p_to->h_addr_list;
    for (i = 0, addresses--; i < addresses; i++, p += address_length)
        addr_list[i] = (ULONG_PTR)p;

    /* NOTE: h_aliases must be filled in manually because we don't know each string
     * size, leave these pointers NULL (already set to NULL by memset earlier).
     */
    p += aliases_size;

    p_to->h_name = (ULONG_PTR)p;
    strcpy(p, name);

    return p_to;
}

static struct qemu_WS_hostent *WS_dup_he(const struct WS_hostent *p_he)
{
    int i, addresses = 0, alias_size = 0;
    struct qemu_WS_hostent *p_to;
    char *p;
    qemu_ptr *aliases;
    qemu_ptr *addrs;

    for( i = 0; p_he->h_aliases[i]; i++) alias_size += strlen(p_he->h_aliases[i]) + 1;
    while (p_he->h_addr_list[addresses]) addresses++;

    p_to = WS_create_he(p_he->h_name, i + 1, alias_size, addresses + 1, p_he->h_length);

    if (!p_to) return NULL;
    p_to->h_addrtype = p_he->h_addrtype;
    p_to->h_length = p_he->h_length;

    addrs = (qemu_ptr *)(ULONG_PTR)p_to->h_addr_list;
    for(i = 0, p = (char *)(ULONG_PTR)addrs[0]; p_he->h_addr_list[i]; i++, p += p_to->h_length)
        memcpy(p, p_he->h_addr_list[i], p_to->h_length);

    /* Fill the aliases after the IP data */
    aliases = (qemu_ptr *)(ULONG_PTR)p_to->h_aliases;
    for(i = 0; p_he->h_aliases[i]; i++)
    {
        aliases[i] = (ULONG_PTR)p;
        strcpy(p, p_he->h_aliases[i]);
        p += strlen(p) + 1;
    }

    return p_to;
}

void qemu_WS_gethostbyaddr(struct qemu_syscall *call)
{
    struct qemu_WS_gethostbyaddr *c = (struct qemu_WS_gethostbyaddr *)call;
    void *ret;
    WINE_TRACE("\n");

    ret = p_gethostbyaddr(QEMU_G2H(c->addr), c->len, c->type);
    if (!ret)
    {
        c->super.iret = 0;
        return;
    }

#if GUEST_BIT != HOST_BIT
    c->super.iret = QEMU_H2G(WS_dup_he(ret));
#else
    c->super.iret = QEMU_H2G(ret);
#endif
}

#endif

struct qemu_WS_gethostbyname
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct WS_hostent* WINAPI WS_gethostbyname(const char* name)
{
    struct qemu_WS_gethostbyname call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_GETHOSTBYNAME);
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (struct WS_hostent *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WS_gethostbyname(struct qemu_syscall *call)
{
    struct qemu_WS_gethostbyname *c = (struct qemu_WS_gethostbyname *)call;
    void *ret;
    WINE_TRACE("\n");

    ret = p_gethostbyname(QEMU_G2H(c->name));
    if (!ret)
    {
        c->super.iret = 0;
        return;
    }

#if GUEST_BIT != HOST_BIT
    c->super.iret = QEMU_H2G(WS_dup_he(ret));
#else
    c->super.iret = QEMU_H2G(ret);
#endif
}

#endif

struct qemu_WS_getprotobyname
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct WS_protoent* WINAPI WS_getprotobyname(const char* name)
{
    struct qemu_WS_getprotobyname call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_GETPROTOBYNAME);
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return (struct WS_protoent *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WS_getprotobyname(struct qemu_syscall *call)
{
    struct qemu_WS_getprotobyname *c = (struct qemu_WS_getprotobyname *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_getprotobyname(QEMU_G2H(c->name)));
}

#endif

struct qemu_WS_getprotobynumber
{
    struct qemu_syscall super;
    uint64_t number;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct WS_protoent* WINAPI WS_getprotobynumber(int number)
{
    struct qemu_WS_getprotobynumber call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_GETPROTOBYNUMBER);
    call.number = (ULONG_PTR)number;

    qemu_syscall(&call.super);

    return (struct WS_protoent *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WS_getprotobynumber(struct qemu_syscall *call)
{
    struct qemu_WS_getprotobynumber *c = (struct qemu_WS_getprotobynumber *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(p_getprotobynumber(c->number));
}

#endif

struct qemu_WS_getservbyname
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t proto;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct WS_servent* WINAPI WS_getservbyname(const char *name, const char *proto)
{
    struct qemu_WS_getservbyname call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_GETSERVBYNAME);
    call.name = (ULONG_PTR)name;
    call.proto = (ULONG_PTR)proto;

    qemu_syscall(&call.super);

    return (struct WS_servent *)(ULONG_PTR)call.super.iret;
}

#else

static struct qemu_WS_servent *check_buffer_se(int size)
{
    struct per_thread_data *ptb = get_per_thread_data();
    if (ptb->se_buffer)
    {
        if (ptb->se_len >= size ) return ptb->se_buffer;
        HeapFree( GetProcessHeap(), 0, ptb->se_buffer );
    }
    ptb->se_buffer = HeapAlloc( GetProcessHeap(), 0, (ptb->se_len = size) );
    if (!ptb->se_buffer) SetLastError(WSAENOBUFS);
    return ptb->se_buffer;
}

static int list_size(char** l, int item_size)
{
    int i,j = 0;
    if(l)
    {
        for(i=0;l[i];i++)
            j += (item_size) ? item_size : strlen(l[i]) + 1;
        j += (i + 1) * sizeof(qemu_ptr);
    }
    return j;
}

static int list_dup(char **l_src, qemu_ptr *l_to, int item_size)
{
   char *p;
   int i;

   for (i = 0; l_src[i]; i++) ;
   p = (char *)(l_to + i + 1);
   for (i = 0; l_src[i]; i++)
   {
       int count = ( item_size ) ? item_size : strlen(l_src[i]) + 1;
       memcpy(p, l_src[i], count);
       l_to[i] = (ULONG_PTR)p;
       p += count;
   }
   l_to[i] = 0;
   return p - (char *)l_to;
}

static struct qemu_WS_servent *WS_dup_se(const struct WS_servent *p_se)
{
    char *p;
    struct qemu_WS_servent *p_to;

    int size = (sizeof(*p_se) +
                strlen(p_se->s_proto) + 1 +
                strlen(p_se->s_name) + 1 +
                list_size(p_se->s_aliases, 0));

    if (!(p_to = check_buffer_se(size))) return NULL;
    p_to->s_port = p_se->s_port;

    p = (char *)(p_to + 1);
    p_to->s_name = (ULONG_PTR)p;
    strcpy(p, p_se->s_name);
    p += strlen(p) + 1;

    p_to->s_proto = (ULONG_PTR)p;
    strcpy(p, p_se->s_proto);
    p += strlen(p) + 1;

    p_to->s_aliases = (ULONG_PTR)p;
    list_dup(p_se->s_aliases, (qemu_ptr *)(ULONG_PTR)p_to->s_aliases, 0);
    return p_to;
}

void qemu_WS_getservbyname(struct qemu_syscall *call)
{
    struct qemu_WS_getservbyname *c = (struct qemu_WS_getservbyname *)call;
    void *ret;
    WINE_TRACE("\n");

    ret = p_getservbyname(QEMU_G2H(c->name), QEMU_G2H(c->proto));
    if (!ret)
    {
        c->super.iret = 0;
        return;
    }

#if GUEST_BIT != HOST_BIT
    c->super.iret = QEMU_H2G(WS_dup_se(ret));
#else
    c->super.iret = QEMU_H2G(ret);
#endif
}

#endif

struct qemu_WS_freeaddrinfo
{
    struct qemu_syscall super;
    uint64_t res;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI WS_freeaddrinfo(struct addrinfo *res)
{
    struct qemu_WS_freeaddrinfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_FREEADDRINFO);
    call.res = (ULONG_PTR)res;

    qemu_syscall(&call.super);
}

#else

void qemu_WS_freeaddrinfo(struct qemu_syscall *call)
{
    struct qemu_WS_freeaddrinfo *c = (struct qemu_WS_freeaddrinfo *)call;
    WINE_FIXME("Unverified!\n");
    p_freeaddrinfo(QEMU_G2H(c->res));
}

#endif

struct qemu_WS_getaddrinfo
{
    struct qemu_syscall super;
    uint64_t nodename;
    uint64_t servname;
    uint64_t hints;
    uint64_t res;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_getaddrinfo(LPCSTR nodename, LPCSTR servname, const struct addrinfo *hints, struct addrinfo **res)
{
    struct qemu_WS_getaddrinfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_GETADDRINFO);
    call.nodename = (ULONG_PTR)nodename;
    call.servname = (ULONG_PTR)servname;
    call.hints = (ULONG_PTR)hints;
    call.res = (ULONG_PTR)res;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_getaddrinfo(struct qemu_syscall *call)
{
    struct qemu_WS_getaddrinfo *c = (struct qemu_WS_getaddrinfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_getaddrinfo(QEMU_G2H(c->nodename), QEMU_G2H(c->servname), QEMU_G2H(c->hints), QEMU_G2H(c->res));
}

#endif

struct qemu_GetAddrInfoExW
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t servname;
    uint64_t namespace;
    uint64_t namespace_id;
    uint64_t hints;
    uint64_t result;
    uint64_t timeout;
    uint64_t overlapped;
    uint64_t completion_routine;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI GetAddrInfoExW(const WCHAR *name, const WCHAR *servname, DWORD namespace, GUID *namespace_id, const ADDRINFOEXW *hints, ADDRINFOEXW **result, struct timeval *timeout, OVERLAPPED *overlapped, LPLOOKUPSERVICE_COMPLETION_ROUTINE completion_routine, HANDLE *handle)
{
    struct qemu_GetAddrInfoExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETADDRINFOEXW);
    call.name = (ULONG_PTR)name;
    call.servname = (ULONG_PTR)servname;
    call.namespace = (ULONG_PTR)namespace;
    call.namespace_id = (ULONG_PTR)namespace_id;
    call.hints = (ULONG_PTR)hints;
    call.result = (ULONG_PTR)result;
    call.timeout = (ULONG_PTR)timeout;
    call.overlapped = (ULONG_PTR)overlapped;
    call.completion_routine = (ULONG_PTR)completion_routine;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAddrInfoExW(struct qemu_syscall *call)
{
    struct qemu_GetAddrInfoExW *c = (struct qemu_GetAddrInfoExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAddrInfoExW(QEMU_G2H(c->name), QEMU_G2H(c->servname), c->namespace, QEMU_G2H(c->namespace_id), QEMU_G2H(c->hints), QEMU_G2H(c->result), QEMU_G2H(c->timeout), QEMU_G2H(c->overlapped), QEMU_G2H(c->completion_routine), QEMU_G2H(c->handle));
}

#endif

struct qemu_GetAddrInfoExOverlappedResult
{
    struct qemu_syscall super;
    uint64_t overlapped;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI GetAddrInfoExOverlappedResult(OVERLAPPED *overlapped)
{
    struct qemu_GetAddrInfoExOverlappedResult call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETADDRINFOEXOVERLAPPEDRESULT);
    call.overlapped = (ULONG_PTR)overlapped;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAddrInfoExOverlappedResult(struct qemu_syscall *call)
{
    struct qemu_GetAddrInfoExOverlappedResult *c = (struct qemu_GetAddrInfoExOverlappedResult *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAddrInfoExOverlappedResult(QEMU_G2H(c->overlapped));
}

#endif

struct qemu_GetAddrInfoExCancel
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI GetAddrInfoExCancel(HANDLE *handle)
{
    struct qemu_GetAddrInfoExCancel call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETADDRINFOEXCANCEL);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAddrInfoExCancel(struct qemu_syscall *call)
{
    struct qemu_GetAddrInfoExCancel *c = (struct qemu_GetAddrInfoExCancel *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAddrInfoExCancel(QEMU_G2H(c->handle));
}

#endif

struct qemu_GetAddrInfoW
{
    struct qemu_syscall super;
    uint64_t nodename;
    uint64_t servname;
    uint64_t hints;
    uint64_t res;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI GetAddrInfoW(LPCWSTR nodename, LPCWSTR servname, const ADDRINFOW *hints, PADDRINFOW *res)
{
    struct qemu_GetAddrInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETADDRINFOW);
    call.nodename = (ULONG_PTR)nodename;
    call.servname = (ULONG_PTR)servname;
    call.hints = (ULONG_PTR)hints;
    call.res = (ULONG_PTR)res;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetAddrInfoW(struct qemu_syscall *call)
{
    struct qemu_GetAddrInfoW *c = (struct qemu_GetAddrInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetAddrInfoW(QEMU_G2H(c->nodename), QEMU_G2H(c->servname), QEMU_G2H(c->hints), QEMU_G2H(c->res));
}

#endif

struct qemu_FreeAddrInfoW
{
    struct qemu_syscall super;
    uint64_t ai;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI FreeAddrInfoW(PADDRINFOW ai)
{
    struct qemu_FreeAddrInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREEADDRINFOW);
    call.ai = (ULONG_PTR)ai;

    qemu_syscall(&call.super);
}

#else

void qemu_FreeAddrInfoW(struct qemu_syscall *call)
{
    struct qemu_FreeAddrInfoW *c = (struct qemu_FreeAddrInfoW *)call;
    WINE_FIXME("Unverified!\n");
    FreeAddrInfoW(QEMU_G2H(c->ai));
}

#endif

struct qemu_FreeAddrInfoExW
{
    struct qemu_syscall super;
    uint64_t ai;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI FreeAddrInfoExW(ADDRINFOEXW *ai)
{
    struct qemu_FreeAddrInfoExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREEADDRINFOEXW);
    call.ai = (ULONG_PTR)ai;

    qemu_syscall(&call.super);
}

#else

void qemu_FreeAddrInfoExW(struct qemu_syscall *call)
{
    struct qemu_FreeAddrInfoExW *c = (struct qemu_FreeAddrInfoExW *)call;
    WINE_FIXME("Unverified!\n");
    FreeAddrInfoExW(QEMU_G2H(c->ai));
}

#endif

struct qemu_WS_getnameinfo
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t salen;
    uint64_t host;
    uint64_t hostlen;
    uint64_t serv;
    uint64_t servlen;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_getnameinfo(const SOCKADDR *sa, socklen_t salen, PCHAR host, DWORD hostlen, PCHAR serv, DWORD servlen, INT flags)
{
    struct qemu_WS_getnameinfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_GETNAMEINFO);
    call.sa = (ULONG_PTR)sa;
    call.salen = (ULONG_PTR)salen;
    call.host = (ULONG_PTR)host;
    call.hostlen = (ULONG_PTR)hostlen;
    call.serv = (ULONG_PTR)serv;
    call.servlen = (ULONG_PTR)servlen;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_getnameinfo(struct qemu_syscall *call)
{
    struct qemu_WS_getnameinfo *c = (struct qemu_WS_getnameinfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_getnameinfo(QEMU_G2H(c->sa), c->salen, QEMU_G2H(c->host), c->hostlen, QEMU_G2H(c->serv), c->servlen, c->flags);
}

#endif

struct qemu_GetNameInfoW
{
    struct qemu_syscall super;
    uint64_t sa;
    uint64_t salen;
    uint64_t host;
    uint64_t hostlen;
    uint64_t serv;
    uint64_t servlen;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI GetNameInfoW(const SOCKADDR *sa, socklen_t salen, PWCHAR host, DWORD hostlen, PWCHAR serv, DWORD servlen, INT flags)
{
    struct qemu_GetNameInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETNAMEINFOW);
    call.sa = (ULONG_PTR)sa;
    call.salen = (ULONG_PTR)salen;
    call.host = (ULONG_PTR)host;
    call.hostlen = (ULONG_PTR)hostlen;
    call.serv = (ULONG_PTR)serv;
    call.servlen = (ULONG_PTR)servlen;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetNameInfoW(struct qemu_syscall *call)
{
    struct qemu_GetNameInfoW *c = (struct qemu_GetNameInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetNameInfoW(QEMU_G2H(c->sa), c->salen, QEMU_G2H(c->host), c->hostlen, QEMU_G2H(c->serv), c->servlen, c->flags);
}

#endif

struct qemu_WS_getservbyport
{
    struct qemu_syscall super;
    uint64_t port;
    uint64_t proto;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI struct WS_servent* WINAPI WS_getservbyport(int port, const char *proto)
{
    struct qemu_WS_getservbyport call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_GETSERVBYPORT);
    call.port = (ULONG_PTR)port;
    call.proto = (ULONG_PTR)proto;

    qemu_syscall(&call.super);

    return (struct WS_servent *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WS_getservbyport(struct qemu_syscall *call)
{
    struct qemu_WS_getservbyport *c = (struct qemu_WS_getservbyport *)call;
    void *ret;
    WINE_TRACE("\n");

    ret = p_getservbyport(c->port, QEMU_G2H(c->proto));
    if (!ret)
    {
        c->super.iret = 0;
        return;
    }

#if GUEST_BIT != HOST_BIT
    c->super.iret = QEMU_H2G(WS_dup_se(ret));
#else
    c->super.iret = QEMU_H2G(ret);
#endif
}

#endif

struct qemu_WS_gethostname
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t namelen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WS_gethostname(char *name, int namelen)
{
    struct qemu_WS_gethostname call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_GETHOSTNAME);
    call.name = (ULONG_PTR)name;
    call.namelen = namelen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_gethostname(struct qemu_syscall *call)
{
    struct qemu_WS_gethostname *c = (struct qemu_WS_gethostname *)call;
    WINE_TRACE("\n");
    c->super.iret = p_gethostname(QEMU_G2H(c->name), c->namelen);
}

#endif

struct qemu_WSAEnumNetworkEvents
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t hEvent;
    uint64_t lpEvent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WSAEnumNetworkEvents(SOCKET s, WSAEVENT hEvent, LPWSANETWORKEVENTS lpEvent)
{
    struct qemu_WSAEnumNetworkEvents call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAENUMNETWORKEVENTS);
    call.s = guest_SOCKET_g2h(s);
    call.hEvent = (ULONG_PTR)hEvent;
    call.lpEvent = (ULONG_PTR)lpEvent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAEnumNetworkEvents(struct qemu_syscall *call)
{
    struct qemu_WSAEnumNetworkEvents *c = (struct qemu_WSAEnumNetworkEvents *)call;
    WINE_TRACE("\n");

    /* WSANETWORKEVENTS has the same size in 32 and 64 bit. */
    c->super.iret = WSAEnumNetworkEvents(c->s, (WSAEVENT)c->hEvent, QEMU_G2H(c->lpEvent));
}

#endif

struct qemu_WSAEventSelect
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t hEvent;
    uint64_t lEvent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WSAEventSelect(SOCKET s, WSAEVENT hEvent, LONG lEvent)
{
    struct qemu_WSAEventSelect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAEVENTSELECT);
    call.s = guest_SOCKET_g2h(s);
    call.hEvent = (ULONG_PTR)hEvent;
    call.lEvent = lEvent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAEventSelect(struct qemu_syscall *call)
{
    struct qemu_WSAEventSelect *c = (struct qemu_WSAEventSelect *)call;
    WINE_TRACE("\n");
    c->super.iret = WSAEventSelect(c->s, (WSAEVENT)c->hEvent, c->lEvent);
}

#endif

struct qemu_WSAGetOverlappedResult
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t lpOverlapped;
    uint64_t lpcbTransfer;
    uint64_t fWait;
    uint64_t lpdwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WSAGetOverlappedResult(SOCKET s, LPWSAOVERLAPPED lpOverlapped, LPDWORD lpcbTransfer, BOOL fWait, LPDWORD lpdwFlags)
{
    struct qemu_WSAGetOverlappedResult call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAGETOVERLAPPEDRESULT);
    call.s = guest_SOCKET_g2h(s);
    call.lpOverlapped = (ULONG_PTR)lpOverlapped;
    call.lpcbTransfer = (ULONG_PTR)lpcbTransfer;
    call.fWait = fWait;
    call.lpdwFlags = (ULONG_PTR)lpdwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAGetOverlappedResult(struct qemu_syscall *call)
{
    struct qemu_WSAGetOverlappedResult *c = (struct qemu_WSAGetOverlappedResult *)call;
    NTSTATUS status;
    struct qemu_OVERLAPPED *ov32;
    HANDLE event;
    DWORD *transfer, *flags;
    WINE_TRACE("\n");

    transfer = QEMU_G2H(c->lpcbTransfer);
    flags = QEMU_G2H(c->lpdwFlags);
#if GUEST_BIT == HOST_BIT
    c->super.iret = WSAGetOverlappedResult(c->s, QEMU_G2H(c->lpOverlapped), transfer, c->fWait, flags);
    return;
#endif

    ov32 = QEMU_G2H(c->lpOverlapped);
    if (!ov32)
    {
        WINE_ERR( "Invalid pointer\n" );
        SetLastError(WSA_INVALID_PARAMETER);
        c->super.iret = FALSE;
        return;
    }

    status = ov32->Internal;
    if (status == STATUS_PENDING)
    {
        if (!c->fWait)
        {
            SetLastError( WSA_IO_INCOMPLETE );
            c->super.iret = FALSE;
            return;
        }

        event = HANDLE_g2h(ov32->hEvent);
        if (event)
        {
            if (WaitForSingleObject(event, INFINITE ) == WAIT_FAILED)
            {
                c->super.iret = FALSE;
                return;
            }
        }
        else
        {
            OVERLAPPED copy;
            OVERLAPPED_g2h(&copy, ov32);
            c->super.iret = WSAGetOverlappedResult(c->s, &copy, QEMU_G2H(c->lpcbTransfer),
                    c->fWait, QEMU_G2H(c->lpdwFlags));
            return;
        }
        status = ov32->Internal;
    }

    if (transfer)
        *transfer = ov32->InternalHigh;

    if (flags)
        *flags = ov32->Offset;

    if (status) SetLastError( RtlNtStatusToDosError(status) );
    c->super.iret = !status;
}

#endif

struct qemu_WSAAsyncSelect
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t hWnd;
    uint64_t uMsg;
    uint64_t lEvent;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAAsyncSelect(SOCKET s, HWND hWnd, UINT uMsg, LONG lEvent)
{
    struct qemu_WSAAsyncSelect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAASYNCSELECT);
    call.s = guest_SOCKET_g2h(s);
    call.hWnd = (ULONG_PTR)hWnd;
    call.uMsg = (ULONG_PTR)uMsg;
    call.lEvent = (ULONG_PTR)lEvent;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAAsyncSelect(struct qemu_syscall *call)
{
    struct qemu_WSAAsyncSelect *c = (struct qemu_WSAAsyncSelect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAAsyncSelect(c->s, QEMU_G2H(c->hWnd), c->uMsg, c->lEvent);
}

#endif

struct qemu_WSACreateEvent
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WSAEVENT WINAPI WSACreateEvent(void)
{
    struct qemu_WSACreateEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSACREATEEVENT);

    qemu_syscall(&call.super);

    return (WSAEVENT)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WSACreateEvent(struct qemu_syscall *call)
{
    struct qemu_WSACreateEvent *c = (struct qemu_WSACreateEvent *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)WSACreateEvent();
}

#endif

struct qemu_WSACloseEvent
{
    struct qemu_syscall super;
    uint64_t event;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WSACloseEvent(WSAEVENT event)
{
    struct qemu_WSACloseEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSACLOSEEVENT);
    call.event = (ULONG_PTR)event;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSACloseEvent(struct qemu_syscall *call)
{
    struct qemu_WSACloseEvent *c = (struct qemu_WSACloseEvent *)call;
    WINE_TRACE("\n");
    c->super.iret = WSACloseEvent((WSAEVENT)c->event);
}

#endif

struct qemu_WSASocketA
{
    struct qemu_syscall super;
    uint64_t af;
    uint64_t type;
    uint64_t protocol;
    uint64_t lpProtocolInfo;
    uint64_t g;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SOCKET WINAPI WSASocketA(int af, int type, int protocol, LPWSAPROTOCOL_INFOA lpProtocolInfo, GROUP g, DWORD dwFlags)
{
    struct qemu_WSASocketA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSASOCKETA);
    call.af = af;
    call.type = type;
    call.protocol = protocol;
    call.lpProtocolInfo = (ULONG_PTR)lpProtocolInfo;
    call.g = g;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSASocketA(struct qemu_syscall *call)
{
    struct qemu_WSASocketA *c = (struct qemu_WSASocketA *)call;
    WINE_TRACE("\n");

    /* WSAPROTOCOL_INFO has the same size in 32 and 64 bit. */
    c->super.iret = WSASocketA(c->af, c->type, c->protocol, QEMU_G2H(c->lpProtocolInfo), c->g, c->dwFlags);
}

#endif

struct qemu_WSASocketW
{
    struct qemu_syscall super;
    uint64_t af;
    uint64_t type;
    uint64_t protocol;
    uint64_t lpProtocolInfo;
    uint64_t g;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SOCKET WINAPI WSASocketW(int af, int type, int protocol, LPWSAPROTOCOL_INFOW lpProtocolInfo, GROUP g, DWORD dwFlags)
{
    struct qemu_WSASocketW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSASOCKETW);
    call.af = (ULONG_PTR)af;
    call.type = (ULONG_PTR)type;
    call.protocol = (ULONG_PTR)protocol;
    call.lpProtocolInfo = (ULONG_PTR)lpProtocolInfo;
    call.g = (ULONG_PTR)g;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSASocketW(struct qemu_syscall *call)
{
    struct qemu_WSASocketW *c = (struct qemu_WSASocketW *)call;
    WINE_FIXME("Unverified!\n");

    /* WSAPROTOCOL_INFO has the same size in 32 and 64 bit. */
    c->super.iret = WSASocketW(c->af, c->type, c->protocol, QEMU_G2H(c->lpProtocolInfo), c->g, c->dwFlags);
}

#endif

struct qemu_WSAJoinLeaf
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t addr;
    uint64_t addrlen;
    uint64_t lpCallerData;
    uint64_t lpCalleeData;
    uint64_t lpSQOS;
    uint64_t lpGQOS;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI SOCKET WINAPI WSAJoinLeaf(SOCKET s, const struct sockaddr *addr, int addrlen, LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS, DWORD dwFlags)
{
    struct qemu_WSAJoinLeaf call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAJOINLEAF);
    call.s = guest_SOCKET_g2h(s);
    call.addr = (ULONG_PTR)addr;
    call.addrlen = (ULONG_PTR)addrlen;
    call.lpCallerData = (ULONG_PTR)lpCallerData;
    call.lpCalleeData = (ULONG_PTR)lpCalleeData;
    call.lpSQOS = (ULONG_PTR)lpSQOS;
    call.lpGQOS = (ULONG_PTR)lpGQOS;
    call.dwFlags = (ULONG_PTR)dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAJoinLeaf(struct qemu_syscall *call)
{
    struct qemu_WSAJoinLeaf *c = (struct qemu_WSAJoinLeaf *)call;
    WINE_FIXME("Unverified!\n");

    /* WS_sockaddr has the same size in 32 and 64 bit. */
    c->super.iret = WSAJoinLeaf(c->s, QEMU_G2H(c->addr), c->addrlen, QEMU_G2H(c->lpCallerData), QEMU_G2H(c->lpCalleeData), QEMU_G2H(c->lpSQOS), QEMU_G2H(c->lpGQOS), c->dwFlags);
}

#endif

struct qemu___WSAFDIsSet
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t set;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI __WSAFDIsSet(SOCKET s, fd_set *set)
{
    struct qemu___WSAFDIsSet call;
    call.super.id = QEMU_SYSCALL_ID(CALL___WSAFDISSET);
    call.s = guest_SOCKET_g2h(s);
    call.set = (ULONG_PTR)set;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu___WSAFDIsSet(struct qemu_syscall *call)
{
    struct qemu___WSAFDIsSet *c = (struct qemu___WSAFDIsSet *)call;
    WS_fd_set stack, *set = &stack;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    set = QEMU_G2H(c->set);
#else
    if (c->set)
        WS_fd_set_g2h(set, QEMU_G2H(c->set));
    else
        set = NULL;
#endif

    c->super.iret = __WSAFDIsSet(c->s, set);
}

#endif

struct qemu_WSAIsBlocking
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WSAIsBlocking(void)
{
    struct qemu_WSAIsBlocking call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAISBLOCKING);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAIsBlocking(struct qemu_syscall *call)
{
    struct qemu_WSAIsBlocking *c = (struct qemu_WSAIsBlocking *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAIsBlocking();
}

#endif

struct qemu_WSACancelBlockingCall
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSACancelBlockingCall(void)
{
    struct qemu_WSACancelBlockingCall call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSACANCELBLOCKINGCALL);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSACancelBlockingCall(struct qemu_syscall *call)
{
    struct qemu_WSACancelBlockingCall *c = (struct qemu_WSACancelBlockingCall *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSACancelBlockingCall();
}

#endif

struct qemu_WSASetBlockingHook
{
    struct qemu_syscall super;
    uint64_t lpBlockFunc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI FARPROC WINAPI WSASetBlockingHook(FARPROC lpBlockFunc)
{
    struct qemu_WSASetBlockingHook call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSASETBLOCKINGHOOK);
    call.lpBlockFunc = (ULONG_PTR)lpBlockFunc;

    qemu_syscall(&call.super);

    return (FARPROC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WSASetBlockingHook(struct qemu_syscall *call)
{
    struct qemu_WSASetBlockingHook *c = (struct qemu_WSASetBlockingHook *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)WSASetBlockingHook(QEMU_G2H(c->lpBlockFunc));
}

#endif

struct qemu_WSAUnhookBlockingHook
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAUnhookBlockingHook(void)
{
    struct qemu_WSAUnhookBlockingHook call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAUNHOOKBLOCKINGHOOK);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAUnhookBlockingHook(struct qemu_syscall *call)
{
    struct qemu_WSAUnhookBlockingHook *c = (struct qemu_WSAUnhookBlockingHook *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAUnhookBlockingHook();
}

#endif

struct qemu_WSABufOp
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t lpBuffers;
    uint64_t dwBufferCount;
    uint64_t NumberOfBytesTransfered;
    uint64_t lpFlags;
    uint64_t dwFlags;
    uint64_t sockaddr;
    uint64_t lpSockaddr_len;
    uint64_t sockaddr_len;
    uint64_t lpOverlapped;
    uint64_t lpCompletionRoutine;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD NumberOfBytesReceived, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    struct qemu_WSABufOp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSARECV);
    call.s = guest_SOCKET_g2h(s);
    call.lpBuffers = (ULONG_PTR)lpBuffers;
    call.dwBufferCount = (ULONG_PTR)dwBufferCount;
    call.NumberOfBytesTransfered = (ULONG_PTR)NumberOfBytesReceived;
    call.lpFlags = (ULONG_PTR)lpFlags;
    call.lpOverlapped = (ULONG_PTR)lpOverlapped;
    call.lpCompletionRoutine = (ULONG_PTR)lpCompletionRoutine;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI INT WINAPI WSASend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    struct qemu_WSABufOp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSASEND);
    call.s = guest_SOCKET_g2h(s);
    call.lpBuffers = (ULONG_PTR)lpBuffers;
    call.dwBufferCount = (ULONG_PTR)dwBufferCount;
    call.NumberOfBytesTransfered = (ULONG_PTR)lpNumberOfBytesSent;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.lpOverlapped = (ULONG_PTR)lpOverlapped;
    call.lpCompletionRoutine = (ULONG_PTR)lpCompletionRoutine;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI INT WINAPI WSASendTo(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, const struct sockaddr *to, int tolen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    struct qemu_WSABufOp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSASENDTO);
    call.s = guest_SOCKET_g2h(s);
    call.lpBuffers = (ULONG_PTR)lpBuffers;
    call.dwBufferCount = (ULONG_PTR)dwBufferCount;
    call.NumberOfBytesTransfered = (ULONG_PTR)lpNumberOfBytesSent;
    call.dwFlags = (ULONG_PTR)dwFlags;
    call.sockaddr = (ULONG_PTR)to;
    call.sockaddr_len = (ULONG_PTR)tolen;
    call.lpOverlapped = (ULONG_PTR)lpOverlapped;
    call.lpCompletionRoutine = (ULONG_PTR)lpCompletionRoutine;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI INT WINAPI WSARecvFrom(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, struct sockaddr *lpFrom, LPINT lpFromlen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    struct qemu_WSABufOp call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSARECVFROM);
    call.s = guest_SOCKET_g2h(s);
    call.lpBuffers = (ULONG_PTR)lpBuffers;
    call.dwBufferCount = (ULONG_PTR)dwBufferCount;
    call.NumberOfBytesTransfered = (ULONG_PTR)lpNumberOfBytesRecvd;
    call.lpFlags = (ULONG_PTR)lpFlags;
    call.sockaddr = (ULONG_PTR)lpFrom;
    call.lpSockaddr_len = (ULONG_PTR)lpFromlen;
    call.lpOverlapped = (ULONG_PTR)lpOverlapped;
    call.lpCompletionRoutine = (ULONG_PTR)lpCompletionRoutine;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static uint64_t call_op(uint64_t op, SOCKET s, WSABUF *buffers, DWORD buffer_count, DWORD *bytes_transfered,
        DWORD dwFlags, DWORD *lpFlags, struct WS_sockaddr *addr, INT addr_len, INT *lp_addr_len,
        WSAOVERLAPPED *ov, LPWSAOVERLAPPED_COMPLETION_ROUTINE completion)
{
    switch (op)
    {
        case QEMU_SYSCALL_ID(CALL_WSARECV):
            return WSARecv(s, buffers, buffer_count, bytes_transfered, lpFlags, ov, completion);
        case QEMU_SYSCALL_ID(CALL_WSARECVFROM):
            return WSARecvFrom(s, buffers, buffer_count, bytes_transfered, lpFlags, addr, lp_addr_len, ov, completion);
        case QEMU_SYSCALL_ID(CALL_WSASEND):
            return WSASend(s, buffers, buffer_count, bytes_transfered, dwFlags, ov, completion);
        case QEMU_SYSCALL_ID(CALL_WSASENDTO):
            return WSASendTo(s, buffers, buffer_count, bytes_transfered, dwFlags, addr, addr_len, ov, completion);
    }
}

void qemu_WSABufOp(struct qemu_syscall *call)
{
    struct qemu_WSABufOp *c = (struct qemu_WSABufOp *)call;
    WSABUF stackbuf[10], *buffers;
    struct qemu_WSABUF *guest_buffers;
    unsigned int i;
    DWORD buf_count;
    struct qemu_OVERLAPPED *ov32;
    struct OVERLAPPED_data *ov_wrapper;
    HANDLE guest_event;
    DWORD flags;

    switch (c->super.id)
    {
        case QEMU_SYSCALL_ID(CALL_WSARECV):
            WINE_TRACE("WSARecv\n");
            flags = c->lpFlags ? *(DWORD *)QEMU_G2H(c->lpFlags) : 0;
            break;
        case QEMU_SYSCALL_ID(CALL_WSARECVFROM):
            WINE_TRACE("WSARecvFrom\n");
            flags = c->lpFlags ? *(DWORD *)QEMU_G2H(c->lpFlags) : 0;
            break;
        case QEMU_SYSCALL_ID(CALL_WSASEND):
            WINE_TRACE("WSASend\n");
            flags = c->dwFlags;
            break;
        case QEMU_SYSCALL_ID(CALL_WSASENDTO):
            WINE_TRACE("WSASendTo\n");
            flags = c->dwFlags;
            break;
        default:
            WINE_ERR("Unexpected op 0x%lx\n", c->super.id);
    }

    buf_count = c->dwBufferCount;
#if GUEST_BIT == HOST_BIT
    if (c->lpCompletionRoutine)
        WINE_FIXME("Completion routine not handled yet.\n");

    c->super.iret = call_op(c->super.id, c->s, QEMU_G2H(c->lpBuffers), buf_count, QEMU_G2H(c->NumberOfBytesTransfered),
            c->dwFlags, QEMU_G2H(c->lpFlags), QEMU_G2H(c->sockaddr), c->sockaddr_len, QEMU_G2H(c->lpSockaddr_len),
            QEMU_G2H(c->lpOverlapped), QEMU_G2H(c->lpCompletionRoutine));
    return;
#endif

    ov32 = QEMU_G2H(c->lpOverlapped);
    if (ov32)
    {
        ov_wrapper = p_alloc_OVERLAPPED_data(ov32, c->lpCompletionRoutine, TRUE);
        ov_wrapper->wsa = TRUE;
        ov_wrapper->wsa_flags = flags;
        guest_event = HANDLE_g2h(ov32->hEvent);
    }
    else
    {
        WINE_TRACE("Synchronous operation, easy...\n");
        ov_wrapper = NULL;
    }

    guest_buffers = (struct qemu_WSABUF *)QEMU_G2H(c->lpBuffers);
    if (!guest_buffers)
    {
        WINE_WARN("Buffers is NULL.\n");
        c->super.iret = call_op(c->super.id, c->s, NULL, buf_count, QEMU_G2H(c->NumberOfBytesTransfered),
                c->dwFlags, QEMU_G2H(c->lpFlags), QEMU_G2H(c->sockaddr), c->sockaddr_len, QEMU_G2H(c->lpSockaddr_len),
                ov_wrapper ? &ov_wrapper->ov : NULL, NULL);
        buffers = NULL;
        goto done;
    }

    if (!ov32 && buf_count < sizeof(stackbuf) / sizeof(*stackbuf))
        buffers = stackbuf;
    else
        buffers = HeapAlloc(GetProcessHeap(), 0, sizeof(*buffers) * buf_count);

    for (i = 0; i < buf_count; ++i)
        WSABUF_g2h(&buffers[i], &guest_buffers[i]);

    c->super.iret = call_op(c->super.id, c->s, buffers, buf_count, QEMU_G2H(c->NumberOfBytesTransfered),
            c->dwFlags, QEMU_G2H(c->lpFlags), QEMU_G2H(c->sockaddr), c->sockaddr_len, QEMU_G2H(c->lpSockaddr_len),
            ov_wrapper ? &ov_wrapper->ov : NULL, NULL);

done:
    if (ov32)
    {
        OVERLAPPED_h2g(ov32, &ov_wrapper->ov);
        ov32->hEvent = (ULONG_PTR)guest_event;
        ov_wrapper->buffers = buffers;
        p_process_OVERLAPPED_data(c->super.iret == SOCKET_ERROR ? 0 : 1, ov_wrapper);
    }
    else if (buffers != stackbuf)
    {
        HeapFree(GetProcessHeap(), 0, buffers);
    }
}

#endif

struct qemu_WSCInstallProvider
{
    struct qemu_syscall super;
    uint64_t lpProviderId;
    uint64_t lpszProviderDllPath;
    uint64_t lpProtocolInfoList;
    uint64_t dwNumberOfEntries;
    uint64_t lpErrno;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSCInstallProvider(const LPGUID lpProviderId, LPCWSTR lpszProviderDllPath, const LPWSAPROTOCOL_INFOW lpProtocolInfoList, DWORD dwNumberOfEntries, LPINT lpErrno)
{
    struct qemu_WSCInstallProvider call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSCINSTALLPROVIDER);
    call.lpProviderId = (ULONG_PTR)lpProviderId;
    call.lpszProviderDllPath = (ULONG_PTR)lpszProviderDllPath;
    call.lpProtocolInfoList = (ULONG_PTR)lpProtocolInfoList;
    call.dwNumberOfEntries = (ULONG_PTR)dwNumberOfEntries;
    call.lpErrno = (ULONG_PTR)lpErrno;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSCInstallProvider(struct qemu_syscall *call)
{
    struct qemu_WSCInstallProvider *c = (struct qemu_WSCInstallProvider *)call;
    WINE_FIXME("Unverified!\n");

    /* WSAPROTOCOL_INFO has the same size in 32 and 64 bit. */
    c->super.iret = WSCInstallProvider(QEMU_G2H(c->lpProviderId), QEMU_G2H(c->lpszProviderDllPath), QEMU_G2H(c->lpProtocolInfoList), c->dwNumberOfEntries, QEMU_G2H(c->lpErrno));
}

#endif

struct qemu_WSCDeinstallProvider
{
    struct qemu_syscall super;
    uint64_t lpProviderId;
    uint64_t lpErrno;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSCDeinstallProvider(LPGUID lpProviderId, LPINT lpErrno)
{
    struct qemu_WSCDeinstallProvider call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSCDEINSTALLPROVIDER);
    call.lpProviderId = (ULONG_PTR)lpProviderId;
    call.lpErrno = (ULONG_PTR)lpErrno;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSCDeinstallProvider(struct qemu_syscall *call)
{
    struct qemu_WSCDeinstallProvider *c = (struct qemu_WSCDeinstallProvider *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSCDeinstallProvider(QEMU_G2H(c->lpProviderId), QEMU_G2H(c->lpErrno));
}

#endif

struct qemu_WSAAccept
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t addr;
    uint64_t addrlen;
    uint64_t lpfnCondition;
    uint64_t dwCallbackData;
    uint64_t wrapper;
};

struct qemu_WSAAccept_cb
{
    uint64_t func;
    uint64_t callerId;
    uint64_t callerData;
    uint64_t Qos;
    uint64_t GQOS;
    uint64_t calleeId;
    uint64_t calleeData;
    uint64_t g;
    uint64_t data;
};

#ifdef QEMU_DLL_GUEST

static int __fastcall WSAAccept_guest_proc(struct qemu_WSAAccept_cb *data)
{
    LPCONDITIONPROC func = (LPCONDITIONPROC)(ULONG_PTR)data->func;
    return func((WSABUF *)(ULONG_PTR)data->callerId, (WSABUF *)(ULONG_PTR)data->callerData,
            (QOS *)(ULONG_PTR)data->Qos, (QOS *)(ULONG_PTR)data->GQOS, (WSABUF *)(ULONG_PTR)data->calleeId,
            (WSABUF *)(ULONG_PTR)data->calleeData,
            (GROUP *)(ULONG_PTR)data->g, data->data);
}

WINBASEAPI SOCKET WINAPI WSAAccept(SOCKET s, struct sockaddr *addr, LPINT addrlen,
        LPCONDITIONPROC lpfnCondition, DWORD_PTR dwCallbackData)
{
    struct qemu_WSAAccept call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAACCEPT);
    call.s = guest_SOCKET_g2h(s);
    call.addr = (ULONG_PTR)addr;
    call.addrlen = (ULONG_PTR)addrlen;
    call.lpfnCondition = (ULONG_PTR)lpfnCondition;
    call.dwCallbackData = (ULONG_PTR)dwCallbackData;
    call.wrapper = (ULONG_PTR)WSAAccept_guest_proc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct WSAAccept_data
{
    uint64_t func, data, wrapper;
};

static int CALLBACK WSAAccept_host_proc(WSABUF *callerId, WSABUF *callerData, QOS *pQos,
        QOS *lpGQOS, WSABUF *calleeId, WSABUF *calleeData, GROUP *g, DWORD_PTR callbackData)
{
    struct WSAAccept_data *data = (struct WSAAccept_data *)callbackData;
    struct qemu_WSAAccept_cb call;
    int ret;
    struct qemu_WSABUF guest_caller_id, guest_caller_data, guest_callee_id, guest_callee_data;

#if GUEST_BIT == HOST_BIT
    call.callerId = QEMU_H2G(callerId);
    call.callerData = QEMU_H2G(callerData);
    call.calleeId = QEMU_H2G(calleeId);
    call.calleeData = QEMU_H2G(calleeData);
    call.Qos = QEMU_H2G(pQos);
    call.GQOS = QEMU_H2G(lpGQOS);
#else
    WSABUF_h2g(&guest_caller_id, callerId);
    WSABUF_h2g(&guest_caller_data, callerData);
    WSABUF_h2g(&guest_callee_id, calleeId);
    WSABUF_h2g(&guest_callee_data, calleeData);

    call.callerId = QEMU_H2G(&guest_caller_id);
    call.callerData = QEMU_H2G(&guest_caller_data);
    call.calleeId = QEMU_H2G(&guest_callee_id);
    call.calleeData = QEMU_H2G(&guest_callee_data);

    if (pQos || lpGQOS)
        WINE_FIXME("QOS structures not translated to 32 bit yet.\n");
#endif
    call.g = QEMU_H2G(g);
    call.data = data->data;
    call.func = data->func;

    WINE_TRACE("Calling guest callback 0x%lx.\n", call.func);
    ret = qemu_ops->qemu_execute(QEMU_G2H(data->wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned %d.\n", ret);

    return ret;
}

void qemu_WSAAccept(struct qemu_syscall *call)
{
    struct qemu_WSAAccept *c = (struct qemu_WSAAccept *)call;
    struct WSAAccept_data data;
    WINE_TRACE("\n");

    data.func = c->lpfnCondition;
    data.data = c->dwCallbackData;
    data.wrapper = c->wrapper;

    /* WS_sockaddr has the same size in 32 and 64 bit. */
    c->super.iret = WSAAccept(c->s, QEMU_G2H(c->addr), QEMU_G2H(c->addrlen),
            c->lpfnCondition ? WSAAccept_host_proc : NULL, (DWORD_PTR)&data);
}

#endif

struct qemu_WSADuplicateSocketA
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t dwProcessId;
    uint64_t lpProtocolInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WSADuplicateSocketA(SOCKET s, DWORD dwProcessId, LPWSAPROTOCOL_INFOA lpProtocolInfo)
{
    struct qemu_WSADuplicateSocketA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSADUPLICATESOCKETA);
    call.s = guest_SOCKET_g2h(s);
    call.dwProcessId = dwProcessId;
    call.lpProtocolInfo = (ULONG_PTR)lpProtocolInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSADuplicateSocketA(struct qemu_syscall *call)
{
    struct qemu_WSADuplicateSocketA *c = (struct qemu_WSADuplicateSocketA *)call;
    WINE_TRACE("\n");

    /* WSAPROTOCOL_INFO has the same size in 32 and 64 bit. */
    c->super.iret = WSADuplicateSocketA(c->s, c->dwProcessId, QEMU_G2H(c->lpProtocolInfo));
}

#endif

struct qemu_WSADuplicateSocketW
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t dwProcessId;
    uint64_t lpProtocolInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WSADuplicateSocketW(SOCKET s, DWORD dwProcessId, LPWSAPROTOCOL_INFOW lpProtocolInfo)
{
    struct qemu_WSADuplicateSocketW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSADUPLICATESOCKETW);
    call.s = guest_SOCKET_g2h(s);
    call.dwProcessId = (ULONG_PTR)dwProcessId;
    call.lpProtocolInfo = (ULONG_PTR)lpProtocolInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSADuplicateSocketW(struct qemu_syscall *call)
{
    struct qemu_WSADuplicateSocketW *c = (struct qemu_WSADuplicateSocketW *)call;
    WINE_FIXME("Unverified!\n");

    /* WSAPROTOCOL_INFO has the same size in 32 and 64 bit. */
    c->super.iret = WSADuplicateSocketW(c->s, c->dwProcessId, QEMU_G2H(c->lpProtocolInfo));
}

#endif

struct qemu_WSAInstallServiceClassA
{
    struct qemu_syscall super;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WSAInstallServiceClassA(LPWSASERVICECLASSINFOA info)
{
    struct qemu_WSAInstallServiceClassA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAINSTALLSERVICECLASSA);
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAInstallServiceClassA(struct qemu_syscall *call)
{
    struct qemu_WSAInstallServiceClassA *c = (struct qemu_WSAInstallServiceClassA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAInstallServiceClassA(QEMU_G2H(c->info));
}

#endif

struct qemu_WSAInstallServiceClassW
{
    struct qemu_syscall super;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WSAInstallServiceClassW(LPWSASERVICECLASSINFOW info)
{
    struct qemu_WSAInstallServiceClassW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAINSTALLSERVICECLASSW);
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAInstallServiceClassW(struct qemu_syscall *call)
{
    struct qemu_WSAInstallServiceClassW *c = (struct qemu_WSAInstallServiceClassW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAInstallServiceClassW(QEMU_G2H(c->info));
}

#endif

struct qemu_WSARemoveServiceClass
{
    struct qemu_syscall super;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI WSARemoveServiceClass(LPGUID info)
{
    struct qemu_WSARemoveServiceClass call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAREMOVESERVICECLASS);
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSARemoveServiceClass(struct qemu_syscall *call)
{
    struct qemu_WSARemoveServiceClass *c = (struct qemu_WSARemoveServiceClass *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSARemoveServiceClass(QEMU_G2H(c->info));
}

#endif

struct qemu_WS_inet_ntop
{
    struct qemu_syscall super;
    uint64_t family;
    uint64_t addr;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCSTR WINAPI WS_inet_ntop(INT family, PVOID addr, PSTR buffer, SIZE_T len)
{
    struct qemu_WS_inet_ntop call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_INET_NTOP);
    call.family = family;
    call.addr = (ULONG_PTR)addr;
    call.buffer = (ULONG_PTR)buffer;
    call.len = len;

    qemu_syscall(&call.super);

    return (const char *)(ULONG_PTR)call.super.iret;
}

#else

void qemu_WS_inet_ntop(struct qemu_syscall *call)
{
    struct qemu_WS_inet_ntop *c = (struct qemu_WS_inet_ntop *)call;
    WINE_TRACE("\n");

#if GUEST_BIT != HOST_BIT
    if (c->family != WS_AF_INET && c->family != WS_AF_INET6 && c->family != WS_AF_UNSPEC)
        WINE_FIXME("Untested family %lx.\n", c->family);
#endif

    c->super.iret = QEMU_H2G(p_inet_ntop(c->family, QEMU_G2H(c->addr), QEMU_G2H(c->buffer), c->len));
}

#endif

struct qemu_WS_inet_pton
{
    struct qemu_syscall super;
    uint64_t family;
    uint64_t addr;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WS_inet_pton(INT family, PCSTR addr, PVOID buffer)
{
    struct qemu_WS_inet_pton call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WS_INET_PTON);
    call.family = family;
    call.addr = (ULONG_PTR)addr;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WS_inet_pton(struct qemu_syscall *call)
{
    struct qemu_WS_inet_pton *c = (struct qemu_WS_inet_pton *)call;
    WINE_TRACE("\n");

#if GUEST_BIT != HOST_BIT
    if (c->family != WS_AF_INET && c->family != WS_AF_INET6 && c->family != WS_AF_UNSPEC)
        WINE_FIXME("Untested family %lx.\n", c->family);
#endif

    c->super.iret = p_inet_pton(c->family, QEMU_G2H(c->addr), QEMU_G2H(c->buffer));
}

#endif

struct qemu_InetPtonW
{
    struct qemu_syscall super;
    uint64_t family;
    uint64_t addr;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI InetPtonW(INT family, PCWSTR addr, PVOID buffer)
{
    struct qemu_InetPtonW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INETPTONW);
    call.family = family;
    call.addr = (ULONG_PTR)addr;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_InetPtonW(struct qemu_syscall *call)
{
    struct qemu_InetPtonW *c = (struct qemu_InetPtonW *)call;
    WINE_TRACE("\n");

#if GUEST_BIT != HOST_BIT
    if (c->family != WS_AF_INET && c->family != WS_AF_INET6 && c->family != WS_AF_UNSPEC)
        WINE_FIXME("Untested family %lx.\n", c->family);
#endif

    c->super.iret = InetPtonW(c->family, QEMU_G2H(c->addr), QEMU_G2H(c->buffer));
}

#endif

struct qemu_InetNtopW
{
    struct qemu_syscall super;
    uint64_t family;
    uint64_t addr;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PCWSTR WINAPI wininet_InetNtopW(INT family, PVOID addr, PWSTR buffer, SIZE_T len)
{
    struct qemu_InetNtopW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_INETNTOPW);
    call.family = family;
    call.addr = (ULONG_PTR)addr;
    call.buffer = (ULONG_PTR)buffer;
    call.len = len;

    qemu_syscall(&call.super);

    return (PCWSTR)(ULONG_PTR)call.super.iret;
}

#else

void qemu_InetNtopW(struct qemu_syscall *call)
{
    struct qemu_InetNtopW *c = (struct qemu_InetNtopW *)call;
    WINE_TRACE("\n");

#if GUEST_BIT != HOST_BIT
    if (c->family != WS_AF_INET && c->family != WS_AF_INET6 && c->family != WS_AF_UNSPEC)
        WINE_FIXME("Untested family %lx.\n", c->family);
#endif

    c->super.iret = (ULONG_PTR)InetNtopW(c->family, QEMU_G2H(c->addr), QEMU_G2H(c->buffer), c->len);
}

#endif

struct qemu_WSAStringToAddressA
{
    struct qemu_syscall super;
    uint64_t AddressString;
    uint64_t AddressFamily;
    uint64_t lpProtocolInfo;
    uint64_t lpAddress;
    uint64_t lpAddressLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAStringToAddressA(LPSTR AddressString, INT AddressFamily, LPWSAPROTOCOL_INFOA lpProtocolInfo,
        LPSOCKADDR lpAddress, LPINT lpAddressLength)
{
    struct qemu_WSAStringToAddressA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSASTRINGTOADDRESSA);
    call.AddressString = (ULONG_PTR)AddressString;
    call.AddressFamily = AddressFamily;
    call.lpProtocolInfo = (ULONG_PTR)lpProtocolInfo;
    call.lpAddress = (ULONG_PTR)lpAddress;
    call.lpAddressLength = (ULONG_PTR)lpAddressLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAStringToAddressA(struct qemu_syscall *call)
{
    struct qemu_WSAStringToAddressA *c = (struct qemu_WSAStringToAddressA *)call;
    WINE_TRACE("\n");

    /* WSAPROTOCOL_INFO has the same size in 32 and 64 bit. */
    c->super.iret = WSAStringToAddressA(QEMU_G2H(c->AddressString), c->AddressFamily, QEMU_G2H(c->lpProtocolInfo),
            QEMU_G2H(c->lpAddress), QEMU_G2H(c->lpAddressLength));
}

#endif

struct qemu_WSAStringToAddressW
{
    struct qemu_syscall super;
    uint64_t AddressString;
    uint64_t AddressFamily;
    uint64_t lpProtocolInfo;
    uint64_t lpAddress;
    uint64_t lpAddressLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAStringToAddressW(LPWSTR AddressString, INT AddressFamily, LPWSAPROTOCOL_INFOW lpProtocolInfo,
        LPSOCKADDR lpAddress, LPINT lpAddressLength)
{
    struct qemu_WSAStringToAddressW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSASTRINGTOADDRESSW);
    call.AddressString = (ULONG_PTR)AddressString;
    call.AddressFamily = AddressFamily;
    call.lpProtocolInfo = (ULONG_PTR)lpProtocolInfo;
    call.lpAddress = (ULONG_PTR)lpAddress;
    call.lpAddressLength = (ULONG_PTR)lpAddressLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAStringToAddressW(struct qemu_syscall *call)
{
    struct qemu_WSAStringToAddressW *c = (struct qemu_WSAStringToAddressW *)call;
    WINE_TRACE("\n");

    /* WSAPROTOCOL_INFO has the same size in 32 and 64 bit. */
    c->super.iret = WSAStringToAddressW(QEMU_G2H(c->AddressString), c->AddressFamily, QEMU_G2H(c->lpProtocolInfo),
            QEMU_G2H(c->lpAddress), QEMU_G2H(c->lpAddressLength));
}

#endif

struct qemu_WSAAddressToStringA
{
    struct qemu_syscall super;
    uint64_t sockaddr;
    uint64_t len;
    uint64_t info;
    uint64_t string;
    uint64_t lenstr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAAddressToStringA(LPSOCKADDR sockaddr, DWORD len, LPWSAPROTOCOL_INFOA info,
        LPSTR string, LPDWORD lenstr)
{
    struct qemu_WSAAddressToStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAADDRESSTOSTRINGA);
    call.sockaddr = (ULONG_PTR)sockaddr;
    call.len = (ULONG_PTR)len;
    call.info = (ULONG_PTR)info;
    call.string = (ULONG_PTR)string;
    call.lenstr = (ULONG_PTR)lenstr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAAddressToStringA(struct qemu_syscall *call)
{
    struct qemu_WSAAddressToStringA *c = (struct qemu_WSAAddressToStringA *)call;
    WINE_TRACE("\n");

    /* WSAPROTOCOL_INFO has the same size in 32 and 64 bit. */
    c->super.iret = WSAAddressToStringA(QEMU_G2H(c->sockaddr), c->len, QEMU_G2H(c->info), QEMU_G2H(c->string), QEMU_G2H(c->lenstr));
}

#endif

struct qemu_WSAAddressToStringW
{
    struct qemu_syscall super;
    uint64_t sockaddr;
    uint64_t len;
    uint64_t info;
    uint64_t string;
    uint64_t lenstr;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAAddressToStringW(LPSOCKADDR sockaddr, DWORD len, LPWSAPROTOCOL_INFOW info,
        LPWSTR string, LPDWORD lenstr)
{
    struct qemu_WSAAddressToStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAADDRESSTOSTRINGW);
    call.sockaddr = (ULONG_PTR)sockaddr;
    call.len = len;
    call.info = (ULONG_PTR)info;
    call.string = (ULONG_PTR)string;
    call.lenstr = (ULONG_PTR)lenstr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAAddressToStringW(struct qemu_syscall *call)
{
    struct qemu_WSAAddressToStringW *c = (struct qemu_WSAAddressToStringW *)call;
    WINE_TRACE("\n");

    /* WSAPROTOCOL_INFO has the same size in 32 and 64 bit. */
    c->super.iret = WSAAddressToStringW(QEMU_G2H(c->sockaddr), c->len, QEMU_G2H(c->info), QEMU_G2H(c->string), QEMU_G2H(c->lenstr));
}

#endif

struct qemu_WSAEnumNameSpaceProvidersA
{
    struct qemu_syscall super;
    uint64_t len;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAEnumNameSpaceProvidersA(LPDWORD len, LPWSANAMESPACE_INFOA buffer)
{
    struct qemu_WSAEnumNameSpaceProvidersA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAENUMNAMESPACEPROVIDERSA);
    call.len = (ULONG_PTR)len;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAEnumNameSpaceProvidersA(struct qemu_syscall *call)
{
    struct qemu_WSAEnumNameSpaceProvidersA *c = (struct qemu_WSAEnumNameSpaceProvidersA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAEnumNameSpaceProvidersA(QEMU_G2H(c->len), QEMU_G2H(c->buffer));
}

#endif

struct qemu_WSAEnumNameSpaceProvidersW
{
    struct qemu_syscall super;
    uint64_t len;
    uint64_t buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAEnumNameSpaceProvidersW(LPDWORD len, LPWSANAMESPACE_INFOW buffer)
{
    struct qemu_WSAEnumNameSpaceProvidersW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAENUMNAMESPACEPROVIDERSW);
    call.len = (ULONG_PTR)len;
    call.buffer = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAEnumNameSpaceProvidersW(struct qemu_syscall *call)
{
    struct qemu_WSAEnumNameSpaceProvidersW *c = (struct qemu_WSAEnumNameSpaceProvidersW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAEnumNameSpaceProvidersW(QEMU_G2H(c->len), QEMU_G2H(c->buffer));
}

#endif

struct qemu_WSAGetQOSByName
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t lpQOSName;
    uint64_t lpQOS;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI WSAGetQOSByName(SOCKET s, LPWSABUF lpQOSName, LPQOS lpQOS)
{
    struct qemu_WSAGetQOSByName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAGETQOSBYNAME);
    call.s = guest_SOCKET_g2h(s);
    call.lpQOSName = (ULONG_PTR)lpQOSName;
    call.lpQOS = (ULONG_PTR)lpQOS;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAGetQOSByName(struct qemu_syscall *call)
{
    struct qemu_WSAGetQOSByName *c = (struct qemu_WSAGetQOSByName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAGetQOSByName(c->s, QEMU_G2H(c->lpQOSName), QEMU_G2H(c->lpQOS));
}

#endif

struct qemu_WSAGetServiceClassInfoA
{
    struct qemu_syscall super;
    uint64_t provider;
    uint64_t service;
    uint64_t len;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAGetServiceClassInfoA(LPGUID provider, LPGUID service, LPDWORD len, LPWSASERVICECLASSINFOA info)
{
    struct qemu_WSAGetServiceClassInfoA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAGETSERVICECLASSINFOA);
    call.provider = (ULONG_PTR)provider;
    call.service = (ULONG_PTR)service;
    call.len = (ULONG_PTR)len;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAGetServiceClassInfoA(struct qemu_syscall *call)
{
    struct qemu_WSAGetServiceClassInfoA *c = (struct qemu_WSAGetServiceClassInfoA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAGetServiceClassInfoA(QEMU_G2H(c->provider), QEMU_G2H(c->service), QEMU_G2H(c->len), QEMU_G2H(c->info));
}

#endif

struct qemu_WSAGetServiceClassInfoW
{
    struct qemu_syscall super;
    uint64_t provider;
    uint64_t service;
    uint64_t len;
    uint64_t info;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAGetServiceClassInfoW(LPGUID provider, LPGUID service, LPDWORD len, LPWSASERVICECLASSINFOW info)
{
    struct qemu_WSAGetServiceClassInfoW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAGETSERVICECLASSINFOW);
    call.provider = (ULONG_PTR)provider;
    call.service = (ULONG_PTR)service;
    call.len = (ULONG_PTR)len;
    call.info = (ULONG_PTR)info;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAGetServiceClassInfoW(struct qemu_syscall *call)
{
    struct qemu_WSAGetServiceClassInfoW *c = (struct qemu_WSAGetServiceClassInfoW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAGetServiceClassInfoW(QEMU_G2H(c->provider), QEMU_G2H(c->service), QEMU_G2H(c->len), QEMU_G2H(c->info));
}

#endif

struct qemu_WSAGetServiceClassNameByClassIdA
{
    struct qemu_syscall super;
    uint64_t class;
    uint64_t service;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAGetServiceClassNameByClassIdA(LPGUID class, LPSTR service, LPDWORD len)
{
    struct qemu_WSAGetServiceClassNameByClassIdA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAGETSERVICECLASSNAMEBYCLASSIDA);
    call.class = (ULONG_PTR)class;
    call.service = (ULONG_PTR)service;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAGetServiceClassNameByClassIdA(struct qemu_syscall *call)
{
    struct qemu_WSAGetServiceClassNameByClassIdA *c = (struct qemu_WSAGetServiceClassNameByClassIdA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAGetServiceClassNameByClassIdA(QEMU_G2H(c->class), QEMU_G2H(c->service), QEMU_G2H(c->len));
}

#endif

struct qemu_WSAGetServiceClassNameByClassIdW
{
    struct qemu_syscall super;
    uint64_t class;
    uint64_t service;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAGetServiceClassNameByClassIdW(LPGUID class, LPWSTR service, LPDWORD len)
{
    struct qemu_WSAGetServiceClassNameByClassIdW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAGETSERVICECLASSNAMEBYCLASSIDW);
    call.class = (ULONG_PTR)class;
    call.service = (ULONG_PTR)service;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAGetServiceClassNameByClassIdW(struct qemu_syscall *call)
{
    struct qemu_WSAGetServiceClassNameByClassIdW *c = (struct qemu_WSAGetServiceClassNameByClassIdW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAGetServiceClassNameByClassIdW(QEMU_G2H(c->class), QEMU_G2H(c->service), QEMU_G2H(c->len));
}

#endif

struct qemu_WSALookupServiceBeginA
{
    struct qemu_syscall super;
    uint64_t lpqsRestrictions;
    uint64_t dwControlFlags;
    uint64_t lphLookup;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSALookupServiceBeginA(LPWSAQUERYSETA lpqsRestrictions, DWORD dwControlFlags, LPHANDLE lphLookup)
{
    struct qemu_WSALookupServiceBeginA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSALOOKUPSERVICEBEGINA);
    call.lpqsRestrictions = (ULONG_PTR)lpqsRestrictions;
    call.dwControlFlags = (ULONG_PTR)dwControlFlags;
    call.lphLookup = (ULONG_PTR)lphLookup;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSALookupServiceBeginA(struct qemu_syscall *call)
{
    struct qemu_WSALookupServiceBeginA *c = (struct qemu_WSALookupServiceBeginA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSALookupServiceBeginA(QEMU_G2H(c->lpqsRestrictions), c->dwControlFlags, QEMU_G2H(c->lphLookup));
}

#endif

struct qemu_WSALookupServiceBeginW
{
    struct qemu_syscall super;
    uint64_t lpqsRestrictions;
    uint64_t dwControlFlags;
    uint64_t lphLookup;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSALookupServiceBeginW(LPWSAQUERYSETW lpqsRestrictions, DWORD dwControlFlags, LPHANDLE lphLookup)
{
    struct qemu_WSALookupServiceBeginW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSALOOKUPSERVICEBEGINW);
    call.lpqsRestrictions = (ULONG_PTR)lpqsRestrictions;
    call.dwControlFlags = (ULONG_PTR)dwControlFlags;
    call.lphLookup = (ULONG_PTR)lphLookup;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSALookupServiceBeginW(struct qemu_syscall *call)
{
    struct qemu_WSALookupServiceBeginW *c = (struct qemu_WSALookupServiceBeginW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSALookupServiceBeginW(QEMU_G2H(c->lpqsRestrictions), c->dwControlFlags, QEMU_G2H(c->lphLookup));
}

#endif

struct qemu_WSALookupServiceEnd
{
    struct qemu_syscall super;
    uint64_t lookup;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSALookupServiceEnd(HANDLE lookup)
{
    struct qemu_WSALookupServiceEnd call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSALOOKUPSERVICEEND);
    call.lookup = (ULONG_PTR)lookup;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSALookupServiceEnd(struct qemu_syscall *call)
{
    struct qemu_WSALookupServiceEnd *c = (struct qemu_WSALookupServiceEnd *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSALookupServiceEnd(QEMU_G2H(c->lookup));
}

#endif

struct qemu_WSALookupServiceNextA
{
    struct qemu_syscall super;
    uint64_t lookup;
    uint64_t flags;
    uint64_t len;
    uint64_t results;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSALookupServiceNextA(HANDLE lookup, DWORD flags, LPDWORD len, LPWSAQUERYSETA results)
{
    struct qemu_WSALookupServiceNextA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSALOOKUPSERVICENEXTA);
    call.lookup = (ULONG_PTR)lookup;
    call.flags = (ULONG_PTR)flags;
    call.len = (ULONG_PTR)len;
    call.results = (ULONG_PTR)results;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSALookupServiceNextA(struct qemu_syscall *call)
{
    struct qemu_WSALookupServiceNextA *c = (struct qemu_WSALookupServiceNextA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSALookupServiceNextA(QEMU_G2H(c->lookup), c->flags, QEMU_G2H(c->len), QEMU_G2H(c->results));
}

#endif

struct qemu_WSALookupServiceNextW
{
    struct qemu_syscall super;
    uint64_t lookup;
    uint64_t flags;
    uint64_t len;
    uint64_t results;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSALookupServiceNextW(HANDLE lookup, DWORD flags, LPDWORD len, LPWSAQUERYSETW results)
{
    struct qemu_WSALookupServiceNextW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSALOOKUPSERVICENEXTW);
    call.lookup = (ULONG_PTR)lookup;
    call.flags = (ULONG_PTR)flags;
    call.len = (ULONG_PTR)len;
    call.results = (ULONG_PTR)results;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSALookupServiceNextW(struct qemu_syscall *call)
{
    struct qemu_WSALookupServiceNextW *c = (struct qemu_WSALookupServiceNextW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSALookupServiceNextW(QEMU_G2H(c->lookup), c->flags, QEMU_G2H(c->len), QEMU_G2H(c->results));
}

#endif

struct qemu_WSANtohl
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t netlong;
    uint64_t lphostlong;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSANtohl(SOCKET s, u_long netlong, u_long* lphostlong)
{
    struct qemu_WSANtohl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSANTOHL);
    call.s = guest_SOCKET_g2h(s);
    call.netlong = (ULONG_PTR)netlong;
    call.lphostlong = (ULONG_PTR)lphostlong;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSANtohl(struct qemu_syscall *call)
{
    struct qemu_WSANtohl *c = (struct qemu_WSANtohl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSANtohl(c->s, c->netlong, QEMU_G2H(c->lphostlong));
}

#endif

struct qemu_WSANtohs
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t netshort;
    uint64_t lphostshort;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSANtohs(SOCKET s, u_short netshort, u_short* lphostshort)
{
    struct qemu_WSANtohs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSANTOHS);
    call.s = guest_SOCKET_g2h(s);
    call.netshort = (ULONG_PTR)netshort;
    call.lphostshort = (ULONG_PTR)lphostshort;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSANtohs(struct qemu_syscall *call)
{
    struct qemu_WSANtohs *c = (struct qemu_WSANtohs *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSANtohs(c->s, c->netshort, QEMU_G2H(c->lphostshort));
}

#endif

struct qemu_WSAProviderConfigChange
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t overlapped;
    uint64_t completion;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAProviderConfigChange(LPHANDLE handle, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completion)
{
    struct qemu_WSAProviderConfigChange call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAPROVIDERCONFIGCHANGE);
    call.handle = (ULONG_PTR)handle;
    call.overlapped = (ULONG_PTR)overlapped;
    call.completion = (ULONG_PTR)completion;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAProviderConfigChange(struct qemu_syscall *call)
{
    struct qemu_WSAProviderConfigChange *c = (struct qemu_WSAProviderConfigChange *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSAProviderConfigChange(QEMU_G2H(c->handle), QEMU_G2H(c->overlapped), QEMU_G2H(c->completion));
}

#endif

struct qemu_WSARecvDisconnect
{
    struct qemu_syscall super;
    uint64_t s;
    uint64_t disconnectdata;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSARecvDisconnect(SOCKET s, LPWSABUF disconnectdata)
{
    struct qemu_WSARecvDisconnect call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSARECVDISCONNECT);
    call.s = guest_SOCKET_g2h(s);
    call.disconnectdata = (ULONG_PTR)disconnectdata;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSARecvDisconnect(struct qemu_syscall *call)
{
    struct qemu_WSARecvDisconnect *c = (struct qemu_WSARecvDisconnect *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSARecvDisconnect(c->s, QEMU_G2H(c->disconnectdata));
}

#endif

struct qemu_WSASetServiceA
{
    struct qemu_syscall super;
    uint64_t query;
    uint64_t operation;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSASetServiceA(LPWSAQUERYSETA query, WSAESETSERVICEOP operation, DWORD flags)
{
    struct qemu_WSASetServiceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSASETSERVICEA);
    call.query = (ULONG_PTR)query;
    call.operation = (ULONG_PTR)operation;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSASetServiceA(struct qemu_syscall *call)
{
    struct qemu_WSASetServiceA *c = (struct qemu_WSASetServiceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSASetServiceA(QEMU_G2H(c->query), c->operation, c->flags);
}

#endif

struct qemu_WSASetServiceW
{
    struct qemu_syscall super;
    uint64_t query;
    uint64_t operation;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSASetServiceW(LPWSAQUERYSETW query, WSAESETSERVICEOP operation, DWORD flags)
{
    struct qemu_WSASetServiceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSASETSERVICEW);
    call.query = (ULONG_PTR)query;
    call.operation = (ULONG_PTR)operation;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSASetServiceW(struct qemu_syscall *call)
{
    struct qemu_WSASetServiceW *c = (struct qemu_WSASetServiceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSASetServiceW(QEMU_G2H(c->query), c->operation, c->flags);
}

#endif

struct qemu_WSCEnableNSProvider
{
    struct qemu_syscall super;
    uint64_t provider;
    uint64_t enable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSCEnableNSProvider(LPGUID provider, BOOL enable)
{
    struct qemu_WSCEnableNSProvider call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSCENABLENSPROVIDER);
    call.provider = (ULONG_PTR)provider;
    call.enable = (ULONG_PTR)enable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSCEnableNSProvider(struct qemu_syscall *call)
{
    struct qemu_WSCEnableNSProvider *c = (struct qemu_WSCEnableNSProvider *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSCEnableNSProvider(QEMU_G2H(c->provider), c->enable);
}

#endif

struct qemu_WSCGetProviderPath
{
    struct qemu_syscall super;
    uint64_t provider;
    uint64_t path;
    uint64_t len;
    uint64_t errcode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSCGetProviderPath(LPGUID provider, LPWSTR path, LPINT len, LPINT errcode)
{
    struct qemu_WSCGetProviderPath call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSCGETPROVIDERPATH);
    call.provider = (ULONG_PTR)provider;
    call.path = (ULONG_PTR)path;
    call.len = (ULONG_PTR)len;
    call.errcode = (ULONG_PTR)errcode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSCGetProviderPath(struct qemu_syscall *call)
{
    struct qemu_WSCGetProviderPath *c = (struct qemu_WSCGetProviderPath *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSCGetProviderPath(QEMU_G2H(c->provider), QEMU_G2H(c->path), QEMU_G2H(c->len), QEMU_G2H(c->errcode));
}

#endif

struct qemu_WSCInstallNameSpace
{
    struct qemu_syscall super;
    uint64_t identifier;
    uint64_t path;
    uint64_t namespace;
    uint64_t version;
    uint64_t provider;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSCInstallNameSpace(LPWSTR identifier, LPWSTR path, DWORD namespace, DWORD version, LPGUID provider)
{
    struct qemu_WSCInstallNameSpace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSCINSTALLNAMESPACE);
    call.identifier = (ULONG_PTR)identifier;
    call.path = (ULONG_PTR)path;
    call.namespace = (ULONG_PTR)namespace;
    call.version = (ULONG_PTR)version;
    call.provider = (ULONG_PTR)provider;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSCInstallNameSpace(struct qemu_syscall *call)
{
    struct qemu_WSCInstallNameSpace *c = (struct qemu_WSCInstallNameSpace *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSCInstallNameSpace(QEMU_G2H(c->identifier), QEMU_G2H(c->path), c->namespace, c->version, QEMU_G2H(c->provider));
}

#endif

struct qemu_WSCUnInstallNameSpace
{
    struct qemu_syscall super;
    uint64_t lpProviderId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSCUnInstallNameSpace(LPGUID lpProviderId)
{
    struct qemu_WSCUnInstallNameSpace call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSCUNINSTALLNAMESPACE);
    call.lpProviderId = (ULONG_PTR)lpProviderId;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSCUnInstallNameSpace(struct qemu_syscall *call)
{
    struct qemu_WSCUnInstallNameSpace *c = (struct qemu_WSCUnInstallNameSpace *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSCUnInstallNameSpace(QEMU_G2H(c->lpProviderId));
}

#endif

struct qemu_WSCWriteProviderOrder
{
    struct qemu_syscall super;
    uint64_t entry;
    uint64_t number;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSCWriteProviderOrder(LPDWORD entry, DWORD number)
{
    struct qemu_WSCWriteProviderOrder call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSCWRITEPROVIDERORDER);
    call.entry = (ULONG_PTR)entry;
    call.number = (ULONG_PTR)number;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSCWriteProviderOrder(struct qemu_syscall *call)
{
    struct qemu_WSCWriteProviderOrder *c = (struct qemu_WSCWriteProviderOrder *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSCWriteProviderOrder(QEMU_G2H(c->entry), c->number);
}

#endif

struct qemu_WSANSPIoctl
{
    struct qemu_syscall super;
    uint64_t hLookup;
    uint64_t dwControlCode;
    uint64_t lpvInBuffer;
    uint64_t cbInBuffer;
    uint64_t lpvOutBuffer;
    uint64_t cbOutBuffer;
    uint64_t lpcbBytesReturned;
    uint64_t lpCompletion;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSANSPIoctl(HANDLE hLookup, DWORD dwControlCode, LPVOID lpvInBuffer, DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned, LPWSACOMPLETION lpCompletion)
{
    struct qemu_WSANSPIoctl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSANSPIOCTL);
    call.hLookup = (ULONG_PTR)hLookup;
    call.dwControlCode = (ULONG_PTR)dwControlCode;
    call.lpvInBuffer = (ULONG_PTR)lpvInBuffer;
    call.cbInBuffer = (ULONG_PTR)cbInBuffer;
    call.lpvOutBuffer = (ULONG_PTR)lpvOutBuffer;
    call.cbOutBuffer = (ULONG_PTR)cbOutBuffer;
    call.lpcbBytesReturned = (ULONG_PTR)lpcbBytesReturned;
    call.lpCompletion = (ULONG_PTR)lpCompletion;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSANSPIoctl(struct qemu_syscall *call)
{
    struct qemu_WSANSPIoctl *c = (struct qemu_WSANSPIoctl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = WSANSPIoctl(QEMU_G2H(c->hLookup), c->dwControlCode, QEMU_G2H(c->lpvInBuffer), c->cbInBuffer, QEMU_G2H(c->lpvOutBuffer), c->cbOutBuffer, QEMU_G2H(c->lpcbBytesReturned), QEMU_G2H(c->lpCompletion));
}

#endif

struct qemu_WSAEnumProtocolsA
{
    struct qemu_syscall super;
    uint64_t protocols;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAEnumProtocolsA(LPINT protocols, LPWSAPROTOCOL_INFOA buffer, LPDWORD len)
{
    struct qemu_WSAEnumProtocolsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAENUMPROTOCOLSA);
    call.protocols = (ULONG_PTR)protocols;
    call.buffer = (ULONG_PTR)buffer;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAEnumProtocolsA(struct qemu_syscall *call)
{
    struct qemu_WSAEnumProtocolsA *c = (struct qemu_WSAEnumProtocolsA *)call;
    WINE_FIXME("Unverified!\n");

    /* WSAPROTOCOL_INFO has the same size in 32 and 64 bit. */
    c->super.iret = WSAEnumProtocolsA(QEMU_G2H(c->protocols), QEMU_G2H(c->buffer), QEMU_G2H(c->len));
}

#endif

struct qemu_WSAEnumProtocolsW
{
    struct qemu_syscall super;
    uint64_t protocols;
    uint64_t buffer;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSAEnumProtocolsW(LPINT protocols, LPWSAPROTOCOL_INFOW buffer, LPDWORD len)
{
    struct qemu_WSAEnumProtocolsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSAENUMPROTOCOLSW);
    call.protocols = (ULONG_PTR)protocols;
    call.buffer = (ULONG_PTR)buffer;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSAEnumProtocolsW(struct qemu_syscall *call)
{
    struct qemu_WSAEnumProtocolsW *c = (struct qemu_WSAEnumProtocolsW *)call;
    WINE_FIXME("Unverified!\n");

    /* WSAPROTOCOL_INFO has the same size in 32 and 64 bit. */
    c->super.iret = WSAEnumProtocolsW(QEMU_G2H(c->protocols), QEMU_G2H(c->buffer), QEMU_G2H(c->len));
}

#endif

struct qemu_WSCEnumProtocols
{
    struct qemu_syscall super;
    uint64_t protocols;
    uint64_t buffer;
    uint64_t len;
    uint64_t err;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI WSCEnumProtocols(LPINT protocols, LPWSAPROTOCOL_INFOW buffer, LPDWORD len, LPINT err)
{
    struct qemu_WSCEnumProtocols call;
    call.super.id = QEMU_SYSCALL_ID(CALL_WSCENUMPROTOCOLS);
    call.protocols = (ULONG_PTR)protocols;
    call.buffer = (ULONG_PTR)buffer;
    call.len = (ULONG_PTR)len;
    call.err = (ULONG_PTR)err;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_WSCEnumProtocols(struct qemu_syscall *call)
{
    struct qemu_WSCEnumProtocols *c = (struct qemu_WSCEnumProtocols *)call;
    WINE_FIXME("Unverified!\n");

    /* WSAPROTOCOL_INFO has the same size in 32 and 64 bit. */
    c->super.iret = WSCEnumProtocols(QEMU_G2H(c->protocols), QEMU_G2H(c->buffer), QEMU_G2H(c->len), QEMU_G2H(c->err));
}

#endif

