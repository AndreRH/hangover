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
#include <ws2tcpip.h>
#include <winternl.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <fltdefs.h>
#include <netioapi.h>
#include <tcpestats.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_iphlpapi.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_iphlpapi);
#endif


struct qemu_Icmp6CreateFile
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI Icmp6CreateFile(VOID)
{
    struct qemu_Icmp6CreateFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ICMP6CREATEFILE);

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add Icmp6CreateFile to Wine headers? */
extern HANDLE WINAPI Icmp6CreateFile(VOID);
void qemu_Icmp6CreateFile(struct qemu_syscall *call)
{
    struct qemu_Icmp6CreateFile *c = (struct qemu_Icmp6CreateFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)Icmp6CreateFile();
}

#endif

struct qemu_Icmp6SendEcho2
{
    struct qemu_syscall super;
    uint64_t IcmpHandle;
    uint64_t Event;
    uint64_t ApcRoutine;
    uint64_t ApcContext;
    uint64_t SourceAddress;
    uint64_t DestinationAddress;
    uint64_t RequestData;
    uint64_t RequestSize;
    uint64_t RequestOptions;
    uint64_t ReplyBuffer;
    uint64_t ReplySize;
    uint64_t Timeout;
};

#ifdef QEMU_DLL_GUEST

/* Somehow mingw doesn't accept its own definition back. I guess it has something to do with FARPROC or PIP_OPTION_INFORMATION. */
DWORD WINAPI iphlpapi_Icmp6SendEcho2(HANDLE IcmpHandle,HANDLE Event,FARPROC ApcRoutine,PVOID ApcContext,struct sockaddr_in6 *SourceAddress,struct sockaddr_in6 *DestinationAddress,LPVOID RequestData,WORD RequestSize,PIP_OPTION_INFORMATION RequestOptions,LPVOID ReplyBuffer,DWORD ReplySize,DWORD Timeout)
{
    struct qemu_Icmp6SendEcho2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ICMP6SENDECHO2);
    call.IcmpHandle = (ULONG_PTR)IcmpHandle;
    call.Event = (ULONG_PTR)Event;
    call.ApcRoutine = (ULONG_PTR)ApcRoutine;
    call.ApcContext = (ULONG_PTR)ApcContext;
    call.SourceAddress = (ULONG_PTR)SourceAddress;
    call.DestinationAddress = (ULONG_PTR)DestinationAddress;
    call.RequestData = (ULONG_PTR)RequestData;
    call.RequestSize = (ULONG_PTR)RequestSize;
    call.RequestOptions = (ULONG_PTR)RequestOptions;
    call.ReplyBuffer = (ULONG_PTR)ReplyBuffer;
    call.ReplySize = (ULONG_PTR)ReplySize;
    call.Timeout = (ULONG_PTR)Timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add Icmp6SendEcho2 to Wine headers? */
