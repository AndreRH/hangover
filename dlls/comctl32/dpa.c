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
#include <commctrl.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_comctl32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comctl32);
#endif


struct qemu_DPA_LoadStream
{
    struct qemu_syscall super;
    uint64_t phDpa;
    uint64_t loadProc;
    uint64_t pStream;
    uint64_t pData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DPA_LoadStream (HDPA *phDpa, PFNDPASTREAM loadProc, IStream *pStream, LPVOID pData)
{
    struct qemu_DPA_LoadStream call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_LOADSTREAM);
    call.phDpa = (ULONG_PTR)phDpa;
    call.loadProc = (ULONG_PTR)loadProc;
    call.pStream = (ULONG_PTR)pStream;
    call.pData = (ULONG_PTR)pData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DPA_LoadStream(struct qemu_syscall *call)
{
    struct qemu_DPA_LoadStream *c = (struct qemu_DPA_LoadStream *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DPA_LoadStream(QEMU_G2H(c->phDpa), QEMU_G2H(c->loadProc), QEMU_G2H(c->pStream), QEMU_G2H(c->pData));
}

#endif

struct qemu_DPA_SaveStream
{
    struct qemu_syscall super;
    uint64_t hDpa;
    uint64_t saveProc;
    uint64_t pStream;
    uint64_t pData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DPA_SaveStream (HDPA hDpa, PFNDPASTREAM saveProc, IStream *pStream, LPVOID pData)
{
    struct qemu_DPA_SaveStream call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_SAVESTREAM);
    call.hDpa = (ULONG_PTR)hDpa;
    call.saveProc = (ULONG_PTR)saveProc;
    call.pStream = (ULONG_PTR)pStream;
    call.pData = (ULONG_PTR)pData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DPA_SaveStream(struct qemu_syscall *call)
{
    struct qemu_DPA_SaveStream *c = (struct qemu_DPA_SaveStream *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DPA_SaveStream(QEMU_G2H(c->hDpa), QEMU_G2H(c->saveProc), QEMU_G2H(c->pStream), QEMU_G2H(c->pData));
}

#endif

struct qemu_DPA_Merge
{
    struct qemu_syscall super;
    uint64_t hdpa1;
    uint64_t hdpa2;
    uint64_t dwFlags;
    uint64_t pfnCompare;
    uint64_t pfnMerge;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DPA_Merge (HDPA hdpa1, HDPA hdpa2, DWORD dwFlags, PFNDPACOMPARE pfnCompare, PFNDPAMERGE pfnMerge, LPARAM lParam)
{
    struct qemu_DPA_Merge call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_MERGE);
    call.hdpa1 = (ULONG_PTR)hdpa1;
    call.hdpa2 = (ULONG_PTR)hdpa2;
    call.dwFlags = dwFlags;
    call.pfnCompare = (ULONG_PTR)pfnCompare;
    call.pfnMerge = (ULONG_PTR)pfnMerge;
    call.lParam = lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DPA_Merge(struct qemu_syscall *call)
{
    struct qemu_DPA_Merge *c = (struct qemu_DPA_Merge *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DPA_Merge(QEMU_G2H(c->hdpa1), QEMU_G2H(c->hdpa2), c->dwFlags, QEMU_G2H(c->pfnCompare), QEMU_G2H(c->pfnMerge), c->lParam);
}

#endif

struct qemu_DPA_Destroy
{
    struct qemu_syscall super;
    uint64_t hdpa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DPA_Destroy (HDPA hdpa)
{
    struct qemu_DPA_Destroy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_DESTROY);
    call.hdpa = (ULONG_PTR)hdpa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DPA_Destroy(struct qemu_syscall *call)
{
    struct qemu_DPA_Destroy *c = (struct qemu_DPA_Destroy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DPA_Destroy(QEMU_G2H(c->hdpa));
}

#endif

struct qemu_DPA_Grow
{
    struct qemu_syscall super;
    uint64_t hdpa;
    uint64_t nGrow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DPA_Grow (HDPA hdpa, INT nGrow)
{
    struct qemu_DPA_Grow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_GROW);
    call.hdpa = (ULONG_PTR)hdpa;
    call.nGrow = nGrow;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DPA_Grow(struct qemu_syscall *call)
{
    struct qemu_DPA_Grow *c = (struct qemu_DPA_Grow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DPA_Grow(QEMU_G2H(c->hdpa), c->nGrow);
}

#endif

struct qemu_DPA_Clone
{
    struct qemu_syscall super;
    uint64_t hdpa;
    uint64_t hdpaNew;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDPA WINAPI DPA_Clone (const HDPA hdpa, HDPA hdpaNew)
{
    struct qemu_DPA_Clone call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_CLONE);
    call.hdpa = (ULONG_PTR)hdpa;
    call.hdpaNew = (ULONG_PTR)hdpaNew;

    qemu_syscall(&call.super);

    return (HDPA)(ULONG_PTR)call.super.iret;
}

#else

extern HDPA WINAPI DPA_Clone (const HDPA hdpa, HDPA hdpaNew);
void qemu_DPA_Clone(struct qemu_syscall *call)
{
    struct qemu_DPA_Clone *c = (struct qemu_DPA_Clone *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(DPA_Clone(QEMU_G2H(c->hdpa), QEMU_G2H(c->hdpaNew)));
}

#endif

struct qemu_DPA_GetPtr
{
    struct qemu_syscall super;
    uint64_t hdpa;
    uint64_t nIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI DPA_GetPtr (HDPA hdpa, INT_PTR nIndex)
{
    struct qemu_DPA_GetPtr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_GETPTR);
    call.hdpa = (ULONG_PTR)hdpa;
    call.nIndex = nIndex;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DPA_GetPtr(struct qemu_syscall *call)
{
    struct qemu_DPA_GetPtr *c = (struct qemu_DPA_GetPtr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DPA_GetPtr(QEMU_G2H(c->hdpa), c->nIndex);
}

#endif

struct qemu_DPA_GetPtrIndex
{
    struct qemu_syscall super;
    uint64_t hdpa;
    uint64_t p;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI DPA_GetPtrIndex (HDPA hdpa, LPCVOID p)
{
    struct qemu_DPA_GetPtrIndex call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_GETPTRINDEX);
    call.hdpa = (ULONG_PTR)hdpa;
    call.p = (ULONG_PTR)p;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DPA_GetPtrIndex(struct qemu_syscall *call)
{
    struct qemu_DPA_GetPtrIndex *c = (struct qemu_DPA_GetPtrIndex *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DPA_GetPtrIndex(QEMU_G2H(c->hdpa), QEMU_G2H(c->p));
}

#endif

struct qemu_DPA_InsertPtr
{
    struct qemu_syscall super;
    uint64_t hdpa;
    uint64_t i;
    uint64_t p;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI DPA_InsertPtr (HDPA hdpa, INT i, LPVOID p)
{
    struct qemu_DPA_InsertPtr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_INSERTPTR);
    call.hdpa = (ULONG_PTR)hdpa;
    call.i = i;
    call.p = (ULONG_PTR)p;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DPA_InsertPtr(struct qemu_syscall *call)
{
    struct qemu_DPA_InsertPtr *c = (struct qemu_DPA_InsertPtr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DPA_InsertPtr(QEMU_G2H(c->hdpa), c->i, QEMU_G2H(c->p));
}

#endif

struct qemu_DPA_SetPtr
{
    struct qemu_syscall super;
    uint64_t hdpa;
    uint64_t i;
    uint64_t p;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DPA_SetPtr (HDPA hdpa, INT i, LPVOID p)
{
    struct qemu_DPA_SetPtr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_SETPTR);
    call.hdpa = (ULONG_PTR)hdpa;
    call.i = i;
    call.p = (ULONG_PTR)p;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DPA_SetPtr(struct qemu_syscall *call)
{
    struct qemu_DPA_SetPtr *c = (struct qemu_DPA_SetPtr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DPA_SetPtr(QEMU_G2H(c->hdpa), c->i, QEMU_G2H(c->p));
}

#endif

struct qemu_DPA_DeletePtr
{
    struct qemu_syscall super;
    uint64_t hdpa;
    uint64_t i;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI DPA_DeletePtr (HDPA hdpa, INT i)
{
    struct qemu_DPA_DeletePtr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_DELETEPTR);
    call.hdpa = (ULONG_PTR)hdpa;
    call.i = i;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DPA_DeletePtr(struct qemu_syscall *call)
{
    struct qemu_DPA_DeletePtr *c = (struct qemu_DPA_DeletePtr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)DPA_DeletePtr(QEMU_G2H(c->hdpa), c->i);
}

#endif

struct qemu_DPA_DeleteAllPtrs
{
    struct qemu_syscall super;
    uint64_t hdpa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DPA_DeleteAllPtrs (HDPA hdpa)
{
    struct qemu_DPA_DeleteAllPtrs call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_DELETEALLPTRS);
    call.hdpa = (ULONG_PTR)hdpa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DPA_DeleteAllPtrs(struct qemu_syscall *call)
{
    struct qemu_DPA_DeleteAllPtrs *c = (struct qemu_DPA_DeleteAllPtrs *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DPA_DeleteAllPtrs(QEMU_G2H(c->hdpa));
}

#endif

struct qemu_DPA_Sort
{
    struct qemu_syscall super;
    uint64_t hdpa;
    uint64_t pfnCompare;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DPA_Sort (HDPA hdpa, PFNDPACOMPARE pfnCompare, LPARAM lParam)
{
    struct qemu_DPA_Sort call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_SORT);
    call.hdpa = (ULONG_PTR)hdpa;
    call.pfnCompare = (ULONG_PTR)pfnCompare;
    call.lParam = lParam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DPA_Sort(struct qemu_syscall *call)
{
    struct qemu_DPA_Sort *c = (struct qemu_DPA_Sort *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DPA_Sort(QEMU_G2H(c->hdpa), QEMU_G2H(c->pfnCompare), c->lParam);
}

#endif

struct qemu_DPA_Search
{
    struct qemu_syscall super;
    uint64_t hdpa;
    uint64_t pFind;
    uint64_t nStart;
    uint64_t pfnCompare;
    uint64_t lParam;
    uint64_t uOptions;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI DPA_Search (HDPA hdpa, LPVOID pFind, INT nStart, PFNDPACOMPARE pfnCompare, LPARAM lParam, UINT uOptions)
{
    struct qemu_DPA_Search call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_SEARCH);
    call.hdpa = (ULONG_PTR)hdpa;
    call.pFind = (ULONG_PTR)pFind;
    call.nStart = nStart;
    call.pfnCompare = (ULONG_PTR)pfnCompare;
    call.lParam = lParam;
    call.uOptions = uOptions;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DPA_Search(struct qemu_syscall *call)
{
    struct qemu_DPA_Search *c = (struct qemu_DPA_Search *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DPA_Search(QEMU_G2H(c->hdpa), QEMU_G2H(c->pFind), c->nStart, QEMU_G2H(c->pfnCompare), c->lParam, c->uOptions);
}

#endif

struct qemu_DPA_CreateEx
{
    struct qemu_syscall super;
    uint64_t nGrow;
    uint64_t hHeap;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDPA WINAPI DPA_CreateEx (INT nGrow, HANDLE hHeap)
{
    struct qemu_DPA_CreateEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_CREATEEX);
    call.nGrow = nGrow;
    call.hHeap = (ULONG_PTR)hHeap;

    qemu_syscall(&call.super);

    return (HDPA)(ULONG_PTR)call.super.iret;
}

#else

extern HDPA WINAPI DPA_CreateEx (INT nGrow, HANDLE hHeap);
void qemu_DPA_CreateEx(struct qemu_syscall *call)
{
    struct qemu_DPA_CreateEx *c = (struct qemu_DPA_CreateEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(DPA_CreateEx(c->nGrow, QEMU_G2H(c->hHeap)));
}

#endif

struct qemu_DPA_Create
{
    struct qemu_syscall super;
    uint64_t nGrow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDPA WINAPI DPA_Create (INT nGrow)
{
    struct qemu_DPA_Create call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_CREATE);
    call.nGrow = nGrow;

    qemu_syscall(&call.super);

    return (HDPA)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DPA_Create(struct qemu_syscall *call)
{
    struct qemu_DPA_Create *c = (struct qemu_DPA_Create *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(DPA_Create(c->nGrow));
}

#endif

struct qemu_DPA_EnumCallback
{
    struct qemu_syscall super;
    uint64_t hdpa;
    uint64_t enumProc;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI DPA_EnumCallback (HDPA hdpa, PFNDPAENUMCALLBACK enumProc, LPVOID lParam)
{
    struct qemu_DPA_EnumCallback call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_ENUMCALLBACK);
    call.hdpa = (ULONG_PTR)hdpa;
    call.enumProc = (ULONG_PTR)enumProc;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);
}

#else

void qemu_DPA_EnumCallback(struct qemu_syscall *call)
{
    struct qemu_DPA_EnumCallback *c = (struct qemu_DPA_EnumCallback *)call;
    WINE_FIXME("Unverified!\n");
    DPA_EnumCallback(QEMU_G2H(c->hdpa), QEMU_G2H(c->enumProc), QEMU_G2H(c->lParam));
}

#endif

struct qemu_DPA_DestroyCallback
{
    struct qemu_syscall super;
    uint64_t hdpa;
    uint64_t enumProc;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI DPA_DestroyCallback (HDPA hdpa, PFNDPAENUMCALLBACK enumProc, LPVOID lParam)
{
    struct qemu_DPA_DestroyCallback call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_DESTROYCALLBACK);
    call.hdpa = (ULONG_PTR)hdpa;
    call.enumProc = (ULONG_PTR)enumProc;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);
}

#else

void qemu_DPA_DestroyCallback(struct qemu_syscall *call)
{
    struct qemu_DPA_DestroyCallback *c = (struct qemu_DPA_DestroyCallback *)call;
    WINE_FIXME("Unverified!\n");
    DPA_DestroyCallback(QEMU_G2H(c->hdpa), QEMU_G2H(c->enumProc), QEMU_G2H(c->lParam));
}

#endif

struct qemu_DPA_GetSize
{
    struct qemu_syscall super;
    uint64_t hdpa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONGLONG WINAPI DPA_GetSize(HDPA hdpa)
{
    struct qemu_DPA_GetSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DPA_GETSIZE);
    call.hdpa = (ULONG_PTR)hdpa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DPA_GetSize(struct qemu_syscall *call)
{
    struct qemu_DPA_GetSize *c = (struct qemu_DPA_GetSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DPA_GetSize(QEMU_G2H(c->hdpa));
}

#endif

