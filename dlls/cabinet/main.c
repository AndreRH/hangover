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
#include <fci.h>
#include <fdi.h>
#include <shlwapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_cabinet.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_cabinet);
#endif

struct qemu_DllGetVersion
{
    struct qemu_syscall super;
    uint64_t pdvi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllGetVersion (DLLVERSIONINFO *pdvi)
{
    struct qemu_DllGetVersion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLGETVERSION);
    call.pdvi = (ULONG_PTR)pdvi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static HRESULT (* WINAPI p_DllGetVersion)(DLLVERSIONINFO *pdvi);
static void qemu_DllGetVersion(struct qemu_syscall *call)
{
    struct qemu_DllGetVersion *c = (struct qemu_DllGetVersion *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DllGetVersion(QEMU_G2H(c->pdvi));
}

#endif

struct qemu_Extract
{
    struct qemu_syscall super;
    uint64_t dest;
    uint64_t szCabName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI Extract(SESSION *dest, LPCSTR szCabName)
{
    struct qemu_Extract call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTRACT);
    call.dest = (ULONG_PTR)dest;
    call.szCabName = (ULONG_PTR)szCabName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static HRESULT (WINAPI *p_Extract)(SESSION *, const char *);
static void qemu_Extract(struct qemu_syscall *call)
{
    struct qemu_Extract *c = (struct qemu_Extract *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_Extract(QEMU_G2H(c->dest), QEMU_G2H(c->szCabName));
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

    qemu_DllGetVersion,
    qemu_Extract,
    qemu_FCIAddFile,
    qemu_FCICreate,
    qemu_FCIDestroy,
    qemu_FCIFlushCabinet,
    qemu_FCIFlushFolder,
    qemu_FDICopy,
    qemu_FDICreate,
    qemu_FDIDestroy,
    qemu_FDIIsCabinet,
    qemu_FDITruncateCabinet,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side cabinet wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
