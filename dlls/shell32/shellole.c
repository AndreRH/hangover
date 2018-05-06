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

#define COBJMACROS
#include <windows.h>
#include <stdio.h>
#include <shlobj.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_shell32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);
#endif

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

enum obj_init
{
    SHELLFOLDER,
};

typedef void * (*LPFNCREATEINSTANCE)(IUnknown *host);

struct qemu_shell_cf
{
    /* Shared fields */
    uint64_t            init_type;

    /* Guest fields */
    IClassFactory       IClassFactory_iface;

    /* Host fields */
    IClassFactory       *host;
    LPFNCREATEINSTANCE  create;
};

struct qemu_cf_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t obj;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_shell_cf *impl_from_IClassFactory(IClassFactory *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_shell_cf, IClassFactory_iface);
}

WINBASEAPI HRESULT WINAPI qemu_cf_QueryInterface(IClassFactory *iface, const IID *iid, void **obj)
{
    struct qemu_cf_QueryInterface call;
    struct qemu_shell_cf *cf = impl_from_IClassFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_CF_QUERYINTERFACE);
    call.iface = (ULONG_PTR)cf;
    call.iid = (ULONG_PTR)iid;
    call.obj = (ULONG_PTR)obj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_cf_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_cf_QueryInterface *c = (struct qemu_cf_QueryInterface *)call;
    struct qemu_shell_cf *cf;

    WINE_FIXME("Unverified!\n");
    cf = QEMU_G2H(c->iface);

    c->super.iret = IClassFactory_QueryInterface(cf->host, QEMU_G2H(c->iid), QEMU_G2H(c->obj));
}

#endif

struct qemu_cf_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI qemu_cf_AddRef(IClassFactory *iface)
{
    struct qemu_cf_AddRef call;
    struct qemu_shell_cf *cf = impl_from_IClassFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_CF_ADDREF);
    call.iface = (ULONG_PTR)cf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_cf_AddRef(struct qemu_syscall *call)
{
    struct qemu_cf_AddRef *c = (struct qemu_cf_AddRef *)call;
    struct qemu_shell_cf *cf;

    WINE_TRACE("\n");
    cf = QEMU_G2H(c->iface);

    c->super.iret = IClassFactory_AddRef(cf->host);
}

#endif

struct qemu_cf_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI ULONG WINAPI qemu_cf_Release(IClassFactory *iface)
{
    struct qemu_cf_Release call;
    struct qemu_shell_cf *cf = impl_from_IClassFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_CF_RELEASE);
    call.iface = (ULONG_PTR)cf;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_cf_Release(struct qemu_syscall *call)
{
    struct qemu_cf_Release *c = (struct qemu_cf_Release *)call;
    struct qemu_shell_cf *cf;

    WINE_TRACE("\n");
    cf = QEMU_G2H(c->iface);

    c->super.iret = IClassFactory_Release(cf->host);
    if (!c->super.iret)
    {
        WINE_TRACE("Destroying class factory %p.\n", cf);
        HeapFree(GetProcessHeap(), 0, cf);
    }
}

#endif

struct qemu_cf_CreateInstance
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t unk_outer;
    uint64_t iid;
    uint64_t obj;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI qemu_cf_CreateInstance(IClassFactory *iface, IUnknown *unk_outer, const IID *iid, void **obj)
{
    struct qemu_cf_CreateInstance call;
    struct qemu_shell_cf *cf = impl_from_IClassFactory(iface);
    struct qemu_shellfolder *folder;
    HRESULT hr;

    call.super.id = QEMU_SYSCALL_ID(CALL_CF_CREATEINSTANCE);
    call.iface = (ULONG_PTR)cf;
    call.unk_outer = (ULONG_PTR)unk_outer;
    call.iid = (ULONG_PTR)iid;

    *obj = NULL;
    qemu_syscall(&call.super);
    hr = call.super.iret;

    if (FAILED(hr))
        return hr;

    switch (cf->init_type)
    {
        case SHELLFOLDER:
            folder = (struct qemu_shellfolder *)(ULONG_PTR)call.obj;
            qemu_shellfolder_guest_init(folder);
            hr = IShellFolder2_QueryInterface(&folder->IShellFolder2_iface, iid, obj);
            IShellFolder2_Release(&folder->IShellFolder2_iface);
            break;
    }

    return hr;
}

#else

