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
#include <wincred.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif


struct qemu_CredDeleteA
{
    struct qemu_syscall super;
    uint64_t TargetName;
    uint64_t Type;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredDeleteA(LPCSTR TargetName, DWORD Type, DWORD Flags)
{
    struct qemu_CredDeleteA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDDELETEA);
    call.TargetName = (ULONG_PTR)TargetName;
    call.Type = Type;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredDeleteA(struct qemu_syscall *call)
{
    struct qemu_CredDeleteA *c = (struct qemu_CredDeleteA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredDeleteA(QEMU_G2H(c->TargetName), c->Type, c->Flags);
}

#endif

struct qemu_CredDeleteW
{
    struct qemu_syscall super;
    uint64_t TargetName;
    uint64_t Type;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredDeleteW(LPCWSTR TargetName, DWORD Type, DWORD Flags)
{
    struct qemu_CredDeleteW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDDELETEW);
    call.TargetName = (ULONG_PTR)TargetName;
    call.Type = Type;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredDeleteW(struct qemu_syscall *call)
{
    struct qemu_CredDeleteW *c = (struct qemu_CredDeleteW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredDeleteW(QEMU_G2H(c->TargetName), c->Type, c->Flags);
}

#endif

struct qemu_CredEnumerateA
{
    struct qemu_syscall super;
    uint64_t Filter;
    uint64_t Flags;
    uint64_t Count;
    uint64_t Credentials;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredEnumerateA(LPCSTR Filter, DWORD Flags, DWORD *Count, PCREDENTIALA **Credentials)
{
    struct qemu_CredEnumerateA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDENUMERATEA);
    call.Filter = (ULONG_PTR)Filter;
    call.Flags = Flags;
    call.Count = (ULONG_PTR)Count;
    call.Credentials = (ULONG_PTR)Credentials;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredEnumerateA(struct qemu_syscall *call)
{
    struct qemu_CredEnumerateA *c = (struct qemu_CredEnumerateA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredEnumerateA(QEMU_G2H(c->Filter), c->Flags, QEMU_G2H(c->Count), QEMU_G2H(c->Credentials));
}

#endif

struct qemu_CredEnumerateW
{
    struct qemu_syscall super;
    uint64_t Filter;
    uint64_t Flags;
    uint64_t Count;
    uint64_t Credentials;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredEnumerateW(LPCWSTR Filter, DWORD Flags, DWORD *Count, PCREDENTIALW **Credentials)
{
    struct qemu_CredEnumerateW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDENUMERATEW);
    call.Filter = (ULONG_PTR)Filter;
    call.Flags = Flags;
    call.Count = (ULONG_PTR)Count;
    call.Credentials = (ULONG_PTR)Credentials;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredEnumerateW(struct qemu_syscall *call)
{
    struct qemu_CredEnumerateW *c = (struct qemu_CredEnumerateW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredEnumerateW(QEMU_G2H(c->Filter), c->Flags, QEMU_G2H(c->Count), QEMU_G2H(c->Credentials));
}

#endif

struct qemu_CredFree
{
    struct qemu_syscall super;
    uint64_t Buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI CredFree(PVOID Buffer)
{
    struct qemu_CredFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDFREE);
    call.Buffer = (ULONG_PTR)Buffer;

    qemu_syscall(&call.super);
}

#else

void qemu_CredFree(struct qemu_syscall *call)
{
    struct qemu_CredFree *c = (struct qemu_CredFree *)call;
    WINE_FIXME("Unverified!\n");
    CredFree(QEMU_G2H(c->Buffer));
}

#endif

struct qemu_CredReadA
{
    struct qemu_syscall super;
    uint64_t TargetName;
    uint64_t Type;
    uint64_t Flags;
    uint64_t Credential;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredReadA(LPCSTR TargetName, DWORD Type, DWORD Flags, PCREDENTIALA *Credential)
{
    struct qemu_CredReadA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDREADA);
    call.TargetName = (ULONG_PTR)TargetName;
    call.Type = Type;
    call.Flags = Flags;
    call.Credential = (ULONG_PTR)Credential;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredReadA(struct qemu_syscall *call)
{
    struct qemu_CredReadA *c = (struct qemu_CredReadA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredReadA(QEMU_G2H(c->TargetName), c->Type, c->Flags, QEMU_G2H(c->Credential));
}

#endif

struct qemu_CredReadW
{
    struct qemu_syscall super;
    uint64_t TargetName;
    uint64_t Type;
    uint64_t Flags;
    uint64_t Credential;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredReadW(LPCWSTR TargetName, DWORD Type, DWORD Flags, PCREDENTIALW *Credential)
{
    struct qemu_CredReadW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDREADW);
    call.TargetName = (ULONG_PTR)TargetName;
    call.Type = Type;
    call.Flags = Flags;
    call.Credential = (ULONG_PTR)Credential;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredReadW(struct qemu_syscall *call)
{
    struct qemu_CredReadW *c = (struct qemu_CredReadW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredReadW(QEMU_G2H(c->TargetName), c->Type, c->Flags, QEMU_G2H(c->Credential));
}

#endif

struct qemu_CredReadDomainCredentialsA
{
    struct qemu_syscall super;
    uint64_t TargetInformation;
    uint64_t Flags;
    uint64_t Size;
    uint64_t Credentials;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredReadDomainCredentialsA(PCREDENTIAL_TARGET_INFORMATIONA TargetInformation, DWORD Flags, DWORD *Size, PCREDENTIALA **Credentials)
{
    struct qemu_CredReadDomainCredentialsA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDREADDOMAINCREDENTIALSA);
    call.TargetInformation = (ULONG_PTR)TargetInformation;
    call.Flags = Flags;
    call.Size = (ULONG_PTR)Size;
    call.Credentials = (ULONG_PTR)Credentials;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredReadDomainCredentialsA(struct qemu_syscall *call)
{
    struct qemu_CredReadDomainCredentialsA *c = (struct qemu_CredReadDomainCredentialsA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredReadDomainCredentialsA(QEMU_G2H(c->TargetInformation), c->Flags, QEMU_G2H(c->Size), QEMU_G2H(c->Credentials));
}

#endif

struct qemu_CredReadDomainCredentialsW
{
    struct qemu_syscall super;
    uint64_t TargetInformation;
    uint64_t Flags;
    uint64_t Size;
    uint64_t Credentials;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredReadDomainCredentialsW(PCREDENTIAL_TARGET_INFORMATIONW TargetInformation, DWORD Flags, DWORD *Size, PCREDENTIALW **Credentials)
{
    struct qemu_CredReadDomainCredentialsW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDREADDOMAINCREDENTIALSW);
    call.TargetInformation = (ULONG_PTR)TargetInformation;
    call.Flags = Flags;
    call.Size = (ULONG_PTR)Size;
    call.Credentials = (ULONG_PTR)Credentials;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredReadDomainCredentialsW(struct qemu_syscall *call)
{
    struct qemu_CredReadDomainCredentialsW *c = (struct qemu_CredReadDomainCredentialsW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredReadDomainCredentialsW(QEMU_G2H(c->TargetInformation), c->Flags, QEMU_G2H(c->Size), QEMU_G2H(c->Credentials));
}

#endif

struct qemu_CredWriteA
{
    struct qemu_syscall super;
    uint64_t Credential;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredWriteA(PCREDENTIALA Credential, DWORD Flags)
{
    struct qemu_CredWriteA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDWRITEA);
    call.Credential = (ULONG_PTR)Credential;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredWriteA(struct qemu_syscall *call)
{
    struct qemu_CredWriteA *c = (struct qemu_CredWriteA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredWriteA(QEMU_G2H(c->Credential), c->Flags);
}

#endif

struct qemu_CredWriteW
{
    struct qemu_syscall super;
    uint64_t Credential;
    uint64_t Flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredWriteW(PCREDENTIALW Credential, DWORD Flags)
{
    struct qemu_CredWriteW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDWRITEW);
    call.Credential = (ULONG_PTR)Credential;
    call.Flags = Flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredWriteW(struct qemu_syscall *call)
{
    struct qemu_CredWriteW *c = (struct qemu_CredWriteW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredWriteW(QEMU_G2H(c->Credential), c->Flags);
}

#endif

struct qemu_CredGetSessionTypes
{
    struct qemu_syscall super;
    uint64_t persistCount;
    uint64_t persists;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINADVAPI BOOL WINAPI CredGetSessionTypes(DWORD persistCount, LPDWORD persists)
{
    struct qemu_CredGetSessionTypes call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDGETSESSIONTYPES);
    call.persistCount = persistCount;
    call.persists = (ULONG_PTR)persists;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredGetSessionTypes(struct qemu_syscall *call)
{
    struct qemu_CredGetSessionTypes *c = (struct qemu_CredGetSessionTypes *)call;
    WINE_TRACE("\n");
    c->super.iret = CredGetSessionTypes(c->persistCount, QEMU_G2H(c->persists));
}

#endif

struct qemu_CredMarshalCredentialA
{
    struct qemu_syscall super;
    uint64_t type;
    uint64_t cred;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredMarshalCredentialA(CRED_MARSHAL_TYPE type, PVOID cred, LPSTR *out)
{
    struct qemu_CredMarshalCredentialA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDMARSHALCREDENTIALA);
    call.type = type;
    call.cred = (ULONG_PTR)cred;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredMarshalCredentialA(struct qemu_syscall *call)
{
    struct qemu_CredMarshalCredentialA *c = (struct qemu_CredMarshalCredentialA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredMarshalCredentialA(c->type, QEMU_G2H(c->cred), QEMU_G2H(c->out));
}

#endif

struct qemu_CredMarshalCredentialW
{
    struct qemu_syscall super;
    uint64_t type;
    uint64_t cred;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredMarshalCredentialW(CRED_MARSHAL_TYPE type, PVOID cred, LPWSTR *out)
{
    struct qemu_CredMarshalCredentialW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDMARSHALCREDENTIALW);
    call.type = type;
    call.cred = (ULONG_PTR)cred;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredMarshalCredentialW(struct qemu_syscall *call)
{
    struct qemu_CredMarshalCredentialW *c = (struct qemu_CredMarshalCredentialW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredMarshalCredentialW(c->type, QEMU_G2H(c->cred), QEMU_G2H(c->out));
}

#endif

struct qemu_CredUnmarshalCredentialA
{
    struct qemu_syscall super;
    uint64_t cred;
    uint64_t type;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredUnmarshalCredentialA(LPCSTR cred, PCRED_MARSHAL_TYPE type, PVOID *out)
{
    struct qemu_CredUnmarshalCredentialA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDUNMARSHALCREDENTIALA);
    call.cred = (ULONG_PTR)cred;
    call.type = (ULONG_PTR)type;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredUnmarshalCredentialA(struct qemu_syscall *call)
{
    struct qemu_CredUnmarshalCredentialA *c = (struct qemu_CredUnmarshalCredentialA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredUnmarshalCredentialA(QEMU_G2H(c->cred), QEMU_G2H(c->type), QEMU_G2H(c->out));
}

#endif

struct qemu_CredUnmarshalCredentialW
{
    struct qemu_syscall super;
    uint64_t cred;
    uint64_t type;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredUnmarshalCredentialW(LPCWSTR cred, PCRED_MARSHAL_TYPE type, PVOID *out)
{
    struct qemu_CredUnmarshalCredentialW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDUNMARSHALCREDENTIALW);
    call.cred = (ULONG_PTR)cred;
    call.type = (ULONG_PTR)type;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredUnmarshalCredentialW(struct qemu_syscall *call)
{
    struct qemu_CredUnmarshalCredentialW *c = (struct qemu_CredUnmarshalCredentialW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredUnmarshalCredentialW(QEMU_G2H(c->cred), QEMU_G2H(c->type), QEMU_G2H(c->out));
}

#endif

struct qemu_CredIsMarshaledCredentialW
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredIsMarshaledCredentialW(LPCWSTR name)
{
    struct qemu_CredIsMarshaledCredentialW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDISMARSHALEDCREDENTIALW);
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredIsMarshaledCredentialW(struct qemu_syscall *call)
{
    struct qemu_CredIsMarshaledCredentialW *c = (struct qemu_CredIsMarshaledCredentialW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredIsMarshaledCredentialW(QEMU_G2H(c->name));
}

#endif

struct qemu_CredIsMarshaledCredentialA
{
    struct qemu_syscall super;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CredIsMarshaledCredentialA(LPCSTR name)
{
    struct qemu_CredIsMarshaledCredentialA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREDISMARSHALEDCREDENTIALA);
    call.name = (ULONG_PTR)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_CredIsMarshaledCredentialA(struct qemu_syscall *call)
{
    struct qemu_CredIsMarshaledCredentialA *c = (struct qemu_CredIsMarshaledCredentialA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CredIsMarshaledCredentialA(QEMU_G2H(c->name));
}

#endif

