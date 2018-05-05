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
#include <shtypes.h>
#include <shlobj.h>
#include <shlwapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif


struct qemu_ILGetDisplayNameEx
{
    struct qemu_syscall super;
    uint64_t psf;
    uint64_t pidl;
    uint64_t path;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ILGetDisplayNameEx(LPSHELLFOLDER psf, LPCITEMIDLIST pidl, LPVOID path, DWORD type)
{
    struct qemu_ILGetDisplayNameEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILGETDISPLAYNAMEEX);
    call.psf = (ULONG_PTR)psf;
    call.pidl = (ULONG_PTR)pidl;
    call.path = (ULONG_PTR)path;
    call.type = (ULONG_PTR)type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ILGetDisplayNameEx to Wine headers? */
extern BOOL WINAPI ILGetDisplayNameEx(LPSHELLFOLDER psf, LPCITEMIDLIST pidl, LPVOID path, DWORD type);
void qemu_ILGetDisplayNameEx(struct qemu_syscall *call)
{
    struct qemu_ILGetDisplayNameEx *c = (struct qemu_ILGetDisplayNameEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ILGetDisplayNameEx(QEMU_G2H(c->psf), QEMU_G2H(c->pidl), QEMU_G2H(c->path), c->type);
}

#endif

struct qemu_ILGetDisplayName
{
    struct qemu_syscall super;
    uint64_t pidl;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ILGetDisplayName(LPCITEMIDLIST pidl, LPVOID path)
{
    struct qemu_ILGetDisplayName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILGETDISPLAYNAME);
    call.pidl = (ULONG_PTR)pidl;
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add ILGetDisplayName to Wine headers? */
extern BOOL WINAPI ILGetDisplayName(LPCITEMIDLIST pidl, LPVOID path);
void qemu_ILGetDisplayName(struct qemu_syscall *call)
{
    struct qemu_ILGetDisplayName *c = (struct qemu_ILGetDisplayName *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ILGetDisplayName(QEMU_G2H(c->pidl), QEMU_G2H(c->path));
}

#endif

struct qemu_ILFindLastID
{
    struct qemu_syscall super;
    uint64_t idl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI ILFindLastID(const ITEMIDLIST *idl)
{
    struct qemu_ILFindLastID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILFINDLASTID);
    call.idl = (ULONG_PTR)idl;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ILFindLastID(struct qemu_syscall *call)
{
    struct qemu_ILFindLastID *c = (struct qemu_ILFindLastID *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)ILFindLastID(QEMU_G2H(c->idl));
}

#endif

struct qemu_ILRemoveLastID
{
    struct qemu_syscall super;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ILRemoveLastID(LPITEMIDLIST pidl)
{
    struct qemu_ILRemoveLastID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILREMOVELASTID);
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ILRemoveLastID(struct qemu_syscall *call)
{
    struct qemu_ILRemoveLastID *c = (struct qemu_ILRemoveLastID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ILRemoveLastID(QEMU_G2H(c->pidl));
}

#endif

struct qemu_ILClone
{
    struct qemu_syscall super;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI ILClone (LPCITEMIDLIST pidl)
{
    struct qemu_ILClone call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILCLONE);
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ILClone(struct qemu_syscall *call)
{
    struct qemu_ILClone *c = (struct qemu_ILClone *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ILClone(QEMU_G2H(c->pidl));
}

#endif

struct qemu_ILCloneFirst
{
    struct qemu_syscall super;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI ILCloneFirst(LPCITEMIDLIST pidl)
{
    struct qemu_ILCloneFirst call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILCLONEFIRST);
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ILCloneFirst(struct qemu_syscall *call)
{
    struct qemu_ILCloneFirst *c = (struct qemu_ILCloneFirst *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ILCloneFirst(QEMU_G2H(c->pidl));
}

#endif

struct qemu_ILLoadFromStream
{
    struct qemu_syscall super;
    uint64_t pStream;
    uint64_t ppPidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ILLoadFromStream (IStream * pStream, LPITEMIDLIST * ppPidl)
{
    struct qemu_ILLoadFromStream call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILLOADFROMSTREAM);
    call.pStream = (ULONG_PTR)pStream;
    call.ppPidl = (ULONG_PTR)ppPidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ILLoadFromStream(struct qemu_syscall *call)
{
    struct qemu_ILLoadFromStream *c = (struct qemu_ILLoadFromStream *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ILLoadFromStream(QEMU_G2H(c->pStream), QEMU_G2H(c->ppPidl));
}

#endif

struct qemu_ILSaveToStream
{
    struct qemu_syscall super;
    uint64_t pStream;
    uint64_t pPidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI ILSaveToStream (IStream * pStream, LPCITEMIDLIST pPidl)
{
    struct qemu_ILSaveToStream call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILSAVETOSTREAM);
    call.pStream = (ULONG_PTR)pStream;
    call.pPidl = (ULONG_PTR)pPidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ILSaveToStream(struct qemu_syscall *call)
{
    struct qemu_ILSaveToStream *c = (struct qemu_ILSaveToStream *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ILSaveToStream(QEMU_G2H(c->pStream), QEMU_G2H(c->pPidl));
}

#endif

struct qemu_SHILCreateFromPathAW
{
    struct qemu_syscall super;
    uint64_t path;
    uint64_t ppidl;
    uint64_t attributes;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHILCreateFromPathAW (LPCVOID path, LPITEMIDLIST * ppidl, DWORD * attributes)
{
    struct qemu_SHILCreateFromPathAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHILCREATEFROMPATHAW);
    call.path = (ULONG_PTR)path;
    call.ppidl = (ULONG_PTR)ppidl;
    call.attributes = (ULONG_PTR)attributes;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHILCreateFromPathAW(struct qemu_syscall *call)
{
    struct qemu_SHILCreateFromPathAW *c = (struct qemu_SHILCreateFromPathAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHILCreateFromPath(QEMU_G2H(c->path), QEMU_G2H(c->ppidl), QEMU_G2H(c->attributes));
}

#endif

struct qemu_SHCloneSpecialIDList
{
    struct qemu_syscall super;
    uint64_t hwndOwner;
    uint64_t nFolder;
    uint64_t fCreate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI SHCloneSpecialIDList(HWND hwndOwner, int nFolder, WINBOOL fCreate)
{
    struct qemu_SHCloneSpecialIDList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCLONESPECIALIDLIST);
    call.hwndOwner = (ULONG_PTR)hwndOwner;
    call.nFolder = (ULONG_PTR)nFolder;
    call.fCreate = (ULONG_PTR)fCreate;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add SHCloneSpecialIDList to Wine headers? */
extern LPITEMIDLIST WINAPI SHCloneSpecialIDList(HWND hwndOwner, DWORD nFolder, BOOL fCreate);
void qemu_SHCloneSpecialIDList(struct qemu_syscall *call)
{
    struct qemu_SHCloneSpecialIDList *c = (struct qemu_SHCloneSpecialIDList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)SHCloneSpecialIDList(QEMU_G2H(c->hwndOwner), c->nFolder, c->fCreate);
}

#endif

struct qemu_ILGlobalClone
{
    struct qemu_syscall super;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI ILGlobalClone(LPCITEMIDLIST pidl)
{
    struct qemu_ILGlobalClone call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILGLOBALCLONE);
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add ILGlobalClone to Wine headers? */
extern LPITEMIDLIST WINAPI ILGlobalClone(LPCITEMIDLIST pidl);
void qemu_ILGlobalClone(struct qemu_syscall *call)
{
    struct qemu_ILGlobalClone *c = (struct qemu_ILGlobalClone *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ILGlobalClone(QEMU_G2H(c->pidl));
}

#endif

struct qemu_ILIsEqual
{
    struct qemu_syscall super;
    uint64_t pidl1;
    uint64_t pidl2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ILIsEqual(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
    struct qemu_ILIsEqual call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILISEQUAL);
    call.pidl1 = (ULONG_PTR)pidl1;
    call.pidl2 = (ULONG_PTR)pidl2;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ILIsEqual(struct qemu_syscall *call)
{
    struct qemu_ILIsEqual *c = (struct qemu_ILIsEqual *)call;
    WINE_TRACE("\n");
    c->super.iret = ILIsEqual(QEMU_G2H(c->pidl1), QEMU_G2H(c->pidl2));
}

#endif

struct qemu_ILIsParent
{
    struct qemu_syscall super;
    uint64_t pidlParent;
    uint64_t pidlChild;
    uint64_t bImmediate;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ILIsParent(LPCITEMIDLIST pidlParent, LPCITEMIDLIST pidlChild, BOOL bImmediate)
{
    struct qemu_ILIsParent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILISPARENT);
    call.pidlParent = (ULONG_PTR)pidlParent;
    call.pidlChild = (ULONG_PTR)pidlChild;
    call.bImmediate = (ULONG_PTR)bImmediate;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ILIsParent(struct qemu_syscall *call)
{
    struct qemu_ILIsParent *c = (struct qemu_ILIsParent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ILIsParent(QEMU_G2H(c->pidlParent), QEMU_G2H(c->pidlChild), c->bImmediate);
}

#endif

struct qemu_ILFindChild
{
    struct qemu_syscall super;
    uint64_t pidl1;
    uint64_t pidl2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI ILFindChild(PIDLIST_ABSOLUTE pidl1, PCIDLIST_ABSOLUTE pidl2)
{
    struct qemu_ILFindChild call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILFINDCHILD);
    call.pidl1 = (ULONG_PTR)pidl1;
    call.pidl2 = (ULONG_PTR)pidl2;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ILFindChild(struct qemu_syscall *call)
{
    struct qemu_ILFindChild *c = (struct qemu_ILFindChild *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ILFindChild(QEMU_G2H(c->pidl1), QEMU_G2H(c->pidl2));
}

#endif

struct qemu_ILCombine
{
    struct qemu_syscall super;
    uint64_t pidl1;
    uint64_t pidl2;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI ILCombine(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
    struct qemu_ILCombine call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILCOMBINE);
    call.pidl1 = (ULONG_PTR)pidl1;
    call.pidl2 = (ULONG_PTR)pidl2;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ILCombine(struct qemu_syscall *call)
{
    struct qemu_ILCombine *c = (struct qemu_ILCombine *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ILCombine(QEMU_G2H(c->pidl1), QEMU_G2H(c->pidl2));
}

#endif

struct qemu_SHGetRealIDL
{
    struct qemu_syscall super;
    uint64_t lpsf;
    uint64_t pidlSimple;
    uint64_t pidlReal;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetRealIDL(LPSHELLFOLDER lpsf, LPCITEMIDLIST pidlSimple, LPITEMIDLIST *pidlReal)
{
    struct qemu_SHGetRealIDL call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETREALIDL);
    call.lpsf = (ULONG_PTR)lpsf;
    call.pidlSimple = (ULONG_PTR)pidlSimple;
    call.pidlReal = (ULONG_PTR)pidlReal;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetRealIDL(struct qemu_syscall *call)
{
    struct qemu_SHGetRealIDL *c = (struct qemu_SHGetRealIDL *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetRealIDL(QEMU_G2H(c->lpsf), QEMU_G2H(c->pidlSimple), QEMU_G2H(c->pidlReal));
}

#endif

struct qemu_SHLogILFromFSIL
{
    struct qemu_syscall super;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI SHLogILFromFSIL(LPITEMIDLIST pidl)
{
    struct qemu_SHLogILFromFSIL call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHLOGILFROMFSIL);
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add SHLogILFromFSIL to Wine headers? */
extern LPITEMIDLIST WINAPI SHLogILFromFSIL(LPITEMIDLIST pidl);
void qemu_SHLogILFromFSIL(struct qemu_syscall *call)
{
    struct qemu_SHLogILFromFSIL *c = (struct qemu_SHLogILFromFSIL *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)SHLogILFromFSIL(QEMU_G2H(c->pidl));
}

#endif

struct qemu_ILGetSize
{
    struct qemu_syscall super;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI ILGetSize(LPCITEMIDLIST pidl)
{
    struct qemu_ILGetSize call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILGETSIZE);
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ILGetSize(struct qemu_syscall *call)
{
    struct qemu_ILGetSize *c = (struct qemu_ILGetSize *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ILGetSize(QEMU_G2H(c->pidl));
}

#endif

struct qemu_ILGetNext
{
    struct qemu_syscall super;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI ILGetNext(LPCITEMIDLIST pidl)
{
    struct qemu_ILGetNext call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILGETNEXT);
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ILGetNext(struct qemu_syscall *call)
{
    struct qemu_ILGetNext *c = (struct qemu_ILGetNext *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ILGetNext(QEMU_G2H(c->pidl));
}

#endif

struct qemu_ILAppendID
{
    struct qemu_syscall super;
    uint64_t pidl;
    uint64_t item;
    uint64_t bEnd;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI ILAppendID(LPITEMIDLIST pidl, LPCSHITEMID item, BOOL bEnd)
{
    struct qemu_ILAppendID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILAPPENDID);
    call.pidl = (ULONG_PTR)pidl;
    call.item = (ULONG_PTR)item;
    call.bEnd = (ULONG_PTR)bEnd;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ILAppendID(struct qemu_syscall *call)
{
    struct qemu_ILAppendID *c = (struct qemu_ILAppendID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ILAppendID(QEMU_G2H(c->pidl), QEMU_G2H(c->item), c->bEnd);
}

#endif

struct qemu_ILFree
{
    struct qemu_syscall super;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI ILFree(LPITEMIDLIST pidl)
{
    struct qemu_ILFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILFREE);
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);
}

#else

void qemu_ILFree(struct qemu_syscall *call)
{
    struct qemu_ILFree *c = (struct qemu_ILFree *)call;
    WINE_TRACE("\n");
    ILFree(QEMU_G2H(c->pidl));
}

#endif

struct qemu_ILGlobalFree
{
    struct qemu_syscall super;
    uint64_t pidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI ILGlobalFree(LPITEMIDLIST pidl)
{
    struct qemu_ILGlobalFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILGLOBALFREE);
    call.pidl = (ULONG_PTR)pidl;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add ILGlobalFree to Wine headers? */
extern void WINAPI ILGlobalFree(LPITEMIDLIST pidl);
void qemu_ILGlobalFree(struct qemu_syscall *call)
{
    struct qemu_ILGlobalFree *c = (struct qemu_ILGlobalFree *)call;
    WINE_FIXME("Unverified!\n");
    ILGlobalFree(QEMU_G2H(c->pidl));
}

#endif

struct qemu_ILCreateFromPathAW
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

LPITEMIDLIST WINAPI ILCreateFromPathAW (LPCVOID path)
{
    struct qemu_ILCreateFromPathAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILCREATEFROMPATHAW);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ILCreateFromPathAW(struct qemu_syscall *call)
{
    struct qemu_ILCreateFromPathAW *c = (struct qemu_ILCreateFromPathAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ILCreateFromPath(QEMU_G2H(c->path));
}

#endif

struct qemu_ILCreateFromPathA
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI ILCreateFromPathA (LPCSTR path)
{
    struct qemu_ILCreateFromPathA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILCREATEFROMPATHA);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ILCreateFromPathA(struct qemu_syscall *call)
{
    struct qemu_ILCreateFromPathA *c = (struct qemu_ILCreateFromPathA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ILCreateFromPathA(QEMU_G2H(c->path));
}

#endif

struct qemu_ILCreateFromPathW
{
    struct qemu_syscall super;
    uint64_t path;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI ILCreateFromPathW (LPCWSTR path)
{
    struct qemu_ILCreateFromPathW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ILCREATEFROMPATHW);
    call.path = (ULONG_PTR)path;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_ILCreateFromPathW(struct qemu_syscall *call)
{
    struct qemu_ILCreateFromPathW *c = (struct qemu_ILCreateFromPathW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)ILCreateFromPathW(QEMU_G2H(c->path));
}

#endif

struct qemu_SHSimpleIDListFromPathAW
{
    struct qemu_syscall super;
    uint64_t lpszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPITEMIDLIST WINAPI SHSimpleIDListFromPathAW(LPCVOID lpszPath)
{
    struct qemu_SHSimpleIDListFromPathAW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHSIMPLEIDLISTFROMPATHAW);
    call.lpszPath = (ULONG_PTR)lpszPath;

    qemu_syscall(&call.super);

    return (LPITEMIDLIST)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SHSimpleIDListFromPathAW(struct qemu_syscall *call)
{
    struct qemu_SHSimpleIDListFromPathAW *c = (struct qemu_SHSimpleIDListFromPathAW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)SHSimpleIDListFromPath(QEMU_G2H(c->lpszPath));
}

#endif

struct qemu_SHGetDataFromIDListA
{
    struct qemu_syscall super;
    uint64_t psf;
    uint64_t pidl;
    uint64_t nFormat;
    uint64_t dest;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetDataFromIDListA(LPSHELLFOLDER psf, LPCITEMIDLIST pidl, int nFormat, LPVOID dest, int len)
{
    struct qemu_SHGetDataFromIDListA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETDATAFROMIDLISTA);
    call.psf = (ULONG_PTR)psf;
    call.pidl = (ULONG_PTR)pidl;
    call.nFormat = (ULONG_PTR)nFormat;
    call.dest = (ULONG_PTR)dest;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetDataFromIDListA(struct qemu_syscall *call)
{
    struct qemu_SHGetDataFromIDListA *c = (struct qemu_SHGetDataFromIDListA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetDataFromIDListA(QEMU_G2H(c->psf), QEMU_G2H(c->pidl), c->nFormat, QEMU_G2H(c->dest), c->len);
}

#endif

struct qemu_SHGetDataFromIDListW
{
    struct qemu_syscall super;
    uint64_t psf;
    uint64_t pidl;
    uint64_t nFormat;
    uint64_t dest;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetDataFromIDListW(LPSHELLFOLDER psf, LPCITEMIDLIST pidl, int nFormat, LPVOID dest, int len)
{
    struct qemu_SHGetDataFromIDListW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETDATAFROMIDLISTW);
    call.psf = (ULONG_PTR)psf;
    call.pidl = (ULONG_PTR)pidl;
    call.nFormat = (ULONG_PTR)nFormat;
    call.dest = (ULONG_PTR)dest;
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetDataFromIDListW(struct qemu_syscall *call)
{
    struct qemu_SHGetDataFromIDListW *c = (struct qemu_SHGetDataFromIDListW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetDataFromIDListW(QEMU_G2H(c->psf), QEMU_G2H(c->pidl), c->nFormat, QEMU_G2H(c->dest), c->len);
}

#endif

struct qemu_SHGetPathFromIDListA
{
    struct qemu_syscall super;
    uint64_t pidl;
    uint64_t pszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHGetPathFromIDListA(LPCITEMIDLIST pidl, LPSTR pszPath)
{
    struct qemu_SHGetPathFromIDListA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETPATHFROMIDLISTA);
    call.pidl = (ULONG_PTR)pidl;
    call.pszPath = (ULONG_PTR)pszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetPathFromIDListA(struct qemu_syscall *call)
{
    struct qemu_SHGetPathFromIDListA *c = (struct qemu_SHGetPathFromIDListA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetPathFromIDListA(QEMU_G2H(c->pidl), QEMU_G2H(c->pszPath));
}

#endif

struct qemu_SHGetPathFromIDListW
{
    struct qemu_syscall super;
    uint64_t pidl;
    uint64_t pszPath;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHGetPathFromIDListW(LPCITEMIDLIST pidl, LPWSTR pszPath)
{
    struct qemu_SHGetPathFromIDListW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETPATHFROMIDLISTW);
    call.pidl = (ULONG_PTR)pidl;
    call.pszPath = (ULONG_PTR)pszPath;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetPathFromIDListW(struct qemu_syscall *call)
{
    struct qemu_SHGetPathFromIDListW *c = (struct qemu_SHGetPathFromIDListW *)call;
    WINE_TRACE("\n");
    c->super.iret = SHGetPathFromIDListW(QEMU_G2H(c->pidl), QEMU_G2H(c->pszPath));
}

#endif

struct qemu_SHGetPathFromIDListEx
{
    struct qemu_syscall super;
    uint64_t pidl;
    uint64_t path;
    uint64_t path_size;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI SHGetPathFromIDListEx(LPCITEMIDLIST pidl, WCHAR *path, DWORD path_size, GPFIDL_FLAGS flags)
{
    struct qemu_SHGetPathFromIDListEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETPATHFROMIDLISTEX);
    call.pidl = (ULONG_PTR)pidl;
    call.path = (ULONG_PTR)path;
    call.path_size = (ULONG_PTR)path_size;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetPathFromIDListEx(struct qemu_syscall *call)
{
    struct qemu_SHGetPathFromIDListEx *c = (struct qemu_SHGetPathFromIDListEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetPathFromIDListEx(QEMU_G2H(c->pidl), QEMU_G2H(c->path), c->path_size, c->flags);
}

#endif

struct qemu_SHBindToParent
{
    struct qemu_syscall super;
    uint64_t pidl;
    uint64_t riid;
    uint64_t ppv;
    uint64_t ppidlLast;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHBindToParent(LPCITEMIDLIST pidl, REFIID riid, LPVOID *ppv, LPCITEMIDLIST *ppidlLast)
{
    struct qemu_SHBindToParent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHBINDTOPARENT);
    call.pidl = (ULONG_PTR)pidl;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;
    call.ppidlLast = (ULONG_PTR)ppidlLast;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHBindToParent(struct qemu_syscall *call)
{
    struct qemu_SHBindToParent *c = (struct qemu_SHBindToParent *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHBindToParent(QEMU_G2H(c->pidl), QEMU_G2H(c->riid), QEMU_G2H(c->ppv), QEMU_G2H(c->ppidlLast));
}

#endif

struct qemu_SHParseDisplayName
{
    struct qemu_syscall super;
    uint64_t name;
    uint64_t bindctx;
    uint64_t pidlist;
    uint64_t attr_in;
    uint64_t attr_out;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHParseDisplayName(LPCWSTR name, IBindCtx *bindctx, LPITEMIDLIST *pidlist,
        SFGAOF attr_in, SFGAOF *attr_out)
{
    struct qemu_SHParseDisplayName call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHPARSEDISPLAYNAME);
    call.name = (ULONG_PTR)name;
    call.bindctx = (ULONG_PTR)bindctx;
    call.attr_in = (ULONG_PTR)attr_in;
    call.attr_out = (ULONG_PTR)attr_out;

    qemu_syscall(&call.super);
    *pidlist = (ITEMIDLIST *)(ULONG_PTR)call.pidlist;

    return call.super.iret;
}

#else

void qemu_SHParseDisplayName(struct qemu_syscall *call)
{
    struct qemu_SHParseDisplayName *c = (struct qemu_SHParseDisplayName *)call;
    ITEMIDLIST *list;

    /* SFGAOF is a ULONG, *pidlist is written unconditionally */
    WINE_TRACE("\n");

    if (c->bindctx)
        WINE_FIXME("Bind Context not handled yet.\n");

    c->super.iret = SHParseDisplayName(QEMU_G2H(c->name), QEMU_G2H(c->bindctx), &list,
            c->attr_in, QEMU_G2H(c->attr_out));
    c->pidlist = QEMU_H2G(list);
}

#endif

struct qemu_SHGetNameFromIDList
{
    struct qemu_syscall super;
    uint64_t pidl;
    uint64_t sigdnName;
    uint64_t ppszName;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetNameFromIDList(PCIDLIST_ABSOLUTE pidl, SIGDN sigdnName, PWSTR *ppszName)
{
    struct qemu_SHGetNameFromIDList call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETNAMEFROMIDLIST);
    call.pidl = (ULONG_PTR)pidl;
    call.sigdnName = (ULONG_PTR)sigdnName;
    call.ppszName = (ULONG_PTR)ppszName;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetNameFromIDList(struct qemu_syscall *call)
{
    struct qemu_SHGetNameFromIDList *c = (struct qemu_SHGetNameFromIDList *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetNameFromIDList(QEMU_G2H(c->pidl), c->sigdnName, QEMU_G2H(c->ppszName));
}

#endif

struct qemu_SHGetIDListFromObject
{
    struct qemu_syscall super;
    uint64_t punk;
    uint64_t ppidl;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetIDListFromObject(IUnknown *punk, PIDLIST_ABSOLUTE *ppidl)
{
    struct qemu_SHGetIDListFromObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETIDLISTFROMOBJECT);
    call.punk = (ULONG_PTR)punk;
    call.ppidl = (ULONG_PTR)ppidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHGetIDListFromObject(struct qemu_syscall *call)
{
    struct qemu_SHGetIDListFromObject *c = (struct qemu_SHGetIDListFromObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetIDListFromObject(QEMU_G2H(c->punk), QEMU_G2H(c->ppidl));
}

#endif

