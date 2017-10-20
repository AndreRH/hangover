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
#include <shlwapi.h>
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

struct qemu_Shell_GetImageLists
{
    struct qemu_syscall super;
    uint64_t lpBigList;
    uint64_t lpSmallList;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI Shell_GetImageLists(HIMAGELIST * lpBigList, HIMAGELIST * lpSmallList)
{
    struct qemu_Shell_GetImageLists call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHELL_GETIMAGELISTS);
    call.lpBigList = (ULONG_PTR)lpBigList;
    call.lpSmallList = (ULONG_PTR)lpSmallList;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Shell_GetImageLists(struct qemu_syscall *call)
{
    struct qemu_Shell_GetImageLists *c = (struct qemu_Shell_GetImageLists *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = Shell_GetImageLists(QEMU_G2H(c->lpBigList), QEMU_G2H(c->lpSmallList));
}

#endif

struct qemu_SHMapPIDLToSystemImageListIndex
{
    struct qemu_syscall super;
    uint64_t sh;
    uint64_t pidl;
    uint64_t pIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI SHMapPIDLToSystemImageListIndex(IShellFolder *sh, LPCITEMIDLIST pidl, int *pIndex)
{
    struct qemu_SHMapPIDLToSystemImageListIndex call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHMAPPIDLTOSYSTEMIMAGELISTINDEX);
    call.sh = (ULONG_PTR)sh;
    call.pidl = (ULONG_PTR)pidl;
    call.pIndex = (ULONG_PTR)pIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHMapPIDLToSystemImageListIndex(struct qemu_syscall *call)
{
    struct qemu_SHMapPIDLToSystemImageListIndex *c = (struct qemu_SHMapPIDLToSystemImageListIndex *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHMapPIDLToSystemImageListIndex(QEMU_G2H(c->sh), QEMU_G2H(c->pidl), QEMU_G2H(c->pIndex));
}

#endif

struct qemu_SHMapIDListToImageListIndexAsync
{
    struct qemu_syscall super;
    uint64_t pts;
    uint64_t psf;
    uint64_t pidl;
    uint64_t flags;
    uint64_t pfn;
    uint64_t pvData;
    uint64_t pvHint;
    uint64_t piIndex;
    uint64_t piIndexSel;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHMapIDListToImageListIndexAsync(IUnknown *pts, IShellFolder *psf, LPCITEMIDLIST pidl, UINT flags, void *pfn, void *pvData, void *pvHint, int *piIndex, int *piIndexSel)
{
    struct qemu_SHMapIDListToImageListIndexAsync call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHMAPIDLISTTOIMAGELISTINDEXASYNC);
    call.pts = (ULONG_PTR)pts;
    call.psf = (ULONG_PTR)psf;
    call.pidl = (ULONG_PTR)pidl;
    call.flags = flags;
    call.pfn = (ULONG_PTR)pfn;
    call.pvData = (ULONG_PTR)pvData;
    call.pvHint = (ULONG_PTR)pvHint;
    call.piIndex = (ULONG_PTR)piIndex;
    call.piIndexSel = (ULONG_PTR)piIndexSel;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHMapIDListToImageListIndexAsync(struct qemu_syscall *call)
{
    struct qemu_SHMapIDListToImageListIndexAsync *c = (struct qemu_SHMapIDListToImageListIndexAsync *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_SHMapIDListToImageListIndexAsync(QEMU_G2H(c->pts), QEMU_G2H(c->psf), QEMU_G2H(c->pidl), c->flags, QEMU_G2H(c->pfn), QEMU_G2H(c->pvData), QEMU_G2H(c->pvHint), QEMU_G2H(c->piIndex), QEMU_G2H(c->piIndexSel));
}

#endif

struct qemu_Shell_GetCachedImageIndexAW
{
    struct qemu_syscall super;
    uint64_t szPath;
    uint64_t nIndex;
    uint64_t bSimulateDoc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI Shell_GetCachedImageIndexAW(LPCVOID szPath, INT nIndex, BOOL bSimulateDoc)
{
    struct qemu_Shell_GetCachedImageIndexAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHELL_GETCACHEDIMAGEINDEXAW);
    call.szPath = (ULONG_PTR)szPath;
    call.nIndex = nIndex;
    call.bSimulateDoc = bSimulateDoc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Shell_GetCachedImageIndexAW(struct qemu_syscall *call)
{
    struct qemu_Shell_GetCachedImageIndexAW *c = (struct qemu_Shell_GetCachedImageIndexAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_Shell_GetCachedImageIndexAW(QEMU_G2H(c->szPath), c->nIndex, c->bSimulateDoc);
}

#endif

struct qemu_ExtractIconExW
{
    struct qemu_syscall super;
    uint64_t lpszFile;
    uint64_t nIconIndex;
    uint64_t phiconLarge;
    uint64_t phiconSmall;
    uint64_t nIcons;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ExtractIconExW(LPCWSTR lpszFile, INT nIconIndex, HICON * phiconLarge, HICON * phiconSmall, UINT nIcons)
{
    struct qemu_ExtractIconExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTRACTICONEXW);
    call.lpszFile = (ULONG_PTR)lpszFile;
    call.nIconIndex = nIconIndex;
    call.phiconLarge = (ULONG_PTR)phiconLarge;
    call.phiconSmall = (ULONG_PTR)phiconSmall;
    call.nIcons = nIcons;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExtractIconExW(struct qemu_syscall *call)
{
    struct qemu_ExtractIconExW *c = (struct qemu_ExtractIconExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ExtractIconExW(QEMU_G2H(c->lpszFile), c->nIconIndex, QEMU_G2H(c->phiconLarge), QEMU_G2H(c->phiconSmall), c->nIcons);
}

#endif

struct qemu_ExtractIconExA
{
    struct qemu_syscall super;
    uint64_t lpszFile;
    uint64_t nIconIndex;
    uint64_t phiconLarge;
    uint64_t phiconSmall;
    uint64_t nIcons;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ExtractIconExA(LPCSTR lpszFile, INT nIconIndex, HICON * phiconLarge, HICON * phiconSmall, UINT nIcons)
{
    struct qemu_ExtractIconExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTRACTICONEXA);
    call.lpszFile = (ULONG_PTR)lpszFile;
    call.nIconIndex = nIconIndex;
    call.phiconLarge = (ULONG_PTR)phiconLarge;
    call.phiconSmall = (ULONG_PTR)phiconSmall;
    call.nIcons = nIcons;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ExtractIconExA(struct qemu_syscall *call)
{
    struct qemu_ExtractIconExA *c = (struct qemu_ExtractIconExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ExtractIconExA(QEMU_G2H(c->lpszFile), c->nIconIndex, QEMU_G2H(c->phiconLarge), QEMU_G2H(c->phiconSmall), c->nIcons);
}

#endif

struct qemu_ExtractAssociatedIconA
{
    struct qemu_syscall super;
    uint64_t hInst;
    uint64_t lpIconPath;
    uint64_t lpiIcon;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HICON WINAPI ExtractAssociatedIconA(HINSTANCE hInst, LPSTR lpIconPath, LPWORD lpiIcon)
{
    struct qemu_ExtractAssociatedIconA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTRACTASSOCIATEDICONA);
    call.hInst = (ULONG_PTR)hInst;
    call.lpIconPath = (ULONG_PTR)lpIconPath;
    call.lpiIcon = (ULONG_PTR)lpiIcon;

    qemu_syscall(&call.super);

    return (HICON)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ExtractAssociatedIconA(struct qemu_syscall *call)
{
    struct qemu_ExtractAssociatedIconA *c = (struct qemu_ExtractAssociatedIconA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)ExtractAssociatedIconA(QEMU_G2H(c->hInst), QEMU_G2H(c->lpIconPath), QEMU_G2H(c->lpiIcon));
}

#endif

struct qemu_ExtractAssociatedIconW
{
    struct qemu_syscall super;
    uint64_t hInst;
    uint64_t lpIconPath;
    uint64_t lpiIcon;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HICON WINAPI ExtractAssociatedIconW(HINSTANCE hInst, LPWSTR lpIconPath, LPWORD lpiIcon)
{
    struct qemu_ExtractAssociatedIconW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTRACTASSOCIATEDICONW);
    call.hInst = (ULONG_PTR)hInst;
    call.lpIconPath = (ULONG_PTR)lpIconPath;
    call.lpiIcon = (ULONG_PTR)lpiIcon;

    qemu_syscall(&call.super);

    return (HICON)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ExtractAssociatedIconW(struct qemu_syscall *call)
{
    struct qemu_ExtractAssociatedIconW *c = (struct qemu_ExtractAssociatedIconW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)ExtractAssociatedIconW(QEMU_G2H(c->hInst), QEMU_G2H(c->lpIconPath), QEMU_G2H(c->lpiIcon));
}

#endif

struct qemu_ExtractAssociatedIconExW
{
    struct qemu_syscall super;
    uint64_t hInst;
    uint64_t lpIconPath;
    uint64_t lpiIconIdx;
    uint64_t lpiIconId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HICON WINAPI ExtractAssociatedIconExW(HINSTANCE hInst, LPWSTR lpIconPath, LPWORD lpiIconIdx, LPWORD lpiIconId)
{
    struct qemu_ExtractAssociatedIconExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTRACTASSOCIATEDICONEXW);
    call.hInst = (ULONG_PTR)hInst;
    call.lpIconPath = (ULONG_PTR)lpIconPath;
    call.lpiIconIdx = (ULONG_PTR)lpiIconIdx;
    call.lpiIconId = (ULONG_PTR)lpiIconId;

    qemu_syscall(&call.super);

    return (HICON)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ExtractAssociatedIconExW(struct qemu_syscall *call)
{
    struct qemu_ExtractAssociatedIconExW *c = (struct qemu_ExtractAssociatedIconExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)ExtractAssociatedIconExW(QEMU_G2H(c->hInst), QEMU_G2H(c->lpIconPath), QEMU_G2H(c->lpiIconIdx), QEMU_G2H(c->lpiIconId));
}

#endif

struct qemu_ExtractAssociatedIconExA
{
    struct qemu_syscall super;
    uint64_t hInst;
    uint64_t lpIconPath;
    uint64_t lpiIconIdx;
    uint64_t lpiIconId;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HICON WINAPI ExtractAssociatedIconExA(HINSTANCE hInst, LPSTR lpIconPath, LPWORD lpiIconIdx, LPWORD lpiIconId)
{
    struct qemu_ExtractAssociatedIconExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_EXTRACTASSOCIATEDICONEXA);
    call.hInst = (ULONG_PTR)hInst;
    call.lpIconPath = (ULONG_PTR)lpIconPath;
    call.lpiIconIdx = (ULONG_PTR)lpiIconIdx;
    call.lpiIconId = (ULONG_PTR)lpiIconId;

    qemu_syscall(&call.super);

    return (HICON)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ExtractAssociatedIconExA(struct qemu_syscall *call)
{
    struct qemu_ExtractAssociatedIconExA *c = (struct qemu_ExtractAssociatedIconExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)ExtractAssociatedIconExA(QEMU_G2H(c->hInst), QEMU_G2H(c->lpIconPath), QEMU_G2H(c->lpiIconIdx), QEMU_G2H(c->lpiIconId));
}

#endif

struct qemu_SHDefExtractIconW
{
    struct qemu_syscall super;
    uint64_t pszIconFile;
    uint64_t iIndex;
    uint64_t uFlags;
    uint64_t phiconLarge;
    uint64_t phiconSmall;
    uint64_t nIconSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHDefExtractIconW(LPCWSTR pszIconFile, int iIndex, UINT uFlags, HICON* phiconLarge, HICON* phiconSmall, UINT nIconSize)
{
    struct qemu_SHDefExtractIconW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHDEFEXTRACTICONW);
    call.pszIconFile = (ULONG_PTR)pszIconFile;
    call.iIndex = iIndex;
    call.uFlags = uFlags;
    call.phiconLarge = (ULONG_PTR)phiconLarge;
    call.phiconSmall = (ULONG_PTR)phiconSmall;
    call.nIconSize = nIconSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHDefExtractIconW(struct qemu_syscall *call)
{
    struct qemu_SHDefExtractIconW *c = (struct qemu_SHDefExtractIconW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHDefExtractIconW(QEMU_G2H(c->pszIconFile), c->iIndex, c->uFlags, QEMU_G2H(c->phiconLarge), QEMU_G2H(c->phiconSmall), c->nIconSize);
}

#endif

struct qemu_SHDefExtractIconA
{
    struct qemu_syscall super;
    uint64_t pszIconFile;
    uint64_t iIndex;
    uint64_t uFlags;
    uint64_t phiconLarge;
    uint64_t phiconSmall;
    uint64_t nIconSize;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHDefExtractIconA(LPCSTR pszIconFile, int iIndex, UINT uFlags, HICON* phiconLarge, HICON* phiconSmall, UINT nIconSize)
{
    struct qemu_SHDefExtractIconA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHDEFEXTRACTICONA);
    call.pszIconFile = (ULONG_PTR)pszIconFile;
    call.iIndex = iIndex;
    call.uFlags = uFlags;
    call.phiconLarge = (ULONG_PTR)phiconLarge;
    call.phiconSmall = (ULONG_PTR)phiconSmall;
    call.nIconSize = nIconSize;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHDefExtractIconA(struct qemu_syscall *call)
{
    struct qemu_SHDefExtractIconA *c = (struct qemu_SHDefExtractIconA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHDefExtractIconA(QEMU_G2H(c->pszIconFile), c->iIndex, c->uFlags, QEMU_G2H(c->phiconLarge), QEMU_G2H(c->phiconSmall), c->nIconSize);
}

#endif

struct qemu_SHGetIconOverlayIndexA
{
    struct qemu_syscall super;
    uint64_t pszIconPath;
    uint64_t iIconIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI SHGetIconOverlayIndexA(LPCSTR pszIconPath, INT iIconIndex)
{
    struct qemu_SHGetIconOverlayIndexA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETICONOVERLAYINDEXA);
    call.pszIconPath = (ULONG_PTR)pszIconPath;
    call.iIconIndex = iIconIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHGetIconOverlayIndexA to Wine headers? */
extern INT WINAPI SHGetIconOverlayIndexA(LPCSTR pszIconPath, INT iIconIndex);
void qemu_SHGetIconOverlayIndexA(struct qemu_syscall *call)
{
    struct qemu_SHGetIconOverlayIndexA *c = (struct qemu_SHGetIconOverlayIndexA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetIconOverlayIndexA(QEMU_G2H(c->pszIconPath), c->iIconIndex);
}

#endif

struct qemu_SHGetIconOverlayIndexW
{
    struct qemu_syscall super;
    uint64_t pszIconPath;
    uint64_t iIconIndex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT WINAPI SHGetIconOverlayIndexW(LPCWSTR pszIconPath, INT iIconIndex)
{
    struct qemu_SHGetIconOverlayIndexW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETICONOVERLAYINDEXW);
    call.pszIconPath = (ULONG_PTR)pszIconPath;
    call.iIconIndex = iIconIndex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHGetIconOverlayIndexW to Wine headers? */
extern INT WINAPI SHGetIconOverlayIndexW(LPCWSTR pszIconPath, INT iIconIndex);
void qemu_SHGetIconOverlayIndexW(struct qemu_syscall *call)
{
    struct qemu_SHGetIconOverlayIndexW *c = (struct qemu_SHGetIconOverlayIndexW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetIconOverlayIndexW(QEMU_G2H(c->pszIconPath), c->iIconIndex);
}

#endif

struct qemu_SHGetStockIconInfo
{
    struct qemu_syscall super;
    uint64_t id;
    uint64_t flags;
    uint64_t sii;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetStockIconInfo(SHSTOCKICONID id, UINT flags, SHSTOCKICONINFO *sii)
{
    struct qemu_SHGetStockIconInfo call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETSTOCKICONINFO);
    call.id = id;
    call.flags = flags;
    call.sii = (ULONG_PTR)sii;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetStockIconInfo(struct qemu_syscall *call)
{
    struct qemu_SHGetStockIconInfo *c = (struct qemu_SHGetStockIconInfo *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetStockIconInfo(c->id, c->flags, QEMU_G2H(c->sii));
}

#endif

