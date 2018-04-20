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
// #include <wct.h>
// #include <wmistr.h>
// #include <evntrace.h>
// #include <evntprov.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif

struct qemu_SystemFunction006
{
    struct qemu_syscall super;
    uint64_t password;
    uint64_t hash;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction006(LPCSTR password, LPSTR hash)
{
    struct qemu_SystemFunction006 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION006);
    call.password = (ULONG_PTR)password;
    call.hash = (ULONG_PTR)hash;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI SystemFunction006( LPCSTR password, LPSTR hash );
void qemu_SystemFunction006(struct qemu_syscall *call)
{
    struct qemu_SystemFunction006 *c = (struct qemu_SystemFunction006 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction006(QEMU_G2H(c->password), QEMU_G2H(c->hash));
}

#endif

struct qemu_SystemFunction008
{
    struct qemu_syscall super;
    uint64_t challenge;
    uint64_t hash;
    uint64_t response;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction008(const BYTE *challenge, const BYTE *hash, LPBYTE response)
{
    struct qemu_SystemFunction008 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION008);
    call.challenge = (ULONG_PTR)challenge;
    call.hash = (ULONG_PTR)hash;
    call.response = (ULONG_PTR)response;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI SystemFunction008(const BYTE *challenge, const BYTE *hash, LPBYTE response);
void qemu_SystemFunction008(struct qemu_syscall *call)
{
    struct qemu_SystemFunction008 *c = (struct qemu_SystemFunction008 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction008(QEMU_G2H(c->challenge), QEMU_G2H(c->hash), QEMU_G2H(c->response));
}

#endif

struct qemu_SystemFunction009
{
    struct qemu_syscall super;
    uint64_t challenge;
    uint64_t hash;
    uint64_t response;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction009(const BYTE *challenge, const BYTE *hash, LPBYTE response)
{
    struct qemu_SystemFunction009 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION009);
    call.challenge = (ULONG_PTR)challenge;
    call.hash = (ULONG_PTR)hash;
    call.response = (ULONG_PTR)response;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

NTSTATUS WINAPI SystemFunction009(const BYTE *challenge, const BYTE *hash, LPBYTE response);
void qemu_SystemFunction009(struct qemu_syscall *call)
{
    struct qemu_SystemFunction009 *c = (struct qemu_SystemFunction009 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction009(QEMU_G2H(c->challenge), QEMU_G2H(c->hash), QEMU_G2H(c->response));
}

#endif

struct qemu_SystemFunction001
{
    struct qemu_syscall super;
    uint64_t data;
    uint64_t key;
    uint64_t output;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction001(const BYTE *data, const BYTE *key, LPBYTE output)
{
    struct qemu_SystemFunction001 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION001);
    call.data = (ULONG_PTR)data;
    call.key = (ULONG_PTR)key;
    call.output = (ULONG_PTR)output;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI SystemFunction001(const BYTE *data, const BYTE *key, LPBYTE output);
void qemu_SystemFunction001(struct qemu_syscall *call)
{
    struct qemu_SystemFunction001 *c = (struct qemu_SystemFunction001 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction001(QEMU_G2H(c->data), QEMU_G2H(c->key), QEMU_G2H(c->output));
}

#endif

struct qemu_SystemFunction002
{
    struct qemu_syscall super;
    uint64_t data;
    uint64_t key;
    uint64_t output;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction002(const BYTE *data, const BYTE *key, LPBYTE output)
{
    struct qemu_SystemFunction002 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION002);
    call.data = (ULONG_PTR)data;
    call.key = (ULONG_PTR)key;
    call.output = (ULONG_PTR)output;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI SystemFunction002(const BYTE *data, const BYTE *key, LPBYTE output);
void qemu_SystemFunction002(struct qemu_syscall *call)
{
    struct qemu_SystemFunction002 *c = (struct qemu_SystemFunction002 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction002(QEMU_G2H(c->data), QEMU_G2H(c->key), QEMU_G2H(c->output));
}

#endif

struct qemu_SystemFunction003
{
    struct qemu_syscall super;
    uint64_t key;
    uint64_t output;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction003(const BYTE *key, LPBYTE output)
{
    struct qemu_SystemFunction003 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION003);
    call.key = (ULONG_PTR)key;
    call.output = (ULONG_PTR)output;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI SystemFunction003(const BYTE *key, LPBYTE output);
void qemu_SystemFunction003(struct qemu_syscall *call)
{
    struct qemu_SystemFunction003 *c = (struct qemu_SystemFunction003 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction003(QEMU_G2H(c->key), QEMU_G2H(c->output));
}

#endif

struct qemu_SystemFunction004_5
{
    struct qemu_syscall super;
    uint64_t in;
    uint64_t key;
    uint64_t out;
};

struct ustring
{
    DWORD Length;
    DWORD MaximumLength;
    unsigned char *Buffer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction004(const struct ustring *in, const struct ustring *key, struct ustring *out)
{
    struct qemu_SystemFunction004_5 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION004);
    call.in = (ULONG_PTR)in;
    call.key = (ULONG_PTR)key;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI NTSTATUS WINAPI SystemFunction005(const struct ustring *in, const struct ustring *key, struct ustring *out)
{
    struct qemu_SystemFunction004_5 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION005);
    call.in = (ULONG_PTR)in;
    call.key = (ULONG_PTR)key;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* Not a public struct, so it is here instead of the thunk headers. */
struct qemu_ustring
{
    DWORD Length;
    DWORD MaximumLength;
    qemu_ptr Buffer;
};

extern NTSTATUS WINAPI SystemFunction004(const struct ustring *in, const struct ustring *key, struct ustring *out);
extern NTSTATUS WINAPI SystemFunction005(const struct ustring *in, const struct ustring *key, struct ustring *out);
void qemu_SystemFunction004_5(struct qemu_syscall *call)
{
    struct qemu_SystemFunction004_5 *c = (struct qemu_SystemFunction004_5 *)call;
    struct ustring key_stack, *key = &key_stack;
    struct ustring out_stack, *out = &out_stack;
    struct ustring in_stack, *in = &in_stack;
    struct qemu_ustring *key32, *out32, *in32;
    WINE_TRACE("\n");

#if GUEST_BIT == HOST_BIT
    key = QEMU_G2H(c->key);
    out = QEMU_G2H(c->out);
    in = QEMU_G2H(c->in);
#else
    in32 = QEMU_G2H(c->in);
    if (in32)
    {
        in->Length = in32->Length;
        in->MaximumLength = in32->MaximumLength;
        in->Buffer = (unsigned char *)(ULONG_PTR)in32->Buffer;
    }
    else
    {
        in = NULL;
    }

    key32 = QEMU_G2H(c->key);
    if (key32)
    {
        key->Length = key32->Length;
        key->MaximumLength = key32->MaximumLength;
        key->Buffer = (unsigned char *)(ULONG_PTR)key32->Buffer;
    }
    else
    {
        key = NULL;
    }

    out32 = QEMU_G2H(c->out);
    if (out32)
    {
        out->Length = out32->Length;
        out->MaximumLength = out32->MaximumLength;
        out->Buffer = (unsigned char *)(ULONG_PTR)out32->Buffer;
    }
    else
    {
        out = NULL;
    }
#endif

    if (c->super.id == QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION004))
        c->super.iret = SystemFunction004(in, key, out);
    else
        c->super.iret = SystemFunction005(in, key, out);

#if GUEST_BIT != HOST_BIT
    if (out32)
        out32->Length = out->Length;
#endif
}

#endif

struct qemu_SystemFunction012
{
    struct qemu_syscall super;
    uint64_t in;
    uint64_t key;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction012(const BYTE *in, const BYTE *key, LPBYTE out)
{
    struct qemu_SystemFunction012 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION012);
    call.in = (ULONG_PTR)in;
    call.key = (ULONG_PTR)key;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI SystemFunction012(const BYTE *in, const BYTE *key, LPBYTE out);
void qemu_SystemFunction012(struct qemu_syscall *call)
{
    struct qemu_SystemFunction012 *c = (struct qemu_SystemFunction012 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction012(QEMU_G2H(c->in), QEMU_G2H(c->key), QEMU_G2H(c->out));
}

#endif

struct qemu_SystemFunction013
{
    struct qemu_syscall super;
    uint64_t in;
    uint64_t key;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction013(const BYTE *in, const BYTE *key, LPBYTE out)
{
    struct qemu_SystemFunction013 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION013);
    call.in = (ULONG_PTR)in;
    call.key = (ULONG_PTR)key;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI SystemFunction013(const BYTE *in, const BYTE *key, LPBYTE out);
void qemu_SystemFunction013(struct qemu_syscall *call)
{
    struct qemu_SystemFunction013 *c = (struct qemu_SystemFunction013 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction013(QEMU_G2H(c->in), QEMU_G2H(c->key), QEMU_G2H(c->out));
}

#endif

struct qemu_SystemFunction024
{
    struct qemu_syscall super;
    uint64_t in;
    uint64_t key;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction024(const BYTE *in, const BYTE *key, LPBYTE out)
{
    struct qemu_SystemFunction024 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION024);
    call.in = (ULONG_PTR)in;
    call.key = (ULONG_PTR)key;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI SystemFunction024(const BYTE *in, const BYTE *key, LPBYTE out);
void qemu_SystemFunction024(struct qemu_syscall *call)
{
    struct qemu_SystemFunction024 *c = (struct qemu_SystemFunction024 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction024(QEMU_G2H(c->in), QEMU_G2H(c->key), QEMU_G2H(c->out));
}

#endif

struct qemu_SystemFunction025
{
    struct qemu_syscall super;
    uint64_t in;
    uint64_t key;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI SystemFunction025(const BYTE *in, const BYTE *key, LPBYTE out)
{
    struct qemu_SystemFunction025 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SYSTEMFUNCTION025);
    call.in = (ULONG_PTR)in;
    call.key = (ULONG_PTR)key;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI SystemFunction025(const BYTE *in, const BYTE *key, LPBYTE out);
void qemu_SystemFunction025(struct qemu_syscall *call)
{
    struct qemu_SystemFunction025 *c = (struct qemu_SystemFunction025 *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SystemFunction025(QEMU_G2H(c->in), QEMU_G2H(c->key), QEMU_G2H(c->out));
}

#endif

