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
    qemu_CertCompareCertificate,
    qemu_CertCompareCertificateName,
    qemu_CertCompareIntegerBlob,
    qemu_CertComparePublicKeyInfo,
    qemu_CertCreateCertificateChainEngine,
    qemu_CertCreateCertificateContext,
    qemu_CertCreateContext,
    qemu_CertCreateCRLContext,
    qemu_CertCreateCTLContext,
    qemu_CertCreateSelfSignCertificate,
    qemu_CertDeleteCTLFromStore,
    qemu_CertDuplicateCertificateChain,
    qemu_CertDuplicateCertificateContext,
    qemu_CertDuplicateCRLContext,
    qemu_CertDuplicateCTLContext,
    qemu_CertEnumCertificateContextProperties,
    qemu_CertEnumCRLContextProperties,
    qemu_CertEnumCTLContextProperties,
    qemu_CertEnumCTLsInStore,
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
    qemu_CertGetPublicKeyLength,
    qemu_CertGetSubjectCertificateFromStore,
    qemu_CertGetValidUsages,
    qemu_CertIsRDNAttrsInCertificateName,
    qemu_CertIsValidCRLForCertificate,
    qemu_CertOIDToAlgId,
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
    qemu_CryptUnprotectMemory,
    qemu_CryptUnregisterDefaultOIDFunction,
    qemu_CryptUnregisterOIDFunction,
    qemu_CryptVerifyCertificateSignature,
    qemu_CryptVerifyCertificateSignatureEx,
    qemu_CryptVerifyDetachedMessageHash,
    qemu_CryptVerifyDetachedMessageSignature,
    qemu_CryptVerifyMessageHash,
    qemu_CryptVerifyMessageSignature,
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

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side crypt32 wrapper.\n");
    HMODULE crypt32 = GetModuleHandleA("crypt32");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
