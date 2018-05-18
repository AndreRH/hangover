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

struct FCI_alloc_cb
{
    uint64_t func;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

void * __fastcall fci_alloc_guest(struct FCI_alloc_cb *call)
{
    PFNFCIALLOC fn = (PFNFCIALLOC)(ULONG_PTR)call->func;
    return fn(call->size);
}

WINBASEAPI HFCI CDECL FCICreate(PERF perf, PFNFCIFILEPLACED pfnfiledest, PFNFCIALLOC pfnalloc, PFNFCIFREE pfnfree,
        PFNFCIOPEN pfnopen, PFNFCIREAD pfnread, PFNFCIWRITE pfnwrite, PFNFCICLOSE pfnclose, PFNFCISEEK pfnseek,
        PFNFCIDELETE pfndelete, PFNFCIGETTEMPFILE pfnfcigtf, PCCAB pccab, void *pv)
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

static int CDECL host_dest(PCCAB pccab, char *pszFile, LONG cbFile,
        BOOL fContinuation, void *pv)
{
    struct qemu_fci *fci = TlsGetValue(cabinet_tls);
    WINE_FIXME("Not implemented\n");
    return 0;
}

static void * CDECL host_alloc(ULONG cb)
{
    struct qemu_fci *fci = TlsGetValue(cabinet_tls);
    uint64_t ret;
    struct FCI_alloc_cb call;

    WINE_TRACE("Calling guest callback %p(0x%x).\n", (void *)fci->alloc, cb);
    call.func = fci->alloc;
    call.size = cb;
    ret = qemu_ops->qemu_execute(QEMU_G2H(fci_alloc_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned %p.\n", (void *)ret);

    return QEMU_G2H(ret);
}

static void CDECL host_free(void *memory)
{
    struct qemu_fci *fci = TlsGetValue(cabinet_tls);
    WINE_FIXME("Not implemented\n");
}

static INT_PTR CDECL host_open(char *pszFile, int oflag, int pmode, int *err, void *pv)
{
    struct qemu_fci *fci = TlsGetValue(cabinet_tls);
    WINE_FIXME("Not implemented\n");
    return 0;
}

static UINT CDECL host_read(INT_PTR hf, void *memory, UINT cb, int *err, void *pv)
{
    struct qemu_fci *fci = TlsGetValue(cabinet_tls);
    WINE_FIXME("Not implemented\n");
    return 0;
}

static UINT CDECL host_write(INT_PTR hf, void *memory, UINT cb, int *err, void *pv)
{
    struct qemu_fci *fci = TlsGetValue(cabinet_tls);
    WINE_FIXME("Not implemented\n");
    return 0;
}

static int CDECL host_close(INT_PTR hf, int *err, void *pv)
{
    WINE_FIXME("Not implemented\n");
    return 0;
}

static LONG CDECL host_seek(INT_PTR hf, LONG dist, int seektype, int *err, void *pv)
{
    WINE_FIXME("Not implemented\n");
    return 0;
}

static int CDECL host_delete(char *pszFile, int *err, void *pv)
{
    WINE_FIXME("Not implemented\n");
    return 0;
}

static BOOL CDECL host_temp(char *pszTempName, int cbTempName, void *pv)
{
    WINE_FIXME("Not implemented\n");
    return 0;
}

void qemu_FCICreate(struct qemu_syscall *call)
{
    struct qemu_FCICreate *c = (struct qemu_FCICreate *)call;
    struct qemu_fci *fci;
    struct qemu_fci *old_tls = TlsGetValue(cabinet_tls);

    WINE_TRACE("\n");
    fci = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*fci));
    if (!fci)
        WINE_ERR("Out of memory\n");

    fci->dest = c->pfnfiledest;
    fci->alloc = c->pfnalloc;
    fci->free = c->pfnfree;
    fci->open = c->pfnopen;
    fci->read = c->pfnread;
    fci->write = c->pfnwrite;
    fci->close = c->pfnclose;
    fci->seek = c->pfnfcigtf;
    fci->del = c->pfndelete;
    fci->temp = c->pfnfcigtf;

    TlsSetValue(cabinet_tls, fci);

    fci->host = FCICreate(QEMU_G2H(c->perf), c->pfnfiledest ? host_dest : NULL, c->pfnalloc ? host_alloc : NULL,
            c->pfnfree ? host_free : NULL, c->pfnopen ? host_open : NULL, c->pfnread ? host_read : NULL,
            c->pfnwrite ? host_write : NULL, c->pfnclose ? host_close : NULL, c->pfnseek ? host_seek : NULL,
            c->pfndelete ? host_delete : NULL, c->pfnfcigtf ? host_temp : NULL, QEMU_G2H(c->pccab), QEMU_G2H(c->pv));

    TlsSetValue(cabinet_tls, old_tls);

    if (!fci->host)
    {
        HeapFree(GetProcessHeap(), 0, fci);
        fci = NULL;
    }

    c->super.iret = QEMU_H2G(fci);
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
    struct qemu_fci *fci;

    WINE_FIXME("Unverified!\n");
    fci = QEMU_G2H(c->hfci);
    c->super.iret = FCIAddFile(fci->host, QEMU_G2H(c->pszSourceFile), QEMU_G2H(c->pszFileName), c->fExecute, QEMU_G2H(c->pfnfcignc), QEMU_G2H(c->pfnfcis), QEMU_G2H(c->pfnfcigoi), c->typeCompress);
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
    struct qemu_fci *fci;

    WINE_FIXME("Unverified!\n");
    fci = QEMU_G2H(c->hfci);
    c->super.iret = FCIFlushCabinet(fci->host, c->fGetNextCab, QEMU_G2H(c->pfnfcignc), QEMU_G2H(c->pfnfcis));
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
    struct qemu_fci *fci;

    WINE_FIXME("Unverified!\n");
    fci = QEMU_G2H(c->hfci);
    c->super.iret = FCIDestroy(fci->host);
    HeapFree(GetProcessHeap(), 0, fci);
}

#endif

