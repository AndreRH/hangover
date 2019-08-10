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

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_wsock32.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_wsock32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_EnumProtocolsA,
    qemu_EnumProtocolsW,
    qemu_GetAddressByNameA,
    qemu_GetAddressByNameW,
    qemu_GetServiceA,
    qemu_GetServiceW,
    qemu_GetTypeByNameA,
    qemu_GetTypeByNameW,
    qemu_s_perror,
    qemu_SetServiceA,
    qemu_SetServiceW,
    qemu_WS1_getsockopt,
    qemu_WS1_setsockopt,
    qemu_WSARecvEx,
    qemu_WsControl,
    qemu_WSOCK32_getnetbyname,
    qemu_WSOCK32_inet_network,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE wsock32;
    WINE_TRACE("Loading host-side wsock32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    wsock32 = LoadLibraryA("wsock32");
    if (!wsock32)
        WINE_ERR("Cannot find wsock32.dll.\n");

    p_EnumProtocolsA = (void *)GetProcAddress(wsock32, "EnumProtocols");
    p_EnumProtocolsW = (void *)GetProcAddress(wsock32, "EnumProtocolsW");
    p_getnetbyname = (void *)GetProcAddress(wsock32, "getnetbyname");
    p_getsockopt = (void *)GetProcAddress(wsock32, "getsockopt");
    p_inet_network = (void *)GetProcAddress(wsock32, "inet_network");
    p_setsockopt = (void *)GetProcAddress(wsock32, "setsockopt");
    p_WsControl = (void *)GetProcAddress(wsock32, "WsControl");

    return dll_functions;
}

#endif
