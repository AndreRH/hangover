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

struct FCI_free_cb
{
    uint64_t func;
    uint64_t mem;
};

struct FCI_read_cb
{
    uint64_t func;
    uint64_t hf, memory, cb, err, pv;
};

struct FCI_close_cb
{
    uint64_t func;
    uint64_t hf, err, pv;

};

struct FCI_dest_cb
{
    uint64_t func;
    uint64_t cab, file, cb, cont, pv;

};

struct FCI_open_cb
{
    uint64_t func;
    uint64_t file, flag, mode, err, pv;
};

struct FCI_temp_cb
{
    uint64_t func;
    uint64_t name, cb, pv;
};

struct FCI_delete_cb
{
    uint64_t func;
    uint64_t name, err, pv;
};

struct FCI_seek_cb
{
    uint64_t func;
    uint64_t hf, dist, type, err, pv;
};

#ifdef QEMU_DLL_GUEST

void * __fastcall fci_alloc_guest(struct FCI_alloc_cb *call)
{
    PFNFCIALLOC fn = (PFNFCIALLOC)(ULONG_PTR)call->func;
    return fn(call->size);
}

void __fastcall fci_free_guest(struct FCI_free_cb *call)
{
    PFNFCIFREE fn = (PFNFCIFREE)(ULONG_PTR)call->func;
    fn((void *)(ULONG_PTR)call->mem);
}

UINT __fastcall fci_readwrite_guest(struct FCI_read_cb *call)
{
    PFNFCIREAD fn = (PFNFCIREAD)(ULONG_PTR)call->func;
    return fn(call->hf, (void *)(ULONG_PTR)call->memory, call->cb, (int *)(ULONG_PTR)call->err,
            (void *)(ULONG_PTR)call->pv);
}

int __fastcall fci_close_guest(struct FCI_close_cb *call)
{
    PFNFCICLOSE fn = (PFNFCICLOSE)(ULONG_PTR)call->func;
    return fn(call->hf, (int *)(ULONG_PTR)call->err, (void *)(ULONG_PTR)call->pv);
}

int __fastcall fci_dest_guest(struct FCI_dest_cb *call)
{
    PFNFCIFILEPLACED fn = (PFNFCIFILEPLACED)(ULONG_PTR)call->func;
    return fn((CCAB *)(ULONG_PTR)call->cab, (char *)(ULONG_PTR)call->file, call->cb, call->cont,
            (void *)(ULONG_PTR)call->pv);
}

INT_PTR __fastcall fci_open_guest(struct FCI_open_cb *call)
{
    PFNFCIOPEN fn = (PFNFCIOPEN)(ULONG_PTR)call->func;
    return fn((char *)(ULONG_PTR)call->file, call->flag, call->mode, (int *)(ULONG_PTR)call->err,
            (void *)(ULONG_PTR)call->pv);
}

BOOL __fastcall fci_temp_guest(struct FCI_temp_cb *call)
{
    PFNFCIGETTEMPFILE fn = (PFNFCIGETTEMPFILE)(ULONG_PTR)call->func;
    return fn((char *)(ULONG_PTR)call->name, call->cb, (void *)(ULONG_PTR)call->pv);
}

int __fastcall fci_delete_guest(struct FCI_delete_cb *call)
{
    PFNFCIDELETE fn = (PFNFCIDELETE)(ULONG_PTR)call->func;
    return fn((char *)(ULONG_PTR)call->name, (int *)(ULONG_PTR)call->err, (void *)(ULONG_PTR)call->pv);
}

LONG __fastcall fci_seek_guest(struct FCI_seek_cb *call)
{
    PFNFCISEEK fn = (PFNFCISEEK)(ULONG_PTR)call->func;
    return fn(call->hf, call->dist, call->type, (int *)(ULONG_PTR)call->err, (void *)(ULONG_PTR)call->pv);
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
    struct qemu_fxi *fci = cabinet_tls;
    struct FCI_dest_cb call;
    int ret;

    call.func = fci->dest;
    call.cab = QEMU_H2G(pccab);
    call.file = QEMU_H2G(pszFile);
    call.cb = cbFile;
    call.cont = fContinuation;
    call.pv = QEMU_H2G(pv);

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fci_dest_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", ret);

    return ret;
}

