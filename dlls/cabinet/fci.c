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


struct qemu_FCICreate
{
    struct qemu_syscall super;
    uint64_t perf;
    uint64_t pfnfiledest;
    uint64_t pfnalloc;
    uint64_t pfnfree;
    uint64_t pfnopen;
    uint64_t pfnread;
    uint64_t pfnwrite;
    uint64_t pfnclose;
    uint64_t pfnseek;
    uint64_t pfndelete;
    uint64_t pfnfcigtf;
    uint64_t pccab;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HFCI CDECL FCICreate(PERF perf, PFNFCIFILEPLACED pfnfiledest, PFNFCIALLOC pfnalloc, PFNFCIFREE pfnfree, PFNFCIOPEN pfnopen, PFNFCIREAD pfnread, PFNFCIWRITE pfnwrite, PFNFCICLOSE pfnclose, PFNFCISEEK pfnseek, PFNFCIDELETE pfndelete, PFNFCIGETTEMPFILE pfnfcigtf, PCCAB pccab, void *pv)
{
    struct qemu_FCICreate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FCICREATE);
    call.perf = (ULONG_PTR)perf;
    call.pfnfiledest = (ULONG_PTR)pfnfiledest;
    call.pfnalloc = (ULONG_PTR)pfnalloc;
    call.pfnfree = (ULONG_PTR)pfnfree;
    call.pfnopen = (ULONG_PTR)pfnopen;
    call.pfnread = (ULONG_PTR)pfnread;
    call.pfnwrite = (ULONG_PTR)pfnwrite;
    call.pfnclose = (ULONG_PTR)pfnclose;
    call.pfnseek = (ULONG_PTR)pfnseek;
    call.pfndelete = (ULONG_PTR)pfndelete;
    call.pfnfcigtf = (ULONG_PTR)pfnfcigtf;
    call.pccab = (ULONG_PTR)pccab;
    call.pv = (ULONG_PTR)pv;

    qemu_syscall(&call.super);

    return (HFCI)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FCICreate(struct qemu_syscall *call)
{
    struct qemu_FCICreate *c = (struct qemu_FCICreate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(FCICreate(QEMU_G2H(c->perf), QEMU_G2H(c->pfnfiledest), QEMU_G2H(c->pfnalloc), QEMU_G2H(c->pfnfree), QEMU_G2H(c->pfnopen), QEMU_G2H(c->pfnread), QEMU_G2H(c->pfnwrite), QEMU_G2H(c->pfnclose), QEMU_G2H(c->pfnseek), QEMU_G2H(c->pfndelete), QEMU_G2H(c->pfnfcigtf), QEMU_G2H(c->pccab), QEMU_G2H(c->pv)));
}

#endif

struct qemu_FCIAddFile
{
    struct qemu_syscall super;
    uint64_t hfci;
    uint64_t pszSourceFile;
    uint64_t pszFileName;
    uint64_t fExecute;
    uint64_t pfnfcignc;
    uint64_t pfnfcis;
    uint64_t pfnfcigoi;
    uint64_t typeCompress;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL FCIAddFile(HFCI hfci, char *pszSourceFile, char *pszFileName, BOOL fExecute, PFNFCIGETNEXTCABINET pfnfcignc, PFNFCISTATUS pfnfcis, PFNFCIGETOPENINFO pfnfcigoi, TCOMP typeCompress)
{
    struct qemu_FCIAddFile call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FCIADDFILE);
    call.hfci = (ULONG_PTR)hfci;
    call.pszSourceFile = (ULONG_PTR)pszSourceFile;
    call.pszFileName = (ULONG_PTR)pszFileName;
    call.fExecute = fExecute;
    call.pfnfcignc = (ULONG_PTR)pfnfcignc;
    call.pfnfcis = (ULONG_PTR)pfnfcis;
    call.pfnfcigoi = (ULONG_PTR)pfnfcigoi;
    call.typeCompress = typeCompress;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FCIAddFile(struct qemu_syscall *call)
{
    struct qemu_FCIAddFile *c = (struct qemu_FCIAddFile *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FCIAddFile(QEMU_G2H(c->hfci), QEMU_G2H(c->pszSourceFile), QEMU_G2H(c->pszFileName), c->fExecute, QEMU_G2H(c->pfnfcignc), QEMU_G2H(c->pfnfcis), QEMU_G2H(c->pfnfcigoi), c->typeCompress);
}

#endif

struct qemu_FCIFlushFolder
{
    struct qemu_syscall super;
    uint64_t hfci;
    uint64_t pfnfcignc;
    uint64_t pfnfcis;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL FCIFlushFolder(HFCI hfci, PFNFCIGETNEXTCABINET pfnfcignc, PFNFCISTATUS pfnfcis)
{
    struct qemu_FCIFlushFolder call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FCIFLUSHFOLDER);
    call.hfci = (ULONG_PTR)hfci;
    call.pfnfcignc = (ULONG_PTR)pfnfcignc;
    call.pfnfcis = (ULONG_PTR)pfnfcis;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FCIFlushFolder(struct qemu_syscall *call)
{
    struct qemu_FCIFlushFolder *c = (struct qemu_FCIFlushFolder *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FCIFlushFolder(QEMU_G2H(c->hfci), QEMU_G2H(c->pfnfcignc), QEMU_G2H(c->pfnfcis));
}

#endif

struct qemu_FCIFlushCabinet
{
    struct qemu_syscall super;
    uint64_t hfci;
    uint64_t fGetNextCab;
    uint64_t pfnfcignc;
    uint64_t pfnfcis;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL FCIFlushCabinet(HFCI hfci, BOOL fGetNextCab, PFNFCIGETNEXTCABINET pfnfcignc, PFNFCISTATUS pfnfcis)
{
    struct qemu_FCIFlushCabinet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FCIFLUSHCABINET);
    call.hfci = (ULONG_PTR)hfci;
    call.fGetNextCab = fGetNextCab;
    call.pfnfcignc = (ULONG_PTR)pfnfcignc;
    call.pfnfcis = (ULONG_PTR)pfnfcis;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FCIFlushCabinet(struct qemu_syscall *call)
{
    struct qemu_FCIFlushCabinet *c = (struct qemu_FCIFlushCabinet *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FCIFlushCabinet(QEMU_G2H(c->hfci), c->fGetNextCab, QEMU_G2H(c->pfnfcignc), QEMU_G2H(c->pfnfcis));
}

#endif

struct qemu_FCIDestroy
{
    struct qemu_syscall super;
    uint64_t hfci;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL CDECL FCIDestroy(HFCI hfci)
{
    struct qemu_FCIDestroy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FCIDESTROY);
    call.hfci = (ULONG_PTR)hfci;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FCIDestroy(struct qemu_syscall *call)
{
    struct qemu_FCIDestroy *c = (struct qemu_FCIDestroy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FCIDestroy(QEMU_G2H(c->hfci));
}

#endif

