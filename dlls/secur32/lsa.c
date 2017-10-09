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
#include <sspi.h>
#include <ntsecapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_secur32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_secur32);
#endif


struct qemu_LsaCallAuthenticationPackage
{
    struct qemu_syscall super;
    uint64_t LsaHandle;
    uint64_t AuthenticationPackage;
    uint64_t ProtocolSubmitBuffer;
    uint64_t SubmitBufferLength;
    uint64_t ProtocolReturnBuffer;
    uint64_t ReturnBufferLength;
    uint64_t ProtocolStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaCallAuthenticationPackage(HANDLE LsaHandle, ULONG AuthenticationPackage, PVOID ProtocolSubmitBuffer, ULONG SubmitBufferLength, PVOID* ProtocolReturnBuffer, PULONG ReturnBufferLength, PNTSTATUS ProtocolStatus)
{
    struct qemu_LsaCallAuthenticationPackage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSACALLAUTHENTICATIONPACKAGE);
    call.LsaHandle = (ULONG_PTR)LsaHandle;
    call.AuthenticationPackage = (ULONG_PTR)AuthenticationPackage;
    call.ProtocolSubmitBuffer = (ULONG_PTR)ProtocolSubmitBuffer;
    call.SubmitBufferLength = (ULONG_PTR)SubmitBufferLength;
    call.ProtocolReturnBuffer = (ULONG_PTR)ProtocolReturnBuffer;
    call.ReturnBufferLength = (ULONG_PTR)ReturnBufferLength;
    call.ProtocolStatus = (ULONG_PTR)ProtocolStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaCallAuthenticationPackage(struct qemu_syscall *call)
{
    struct qemu_LsaCallAuthenticationPackage *c = (struct qemu_LsaCallAuthenticationPackage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaCallAuthenticationPackage(QEMU_G2H(c->LsaHandle), c->AuthenticationPackage, QEMU_G2H(c->ProtocolSubmitBuffer), c->SubmitBufferLength, QEMU_G2H(c->ProtocolReturnBuffer), QEMU_G2H(c->ReturnBufferLength), QEMU_G2H(c->ProtocolStatus));
}

#endif

struct qemu_LsaConnectUntrusted
{
    struct qemu_syscall super;
    uint64_t LsaHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaConnectUntrusted(PHANDLE LsaHandle)
{
    struct qemu_LsaConnectUntrusted call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSACONNECTUNTRUSTED);
    call.LsaHandle = (ULONG_PTR)LsaHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaConnectUntrusted(struct qemu_syscall *call)
{
    struct qemu_LsaConnectUntrusted *c = (struct qemu_LsaConnectUntrusted *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaConnectUntrusted(QEMU_G2H(c->LsaHandle));
}

#endif

struct qemu_LsaDeregisterLogonProcess
{
    struct qemu_syscall super;
    uint64_t LsaHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaDeregisterLogonProcess(HANDLE LsaHandle)
{
    struct qemu_LsaDeregisterLogonProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSADEREGISTERLOGONPROCESS);
    call.LsaHandle = (ULONG_PTR)LsaHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaDeregisterLogonProcess(struct qemu_syscall *call)
{
    struct qemu_LsaDeregisterLogonProcess *c = (struct qemu_LsaDeregisterLogonProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaDeregisterLogonProcess(QEMU_G2H(c->LsaHandle));
}

#endif

struct qemu_LsaEnumerateLogonSessions
{
    struct qemu_syscall super;
    uint64_t LogonSessionCount;
    uint64_t LogonSessionList;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaEnumerateLogonSessions(PULONG LogonSessionCount, PLUID* LogonSessionList)
{
    struct qemu_LsaEnumerateLogonSessions call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAENUMERATELOGONSESSIONS);
    call.LogonSessionCount = (ULONG_PTR)LogonSessionCount;
    call.LogonSessionList = (ULONG_PTR)LogonSessionList;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaEnumerateLogonSessions(struct qemu_syscall *call)
{
    struct qemu_LsaEnumerateLogonSessions *c = (struct qemu_LsaEnumerateLogonSessions *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaEnumerateLogonSessions(QEMU_G2H(c->LogonSessionCount), QEMU_G2H(c->LogonSessionList));
}

#endif

struct qemu_LsaFreeReturnBuffer
{
    struct qemu_syscall super;
    uint64_t Buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaFreeReturnBuffer(PVOID Buffer)
{
    struct qemu_LsaFreeReturnBuffer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAFREERETURNBUFFER);
    call.Buffer = (ULONG_PTR)Buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaFreeReturnBuffer(struct qemu_syscall *call)
{
    struct qemu_LsaFreeReturnBuffer *c = (struct qemu_LsaFreeReturnBuffer *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaFreeReturnBuffer(QEMU_G2H(c->Buffer));
}

#endif

struct qemu_LsaGetLogonSessionData
{
    struct qemu_syscall super;
    uint64_t LogonId;
    uint64_t ppLogonSessionData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaGetLogonSessionData(PLUID LogonId, PSECURITY_LOGON_SESSION_DATA* ppLogonSessionData)
{
    struct qemu_LsaGetLogonSessionData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAGETLOGONSESSIONDATA);
    call.LogonId = (ULONG_PTR)LogonId;
    call.ppLogonSessionData = (ULONG_PTR)ppLogonSessionData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaGetLogonSessionData(struct qemu_syscall *call)
{
    struct qemu_LsaGetLogonSessionData *c = (struct qemu_LsaGetLogonSessionData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaGetLogonSessionData(QEMU_G2H(c->LogonId), QEMU_G2H(c->ppLogonSessionData));
}

#endif

struct qemu_LsaLogonUser
{
    struct qemu_syscall super;
    uint64_t LsaHandle;
    uint64_t OriginName;
    uint64_t LogonType;
    uint64_t AuthenticationPackage;
    uint64_t AuthenticationInformation;
    uint64_t AuthenticationInformationLength;
    uint64_t LocalGroups;
    uint64_t SourceContext;
    uint64_t ProfileBuffer;
    uint64_t ProfileBufferLength;
    uint64_t LogonId;
    uint64_t Token;
    uint64_t Quotas;
    uint64_t SubStatus;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaLogonUser(HANDLE LsaHandle, PLSA_STRING OriginName, SECURITY_LOGON_TYPE LogonType, ULONG AuthenticationPackage, PVOID AuthenticationInformation, ULONG AuthenticationInformationLength, PTOKEN_GROUPS LocalGroups, PTOKEN_SOURCE SourceContext, PVOID* ProfileBuffer, PULONG ProfileBufferLength, PLUID LogonId, PHANDLE Token, PQUOTA_LIMITS Quotas, PNTSTATUS SubStatus)
{
    struct qemu_LsaLogonUser call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSALOGONUSER);
    call.LsaHandle = (ULONG_PTR)LsaHandle;
    call.OriginName = (ULONG_PTR)OriginName;
    call.LogonType = (ULONG_PTR)LogonType;
    call.AuthenticationPackage = (ULONG_PTR)AuthenticationPackage;
    call.AuthenticationInformation = (ULONG_PTR)AuthenticationInformation;
    call.AuthenticationInformationLength = (ULONG_PTR)AuthenticationInformationLength;
    call.LocalGroups = (ULONG_PTR)LocalGroups;
    call.SourceContext = (ULONG_PTR)SourceContext;
    call.ProfileBuffer = (ULONG_PTR)ProfileBuffer;
    call.ProfileBufferLength = (ULONG_PTR)ProfileBufferLength;
    call.LogonId = (ULONG_PTR)LogonId;
    call.Token = (ULONG_PTR)Token;
    call.Quotas = (ULONG_PTR)Quotas;
    call.SubStatus = (ULONG_PTR)SubStatus;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaLogonUser(struct qemu_syscall *call)
{
    struct qemu_LsaLogonUser *c = (struct qemu_LsaLogonUser *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaLogonUser(QEMU_G2H(c->LsaHandle), QEMU_G2H(c->OriginName), c->LogonType, c->AuthenticationPackage, QEMU_G2H(c->AuthenticationInformation), c->AuthenticationInformationLength, QEMU_G2H(c->LocalGroups), QEMU_G2H(c->SourceContext), QEMU_G2H(c->ProfileBuffer), QEMU_G2H(c->ProfileBufferLength), QEMU_G2H(c->LogonId), QEMU_G2H(c->Token), QEMU_G2H(c->Quotas), QEMU_G2H(c->SubStatus));
}

#endif

struct qemu_LsaLookupAuthenticationPackage
{
    struct qemu_syscall super;
    uint64_t LsaHandle;
    uint64_t PackageName;
    uint64_t AuthenticationPackage;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaLookupAuthenticationPackage(HANDLE LsaHandle, PLSA_STRING PackageName, PULONG AuthenticationPackage)
{
    struct qemu_LsaLookupAuthenticationPackage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSALOOKUPAUTHENTICATIONPACKAGE);
    call.LsaHandle = (ULONG_PTR)LsaHandle;
    call.PackageName = (ULONG_PTR)PackageName;
    call.AuthenticationPackage = (ULONG_PTR)AuthenticationPackage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaLookupAuthenticationPackage(struct qemu_syscall *call)
{
    struct qemu_LsaLookupAuthenticationPackage *c = (struct qemu_LsaLookupAuthenticationPackage *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaLookupAuthenticationPackage(QEMU_G2H(c->LsaHandle), QEMU_G2H(c->PackageName), QEMU_G2H(c->AuthenticationPackage));
}

#endif

struct qemu_LsaRegisterLogonProcess
{
    struct qemu_syscall super;
    uint64_t LogonProcessName;
    uint64_t LsaHandle;
    uint64_t SecurityMode;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI LsaRegisterLogonProcess(PLSA_STRING LogonProcessName, PHANDLE LsaHandle, PLSA_OPERATIONAL_MODE SecurityMode)
{
    struct qemu_LsaRegisterLogonProcess call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LSAREGISTERLOGONPROCESS);
    call.LogonProcessName = (ULONG_PTR)LogonProcessName;
    call.LsaHandle = (ULONG_PTR)LsaHandle;
    call.SecurityMode = (ULONG_PTR)SecurityMode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_LsaRegisterLogonProcess(struct qemu_syscall *call)
{
    struct qemu_LsaRegisterLogonProcess *c = (struct qemu_LsaRegisterLogonProcess *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = LsaRegisterLogonProcess(QEMU_G2H(c->LogonProcessName), QEMU_G2H(c->LsaHandle), QEMU_G2H(c->SecurityMode));
}

#endif