void * CDECL host_alloc(ULONG cb)
{
    struct qemu_fxi *fci = cabinet_tls;
    uint64_t ret;
    struct FCI_alloc_cb call;

    WINE_TRACE("Calling guest callback %p(0x%x).\n", (void *)fci->alloc, cb);
    call.func = fci->alloc;
    call.size = cb;
    ret = qemu_ops->qemu_execute(QEMU_G2H(fci_alloc_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned %p.\n", (void *)ret);

    return QEMU_G2H(ret);
}

void CDECL host_free(void *memory)
{
    struct qemu_fxi *fci = cabinet_tls;
    struct FCI_free_cb call;

    WINE_TRACE("Calling guest callback %p(%p).\n", (void *)fci->free, memory);
    call.func = fci->free;
    call.mem = QEMU_H2G(memory);
    qemu_ops->qemu_execute(QEMU_G2H(fci_free_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned.\n");
}

static INT_PTR CDECL host_open(char *pszFile, int oflag, int pmode, int *err, void *pv)
{
    struct qemu_fxi *fci = cabinet_tls;
    struct FCI_open_cb call;
    UINT ret;

    call.func = fci->open;
    call.file = QEMU_H2G(pszFile);
    call.flag = oflag;
    call.mode = pmode;
    call.err = QEMU_H2G(err);
    call.pv = QEMU_H2G(pv);

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fci_open_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", ret);

    return ret;
}

static UINT CDECL host_read(INT_PTR hf, void *memory, UINT cb, int *err, void *pv)
{
    struct qemu_fxi *fci = cabinet_tls;
    struct FCI_read_cb call;
    UINT ret;

    call.func = fci->read;
    call.hf = hf;
    call.memory = QEMU_H2G(memory);
    call.cb = cb;
    call.err = QEMU_H2G(err);
    call.pv = QEMU_H2G(pv);

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fci_readwrite_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x, in len %x.\n", ret, cb);

    return ret;
}

static UINT CDECL host_write(INT_PTR hf, void *memory, UINT cb, int *err, void *pv)
{
    struct qemu_fxi *fci = cabinet_tls;
    struct FCI_read_cb call;
    UINT ret;

    call.func = fci->write;
    call.hf = hf;
    call.memory = QEMU_H2G(memory);
    call.cb = cb;
    call.err = QEMU_H2G(err);
    call.pv = QEMU_H2G(pv);

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fci_readwrite_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", ret);

    return ret;
}

static int CDECL host_close(INT_PTR hf, int *err, void *pv)
{
    struct qemu_fxi *fci = cabinet_tls;
    struct FCI_close_cb call;
    int ret;

    call.func = fci->read;
    call.hf = hf;
    call.err = QEMU_H2G(err);
    call.pv = QEMU_H2G(pv);

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fci_close_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", ret);

    return ret;
}

static LONG CDECL host_seek(INT_PTR hf, LONG dist, int seektype, int *err, void *pv)
{
    struct qemu_fxi *fci = cabinet_tls;
    struct FCI_seek_cb call;
    LONG ret;

    call.func = fci->seek;
    call.hf = hf;
    call.dist = dist;
    call.type = seektype;
    call.err = QEMU_H2G(err);
    call.pv = QEMU_H2G(pv);

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fci_seek_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", ret);

    return ret;
}

static int CDECL host_delete(char *pszFile, int *err, void *pv)
{
    struct qemu_fxi *fci = cabinet_tls;
    struct FCI_delete_cb call;
    BOOL ret;

    call.func = fci->temp;
    call.name = QEMU_H2G(pszFile);
    call.err = QEMU_H2G(err);
    call.pv = QEMU_H2G(pv);

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fci_delete_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", ret);

    return ret;
}

static BOOL CDECL host_temp(char *pszTempName, int cbTempName, void *pv)
{
    struct qemu_fxi *fci = cabinet_tls;
    struct FCI_temp_cb call;
    BOOL ret;

    call.func = fci->temp;
    call.name = QEMU_H2G(pszTempName);
    call.cb = cbTempName;
    call.pv = QEMU_H2G(pv);

    WINE_TRACE("Calling guest\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fci_temp_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", ret);

    return ret;
}

void qemu_FCICreate(struct qemu_syscall *call)
{
    struct qemu_FCICreate *c = (struct qemu_FCICreate *)call;
    struct qemu_fxi *fci;
    struct qemu_fxi *old_tls = cabinet_tls;

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
    fci->seek = c->pfnseek;
    fci->del = c->pfndelete;
    fci->temp = c->pfnfcigtf;

    cabinet_tls = fci;

    /* ERF and CCAB are compatible between 32 and 64 bit. */
    fci->host.fci = FCICreate(QEMU_G2H(c->perf), c->pfnfiledest ? host_dest : NULL, c->pfnalloc ? host_alloc : NULL,
            c->pfnfree ? host_free : NULL, c->pfnopen ? host_open : NULL, c->pfnread ? host_read : NULL,
            c->pfnwrite ? host_write : NULL, c->pfnclose ? host_close : NULL, c->pfnseek ? host_seek : NULL,
            c->pfndelete ? host_delete : NULL, c->pfnfcigtf ? host_temp : NULL, QEMU_G2H(c->pccab), QEMU_G2H(c->pv));

    cabinet_tls = old_tls;

    if (!fci->host.fci)
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

struct FCI_open_info_cb
{
    uint64_t func;
    uint64_t name, date, time, attribs, err, pv;
};

struct FCI_progress_cb
{
    uint64_t func;
    uint64_t type, cb1, cb2, pv;
};

#ifdef QEMU_DLL_GUEST

INT_PTR __fastcall fci_open_info_guest(struct FCI_open_info_cb *call)
{
    PFNFCIGETOPENINFO func = (PFNFCIGETOPENINFO)(ULONG_PTR)call->func;
    return func((char *)(ULONG_PTR)call->name, (USHORT *)(ULONG_PTR)call->date, (USHORT *)(ULONG_PTR)call->time,
            (USHORT *)(ULONG_PTR)call->attribs, (int *)(ULONG_PTR)call->err, (void *)(ULONG_PTR)call->pv);
}

LONG __fastcall fci_progress_guest(struct FCI_progress_cb *call)
{
    PFNFCISTATUS fn = (PFNFCISTATUS)(ULONG_PTR)call->func;
    return fn(call->type, call->cb1, call->cb2, (void *)(ULONG_PTR)call->pv);
}

WINBASEAPI BOOL CDECL FCIAddFile(HFCI hfci, char *pszSourceFile, char *pszFileName, BOOL fExecute,
        PFNFCIGETNEXTCABINET pfnfcignc, PFNFCISTATUS pfnfcis, PFNFCIGETOPENINFO pfnfcigoi, TCOMP typeCompress)
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

static BOOL CDECL host_next(PCCAB pccab, ULONG  cbPrevCab, void *pv)
{
    WINE_FIXME("Unimplemented\n");
    return TRUE;
}

static LONG CDECL host_progress(UINT typeStatus, ULONG cb1, ULONG cb2, void *pv)
{
    struct qemu_fxi *fci = cabinet_tls;
    struct FCI_progress_cb call;
    LONG ret;

    call.func = fci->progress;
    call.type = typeStatus;
    call.cb1 = cb1;
    call.cb2 = cb2;
    call.pv = QEMU_H2G(pv);

    WINE_TRACE("Calling guest callback.\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fci_progress_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned 0x%x.\n", ret);

    return ret;
}

static INT_PTR CDECL host_open_info(char *pszName, USHORT *pdate, USHORT *ptime,
        USHORT *pattribs, int *err, void *pv)
{
    struct FCI_open_info_cb call;
    struct qemu_fxi *fci = cabinet_tls;
    INT_PTR ret;

    call.func = fci->open_info;
    call.name = QEMU_H2G(pszName);
    call.date = QEMU_H2G(pdate);
    call.time = QEMU_H2G(ptime);
    call.attribs = QEMU_H2G(pattribs);
    call.err = QEMU_H2G(err);
    call.pv = QEMU_H2G(pv);

    WINE_TRACE("Calling host callback with many parameters.\n");
    ret = qemu_ops->qemu_execute(QEMU_G2H(fci_open_info_guest), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned %p.\n", (void *)ret);

    return ret;
}

void qemu_FCIAddFile(struct qemu_syscall *call)
{
    struct qemu_FCIAddFile *c = (struct qemu_FCIAddFile *)call;
    struct qemu_fxi *fci;
    struct qemu_fxi *old_tls = cabinet_tls;
    uint64_t old_open_info, old_progress;

    WINE_TRACE("\n");

    fci = QEMU_G2H(c->hfci);
    old_open_info = fci->open_info;
    old_progress = fci->progress;
    fci->open_info = c->pfnfcigoi;
    fci->progress = c->pfnfcis;

    cabinet_tls = fci;

    c->super.iret = FCIAddFile(fci->host.fci, QEMU_G2H(c->pszSourceFile), QEMU_G2H(c->pszFileName), c->fExecute, 
            c->pfnfcignc ? host_next : NULL, c->pfnfcis ? host_progress : NULL,
            c->pfnfcigoi ? host_open_info : NULL, c->typeCompress);

    cabinet_tls = old_tls;
    fci->open_info = old_open_info;
    fci->progress = old_progress;
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
    struct qemu_fxi *fci;
    struct qemu_fxi *old_tls = cabinet_tls;
    uint64_t old_progress;

    WINE_TRACE("\n");
    fci = QEMU_G2H(c->hfci);
    old_progress = fci->progress;
    fci->progress = c->pfnfcis;

    cabinet_tls = fci;

    c->super.iret = FCIFlushCabinet(fci->host.fci, c->fGetNextCab, c->pfnfcignc ? host_next : NULL,
            c->pfnfcis ? host_progress : NULL);

    cabinet_tls = old_tls;

    fci->progress = old_progress;
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
    struct qemu_fxi *fci;
    struct qemu_fxi *old_tls = cabinet_tls;

    WINE_TRACE("\n");
    fci = QEMU_G2H(c->hfci);

    cabinet_tls = fci;

    c->super.iret = FCIDestroy(fci->host.fci);
    if (c->super.iret)
        HeapFree(GetProcessHeap(), 0, fci);

    cabinet_tls = old_tls;
}

#endif

