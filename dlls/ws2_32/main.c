/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ws2_32.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ws2_32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu___WSAFDIsSet,
    qemu_FreeAddrInfoExW,
    qemu_FreeAddrInfoW,
    qemu_GetAddrInfoExCancel,
    qemu_GetAddrInfoExOverlappedResult,
    qemu_GetAddrInfoExW,
    qemu_GetAddrInfoW,
    qemu_GetNameInfoW,
    qemu_InetNtopW,
    qemu_InetPtonW,
    qemu_WPUCompleteOverlappedRequest,
    qemu_WS_accept,
    qemu_WS_bind,
    qemu_WS_closesocket,
    qemu_WS_connect,
    qemu_WS_freeaddrinfo,
    qemu_WS_getaddrinfo,
    qemu_WS_gethostbyaddr,
    qemu_WS_gethostbyname,
    qemu_WS_gethostname,
    qemu_WS_getnameinfo,
    qemu_WS_getpeername,
    qemu_WS_getprotobyname,
    qemu_WS_getprotobynumber,
    qemu_WS_getservbyname,
    qemu_WS_getservbyport,
    qemu_WS_getsockname,
    qemu_WS_getsockopt,
    qemu_WS_htonl,
    qemu_WS_htons,
    qemu_WS_inet_addr,
    qemu_WS_inet_ntoa,
    qemu_WS_inet_ntop,
    qemu_WS_inet_pton,
    qemu_WS_ioctlsocket,
    qemu_WS_listen,
    qemu_WS_ntohl,
    qemu_WS_ntohs,
    qemu_WS_recv,
    qemu_WS_recvfrom,
    qemu_WS_select,
    qemu_WS_send,
    qemu_WS_sendto,
    qemu_WS_setsockopt,
    qemu_WS_shutdown,
    qemu_WS_socket,
    qemu_WSAAccept,
    qemu_WSAAddressToStringA,
    qemu_WSAAddressToStringW,
    qemu_WSAAsyncGetHostByAddr,
    qemu_WSAAsyncGetHostByName,
    qemu_WSAAsyncGetProtoByName,
    qemu_WSAAsyncGetProtoByNumber,
    qemu_WSAAsyncGetServByName,
    qemu_WSAAsyncGetServByPort,
    qemu_WSAAsyncSelect,
    qemu_WSACancelAsyncRequest,
    qemu_WSACancelBlockingCall,
    qemu_WSACleanup,
    qemu_WSACloseEvent,
    qemu_WSAConnect,
    qemu_WSACreateEvent,
    qemu_WSADuplicateSocketA,
    qemu_WSADuplicateSocketW,
    qemu_WSAEnumNameSpaceProvidersA,
    qemu_WSAEnumNameSpaceProvidersW,
    qemu_WSAEnumNetworkEvents,
    qemu_WSAEnumProtocolsA,
    qemu_WSAEnumProtocolsW,
    qemu_WSAEventSelect,
    qemu_WSAGetLastError,
    qemu_WSAGetOverlappedResult,
    qemu_WSAGetQOSByName,
    qemu_WSAGetServiceClassInfoA,
    qemu_WSAGetServiceClassInfoW,
    qemu_WSAGetServiceClassNameByClassIdA,
    qemu_WSAGetServiceClassNameByClassIdW,
    qemu_WSAHtonl,
    qemu_WSAHtons,
    qemu_WSAInstallServiceClassA,
    qemu_WSAInstallServiceClassW,
    qemu_WSAIoctl,
    qemu_WSAIsBlocking,
    qemu_WSAJoinLeaf,
    qemu_WSALookupServiceBeginA,
    qemu_WSALookupServiceBeginW,
    qemu_WSALookupServiceEnd,
    qemu_WSALookupServiceNextA,
    qemu_WSALookupServiceNextW,
    qemu_WSANSPIoctl,
    qemu_WSANtohl,
    qemu_WSANtohs,
    qemu_WSAPoll,
    qemu_WSAProviderConfigChange,
    qemu_WSApSetPostRoutine,
    qemu_WSARecv,
    qemu_WSARecvDisconnect,
    qemu_WSARecvFrom,
    qemu_WSARemoveServiceClass,
    qemu_WSASend,
    qemu_WSASendDisconnect,
    qemu_WSASendMsg,
    qemu_WSASendTo,
    qemu_WSASetBlockingHook,
    qemu_WSASetLastError,
    qemu_WSASetServiceA,
    qemu_WSASetServiceW,
    qemu_WSASocketA,
    qemu_WSASocketW,
    qemu_WSAStartup,
    qemu_WSAStringToAddressA,
    qemu_WSAStringToAddressW,
    qemu_WSAUnhookBlockingHook,
    qemu_WSCDeinstallProvider,
    qemu_WSCEnableNSProvider,
    qemu_WSCEnumProtocols,
    qemu_WSCGetProviderPath,
    qemu_WSCInstallNameSpace,
    qemu_WSCInstallProvider,
    qemu_WSCUnInstallNameSpace,
    qemu_WSCWriteProviderOrder,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE ws2_32;
    WINE_TRACE("Loading host-side ws2_32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    ws2_32 = LoadLibraryA("ws2_32");
    if (!ws2_32)
        WINE_ERR("Cannot find ws2_32.dll.\n");

    p_accept = (void *)GetProcAddress(ws2_32, "accept");
    if (!p_accept)
        WINE_ERR("Failed to get address of accept!\n");
    p_bind = (void *)GetProcAddress(ws2_32, "bind");
    if (!p_bind)
        WINE_ERR("Failed to get address of bind!\n");
    p_closesocket = (void *)GetProcAddress(ws2_32, "closesocket");
    if (!p_closesocket)
        WINE_ERR("Failed to get address of closesocket!\n");
    p_connect = (void *)GetProcAddress(ws2_32, "connect");
    if (!p_connect)
        WINE_ERR("Failed to get address of connect!\n");
    p_freeaddrinfo = (void *)GetProcAddress(ws2_32, "freeaddrinfo");
    if (!p_freeaddrinfo)
        WINE_ERR("Failed to get address of freeaddrinfo!\n");
    p_getaddrinfo = (void *)GetProcAddress(ws2_32, "getaddrinfo");
    if (!p_getaddrinfo)
        WINE_ERR("Failed to get address of getaddrinfo!\n");
    p_gethostbyaddr = (void *)GetProcAddress(ws2_32, "gethostbyaddr");
    if (!p_gethostbyaddr)
        WINE_ERR("Failed to get address of gethostbyaddr!\n");
    p_gethostbyname = (void *)GetProcAddress(ws2_32, "gethostbyname");
    if (!p_gethostbyname)
        WINE_ERR("Failed to get address of gethostbyname!\n");
    p_gethostname = (void *)GetProcAddress(ws2_32, "gethostname");
    if (!p_gethostname)
        WINE_ERR("Failed to get address of gethostname!\n");
    p_getnameinfo = (void *)GetProcAddress(ws2_32, "getnameinfo");
    if (!p_getnameinfo)
        WINE_ERR("Failed to get address of getnameinfo!\n");
    p_getpeername = (void *)GetProcAddress(ws2_32, "getpeername");
    if (!p_getpeername)
        WINE_ERR("Failed to get address of getpeername!\n");
    p_getprotobyname = (void *)GetProcAddress(ws2_32, "getprotobyname");
    if (!p_getprotobyname)
        WINE_ERR("Failed to get address of getprotobyname!\n");
    p_getprotobynumber = (void *)GetProcAddress(ws2_32, "getprotobynumber");
    if (!p_getprotobynumber)
        WINE_ERR("Failed to get address of getprotobynumber!\n");
    p_getservbyname = (void *)GetProcAddress(ws2_32, "getservbyname");
    if (!p_getservbyname)
        WINE_ERR("Failed to get address of getservbyname!\n");
    p_getservbyport = (void *)GetProcAddress(ws2_32, "getservbyport");
    if (!p_getservbyport)
        WINE_ERR("Failed to get address of getservbyport!\n");
    p_getsockname = (void *)GetProcAddress(ws2_32, "getsockname");
    if (!p_getsockname)
        WINE_ERR("Failed to get address of getsockname!\n");
    p_getsockopt = (void *)GetProcAddress(ws2_32, "getsockopt");
    if (!p_getsockopt)
        WINE_ERR("Failed to get address of getsockopt!\n");
    p_htonl = (void *)GetProcAddress(ws2_32, "htonl");
    if (!p_htonl)
        WINE_ERR("Failed to get address of htonl!\n");
    p_htons = (void *)GetProcAddress(ws2_32, "htons");
    if (!p_htons)
        WINE_ERR("Failed to get address of htons!\n");
    p_inet_addr = (void *)GetProcAddress(ws2_32, "inet_addr");
    if (!p_inet_addr)
        WINE_ERR("Failed to get address of inet_addr!\n");
    p_inet_ntoa = (void *)GetProcAddress(ws2_32, "inet_ntoa");
    if (!p_inet_ntoa)
        WINE_ERR("Failed to get address of inet_ntoa!\n");
    p_inet_ntop = (void *)GetProcAddress(ws2_32, "inet_ntop");
    if (!p_inet_ntop)
        WINE_ERR("Failed to get address of inet_ntop!\n");
    p_inet_pton = (void *)GetProcAddress(ws2_32, "inet_pton");
    if (!p_inet_pton)
        WINE_ERR("Failed to get address of inet_pton!\n");
    p_ioctlsocket = (void *)GetProcAddress(ws2_32, "ioctlsocket");
    if (!p_ioctlsocket)
        WINE_ERR("Failed to get address of ioctlsocket!\n");
    p_listen = (void *)GetProcAddress(ws2_32, "listen");
    if (!p_listen)
        WINE_ERR("Failed to get address of listen!\n");
    p_ntohl = (void *)GetProcAddress(ws2_32, "ntohl");
    if (!p_ntohl)
        WINE_ERR("Failed to get address of ntohl!\n");
    p_ntohs = (void *)GetProcAddress(ws2_32, "ntohs");
    if (!p_ntohs)
        WINE_ERR("Failed to get address of ntohs!\n");
    p_recv = (void *)GetProcAddress(ws2_32, "recv");
    if (!p_recv)
        WINE_ERR("Failed to get address of recv!\n");
    p_recvfrom = (void *)GetProcAddress(ws2_32, "recvfrom");
    if (!p_recvfrom)
        WINE_ERR("Failed to get address of recvfrom!\n");
    p_select = (void *)GetProcAddress(ws2_32, "select");
    if (!p_select)
        WINE_ERR("Failed to get address of select!\n");
    p_send = (void *)GetProcAddress(ws2_32, "send");
    if (!p_send)
        WINE_ERR("Failed to get address of send!\n");
    p_sendto = (void *)GetProcAddress(ws2_32, "sendto");
    if (!p_sendto)
        WINE_ERR("Failed to get address of sendto!\n");
    p_setsockopt = (void *)GetProcAddress(ws2_32, "setsockopt");
    if (!p_setsockopt)
        WINE_ERR("Failed to get address of setsockopt!\n");
    p_shutdown = (void *)GetProcAddress(ws2_32, "shutdown");
    if (!p_shutdown)
        WINE_ERR("Failed to get address of shutdown!\n");
    p_socket = (void *)GetProcAddress(ws2_32, "socket");
    if (!p_socket)
        WINE_ERR("Failed to get address of socket!\n");

    return dll_functions;
}

#endif