static void *IShellFolder_Constructor(IUnknown *host)
{
    IShellFolder2 *sf;
    struct qemu_shellfolder *folder;
    HRESULT hr;

    hr = IUnknown_QueryInterface(host, &IID_IShellFolder2, (void **)&sf);
    if (FAILED(hr))
        WINE_ERR("Cannot query IShellFolder2 inteface.\n");

    folder = qemu_shellfolder_host_create(sf);
    if (!folder)
        IShellFolder2_Release(sf);

    return folder;
}

void qemu_cf_CreateInstance(struct qemu_syscall *call)
{
    struct qemu_cf_CreateInstance *c = (struct qemu_cf_CreateInstance *)call;
    struct qemu_shell_cf *cf;
    IUnknown *obj;

    WINE_TRACE("\n");
    cf = QEMU_G2H(c->iface);

    c->obj = 0;

    /* This will have to be handled in the guest side of our wrappers. */
    if (c->unk_outer)
        WINE_FIXME("Outer unknown interface not handled yet.\n");

    c->super.iret = IClassFactory_CreateInstance(cf->host, NULL, QEMU_G2H(c->iid), (void **)&obj);
    if (FAILED(c->super.iret))
    {
        /* Did we do something wrong? */
        WINE_FIXME("Host-side CreateInstance failed.\n");
        return;
    }

    c->obj = QEMU_H2G(cf->create(obj));
    if (!c->obj)
        c->super.iret = E_FAIL;

    IUnknown_Release(obj);
}

#endif

struct qemu_cf_LockServer
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lock;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI qemu_cf_LockServer(IClassFactory *iface, BOOL lock)
{
    struct qemu_cf_LockServer call;
    struct qemu_shell_cf *cf = impl_from_IClassFactory(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_CF_LOCKSERVER);
    call.iface = (ULONG_PTR)cf;
    call.lock = lock;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_cf_LockServer(struct qemu_syscall *call)
{
    struct qemu_cf_LockServer *c = (struct qemu_cf_LockServer *)call;
    struct qemu_shell_cf *cf;

    WINE_FIXME("Unverified!\n");
    cf = QEMU_G2H(c->iface);

    c->super.iret = IClassFactory_LockServer(cf->host, c->lock);
}

#endif

#ifdef QEMU_DLL_GUEST

 const IClassFactoryVtbl class_factory_vtbl =
{
    qemu_cf_QueryInterface,
    qemu_cf_AddRef,
    qemu_cf_Release,
    qemu_cf_CreateInstance,
    qemu_cf_LockServer
};

WINBASEAPI HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID iid, LPVOID *ppv)
{
    struct qemu_DllGetClassObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLGETCLASSOBJECT);
    call.rclsid = (ULONG_PTR)rclsid;
    call.iid = (ULONG_PTR)iid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        struct qemu_shell_cf *cf = (struct qemu_shell_cf *)(ULONG_PTR)call.ppv;
        cf->IClassFactory_iface.lpVtbl = &class_factory_vtbl;
        *ppv = &cf->IClassFactory_iface;
    }

    return call.super.iret;
}

#else

/* FIXME: Query them from host Shell32 somehow. */
#include <initguid.h>
DEFINE_GUID( CLSID_UnixFolder, 0xcc702eb2, 0x7dc5, 0x11d9, 0xc6, 0x87, 0x00, 0x04, 0x23, 0x8a, 0x01, 0xcd );
DEFINE_GUID( CLSID_UnixDosFolder, 0x9d20aae8, 0x0625, 0x44b0, 0x9c, 0xa7, 0x71, 0x88, 0x9c, 0x22, 0x54, 0xd9 );

