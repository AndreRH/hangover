/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
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

#define COBJMACROS
#define INITGUID

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_bcrypt.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_bcrypt);
#endif

struct qemu_BCryptAddContextFunction
{
    struct qemu_syscall super;
    uint64_t table;
    uint64_t context;
    uint64_t iface;
    uint64_t function;
    uint64_t pos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptAddContextFunction(ULONG table, LPCWSTR context, ULONG iface, LPCWSTR function,
        ULONG pos)
{
    struct qemu_BCryptAddContextFunction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTADDCONTEXTFUNCTION);
    call.table = table;
    call.context = (ULONG_PTR)context;
    call.iface = iface;
    call.function = (ULONG_PTR)function;
    call.pos = pos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI BCryptAddContextFunction(ULONG table, LPCWSTR context, ULONG iface, LPCWSTR function, ULONG pos);
static void qemu_BCryptAddContextFunction(struct qemu_syscall *call)
{
    struct qemu_BCryptAddContextFunction *c = (struct qemu_BCryptAddContextFunction *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BCryptAddContextFunction(c->table, QEMU_G2H(c->context), c->iface, QEMU_G2H(c->function), c->pos);
}

#endif

struct qemu_BCryptAddContextFunctionProvider
{
    struct qemu_syscall super;
    uint64_t table;
    uint64_t context;
    uint64_t iface;
    uint64_t function;
    uint64_t provider;
    uint64_t pos;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptAddContextFunctionProvider(ULONG table, LPCWSTR context, ULONG iface,
        LPCWSTR function, LPCWSTR provider, ULONG pos)
{
    struct qemu_BCryptAddContextFunctionProvider call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTADDCONTEXTFUNCTIONPROVIDER);
    call.table = table;
    call.context = (ULONG_PTR)context;
    call.iface = iface;
    call.function = (ULONG_PTR)function;
    call.provider = (ULONG_PTR)provider;
    call.pos = pos;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI BCryptAddContextFunctionProvider(ULONG table, LPCWSTR context, ULONG iface, LPCWSTR function,
        LPCWSTR provider, ULONG pos);
static void qemu_BCryptAddContextFunctionProvider(struct qemu_syscall *call)
{
    struct qemu_BCryptAddContextFunctionProvider *c = (struct qemu_BCryptAddContextFunctionProvider *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BCryptAddContextFunctionProvider(c->table, QEMU_G2H(c->context), c->iface, QEMU_G2H(c->function),
            QEMU_G2H(c->provider), c->pos);
}

#endif

struct qemu_BCryptRemoveContextFunction
{
    struct qemu_syscall super;
    uint64_t table;
    uint64_t context;
    uint64_t iface;
    uint64_t function;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptRemoveContextFunction(ULONG table, LPCWSTR context, ULONG iface, LPCWSTR function)
{
    struct qemu_BCryptRemoveContextFunction call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTREMOVECONTEXTFUNCTION);
    call.table = table;
    call.context = (ULONG_PTR)context;
    call.iface = iface;
    call.function = (ULONG_PTR)function;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI BCryptRemoveContextFunction(ULONG table, LPCWSTR context, ULONG iface, LPCWSTR function);
static void qemu_BCryptRemoveContextFunction(struct qemu_syscall *call)
{
    struct qemu_BCryptRemoveContextFunction *c = (struct qemu_BCryptRemoveContextFunction *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BCryptRemoveContextFunction(c->table, QEMU_G2H(c->context), c->iface, QEMU_G2H(c->function));
}

#endif

struct qemu_BCryptRemoveContextFunctionProvider
{
    struct qemu_syscall super;
    uint64_t table;
    uint64_t context;
    uint64_t iface;
    uint64_t function;
    uint64_t provider;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptRemoveContextFunctionProvider(ULONG table, LPCWSTR context, ULONG iface,
        LPCWSTR function, LPCWSTR provider)
{
    struct qemu_BCryptRemoveContextFunctionProvider call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTREMOVECONTEXTFUNCTIONPROVIDER);
    call.table = table;
    call.context = (ULONG_PTR)context;
    call.iface = iface;
    call.function = (ULONG_PTR)function;
    call.provider = (ULONG_PTR)provider;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI BCryptRemoveContextFunctionProvider(ULONG table, LPCWSTR context, ULONG iface,
        LPCWSTR function, LPCWSTR provider);
static void qemu_BCryptRemoveContextFunctionProvider(struct qemu_syscall *call)
{
    struct qemu_BCryptRemoveContextFunctionProvider *c = (struct qemu_BCryptRemoveContextFunctionProvider *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BCryptRemoveContextFunctionProvider(c->table, QEMU_G2H(c->context), c->iface,
            QEMU_G2H(c->function), QEMU_G2H(c->provider));
}

#endif

struct qemu_BCryptRegisterProvider
{
    struct qemu_syscall super;
    uint64_t provider;
    uint64_t flags;
    uint64_t reg;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptRegisterProvider(LPCWSTR provider, ULONG flags, PCRYPT_PROVIDER_REG reg)
{
    struct qemu_BCryptRegisterProvider call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTREGISTERPROVIDER);
    call.provider = (ULONG_PTR)provider;
    call.flags = flags;
    call.reg = (ULONG_PTR)reg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI BCryptRegisterProvider(LPCWSTR provider, ULONG flags, PCRYPT_PROVIDER_REG reg);
static void qemu_BCryptRegisterProvider(struct qemu_syscall *call)
{
    struct qemu_BCryptRegisterProvider *c = (struct qemu_BCryptRegisterProvider *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BCryptRegisterProvider(QEMU_G2H(c->provider), c->flags, QEMU_G2H(c->reg));
}

#endif

struct qemu_BCryptUnregisterProvider
{
    struct qemu_syscall super;
    uint64_t provider;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptUnregisterProvider(LPCWSTR provider)
{
    struct qemu_BCryptUnregisterProvider call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTUNREGISTERPROVIDER);
    call.provider = (ULONG_PTR)provider;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern WINBASEAPI NTSTATUS WINAPI BCryptUnregisterProvider(LPCWSTR provider);
static void qemu_BCryptUnregisterProvider(struct qemu_syscall *call)
{
    struct qemu_BCryptUnregisterProvider *c = (struct qemu_BCryptUnregisterProvider *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BCryptUnregisterProvider(QEMU_G2H(c->provider));
}

#endif

struct qemu_BCryptEnumAlgorithms
{
    struct qemu_syscall super;
    uint64_t dwAlgOperations;
    uint64_t pAlgCount;
    uint64_t ppAlgList;
    uint64_t dwFlags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptEnumAlgorithms(ULONG dwAlgOperations, ULONG *pAlgCount,
        BCRYPT_ALGORITHM_IDENTIFIER **ppAlgList, ULONG dwFlags)
{
    struct qemu_BCryptEnumAlgorithms call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTENUMALGORITHMS);
    call.dwAlgOperations = dwAlgOperations;
    call.pAlgCount = (ULONG_PTR)pAlgCount;
    call.ppAlgList = (ULONG_PTR)ppAlgList;
    call.dwFlags = dwFlags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptEnumAlgorithms(struct qemu_syscall *call)
{
    struct qemu_BCryptEnumAlgorithms *c = (struct qemu_BCryptEnumAlgorithms *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BCryptEnumAlgorithms(c->dwAlgOperations, QEMU_G2H(c->pAlgCount), QEMU_G2H(c->ppAlgList),
            c->dwFlags);
}

#endif

struct qemu_BCryptGenRandom
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t buffer;
    uint64_t count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptGenRandom(BCRYPT_ALG_HANDLE handle, UCHAR *buffer, ULONG count, ULONG flags)
{
    struct qemu_BCryptGenRandom call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTGENRANDOM);
    call.handle = (ULONG_PTR)handle;
    call.buffer = (ULONG_PTR)buffer;
    call.count = count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptGenRandom(struct qemu_syscall *call)
{
    struct qemu_BCryptGenRandom *c = (struct qemu_BCryptGenRandom *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptGenRandom(QEMU_G2H(c->handle), QEMU_G2H(c->buffer), c->count, c->flags);
}

#endif

struct qemu_BCryptOpenAlgorithmProvider
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t id;
    uint64_t implementation;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptOpenAlgorithmProvider(BCRYPT_ALG_HANDLE *handle, LPCWSTR id,
        LPCWSTR implementation, DWORD flags)
{
    struct qemu_BCryptOpenAlgorithmProvider call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTOPENALGORITHMPROVIDER);
    call.handle = (ULONG_PTR)handle;
    call.id = (ULONG_PTR)id;
    call.implementation = (ULONG_PTR)implementation;
    call.flags = flags;

    qemu_syscall(&call.super);
    if (call.super.iret == STATUS_SUCCESS)
        *handle = (BCRYPT_ALG_HANDLE)(ULONG_PTR)call.handle;

    return call.super.iret;
}

#else

static void qemu_BCryptOpenAlgorithmProvider(struct qemu_syscall *call)
{
    struct qemu_BCryptOpenAlgorithmProvider *c = (struct qemu_BCryptOpenAlgorithmProvider *)call;
    BCRYPT_ALG_HANDLE handle;

    WINE_TRACE("\n");
    c->super.iret = BCryptOpenAlgorithmProvider(c->handle ? &handle : NULL, QEMU_G2H(c->id),
            QEMU_G2H(c->implementation), c->flags);
    c->handle = QEMU_H2G(handle);
}

#endif

struct qemu_BCryptCloseAlgorithmProvider
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptCloseAlgorithmProvider(BCRYPT_ALG_HANDLE handle, DWORD flags)
{
    struct qemu_BCryptCloseAlgorithmProvider call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTCLOSEALGORITHMPROVIDER);
    call.handle = (ULONG_PTR)handle;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptCloseAlgorithmProvider(struct qemu_syscall *call)
{
    struct qemu_BCryptCloseAlgorithmProvider *c = (struct qemu_BCryptCloseAlgorithmProvider *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptCloseAlgorithmProvider(QEMU_G2H(c->handle), c->flags);
}

#endif

struct qemu_BCryptGetFipsAlgorithmMode
{
    struct qemu_syscall super;
    uint64_t enabled;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptGetFipsAlgorithmMode(BOOLEAN *enabled)
{
    struct qemu_BCryptGetFipsAlgorithmMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTGETFIPSALGORITHMMODE);
    call.enabled = (ULONG_PTR)enabled;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptGetFipsAlgorithmMode(struct qemu_syscall *call)
{
    struct qemu_BCryptGetFipsAlgorithmMode *c = (struct qemu_BCryptGetFipsAlgorithmMode *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptGetFipsAlgorithmMode(QEMU_G2H(c->enabled));
}

#endif

struct qemu_BCryptGetProperty
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t prop;
    uint64_t buffer;
    uint64_t count;
    uint64_t res;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptGetProperty(BCRYPT_HANDLE handle, LPCWSTR prop, UCHAR *buffer,
        ULONG count, ULONG *res, ULONG flags)
{
    struct qemu_BCryptGetProperty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTGETPROPERTY);
    call.handle = (ULONG_PTR)handle;
    call.prop = (ULONG_PTR)prop;
    call.buffer = (ULONG_PTR)buffer;
    call.count = count;
    call.res = (ULONG_PTR)res;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptGetProperty(struct qemu_syscall *call)
{
    struct qemu_BCryptGetProperty *c = (struct qemu_BCryptGetProperty *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptGetProperty(QEMU_G2H(c->handle), QEMU_G2H(c->prop), QEMU_G2H(c->buffer),
            c->count, QEMU_G2H(c->res), c->flags);
}

#endif

struct qemu_BCryptCreateHash
{
    struct qemu_syscall super;
    uint64_t algorithm;
    uint64_t handle;
    uint64_t object;
    uint64_t objectlen;
    uint64_t secret;
    uint64_t secretlen;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptCreateHash(BCRYPT_ALG_HANDLE algorithm, BCRYPT_HASH_HANDLE *handle,
        UCHAR *object, ULONG objectlen, UCHAR *secret, ULONG secretlen, ULONG flags)
{
    struct qemu_BCryptCreateHash call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTCREATEHASH);
    call.algorithm = (ULONG_PTR)algorithm;
    call.object = (ULONG_PTR)object;
    call.objectlen = objectlen;
    call.secret = (ULONG_PTR)secret;
    call.secretlen = secretlen;
    call.flags = flags;

    qemu_syscall(&call.super);
    if (call.super.iret == STATUS_SUCCESS)
        *handle = (BCRYPT_HASH_HANDLE)(ULONG_PTR)call.handle;
    

    return call.super.iret;
}

#else

static void qemu_BCryptCreateHash(struct qemu_syscall *call)
{
    struct qemu_BCryptCreateHash *c = (struct qemu_BCryptCreateHash *)call;
    BCRYPT_HASH_HANDLE handle;

    WINE_TRACE("\n");
    c->super.iret = BCryptCreateHash(QEMU_G2H(c->algorithm), &handle,
            QEMU_G2H(c->object), c->objectlen, QEMU_G2H(c->secret), c->secretlen, c->flags);
    c->handle = QEMU_H2G(handle);
}

#endif

struct qemu_BCryptDuplicateHash
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t handle_copy;
    uint64_t object;
    uint64_t objectlen;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptDuplicateHash(BCRYPT_HASH_HANDLE handle, BCRYPT_HASH_HANDLE *handle_copy,
        UCHAR *object, ULONG objectlen, ULONG flags)
{
    struct qemu_BCryptDuplicateHash call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTDUPLICATEHASH);
    call.handle = (ULONG_PTR)handle;
    call.handle_copy = (ULONG_PTR)handle_copy;
    call.object = (ULONG_PTR)object;
    call.objectlen = objectlen;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptDuplicateHash(struct qemu_syscall *call)
{
    struct qemu_BCryptDuplicateHash *c = (struct qemu_BCryptDuplicateHash *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = BCryptDuplicateHash(QEMU_G2H(c->handle), QEMU_G2H(c->handle_copy), QEMU_G2H(c->object),
            c->objectlen, c->flags);
}

#endif

struct qemu_BCryptDestroyHash
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptDestroyHash(BCRYPT_HASH_HANDLE handle)
{
    struct qemu_BCryptDestroyHash call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTDESTROYHASH);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptDestroyHash(struct qemu_syscall *call)
{
    struct qemu_BCryptDestroyHash *c = (struct qemu_BCryptDestroyHash *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptDestroyHash(QEMU_G2H(c->handle));
}

#endif

struct qemu_BCryptHashData
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t input;
    uint64_t size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptHashData(BCRYPT_HASH_HANDLE handle, UCHAR *input, ULONG size, ULONG flags)
{
    struct qemu_BCryptHashData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTHASHDATA);
    call.handle = (ULONG_PTR)handle;
    call.input = (ULONG_PTR)input;
    call.size = size;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptHashData(struct qemu_syscall *call)
{
    struct qemu_BCryptHashData *c = (struct qemu_BCryptHashData *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptHashData(QEMU_G2H(c->handle), QEMU_G2H(c->input), c->size, c->flags);
}

#endif

struct qemu_BCryptFinishHash
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t output;
    uint64_t size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptFinishHash(BCRYPT_HASH_HANDLE handle, UCHAR *output, ULONG size, ULONG flags)
{
    struct qemu_BCryptFinishHash call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTFINISHHASH);
    call.handle = (ULONG_PTR)handle;
    call.output = (ULONG_PTR)output;
    call.size = size;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptFinishHash(struct qemu_syscall *call)
{
    struct qemu_BCryptFinishHash *c = (struct qemu_BCryptFinishHash *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptFinishHash(QEMU_G2H(c->handle), QEMU_G2H(c->output), c->size, c->flags);
}

#endif

struct qemu_BCryptHash
{
    struct qemu_syscall super;
    uint64_t algorithm;
    uint64_t secret;
    uint64_t secretlen;
    uint64_t input;
    uint64_t inputlen;
    uint64_t output;
    uint64_t outputlen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptHash(BCRYPT_ALG_HANDLE algorithm, UCHAR *secret, ULONG secretlen, UCHAR *input,
        ULONG inputlen, UCHAR *output, ULONG outputlen)
{
    struct qemu_BCryptHash call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTHASH);
    call.algorithm = (ULONG_PTR)algorithm;
    call.secret = (ULONG_PTR)secret;
    call.secretlen = secretlen;
    call.input = (ULONG_PTR)input;
    call.inputlen = inputlen;
    call.output = (ULONG_PTR)output;
    call.outputlen = outputlen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptHash(struct qemu_syscall *call)
{
    struct qemu_BCryptHash *c = (struct qemu_BCryptHash *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptHash(QEMU_G2H(c->algorithm), QEMU_G2H(c->secret), c->secretlen, QEMU_G2H(c->input),
            c->inputlen, QEMU_G2H(c->output), c->outputlen);
}

#endif

struct qemu_BCryptGenerateSymmetricKey
{
    struct qemu_syscall super;
    uint64_t algorithm;
    uint64_t handle;
    uint64_t object;
    uint64_t object_len;
    uint64_t secret;
    uint64_t secret_len;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptGenerateSymmetricKey(BCRYPT_ALG_HANDLE algorithm, BCRYPT_KEY_HANDLE *handle,
        UCHAR *object, ULONG object_len, UCHAR *secret, ULONG secret_len, ULONG flags)
{
    struct qemu_BCryptGenerateSymmetricKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTGENERATESYMMETRICKEY);
    call.algorithm = (ULONG_PTR)algorithm;
    call.object = (ULONG_PTR)object;
    call.object_len = object_len;
    call.secret = (ULONG_PTR)secret;
    call.secret_len = secret_len;
    call.flags = flags;

    qemu_syscall(&call.super);
    if (call.super.iret == ERROR_SUCCESS)
        *handle = (BCRYPT_KEY_HANDLE)(ULONG_PTR)call.handle;

    return call.super.iret;
}

#else

static void qemu_BCryptGenerateSymmetricKey(struct qemu_syscall *call)
{
    struct qemu_BCryptGenerateSymmetricKey *c = (struct qemu_BCryptGenerateSymmetricKey *)call;
    BCRYPT_KEY_HANDLE handle;

    WINE_TRACE("\n");
    c->super.iret = BCryptGenerateSymmetricKey(QEMU_G2H(c->algorithm), &handle, QEMU_G2H(c->object),
            c->object_len, QEMU_G2H(c->secret), c->secret_len, c->flags);
    c->handle = QEMU_H2G(handle);
}

#endif

struct qemu_BCryptImportKey
{
    struct qemu_syscall super;
    uint64_t algorithm;
    uint64_t decrypt_key;
    uint64_t type;
    uint64_t key;
    uint64_t object;
    uint64_t object_len;
    uint64_t input;
    uint64_t input_len;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptImportKey(BCRYPT_ALG_HANDLE algorithm, BCRYPT_KEY_HANDLE decrypt_key,
        LPCWSTR type, BCRYPT_KEY_HANDLE *key, PUCHAR object, ULONG object_len, PUCHAR input, ULONG input_len,
        ULONG flags)
{
    struct qemu_BCryptImportKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTIMPORTKEY);
    call.algorithm = (ULONG_PTR)algorithm;
    call.decrypt_key = (ULONG_PTR)decrypt_key;
    call.type = (ULONG_PTR)type;
    call.key = (ULONG_PTR)key;
    call.object = (ULONG_PTR)object;
    call.object_len = object_len;
    call.input = (ULONG_PTR)input;
    call.input_len = input_len;
    call.flags = flags;

    qemu_syscall(&call.super);
    if (call.super.iret == ERROR_SUCCESS)
        *key = (BCRYPT_KEY_HANDLE)(ULONG_PTR)call.key;

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI BCryptImportKey(BCRYPT_ALG_HANDLE algorithm, BCRYPT_KEY_HANDLE decrypt_key, LPCWSTR type,
        BCRYPT_KEY_HANDLE *key, PUCHAR object, ULONG object_len, PUCHAR input, ULONG input_len, ULONG flags);
static void qemu_BCryptImportKey(struct qemu_syscall *call)
{
    struct qemu_BCryptImportKey *c = (struct qemu_BCryptImportKey *)call;
    BCRYPT_KEY_HANDLE key;

    WINE_TRACE("\n");
    c->super.iret = BCryptImportKey(QEMU_G2H(c->algorithm), QEMU_G2H(c->decrypt_key), QEMU_G2H(c->type),
            c->key ? &key : NULL, QEMU_G2H(c->object), c->object_len, QEMU_G2H(c->input), c->input_len, c->flags);
    c->key = QEMU_H2G(key);
}

#endif

struct qemu_BCryptExportKey
{
    struct qemu_syscall super;
    uint64_t export_key;
    uint64_t encrypt_key;
    uint64_t type;
    uint64_t output;
    uint64_t output_len;
    uint64_t size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptExportKey(BCRYPT_KEY_HANDLE export_key, BCRYPT_KEY_HANDLE encrypt_key,
        LPCWSTR type, PUCHAR output, ULONG output_len, ULONG *size, ULONG flags)
{
    struct qemu_BCryptExportKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTEXPORTKEY);
    call.export_key = (ULONG_PTR)export_key;
    call.encrypt_key = (ULONG_PTR)encrypt_key;
    call.type = (ULONG_PTR)type;
    call.output = (ULONG_PTR)output;
    call.output_len = output_len;
    call.size = (ULONG_PTR)size;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI BCryptExportKey(BCRYPT_KEY_HANDLE export_key, BCRYPT_KEY_HANDLE encrypt_key, LPCWSTR type,
        PUCHAR output, ULONG output_len, ULONG *size, ULONG flags);
static void qemu_BCryptExportKey(struct qemu_syscall *call)
{
    struct qemu_BCryptExportKey *c = (struct qemu_BCryptExportKey *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptExportKey(QEMU_G2H(c->export_key), QEMU_G2H(c->encrypt_key), QEMU_G2H(c->type),
            QEMU_G2H(c->output), c->output_len, QEMU_G2H(c->size), c->flags);
}

#endif

struct qemu_BCryptDuplicateKey
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t handle_copy;
    uint64_t object;
    uint64_t object_len;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptDuplicateKey(BCRYPT_KEY_HANDLE handle, BCRYPT_KEY_HANDLE *handle_copy,
        UCHAR *object, ULONG object_len, ULONG flags)
{
    struct qemu_BCryptDuplicateKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTDUPLICATEKEY);
    call.handle = (ULONG_PTR)handle;
    call.handle_copy = (ULONG_PTR)handle_copy;
    call.object = (ULONG_PTR)object;
    call.object_len = object_len;
    call.flags = flags;

    qemu_syscall(&call.super);
    if (call.super.iret == ERROR_SUCCESS)
        *handle_copy = (BCRYPT_KEY_HANDLE)(ULONG_PTR)call.handle_copy;

    return call.super.iret;
}

#else

extern NTSTATUS WINAPI BCryptDuplicateKey(BCRYPT_KEY_HANDLE handle, BCRYPT_KEY_HANDLE *handle_copy, UCHAR *object,
        ULONG object_len, ULONG flags);
static void qemu_BCryptDuplicateKey(struct qemu_syscall *call)
{
    struct qemu_BCryptDuplicateKey *c = (struct qemu_BCryptDuplicateKey *)call;
    BCRYPT_KEY_HANDLE handle_copy;

    WINE_TRACE("\n");
    c->super.iret = BCryptDuplicateKey(QEMU_G2H(c->handle), c->handle_copy ? &handle_copy : NULL,
            QEMU_G2H(c->object), c->object_len, c->flags);
    c->handle_copy = QEMU_H2G(handle_copy);
}

#endif

struct qemu_BCryptImportKeyPair
{
    struct qemu_syscall super;
    uint64_t algorithm;
    uint64_t decrypt_key;
    uint64_t type;
    uint64_t ret_key;
    uint64_t input;
    uint64_t input_len;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptImportKeyPair(BCRYPT_ALG_HANDLE algorithm, BCRYPT_KEY_HANDLE decrypt_key,
        const WCHAR *type, BCRYPT_KEY_HANDLE *ret_key, UCHAR *input, ULONG input_len, ULONG flags)
{
    struct qemu_BCryptImportKeyPair call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTIMPORTKEYPAIR);
    call.algorithm = (ULONG_PTR)algorithm;
    call.decrypt_key = (ULONG_PTR)decrypt_key;
    call.type = (ULONG_PTR)type;
    call.ret_key = (ULONG_PTR)ret_key;
    call.input = (ULONG_PTR)input;
    call.input_len = input_len;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptImportKeyPair(struct qemu_syscall *call)
{
    struct qemu_BCryptImportKeyPair *c = (struct qemu_BCryptImportKeyPair *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptImportKeyPair(QEMU_G2H(c->algorithm), QEMU_G2H(c->decrypt_key), QEMU_G2H(c->type),
            QEMU_G2H(c->ret_key), QEMU_G2H(c->input), c->input_len, c->flags);
}

#endif

struct qemu_BCryptVerifySignature
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t padding;
    uint64_t hash;
    uint64_t hash_len;
    uint64_t signature;
    uint64_t signature_len;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptVerifySignature(BCRYPT_KEY_HANDLE handle, void *padding, UCHAR *hash,
        ULONG hash_len, UCHAR *signature, ULONG signature_len, ULONG flags)
{
    struct qemu_BCryptVerifySignature call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTVERIFYSIGNATURE);
    call.handle = (ULONG_PTR)handle;
    call.padding = (ULONG_PTR)padding;
    call.hash = (ULONG_PTR)hash;
    call.hash_len = hash_len;
    call.signature = (ULONG_PTR)signature;
    call.signature_len = signature_len;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptVerifySignature(struct qemu_syscall *call)
{
    struct qemu_BCryptVerifySignature *c = (struct qemu_BCryptVerifySignature *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptVerifySignature(QEMU_G2H(c->handle), QEMU_G2H(c->padding), QEMU_G2H(c->hash),
            c->hash_len, QEMU_G2H(c->signature), c->signature_len, c->flags);
}

#endif

struct qemu_BCryptDestroyKey
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptDestroyKey(BCRYPT_KEY_HANDLE handle)
{
    struct qemu_BCryptDestroyKey call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTDESTROYKEY);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptDestroyKey(struct qemu_syscall *call)
{
    struct qemu_BCryptDestroyKey *c = (struct qemu_BCryptDestroyKey *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptDestroyKey(QEMU_G2H(c->handle));
}

#endif

struct qemu_BCryptEncrypt
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t input;
    uint64_t input_len;
    uint64_t padding;
    uint64_t iv;
    uint64_t iv_len;
    uint64_t output;
    uint64_t output_len;
    uint64_t ret_len;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptEncrypt(BCRYPT_KEY_HANDLE handle, UCHAR *input, ULONG input_len,
        void *padding, UCHAR *iv, ULONG iv_len, UCHAR *output, ULONG output_len, ULONG *ret_len, ULONG flags)
{
    struct qemu_BCryptEncrypt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTENCRYPT);
    call.handle = (ULONG_PTR)handle;
    call.input = (ULONG_PTR)input;
    call.input_len = input_len;
    call.padding = (ULONG_PTR)padding;
    call.iv = (ULONG_PTR)iv;
    call.iv_len = iv_len;
    call.output = (ULONG_PTR)output;
    call.output_len = output_len;
    call.ret_len = (ULONG_PTR)ret_len;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptEncrypt(struct qemu_syscall *call)
{
    struct qemu_BCryptEncrypt *c = (struct qemu_BCryptEncrypt *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptEncrypt(QEMU_G2H(c->handle), QEMU_G2H(c->input), c->input_len, QEMU_G2H(c->padding),
            QEMU_G2H(c->iv), c->iv_len, QEMU_G2H(c->output), c->output_len, QEMU_G2H(c->ret_len), c->flags);
}

#endif

struct qemu_BCryptDecrypt
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t input;
    uint64_t input_len;
    uint64_t padding;
    uint64_t iv;
    uint64_t iv_len;
    uint64_t output;
    uint64_t output_len;
    uint64_t ret_len;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptDecrypt(BCRYPT_KEY_HANDLE handle, UCHAR *input, ULONG input_len,
        void *padding, UCHAR *iv, ULONG iv_len, UCHAR *output, ULONG output_len, ULONG *ret_len, ULONG flags)
{
    struct qemu_BCryptDecrypt call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTDECRYPT);
    call.handle = (ULONG_PTR)handle;
    call.input = (ULONG_PTR)input;
    call.input_len = input_len;
    call.padding = (ULONG_PTR)padding;
    call.iv = (ULONG_PTR)iv;
    call.iv_len = iv_len;
    call.output = (ULONG_PTR)output;
    call.output_len = output_len;
    call.ret_len = (ULONG_PTR)ret_len;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptDecrypt(struct qemu_syscall *call)
{
    struct qemu_BCryptDecrypt *c = (struct qemu_BCryptDecrypt *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptDecrypt(QEMU_G2H(c->handle), QEMU_G2H(c->input), c->input_len, QEMU_G2H(c->padding),
            QEMU_G2H(c->iv), c->iv_len, QEMU_G2H(c->output), c->output_len, QEMU_G2H(c->ret_len), c->flags);
}

#endif

struct qemu_BCryptSetProperty
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t prop;
    uint64_t value;
    uint64_t size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI NTSTATUS WINAPI BCryptSetProperty(BCRYPT_HANDLE handle, const WCHAR *prop, UCHAR *value,
        ULONG size, ULONG flags)
{
    struct qemu_BCryptSetProperty call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BCRYPTSETPROPERTY);
    call.handle = (ULONG_PTR)handle;
    call.prop = (ULONG_PTR)prop;
    call.value = (ULONG_PTR)value;
    call.size = size;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_BCryptSetProperty(struct qemu_syscall *call)
{
    struct qemu_BCryptSetProperty *c = (struct qemu_BCryptSetProperty *)call;
    WINE_TRACE("\n");
    c->super.iret = BCryptSetProperty(QEMU_G2H(QEMU_G2H(c->handle)), QEMU_G2H(c->prop),
            QEMU_G2H(c->value), c->size, c->flags);
}

#endif
#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{

    qemu_BCryptAddContextFunction,
    qemu_BCryptAddContextFunctionProvider,
    qemu_BCryptCloseAlgorithmProvider,
    qemu_BCryptCreateHash,
    qemu_BCryptDecrypt,
    qemu_BCryptDestroyHash,
    qemu_BCryptDestroyKey,
    qemu_BCryptDuplicateHash,
    qemu_BCryptDuplicateKey,
    qemu_BCryptEncrypt,
    qemu_BCryptEnumAlgorithms,
    qemu_BCryptExportKey,
    qemu_BCryptFinishHash,
    qemu_BCryptGenerateSymmetricKey,
    qemu_BCryptGenRandom,
    qemu_BCryptGetFipsAlgorithmMode,
    qemu_BCryptGetProperty,
    qemu_BCryptHash,
    qemu_BCryptHashData,
    qemu_BCryptImportKey,
    qemu_BCryptImportKeyPair,
    qemu_BCryptOpenAlgorithmProvider,
    qemu_BCryptRegisterProvider,
    qemu_BCryptRemoveContextFunction,
    qemu_BCryptRemoveContextFunctionProvider,
    qemu_BCryptSetProperty,
    qemu_BCryptUnregisterProvider,
    qemu_BCryptVerifySignature,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side bcrypt wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