extern DWORD WINAPI Icmp6SendEcho2(HANDLE IcmpHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, struct WS_sockaddr_in6* SourceAddress, struct WS_sockaddr_in6* DestinationAddress, LPVOID RequestData, WORD RequestSize, PIP_OPTION_INFORMATION RequestOptions, LPVOID ReplyBuffer, DWORD ReplySize, DWORD Timeout);
void qemu_Icmp6SendEcho2(struct qemu_syscall *call)
{
    struct qemu_Icmp6SendEcho2 *c = (struct qemu_Icmp6SendEcho2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Icmp6SendEcho2(QEMU_G2H(c->IcmpHandle), QEMU_G2H(c->Event), QEMU_G2H(c->ApcRoutine), QEMU_G2H(c->ApcContext), QEMU_G2H(c->SourceAddress), QEMU_G2H(c->DestinationAddress), QEMU_G2H(c->RequestData), c->RequestSize, QEMU_G2H(c->RequestOptions), QEMU_G2H(c->ReplyBuffer), c->ReplySize, c->Timeout);
}

#endif

struct qemu_IcmpCreateFile
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI IcmpCreateFile(VOID)
{
    struct qemu_IcmpCreateFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ICMPCREATEFILE);

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_IcmpCreateFile(struct qemu_syscall *call)
{
    struct qemu_IcmpCreateFile *c = (struct qemu_IcmpCreateFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)IcmpCreateFile();
}

#endif

struct qemu_IcmpCloseHandle
{
    struct qemu_syscall super;
    uint64_t IcmpHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI IcmpCloseHandle(HANDLE IcmpHandle)
{
    struct qemu_IcmpCloseHandle call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ICMPCLOSEHANDLE);
    call.IcmpHandle = (ULONG_PTR)IcmpHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IcmpCloseHandle(struct qemu_syscall *call)
{
    struct qemu_IcmpCloseHandle *c = (struct qemu_IcmpCloseHandle *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IcmpCloseHandle(QEMU_G2H(c->IcmpHandle));
}

#endif

struct qemu_IcmpSendEcho
{
    struct qemu_syscall super;
    uint64_t IcmpHandle;
    uint64_t DestinationAddress;
    uint64_t RequestData;
    uint64_t RequestSize;
    uint64_t RequestOptions;
    uint64_t ReplyBuffer;
    uint64_t ReplySize;
    uint64_t Timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI IcmpSendEcho(HANDLE IcmpHandle, IPAddr DestinationAddress, LPVOID RequestData, WORD RequestSize, PIP_OPTION_INFORMATION RequestOptions, LPVOID ReplyBuffer, DWORD ReplySize, DWORD Timeout)
{
    struct qemu_IcmpSendEcho call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ICMPSENDECHO);
    call.IcmpHandle = (ULONG_PTR)IcmpHandle;
    call.DestinationAddress = (ULONG_PTR)DestinationAddress;
    call.RequestData = (ULONG_PTR)RequestData;
    call.RequestSize = (ULONG_PTR)RequestSize;
    call.RequestOptions = (ULONG_PTR)RequestOptions;
    call.ReplyBuffer = (ULONG_PTR)ReplyBuffer;
    call.ReplySize = (ULONG_PTR)ReplySize;
    call.Timeout = (ULONG_PTR)Timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IcmpSendEcho(struct qemu_syscall *call)
{
    struct qemu_IcmpSendEcho *c = (struct qemu_IcmpSendEcho *)call;
    WINE_TRACE("\n");
    c->super.iret = IcmpSendEcho(QEMU_G2H(c->IcmpHandle), c->DestinationAddress, QEMU_G2H(c->RequestData), c->RequestSize, QEMU_G2H(c->RequestOptions), QEMU_G2H(c->ReplyBuffer), c->ReplySize, c->Timeout);
}

#endif

struct qemu_IcmpSendEcho2
{
    struct qemu_syscall super;
    uint64_t IcmpHandle;
    uint64_t Event;
    uint64_t ApcRoutine;
    uint64_t ApcContext;
    uint64_t DestinationAddress;
    uint64_t RequestData;
    uint64_t RequestSize;
    uint64_t RequestOptions;
    uint64_t ReplyBuffer;
    uint64_t ReplySize;
    uint64_t Timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI IcmpSendEcho2(HANDLE IcmpHandle, HANDLE Event, FARPROC ApcRoutine, PVOID ApcContext, IPAddr DestinationAddress, LPVOID RequestData, WORD RequestSize, PIP_OPTION_INFORMATION RequestOptions, LPVOID ReplyBuffer, DWORD ReplySize, DWORD Timeout)
{
    struct qemu_IcmpSendEcho2 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ICMPSENDECHO2);
    call.IcmpHandle = (ULONG_PTR)IcmpHandle;
    call.Event = (ULONG_PTR)Event;
    call.ApcRoutine = (ULONG_PTR)ApcRoutine;
    call.ApcContext = (ULONG_PTR)ApcContext;
    call.DestinationAddress = (ULONG_PTR)DestinationAddress;
    call.RequestData = (ULONG_PTR)RequestData;
    call.RequestSize = (ULONG_PTR)RequestSize;
    call.RequestOptions = (ULONG_PTR)RequestOptions;
    call.ReplyBuffer = (ULONG_PTR)ReplyBuffer;
    call.ReplySize = (ULONG_PTR)ReplySize;
    call.Timeout = (ULONG_PTR)Timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IcmpSendEcho2 to Wine headers? */
extern DWORD WINAPI IcmpSendEcho2(HANDLE IcmpHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, IPAddr DestinationAddress, LPVOID RequestData, WORD RequestSize, PIP_OPTION_INFORMATION RequestOptions, LPVOID ReplyBuffer, DWORD ReplySize, DWORD Timeout);
void qemu_IcmpSendEcho2(struct qemu_syscall *call)
{
    struct qemu_IcmpSendEcho2 *c = (struct qemu_IcmpSendEcho2 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IcmpSendEcho2(QEMU_G2H(c->IcmpHandle), QEMU_G2H(c->Event), QEMU_G2H(c->ApcRoutine), QEMU_G2H(c->ApcContext), c->DestinationAddress, QEMU_G2H(c->RequestData), c->RequestSize, QEMU_G2H(c->RequestOptions), QEMU_G2H(c->ReplyBuffer), c->ReplySize, c->Timeout);
}

#endif

struct qemu_IcmpSendEcho2Ex
{
    struct qemu_syscall super;
    uint64_t IcmpHandle;
    uint64_t Event;
    uint64_t ApcRoutine;
    uint64_t ApcContext;
    uint64_t SourceAddress;
    uint64_t DestinationAddress;
    uint64_t RequestData;
    uint64_t RequestSize;
    uint64_t RequestOptions;
    uint64_t ReplyBuffer;
    uint64_t ReplySize;
    uint64_t Timeout;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI IcmpSendEcho2Ex(HANDLE IcmpHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, IPAddr SourceAddress, IPAddr DestinationAddress, LPVOID RequestData, WORD RequestSize, PIP_OPTION_INFORMATION RequestOptions, LPVOID ReplyBuffer, DWORD ReplySize, DWORD Timeout)
{
    struct qemu_IcmpSendEcho2Ex call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ICMPSENDECHO2EX);
    call.IcmpHandle = (ULONG_PTR)IcmpHandle;
    call.Event = (ULONG_PTR)Event;
    call.ApcRoutine = (ULONG_PTR)ApcRoutine;
    call.ApcContext = (ULONG_PTR)ApcContext;
    call.SourceAddress = (ULONG_PTR)SourceAddress;
    call.DestinationAddress = (ULONG_PTR)DestinationAddress;
    call.RequestData = (ULONG_PTR)RequestData;
    call.RequestSize = (ULONG_PTR)RequestSize;
    call.RequestOptions = (ULONG_PTR)RequestOptions;
    call.ReplyBuffer = (ULONG_PTR)ReplyBuffer;
    call.ReplySize = (ULONG_PTR)ReplySize;
    call.Timeout = (ULONG_PTR)Timeout;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add IcmpSendEcho2Ex to Wine headers? */
extern DWORD WINAPI IcmpSendEcho2Ex(HANDLE IcmpHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, IPAddr SourceAddress, IPAddr DestinationAddress, LPVOID RequestData, WORD RequestSize, PIP_OPTION_INFORMATION RequestOptions, LPVOID ReplyBuffer, DWORD ReplySize, DWORD Timeout);
void qemu_IcmpSendEcho2Ex(struct qemu_syscall *call)
{
    struct qemu_IcmpSendEcho2Ex *c = (struct qemu_IcmpSendEcho2Ex *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = IcmpSendEcho2Ex(QEMU_G2H(c->IcmpHandle), QEMU_G2H(c->Event), QEMU_G2H(c->ApcRoutine), QEMU_G2H(c->ApcContext), c->SourceAddress, c->DestinationAddress, QEMU_G2H(c->RequestData), c->RequestSize, QEMU_G2H(c->RequestOptions), QEMU_G2H(c->ReplyBuffer), c->ReplySize, c->Timeout);
}

#endif