const struct
{
    REFIID              clsid;
    LPFNCREATEINSTANCE  lpfnCI;
    enum obj_init       init;
}
InterfaceTable[] =
{
//     {&CLSID_ApplicationAssociationRegistration, ApplicationAssociationRegistration_Constructor},
//     {&CLSID_ApplicationDestinations,            ApplicationDestinations_Constructor},
//     {&CLSID_AutoComplete,                       IAutoComplete_Constructor},
//     {&CLSID_ControlPanel,                       IControlPanel_Constructor},
//     {&CLSID_DragDropHelper,                     IDropTargetHelper_Constructor},

    {&CLSID_FolderShortcut,                     IShellFolder_Constructor,                           SHELLFOLDER},

//     {&CLSID_MyComputer,                         ISF_MyComputer_Constructor},
    {&CLSID_MyDocuments,                        IShellFolder_Constructor,                           SHELLFOLDER},
//     {&CLSID_NetworkPlaces,                      ISF_NetworkPlaces_Constructor},
//     {&CLSID_Printers,                           Printers_Constructor},
//     {&CLSID_QueryAssociations,                  QueryAssociations_Constructor},
//     {&CLSID_RecycleBin,                         RecycleBin_Constructor},
    {&CLSID_ShellDesktop,                       IShellFolder_Constructor,                           SHELLFOLDER},
//     {&CLSID_ShellFSFolder,                      IFSFolder_Constructor},
//     {&CLSID_ShellItem,                          IShellItem_Constructor},
//     {&CLSID_ShellLink,                          IShellLink_Constructor},
    {&CLSID_UnixDosFolder,                      IShellFolder_Constructor,                           SHELLFOLDER},
    {&CLSID_UnixFolder,                         IShellFolder_Constructor,                           SHELLFOLDER},
//     {&CLSID_ExplorerBrowser,                    ExplorerBrowser_Constructor},
//     {&CLSID_KnownFolderManager,                 KnownFolderManager_Constructor},
//     {&CLSID_Shell,                              IShellDispatch_Constructor},
//     {&CLSID_DestinationList,                    CustomDestinationList_Constructor},
//     {&CLSID_ShellImageDataFactory,              ShellImageDataFactory_Constructor},
    {NULL, NULL, 0}
};

void qemu_DllGetClassObject(struct qemu_syscall *call)
{
    struct qemu_DllGetClassObject *c = (struct qemu_DllGetClassObject *)call;
    HRESULT hr;
    CLSID *rclsid;
    const IID *iid;
    IClassFactory *host = NULL;
    struct qemu_shell_cf *cf = NULL;
    unsigned int i;

    WINE_TRACE("\n");
    rclsid = QEMU_G2H(c->rclsid);
    iid = QEMU_G2H(c->iid);

    hr = p_DllGetClassObject(rclsid, &IID_IClassFactory, c->ppv ? (void **)&host : NULL);
    c->super.iret = hr;
    if (FAILED(hr))
    {
        c->ppv = 0;
        return;
    }

    for(i = 0; InterfaceTable[i].clsid; ++i)
    {
        if(IsEqualIID(InterfaceTable[i].clsid, rclsid))
        {
            WINE_TRACE("index[%u]\n", i);
            cf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*cf));
            cf->host = host;
            cf->init_type = InterfaceTable[i].init;
            cf->create = InterfaceTable[i].lpfnCI;
            break;
        }
    }

    if (!cf)
    {
        WINE_FIXME("Implement wrapper for interface %p.\n", wine_dbgstr_guid(rclsid));
        c->super.iret = CLASS_E_CLASSNOTAVAILABLE;
        c->ppv = 0;
        IClassFactory_Release(host);
        return;
    }

    WINE_TRACE("Created class factory %p.\n", cf);
    c->ppv = QEMU_H2G(cf);
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

SHSTDAPI SHCLSIDFromStringAW(const WCHAR *clsid, CLSID *id)
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
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetMalloc(LPMALLOC *lpmal)
{
    struct qemu_SHGetMalloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETMALLOC);

    /* This forwards to ole32.dll, and this call is also used internally in the shell32 implementation.
     * We have two ole32 implementations (host and guest), so there are 2 different IMalloc instances.
     *
     * IMalloc wraps around HeapAlloc(GetProcessHeap()), so having the two different implementations
     * works. However, it also has hooking functionality. If an application depends on the hooks being
     * called for shell32-internal allocs and frees we'll have to merge those two implementations, most
     * likely by hooking ole32's CoGetMalloc. */

    /* For logging. */
    qemu_syscall(&call.super);

    return CoGetMalloc(MEMCTX_TASK, lpmal);
}

#else

void qemu_SHGetMalloc(struct qemu_syscall *call)
{
    struct qemu_SHGetMalloc *c = (struct qemu_SHGetMalloc *)call;
    WINE_TRACE("Handled on the guest side.\n");
}

#endif

