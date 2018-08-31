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

#include <windows.h>
#include <stdio.h>
#include <i_cryptasn1tls.h>

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_crypt32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_crypt32);
#endif

typedef void * HLRUCACHE;

struct qemu_I_CryptCreateLruCache
{
    struct qemu_syscall super;
    uint64_t unknown;
    uint64_t out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI I_CryptCreateLruCache(void *unknown, HLRUCACHE *out)
{
    struct qemu_I_CryptCreateLruCache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTCREATELRUCACHE);
    call.unknown = (ULONG_PTR)unknown;
    call.out = (ULONG_PTR)out;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI I_CryptCreateLruCache(void *unknown, HLRUCACHE *out);
static void qemu_I_CryptCreateLruCache(struct qemu_syscall *call)
{
    struct qemu_I_CryptCreateLruCache *c = (struct qemu_I_CryptCreateLruCache *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptCreateLruCache(QEMU_G2H(c->unknown), QEMU_G2H(c->out));
}

#endif

struct qemu_I_CryptFindLruEntry
{
    struct qemu_syscall super;
    uint64_t unk0;
    uint64_t unk1;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI I_CryptFindLruEntry(DWORD unk0, DWORD unk1)
{
    struct qemu_I_CryptFindLruEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTFINDLRUENTRY);
    call.unk0 = unk0;
    call.unk1 = unk1;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI I_CryptFindLruEntry(DWORD unk0, DWORD unk1);
static void qemu_I_CryptFindLruEntry(struct qemu_syscall *call)
{
    struct qemu_I_CryptFindLruEntry *c = (struct qemu_I_CryptFindLruEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptFindLruEntry(c->unk0, c->unk1);
}

#endif

struct qemu_I_CryptFindLruEntryData
{
    struct qemu_syscall super;
    uint64_t unk0;
    uint64_t unk1;
    uint64_t unk2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI I_CryptFindLruEntryData(DWORD unk0, DWORD unk1, DWORD unk2)
{
    struct qemu_I_CryptFindLruEntryData call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTFINDLRUENTRYDATA);
    call.unk0 = unk0;
    call.unk1 = unk1;
    call.unk2 = unk2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI I_CryptFindLruEntryData(DWORD unk0, DWORD unk1, DWORD unk2);
static void qemu_I_CryptFindLruEntryData(struct qemu_syscall *call)
{
    struct qemu_I_CryptFindLruEntryData *c = (struct qemu_I_CryptFindLruEntryData *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptFindLruEntryData(c->unk0, c->unk1, c->unk2);
}

#endif

struct qemu_I_CryptCreateLruEntry
{
    struct qemu_syscall super;
    uint64_t h;
    uint64_t unk0;
    uint64_t unk1;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI I_CryptCreateLruEntry(HLRUCACHE h, DWORD unk0, DWORD unk1)
{
    struct qemu_I_CryptCreateLruEntry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTCREATELRUENTRY);
    call.h = (ULONG_PTR)h;
    call.unk0 = unk0;
    call.unk1 = unk1;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI I_CryptCreateLruEntry(HLRUCACHE h, DWORD unk0, DWORD unk1);
static void qemu_I_CryptCreateLruEntry(struct qemu_syscall *call)
{
    struct qemu_I_CryptCreateLruEntry *c = (struct qemu_I_CryptCreateLruEntry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptCreateLruEntry(QEMU_G2H(c->h), c->unk0, c->unk1);
}

#endif

struct qemu_I_CryptFlushLruCache
{
    struct qemu_syscall super;
    uint64_t h;
    uint64_t unk0;
    uint64_t unk1;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI I_CryptFlushLruCache(HLRUCACHE h, DWORD unk0, DWORD unk1)
{
    struct qemu_I_CryptFlushLruCache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTFLUSHLRUCACHE);
    call.h = (ULONG_PTR)h;
    call.unk0 = unk0;
    call.unk1 = unk1;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern DWORD WINAPI I_CryptFlushLruCache(HLRUCACHE h, DWORD unk0, DWORD unk1);
static void qemu_I_CryptFlushLruCache(struct qemu_syscall *call)
{
    struct qemu_I_CryptFlushLruCache *c = (struct qemu_I_CryptFlushLruCache *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptFlushLruCache(QEMU_G2H(c->h), c->unk0, c->unk1);
}

#endif

struct qemu_I_CryptFreeLruCache
{
    struct qemu_syscall super;
    uint64_t h;
    uint64_t unk0;
    uint64_t unk1;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HLRUCACHE WINAPI I_CryptFreeLruCache(HLRUCACHE h, DWORD unk0, DWORD unk1)
{
    struct qemu_I_CryptFreeLruCache call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTFREELRUCACHE);
    call.h = (ULONG_PTR)h;
    call.unk0 = unk0;
    call.unk1 = unk1;

    qemu_syscall(&call.super);

    return (HLRUCACHE)(ULONG_PTR)call.super.iret;
}

#else

extern HLRUCACHE WINAPI I_CryptFreeLruCache(HLRUCACHE h, DWORD unk0, DWORD unk1);
static void qemu_I_CryptFreeLruCache(struct qemu_syscall *call)
{
    struct qemu_I_CryptFreeLruCache *c = (struct qemu_I_CryptFreeLruCache *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(I_CryptFreeLruCache(QEMU_G2H(c->h), c->unk0, c->unk1));
}

#endif

struct qemu_CryptMemAlloc
{
    struct qemu_syscall super;
    uint64_t cbSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI CryptMemAlloc(ULONG cbSize)
{
    struct qemu_CryptMemAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMEMALLOC);
    call.cbSize = cbSize;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

static void qemu_CryptMemAlloc(struct qemu_syscall *call)
{
    struct qemu_CryptMemAlloc *c = (struct qemu_CryptMemAlloc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CryptMemAlloc(c->cbSize);
}

#endif

struct qemu_CryptMemRealloc
{
    struct qemu_syscall super;
    uint64_t pv;
    uint64_t cbSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI CryptMemRealloc(LPVOID pv, ULONG cbSize)
{
    struct qemu_CryptMemRealloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMEMREALLOC);
    call.pv = (ULONG_PTR)pv;
    call.cbSize = cbSize;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

static void qemu_CryptMemRealloc(struct qemu_syscall *call)
{
    struct qemu_CryptMemRealloc *c = (struct qemu_CryptMemRealloc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CryptMemRealloc(QEMU_G2H(c->pv), c->cbSize);
}

#endif

struct qemu_CryptMemFree
{
    struct qemu_syscall super;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI CryptMemFree(LPVOID pv)
{
    struct qemu_CryptMemFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTMEMFREE);
    call.pv = (ULONG_PTR)pv;

    qemu_syscall(&call.super);
}

#else

static void qemu_CryptMemFree(struct qemu_syscall *call)
{
    struct qemu_CryptMemFree *c = (struct qemu_CryptMemFree *)call;
    WINE_FIXME("Unverified!\n");
    CryptMemFree(QEMU_G2H(c->pv));
}

#endif

struct qemu_I_CryptAllocTls
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI I_CryptAllocTls(void)
{
    struct qemu_I_CryptAllocTls call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTALLOCTLS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern DWORD WINAPI I_CryptAllocTls(void);
static void qemu_I_CryptAllocTls(struct qemu_syscall *call)
{
    struct qemu_I_CryptAllocTls *c = (struct qemu_I_CryptAllocTls *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptAllocTls();
}

#endif

struct qemu_I_CryptDetachTls
{
    struct qemu_syscall super;
    uint64_t dwTlsIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI I_CryptDetachTls(DWORD dwTlsIndex)
{
    struct qemu_I_CryptDetachTls call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTDETACHTLS);
    call.dwTlsIndex = dwTlsIndex;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

extern LPVOID WINAPI I_CryptDetachTls(DWORD dwTlsIndex);
static void qemu_I_CryptDetachTls(struct qemu_syscall *call)
{
    struct qemu_I_CryptDetachTls *c = (struct qemu_I_CryptDetachTls *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)I_CryptDetachTls(c->dwTlsIndex);
}

#endif

struct qemu_I_CryptGetTls
{
    struct qemu_syscall super;
    uint64_t dwTlsIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI I_CryptGetTls(DWORD dwTlsIndex)
{
    struct qemu_I_CryptGetTls call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTGETTLS);
    call.dwTlsIndex = dwTlsIndex;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

extern LPVOID WINAPI I_CryptGetTls(DWORD dwTlsIndex);
static void qemu_I_CryptGetTls(struct qemu_syscall *call)
{
    struct qemu_I_CryptGetTls *c = (struct qemu_I_CryptGetTls *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)I_CryptGetTls(c->dwTlsIndex);
}

#endif

struct qemu_I_CryptSetTls
{
    struct qemu_syscall super;
    uint64_t dwTlsIndex;
    uint64_t lpTlsValue;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI I_CryptSetTls(DWORD dwTlsIndex, LPVOID lpTlsValue)
{
    struct qemu_I_CryptSetTls call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTSETTLS);
    call.dwTlsIndex = dwTlsIndex;
    call.lpTlsValue = (ULONG_PTR)lpTlsValue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI I_CryptSetTls(DWORD dwTlsIndex, LPVOID lpTlsValue);
static void qemu_I_CryptSetTls(struct qemu_syscall *call)
{
    struct qemu_I_CryptSetTls *c = (struct qemu_I_CryptSetTls *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptSetTls(c->dwTlsIndex, QEMU_G2H(c->lpTlsValue));
}

#endif

struct qemu_I_CryptFreeTls
{
    struct qemu_syscall super;
    uint64_t dwTlsIndex;
    uint64_t unknown;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI I_CryptFreeTls(DWORD dwTlsIndex, DWORD unknown)
{
    struct qemu_I_CryptFreeTls call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTFREETLS);
    call.dwTlsIndex = dwTlsIndex;
    call.unknown = unknown;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI I_CryptFreeTls(DWORD dwTlsIndex, DWORD unknown);
static void qemu_I_CryptFreeTls(struct qemu_syscall *call)
{
    struct qemu_I_CryptFreeTls *c = (struct qemu_I_CryptFreeTls *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptFreeTls(c->dwTlsIndex, c->unknown);
}

#endif

struct qemu_I_CryptGetOssGlobal
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI I_CryptGetOssGlobal(DWORD x)
{
    struct qemu_I_CryptGetOssGlobal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTGETOSSGLOBAL);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI I_CryptGetOssGlobal(DWORD x);
static void qemu_I_CryptGetOssGlobal(struct qemu_syscall *call)
{
    struct qemu_I_CryptGetOssGlobal *c = (struct qemu_I_CryptGetOssGlobal *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptGetOssGlobal(c->x);
}

#endif

struct qemu_I_CryptGetDefaultCryptProv
{
    struct qemu_syscall super;
    uint64_t reserved;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HCRYPTPROV WINAPI I_CryptGetDefaultCryptProv(DWORD reserved)
{
    struct qemu_I_CryptGetDefaultCryptProv call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTGETDEFAULTCRYPTPROV);
    call.reserved = reserved;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern HCRYPTPROV WINAPI I_CryptGetDefaultCryptProv(DWORD reserved);
static void qemu_I_CryptGetDefaultCryptProv(struct qemu_syscall *call)
{
    struct qemu_I_CryptGetDefaultCryptProv *c = (struct qemu_I_CryptGetDefaultCryptProv *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptGetDefaultCryptProv(c->reserved);
}

#endif

struct qemu_I_CryptReadTrustedPublisherDWORDValueFromRegistry
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t value;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI I_CryptReadTrustedPublisherDWORDValueFromRegistry(LPCWSTR name, DWORD *value)
{
    struct qemu_I_CryptReadTrustedPublisherDWORDValueFromRegistry call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTREADTRUSTEDPUBLISHERDWORDVALUEFROMREGISTRY);
    call.name = (ULONG_PTR)name;
    call.value = (ULONG_PTR)value;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI I_CryptReadTrustedPublisherDWORDValueFromRegistry(LPCWSTR name, DWORD *value);
static void qemu_I_CryptReadTrustedPublisherDWORDValueFromRegistry(struct qemu_syscall *call)
{
    struct qemu_I_CryptReadTrustedPublisherDWORDValueFromRegistry *c = (struct qemu_I_CryptReadTrustedPublisherDWORDValueFromRegistry *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptReadTrustedPublisherDWORDValueFromRegistry(QEMU_G2H(c->name), QEMU_G2H(c->value));
}

#endif

struct qemu_I_CryptInstallOssGlobal
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
    uint64_t z;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI I_CryptInstallOssGlobal(DWORD x, DWORD y, DWORD z)
{
    struct qemu_I_CryptInstallOssGlobal call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTINSTALLOSSGLOBAL);
    call.x = (ULONG_PTR)x;
    call.y = y;
    call.z = z;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern DWORD WINAPI I_CryptInstallOssGlobal(DWORD x, DWORD y, DWORD z);
static void qemu_I_CryptInstallOssGlobal(struct qemu_syscall *call)
{
    struct qemu_I_CryptInstallOssGlobal *c = (struct qemu_I_CryptInstallOssGlobal *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptInstallOssGlobal(c->x, c->y, c->z);
}

#endif

struct qemu_I_CryptInstallAsn1Module
{
    struct qemu_syscall super;
    uint64_t x;
    uint64_t y;
    uint64_t z;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HCRYPTASN1MODULE WINAPI I_CryptInstallAsn1Module(ASN1module_t x, DWORD y, void* z)
{
    struct qemu_I_CryptInstallAsn1Module call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTINSTALLASN1MODULE);
    call.x = (ULONG_PTR)x;
    call.y = y;
    call.z = (ULONG_PTR)z;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_I_CryptInstallAsn1Module(struct qemu_syscall *call)
{
    struct qemu_I_CryptInstallAsn1Module *c = (struct qemu_I_CryptInstallAsn1Module *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptInstallAsn1Module(QEMU_G2H(c->x), c->y, QEMU_G2H(c->z));
}

#endif

struct qemu_I_CryptUninstallAsn1Module
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI I_CryptUninstallAsn1Module(HCRYPTASN1MODULE x)
{
    struct qemu_I_CryptUninstallAsn1Module call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTUNINSTALLASN1MODULE);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_I_CryptUninstallAsn1Module(struct qemu_syscall *call)
{
    struct qemu_I_CryptUninstallAsn1Module *c = (struct qemu_I_CryptUninstallAsn1Module *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = I_CryptUninstallAsn1Module(c->x);
}

#endif

struct qemu_I_CryptGetAsn1Decoder
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ASN1decoding_t WINAPI I_CryptGetAsn1Decoder(HCRYPTASN1MODULE x)
{
    struct qemu_I_CryptGetAsn1Decoder call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTGETASN1DECODER);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return (ASN1decoding_t)(ULONG_PTR)call.super.iret;
}

#else

static void qemu_I_CryptGetAsn1Decoder(struct qemu_syscall *call)
{
    struct qemu_I_CryptGetAsn1Decoder *c = (struct qemu_I_CryptGetAsn1Decoder *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(I_CryptGetAsn1Decoder(c->x));
}

#endif

struct qemu_I_CryptGetAsn1Encoder
{
    struct qemu_syscall super;
    uint64_t x;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ASN1encoding_t WINAPI I_CryptGetAsn1Encoder(HCRYPTASN1MODULE x)
{
    struct qemu_I_CryptGetAsn1Encoder call;
    call.super.id = QEMU_SYSCALL_ID(CALL_I_CRYPTGETASN1ENCODER);
    call.x = (ULONG_PTR)x;

    qemu_syscall(&call.super);

    return (ASN1encoding_t)(ULONG_PTR)call.super.iret;
}

#else

static void qemu_I_CryptGetAsn1Encoder(struct qemu_syscall *call)
{
    struct qemu_I_CryptGetAsn1Encoder *c = (struct qemu_I_CryptGetAsn1Encoder *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(I_CryptGetAsn1Encoder(c->x));
}

#endif

struct qemu_CryptProtectMemory
{
    struct qemu_syscall super;
    uint64_t data;
    uint64_t len;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptProtectMemory(void *data, DWORD len, DWORD flags)
{
    struct qemu_CryptProtectMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTPROTECTMEMORY);
    call.data = (ULONG_PTR)data;
    call.len = len;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_CryptProtectMemory(struct qemu_syscall *call)
{
    struct qemu_CryptProtectMemory *c = (struct qemu_CryptProtectMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptProtectMemory(QEMU_G2H(c->data), c->len, c->flags);
}

#endif

struct qemu_CryptUnprotectMemory
{
    struct qemu_syscall super;
    uint64_t data;
    uint64_t len;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI CryptUnprotectMemory(void *data, DWORD len, DWORD flags)
{
    struct qemu_CryptUnprotectMemory call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CRYPTUNPROTECTMEMORY);
    call.data = (ULONG_PTR)data;
    call.len = len;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_CryptUnprotectMemory(struct qemu_syscall *call)
{
    struct qemu_CryptUnprotectMemory *c = (struct qemu_CryptUnprotectMemory *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = CryptUnprotectMemory(QEMU_G2H(c->data), c->len, c->flags);
}

#endif

struct qemu_dll_init
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_dll_init call;

    if (reason == DLL_PROCESS_ATTACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);

        qemu_syscall(&call.super);
    }

    return TRUE;
}

#else

static void qemu_init_dll(struct qemu_syscall *call)
{
    struct qemu_dll_init *c = (struct qemu_dll_init *)call;
}

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{

    qemu_CertAddCertificateContextToStore,
    qemu_CertAddCertificateLinkToStore,
    qemu_CertAddCRLContextToStore,
    qemu_CertAddCTLContextToStore,
    qemu_CertAddEncodedCertificateToStore,
    qemu_CertAddEncodedCertificateToSystemStoreA,
    qemu_CertAddEncodedCertificateToSystemStoreW,
    qemu_CertAddEncodedCRLToStore,
    qemu_CertAddEncodedCTLToStore,
    qemu_CertAddEnhancedKeyUsageIdentifier,
    qemu_CertAddSerializedElementToStore,
    qemu_CertAddStoreToCollection,
    qemu_CertAlgIdToOID,
    qemu_CertCloseStore,
    qemu_CertCompareCertificate,
    qemu_CertCompareCertificateName,
    qemu_CertCompareIntegerBlob,
    qemu_CertComparePublicKeyInfo,
    qemu_CertControlStore,
    qemu_CertCreateCertificateChainEngine,
    qemu_CertCreateCertificateContext,
    qemu_CertCreateContext,
    qemu_CertCreateCRLContext,
    qemu_CertCreateCTLContext,
    qemu_CertCreateSelfSignCertificate,
    qemu_CertDeleteCertificateFromStore,
    qemu_CertDeleteCRLFromStore,
    qemu_CertDeleteCTLFromStore,
    qemu_CertDuplicateCertificateChain,
    qemu_CertDuplicateCertificateContext,
    qemu_CertDuplicateCRLContext,
    qemu_CertDuplicateCTLContext,
    qemu_CertDuplicateStore,
    qemu_CertEnumCertificateContextProperties,
    qemu_CertEnumCertificatesInStore,
    qemu_CertEnumCRLContextProperties,
    qemu_CertEnumCRLsInStore,
    qemu_CertEnumCTLContextProperties,
    qemu_CertEnumCTLsInStore,
    qemu_CertEnumPhysicalStore,
    qemu_CertEnumSystemStore,
    qemu_CertFindAttribute,
    qemu_CertFindCertificateInCRL,
    qemu_CertFindCertificateInStore,
    qemu_CertFindChainInStore,
    qemu_CertFindCRLInStore,
    qemu_CertFindCTLInStore,
    qemu_CertFindExtension,
    qemu_CertFindRDNAttr,
    qemu_CertFreeCertificateChain,
    qemu_CertFreeCertificateChainEngine,
    qemu_CertFreeCertificateContext,
    qemu_CertFreeCRLContext,
    qemu_CertFreeCTLContext,
    qemu_CertGetCertificateChain,
    qemu_CertGetCertificateContextProperty,
    qemu_CertGetCRLContextProperty,
    qemu_CertGetCRLFromStore,
    qemu_CertGetCTLContextProperty,
    qemu_CertGetEnhancedKeyUsage,
    qemu_CertGetIntendedKeyUsage,
    qemu_CertGetIssuerCertificateFromStore,
    qemu_CertGetNameStringA,
    qemu_CertGetNameStringW,
    qemu_CertGetPublicKeyLength,
    qemu_CertGetStoreProperty,
    qemu_CertGetSubjectCertificateFromStore,
    qemu_CertGetValidUsages,
    qemu_CertIsRDNAttrsInCertificateName,
    qemu_CertIsValidCRLForCertificate,
    qemu_CertNameToStrA,
    qemu_CertNameToStrW,
    qemu_CertOIDToAlgId,
    qemu_CertOpenStore,
    qemu_CertOpenSystemStoreA,
    qemu_CertOpenSystemStoreW,
    qemu_CertRDNValueToStrA,
    qemu_CertRDNValueToStrW,
    qemu_CertRegisterPhysicalStore,
    qemu_CertRegisterSystemStore,
    qemu_CertRemoveEnhancedKeyUsageIdentifier,
    qemu_CertRemoveStoreFromCollection,
    qemu_CertSaveStore,
    qemu_CertSerializeCertificateStoreElement,
    qemu_CertSerializeCRLStoreElement,
    qemu_CertSerializeCTLStoreElement,
    qemu_CertSetCertificateContextProperty,
    qemu_CertSetCRLContextProperty,
    qemu_CertSetCTLContextProperty,
    qemu_CertSetEnhancedKeyUsage,
    qemu_CertSetStoreProperty,
    qemu_CertStrToNameA,
    qemu_CertStrToNameW,
    qemu_CertUnregisterPhysicalStore,
    qemu_CertUnregisterSystemStore,
    qemu_CertVerifyCertificateChainPolicy,
    qemu_CertVerifyCRLRevocation,
    qemu_CertVerifyCRLTimeValidity,
    qemu_CertVerifyCTLUsage,
    qemu_CertVerifyRevocation,
    qemu_CertVerifySubjectCertificateContext,
    qemu_CertVerifyTimeValidity,
    qemu_CertVerifyValidityNesting,
    qemu_CryptAcquireCertificatePrivateKey,
    qemu_CryptBinaryToStringA,
    qemu_CryptBinaryToStringW,
    qemu_CryptDecodeObject,
    qemu_CryptDecodeObjectEx,
    qemu_CryptEncodeObject,
    qemu_CryptEncodeObjectEx,
    qemu_CryptEncryptMessage,
    qemu_CryptEnumOIDInfo,
    qemu_CryptExportPublicKeyInfo,
    qemu_CryptExportPublicKeyInfoEx,
    qemu_CryptFindCertificateKeyProvInfo,
    qemu_CryptFindLocalizedName,
    qemu_CryptFindOIDInfo,
    qemu_CryptFormatObject,
    qemu_CryptFreeOIDFunctionAddress,
    qemu_CryptGetDefaultOIDDllList,
    qemu_CryptGetDefaultOIDFunctionAddress,
    qemu_CryptGetMessageCertificates,
    qemu_CryptGetMessageSignerCount,
    qemu_CryptGetOIDFunctionAddress,
    qemu_CryptGetOIDFunctionValue,
    qemu_CryptHashCertificate,
    qemu_CryptHashMessage,
    qemu_CryptHashPublicKeyInfo,
    qemu_CryptHashToBeSigned,
    qemu_CryptImportPublicKeyInfo,
    qemu_CryptImportPublicKeyInfoEx,
    qemu_CryptInitOIDFunctionSet,
    qemu_CryptInstallOIDFunctionAddress,
    qemu_CryptMemAlloc,
    qemu_CryptMemFree,
    qemu_CryptMemRealloc,
    qemu_CryptMsgClose,
    qemu_CryptMsgControl,
    qemu_CryptMsgDuplicate,
    qemu_CryptMsgEncodeAndSignCTL,
    qemu_CryptMsgGetAndVerifySigner,
    qemu_CryptMsgGetParam,
    qemu_CryptMsgOpenToDecode,
    qemu_CryptMsgOpenToEncode,
    qemu_CryptMsgSignCTL,
    qemu_CryptMsgUpdate,
    qemu_CryptMsgVerifyCountersignatureEncoded,
    qemu_CryptMsgVerifyCountersignatureEncodedEx,
    qemu_CryptProtectData,
    qemu_CryptProtectMemory,
    qemu_CryptQueryObject,
    qemu_CryptRegisterDefaultOIDFunction,
    qemu_CryptRegisterOIDFunction,
    qemu_CryptRegisterOIDInfo,
    qemu_CryptSetOIDFunctionValue,
    qemu_CryptSignAndEncodeCertificate,
    qemu_CryptSignCertificate,
    qemu_CryptSignMessage,
    qemu_CryptSIPAddProvider,
    qemu_CryptSIPCreateIndirectData,
    qemu_CryptSIPGetSignedDataMsg,
    qemu_CryptSIPLoad,
    qemu_CryptSIPPutSignedDataMsg,
    qemu_CryptSIPRemoveProvider,
    qemu_CryptSIPRemoveSignedDataMsg,
    qemu_CryptSIPRetrieveSubjectGuid,
    qemu_CryptSIPRetrieveSubjectGuidForCatalogFile,
    qemu_CryptSIPVerifyIndirectData,
    qemu_CryptStringToBinaryA,
    qemu_CryptStringToBinaryW,
    qemu_CryptUnprotectData,
    qemu_CryptUnprotectMemory,
    qemu_CryptUnregisterDefaultOIDFunction,
    qemu_CryptUnregisterOIDFunction,
    qemu_CryptVerifyCertificateSignature,
    qemu_CryptVerifyCertificateSignatureEx,
    qemu_CryptVerifyDetachedMessageHash,
    qemu_CryptVerifyDetachedMessageSignature,
    qemu_CryptVerifyMessageHash,
    qemu_CryptVerifyMessageSignature,
    qemu_I_CertUpdateStore,
    qemu_I_CryptAllocTls,
    qemu_I_CryptCreateLruCache,
    qemu_I_CryptCreateLruEntry,
    qemu_I_CryptDetachTls,
    qemu_I_CryptFindLruEntry,
    qemu_I_CryptFindLruEntryData,
    qemu_I_CryptFlushLruCache,
    qemu_I_CryptFreeLruCache,
    qemu_I_CryptFreeTls,
    qemu_I_CryptGetAsn1Decoder,
    qemu_I_CryptGetAsn1Encoder,
    qemu_I_CryptGetDefaultCryptProv,
    qemu_I_CryptGetOssGlobal,
    qemu_I_CryptGetTls,
    qemu_I_CryptInstallAsn1Module,
    qemu_I_CryptInstallOssGlobal,
    qemu_I_CryptReadTrustedPublisherDWORDValueFromRegistry,
    qemu_I_CryptSetTls,
    qemu_I_CryptUninstallAsn1Module,
    qemu_init_dll,
    qemu_PFXExportCertStore,
    qemu_PFXExportCertStoreEx,
    qemu_PFXImportCertStore,
    qemu_PFXIsPFXBlob,
    qemu_PFXVerifyPassword,
};

HCERTSTORE empty_store;
uint64_t empty_store_replace;

/* Taken from the tests */
static const BYTE selfSignedCert[] =
{
    0x30, 0x82, 0x01, 0x1f, 0x30, 0x81, 0xce, 0xa0, 0x03, 0x02, 0x01, 0x02, 0x02,
    0x10, 0xeb, 0x0d, 0x57, 0x2a, 0x9c, 0x09, 0xba, 0xa4, 0x4a, 0xb7, 0x25, 0x49,
    0xd9, 0x3e, 0xb5, 0x73, 0x30, 0x09, 0x06, 0x05, 0x2b, 0x0e, 0x03, 0x02, 0x1d,
    0x05, 0x00, 0x30, 0x15, 0x31, 0x13, 0x30, 0x11, 0x06, 0x03, 0x55, 0x04, 0x03,
    0x13, 0x0a, 0x4a, 0x75, 0x61, 0x6e, 0x20, 0x4c, 0x61, 0x6e, 0x67, 0x00, 0x30,
    0x1e, 0x17, 0x0d, 0x30, 0x36, 0x30, 0x36, 0x32, 0x39, 0x30, 0x35, 0x30, 0x30,
    0x34, 0x36, 0x5a, 0x17, 0x0d, 0x30, 0x37, 0x30, 0x36, 0x32, 0x39, 0x31, 0x31,
    0x30, 0x30, 0x34, 0x36, 0x5a, 0x30, 0x15, 0x31, 0x13, 0x30, 0x11, 0x06, 0x03,
    0x55, 0x04, 0x03, 0x13, 0x0a, 0x4a, 0x75, 0x61, 0x6e, 0x20, 0x4c, 0x61, 0x6e,
    0x67, 0x00, 0x30, 0x5c, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7,
    0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x4b, 0x00, 0x30, 0x48, 0x02, 0x41,
    0x00, 0xe2, 0x54, 0x3a, 0xa7, 0x83, 0xb1, 0x27, 0x14, 0x3e, 0x59, 0xbb, 0xb4,
    0x53, 0xe6, 0x1f, 0xe7, 0x5d, 0xf1, 0x21, 0x68, 0xad, 0x85, 0x53, 0xdb, 0x6b,
    0x1e, 0xeb, 0x65, 0x97, 0x03, 0x86, 0x60, 0xde, 0xf3, 0x6c, 0x38, 0x75, 0xe0,
    0x4c, 0x61, 0xbb, 0xbc, 0x62, 0x17, 0xa9, 0xcd, 0x79, 0x3f, 0x21, 0x4e, 0x96,
    0xcb, 0x0e, 0xdc, 0x61, 0x94, 0x30, 0x18, 0x10, 0x6b, 0xd0, 0x1c, 0x10, 0x79,
    0x02, 0x03, 0x01, 0x00, 0x01, 0x30, 0x09, 0x06, 0x05, 0x2b, 0x0e, 0x03, 0x02,
    0x1d, 0x05, 0x00, 0x03, 0x41, 0x00, 0x25, 0x90, 0x53, 0x34, 0xd9, 0x56, 0x41,
    0x5e, 0xdb, 0x7e, 0x01, 0x36, 0xec, 0x27, 0x61, 0x5e, 0xb7, 0x4d, 0x90, 0x66,
    0xa2, 0xe1, 0x9d, 0x58, 0x76, 0xd4, 0x9c, 0xba, 0x2c, 0x84, 0xc6, 0x83, 0x7a,
    0x22, 0x0d, 0x03, 0x69, 0x32, 0x1a, 0x6d, 0xcb, 0x0c, 0x15, 0xb3, 0x6b, 0xc7,
    0x0a, 0x8c, 0xb4, 0x5c, 0x34, 0x78, 0xe0, 0x3c, 0x9c, 0xe9, 0xf3, 0x30, 0x9f,
    0xa8, 0x76, 0x57, 0x92, 0x36
};

static CRITICAL_SECTION ctx_cs;
static struct wine_rb_tree ctx_tree;

static int ctx_compare(const void *key, const struct wine_rb_entry *entry)
{
    const struct qemu_cert_context *cert = WINE_RB_ENTRY_VALUE(entry, struct qemu_cert_context, entry);

    if ((ULONG_PTR)cert->cert64 < (ULONG_PTR)key)
        return -1;
    else if ((ULONG_PTR)cert->cert64 == (ULONG_PTR)key)
        return 0;
    else
        return 1;
}

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side crypt32 wrapper.\n");
    HMODULE crypt32 = GetModuleHandleA("crypt32");
    const CERT_CONTEXT *context;
    /* Taken from the tests */

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

#if GUEST_BIT != HOST_BIT
    /* Some certificate get placed in something named "empty_store" in Wine's crypt32. This is a
     * static variable and thus > 4GB. Replace it with a replacement value.*/
    context = CertCreateCertificateContext(X509_ASN_ENCODING,
            selfSignedCert, sizeof(selfSignedCert));
    if (!context)
        WINE_ERR("Could not create the test certificate.\n");

    empty_store = context->hCertStore;

    /* This should find us some unused address. */
    empty_store_replace = (ULONG_PTR)HeapAlloc(GetProcessHeap(), 0, 0);

    CertFreeCertificateContext(context);

    InitializeCriticalSection(&ctx_cs);
    wine_rb_init(&ctx_tree, ctx_compare);
#endif

    return dll_functions;
}

struct qemu_cert_context *context32_create(const CERT_CONTEXT *cert64)
{
    struct qemu_cert_context *ret;
    struct wine_rb_entry *entry;

    EnterCriticalSection(&ctx_cs);
    entry = wine_rb_get(&ctx_tree, cert64);
    if (entry)
    {
        ret = WINE_RB_ENTRY_VALUE(entry, struct qemu_cert_context, entry);
        LeaveCriticalSection(&ctx_cs);

        InterlockedIncrement(&ret->ref);

        WINE_TRACE("Found existing wrapper %p for ctx %p.\n", ret, cert64);
        return ret;
    }

    ret = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ret));
    if (!ret)
        WINE_ERR("Out of memory\n");
    ret->cert64 = cert64;
    ret->ref = 1;
    CERT_CONTEXT_h2g(&ret->cert32, cert64);

    if (cert64->hCertStore == empty_store)
        ret->cert32.hCertStore = empty_store_replace;

    CERT_INFO_h2g(&ret->cert_info, cert64->pCertInfo);
    ret->cert32.pCertInfo = QEMU_H2G(&ret->cert_info);

    /* We have to be able to recognize pointers we already passed to the app, (a) because the tests
     * check for equality and (b) because many getters return pointers into key stores that the
     * caller doesn't release.
     *
     * Unfortunately we cannot use CERT_FIRST_USER_PROP_ID (or higher values) because Wine doesn't
     * implement them and my simple attempt at implementing them lead them to be serialized into
     * certificate blobs, breaking the tests. */
    WINE_TRACE("Put wrapper %p for ctx %p.\n", ret, cert64);
    wine_rb_put(&ctx_tree, cert64, &ret->entry);

    LeaveCriticalSection(&ctx_cs);
    return ret;
}

void context32_decref(struct qemu_cert_context *context)
{
    if (InterlockedDecrement(&context->ref) == 0)
    {
        WINE_TRACE("Freeing CERT_CONTEXT wrapper %p.\n", context);
        EnterCriticalSection(&ctx_cs);
        wine_rb_remove(&ctx_tree, &context->entry);
        LeaveCriticalSection(&ctx_cs);

        HeapFree(GetProcessHeap(), 0, context);
    }
}

HCERTSTORE cert_store_g2h(uint64_t store)
{
#if GUEST_BIT == HOST_BIT
    return QEMU_G2H(store);
#endif

    if (store == empty_store_replace)
        return empty_store;
    else
        return QEMU_G2H(store);
}

const CERT_CONTEXT WINAPI *crypt32_CERT_CONTEXT_g2h(qemu_ptr cert32)
{
    struct qemu_cert_context *impl = context_impl_from_context32(QEMU_G2H((ULONG_PTR)cert32));
    if (!impl)
        return NULL;
    return impl->cert64;
}

const qemu_ptr WINAPI crypt32_CERT_CONTEXT_h2g(CERT_CONTEXT *cert64)
{
    struct qemu_cert_context *impl;
    if (!cert64)
        return 0;
    impl = context32_create(cert64);
    return QEMU_H2G(impl);
}

#endif
