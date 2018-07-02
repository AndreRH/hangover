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
#include <wct.h>
#include <wmistr.h>
#include <evntrace.h>
#include <evntprov.h>
#include <perflib.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_advapi32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_advapi32);
#endif

struct qemu_PerfCreateInstance
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t guid;
    uint64_t name;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI PPERF_COUNTERSET_INSTANCE WINAPI PerfCreateInstance(HANDLE handle, LPCGUID guid, const WCHAR *name, ULONG id)
{
    struct qemu_PerfCreateInstance call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PERFCREATEINSTANCE);
    call.handle = (ULONG_PTR)handle;
    call.guid = (ULONG_PTR)guid;
    call.name = (ULONG_PTR)name;
    call.id = id;

    qemu_syscall(&call.super);

    return (PPERF_COUNTERSET_INSTANCE)(ULONG_PTR)call.super.iret;
}

#else

extern PPERF_COUNTERSET_INSTANCE WINAPI PerfCreateInstance(HANDLE handle, LPCGUID guid, const WCHAR *name, ULONG id);
void qemu_PerfCreateInstance(struct qemu_syscall *call)
{
    struct qemu_PerfCreateInstance *c = (struct qemu_PerfCreateInstance *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(PerfCreateInstance(QEMU_G2H(c->handle), QEMU_G2H(c->guid), QEMU_G2H(c->name), c->id));
}

#endif

struct qemu_PerfDeleteInstance
{
    struct qemu_syscall super;
    uint64_t provider;
    uint64_t block;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI PerfDeleteInstance(HANDLE provider, PPERF_COUNTERSET_INSTANCE block)
{
    struct qemu_PerfDeleteInstance call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PERFDELETEINSTANCE);
    call.provider = (ULONG_PTR)provider;
    call.block = (ULONG_PTR)block;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern ULONG WINAPI PerfDeleteInstance(HANDLE provider, PPERF_COUNTERSET_INSTANCE block);
void qemu_PerfDeleteInstance(struct qemu_syscall *call)
{
    struct qemu_PerfDeleteInstance *c = (struct qemu_PerfDeleteInstance *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PerfDeleteInstance(QEMU_G2H(c->provider), QEMU_G2H(c->block));
}

#endif

struct qemu_PerfSetCounterSetInfo
{
    struct qemu_syscall super;
    uint64_t handle;
    uint64_t template;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI PerfSetCounterSetInfo(HANDLE handle, PPERF_COUNTERSET_INFO template, ULONG size)
{
    struct qemu_PerfSetCounterSetInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PERFSETCOUNTERSETINFO);
    call.handle = (ULONG_PTR)handle;
    call.template = (ULONG_PTR)template;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern ULONG WINAPI PerfSetCounterSetInfo(HANDLE handle, PPERF_COUNTERSET_INFO template, ULONG size);
void qemu_PerfSetCounterSetInfo(struct qemu_syscall *call)
{
    struct qemu_PerfSetCounterSetInfo *c = (struct qemu_PerfSetCounterSetInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PerfSetCounterSetInfo(QEMU_G2H(c->handle), QEMU_G2H(c->template), c->size);
}

#endif

struct qemu_PerfSetCounterRefValue
{
    struct qemu_syscall super;
    uint64_t provider;
    uint64_t instance;
    uint64_t counterid;
    uint64_t address;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI PerfSetCounterRefValue(HANDLE provider, PPERF_COUNTERSET_INSTANCE instance, ULONG counterid, void *address)
{
    struct qemu_PerfSetCounterRefValue call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PERFSETCOUNTERREFVALUE);
    call.provider = (ULONG_PTR)provider;
    call.instance = (ULONG_PTR)instance;
    call.counterid = counterid;
    call.address = (ULONG_PTR)address;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern ULONG WINAPI PerfSetCounterRefValue(HANDLE provider, PPERF_COUNTERSET_INSTANCE instance, ULONG counterid, void *address);
void qemu_PerfSetCounterRefValue(struct qemu_syscall *call)
{
    struct qemu_PerfSetCounterRefValue *c = (struct qemu_PerfSetCounterRefValue *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PerfSetCounterRefValue(QEMU_G2H(c->provider), QEMU_G2H(c->instance), c->counterid, QEMU_G2H(c->address));
}

#endif

struct qemu_PerfStartProvider
{
    struct qemu_syscall super;
    uint64_t guid;
    uint64_t callback;
    uint64_t provider;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI PerfStartProvider(GUID *guid, PERFLIBREQUEST callback, HANDLE *provider)
{
    struct qemu_PerfStartProvider call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PERFSTARTPROVIDER);
    call.guid = (ULONG_PTR)guid;
    call.callback = (ULONG_PTR)callback;
    call.provider = (ULONG_PTR)provider;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern ULONG WINAPI PerfStartProvider(GUID *guid, PERFLIBREQUEST callback, HANDLE *provider);
void qemu_PerfStartProvider(struct qemu_syscall *call)
{
    struct qemu_PerfStartProvider *c = (struct qemu_PerfStartProvider *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PerfStartProvider(QEMU_G2H(c->guid), QEMU_G2H(c->callback), QEMU_G2H(c->provider));
}

#endif

struct qemu_PerfStartProviderEx
{
    struct qemu_syscall super;
    uint64_t guid;
    uint64_t context;
    uint64_t provider;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI PerfStartProviderEx(GUID *guid, PPERF_PROVIDER_CONTEXT context, HANDLE *provider)
{
    struct qemu_PerfStartProviderEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PERFSTARTPROVIDEREX);
    call.guid = (ULONG_PTR)guid;
    call.context = (ULONG_PTR)context;
    call.provider = (ULONG_PTR)provider;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern ULONG WINAPI PerfStartProviderEx(GUID *guid, PPERF_PROVIDER_CONTEXT context, HANDLE *provider);
void qemu_PerfStartProviderEx(struct qemu_syscall *call)
{
    struct qemu_PerfStartProviderEx *c = (struct qemu_PerfStartProviderEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PerfStartProviderEx(QEMU_G2H(c->guid), QEMU_G2H(c->context), QEMU_G2H(c->provider));
}

#endif

struct qemu_PerfStopProvider
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI PerfStopProvider(HANDLE handle)
{
    struct qemu_PerfStopProvider call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PERFSTOPPROVIDER);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern ULONG WINAPI PerfStopProvider(HANDLE handle);
void qemu_PerfStopProvider(struct qemu_syscall *call)
{
    struct qemu_PerfStopProvider *c = (struct qemu_PerfStopProvider *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PerfStopProvider(QEMU_G2H(c->handle));
}

#endif

