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

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ntdef.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ntdll.h"

#ifdef QEMU_DLL_GUEST

/* I can't make mingw's ddk headers work :-(, and even if they worked they
 * are missing definitions of these types. */
typedef void *PLPC_SECTION_WRITE, *PLPC_SECTION_READ, *PLPC_MESSAGE;
typedef unsigned int SHUTDOWN_ACTION, KPROFILE_SOURCE, SYSDBG_COMMAND;
typedef struct _COUNTED_REASON_CONTEXT COUNTED_REASON_CONTEXT;

#else

#include <ddk/ntddk.h>
#include <wine/debug.h>

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ntdll);

#endif

struct qemu_NtDuplicateToken
{
    struct qemu_syscall super;
    uint64_t ExistingToken;
    uint64_t DesiredAccess;
    uint64_t ObjectAttributes;
    uint64_t ImpersonationLevel;
    uint64_t TokenType;
    uint64_t NewToken;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtDuplicateToken(IN HANDLE ExistingToken, IN ACCESS_MASK DesiredAccess, IN POBJECT_ATTRIBUTES ObjectAttributes, IN SECURITY_IMPERSONATION_LEVEL ImpersonationLevel, IN TOKEN_TYPE TokenType, OUT PHANDLE NewToken)
{
    struct qemu_NtDuplicateToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDUPLICATETOKEN);
    call.ExistingToken = (ULONG_PTR)ExistingToken;
    call.DesiredAccess = (ULONG_PTR)DesiredAccess;
    call.ObjectAttributes = (ULONG_PTR)ObjectAttributes;
    call.ImpersonationLevel = (ULONG_PTR)ImpersonationLevel;
    call.TokenType = (ULONG_PTR)TokenType;
    call.NewToken = (ULONG_PTR)NewToken;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtDuplicateToken(struct qemu_syscall *call)
{
    struct qemu_NtDuplicateToken *c = (struct qemu_NtDuplicateToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtDuplicateToken((HANDLE)c->ExistingToken, c->DesiredAccess, QEMU_G2H(c->ObjectAttributes), c->ImpersonationLevel, c->TokenType, QEMU_G2H(c->NewToken));
}

#endif

struct qemu_NtOpenProcessToken
{
    struct qemu_syscall super;
    uint64_t ProcessHandle;
    uint64_t DesiredAccess;
    uint64_t TokenHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenProcessToken(HANDLE ProcessHandle, DWORD DesiredAccess, HANDLE *TokenHandle)
{
    struct qemu_NtOpenProcessToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENPROCESSTOKEN);
    call.ProcessHandle = (ULONG_PTR)ProcessHandle;
    call.DesiredAccess = (ULONG_PTR)DesiredAccess;
    call.TokenHandle = (ULONG_PTR)TokenHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenProcessToken(struct qemu_syscall *call)
{
    struct qemu_NtOpenProcessToken *c = (struct qemu_NtOpenProcessToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenProcessToken(QEMU_G2H(c->ProcessHandle), c->DesiredAccess, QEMU_G2H(c->TokenHandle));
}

#endif

struct qemu_NtOpenProcessTokenEx
{
    struct qemu_syscall super;
    uint64_t process;
    uint64_t access;
    uint64_t attributes;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenProcessTokenEx(HANDLE process, DWORD access, DWORD attributes, HANDLE *handle)
{
    struct qemu_NtOpenProcessTokenEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENPROCESSTOKENEX);
    call.process = (ULONG_PTR)process;
    call.access = (ULONG_PTR)access;
    call.attributes = (ULONG_PTR)attributes;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenProcessTokenEx(struct qemu_syscall *call)
{
    struct qemu_NtOpenProcessTokenEx *c = (struct qemu_NtOpenProcessTokenEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenProcessTokenEx(QEMU_G2H(c->process), c->access, c->attributes, QEMU_G2H(c->handle));
}

#endif

struct qemu_NtOpenThreadToken
{
    struct qemu_syscall super;
    uint64_t ThreadHandle;
    uint64_t DesiredAccess;
    uint64_t OpenAsSelf;
    uint64_t TokenHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenThreadToken(HANDLE ThreadHandle, DWORD DesiredAccess, BOOLEAN OpenAsSelf, HANDLE *TokenHandle)
{
    struct qemu_NtOpenThreadToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENTHREADTOKEN);
    call.ThreadHandle = (ULONG_PTR)ThreadHandle;
    call.DesiredAccess = (ULONG_PTR)DesiredAccess;
    call.OpenAsSelf = (ULONG_PTR)OpenAsSelf;
    call.TokenHandle = (ULONG_PTR)TokenHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenThreadToken(struct qemu_syscall *call)
{
    struct qemu_NtOpenThreadToken *c = (struct qemu_NtOpenThreadToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenThreadToken(QEMU_G2H(c->ThreadHandle), c->DesiredAccess, c->OpenAsSelf, QEMU_G2H(c->TokenHandle));
}

#endif

struct qemu_NtOpenThreadTokenEx
{
    struct qemu_syscall super;
    uint64_t thread;
    uint64_t access;
    uint64_t as_self;
    uint64_t attributes;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtOpenThreadTokenEx(HANDLE thread, DWORD access, BOOLEAN as_self, DWORD attributes, HANDLE *handle)
{
    struct qemu_NtOpenThreadTokenEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTOPENTHREADTOKENEX);
    call.thread = (ULONG_PTR)thread;
    call.access = (ULONG_PTR)access;
    call.as_self = (ULONG_PTR)as_self;
    call.attributes = (ULONG_PTR)attributes;
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtOpenThreadTokenEx(struct qemu_syscall *call)
{
    struct qemu_NtOpenThreadTokenEx *c = (struct qemu_NtOpenThreadTokenEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtOpenThreadTokenEx(QEMU_G2H(c->thread), c->access, c->as_self, c->attributes, QEMU_G2H(c->handle));
}

#endif

struct qemu_NtAdjustPrivilegesToken
{
    struct qemu_syscall super;
    uint64_t TokenHandle;
    uint64_t DisableAllPrivileges;
    uint64_t NewState;
    uint64_t BufferLength;
    uint64_t PreviousState;
    uint64_t ReturnLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtAdjustPrivilegesToken(IN HANDLE TokenHandle, IN BOOLEAN DisableAllPrivileges, IN PTOKEN_PRIVILEGES NewState, IN DWORD BufferLength, OUT PTOKEN_PRIVILEGES PreviousState, OUT PDWORD ReturnLength)
{
    struct qemu_NtAdjustPrivilegesToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTADJUSTPRIVILEGESTOKEN);
    call.TokenHandle = (ULONG_PTR)TokenHandle;
    call.DisableAllPrivileges = (ULONG_PTR)DisableAllPrivileges;
    call.NewState = (ULONG_PTR)NewState;
    call.BufferLength = (ULONG_PTR)BufferLength;
    call.PreviousState = (ULONG_PTR)PreviousState;
    call.ReturnLength = (ULONG_PTR)ReturnLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtAdjustPrivilegesToken(struct qemu_syscall *call)
{
    struct qemu_NtAdjustPrivilegesToken *c = (struct qemu_NtAdjustPrivilegesToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtAdjustPrivilegesToken((HANDLE)c->TokenHandle, c->DisableAllPrivileges, QEMU_G2H(c->NewState), c->BufferLength, QEMU_G2H(c->PreviousState), QEMU_G2H(c->ReturnLength));
}

#endif

struct qemu_NtQueryInformationToken
{
    struct qemu_syscall super;
    uint64_t token;
    uint64_t tokeninfoclass;
    uint64_t tokeninfo;
    uint64_t tokeninfolength;
    uint64_t retlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQueryInformationToken(HANDLE token, TOKEN_INFORMATION_CLASS tokeninfoclass, PVOID tokeninfo, ULONG tokeninfolength, PULONG retlen)
{
    struct qemu_NtQueryInformationToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYINFORMATIONTOKEN);
    call.token = (ULONG_PTR)token;
    call.tokeninfoclass = (ULONG_PTR)tokeninfoclass;
    call.tokeninfo = (ULONG_PTR)tokeninfo;
    call.tokeninfolength = (ULONG_PTR)tokeninfolength;
    call.retlen = (ULONG_PTR)retlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQueryInformationToken(struct qemu_syscall *call)
{
    struct qemu_NtQueryInformationToken *c = (struct qemu_NtQueryInformationToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQueryInformationToken(QEMU_G2H(c->token), c->tokeninfoclass, QEMU_G2H(c->tokeninfo), c->tokeninfolength, QEMU_G2H(c->retlen));
}

#endif

struct qemu_NtSetInformationToken
{
    struct qemu_syscall super;
    uint64_t TokenHandle;
    uint64_t TokenInformationClass;
    uint64_t TokenInformation;
    uint64_t TokenInformationLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetInformationToken(HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, PVOID TokenInformation, ULONG TokenInformationLength)
{
    struct qemu_NtSetInformationToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETINFORMATIONTOKEN);
    call.TokenHandle = (ULONG_PTR)TokenHandle;
    call.TokenInformationClass = (ULONG_PTR)TokenInformationClass;
    call.TokenInformation = (ULONG_PTR)TokenInformation;
    call.TokenInformationLength = (ULONG_PTR)TokenInformationLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetInformationToken(struct qemu_syscall *call)
{
    struct qemu_NtSetInformationToken *c = (struct qemu_NtSetInformationToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetInformationToken(QEMU_G2H(c->TokenHandle), c->TokenInformationClass, QEMU_G2H(c->TokenInformation), c->TokenInformationLength);
}

#endif

struct qemu_NtAdjustGroupsToken
{
    struct qemu_syscall super;
    uint64_t TokenHandle;
    uint64_t ResetToDefault;
    uint64_t NewState;
    uint64_t BufferLength;
    uint64_t PreviousState;
    uint64_t ReturnLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtAdjustGroupsToken(HANDLE TokenHandle, BOOLEAN ResetToDefault, PTOKEN_GROUPS NewState, ULONG BufferLength, PTOKEN_GROUPS PreviousState, PULONG ReturnLength)
{
    struct qemu_NtAdjustGroupsToken call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTADJUSTGROUPSTOKEN);
    call.TokenHandle = (ULONG_PTR)TokenHandle;
    call.ResetToDefault = (ULONG_PTR)ResetToDefault;
    call.NewState = (ULONG_PTR)NewState;
    call.BufferLength = (ULONG_PTR)BufferLength;
    call.PreviousState = (ULONG_PTR)PreviousState;
    call.ReturnLength = (ULONG_PTR)ReturnLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtAdjustGroupsToken(struct qemu_syscall *call)
{
    struct qemu_NtAdjustGroupsToken *c = (struct qemu_NtAdjustGroupsToken *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtAdjustGroupsToken(QEMU_G2H(c->TokenHandle), c->ResetToDefault, QEMU_G2H(c->NewState), c->BufferLength, QEMU_G2H(c->PreviousState), QEMU_G2H(c->ReturnLength));
}

#endif

struct qemu_NtPrivilegeCheck
{
    struct qemu_syscall super;
    uint64_t ClientToken;
    uint64_t RequiredPrivileges;
    uint64_t Result;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtPrivilegeCheck(HANDLE ClientToken, PPRIVILEGE_SET RequiredPrivileges, PBOOLEAN Result)
{
    struct qemu_NtPrivilegeCheck call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTPRIVILEGECHECK);
    call.ClientToken = (ULONG_PTR)ClientToken;
    call.RequiredPrivileges = (ULONG_PTR)RequiredPrivileges;
    call.Result = (ULONG_PTR)Result;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtPrivilegeCheck(struct qemu_syscall *call)
{
    struct qemu_NtPrivilegeCheck *c = (struct qemu_NtPrivilegeCheck *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtPrivilegeCheck(QEMU_G2H(c->ClientToken), QEMU_G2H(c->RequiredPrivileges), QEMU_G2H(c->Result));
}

#endif

struct qemu_NtCreatePort
{
    struct qemu_syscall super;
    uint64_t PortHandle;
    uint64_t ObjectAttributes;
    uint64_t MaxConnectInfoLength;
    uint64_t MaxDataLength;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreatePort(PHANDLE PortHandle,POBJECT_ATTRIBUTES ObjectAttributes, ULONG MaxConnectInfoLength,ULONG MaxDataLength,PULONG reserved)
{
    struct qemu_NtCreatePort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATEPORT);
    call.PortHandle = (ULONG_PTR)PortHandle;
    call.ObjectAttributes = (ULONG_PTR)ObjectAttributes;
    call.MaxConnectInfoLength = (ULONG_PTR)MaxConnectInfoLength;
    call.MaxDataLength = (ULONG_PTR)MaxDataLength;
    call.reserved = (ULONG_PTR)reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCreatePort(struct qemu_syscall *call)
{
    struct qemu_NtCreatePort *c = (struct qemu_NtCreatePort *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCreatePort(QEMU_G2H(c->PortHandle), QEMU_G2H(c->ObjectAttributes), c->MaxConnectInfoLength, c->MaxDataLength, QEMU_G2H(c->reserved));
}

#endif

struct qemu_NtConnectPort
{
    struct qemu_syscall super;
    uint64_t PortHandle;
    uint64_t PortName;
    uint64_t SecurityQos;
    uint64_t WriteSection;
    uint64_t ReadSection;
    uint64_t MaximumMessageLength;
    uint64_t ConnectInfo;
    uint64_t pConnectInfoLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtConnectPort(PHANDLE PortHandle, PUNICODE_STRING PortName, PSECURITY_QUALITY_OF_SERVICE SecurityQos, PLPC_SECTION_WRITE WriteSection, PLPC_SECTION_READ ReadSection, PULONG MaximumMessageLength, PVOID ConnectInfo, PULONG pConnectInfoLength)
{
    struct qemu_NtConnectPort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCONNECTPORT);
    call.PortHandle = (ULONG_PTR)PortHandle;
    call.PortName = (ULONG_PTR)PortName;
    call.SecurityQos = (ULONG_PTR)SecurityQos;
    call.WriteSection = (ULONG_PTR)WriteSection;
    call.ReadSection = (ULONG_PTR)ReadSection;
    call.MaximumMessageLength = (ULONG_PTR)MaximumMessageLength;
    call.ConnectInfo = (ULONG_PTR)ConnectInfo;
    call.pConnectInfoLength = (ULONG_PTR)pConnectInfoLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtConnectPort(struct qemu_syscall *call)
{
    struct qemu_NtConnectPort *c = (struct qemu_NtConnectPort *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtConnectPort(QEMU_G2H(c->PortHandle), QEMU_G2H(c->PortName), QEMU_G2H(c->SecurityQos), QEMU_G2H(c->WriteSection), QEMU_G2H(c->ReadSection), QEMU_G2H(c->MaximumMessageLength), QEMU_G2H(c->ConnectInfo), QEMU_G2H(c->pConnectInfoLength));
}

#endif

struct qemu_NtSecureConnectPort
{
    struct qemu_syscall super;
    uint64_t PortHandle;
    uint64_t PortName;
    uint64_t SecurityQos;
    uint64_t WriteSection;
    uint64_t pSid;
    uint64_t ReadSection;
    uint64_t MaximumMessageLength;
    uint64_t ConnectInfo;
    uint64_t pConnectInfoLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSecureConnectPort(PHANDLE PortHandle, PUNICODE_STRING PortName, PSECURITY_QUALITY_OF_SERVICE SecurityQos, PLPC_SECTION_WRITE WriteSection, PSID pSid, PLPC_SECTION_READ ReadSection, PULONG MaximumMessageLength, PVOID ConnectInfo, PULONG pConnectInfoLength)
{
    struct qemu_NtSecureConnectPort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSECURECONNECTPORT);
    call.PortHandle = (ULONG_PTR)PortHandle;
    call.PortName = (ULONG_PTR)PortName;
    call.SecurityQos = (ULONG_PTR)SecurityQos;
    call.WriteSection = (ULONG_PTR)WriteSection;
    call.pSid = (ULONG_PTR)pSid;
    call.ReadSection = (ULONG_PTR)ReadSection;
    call.MaximumMessageLength = (ULONG_PTR)MaximumMessageLength;
    call.ConnectInfo = (ULONG_PTR)ConnectInfo;
    call.pConnectInfoLength = (ULONG_PTR)pConnectInfoLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSecureConnectPort(struct qemu_syscall *call)
{
    struct qemu_NtSecureConnectPort *c = (struct qemu_NtSecureConnectPort *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSecureConnectPort(QEMU_G2H(c->PortHandle), QEMU_G2H(c->PortName), QEMU_G2H(c->SecurityQos), QEMU_G2H(c->WriteSection), QEMU_G2H(c->pSid), QEMU_G2H(c->ReadSection), QEMU_G2H(c->MaximumMessageLength), QEMU_G2H(c->ConnectInfo), QEMU_G2H(c->pConnectInfoLength));
}

#endif

struct qemu_NtListenPort
{
    struct qemu_syscall super;
    uint64_t PortHandle;
    uint64_t pLpcMessage;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtListenPort(HANDLE PortHandle,PLPC_MESSAGE pLpcMessage)
{
    struct qemu_NtListenPort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTLISTENPORT);
    call.PortHandle = (ULONG_PTR)PortHandle;
    call.pLpcMessage = (ULONG_PTR)pLpcMessage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtListenPort(struct qemu_syscall *call)
{
    struct qemu_NtListenPort *c = (struct qemu_NtListenPort *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtListenPort(QEMU_G2H(c->PortHandle), QEMU_G2H(c->pLpcMessage));
}

#endif

struct qemu_NtAcceptConnectPort
{
    struct qemu_syscall super;
    uint64_t PortHandle;
    uint64_t PortIdentifier;
    uint64_t pLpcMessage;
    uint64_t Accept;
    uint64_t WriteSection;
    uint64_t ReadSection;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtAcceptConnectPort(PHANDLE PortHandle, ULONG PortIdentifier, PLPC_MESSAGE pLpcMessage, BOOLEAN Accept, PLPC_SECTION_WRITE WriteSection, PLPC_SECTION_READ ReadSection)
{
    struct qemu_NtAcceptConnectPort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTACCEPTCONNECTPORT);
    call.PortHandle = (ULONG_PTR)PortHandle;
    call.PortIdentifier = (ULONG_PTR)PortIdentifier;
    call.pLpcMessage = (ULONG_PTR)pLpcMessage;
    call.Accept = (ULONG_PTR)Accept;
    call.WriteSection = (ULONG_PTR)WriteSection;
    call.ReadSection = (ULONG_PTR)ReadSection;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtAcceptConnectPort(struct qemu_syscall *call)
{
    struct qemu_NtAcceptConnectPort *c = (struct qemu_NtAcceptConnectPort *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtAcceptConnectPort(QEMU_G2H(c->PortHandle), c->PortIdentifier, QEMU_G2H(c->pLpcMessage), c->Accept, QEMU_G2H(c->WriteSection), QEMU_G2H(c->ReadSection));
}

#endif

struct qemu_NtCompleteConnectPort
{
    struct qemu_syscall super;
    uint64_t PortHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCompleteConnectPort(HANDLE PortHandle)
{
    struct qemu_NtCompleteConnectPort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCOMPLETECONNECTPORT);
    call.PortHandle = (ULONG_PTR)PortHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCompleteConnectPort(struct qemu_syscall *call)
{
    struct qemu_NtCompleteConnectPort *c = (struct qemu_NtCompleteConnectPort *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCompleteConnectPort(QEMU_G2H(c->PortHandle));
}

#endif

struct qemu_NtRegisterThreadTerminatePort
{
    struct qemu_syscall super;
    uint64_t PortHandle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtRegisterThreadTerminatePort(HANDLE PortHandle)
{
    struct qemu_NtRegisterThreadTerminatePort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTREGISTERTHREADTERMINATEPORT);
    call.PortHandle = (ULONG_PTR)PortHandle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtRegisterThreadTerminatePort(struct qemu_syscall *call)
{
    struct qemu_NtRegisterThreadTerminatePort *c = (struct qemu_NtRegisterThreadTerminatePort *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtRegisterThreadTerminatePort(QEMU_G2H(c->PortHandle));
}

#endif

struct qemu_NtRequestWaitReplyPort
{
    struct qemu_syscall super;
    uint64_t PortHandle;
    uint64_t pLpcMessageIn;
    uint64_t pLpcMessageOut;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtRequestWaitReplyPort(HANDLE PortHandle, PLPC_MESSAGE pLpcMessageIn, PLPC_MESSAGE pLpcMessageOut)
{
    struct qemu_NtRequestWaitReplyPort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTREQUESTWAITREPLYPORT);
    call.PortHandle = (ULONG_PTR)PortHandle;
    call.pLpcMessageIn = (ULONG_PTR)pLpcMessageIn;
    call.pLpcMessageOut = (ULONG_PTR)pLpcMessageOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtRequestWaitReplyPort(struct qemu_syscall *call)
{
    struct qemu_NtRequestWaitReplyPort *c = (struct qemu_NtRequestWaitReplyPort *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtRequestWaitReplyPort(QEMU_G2H(c->PortHandle), QEMU_G2H(c->pLpcMessageIn), QEMU_G2H(c->pLpcMessageOut));
}

#endif

struct qemu_NtReplyWaitReceivePort
{
    struct qemu_syscall super;
    uint64_t PortHandle;
    uint64_t PortIdentifier;
    uint64_t ReplyMessage;
    uint64_t Message;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtReplyWaitReceivePort(HANDLE PortHandle, PULONG PortIdentifier, PLPC_MESSAGE ReplyMessage, PLPC_MESSAGE Message)
{
    struct qemu_NtReplyWaitReceivePort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTREPLYWAITRECEIVEPORT);
    call.PortHandle = (ULONG_PTR)PortHandle;
    call.PortIdentifier = (ULONG_PTR)PortIdentifier;
    call.ReplyMessage = (ULONG_PTR)ReplyMessage;
    call.Message = (ULONG_PTR)Message;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtReplyWaitReceivePort(struct qemu_syscall *call)
{
    struct qemu_NtReplyWaitReceivePort *c = (struct qemu_NtReplyWaitReceivePort *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtReplyWaitReceivePort(QEMU_G2H(c->PortHandle), QEMU_G2H(c->PortIdentifier), QEMU_G2H(c->ReplyMessage), QEMU_G2H(c->Message));
}

#endif

struct qemu_NtSetIntervalProfile
{
    struct qemu_syscall super;
    uint64_t Interval;
    uint64_t Source;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetIntervalProfile(ULONG Interval, KPROFILE_SOURCE Source)
{
    struct qemu_NtSetIntervalProfile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETINTERVALPROFILE);
    call.Interval = (ULONG_PTR)Interval;
    call.Source = (ULONG_PTR)Source;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetIntervalProfile(struct qemu_syscall *call)
{
    struct qemu_NtSetIntervalProfile *c = (struct qemu_NtSetIntervalProfile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetIntervalProfile(c->Interval, c->Source);
}

#endif

struct qemu_NtQuerySystemInformation
{
    struct qemu_syscall super;
    uint64_t SystemInformationClass;
    uint64_t SystemInformation;
    uint64_t Length;
    uint64_t ResultLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQuerySystemInformation(IN SYSTEM_INFORMATION_CLASS SystemInformationClass, OUT PVOID SystemInformation, IN ULONG Length, OUT PULONG ResultLength)
{
    struct qemu_NtQuerySystemInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYSYSTEMINFORMATION);
    call.SystemInformationClass = (ULONG_PTR)SystemInformationClass;
    call.SystemInformation = (ULONG_PTR)SystemInformation;
    call.Length = (ULONG_PTR)Length;
    call.ResultLength = (ULONG_PTR)ResultLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQuerySystemInformation(struct qemu_syscall *call)
{
    struct qemu_NtQuerySystemInformation *c = (struct qemu_NtQuerySystemInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQuerySystemInformation(c->SystemInformationClass, QEMU_G2H(c->SystemInformation), c->Length, QEMU_G2H(c->ResultLength));
}

#endif

struct qemu_NtQuerySystemInformationEx
{
    struct qemu_syscall super;
    uint64_t SystemInformationClass;
    uint64_t Query;
    uint64_t QueryLength;
    uint64_t SystemInformation;
    uint64_t Length;
    uint64_t ResultLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtQuerySystemInformationEx(SYSTEM_INFORMATION_CLASS SystemInformationClass, void *Query, ULONG QueryLength, void *SystemInformation, ULONG Length, ULONG *ResultLength)
{
    struct qemu_NtQuerySystemInformationEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTQUERYSYSTEMINFORMATIONEX);
    call.SystemInformationClass = (ULONG_PTR)SystemInformationClass;
    call.Query = (ULONG_PTR)Query;
    call.QueryLength = (ULONG_PTR)QueryLength;
    call.SystemInformation = (ULONG_PTR)SystemInformation;
    call.Length = (ULONG_PTR)Length;
    call.ResultLength = (ULONG_PTR)ResultLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtQuerySystemInformationEx(struct qemu_syscall *call)
{
    struct qemu_NtQuerySystemInformationEx *c = (struct qemu_NtQuerySystemInformationEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtQuerySystemInformationEx(c->SystemInformationClass, QEMU_G2H(c->Query), c->QueryLength, QEMU_G2H(c->SystemInformation), c->Length, QEMU_G2H(c->ResultLength));
}

#endif

struct qemu_NtSetSystemInformation
{
    struct qemu_syscall super;
    uint64_t SystemInformationClass;
    uint64_t SystemInformation;
    uint64_t Length;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetSystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG Length)
{
    struct qemu_NtSetSystemInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETSYSTEMINFORMATION);
    call.SystemInformationClass = (ULONG_PTR)SystemInformationClass;
    call.SystemInformation = (ULONG_PTR)SystemInformation;
    call.Length = (ULONG_PTR)Length;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetSystemInformation(struct qemu_syscall *call)
{
    struct qemu_NtSetSystemInformation *c = (struct qemu_NtSetSystemInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetSystemInformation(c->SystemInformationClass, QEMU_G2H(c->SystemInformation), c->Length);
}

#endif

struct qemu_NtCreatePagingFile
{
    struct qemu_syscall super;
    uint64_t PageFileName;
    uint64_t MinimumSize;
    uint64_t MaximumSize;
    uint64_t ActualSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreatePagingFile(PUNICODE_STRING PageFileName, PLARGE_INTEGER MinimumSize, PLARGE_INTEGER MaximumSize, PLARGE_INTEGER ActualSize)
{
    struct qemu_NtCreatePagingFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATEPAGINGFILE);
    call.PageFileName = (ULONG_PTR)PageFileName;
    call.MinimumSize = (ULONG_PTR)MinimumSize;
    call.MaximumSize = (ULONG_PTR)MaximumSize;
    call.ActualSize = (ULONG_PTR)ActualSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCreatePagingFile(struct qemu_syscall *call)
{
    struct qemu_NtCreatePagingFile *c = (struct qemu_NtCreatePagingFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCreatePagingFile(QEMU_G2H(c->PageFileName), QEMU_G2H(c->MinimumSize), QEMU_G2H(c->MaximumSize), QEMU_G2H(c->ActualSize));
}

#endif

struct qemu_NtDisplayString
{
    struct qemu_syscall super;
    uint64_t string;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtDisplayString (PUNICODE_STRING string)
{
    struct qemu_NtDisplayString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTDISPLAYSTRING);
    call.string = (ULONG_PTR)string;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtDisplayString(struct qemu_syscall *call)
{
    struct qemu_NtDisplayString *c = (struct qemu_NtDisplayString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtDisplayString(QEMU_G2H(c->string));
}

#endif

struct qemu_NtInitiatePowerAction
{
    struct qemu_syscall super;
    uint64_t SystemAction;
    uint64_t MinSystemState;
    uint64_t Flags;
    uint64_t Asynchronous;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtInitiatePowerAction(IN POWER_ACTION SystemAction, IN SYSTEM_POWER_STATE MinSystemState, IN ULONG Flags, IN BOOLEAN Asynchronous)
{
    struct qemu_NtInitiatePowerAction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTINITIATEPOWERACTION);
    call.SystemAction = (ULONG_PTR)SystemAction;
    call.MinSystemState = (ULONG_PTR)MinSystemState;
    call.Flags = (ULONG_PTR)Flags;
    call.Asynchronous = (ULONG_PTR)Asynchronous;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtInitiatePowerAction(struct qemu_syscall *call)
{
    struct qemu_NtInitiatePowerAction *c = (struct qemu_NtInitiatePowerAction *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtInitiatePowerAction(c->SystemAction, c->MinSystemState, c->Flags, c->Asynchronous);
}

#endif

struct qemu_NtPowerInformation
{
    struct qemu_syscall super;
    uint64_t InformationLevel;
    uint64_t lpInputBuffer;
    uint64_t nInputBufferSize;
    uint64_t lpOutputBuffer;
    uint64_t nOutputBufferSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtPowerInformation(IN POWER_INFORMATION_LEVEL InformationLevel, IN PVOID lpInputBuffer, IN ULONG nInputBufferSize, IN PVOID lpOutputBuffer, IN ULONG nOutputBufferSize)
{
    struct qemu_NtPowerInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTPOWERINFORMATION);
    call.InformationLevel = (ULONG_PTR)InformationLevel;
    call.lpInputBuffer = (ULONG_PTR)lpInputBuffer;
    call.nInputBufferSize = (ULONG_PTR)nInputBufferSize;
    call.lpOutputBuffer = (ULONG_PTR)lpOutputBuffer;
    call.nOutputBufferSize = (ULONG_PTR)nOutputBufferSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtPowerInformation(struct qemu_syscall *call)
{
    struct qemu_NtPowerInformation *c = (struct qemu_NtPowerInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtPowerInformation(c->InformationLevel, QEMU_G2H(c->lpInputBuffer), c->nInputBufferSize, QEMU_G2H(c->lpOutputBuffer), c->nOutputBufferSize);
}

#endif

struct qemu_NtShutdownSystem
{
    struct qemu_syscall super;
    uint64_t Action;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtShutdownSystem(SHUTDOWN_ACTION Action)
{
    struct qemu_NtShutdownSystem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSHUTDOWNSYSTEM);
    call.Action = (ULONG_PTR)Action;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtShutdownSystem(struct qemu_syscall *call)
{
    struct qemu_NtShutdownSystem *c = (struct qemu_NtShutdownSystem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtShutdownSystem(c->Action);
}

#endif

struct qemu_NtAllocateLocallyUniqueId
{
    struct qemu_syscall super;
    uint64_t Luid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtAllocateLocallyUniqueId(PLUID Luid)
{
    struct qemu_NtAllocateLocallyUniqueId call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTALLOCATELOCALLYUNIQUEID);
    call.Luid = (ULONG_PTR)Luid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtAllocateLocallyUniqueId(struct qemu_syscall *call)
{
    struct qemu_NtAllocateLocallyUniqueId *c = (struct qemu_NtAllocateLocallyUniqueId *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtAllocateLocallyUniqueId(QEMU_G2H(c->Luid));
}

#endif

struct qemu_VerSetConditionMask
{
    struct qemu_syscall super;
    uint64_t dwlConditionMask;
    uint64_t dwTypeBitMask;
    uint64_t dwConditionMask;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONGLONG WINAPI VerSetConditionMask(ULONGLONG dwlConditionMask, DWORD dwTypeBitMask, BYTE dwConditionMask)
{
    struct qemu_VerSetConditionMask call;
    call.super.id = QEMU_SYSCALL_ID(CALL_VERSETCONDITIONMASK);
    call.dwlConditionMask = dwlConditionMask;
    call.dwTypeBitMask = dwTypeBitMask;
    call.dwConditionMask = dwConditionMask;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_VerSetConditionMask(struct qemu_syscall *call)
{
    struct qemu_VerSetConditionMask *c = (struct qemu_VerSetConditionMask *)call;
    WINE_TRACE("\n");
    c->super.iret = VerSetConditionMask(c->dwlConditionMask, c->dwTypeBitMask, c->dwConditionMask);
}

#endif

struct qemu_NtAccessCheckAndAuditAlarm
{
    struct qemu_syscall super;
    uint64_t SubsystemName;
    uint64_t HandleId;
    uint64_t ObjectTypeName;
    uint64_t ObjectName;
    uint64_t SecurityDescriptor;
    uint64_t DesiredAccess;
    uint64_t GenericMapping;
    uint64_t ObjectCreation;
    uint64_t GrantedAccess;
    uint64_t AccessStatus;
    uint64_t GenerateOnClose;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtAccessCheckAndAuditAlarm(PUNICODE_STRING SubsystemName, HANDLE HandleId, PUNICODE_STRING ObjectTypeName, PUNICODE_STRING ObjectName, PSECURITY_DESCRIPTOR SecurityDescriptor, ACCESS_MASK DesiredAccess, PGENERIC_MAPPING GenericMapping, BOOLEAN ObjectCreation, PACCESS_MASK GrantedAccess, PBOOLEAN AccessStatus, PBOOLEAN GenerateOnClose)
{
    struct qemu_NtAccessCheckAndAuditAlarm call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTACCESSCHECKANDAUDITALARM);
    call.SubsystemName = (ULONG_PTR)SubsystemName;
    call.HandleId = (ULONG_PTR)HandleId;
    call.ObjectTypeName = (ULONG_PTR)ObjectTypeName;
    call.ObjectName = (ULONG_PTR)ObjectName;
    call.SecurityDescriptor = (ULONG_PTR)SecurityDescriptor;
    call.DesiredAccess = (ULONG_PTR)DesiredAccess;
    call.GenericMapping = (ULONG_PTR)GenericMapping;
    call.ObjectCreation = (ULONG_PTR)ObjectCreation;
    call.GrantedAccess = (ULONG_PTR)GrantedAccess;
    call.AccessStatus = (ULONG_PTR)AccessStatus;
    call.GenerateOnClose = (ULONG_PTR)GenerateOnClose;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtAccessCheckAndAuditAlarm(struct qemu_syscall *call)
{
    struct qemu_NtAccessCheckAndAuditAlarm *c = (struct qemu_NtAccessCheckAndAuditAlarm *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtAccessCheckAndAuditAlarm(QEMU_G2H(c->SubsystemName), QEMU_G2H(c->HandleId), QEMU_G2H(c->ObjectTypeName), QEMU_G2H(c->ObjectName), QEMU_G2H(c->SecurityDescriptor), c->DesiredAccess, QEMU_G2H(c->GenericMapping), c->ObjectCreation, QEMU_G2H(c->GrantedAccess), QEMU_G2H(c->AccessStatus), QEMU_G2H(c->GenerateOnClose));
}

#endif

struct qemu_NtSystemDebugControl
{
    struct qemu_syscall super;
    uint64_t command;
    uint64_t inbuffer;
    uint64_t inbuflength;
    uint64_t outbuffer;
    uint64_t outbuflength;
    uint64_t retlength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSystemDebugControl(SYSDBG_COMMAND command, PVOID inbuffer, ULONG inbuflength, PVOID outbuffer, ULONG outbuflength, PULONG retlength)
{
    struct qemu_NtSystemDebugControl call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSYSTEMDEBUGCONTROL);
    call.command = (ULONG_PTR)command;
    call.inbuffer = (ULONG_PTR)inbuffer;
    call.inbuflength = (ULONG_PTR)inbuflength;
    call.outbuffer = (ULONG_PTR)outbuffer;
    call.outbuflength = (ULONG_PTR)outbuflength;
    call.retlength = (ULONG_PTR)retlength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSystemDebugControl(struct qemu_syscall *call)
{
    struct qemu_NtSystemDebugControl *c = (struct qemu_NtSystemDebugControl *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSystemDebugControl(c->command, QEMU_G2H(c->inbuffer), c->inbuflength, QEMU_G2H(c->outbuffer), c->outbuflength, QEMU_G2H(c->retlength));
}

#endif

struct qemu_NtSetLdtEntries
{
    struct qemu_syscall super;
    uint64_t selector1;
    uint64_t entry1_low;
    uint64_t entry1_high;
    uint64_t selector2;
    uint64_t entry2_low;
    uint64_t entry2_high;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetLdtEntries(ULONG selector1, ULONG entry1_low, ULONG entry1_high, ULONG selector2, ULONG entry2_low, ULONG entry2_high)
{
    struct qemu_NtSetLdtEntries call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETLDTENTRIES);
    call.selector1 = (ULONG_PTR)selector1;
    call.entry1_low = (ULONG_PTR)entry1_low;
    call.entry1_high = (ULONG_PTR)entry1_high;
    call.selector2 = (ULONG_PTR)selector2;
    call.entry2_low = (ULONG_PTR)entry2_low;
    call.entry2_high = (ULONG_PTR)entry2_high;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetLdtEntries(struct qemu_syscall *call)
{
    struct qemu_NtSetLdtEntries *c = (struct qemu_NtSetLdtEntries *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetLdtEntries(c->selector1, c->entry1_low, c->entry1_high, c->selector2, c->entry2_low, c->entry2_high);
}

#endif

struct qemu_RtlIsProcessorFeaturePresent
{
    struct qemu_syscall super;
    uint64_t feature;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOLEAN WINAPI RtlIsProcessorFeaturePresent(UINT feature)
{
    struct qemu_RtlIsProcessorFeaturePresent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RTLISPROCESSORFEATUREPRESENT);
    call.feature = feature;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_RtlIsProcessorFeaturePresent(struct qemu_syscall *call)
{
    struct qemu_RtlIsProcessorFeaturePresent *c = (struct qemu_RtlIsProcessorFeaturePresent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = RtlIsProcessorFeaturePresent(c->feature);
}

#endif

struct qemu_NtSetPowerRequest
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetPowerRequest(HANDLE handle, POWER_REQUEST_TYPE type)
{
    struct qemu_NtSetPowerRequest call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETPOWERREQUEST);
    call.handle = (ULONG_PTR)handle;
    call.type = type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetPowerRequest(struct qemu_syscall *call)
{
    struct qemu_NtSetPowerRequest *c = (struct qemu_NtSetPowerRequest *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetPowerRequest(QEMU_G2H(c->handle), c->type);
}

#endif

struct qemu_NtClearPowerRequest
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtClearPowerRequest(HANDLE handle, POWER_REQUEST_TYPE type)
{
    struct qemu_NtClearPowerRequest call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCLEARPOWERREQUEST);
    call.handle = (ULONG_PTR)handle;
    call.type = type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtClearPowerRequest(struct qemu_syscall *call)
{
    struct qemu_NtClearPowerRequest *c = (struct qemu_NtClearPowerRequest *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtClearPowerRequest(QEMU_G2H(c->handle), c->type);
}

#endif

struct qemu_NtCreatePowerRequest
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtCreatePowerRequest(HANDLE *handle, COUNTED_REASON_CONTEXT *context)
{
    struct qemu_NtCreatePowerRequest call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTCREATEPOWERREQUEST);
    call.handle = (ULONG_PTR)handle;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtCreatePowerRequest(struct qemu_syscall *call)
{
    struct qemu_NtCreatePowerRequest *c = (struct qemu_NtCreatePowerRequest *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtCreatePowerRequest(QEMU_G2H(c->handle), QEMU_G2H(c->context));
}

#endif

struct qemu_NtSetThreadExecutionState
{
    struct qemu_syscall super;
    uint64_t new_state;
    uint64_t old_state;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI NtSetThreadExecutionState(EXECUTION_STATE new_state, EXECUTION_STATE *old_state)
{
    struct qemu_NtSetThreadExecutionState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_NTSETTHREADEXECUTIONSTATE);
    call.new_state = new_state;
    call.old_state = (ULONG_PTR)old_state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_NtSetThreadExecutionState(struct qemu_syscall *call)
{
    struct qemu_NtSetThreadExecutionState *c = (struct qemu_NtSetThreadExecutionState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = NtSetThreadExecutionState(c->new_state, QEMU_G2H(c->old_state));
}

#endif
