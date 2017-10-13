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

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

typedef HRESULT (CALLBACK *LPFNCREATEINSTANCE)(IUnknown* pUnkOuter, REFIID riid, LPVOID* ppvObject);

struct qemu_SHCoCreateInstance
{
    struct qemu_syscall super;
    uint64_t aclsid;
    uint64_t clsid;
    uint64_t pUnkOuter;
    uint64_t refiid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCoCreateInstance(LPCWSTR aclsid, const CLSID *clsid, LPUNKNOWN pUnkOuter, REFIID refiid, LPVOID *ppv)
{
    struct qemu_SHCoCreateInstance call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCOCREATEINSTANCE);
    call.aclsid = (ULONG_PTR)aclsid;
    call.clsid = (ULONG_PTR)clsid;
    call.pUnkOuter = (ULONG_PTR)pUnkOuter;
    call.refiid = (ULONG_PTR)refiid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHCoCreateInstance to Wine headers? */
extern HRESULT WINAPI SHCoCreateInstance(LPCWSTR aclsid, const CLSID *clsid, LPUNKNOWN pUnkOuter, REFIID refiid, LPVOID *ppv);
void qemu_SHCoCreateInstance(struct qemu_syscall *call)
{
    struct qemu_SHCoCreateInstance *c = (struct qemu_SHCoCreateInstance *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCoCreateInstance(QEMU_G2H(c->aclsid), QEMU_G2H(c->clsid), QEMU_G2H(c->pUnkOuter), QEMU_G2H(c->refiid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_DllGetClassObject
{
    struct qemu_syscall super;
    uint64_t rclsid;
    uint64_t iid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID iid, LPVOID *ppv)
{
    struct qemu_DllGetClassObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLGETCLASSOBJECT);
    call.rclsid = (ULONG_PTR)rclsid;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DllGetClassObject(struct qemu_syscall *call)
{
    struct qemu_DllGetClassObject *c = (struct qemu_DllGetClassObject *)call;
    HRESULT hr;
    CLSID *rclsid;
    IID *iid;
    IUnknown *unk = NULL;

    WINE_TRACE("\n");
    rclsid = QEMU_G2H(c->rclsid);
    iid = QEMU_G2H(c->iid);

    hr = p_DllGetClassObject(rclsid, iid, c->ppv ? (void **)&unk : NULL);
    if (FAILED(hr))
    {
        c->super.iret = hr;
        if (c->ppv)
            *(uint64_t *)QEMU_G2H(c->ppv) = QEMU_H2G(unk);
        return;
    }

    WINE_FIXME("Implement a wrapper for object %s!\n", wine_dbgstr_guid(QEMU_G2H(c->rclsid)));

    c->super.iret = E_FAIL;
    *(uint64_t *)QEMU_G2H(c->ppv) = 0;
    return;
}

#endif

struct qemu_SHCLSIDFromString
{
    struct qemu_syscall super;
    uint64_t clsid;
    uint64_t id;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SHCLSIDFromString(const void *clsid, CLSID *id)
{
    struct qemu_SHCLSIDFromString call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCLSIDFROMSTRING);
    call.clsid = (ULONG_PTR)clsid;
    call.id = (ULONG_PTR)id;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCLSIDFromString(struct qemu_syscall *call)
{
    struct qemu_SHCLSIDFromString *c = (struct qemu_SHCLSIDFromString *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = p_SHCLSIDFromString(QEMU_G2H(c->clsid), QEMU_G2H(c->id));
}

#endif

struct qemu_SHGetMalloc
{
    struct qemu_syscall super;
    uint64_t lpmal;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetMalloc(LPMALLOC *lpmal)
{
    struct qemu_SHGetMalloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETMALLOC);
    call.lpmal = (ULONG_PTR)lpmal;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHGetMalloc to Wine headers? */
extern HRESULT WINAPI SHGetMalloc(LPMALLOC *lpmal);
void qemu_SHGetMalloc(struct qemu_syscall *call)
{
    struct qemu_SHGetMalloc *c = (struct qemu_SHGetMalloc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHGetMalloc(QEMU_G2H(c->lpmal));
}

#endif

struct qemu_SHAlloc
{
    struct qemu_syscall super;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI SHAlloc(DWORD len)
{
    struct qemu_SHAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHALLOC);
    call.len = (ULONG_PTR)len;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

/* TODO: Add SHAlloc to Wine headers? */
extern LPVOID WINAPI SHAlloc(DWORD len);
void qemu_SHAlloc(struct qemu_syscall *call)
{
    struct qemu_SHAlloc *c = (struct qemu_SHAlloc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)SHAlloc(c->len);
}

#endif

struct qemu_SHFree
{
    struct qemu_syscall super;
    uint64_t pv;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI SHFree(LPVOID pv)
{
    struct qemu_SHFree call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHFREE);
    call.pv = (ULONG_PTR)pv;

    qemu_syscall(&call.super);
}

#else

/* TODO: Add SHFree to Wine headers? */
extern void WINAPI SHFree(LPVOID pv);
void qemu_SHFree(struct qemu_syscall *call)
{
    struct qemu_SHFree *c = (struct qemu_SHFree *)call;
    WINE_FIXME("Unverified!\n");
    SHFree(QEMU_G2H(c->pv));
}

#endif

struct qemu_DragAcceptFiles
{
    struct qemu_syscall super;
    uint64_t hWnd;
    uint64_t b;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI DragAcceptFiles(HWND hWnd, BOOL b)
{
    struct qemu_DragAcceptFiles call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAGACCEPTFILES);
    call.hWnd = (ULONG_PTR)hWnd;
    call.b = (ULONG_PTR)b;

    qemu_syscall(&call.super);
}

#else

void qemu_DragAcceptFiles(struct qemu_syscall *call)
{
    struct qemu_DragAcceptFiles *c = (struct qemu_DragAcceptFiles *)call;
    WINE_TRACE("\n");
    DragAcceptFiles(QEMU_G2H(c->hWnd), c->b);
}

#endif

struct qemu_DragFinish
{
    struct qemu_syscall super;
    uint64_t h;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI DragFinish(HDROP h)
{
    struct qemu_DragFinish call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAGFINISH);
    call.h = (ULONG_PTR)h;

    qemu_syscall(&call.super);
}

#else

void qemu_DragFinish(struct qemu_syscall *call)
{
    struct qemu_DragFinish *c = (struct qemu_DragFinish *)call;
    WINE_FIXME("Unverified!\n");
    DragFinish(QEMU_G2H(c->h));
}

#endif

struct qemu_DragQueryPoint
{
    struct qemu_syscall super;
    uint64_t hDrop;
    uint64_t p;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DragQueryPoint(HDROP hDrop, POINT *p)
{
    struct qemu_DragQueryPoint call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAGQUERYPOINT);
    call.hDrop = (ULONG_PTR)hDrop;
    call.p = (ULONG_PTR)p;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DragQueryPoint(struct qemu_syscall *call)
{
    struct qemu_DragQueryPoint *c = (struct qemu_DragQueryPoint *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DragQueryPoint(QEMU_G2H(c->hDrop), QEMU_G2H(c->p));
}

#endif

struct qemu_DragQueryFileA
{
    struct qemu_syscall super;
    uint64_t hDrop;
    uint64_t lFile;
    uint64_t lpszFile;
    uint64_t lLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI DragQueryFileA(HDROP hDrop, UINT lFile, LPSTR lpszFile, UINT lLength)
{
    struct qemu_DragQueryFileA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAGQUERYFILEA);
    call.hDrop = (ULONG_PTR)hDrop;
    call.lFile = (ULONG_PTR)lFile;
    call.lpszFile = (ULONG_PTR)lpszFile;
    call.lLength = (ULONG_PTR)lLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DragQueryFileA(struct qemu_syscall *call)
{
    struct qemu_DragQueryFileA *c = (struct qemu_DragQueryFileA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DragQueryFileA(QEMU_G2H(c->hDrop), c->lFile, QEMU_G2H(c->lpszFile), c->lLength);
}

#endif

struct qemu_DragQueryFileW
{
    struct qemu_syscall super;
    uint64_t hDrop;
    uint64_t lFile;
    uint64_t lpszwFile;
    uint64_t lLength;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI UINT WINAPI DragQueryFileW(HDROP hDrop, UINT lFile, LPWSTR lpszwFile, UINT lLength)
{
    struct qemu_DragQueryFileW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DRAGQUERYFILEW);
    call.hDrop = (ULONG_PTR)hDrop;
    call.lFile = (ULONG_PTR)lFile;
    call.lpszwFile = (ULONG_PTR)lpszwFile;
    call.lLength = (ULONG_PTR)lLength;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DragQueryFileW(struct qemu_syscall *call)
{
    struct qemu_DragQueryFileW *c = (struct qemu_DragQueryFileW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DragQueryFileW(QEMU_G2H(c->hDrop), c->lFile, QEMU_G2H(c->lpszwFile), c->lLength);
}

#endif

struct qemu_SHPropStgCreate
{
    struct qemu_syscall super;
    uint64_t psstg;
    uint64_t fmtid;
    uint64_t pclsid;
    uint64_t grfFlags;
    uint64_t grfMode;
    uint64_t dwDisposition;
    uint64_t ppstg;
    uint64_t puCodePage;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHPropStgCreate(IPropertySetStorage *psstg, REFFMTID fmtid, const CLSID *pclsid, DWORD grfFlags, DWORD grfMode, DWORD dwDisposition, IPropertyStorage **ppstg, UINT *puCodePage)
{
    struct qemu_SHPropStgCreate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHPROPSTGCREATE);
    call.psstg = (ULONG_PTR)psstg;
    call.fmtid = (ULONG_PTR)fmtid;
    call.pclsid = (ULONG_PTR)pclsid;
    call.grfFlags = (ULONG_PTR)grfFlags;
    call.grfMode = (ULONG_PTR)grfMode;
    call.dwDisposition = (ULONG_PTR)dwDisposition;
    call.ppstg = (ULONG_PTR)ppstg;
    call.puCodePage = (ULONG_PTR)puCodePage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHPropStgCreate to Wine headers? */
extern HRESULT WINAPI SHPropStgCreate(IPropertySetStorage *psstg, REFFMTID fmtid, const CLSID *pclsid, DWORD grfFlags, DWORD grfMode, DWORD dwDisposition, IPropertyStorage **ppstg, UINT *puCodePage);
void qemu_SHPropStgCreate(struct qemu_syscall *call)
{
    struct qemu_SHPropStgCreate *c = (struct qemu_SHPropStgCreate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHPropStgCreate(QEMU_G2H(c->psstg), QEMU_G2H(c->fmtid), QEMU_G2H(c->pclsid), c->grfFlags, c->grfMode, c->dwDisposition, QEMU_G2H(c->ppstg), QEMU_G2H(c->puCodePage));
}

#endif

struct qemu_SHPropStgReadMultiple
{
    struct qemu_syscall super;
    uint64_t pps;
    uint64_t uCodePage;
    uint64_t cpspec;
    uint64_t rgpspec;
    uint64_t rgvar;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHPropStgReadMultiple(IPropertyStorage *pps, UINT uCodePage, ULONG cpspec, const PROPSPEC *rgpspec, PROPVARIANT *rgvar)
{
    struct qemu_SHPropStgReadMultiple call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHPROPSTGREADMULTIPLE);
    call.pps = (ULONG_PTR)pps;
    call.uCodePage = (ULONG_PTR)uCodePage;
    call.cpspec = (ULONG_PTR)cpspec;
    call.rgpspec = (ULONG_PTR)rgpspec;
    call.rgvar = (ULONG_PTR)rgvar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHPropStgReadMultiple to Wine headers? */
extern HRESULT WINAPI SHPropStgReadMultiple(IPropertyStorage *pps, UINT uCodePage, ULONG cpspec, const PROPSPEC *rgpspec, PROPVARIANT *rgvar);
void qemu_SHPropStgReadMultiple(struct qemu_syscall *call)
{
    struct qemu_SHPropStgReadMultiple *c = (struct qemu_SHPropStgReadMultiple *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHPropStgReadMultiple(QEMU_G2H(c->pps), c->uCodePage, c->cpspec, QEMU_G2H(c->rgpspec), QEMU_G2H(c->rgvar));
}

#endif

struct qemu_SHPropStgWriteMultiple
{
    struct qemu_syscall super;
    uint64_t pps;
    uint64_t uCodePage;
    uint64_t cpspec;
    uint64_t rgpspec;
    uint64_t rgvar;
    uint64_t propidNameFirst;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHPropStgWriteMultiple(IPropertyStorage *pps, UINT *uCodePage, ULONG cpspec, const PROPSPEC *rgpspec, PROPVARIANT *rgvar, PROPID propidNameFirst)
{
    struct qemu_SHPropStgWriteMultiple call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHPROPSTGWRITEMULTIPLE);
    call.pps = (ULONG_PTR)pps;
    call.uCodePage = (ULONG_PTR)uCodePage;
    call.cpspec = (ULONG_PTR)cpspec;
    call.rgpspec = (ULONG_PTR)rgpspec;
    call.rgvar = (ULONG_PTR)rgvar;
    call.propidNameFirst = (ULONG_PTR)propidNameFirst;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHPropStgWriteMultiple to Wine headers? */
extern HRESULT WINAPI SHPropStgWriteMultiple(IPropertyStorage *pps, UINT *uCodePage, ULONG cpspec, const PROPSPEC *rgpspec, PROPVARIANT *rgvar, PROPID propidNameFirst);
void qemu_SHPropStgWriteMultiple(struct qemu_syscall *call)
{
    struct qemu_SHPropStgWriteMultiple *c = (struct qemu_SHPropStgWriteMultiple *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHPropStgWriteMultiple(QEMU_G2H(c->pps), QEMU_G2H(c->uCodePage), c->cpspec, QEMU_G2H(c->rgpspec), QEMU_G2H(c->rgvar), c->propidNameFirst);
}

#endif

struct qemu_SHCreateQueryCancelAutoPlayMoniker
{
    struct qemu_syscall super;
    uint64_t moniker;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateQueryCancelAutoPlayMoniker(IMoniker **moniker)
{
    struct qemu_SHCreateQueryCancelAutoPlayMoniker call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATEQUERYCANCELAUTOPLAYMONIKER);
    call.moniker = (ULONG_PTR)moniker;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHCreateQueryCancelAutoPlayMoniker to Wine headers? */
extern HRESULT WINAPI SHCreateQueryCancelAutoPlayMoniker(IMoniker **moniker);
void qemu_SHCreateQueryCancelAutoPlayMoniker(struct qemu_syscall *call)
{
    struct qemu_SHCreateQueryCancelAutoPlayMoniker *c = (struct qemu_SHCreateQueryCancelAutoPlayMoniker *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateQueryCancelAutoPlayMoniker(QEMU_G2H(c->moniker));
}

#endif
