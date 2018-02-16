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


struct qemu_DSA_Create
{
    struct qemu_syscall super;
    uint64_t nSize;
    uint64_t nGrow;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDSA WINAPI DSA_Create (INT nSize, INT nGrow)
{
    struct qemu_DSA_Create call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DSA_CREATE);
    call.nSize = nSize;
    call.nGrow = nGrow;

    qemu_syscall(&call.super);

    return (HDSA)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DSA_Create(struct qemu_syscall *call)
{
    struct qemu_DSA_Create *c = (struct qemu_DSA_Create *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)p_DSA_Create(c->nSize, c->nGrow);
}

#endif

struct qemu_DSA_Destroy
{
    struct qemu_syscall super;
    uint64_t hdsa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DSA_Destroy (HDSA hdsa)
{
    struct qemu_DSA_Destroy call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DSA_DESTROY);
    call.hdsa = (ULONG_PTR)hdsa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DSA_Destroy(struct qemu_syscall *call)
{
    struct qemu_DSA_Destroy *c = (struct qemu_DSA_Destroy *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DSA_Destroy(QEMU_G2H(c->hdsa));
}

#endif

struct qemu_DSA_GetItem
{
    struct qemu_syscall super;
    uint64_t hdsa;
    uint64_t nIndex;
    uint64_t pDest;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DSA_GetItem (HDSA hdsa, INT nIndex, LPVOID pDest)
{
    struct qemu_DSA_GetItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DSA_GETITEM);
    call.hdsa = (ULONG_PTR)hdsa;
    call.nIndex = nIndex;
    call.pDest = (ULONG_PTR)pDest;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI DSA_GetItem (HDSA hdsa, INT nIndex, LPVOID pDest);
void qemu_DSA_GetItem(struct qemu_syscall *call)
{
    struct qemu_DSA_GetItem *c = (struct qemu_DSA_GetItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DSA_GetItem(QEMU_G2H(c->hdsa), c->nIndex, QEMU_G2H(c->pDest));
}

#endif

struct qemu_DSA_GetItemPtr
{
    struct qemu_syscall super;
    uint64_t hdsa;
    uint64_t nIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI DSA_GetItemPtr (HDSA hdsa, INT nIndex)
{
    struct qemu_DSA_GetItemPtr call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DSA_GETITEMPTR);
    call.hdsa = (ULONG_PTR)hdsa;
    call.nIndex = nIndex;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_DSA_GetItemPtr(struct qemu_syscall *call)
{
    struct qemu_DSA_GetItemPtr *c = (struct qemu_DSA_GetItemPtr *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)p_DSA_GetItemPtr(QEMU_G2H(c->hdsa), c->nIndex);
}

#endif

struct qemu_DSA_SetItem
{
    struct qemu_syscall super;
    uint64_t hdsa;
    uint64_t nIndex;
    uint64_t pSrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI WINBOOL WINAPI DSA_SetItem (HDSA hdsa, int nIndex, const void *pSrc)
{
    struct qemu_DSA_SetItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DSA_SETITEM);
    call.hdsa = (ULONG_PTR)hdsa;
    call.nIndex = nIndex;
    call.pSrc = (ULONG_PTR)pSrc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI DSA_SetItem (HDSA hdsa, int nIndex, const void *pSrc);
void qemu_DSA_SetItem(struct qemu_syscall *call)
{
    struct qemu_DSA_SetItem *c = (struct qemu_DSA_SetItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DSA_SetItem(QEMU_G2H(c->hdsa), c->nIndex, QEMU_G2H(c->pSrc));
}

#endif

struct qemu_DSA_InsertItem
{
    struct qemu_syscall super;
    uint64_t hdsa;
    uint64_t nIndex;
    uint64_t pSrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI DSA_InsertItem (HDSA hdsa, int nIndex, const void *pSrc)
{
    struct qemu_DSA_InsertItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DSA_INSERTITEM);
    call.hdsa = (ULONG_PTR)hdsa;
    call.nIndex = nIndex;
    call.pSrc = (ULONG_PTR)pSrc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DSA_InsertItem(struct qemu_syscall *call)
{
    struct qemu_DSA_InsertItem *c = (struct qemu_DSA_InsertItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DSA_InsertItem(QEMU_G2H(c->hdsa), c->nIndex, QEMU_G2H(c->pSrc));
}

#endif

struct qemu_DSA_DeleteItem
{
    struct qemu_syscall super;
    uint64_t hdsa;
    uint64_t nIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI DSA_DeleteItem (HDSA hdsa, INT nIndex)
{
    struct qemu_DSA_DeleteItem call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DSA_DELETEITEM);
    call.hdsa = (ULONG_PTR)hdsa;
    call.nIndex = nIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern INT WINAPI DSA_DeleteItem (HDSA hdsa, INT nIndex);
void qemu_DSA_DeleteItem(struct qemu_syscall *call)
{
    struct qemu_DSA_DeleteItem *c = (struct qemu_DSA_DeleteItem *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DSA_DeleteItem(QEMU_G2H(c->hdsa), c->nIndex);
}

#endif

struct qemu_DSA_DeleteAllItems
{
    struct qemu_syscall super;
    uint64_t hdsa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DSA_DeleteAllItems (HDSA hdsa)
{
    struct qemu_DSA_DeleteAllItems call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DSA_DELETEALLITEMS);
    call.hdsa = (ULONG_PTR)hdsa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern BOOL WINAPI DSA_DeleteAllItems (HDSA hdsa);
void qemu_DSA_DeleteAllItems(struct qemu_syscall *call)
{
    struct qemu_DSA_DeleteAllItems *c = (struct qemu_DSA_DeleteAllItems *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DSA_DeleteAllItems(QEMU_G2H(c->hdsa));
}

#endif

struct qemu_DSA_EnumCallback
{
    struct qemu_syscall super;
    uint64_t hdsa;
    uint64_t enumProc;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI VOID WINAPI DSA_EnumCallback (HDSA hdsa, PFNDSAENUMCALLBACK enumProc, LPVOID lParam)
{
    struct qemu_DSA_EnumCallback call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DSA_ENUMCALLBACK);
    call.hdsa = (ULONG_PTR)hdsa;
    call.enumProc = (ULONG_PTR)enumProc;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);
}

#else

extern VOID WINAPI DSA_EnumCallback (HDSA hdsa, PFNDSAENUMCALLBACK enumProc, LPVOID lParam);
void qemu_DSA_EnumCallback(struct qemu_syscall *call)
{
    struct qemu_DSA_EnumCallback *c = (struct qemu_DSA_EnumCallback *)call;
    WINE_FIXME("Unverified!\n");
    p_DSA_EnumCallback(QEMU_G2H(c->hdsa), QEMU_G2H(c->enumProc), QEMU_G2H(c->lParam));
}

#endif

struct qemu_DSA_DestroyCallback
{
    struct qemu_syscall super;
    uint64_t hdsa;
    uint64_t enumProc;
    uint64_t lParam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI DSA_DestroyCallback (HDSA hdsa, PFNDSAENUMCALLBACK enumProc, LPVOID lParam)
{
    struct qemu_DSA_DestroyCallback call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DSA_DESTROYCALLBACK);
    call.hdsa = (ULONG_PTR)hdsa;
    call.enumProc = (ULONG_PTR)enumProc;
    call.lParam = (ULONG_PTR)lParam;

    qemu_syscall(&call.super);
}

#else

void qemu_DSA_DestroyCallback(struct qemu_syscall *call)
{
    struct qemu_DSA_DestroyCallback *c = (struct qemu_DSA_DestroyCallback *)call;
    WINE_FIXME("Unverified!\n");
    p_DSA_DestroyCallback(QEMU_G2H(c->hdsa), QEMU_G2H(c->enumProc), QEMU_G2H(c->lParam));
}

#endif

struct qemu_DSA_Clone
{
    struct qemu_syscall super;
    uint64_t hdsa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HDSA WINAPI DSA_Clone(HDSA hdsa)
{
    struct qemu_DSA_Clone call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DSA_CLONE);
    call.hdsa = (ULONG_PTR)hdsa;

    qemu_syscall(&call.super);

    return (HDSA)(ULONG_PTR)call.super.iret;
}

#else

extern HDSA WINAPI DSA_Clone(HDSA hdsa);
void qemu_DSA_Clone(struct qemu_syscall *call)
{
    struct qemu_DSA_Clone *c = (struct qemu_DSA_Clone *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)p_DSA_Clone(QEMU_G2H(c->hdsa));
}

#endif

struct qemu_DSA_GetSize
{
    struct qemu_syscall super;
    uint64_t hdsa;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONGLONG WINAPI DSA_GetSize(HDSA hdsa)
{
    struct qemu_DSA_GetSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DSA_GETSIZE);
    call.hdsa = (ULONG_PTR)hdsa;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

extern ULONGLONG WINAPI DSA_GetSize(HDSA hdsa);
void qemu_DSA_GetSize(struct qemu_syscall *call)
{
    struct qemu_DSA_GetSize *c = (struct qemu_DSA_GetSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_DSA_GetSize(QEMU_G2H(c->hdsa));
}

#endif