struct qemu_SHAlloc
{
    struct qemu_syscall super;
    uint64_t len;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI SHAlloc(SIZE_T len)
{
    struct qemu_SHAlloc call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHALLOC);
    call.len = len;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_SHAlloc(struct qemu_syscall *call)
{
    struct qemu_SHAlloc *c = (struct qemu_SHAlloc *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QEMU_H2G(SHAlloc(c->len));
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
    call.b = b;

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
    call.lFile = lFile;
    call.lpszFile = (ULONG_PTR)lpszFile;
    call.lLength = lLength;

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
    call.lFile = lFile;
    call.lpszwFile = (ULONG_PTR)lpszwFile;
    call.lLength = lLength;

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
    call.grfFlags = grfFlags;
    call.grfMode = grfMode;
    call.dwDisposition = dwDisposition;
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
    call.uCodePage = uCodePage;
    call.cpspec = cpspec;
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
    call.cpspec = cpspec;
    call.rgpspec = (ULONG_PTR)rgpspec;
    call.rgvar = (ULONG_PTR)rgvar;
    call.propidNameFirst = propidNameFirst;

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

void qemu_SHCreateQueryCancelAutoPlayMoniker(struct qemu_syscall *call)
{
    struct qemu_SHCreateQueryCancelAutoPlayMoniker *c = (struct qemu_SHCreateQueryCancelAutoPlayMoniker *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateQueryCancelAutoPlayMoniker(QEMU_G2H(c->moniker));
}

#endif

struct qemu_SHCreateDefClassObject
{
    struct qemu_syscall super;
    uint64_t riid;
    uint64_t ppv;
    uint64_t lpfnCI;
    uint64_t pcRefDll;
    uint64_t riidInst;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateDefClassObject(REFIID riid, LPVOID* ppv, LPFNCREATEINSTANCE lpfnCI, LPDWORD pcRefDll, REFIID riidInst)
{
    struct qemu_SHCreateDefClassObject call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATEDEFCLASSOBJECT);
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;
    call.lpfnCI = (ULONG_PTR)lpfnCI;
    call.pcRefDll = (ULONG_PTR)pcRefDll;
    call.riidInst = (ULONG_PTR)riidInst;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* TODO: Add SHCreateDefClassObject to Wine headers? */
extern HRESULT WINAPI SHCreateDefClassObject(REFIID riid, LPVOID* ppv, LPFNCREATEINSTANCE lpfnCI, LPDWORD pcRefDll, REFIID riidInst);
void qemu_SHCreateDefClassObject(struct qemu_syscall *call)
{
    struct qemu_SHCreateDefClassObject *c = (struct qemu_SHCreateDefClassObject *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateDefClassObject(QEMU_G2H(c->riid), QEMU_G2H(c->ppv), QEMU_G2H(c->lpfnCI), QEMU_G2H(c->pcRefDll), QEMU_G2H(c->riidInst));
}

#endif

struct qemu_SHGetDesktopFolder
{
    struct qemu_syscall super;
    uint64_t psf;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHGetDesktopFolder(IShellFolder **psf)
{
    struct qemu_SHGetDesktopFolder call;
    struct qemu_shellfolder *desktop_folder;

    call.super.id = QEMU_SYSCALL_ID(CALL_SHGETDESKTOPFOLDER);
    qemu_syscall(&call.super);

    if (SUCCEEDED(call.super.iret))
    {
        desktop_folder = (struct qemu_shellfolder *)(ULONG_PTR)call.psf;
        if (!desktop_folder->IShellFolder2_iface.lpVtbl)
            qemu_shellfolder_guest_init(desktop_folder);
        *psf = (IShellFolder *)&desktop_folder->IShellFolder2_iface;
    }

    return call.super.iret;
}

#else

void qemu_SHGetDesktopFolder(struct qemu_syscall *call)
{
    struct qemu_SHGetDesktopFolder *c = (struct qemu_SHGetDesktopFolder *)call;
    IShellFolder *sf;
    struct qemu_shellfolder *folder;

    WINE_TRACE("\n");

    c->psf = 0;
    c->super.iret = SHGetDesktopFolder(&sf);
    if (FAILED(c->super.iret))
        return;

    folder = qemu_shellfolder_host_create((IShellFolder2 *)sf);
    if (!folder)
    {
        c->super.iret = E_OUTOFMEMORY;
        IShellFolder2_Release(sf);
        return;
    }

    WINE_TRACE("Constructed / retrieved desktop folder wrapper %p.\n", folder);
    c->psf = QEMU_H2G(folder);
}

#endif
