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

struct qemu_dll_init
{
    struct qemu_syscall super;
    uint64_t fci_alloc_guest;
    uint64_t fci_free_guest;
    uint64_t fci_open_info_guest;
    uint64_t fci_readwrite_guest;
    uint64_t fci_close_guest;
    uint64_t fci_progress_guest;
    uint64_t fci_dest_guest;
    uint64_t fci_open_guest;
    uint64_t fci_temp_guest;
    uint64_t fci_delete_guest;
    uint64_t fci_seek_guest;

    uint64_t fdi_readwrite_guest;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_dll_init call;

    if (reason == DLL_PROCESS_ATTACH)
    {
        call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
        call.fci_alloc_guest = (ULONG_PTR)fci_alloc_guest;
        call.fci_free_guest = (ULONG_PTR)fci_free_guest;
        call.fci_open_info_guest = (ULONG_PTR)fci_open_info_guest;
        call.fci_readwrite_guest = (ULONG_PTR)fci_readwrite_guest;
        call.fci_close_guest = (ULONG_PTR)fci_close_guest;
        call.fci_progress_guest = (ULONG_PTR)fci_progress_guest;
        call.fci_dest_guest = (ULONG_PTR)fci_dest_guest;
        call.fci_open_guest = (ULONG_PTR)fci_open_guest;
        call.fci_temp_guest = (ULONG_PTR)fci_temp_guest;
        call.fci_delete_guest = (ULONG_PTR)fci_delete_guest;
        call.fci_seek_guest = (ULONG_PTR)fci_seek_guest;

        call.fdi_readwrite_guest = (ULONG_PTR)fdi_readwrite_guest;
        qemu_syscall(&call.super);
    }

    return TRUE;
}

#else

uint64_t fci_dest_guest;
uint64_t fci_alloc_guest;
uint64_t fci_free_guest;
uint64_t fci_open_guest;
uint64_t fci_readwrite_guest;
uint64_t fci_write_guest;
uint64_t fci_close_guest;
uint64_t fci_seek_guest;
uint64_t fci_delete_guest;
uint64_t fci_temp_guest;
uint64_t fci_open_info_guest;
uint64_t fci_progress_guest;

uint64_t fdi_readwrite_guest;

static void qemu_init_dll(struct qemu_syscall *call)
{
    struct qemu_dll_init *c = (struct qemu_dll_init *)call;
    fci_alloc_guest = c->fci_alloc_guest;
    fci_free_guest = c->fci_free_guest;
    fci_open_info_guest = c->fci_open_info_guest;
    fci_readwrite_guest = c->fci_readwrite_guest;
    fci_close_guest = c->fci_close_guest;
    fci_progress_guest = c->fci_progress_guest;
    fci_dest_guest = c->fci_dest_guest;
    fci_open_guest = c->fci_open_guest;
    fci_temp_guest = c->fci_temp_guest;
    fci_delete_guest = c->fci_delete_guest;
    fci_seek_guest = c->fci_seek_guest;

    fdi_readwrite_guest = c->fdi_readwrite_guest;
}

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
    qemu_init_dll,
};

__thread struct qemu_fxi *cabinet_tls;

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side cabinet wrapper.\n");
    HMODULE cabinet = GetModuleHandleA("cabinet");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    p_Extract = (void *)GetProcAddress(cabinet, "Extract");
    if (!p_Extract)
        WINE_ERR("Cannot get Extract entrypoint.\n");
    p_DllGetVersion = (void *)GetProcAddress(cabinet, "DllGetVersion");
    if (!p_Extract)
        WINE_ERR("Cannot get DllGetVersion entrypoint.\n");

    return dll_functions;
}

#endif
