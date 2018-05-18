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
#include <fci.h>
#include <fdi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_cabinet.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_cabinet);
#endif


struct qemu_FDICreate
{
    struct qemu_syscall super;
    uint64_t pfnalloc;
    uint64_t pfnfree;
    uint64_t pfnopen;
    uint64_t pfnread;
    uint64_t pfnwrite;
    uint64_t pfnclose;
    uint64_t pfnseek;
    uint64_t cpuType;
    uint64_t perf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HFDI CDECL FDICreate(PFNALLOC pfnalloc, PFNFREE pfnfree, PFNOPEN pfnopen, PFNREAD pfnread, PFNWRITE pfnwrite, PFNCLOSE pfnclose, PFNSEEK pfnseek, int cpuType, PERF perf)
{
    struct qemu_FDICreate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FDICREATE);
    call.pfnalloc = (ULONG_PTR)pfnalloc;
    call.pfnfree = (ULONG_PTR)pfnfree;
    call.pfnopen = (ULONG_PTR)pfnopen;
    call.pfnread = (ULONG_PTR)pfnread;
    call.pfnwrite = (ULONG_PTR)pfnwrite;
    call.pfnclose = (ULONG_PTR)pfnclose;
    call.pfnseek = (ULONG_PTR)pfnseek;
    call.cpuType = cpuType;
    call.perf = (ULONG_PTR)perf;

    qemu_syscall(&call.super);

    return (HFDI)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FDICreate(struct qemu_syscall *call)
{
    struct qemu_FDICreate *c = (struct qemu_FDICreate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(FDICreate(QEMU_G2H(c->pfnalloc), QEMU_G2H(c->pfnfree), QEMU_G2H(c->pfnopen), QEMU_G2H(c->pfnread), QEMU_G2H(c->pfnwrite), QEMU_G2H(c->pfnclose), QEMU_G2H(c->pfnseek), c->cpuType, QEMU_G2H(c->perf)));
}

#endif

struct qemu_FDIIsCabinet
{
    struct qemu_syscall super;
    uint64_t hfdi;
    uint64_t hf;
    uint64_t pfdici;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL FDIIsCabinet(HFDI hfdi, INT_PTR hf, PFDICABINETINFO pfdici)
{
    struct qemu_FDIIsCabinet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FDIISCABINET);
    call.hfdi = (ULONG_PTR)hfdi;
    call.hf = hf;
    call.pfdici = (ULONG_PTR)pfdici;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FDIIsCabinet(struct qemu_syscall *call)
{
    struct qemu_FDIIsCabinet *c = (struct qemu_FDIIsCabinet *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FDIIsCabinet(QEMU_G2H(c->hfdi), c->hf, QEMU_G2H(c->pfdici));
}

#endif

struct qemu_FDICopy
{
    struct qemu_syscall super;
    uint64_t hfdi;
    uint64_t pszCabinet;
    uint64_t pszCabPath;
    uint64_t flags;
    uint64_t pfnfdin;
    uint64_t pfnfdid;
    uint64_t pvUser;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL FDICopy(HFDI hfdi, char *pszCabinet, char *pszCabPath, int flags, PFNFDINOTIFY pfnfdin, PFNFDIDECRYPT pfnfdid, void *pvUser)
{
    struct qemu_FDICopy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FDICOPY);
    call.hfdi = (ULONG_PTR)hfdi;
    call.pszCabinet = (ULONG_PTR)pszCabinet;
    call.pszCabPath = (ULONG_PTR)pszCabPath;
    call.flags = flags;
    call.pfnfdin = (ULONG_PTR)pfnfdin;
    call.pfnfdid = (ULONG_PTR)pfnfdid;
    call.pvUser = (ULONG_PTR)pvUser;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FDICopy(struct qemu_syscall *call)
{
    struct qemu_FDICopy *c = (struct qemu_FDICopy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FDICopy(QEMU_G2H(c->hfdi), QEMU_G2H(c->pszCabinet), QEMU_G2H(c->pszCabPath), c->flags, QEMU_G2H(c->pfnfdin), QEMU_G2H(c->pfnfdid), QEMU_G2H(c->pvUser));
}

#endif

struct qemu_FDIDestroy
{
    struct qemu_syscall super;
    uint64_t hfdi;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL FDIDestroy(HFDI hfdi)
{
    struct qemu_FDIDestroy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FDIDESTROY);
    call.hfdi = (ULONG_PTR)hfdi;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FDIDestroy(struct qemu_syscall *call)
{
    struct qemu_FDIDestroy *c = (struct qemu_FDIDestroy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FDIDestroy(QEMU_G2H(c->hfdi));
}

#endif

struct qemu_FDITruncateCabinet
{
    struct qemu_syscall super;
    uint64_t hfdi;
    uint64_t pszCabinetName;
    uint64_t iFolderToDelete;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL FDITruncateCabinet(HFDI hfdi, char *pszCabinetName, USHORT iFolderToDelete)
{
    struct qemu_FDITruncateCabinet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FDITRUNCATECABINET);
    call.hfdi = (ULONG_PTR)hfdi;
    call.pszCabinetName = (ULONG_PTR)pszCabinetName;
    call.iFolderToDelete = iFolderToDelete;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FDITruncateCabinet(struct qemu_syscall *call)
{
    struct qemu_FDITruncateCabinet *c = (struct qemu_FDITruncateCabinet *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FDITruncateCabinet(QEMU_G2H(c->hfdi), QEMU_G2H(c->pszCabinetName), c->iFolderToDelete);
}

#endif

