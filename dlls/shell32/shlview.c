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

#define CINTERFACE
#define COBJMACROS
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

/* I somehow have troubles with IID_IShellFolderView on mingw. */
const GUID IID_myIShellFolderView = 
{
    0x37a378c0,
    0xf82d,
    0x11ce,
    { 0xae,0x65,0x08,0x00,0x2b,0x2e,0x12,0x62 }
};

struct qemu_IShellView_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppvObj;
};

#ifdef QEMU_DLL_GUEST

static inline struct qemu_shellview *impl_from_IShellView3(IShellView3 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_shellview, IShellView3_iface);
}

static inline struct qemu_shellview *impl_from_IOleCommandTarget(IOleCommandTarget *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_shellview, IOleCommandTarget_iface);
}

static inline struct qemu_shellview *impl_from_IDropTarget(IDropTarget *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_shellview, IDropTarget_iface);
}

static inline struct qemu_shellview *impl_from_IDropSource(IDropSource *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_shellview, IDropSource_iface);
}

static inline struct qemu_shellview *impl_from_IViewObject(IViewObject *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_shellview, IViewObject_iface);
}

static inline struct qemu_shellview *impl_from_IFolderView2(IFolderView2 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_shellview, IFolderView2_iface);
}

static inline struct qemu_shellview *impl_from_IShellFolderView(IShellFolderView *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_shellview, IShellFolderView_iface);
}

static inline struct qemu_shellview *impl_from_IShellFolderViewDual3(IShellFolderViewDual3 *iface)
{
    return CONTAINING_RECORD(iface, struct qemu_shellview, IShellFolderViewDual3_iface);
}

static HRESULT WINAPI qemu_shellview_QueryInterface(IShellView3 *iface, REFIID riid, void **ppvObj)
{
    struct qemu_IShellView_QueryInterface call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.ppvObj = (ULONG_PTR)ppvObj;

    qemu_syscall(&call.super);

    if(IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, &IID_IShellView) ||
            IsEqualIID(riid, &IID_IShellView2) || IsEqualIID(riid, &IID_IShellView3) || IsEqualIID(riid, &IID_CDefView))
    {
        *ppvObj = &view->IShellView3_iface;
    }
    else if(IsEqualIID(riid, &IID_myIShellFolderView))
    {
        *ppvObj = &view->IShellFolderView_iface;
    }
    else if(IsEqualIID(riid, &IID_IFolderView) || IsEqualIID(riid, &IID_IFolderView2))
    {
        *ppvObj = &view->IFolderView2_iface;
    }
    else if(IsEqualIID(riid, &IID_IOleCommandTarget))
    {
        *ppvObj = &view->IOleCommandTarget_iface;
    }
    else if(IsEqualIID(riid, &IID_IDropTarget))
    {
        *ppvObj = &view->IDropTarget_iface;
    }
    else if(IsEqualIID(riid, &IID_IDropSource))
    {
        *ppvObj = &view->IDropSource_iface;
    }
    else if(IsEqualIID(riid, &IID_IViewObject))
    {
        *ppvObj = &view->IViewObject_iface;
    }
    else if(SUCCEEDED(call.super.iret))
    {
        call.iface = 0;
        qemu_syscall(&call.super);
    }
    else
    {
        *ppvObj = NULL;
    }

    return call.super.iret;
}

#else

void qemu_IShellView_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_IShellView_QueryInterface *c = (struct qemu_IShellView_QueryInterface *)call;
    struct qemu_shellview *view;

    WINE_TRACE("\n");
    view = QEMU_G2H(c->iface);

    if (!view)
    {
        WINE_FIXME("Host handled IID %s, but it is not handled by the wrapper.\n",
                wine_dbgstr_guid(QEMU_G2H(c->riid)));
        DebugBreak();
    }

    c->super.iret = IShellView_QueryInterface(view->host_shellview, QEMU_G2H(c->riid), QEMU_G2H(c->ppvObj));
}

#endif

struct qemu_IShellView_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI qemu_shellview_AddRef(IShellView3 *iface)
{
    struct qemu_IShellView_AddRef call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_AddRef(struct qemu_syscall *call)
{
    struct qemu_IShellView_AddRef *c = (struct qemu_IShellView_AddRef *)call;
    struct qemu_shellview *view;

    WINE_TRACE("\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_AddRef(view->host_shellview);
}

#endif

struct qemu_IShellView_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI qemu_shellview_Release(IShellView3 *iface)
{
    struct qemu_IShellView_Release call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_Release(struct qemu_syscall *call)
{
    struct qemu_IShellView_Release *c = (struct qemu_IShellView_Release *)call;
    struct qemu_shellview *view;

    WINE_TRACE("\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_Release(view->host_shellview);
    if (!c->super.iret)
    {
        WINE_TRACE("Destroying shell view wrapper %p.\n", view);
        HeapFree(GetProcessHeap(), 0, view);
    }
}

#endif

struct qemu_IShellView_GetWindow
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t phWnd;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_GetWindow(IShellView3 *iface, HWND *phWnd)
{
    struct qemu_IShellView_GetWindow call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_GETWINDOW);
    call.iface = (ULONG_PTR)view;
    call.phWnd = (ULONG_PTR)phWnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_GetWindow(struct qemu_syscall *call)
{
    struct qemu_IShellView_GetWindow *c = (struct qemu_IShellView_GetWindow *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_GetWindow(view->host_shellview, QEMU_G2H(c->phWnd));
}

#endif

struct qemu_IShellView_ContextSensitiveHelp
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_ContextSensitiveHelp(IShellView3 *iface, BOOL mode)
{
    struct qemu_IShellView_ContextSensitiveHelp call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_CONTEXTSENSITIVEHELP);
    call.iface = (ULONG_PTR)view;
    call.mode = mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_ContextSensitiveHelp(struct qemu_syscall *call)
{
    struct qemu_IShellView_ContextSensitiveHelp *c = (struct qemu_IShellView_ContextSensitiveHelp *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_ContextSensitiveHelp(view->host_shellview, c->mode);
}

#endif

struct qemu_IShellView_TranslateAccelerator
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpmsg;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_TranslateAccelerator(IShellView3 *iface, MSG *lpmsg)
{
    struct qemu_IShellView_TranslateAccelerator call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_TRANSLATEACCELERATOR);
    call.iface = (ULONG_PTR)view;
    call.lpmsg = (ULONG_PTR)lpmsg;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_TranslateAccelerator(struct qemu_syscall *call)
{
    struct qemu_IShellView_TranslateAccelerator *c = (struct qemu_IShellView_TranslateAccelerator *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_TranslateAccelerator(view->host_shellview, QEMU_G2H(c->lpmsg));
}

#endif

struct qemu_IShellView_EnableModeless
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fEnable;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_EnableModeless(IShellView3 *iface, BOOL fEnable)
{
    struct qemu_IShellView_EnableModeless call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_ENABLEMODELESS);
    call.iface = (ULONG_PTR)view;
    call.fEnable = fEnable;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_EnableModeless(struct qemu_syscall *call)
{
    struct qemu_IShellView_EnableModeless *c = (struct qemu_IShellView_EnableModeless *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_EnableModeless(view->host_shellview, c->fEnable);
}

#endif

struct qemu_IShellView_UIActivate
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t uState;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_UIActivate(IShellView3 *iface, UINT uState)
{
    struct qemu_IShellView_UIActivate call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_UIACTIVATE);
    call.iface = (ULONG_PTR)view;
    call.uState = uState;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_UIActivate(struct qemu_syscall *call)
{
    struct qemu_IShellView_UIActivate *c = (struct qemu_IShellView_UIActivate *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_UIActivate(view->host_shellview, c->uState);
}

#endif

struct qemu_IShellView_Refresh
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_Refresh(IShellView3 *iface)
{
    struct qemu_IShellView_Refresh call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_REFRESH);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_Refresh(struct qemu_syscall *call)
{
    struct qemu_IShellView_Refresh *c = (struct qemu_IShellView_Refresh *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_Refresh(view->host_shellview);
}

#endif

struct qemu_IShellView_CreateViewWindow
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t prev_view;
    uint64_t settings;
    uint64_t owner;
    uint64_t rect;
    uint64_t hWnd;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_CreateViewWindow(IShellView3 *iface, IShellView *prev_view,
        const FOLDERSETTINGS *settings, IShellBrowser *owner, RECT *rect, HWND *hWnd)
{
    struct qemu_IShellView_CreateViewWindow call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_CREATEVIEWWINDOW);
    call.iface = (ULONG_PTR)view;
    call.prev_view = (ULONG_PTR)prev_view;
    call.settings = (ULONG_PTR)settings;
    call.owner = (ULONG_PTR)owner;
    call.rect = (ULONG_PTR)rect;
    call.hWnd = (ULONG_PTR)hWnd;

    qemu_syscall(&call.super);
    *hWnd = (HWND)(ULONG_PTR)call.hWnd;

    return call.super.iret;
}

#else

void qemu_IShellView_CreateViewWindow(struct qemu_syscall *call)
{
    struct qemu_IShellView_CreateViewWindow *c = (struct qemu_IShellView_CreateViewWindow *)call;
    struct qemu_shellview *view;
    struct shellbrowser_wrapper *shellbrowser_wrapper;
    IShellBrowser *browser = NULL;
    HWND hwnd;

    WINE_TRACE("\n");
    view = QEMU_G2H(c->iface);

    if (c->prev_view)
        WINE_FIXME("prev_view not handled yet.\n");
    if (c->owner)
    {
        shellbrowser_wrapper = shellbrowser_wrapper_create(c->owner, view);
        browser = shellbrowser_wrapper_host_iface(shellbrowser_wrapper);
    }

    c->super.iret = IShellView_CreateViewWindow(view->host_shellview, QEMU_G2H(c->prev_view),
            QEMU_G2H(c->settings), browser, QEMU_G2H(c->rect), &hwnd);
    c->hWnd = QEMU_H2G(hwnd);

    if (browser)
        WINE_TRACE("Browser has ref %u\n", IShellBrowser_Release(browser));
}

#endif

struct qemu_IShellView_DestroyViewWindow
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_DestroyViewWindow(IShellView3 *iface)
{
    struct qemu_IShellView_DestroyViewWindow call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_DESTROYVIEWWINDOW);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_DestroyViewWindow(struct qemu_syscall *call)
{
    struct qemu_IShellView_DestroyViewWindow *c = (struct qemu_IShellView_DestroyViewWindow *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_DestroyViewWindow(view->host_shellview);
}

#endif

struct qemu_IShellView_GetCurrentInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpfs;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_GetCurrentInfo(IShellView3 *iface, LPFOLDERSETTINGS lpfs)
{
    struct qemu_IShellView_GetCurrentInfo call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_GETCURRENTINFO);
    call.iface = (ULONG_PTR)view;
    call.lpfs = (ULONG_PTR)lpfs;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_GetCurrentInfo(struct qemu_syscall *call)
{
    struct qemu_IShellView_GetCurrentInfo *c = (struct qemu_IShellView_GetCurrentInfo *)call;
    struct qemu_shellview *view;

    WINE_TRACE("\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_GetCurrentInfo(view->host_shellview, QEMU_G2H(c->lpfs));
}

#endif

struct qemu_IShellView_AddPropertySheetPages
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwReserved;
    uint64_t lpfn;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_AddPropertySheetPages(IShellView3 *iface, DWORD dwReserved, LPFNADDPROPSHEETPAGE lpfn, LPARAM lparam)
{
    struct qemu_IShellView_AddPropertySheetPages call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_ADDPROPERTYSHEETPAGES);
    call.iface = (ULONG_PTR)view;
    call.dwReserved = dwReserved;
    call.lpfn = (ULONG_PTR)lpfn;
    call.lparam = lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_AddPropertySheetPages(struct qemu_syscall *call)
{
    struct qemu_IShellView_AddPropertySheetPages *c = (struct qemu_IShellView_AddPropertySheetPages *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_AddPropertySheetPages(view->host_shellview, c->dwReserved, QEMU_G2H(c->lpfn), c->lparam);
}

#endif

struct qemu_IShellView_SaveViewState
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_SaveViewState(IShellView3 *iface)
{
    struct qemu_IShellView_SaveViewState call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_SAVEVIEWSTATE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_SaveViewState(struct qemu_syscall *call)
{
    struct qemu_IShellView_SaveViewState *c = (struct qemu_IShellView_SaveViewState *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_SaveViewState(view->host_shellview);
}

#endif

struct qemu_IShellView_SelectItem
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_SelectItem(IShellView3 *iface, LPCITEMIDLIST pidl, UINT flags)
{
    struct qemu_IShellView_SelectItem call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_SELECTITEM);
    call.iface = (ULONG_PTR)view;
    call.pidl = (ULONG_PTR)pidl;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_SelectItem(struct qemu_syscall *call)
{
    struct qemu_IShellView_SelectItem *c = (struct qemu_IShellView_SelectItem *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_SelectItem(view->host_shellview, QEMU_G2H(QEMU_G2H(c->pidl)), c->flags);
}

#endif

struct qemu_IShellView_GetItemObject
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t uItem;
    uint64_t riid;
    uint64_t ppvOut;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_GetItemObject(IShellView3 *iface, UINT uItem, REFIID riid, void **ppvOut)
{
    struct qemu_IShellView_GetItemObject call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW_GETITEMOBJECT);
    call.iface = (ULONG_PTR)view;
    call.uItem = uItem;
    call.riid = (ULONG_PTR)riid;
    call.ppvOut = (ULONG_PTR)ppvOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView_GetItemObject(struct qemu_syscall *call)
{
    struct qemu_IShellView_GetItemObject *c = (struct qemu_IShellView_GetItemObject *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView_GetItemObject(view->host_shellview, c->uItem, QEMU_G2H(c->riid), QEMU_G2H(c->ppvOut));
}

#endif

struct qemu_IShellView2_GetView
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t view_guid;
    uint64_t view_type;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_GetView(IShellView3 *iface, SHELLVIEWID *view_guid, ULONG view_type)
{
    struct qemu_IShellView2_GetView call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW2_GETVIEW);
    call.iface = (ULONG_PTR)view;
    call.view_guid = (ULONG_PTR)view_guid;
    call.view_type = view_type;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView2_GetView(struct qemu_syscall *call)
{
    struct qemu_IShellView2_GetView *c = (struct qemu_IShellView2_GetView *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView2_GetView(view->host_shellview, QEMU_G2H(c->view_guid), c->view_type);
}

#endif

struct qemu_IShellView2_CreateViewWindow2
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t view_params;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_CreateViewWindow2(IShellView3 *iface, SV2CVW2_PARAMS *view_params)
{
    struct qemu_IShellView2_CreateViewWindow2 call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW2_CREATEVIEWWINDOW2);
    call.iface = (ULONG_PTR)view;
    call.view_params = (ULONG_PTR)view_params;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView2_CreateViewWindow2(struct qemu_syscall *call)
{
    struct qemu_IShellView2_CreateViewWindow2 *c = (struct qemu_IShellView2_CreateViewWindow2 *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView2_CreateViewWindow2(view->host_shellview, QEMU_G2H(c->view_params));
}

#endif

struct qemu_IShellView2_HandleRename
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t new_pidl;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_HandleRename(IShellView3 *iface, LPCITEMIDLIST new_pidl)
{
    struct qemu_IShellView2_HandleRename call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW2_HANDLERENAME);
    call.iface = (ULONG_PTR)view;
    call.new_pidl = (ULONG_PTR)new_pidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView2_HandleRename(struct qemu_syscall *call)
{
    struct qemu_IShellView2_HandleRename *c = (struct qemu_IShellView2_HandleRename *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView2_HandleRename(view->host_shellview, QEMU_G2H(c->new_pidl));
}

#endif

struct qemu_IShellView2_SelectAndPositionItem
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t item;
    uint64_t flags;
    uint64_t point;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_SelectAndPositionItem(IShellView3 *iface, LPCITEMIDLIST item, UINT flags, POINT *point)
{
    struct qemu_IShellView2_SelectAndPositionItem call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW2_SELECTANDPOSITIONITEM);
    call.iface = (ULONG_PTR)view;
    call.item = (ULONG_PTR)item;
    call.flags = flags;
    call.point = (ULONG_PTR)point;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView2_SelectAndPositionItem(struct qemu_syscall *call)
{
    struct qemu_IShellView2_SelectAndPositionItem *c = (struct qemu_IShellView2_SelectAndPositionItem *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView2_SelectAndPositionItem(view->host_shellview, QEMU_G2H(c->item), c->flags, QEMU_G2H(c->point));
}

#endif

struct qemu_IShellView3_CreateViewWindow3
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t owner;
    uint64_t prev_view;
    uint64_t view_flags;
    uint64_t mask;
    uint64_t flags;
    uint64_t mode;
    uint64_t view_id;
    uint64_t rect;
    uint64_t hwnd;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI qemu_shellview_CreateViewWindow3(IShellView3 *iface, IShellBrowser *owner, IShellView *prev_view, SV3CVW3_FLAGS view_flags, FOLDERFLAGS mask, FOLDERFLAGS flags, FOLDERVIEWMODE mode, const SHELLVIEWID *view_id, const RECT *rect, HWND *hwnd)
{
    struct qemu_IShellView3_CreateViewWindow3 call;
    struct qemu_shellview *view = impl_from_IShellView3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLVIEW3_CREATEVIEWWINDOW3);
    call.iface = (ULONG_PTR)view;
    call.owner = (ULONG_PTR)owner;
    call.prev_view = (ULONG_PTR)prev_view;
    call.view_flags = view_flags;
    call.mask = mask;
    call.flags = flags;
    call.mode = mode;
    call.view_id = (ULONG_PTR)view_id;
    call.rect = (ULONG_PTR)rect;
    call.hwnd = (ULONG_PTR)hwnd;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellView3_CreateViewWindow3(struct qemu_syscall *call)
{
    struct qemu_IShellView3_CreateViewWindow3 *c = (struct qemu_IShellView3_CreateViewWindow3 *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellView3_CreateViewWindow3(view->host_shellview, QEMU_G2H(c->owner), QEMU_G2H(c->prev_view), c->view_flags, c->mask, c->flags, c->mode, QEMU_G2H(c->view_id), QEMU_G2H(c->rect), QEMU_G2H(c->hwnd));
}

#endif

struct qemu_ISVOleCmdTarget_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iid;
    uint64_t ppvObj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVOleCmdTarget_QueryInterface(IOleCommandTarget *iface, REFIID iid, void **ppvObj)
{
    struct qemu_ISVOleCmdTarget_QueryInterface call;
    struct qemu_shellview *view = impl_from_IOleCommandTarget(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVOLECMDTARGET_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.iid = (ULONG_PTR)iid;
    call.ppvObj = (ULONG_PTR)ppvObj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVOleCmdTarget_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_ISVOleCmdTarget_QueryInterface *c = (struct qemu_ISVOleCmdTarget_QueryInterface *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IOleCommandTarget_QueryInterface(view->host_cmd_target, QEMU_G2H(c->iid), QEMU_G2H(c->ppvObj));
}

#endif

struct qemu_ISVOleCmdTarget_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI ISVOleCmdTarget_AddRef(IOleCommandTarget *iface)
{
    struct qemu_ISVOleCmdTarget_AddRef call;
    struct qemu_shellview *view = impl_from_IOleCommandTarget(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVOLECMDTARGET_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVOleCmdTarget_AddRef(struct qemu_syscall *call)
{
    struct qemu_ISVOleCmdTarget_AddRef *c = (struct qemu_ISVOleCmdTarget_AddRef *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IOleCommandTarget_AddRef(view->host_cmd_target);
}

#endif

struct qemu_ISVOleCmdTarget_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI ISVOleCmdTarget_Release(IOleCommandTarget *iface)
{
    struct qemu_ISVOleCmdTarget_Release call;
    struct qemu_shellview *view = impl_from_IOleCommandTarget(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVOLECMDTARGET_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVOleCmdTarget_Release(struct qemu_syscall *call)
{
    struct qemu_ISVOleCmdTarget_Release *c = (struct qemu_ISVOleCmdTarget_Release *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IOleCommandTarget_Release(view->host_cmd_target);
}

#endif

struct qemu_ISVOleCmdTarget_QueryStatus
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pguidCmdGroup;
    uint64_t cCmds;
    uint64_t prgCmds;
    uint64_t pCmdText;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVOleCmdTarget_QueryStatus(IOleCommandTarget *iface, const GUID *pguidCmdGroup, ULONG cCmds, OLECMD *prgCmds, OLECMDTEXT *pCmdText)
{
    struct qemu_ISVOleCmdTarget_QueryStatus call;
    struct qemu_shellview *view = impl_from_IOleCommandTarget(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVOLECMDTARGET_QUERYSTATUS);
    call.iface = (ULONG_PTR)view;
    call.pguidCmdGroup = (ULONG_PTR)pguidCmdGroup;
    call.cCmds = cCmds;
    call.prgCmds = (ULONG_PTR)prgCmds;
    call.pCmdText = (ULONG_PTR)pCmdText;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVOleCmdTarget_QueryStatus(struct qemu_syscall *call)
{
    struct qemu_ISVOleCmdTarget_QueryStatus *c = (struct qemu_ISVOleCmdTarget_QueryStatus *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IOleCommandTarget_QueryStatus(view->host_cmd_target, QEMU_G2H(c->pguidCmdGroup), c->cCmds, QEMU_G2H(c->prgCmds), QEMU_G2H(c->pCmdText));
}

#endif

struct qemu_ISVOleCmdTarget_Exec
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pguidCmdGroup;
    uint64_t nCmdID;
    uint64_t nCmdexecopt;
    uint64_t pvaIn;
    uint64_t pvaOut;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVOleCmdTarget_Exec(IOleCommandTarget *iface, const GUID* pguidCmdGroup, DWORD nCmdID, DWORD nCmdexecopt, VARIANT* pvaIn, VARIANT* pvaOut)
{
    struct qemu_ISVOleCmdTarget_Exec call;
    struct qemu_shellview *view = impl_from_IOleCommandTarget(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVOLECMDTARGET_EXEC);
    call.iface = (ULONG_PTR)view;
    call.pguidCmdGroup = (ULONG_PTR)pguidCmdGroup;
    call.nCmdID = nCmdID;
    call.nCmdexecopt = nCmdexecopt;
    call.pvaIn = (ULONG_PTR)pvaIn;
    call.pvaOut = (ULONG_PTR)pvaOut;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVOleCmdTarget_Exec(struct qemu_syscall *call)
{
    struct qemu_ISVOleCmdTarget_Exec *c = (struct qemu_ISVOleCmdTarget_Exec *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IOleCommandTarget_Exec(view->host_cmd_target, QEMU_G2H(c->pguidCmdGroup), c->nCmdID, c->nCmdexecopt, QEMU_G2H(c->pvaIn), QEMU_G2H(c->pvaOut));
}

#endif

struct qemu_ISVDropTarget_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppvObj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVDropTarget_QueryInterface(IDropTarget *iface, REFIID riid, void **ppvObj)
{
    struct qemu_ISVDropTarget_QueryInterface call;
    struct qemu_shellview *view = impl_from_IDropTarget(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVDROPTARGET_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.ppvObj = (ULONG_PTR)ppvObj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVDropTarget_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_ISVDropTarget_QueryInterface *c = (struct qemu_ISVDropTarget_QueryInterface *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IDropTarget_QueryInterface(view->host_drop_target, QEMU_G2H(c->riid), QEMU_G2H(c->ppvObj));
}

#endif

struct qemu_ISVDropTarget_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI ISVDropTarget_AddRef(IDropTarget *iface)
{
    struct qemu_ISVDropTarget_AddRef call;
    struct qemu_shellview *view = impl_from_IDropTarget(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVDROPTARGET_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVDropTarget_AddRef(struct qemu_syscall *call)
{
    struct qemu_ISVDropTarget_AddRef *c = (struct qemu_ISVDropTarget_AddRef *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IDropTarget_AddRef(view->host_drop_target);
}

#endif

struct qemu_ISVDropTarget_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI ISVDropTarget_Release(IDropTarget *iface)
{
    struct qemu_ISVDropTarget_Release call;
    struct qemu_shellview *view = impl_from_IDropTarget(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVDROPTARGET_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVDropTarget_Release(struct qemu_syscall *call)
{
    struct qemu_ISVDropTarget_Release *c = (struct qemu_ISVDropTarget_Release *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IDropTarget_Release(view->host_drop_target);
}

#endif

struct qemu_ISVDropTarget_DragEnter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pDataObject;
    uint64_t grfKeyState;
    uint64_t ptX;
    uint64_t ptY;
    uint64_t pdwEffect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVDropTarget_DragEnter(IDropTarget *iface, IDataObject *pDataObject, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
    struct qemu_ISVDropTarget_DragEnter call;
    struct qemu_shellview *view = impl_from_IDropTarget(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVDROPTARGET_DRAGENTER);
    call.iface = (ULONG_PTR)view;
    call.pDataObject = (ULONG_PTR)pDataObject;
    call.grfKeyState = grfKeyState;
    call.ptX = pt.x;
    call.ptY = pt.y;
    call.pdwEffect = (ULONG_PTR)pdwEffect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVDropTarget_DragEnter(struct qemu_syscall *call)
{
    struct qemu_ISVDropTarget_DragEnter *c = (struct qemu_ISVDropTarget_DragEnter *)call;
    struct qemu_shellview *view;
    POINTL pt;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);
    pt.x = c->ptX;
    pt.y = c->ptY;

    c->super.iret = IDropTarget_DragEnter(view->host_drop_target, QEMU_G2H(c->pDataObject), c->grfKeyState, pt, QEMU_G2H(c->pdwEffect));
}

#endif

struct qemu_ISVDropTarget_DragOver
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t grfKeyState;
    uint64_t ptX, ptY;
    uint64_t pdwEffect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVDropTarget_DragOver(IDropTarget *iface, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
    struct qemu_ISVDropTarget_DragOver call;
    struct qemu_shellview *view = impl_from_IDropTarget(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVDROPTARGET_DRAGOVER);
    call.iface = (ULONG_PTR)view;
    call.grfKeyState = grfKeyState;
    call.ptX = pt.x;
    call.ptY = pt.y;
    call.pdwEffect = (ULONG_PTR)pdwEffect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVDropTarget_DragOver(struct qemu_syscall *call)
{
    struct qemu_ISVDropTarget_DragOver *c = (struct qemu_ISVDropTarget_DragOver *)call;
    struct qemu_shellview *view;
    POINTL pt;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);
    pt.x = c->ptX;
    pt.y = c->ptY;

    c->super.iret = IDropTarget_DragOver(view->host_drop_target, c->grfKeyState, pt, QEMU_G2H(c->pdwEffect));
}

#endif

struct qemu_ISVDropTarget_DragLeave
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVDropTarget_DragLeave(IDropTarget *iface)
{
    struct qemu_ISVDropTarget_DragLeave call;
    struct qemu_shellview *view = impl_from_IDropTarget(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVDROPTARGET_DRAGLEAVE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVDropTarget_DragLeave(struct qemu_syscall *call)
{
    struct qemu_ISVDropTarget_DragLeave *c = (struct qemu_ISVDropTarget_DragLeave *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IDropTarget_DragLeave(view->host_drop_target);
}

#endif

struct qemu_ISVDropTarget_Drop
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pDataObject;
    uint64_t grfKeyState;
    uint64_t ptX, ptY;
    uint64_t pdwEffect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVDropTarget_Drop(IDropTarget *iface, IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
    struct qemu_ISVDropTarget_Drop call;
    struct qemu_shellview *view = impl_from_IDropTarget(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVDROPTARGET_DROP);
    call.iface = (ULONG_PTR)view;
    call.pDataObject = (ULONG_PTR)pDataObject;
    call.grfKeyState = grfKeyState;
    call.ptX = pt.x;
    call.ptY = pt.y;
    call.pdwEffect = (ULONG_PTR)pdwEffect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVDropTarget_Drop(struct qemu_syscall *call)
{
    struct qemu_ISVDropTarget_Drop *c = (struct qemu_ISVDropTarget_Drop *)call;
    struct qemu_shellview *view;
    POINTL pt;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);
    pt.x = c->ptX;
    pt.y = c->ptY;

    c->super.iret = IDropTarget_Drop(view->host_drop_target, QEMU_G2H(c->pDataObject), c->grfKeyState, pt, QEMU_G2H(c->pdwEffect));
}

#endif

struct qemu_ISVDropSource_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppvObj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVDropSource_QueryInterface(IDropSource *iface, REFIID riid, void **ppvObj)
{
    struct qemu_ISVDropSource_QueryInterface call;
    struct qemu_shellview *view = impl_from_IDropSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVDROPSOURCE_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.ppvObj = (ULONG_PTR)ppvObj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVDropSource_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_ISVDropSource_QueryInterface *c = (struct qemu_ISVDropSource_QueryInterface *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IDropSource_QueryInterface(view->host_drop_source, QEMU_G2H(c->riid), QEMU_G2H(c->ppvObj));
}

#endif

struct qemu_ISVDropSource_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI ISVDropSource_AddRef(IDropSource *iface)
{
    struct qemu_ISVDropSource_AddRef call;
    struct qemu_shellview *view = impl_from_IDropSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVDROPSOURCE_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVDropSource_AddRef(struct qemu_syscall *call)
{
    struct qemu_ISVDropSource_AddRef *c = (struct qemu_ISVDropSource_AddRef *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IDropSource_AddRef(view->host_drop_source);
}

#endif

struct qemu_ISVDropSource_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI ISVDropSource_Release(IDropSource *iface)
{
    struct qemu_ISVDropSource_Release call;
    struct qemu_shellview *view = impl_from_IDropSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVDROPSOURCE_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVDropSource_Release(struct qemu_syscall *call)
{
    struct qemu_ISVDropSource_Release *c = (struct qemu_ISVDropSource_Release *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IDropSource_Release(view->host_drop_source);
}

#endif

struct qemu_ISVDropSource_QueryContinueDrag
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fEscapePressed;
    uint64_t grfKeyState;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVDropSource_QueryContinueDrag(IDropSource *iface, BOOL fEscapePressed, DWORD grfKeyState)
{
    struct qemu_ISVDropSource_QueryContinueDrag call;
    struct qemu_shellview *view = impl_from_IDropSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVDROPSOURCE_QUERYCONTINUEDRAG);
    call.iface = (ULONG_PTR)view;
    call.fEscapePressed = fEscapePressed;
    call.grfKeyState = grfKeyState;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVDropSource_QueryContinueDrag(struct qemu_syscall *call)
{
    struct qemu_ISVDropSource_QueryContinueDrag *c = (struct qemu_ISVDropSource_QueryContinueDrag *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IDropSource_QueryContinueDrag(view->host_drop_source, c->fEscapePressed, c->grfKeyState);
}

#endif

struct qemu_ISVDropSource_GiveFeedback
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwEffect;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVDropSource_GiveFeedback(IDropSource *iface, DWORD dwEffect)
{
    struct qemu_ISVDropSource_GiveFeedback call;
    struct qemu_shellview *view = impl_from_IDropSource(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVDROPSOURCE_GIVEFEEDBACK);
    call.iface = (ULONG_PTR)view;
    call.dwEffect = dwEffect;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVDropSource_GiveFeedback(struct qemu_syscall *call)
{
    struct qemu_ISVDropSource_GiveFeedback *c = (struct qemu_ISVDropSource_GiveFeedback *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IDropSource_GiveFeedback(view->host_drop_source, c->dwEffect);
}

#endif

struct qemu_ISVViewObject_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppvObj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVViewObject_QueryInterface(IViewObject *iface, REFIID riid, void **ppvObj)
{
    struct qemu_ISVViewObject_QueryInterface call;
    struct qemu_shellview *view = impl_from_IViewObject(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVVIEWOBJECT_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.ppvObj = (ULONG_PTR)ppvObj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVViewObject_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_ISVViewObject_QueryInterface *c = (struct qemu_ISVViewObject_QueryInterface *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IViewObject_QueryInterface(view->host_view_object, QEMU_G2H(c->riid), QEMU_G2H(c->ppvObj));
}

#endif

struct qemu_ISVViewObject_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI ISVViewObject_AddRef(IViewObject *iface)
{
    struct qemu_ISVViewObject_AddRef call;
    struct qemu_shellview *view = impl_from_IViewObject(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVVIEWOBJECT_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVViewObject_AddRef(struct qemu_syscall *call)
{
    struct qemu_ISVViewObject_AddRef *c = (struct qemu_ISVViewObject_AddRef *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IViewObject_AddRef(view->host_view_object);
}

#endif

struct qemu_ISVViewObject_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI ISVViewObject_Release(IViewObject *iface)
{
    struct qemu_ISVViewObject_Release call;
    struct qemu_shellview *view = impl_from_IViewObject(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVVIEWOBJECT_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVViewObject_Release(struct qemu_syscall *call)
{
    struct qemu_ISVViewObject_Release *c = (struct qemu_ISVViewObject_Release *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IViewObject_Release(view->host_view_object);
}

#endif

struct qemu_ISVViewObject_Draw
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwDrawAspect;
    uint64_t lindex;
    uint64_t pvAspect;
    uint64_t ptd;
    uint64_t hdcTargetDev;
    uint64_t hdcDraw;
    uint64_t lprcBounds;
    uint64_t lprcWBounds;
    uint64_t pfnContinue;
    uint64_t dwContinue;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVViewObject_Draw(IViewObject *iface, DWORD dwDrawAspect, LONG lindex, void* pvAspect, DVTARGETDEVICE* ptd, HDC hdcTargetDev, HDC hdcDraw, LPCRECTL lprcBounds, LPCRECTL lprcWBounds, BOOL (CALLBACK *pfnContinue)(ULONG_PTR dwContinue), ULONG_PTR dwContinue)
{
    struct qemu_ISVViewObject_Draw call;
    struct qemu_shellview *view = impl_from_IViewObject(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVVIEWOBJECT_DRAW);
    call.iface = (ULONG_PTR)view;
    call.dwDrawAspect = dwDrawAspect;
    call.lindex = lindex;
    call.pvAspect = (ULONG_PTR)pvAspect;
    call.ptd = (ULONG_PTR)ptd;
    call.hdcTargetDev = (ULONG_PTR)hdcTargetDev;
    call.hdcDraw = (ULONG_PTR)hdcDraw;
    call.lprcBounds = (ULONG_PTR)lprcBounds;
    call.lprcWBounds = (ULONG_PTR)lprcWBounds;
    call.pfnContinue = (ULONG_PTR)pfnContinue;
    call.dwContinue = (ULONG_PTR)dwContinue;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVViewObject_Draw(struct qemu_syscall *call)
{
    struct qemu_ISVViewObject_Draw *c = (struct qemu_ISVViewObject_Draw *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IViewObject_Draw(view->host_view_object, c->dwDrawAspect, c->lindex, QEMU_G2H(c->pvAspect), QEMU_G2H(c->ptd), QEMU_G2H(c->hdcTargetDev), QEMU_G2H(c->hdcDraw), QEMU_G2H(c->lprcBounds), QEMU_G2H(c->lprcWBounds), QEMU_G2H(c->pfnContinue), c->dwContinue);
}

#endif

struct qemu_ISVViewObject_GetColorSet
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwDrawAspect;
    uint64_t lindex;
    uint64_t pvAspect;
    uint64_t ptd;
    uint64_t hicTargetDevice;
    uint64_t ppColorSet;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVViewObject_GetColorSet(IViewObject *iface, DWORD dwDrawAspect, LONG lindex, void *pvAspect, DVTARGETDEVICE* ptd, HDC hicTargetDevice, LOGPALETTE** ppColorSet)
{
    struct qemu_ISVViewObject_GetColorSet call;
    struct qemu_shellview *view = impl_from_IViewObject(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVVIEWOBJECT_GETCOLORSET);
    call.iface = (ULONG_PTR)view;
    call.dwDrawAspect = dwDrawAspect;
    call.lindex = lindex;
    call.pvAspect = (ULONG_PTR)pvAspect;
    call.ptd = (ULONG_PTR)ptd;
    call.hicTargetDevice = (ULONG_PTR)hicTargetDevice;
    call.ppColorSet = (ULONG_PTR)ppColorSet;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVViewObject_GetColorSet(struct qemu_syscall *call)
{
    struct qemu_ISVViewObject_GetColorSet *c = (struct qemu_ISVViewObject_GetColorSet *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IViewObject_GetColorSet(view->host_view_object, c->dwDrawAspect, c->lindex, QEMU_G2H(c->pvAspect), QEMU_G2H(c->ptd), QEMU_G2H(c->hicTargetDevice), QEMU_G2H(c->ppColorSet));
}

#endif

struct qemu_ISVViewObject_Freeze
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwDrawAspect;
    uint64_t lindex;
    uint64_t pvAspect;
    uint64_t pdwFreeze;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVViewObject_Freeze(IViewObject *iface, DWORD dwDrawAspect, LONG lindex, void* pvAspect, DWORD* pdwFreeze)
{
    struct qemu_ISVViewObject_Freeze call;
    struct qemu_shellview *view = impl_from_IViewObject(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVVIEWOBJECT_FREEZE);
    call.iface = (ULONG_PTR)view;
    call.dwDrawAspect = dwDrawAspect;
    call.lindex = lindex;
    call.pvAspect = (ULONG_PTR)pvAspect;
    call.pdwFreeze = (ULONG_PTR)pdwFreeze;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVViewObject_Freeze(struct qemu_syscall *call)
{
    struct qemu_ISVViewObject_Freeze *c = (struct qemu_ISVViewObject_Freeze *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IViewObject_Freeze(view->host_view_object, c->dwDrawAspect, c->lindex, QEMU_G2H(c->pvAspect), QEMU_G2H(c->pdwFreeze));
}

#endif

struct qemu_ISVViewObject_Unfreeze
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwFreeze;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVViewObject_Unfreeze(IViewObject *iface, DWORD dwFreeze)
{
    struct qemu_ISVViewObject_Unfreeze call;
    struct qemu_shellview *view = impl_from_IViewObject(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVVIEWOBJECT_UNFREEZE);
    call.iface = (ULONG_PTR)view;
    call.dwFreeze = dwFreeze;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVViewObject_Unfreeze(struct qemu_syscall *call)
{
    struct qemu_ISVViewObject_Unfreeze *c = (struct qemu_ISVViewObject_Unfreeze *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IViewObject_Unfreeze(view->host_view_object, c->dwFreeze);
}

#endif

struct qemu_ISVViewObject_SetAdvise
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t aspects;
    uint64_t advf;
    uint64_t pAdvSink;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVViewObject_SetAdvise(IViewObject *iface, DWORD aspects, DWORD advf, IAdviseSink* pAdvSink)
{
    struct qemu_ISVViewObject_SetAdvise call;
    struct qemu_shellview *view = impl_from_IViewObject(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVVIEWOBJECT_SETADVISE);
    call.iface = (ULONG_PTR)view;
    call.aspects = aspects;
    call.advf = advf;
    call.pAdvSink = (ULONG_PTR)pAdvSink;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVViewObject_SetAdvise(struct qemu_syscall *call)
{
    struct qemu_ISVViewObject_SetAdvise *c = (struct qemu_ISVViewObject_SetAdvise *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IViewObject_SetAdvise(view->host_view_object, c->aspects, c->advf, QEMU_G2H(c->pAdvSink));
}

#endif

struct qemu_ISVViewObject_GetAdvise
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pAspects;
    uint64_t pAdvf;
    uint64_t ppAdvSink;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI ISVViewObject_GetAdvise(IViewObject *iface, DWORD* pAspects, DWORD* pAdvf, IAdviseSink** ppAdvSink)
{
    struct qemu_ISVViewObject_GetAdvise call;
    struct qemu_shellview *view = impl_from_IViewObject(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISVVIEWOBJECT_GETADVISE);
    call.iface = (ULONG_PTR)view;
    call.pAspects = (ULONG_PTR)pAspects;
    call.pAdvf = (ULONG_PTR)pAdvf;
    call.ppAdvSink = (ULONG_PTR)ppAdvSink;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ISVViewObject_GetAdvise(struct qemu_syscall *call)
{
    struct qemu_ISVViewObject_GetAdvise *c = (struct qemu_ISVViewObject_GetAdvise *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IViewObject_GetAdvise(view->host_view_object, QEMU_G2H(c->pAspects), QEMU_G2H(c->pAdvf), QEMU_G2H(c->ppAdvSink));
}

#endif

struct qemu_FolderView_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppvObj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_QueryInterface(IFolderView2 *iface, REFIID riid, void **ppvObj)
{
    struct qemu_FolderView_QueryInterface call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.ppvObj = (ULONG_PTR)ppvObj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_FolderView_QueryInterface *c = (struct qemu_FolderView_QueryInterface *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_QueryInterface(view->host_folder_view, QEMU_G2H(c->riid), QEMU_G2H(c->ppvObj));
}

#endif

struct qemu_FolderView_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI FolderView_AddRef(IFolderView2 *iface)
{
    struct qemu_FolderView_AddRef call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_AddRef(struct qemu_syscall *call)
{
    struct qemu_FolderView_AddRef *c = (struct qemu_FolderView_AddRef *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_AddRef(view->host_folder_view);
}

#endif

struct qemu_FolderView_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI FolderView_Release(IFolderView2 *iface)
{
    struct qemu_FolderView_Release call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_Release(struct qemu_syscall *call)
{
    struct qemu_FolderView_Release *c = (struct qemu_FolderView_Release *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_Release(view->host_folder_view);
}

#endif

struct qemu_FolderView_GetCurrentViewMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_GetCurrentViewMode(IFolderView2 *iface, UINT *mode)
{
    struct qemu_FolderView_GetCurrentViewMode call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_GETCURRENTVIEWMODE);
    call.iface = (ULONG_PTR)view;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_GetCurrentViewMode(struct qemu_syscall *call)
{
    struct qemu_FolderView_GetCurrentViewMode *c = (struct qemu_FolderView_GetCurrentViewMode *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetCurrentViewMode(view->host_folder_view, QEMU_G2H(c->mode));
}

#endif

struct qemu_FolderView_SetCurrentViewMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_SetCurrentViewMode(IFolderView2 *iface, UINT mode)
{
    struct qemu_FolderView_SetCurrentViewMode call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_SETCURRENTVIEWMODE);
    call.iface = (ULONG_PTR)view;
    call.mode = mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_SetCurrentViewMode(struct qemu_syscall *call)
{
    struct qemu_FolderView_SetCurrentViewMode *c = (struct qemu_FolderView_SetCurrentViewMode *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_SetCurrentViewMode(view->host_folder_view, c->mode);
}

#endif

struct qemu_FolderView_GetFolder
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_GetFolder(IFolderView2 *iface, REFIID riid, void **ppv)
{
    struct qemu_FolderView_GetFolder call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_GETFOLDER);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_GetFolder(struct qemu_syscall *call)
{
    struct qemu_FolderView_GetFolder *c = (struct qemu_FolderView_GetFolder *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetFolder(view->host_folder_view, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_FolderView_Item
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t index;
    uint64_t ppidl;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_Item(IFolderView2 *iface, int index, PITEMID_CHILD *ppidl)
{
    struct qemu_FolderView_Item call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_ITEM);
    call.iface = (ULONG_PTR)view;
    call.index = index;
    call.ppidl = (ULONG_PTR)ppidl;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_Item(struct qemu_syscall *call)
{
    struct qemu_FolderView_Item *c = (struct qemu_FolderView_Item *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_Item(view->host_folder_view, c->index, QEMU_G2H(c->ppidl));
}

#endif

struct qemu_FolderView_ItemCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t items;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_ItemCount(IFolderView2 *iface, UINT flags, int *items)
{
    struct qemu_FolderView_ItemCount call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_ITEMCOUNT);
    call.iface = (ULONG_PTR)view;
    call.flags = flags;
    call.items = (ULONG_PTR)items;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_ItemCount(struct qemu_syscall *call)
{
    struct qemu_FolderView_ItemCount *c = (struct qemu_FolderView_ItemCount *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_ItemCount(view->host_folder_view, c->flags, QEMU_G2H(c->items));
}

#endif

struct qemu_FolderView_Items
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_Items(IFolderView2 *iface, UINT flags, REFIID riid, void **ppv)
{
    struct qemu_FolderView_Items call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_ITEMS);
    call.iface = (ULONG_PTR)view;
    call.flags = flags;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_Items(struct qemu_syscall *call)
{
    struct qemu_FolderView_Items *c = (struct qemu_FolderView_Items *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_Items(view->host_folder_view, c->flags, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_FolderView_GetSelectionMarkedItem
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t item;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_GetSelectionMarkedItem(IFolderView2 *iface, int *item)
{
    struct qemu_FolderView_GetSelectionMarkedItem call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_GETSELECTIONMARKEDITEM);
    call.iface = (ULONG_PTR)view;
    call.item = (ULONG_PTR)item;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_GetSelectionMarkedItem(struct qemu_syscall *call)
{
    struct qemu_FolderView_GetSelectionMarkedItem *c = (struct qemu_FolderView_GetSelectionMarkedItem *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetSelectionMarkedItem(view->host_folder_view, QEMU_G2H(c->item));
}

#endif

struct qemu_FolderView_GetFocusedItem
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t item;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_GetFocusedItem(IFolderView2 *iface, int *item)
{
    struct qemu_FolderView_GetFocusedItem call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_GETFOCUSEDITEM);
    call.iface = (ULONG_PTR)view;
    call.item = (ULONG_PTR)item;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_GetFocusedItem(struct qemu_syscall *call)
{
    struct qemu_FolderView_GetFocusedItem *c = (struct qemu_FolderView_GetFocusedItem *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetFocusedItem(view->host_folder_view, QEMU_G2H(c->item));
}

#endif

struct qemu_FolderView_GetItemPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t ppt;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_GetItemPosition(IFolderView2 *iface, PCUITEMID_CHILD pidl, POINT *ppt)
{
    struct qemu_FolderView_GetItemPosition call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_GETITEMPOSITION);
    call.iface = (ULONG_PTR)view;
    call.pidl = (ULONG_PTR)pidl;
    call.ppt = (ULONG_PTR)ppt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_GetItemPosition(struct qemu_syscall *call)
{
    struct qemu_FolderView_GetItemPosition *c = (struct qemu_FolderView_GetItemPosition *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetItemPosition(view->host_folder_view, QEMU_G2H(c->pidl), QEMU_G2H(c->ppt));
}

#endif

struct qemu_FolderView_GetSpacing
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_GetSpacing(IFolderView2 *iface, POINT *pt)
{
    struct qemu_FolderView_GetSpacing call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_GETSPACING);
    call.iface = (ULONG_PTR)view;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_GetSpacing(struct qemu_syscall *call)
{
    struct qemu_FolderView_GetSpacing *c = (struct qemu_FolderView_GetSpacing *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetSpacing(view->host_folder_view, QEMU_G2H(c->pt));
}

#endif

struct qemu_FolderView_GetDefaultSpacing
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_GetDefaultSpacing(IFolderView2 *iface, POINT *pt)
{
    struct qemu_FolderView_GetDefaultSpacing call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_GETDEFAULTSPACING);
    call.iface = (ULONG_PTR)view;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_GetDefaultSpacing(struct qemu_syscall *call)
{
    struct qemu_FolderView_GetDefaultSpacing *c = (struct qemu_FolderView_GetDefaultSpacing *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetDefaultSpacing(view->host_folder_view, QEMU_G2H(c->pt));
}

#endif

struct qemu_FolderView_GetAutoArrange
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_GetAutoArrange(IFolderView2 *iface)
{
    struct qemu_FolderView_GetAutoArrange call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_GETAUTOARRANGE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_GetAutoArrange(struct qemu_syscall *call)
{
    struct qemu_FolderView_GetAutoArrange *c = (struct qemu_FolderView_GetAutoArrange *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetAutoArrange(view->host_folder_view);
}

#endif

struct qemu_FolderView_SelectItem
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t item;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_SelectItem(IFolderView2 *iface, int item, DWORD flags)
{
    struct qemu_FolderView_SelectItem call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_SELECTITEM);
    call.iface = (ULONG_PTR)view;
    call.item = item;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_SelectItem(struct qemu_syscall *call)
{
    struct qemu_FolderView_SelectItem *c = (struct qemu_FolderView_SelectItem *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_SelectItem(view->host_folder_view, c->item, c->flags);
}

#endif

struct qemu_FolderView_SelectAndPositionItems
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t cidl;
    uint64_t apidl;
    uint64_t apt;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView_SelectAndPositionItems(IFolderView2 *iface, UINT cidl, PCUITEMID_CHILD_ARRAY apidl, POINT *apt, DWORD flags)
{
    struct qemu_FolderView_SelectAndPositionItems call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW_SELECTANDPOSITIONITEMS);
    call.iface = (ULONG_PTR)view;
    call.cidl = cidl;
    call.apidl = (ULONG_PTR)apidl;
    call.apt = (ULONG_PTR)apt;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView_SelectAndPositionItems(struct qemu_syscall *call)
{
    struct qemu_FolderView_SelectAndPositionItems *c = (struct qemu_FolderView_SelectAndPositionItems *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_SelectAndPositionItems(view->host_folder_view, c->cidl, QEMU_G2H(c->apidl), QEMU_G2H(c->apt), c->flags);
}

#endif

struct qemu_FolderView2_SetGroupBy
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t key;
    uint64_t ascending;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_SetGroupBy(IFolderView2 *iface, REFPROPERTYKEY key, BOOL ascending)
{
    struct qemu_FolderView2_SetGroupBy call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_SETGROUPBY);
    call.iface = (ULONG_PTR)view;
    call.key = (ULONG_PTR)key;
    call.ascending = ascending;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_SetGroupBy(struct qemu_syscall *call)
{
    struct qemu_FolderView2_SetGroupBy *c = (struct qemu_FolderView2_SetGroupBy *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_SetGroupBy(view->host_folder_view, QEMU_G2H(c->key), c->ascending);
}

#endif

struct qemu_FolderView2_GetGroupBy
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pkey;
    uint64_t ascending;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_GetGroupBy(IFolderView2 *iface, PROPERTYKEY *pkey, BOOL *ascending)
{
    struct qemu_FolderView2_GetGroupBy call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_GETGROUPBY);
    call.iface = (ULONG_PTR)view;
    call.pkey = (ULONG_PTR)pkey;
    call.ascending = (ULONG_PTR)ascending;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_GetGroupBy(struct qemu_syscall *call)
{
    struct qemu_FolderView2_GetGroupBy *c = (struct qemu_FolderView2_GetGroupBy *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetGroupBy(view->host_folder_view, QEMU_G2H(c->pkey), QEMU_G2H(c->ascending));
}

#endif

struct qemu_FolderView2_SetViewProperty
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t propkey;
    uint64_t propvar;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_SetViewProperty(IFolderView2 *iface, PCUITEMID_CHILD pidl, REFPROPERTYKEY propkey, REFPROPVARIANT propvar)
{
    struct qemu_FolderView2_SetViewProperty call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_SETVIEWPROPERTY);
    call.iface = (ULONG_PTR)view;
    call.pidl = (ULONG_PTR)pidl;
    call.propkey = (ULONG_PTR)propkey;
    call.propvar = (ULONG_PTR)propvar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_SetViewProperty(struct qemu_syscall *call)
{
    struct qemu_FolderView2_SetViewProperty *c = (struct qemu_FolderView2_SetViewProperty *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_SetViewProperty(view->host_folder_view, QEMU_G2H(c->pidl), QEMU_G2H(c->propkey), QEMU_G2H(c->propvar));
}

#endif

struct qemu_FolderView2_GetViewProperty
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t propkey;
    uint64_t propvar;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_GetViewProperty(IFolderView2 *iface, PCUITEMID_CHILD pidl, REFPROPERTYKEY propkey, PROPVARIANT *propvar)
{
    struct qemu_FolderView2_GetViewProperty call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_GETVIEWPROPERTY);
    call.iface = (ULONG_PTR)view;
    call.pidl = (ULONG_PTR)pidl;
    call.propkey = (ULONG_PTR)propkey;
    call.propvar = (ULONG_PTR)propvar;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_GetViewProperty(struct qemu_syscall *call)
{
    struct qemu_FolderView2_GetViewProperty *c = (struct qemu_FolderView2_GetViewProperty *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetViewProperty(view->host_folder_view, QEMU_G2H(c->pidl), QEMU_G2H(c->propkey), QEMU_G2H(c->propvar));
}

#endif

struct qemu_FolderView2_SetTileViewProperties
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t prop_list;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_SetTileViewProperties(IFolderView2 *iface, PCUITEMID_CHILD pidl, LPCWSTR prop_list)
{
    struct qemu_FolderView2_SetTileViewProperties call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_SETTILEVIEWPROPERTIES);
    call.iface = (ULONG_PTR)view;
    call.pidl = (ULONG_PTR)pidl;
    call.prop_list = (ULONG_PTR)prop_list;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_SetTileViewProperties(struct qemu_syscall *call)
{
    struct qemu_FolderView2_SetTileViewProperties *c = (struct qemu_FolderView2_SetTileViewProperties *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_SetTileViewProperties(view->host_folder_view, QEMU_G2H(c->pidl), QEMU_G2H(c->prop_list));
}

#endif

struct qemu_FolderView2_SetExtendedTileViewProperties
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t prop_list;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_SetExtendedTileViewProperties(IFolderView2 *iface, PCUITEMID_CHILD pidl, LPCWSTR prop_list)
{
    struct qemu_FolderView2_SetExtendedTileViewProperties call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_SETEXTENDEDTILEVIEWPROPERTIES);
    call.iface = (ULONG_PTR)view;
    call.pidl = (ULONG_PTR)pidl;
    call.prop_list = (ULONG_PTR)prop_list;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_SetExtendedTileViewProperties(struct qemu_syscall *call)
{
    struct qemu_FolderView2_SetExtendedTileViewProperties *c = (struct qemu_FolderView2_SetExtendedTileViewProperties *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_SetExtendedTileViewProperties(view->host_folder_view, QEMU_G2H(c->pidl), QEMU_G2H(c->prop_list));
}

#endif

struct qemu_FolderView2_SetText
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t type;
    uint64_t text;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_SetText(IFolderView2 *iface, FVTEXTTYPE type, LPCWSTR text)
{
    struct qemu_FolderView2_SetText call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_SETTEXT);
    call.iface = (ULONG_PTR)view;
    call.type = type;
    call.text = (ULONG_PTR)text;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_SetText(struct qemu_syscall *call)
{
    struct qemu_FolderView2_SetText *c = (struct qemu_FolderView2_SetText *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_SetText(view->host_folder_view, c->type, QEMU_G2H(c->text));
}

#endif

struct qemu_FolderView2_SetCurrentFolderFlags
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mask;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_SetCurrentFolderFlags(IFolderView2 *iface, DWORD mask, DWORD flags)
{
    struct qemu_FolderView2_SetCurrentFolderFlags call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_SETCURRENTFOLDERFLAGS);
    call.iface = (ULONG_PTR)view;
    call.mask = mask;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_SetCurrentFolderFlags(struct qemu_syscall *call)
{
    struct qemu_FolderView2_SetCurrentFolderFlags *c = (struct qemu_FolderView2_SetCurrentFolderFlags *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_SetCurrentFolderFlags(view->host_folder_view, c->mask, c->flags);
}

#endif

struct qemu_FolderView2_GetCurrentFolderFlags
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_GetCurrentFolderFlags(IFolderView2 *iface, DWORD *flags)
{
    struct qemu_FolderView2_GetCurrentFolderFlags call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_GETCURRENTFOLDERFLAGS);
    call.iface = (ULONG_PTR)view;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_GetCurrentFolderFlags(struct qemu_syscall *call)
{
    struct qemu_FolderView2_GetCurrentFolderFlags *c = (struct qemu_FolderView2_GetCurrentFolderFlags *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetCurrentFolderFlags(view->host_folder_view, QEMU_G2H(c->flags));
}

#endif

struct qemu_FolderView2_GetSortColumnCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t columns;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_GetSortColumnCount(IFolderView2 *iface, int *columns)
{
    struct qemu_FolderView2_GetSortColumnCount call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_GETSORTCOLUMNCOUNT);
    call.iface = (ULONG_PTR)view;
    call.columns = (ULONG_PTR)columns;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_GetSortColumnCount(struct qemu_syscall *call)
{
    struct qemu_FolderView2_GetSortColumnCount *c = (struct qemu_FolderView2_GetSortColumnCount *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetSortColumnCount(view->host_folder_view, QEMU_G2H(c->columns));
}

#endif

struct qemu_FolderView2_SetSortColumns
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t columns;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_SetSortColumns(IFolderView2 *iface, const SORTCOLUMN *columns, int count)
{
    struct qemu_FolderView2_SetSortColumns call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_SETSORTCOLUMNS);
    call.iface = (ULONG_PTR)view;
    call.columns = (ULONG_PTR)columns;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_SetSortColumns(struct qemu_syscall *call)
{
    struct qemu_FolderView2_SetSortColumns *c = (struct qemu_FolderView2_SetSortColumns *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_SetSortColumns(view->host_folder_view, QEMU_G2H(c->columns), c->count);
}

#endif

struct qemu_FolderView2_GetSortColumns
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t columns;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_GetSortColumns(IFolderView2 *iface, SORTCOLUMN *columns, int count)
{
    struct qemu_FolderView2_GetSortColumns call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_GETSORTCOLUMNS);
    call.iface = (ULONG_PTR)view;
    call.columns = (ULONG_PTR)columns;
    call.count = count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_GetSortColumns(struct qemu_syscall *call)
{
    struct qemu_FolderView2_GetSortColumns *c = (struct qemu_FolderView2_GetSortColumns *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetSortColumns(view->host_folder_view, QEMU_G2H(c->columns), c->count);
}

#endif

struct qemu_FolderView2_GetItem
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t item;
    uint64_t riid;
    uint64_t ppv;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_GetItem(IFolderView2 *iface, int item, REFIID riid, void **ppv)
{
    struct qemu_FolderView2_GetItem call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_GETITEM);
    call.iface = (ULONG_PTR)view;
    call.item = item;
    call.riid = (ULONG_PTR)riid;
    call.ppv = (ULONG_PTR)ppv;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_GetItem(struct qemu_syscall *call)
{
    struct qemu_FolderView2_GetItem *c = (struct qemu_FolderView2_GetItem *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetItem(view->host_folder_view, c->item, QEMU_G2H(c->riid), QEMU_G2H(c->ppv));
}

#endif

struct qemu_FolderView2_GetVisibleItem
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start;
    uint64_t previous;
    uint64_t item;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_GetVisibleItem(IFolderView2 *iface, int start, BOOL previous, int *item)
{
    struct qemu_FolderView2_GetVisibleItem call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_GETVISIBLEITEM);
    call.iface = (ULONG_PTR)view;
    call.start = start;
    call.previous = previous;
    call.item = (ULONG_PTR)item;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_GetVisibleItem(struct qemu_syscall *call)
{
    struct qemu_FolderView2_GetVisibleItem *c = (struct qemu_FolderView2_GetVisibleItem *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetVisibleItem(view->host_folder_view, c->start, c->previous, QEMU_G2H(c->item));
}

#endif

struct qemu_FolderView2_GetSelectedItem
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t start;
    uint64_t item;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_GetSelectedItem(IFolderView2 *iface, int start, int *item)
{
    struct qemu_FolderView2_GetSelectedItem call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_GETSELECTEDITEM);
    call.iface = (ULONG_PTR)view;
    call.start = start;
    call.item = (ULONG_PTR)item;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_GetSelectedItem(struct qemu_syscall *call)
{
    struct qemu_FolderView2_GetSelectedItem *c = (struct qemu_FolderView2_GetSelectedItem *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetSelectedItem(view->host_folder_view, c->start, QEMU_G2H(c->item));
}

#endif

struct qemu_FolderView2_GetSelection
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t none_implies_folder;
    uint64_t array;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_GetSelection(IFolderView2 *iface, BOOL none_implies_folder, IShellItemArray **array)
{
    struct qemu_FolderView2_GetSelection call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_GETSELECTION);
    call.iface = (ULONG_PTR)view;
    call.none_implies_folder = none_implies_folder;
    call.array = (ULONG_PTR)array;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_GetSelection(struct qemu_syscall *call)
{
    struct qemu_FolderView2_GetSelection *c = (struct qemu_FolderView2_GetSelection *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetSelection(view->host_folder_view, c->none_implies_folder, QEMU_G2H(c->array));
}

#endif

struct qemu_FolderView2_GetSelectionState
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_GetSelectionState(IFolderView2 *iface, PCUITEMID_CHILD pidl, DWORD *flags)
{
    struct qemu_FolderView2_GetSelectionState call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_GETSELECTIONSTATE);
    call.iface = (ULONG_PTR)view;
    call.pidl = (ULONG_PTR)pidl;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_GetSelectionState(struct qemu_syscall *call)
{
    struct qemu_FolderView2_GetSelectionState *c = (struct qemu_FolderView2_GetSelectionState *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetSelectionState(view->host_folder_view, QEMU_G2H(c->pidl), QEMU_G2H(c->flags));
}

#endif

struct qemu_FolderView2_InvokeVerbOnSelection
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t verb;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_InvokeVerbOnSelection(IFolderView2 *iface, LPCSTR verb)
{
    struct qemu_FolderView2_InvokeVerbOnSelection call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_INVOKEVERBONSELECTION);
    call.iface = (ULONG_PTR)view;
    call.verb = (ULONG_PTR)verb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_InvokeVerbOnSelection(struct qemu_syscall *call)
{
    struct qemu_FolderView2_InvokeVerbOnSelection *c = (struct qemu_FolderView2_InvokeVerbOnSelection *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_InvokeVerbOnSelection(view->host_folder_view, QEMU_G2H(c->verb));
}

#endif

struct qemu_FolderView2_SetViewModeAndIconSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mode;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_SetViewModeAndIconSize(IFolderView2 *iface, FOLDERVIEWMODE mode, int size)
{
    struct qemu_FolderView2_SetViewModeAndIconSize call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_SETVIEWMODEANDICONSIZE);
    call.iface = (ULONG_PTR)view;
    call.mode = mode;
    call.size = size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_SetViewModeAndIconSize(struct qemu_syscall *call)
{
    struct qemu_FolderView2_SetViewModeAndIconSize *c = (struct qemu_FolderView2_SetViewModeAndIconSize *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_SetViewModeAndIconSize(view->host_folder_view, c->mode, c->size);
}

#endif

struct qemu_FolderView2_GetViewModeAndIconSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mode;
    uint64_t size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_GetViewModeAndIconSize(IFolderView2 *iface, FOLDERVIEWMODE *mode, int *size)
{
    struct qemu_FolderView2_GetViewModeAndIconSize call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_GETVIEWMODEANDICONSIZE);
    call.iface = (ULONG_PTR)view;
    call.mode = (ULONG_PTR)mode;
    call.size = (ULONG_PTR)size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_GetViewModeAndIconSize(struct qemu_syscall *call)
{
    struct qemu_FolderView2_GetViewModeAndIconSize *c = (struct qemu_FolderView2_GetViewModeAndIconSize *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetViewModeAndIconSize(view->host_folder_view, QEMU_G2H(c->mode), QEMU_G2H(c->size));
}

#endif

struct qemu_FolderView2_SetGroupSubsetCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t visible_rows;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_SetGroupSubsetCount(IFolderView2 *iface, UINT visible_rows)
{
    struct qemu_FolderView2_SetGroupSubsetCount call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_SETGROUPSUBSETCOUNT);
    call.iface = (ULONG_PTR)view;
    call.visible_rows = visible_rows;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_SetGroupSubsetCount(struct qemu_syscall *call)
{
    struct qemu_FolderView2_SetGroupSubsetCount *c = (struct qemu_FolderView2_SetGroupSubsetCount *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_SetGroupSubsetCount(view->host_folder_view, c->visible_rows);
}

#endif

struct qemu_FolderView2_GetGroupSubsetCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t visible_rows;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_GetGroupSubsetCount(IFolderView2 *iface, UINT *visible_rows)
{
    struct qemu_FolderView2_GetGroupSubsetCount call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_GETGROUPSUBSETCOUNT);
    call.iface = (ULONG_PTR)view;
    call.visible_rows = (ULONG_PTR)visible_rows;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_GetGroupSubsetCount(struct qemu_syscall *call)
{
    struct qemu_FolderView2_GetGroupSubsetCount *c = (struct qemu_FolderView2_GetGroupSubsetCount *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_GetGroupSubsetCount(view->host_folder_view, QEMU_G2H(c->visible_rows));
}

#endif

struct qemu_FolderView2_SetRedraw
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t redraw;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_SetRedraw(IFolderView2 *iface, BOOL redraw)
{
    struct qemu_FolderView2_SetRedraw call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_SETREDRAW);
    call.iface = (ULONG_PTR)view;
    call.redraw = redraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_SetRedraw(struct qemu_syscall *call)
{
    struct qemu_FolderView2_SetRedraw *c = (struct qemu_FolderView2_SetRedraw *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_SetRedraw(view->host_folder_view, c->redraw);
}

#endif

struct qemu_FolderView2_IsMoveInSameFolder
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_IsMoveInSameFolder(IFolderView2 *iface)
{
    struct qemu_FolderView2_IsMoveInSameFolder call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_ISMOVEINSAMEFOLDER);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_IsMoveInSameFolder(struct qemu_syscall *call)
{
    struct qemu_FolderView2_IsMoveInSameFolder *c = (struct qemu_FolderView2_IsMoveInSameFolder *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_IsMoveInSameFolder(view->host_folder_view);
}

#endif

struct qemu_FolderView2_DoRename
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI FolderView2_DoRename(IFolderView2 *iface)
{
    struct qemu_FolderView2_DoRename call;
    struct qemu_shellview *view = impl_from_IFolderView2(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_FOLDERVIEW2_DORENAME);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FolderView2_DoRename(struct qemu_syscall *call)
{
    struct qemu_FolderView2_DoRename *c = (struct qemu_FolderView2_DoRename *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IFolderView2_DoRename(view->host_folder_view);
}

#endif

struct qemu_IShellFolderView_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppvObj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnQueryInterface(IShellFolderView *iface, REFIID riid, void **ppvObj)
{
    struct qemu_IShellFolderView_QueryInterface call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.ppvObj = (ULONG_PTR)ppvObj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_QueryInterface *c = (struct qemu_IShellFolderView_QueryInterface *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_QueryInterface(view->host_shell_folder_view, QEMU_G2H(c->riid), QEMU_G2H(c->ppvObj));
}

#endif

struct qemu_IShellFolderView_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IShellFolderView_fnAddRef(IShellFolderView *iface)
{
    struct qemu_IShellFolderView_AddRef call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_AddRef(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_AddRef *c = (struct qemu_IShellFolderView_AddRef *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_AddRef(view->host_shell_folder_view);
}

#endif

struct qemu_IShellFolderView_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI IShellFolderView_fnRelease(IShellFolderView *iface)
{
    struct qemu_IShellFolderView_Release call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_Release(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_Release *c = (struct qemu_IShellFolderView_Release *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_Release(view->host_shell_folder_view);
}

#endif

struct qemu_IShellFolderView_Rearrange
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sort;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnRearrange(IShellFolderView *iface, LPARAM sort)
{
    struct qemu_IShellFolderView_Rearrange call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_REARRANGE);
    call.iface = (ULONG_PTR)view;
    call.sort = sort;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_Rearrange(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_Rearrange *c = (struct qemu_IShellFolderView_Rearrange *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_Rearrange(view->host_shell_folder_view, c->sort);
}

#endif

struct qemu_IShellFolderView_GetArrangeParam
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sort;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnGetArrangeParam(IShellFolderView *iface, LPARAM *sort)
{
    struct qemu_IShellFolderView_GetArrangeParam call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_GETARRANGEPARAM);
    call.iface = (ULONG_PTR)view;
    call.sort = (ULONG_PTR)sort;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_GetArrangeParam(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_GetArrangeParam *c = (struct qemu_IShellFolderView_GetArrangeParam *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_GetArrangeParam(view->host_shell_folder_view, QEMU_G2H(c->sort));
}

#endif

struct qemu_IShellFolderView_ArrangeGrid
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnArrangeGrid(IShellFolderView *iface)
{
    struct qemu_IShellFolderView_ArrangeGrid call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_ARRANGEGRID);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_ArrangeGrid(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_ArrangeGrid *c = (struct qemu_IShellFolderView_ArrangeGrid *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_ArrangeGrid(view->host_shell_folder_view);
}

#endif

struct qemu_IShellFolderView_AutoArrange
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnAutoArrange(IShellFolderView *iface)
{
    struct qemu_IShellFolderView_AutoArrange call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_AUTOARRANGE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_AutoArrange(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_AutoArrange *c = (struct qemu_IShellFolderView_AutoArrange *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_AutoArrange(view->host_shell_folder_view);
}

#endif

struct qemu_IShellFolderView_GetAutoArrange
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnGetAutoArrange(IShellFolderView *iface)
{
    struct qemu_IShellFolderView_GetAutoArrange call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_GETAUTOARRANGE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_GetAutoArrange(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_GetAutoArrange *c = (struct qemu_IShellFolderView_GetAutoArrange *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_GetAutoArrange(view->host_shell_folder_view);
}

#endif

struct qemu_IShellFolderView_AddObject
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t item;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnAddObject(IShellFolderView *iface, PITEMID_CHILD pidl, UINT *item)
{
    struct qemu_IShellFolderView_AddObject call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_ADDOBJECT);
    call.iface = (ULONG_PTR)view;
    call.pidl = (ULONG_PTR)pidl;
    call.item = (ULONG_PTR)item;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_AddObject(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_AddObject *c = (struct qemu_IShellFolderView_AddObject *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_AddObject(view->host_shell_folder_view, QEMU_G2H(c->pidl), QEMU_G2H(c->item));
}

#endif

struct qemu_IShellFolderView_GetObject
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t item;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnGetObject(IShellFolderView *iface, PITEMID_CHILD *pidl, UINT item)
{
    struct qemu_IShellFolderView_GetObject call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_GETOBJECT);
    call.iface = (ULONG_PTR)view;
    call.pidl = (ULONG_PTR)pidl;
    call.item = item;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_GetObject(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_GetObject *c = (struct qemu_IShellFolderView_GetObject *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_GetObject(view->host_shell_folder_view, QEMU_G2H(QEMU_G2H(c->pidl)), c->item);
}

#endif

struct qemu_IShellFolderView_RemoveObject
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t item;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnRemoveObject(IShellFolderView *iface, PITEMID_CHILD pidl, UINT *item)
{
    struct qemu_IShellFolderView_RemoveObject call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_REMOVEOBJECT);
    call.iface = (ULONG_PTR)view;
    call.pidl = (ULONG_PTR)pidl;
    call.item = (ULONG_PTR)item;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_RemoveObject(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_RemoveObject *c = (struct qemu_IShellFolderView_RemoveObject *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_RemoveObject(view->host_shell_folder_view, QEMU_G2H(c->pidl), QEMU_G2H(c->item));
}

#endif

struct qemu_IShellFolderView_GetObjectCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnGetObjectCount(IShellFolderView *iface, UINT *count)
{
    struct qemu_IShellFolderView_GetObjectCount call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_GETOBJECTCOUNT);
    call.iface = (ULONG_PTR)view;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_GetObjectCount(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_GetObjectCount *c = (struct qemu_IShellFolderView_GetObjectCount *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_GetObjectCount(view->host_shell_folder_view, QEMU_G2H(c->count));
}

#endif

struct qemu_IShellFolderView_SetObjectCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t count;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnSetObjectCount(IShellFolderView *iface, UINT count, UINT flags)
{
    struct qemu_IShellFolderView_SetObjectCount call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_SETOBJECTCOUNT);
    call.iface = (ULONG_PTR)view;
    call.count = count;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_SetObjectCount(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_SetObjectCount *c = (struct qemu_IShellFolderView_SetObjectCount *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_SetObjectCount(view->host_shell_folder_view, c->count, c->flags);
}

#endif

struct qemu_IShellFolderView_UpdateObject
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl_old;
    uint64_t pidl_new;
    uint64_t item;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnUpdateObject(IShellFolderView *iface, PITEMID_CHILD pidl_old, PITEMID_CHILD pidl_new, UINT *item)
{
    struct qemu_IShellFolderView_UpdateObject call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_UPDATEOBJECT);
    call.iface = (ULONG_PTR)view;
    call.pidl_old = (ULONG_PTR)pidl_old;
    call.pidl_new = (ULONG_PTR)pidl_new;
    call.item = (ULONG_PTR)item;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_UpdateObject(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_UpdateObject *c = (struct qemu_IShellFolderView_UpdateObject *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_UpdateObject(view->host_shell_folder_view, QEMU_G2H(c->pidl_old), QEMU_G2H(c->pidl_new), QEMU_G2H(c->item));
}

#endif

struct qemu_IShellFolderView_RefreshObject
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t item;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnRefreshObject(IShellFolderView *iface, PITEMID_CHILD pidl, UINT *item)
{
    struct qemu_IShellFolderView_RefreshObject call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_REFRESHOBJECT);
    call.iface = (ULONG_PTR)view;
    call.pidl = (ULONG_PTR)pidl;
    call.item = (ULONG_PTR)item;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_RefreshObject(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_RefreshObject *c = (struct qemu_IShellFolderView_RefreshObject *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_RefreshObject(view->host_shell_folder_view, QEMU_G2H(c->pidl), QEMU_G2H(c->item));
}

#endif

struct qemu_IShellFolderView_SetRedraw
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t redraw;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnSetRedraw(IShellFolderView *iface, BOOL redraw)
{
    struct qemu_IShellFolderView_SetRedraw call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_SETREDRAW);
    call.iface = (ULONG_PTR)view;
    call.redraw = redraw;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_SetRedraw(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_SetRedraw *c = (struct qemu_IShellFolderView_SetRedraw *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_SetRedraw(view->host_shell_folder_view, c->redraw);
}

#endif

struct qemu_IShellFolderView_GetSelectedCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t count;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnGetSelectedCount(IShellFolderView *iface, UINT *count)
{
    struct qemu_IShellFolderView_GetSelectedCount call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_GETSELECTEDCOUNT);
    call.iface = (ULONG_PTR)view;
    call.count = (ULONG_PTR)count;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_GetSelectedCount(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_GetSelectedCount *c = (struct qemu_IShellFolderView_GetSelectedCount *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_GetSelectedCount(view->host_shell_folder_view, QEMU_G2H(c->count));
}

#endif

struct qemu_IShellFolderView_GetSelectedObjects
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t items;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnGetSelectedObjects(IShellFolderView *iface, PCITEMID_CHILD **pidl, UINT *items)
{
    struct qemu_IShellFolderView_GetSelectedObjects call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_GETSELECTEDOBJECTS);
    call.iface = (ULONG_PTR)view;
    call.pidl = (ULONG_PTR)pidl;
    call.items = (ULONG_PTR)items;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_GetSelectedObjects(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_GetSelectedObjects *c = (struct qemu_IShellFolderView_GetSelectedObjects *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_GetSelectedObjects(view->host_shell_folder_view, QEMU_G2H(QEMU_G2H(c->pidl)), QEMU_G2H(c->items));
}

#endif

struct qemu_IShellFolderView_IsDropOnSource
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t drop_target;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnIsDropOnSource(IShellFolderView *iface, IDropTarget *drop_target)
{
    struct qemu_IShellFolderView_IsDropOnSource call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_ISDROPONSOURCE);
    call.iface = (ULONG_PTR)view;
    call.drop_target = (ULONG_PTR)drop_target;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_IsDropOnSource(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_IsDropOnSource *c = (struct qemu_IShellFolderView_IsDropOnSource *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_IsDropOnSource(view->host_shell_folder_view, QEMU_G2H(c->drop_target));
}

#endif

struct qemu_IShellFolderView_GetDragPoint
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnGetDragPoint(IShellFolderView *iface, POINT *pt)
{
    struct qemu_IShellFolderView_GetDragPoint call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_GETDRAGPOINT);
    call.iface = (ULONG_PTR)view;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_GetDragPoint(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_GetDragPoint *c = (struct qemu_IShellFolderView_GetDragPoint *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_GetDragPoint(view->host_shell_folder_view, QEMU_G2H(c->pt));
}

#endif

struct qemu_IShellFolderView_GetDropPoint
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnGetDropPoint(IShellFolderView *iface, POINT *pt)
{
    struct qemu_IShellFolderView_GetDropPoint call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_GETDROPPOINT);
    call.iface = (ULONG_PTR)view;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_GetDropPoint(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_GetDropPoint *c = (struct qemu_IShellFolderView_GetDropPoint *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_GetDropPoint(view->host_shell_folder_view, QEMU_G2H(c->pt));
}

#endif

struct qemu_IShellFolderView_MoveIcons
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t obj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnMoveIcons(IShellFolderView *iface, IDataObject *obj)
{
    struct qemu_IShellFolderView_MoveIcons call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_MOVEICONS);
    call.iface = (ULONG_PTR)view;
    call.obj = (ULONG_PTR)obj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_MoveIcons(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_MoveIcons *c = (struct qemu_IShellFolderView_MoveIcons *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_MoveIcons(view->host_shell_folder_view, QEMU_G2H(c->obj));
}

#endif

struct qemu_IShellFolderView_SetItemPos
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pidl;
    uint64_t pt;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnSetItemPos(IShellFolderView *iface, PCUITEMID_CHILD pidl, POINT *pt)
{
    struct qemu_IShellFolderView_SetItemPos call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_SETITEMPOS);
    call.iface = (ULONG_PTR)view;
    call.pidl = (ULONG_PTR)pidl;
    call.pt = (ULONG_PTR)pt;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_SetItemPos(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_SetItemPos *c = (struct qemu_IShellFolderView_SetItemPos *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_SetItemPos(view->host_shell_folder_view, QEMU_G2H(c->pidl), QEMU_G2H(c->pt));
}

#endif

struct qemu_IShellFolderView_IsBkDropTarget
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t drop_target;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnIsBkDropTarget(IShellFolderView *iface, IDropTarget *drop_target)
{
    struct qemu_IShellFolderView_IsBkDropTarget call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_ISBKDROPTARGET);
    call.iface = (ULONG_PTR)view;
    call.drop_target = (ULONG_PTR)drop_target;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_IsBkDropTarget(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_IsBkDropTarget *c = (struct qemu_IShellFolderView_IsBkDropTarget *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_IsBkDropTarget(view->host_shell_folder_view, QEMU_G2H(c->drop_target));
}

#endif

struct qemu_IShellFolderView_SetClipboard
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t move;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnSetClipboard(IShellFolderView *iface, BOOL move)
{
    struct qemu_IShellFolderView_SetClipboard call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_SETCLIPBOARD);
    call.iface = (ULONG_PTR)view;
    call.move = move;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_SetClipboard(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_SetClipboard *c = (struct qemu_IShellFolderView_SetClipboard *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_SetClipboard(view->host_shell_folder_view, c->move);
}

#endif

struct qemu_IShellFolderView_SetPoints
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t obj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnSetPoints(IShellFolderView *iface, IDataObject *obj)
{
    struct qemu_IShellFolderView_SetPoints call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_SETPOINTS);
    call.iface = (ULONG_PTR)view;
    call.obj = (ULONG_PTR)obj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_SetPoints(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_SetPoints *c = (struct qemu_IShellFolderView_SetPoints *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_SetPoints(view->host_shell_folder_view, QEMU_G2H(c->obj));
}

#endif

struct qemu_IShellFolderView_GetItemSpacing
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t spacing;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnGetItemSpacing(IShellFolderView *iface, ITEMSPACING *spacing)
{
    struct qemu_IShellFolderView_GetItemSpacing call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_GETITEMSPACING);
    call.iface = (ULONG_PTR)view;
    call.spacing = (ULONG_PTR)spacing;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_GetItemSpacing(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_GetItemSpacing *c = (struct qemu_IShellFolderView_GetItemSpacing *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_GetItemSpacing(view->host_shell_folder_view, QEMU_G2H(c->spacing));
}

#endif

struct qemu_IShellFolderView_SetCallback
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t new_cb;
    uint64_t old_cb;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnSetCallback(IShellFolderView *iface, IShellFolderViewCB *new_cb, IShellFolderViewCB **old_cb)
{
    struct qemu_IShellFolderView_SetCallback call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_SETCALLBACK);
    call.iface = (ULONG_PTR)view;
    call.new_cb = (ULONG_PTR)new_cb;
    call.old_cb = (ULONG_PTR)old_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_SetCallback(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_SetCallback *c = (struct qemu_IShellFolderView_SetCallback *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_SetCallback(view->host_shell_folder_view, QEMU_G2H(c->new_cb), QEMU_G2H(c->old_cb));
}

#endif

struct qemu_IShellFolderView_Select
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnSelect(IShellFolderView *iface, UINT flags)
{
    struct qemu_IShellFolderView_Select call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_SELECT);
    call.iface = (ULONG_PTR)view;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_Select(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_Select *c = (struct qemu_IShellFolderView_Select *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_Select(view->host_shell_folder_view, c->flags);
}

#endif

struct qemu_IShellFolderView_QuerySupport
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t support;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnQuerySupport(IShellFolderView *iface, UINT *support)
{
    struct qemu_IShellFolderView_QuerySupport call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_QUERYSUPPORT);
    call.iface = (ULONG_PTR)view;
    call.support = (ULONG_PTR)support;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_QuerySupport(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_QuerySupport *c = (struct qemu_IShellFolderView_QuerySupport *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_QuerySupport(view->host_shell_folder_view, QEMU_G2H(c->support));
}

#endif

struct qemu_IShellFolderView_SetAutomationObject
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t disp;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IShellFolderView_fnSetAutomationObject(IShellFolderView *iface, IDispatch *disp)
{
    struct qemu_IShellFolderView_SetAutomationObject call;
    struct qemu_shellview *view = impl_from_IShellFolderView(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_ISHELLFOLDERVIEW_SETAUTOMATIONOBJECT);
    call.iface = (ULONG_PTR)view;
    call.disp = (ULONG_PTR)disp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IShellFolderView_SetAutomationObject(struct qemu_syscall *call)
{
    struct qemu_IShellFolderView_SetAutomationObject *c = (struct qemu_IShellFolderView_SetAutomationObject *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderView_SetAutomationObject(view->host_shell_folder_view, QEMU_G2H(c->disp));
}

#endif

struct qemu_shellfolderviewdual_QueryInterface
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t ppvObj;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_QueryInterface(IShellFolderViewDual3 *iface, REFIID riid, void **ppvObj)
{
    struct qemu_shellfolderviewdual_QueryInterface call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_QUERYINTERFACE);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.ppvObj = (ULONG_PTR)ppvObj;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_QueryInterface(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_QueryInterface *c = (struct qemu_shellfolderviewdual_QueryInterface *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_QueryInterface(view->host_dual_view, QEMU_G2H(c->riid), QEMU_G2H(c->ppvObj));
}

#endif

struct qemu_shellfolderviewdual_AddRef
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI shellfolderviewdual_AddRef(IShellFolderViewDual3 *iface)
{
    struct qemu_shellfolderviewdual_AddRef call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_ADDREF);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_AddRef(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_AddRef *c = (struct qemu_shellfolderviewdual_AddRef *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_AddRef(view->host_dual_view);
}

#endif

struct qemu_shellfolderviewdual_Release
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static ULONG WINAPI shellfolderviewdual_Release(IShellFolderViewDual3 *iface)
{
    struct qemu_shellfolderviewdual_Release call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_RELEASE);
    call.iface = (ULONG_PTR)view;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_Release(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_Release *c = (struct qemu_shellfolderviewdual_Release *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_Release(view->host_dual_view);
}

#endif

struct qemu_shellfolderviewdual_GetTypeInfoCount
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t pctinfo;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_GetTypeInfoCount(IShellFolderViewDual3 *iface, UINT *pctinfo)
{
    struct qemu_shellfolderviewdual_GetTypeInfoCount call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GETTYPEINFOCOUNT);
    call.iface = (ULONG_PTR)view;
    call.pctinfo = (ULONG_PTR)pctinfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_GetTypeInfoCount(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_GetTypeInfoCount *c = (struct qemu_shellfolderviewdual_GetTypeInfoCount *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_GetTypeInfoCount(view->host_dual_view, QEMU_G2H(c->pctinfo));
}

#endif

struct qemu_shellfolderviewdual_GetTypeInfo
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t iTInfo;
    uint64_t lcid;
    uint64_t ppTInfo;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_GetTypeInfo(IShellFolderViewDual3 *iface, UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
    struct qemu_shellfolderviewdual_GetTypeInfo call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GETTYPEINFO);
    call.iface = (ULONG_PTR)view;
    call.iTInfo = iTInfo;
    call.lcid = lcid;
    call.ppTInfo = (ULONG_PTR)ppTInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_GetTypeInfo(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_GetTypeInfo *c = (struct qemu_shellfolderviewdual_GetTypeInfo *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_GetTypeInfo(view->host_dual_view, c->iTInfo, c->lcid, QEMU_G2H(c->ppTInfo));
}

#endif

struct qemu_shellfolderviewdual_GetIDsOfNames
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t riid;
    uint64_t rgszNames;
    uint64_t cNames;
    uint64_t lcid;
    uint64_t rgDispId;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_GetIDsOfNames(IShellFolderViewDual3 *iface, REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
    struct qemu_shellfolderviewdual_GetIDsOfNames call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GETIDSOFNAMES);
    call.iface = (ULONG_PTR)view;
    call.riid = (ULONG_PTR)riid;
    call.rgszNames = (ULONG_PTR)rgszNames;
    call.cNames = cNames;
    call.lcid = lcid;
    call.rgDispId = (ULONG_PTR)rgDispId;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_GetIDsOfNames(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_GetIDsOfNames *c = (struct qemu_shellfolderviewdual_GetIDsOfNames *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_GetIDsOfNames(view->host_dual_view, QEMU_G2H(c->riid), QEMU_G2H(c->rgszNames), c->cNames, c->lcid, QEMU_G2H(c->rgDispId));
}

#endif

struct qemu_shellfolderviewdual_Invoke
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dispIdMember;
    uint64_t riid;
    uint64_t lcid;
    uint64_t wFlags;
    uint64_t pDispParams;
    uint64_t pVarResult;
    uint64_t pExcepInfo;
    uint64_t puArgErr;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_Invoke(IShellFolderViewDual3 *iface, DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    struct qemu_shellfolderviewdual_Invoke call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_INVOKE);
    call.iface = (ULONG_PTR)view;
    call.dispIdMember = dispIdMember;
    call.riid = (ULONG_PTR)riid;
    call.lcid = lcid;
    call.wFlags = wFlags;
    call.pDispParams = (ULONG_PTR)pDispParams;
    call.pVarResult = (ULONG_PTR)pVarResult;
    call.pExcepInfo = (ULONG_PTR)pExcepInfo;
    call.puArgErr = (ULONG_PTR)puArgErr;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_Invoke(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_Invoke *c = (struct qemu_shellfolderviewdual_Invoke *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_Invoke(view->host_dual_view, c->dispIdMember, QEMU_G2H(c->riid), c->lcid, c->wFlags, QEMU_G2H(c->pDispParams), QEMU_G2H(c->pVarResult), QEMU_G2H(c->pExcepInfo), QEMU_G2H(c->puArgErr));
}

#endif

struct qemu_shellfolderviewdual_get_Application
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t disp;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_get_Application(IShellFolderViewDual3 *iface, IDispatch **disp)
{
    struct qemu_shellfolderviewdual_get_Application call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GET_APPLICATION);
    call.iface = (ULONG_PTR)view;
    call.disp = (ULONG_PTR)disp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_get_Application(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_get_Application *c = (struct qemu_shellfolderviewdual_get_Application *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_get_Application(view->host_dual_view, QEMU_G2H(c->disp));
}

#endif

struct qemu_shellfolderviewdual_get_Parent
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t disp;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_get_Parent(IShellFolderViewDual3 *iface, IDispatch **disp)
{
    struct qemu_shellfolderviewdual_get_Parent call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GET_PARENT);
    call.iface = (ULONG_PTR)view;
    call.disp = (ULONG_PTR)disp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_get_Parent(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_get_Parent *c = (struct qemu_shellfolderviewdual_get_Parent *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_get_Parent(view->host_dual_view, QEMU_G2H(c->disp));
}

#endif

struct qemu_shellfolderviewdual_get_Folder
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t folder;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_get_Folder(IShellFolderViewDual3 *iface, Folder **folder)
{
    struct qemu_shellfolderviewdual_get_Folder call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GET_FOLDER);
    call.iface = (ULONG_PTR)view;
    call.folder = (ULONG_PTR)folder;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_get_Folder(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_get_Folder *c = (struct qemu_shellfolderviewdual_get_Folder *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_get_Folder(view->host_dual_view, QEMU_G2H(c->folder));
}

#endif

struct qemu_shellfolderviewdual_SelectedItems
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t items;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_SelectedItems(IShellFolderViewDual3 *iface, FolderItems **items)
{
    struct qemu_shellfolderviewdual_SelectedItems call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_SELECTEDITEMS);
    call.iface = (ULONG_PTR)view;
    call.items = (ULONG_PTR)items;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_SelectedItems(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_SelectedItems *c = (struct qemu_shellfolderviewdual_SelectedItems *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_SelectedItems(view->host_dual_view, QEMU_G2H(c->items));
}

#endif

struct qemu_shellfolderviewdual_get_FocusedItem
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t item;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_get_FocusedItem(IShellFolderViewDual3 *iface, FolderItem **item)
{
    struct qemu_shellfolderviewdual_get_FocusedItem call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GET_FOCUSEDITEM);
    call.iface = (ULONG_PTR)view;
    call.item = (ULONG_PTR)item;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_get_FocusedItem(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_get_FocusedItem *c = (struct qemu_shellfolderviewdual_get_FocusedItem *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_get_FocusedItem(view->host_dual_view, QEMU_G2H(c->item));
}

#endif

struct qemu_shellfolderviewdual_SelectItem
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t v;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_SelectItem(IShellFolderViewDual3 *iface, VARIANT *v, int flags)
{
    struct qemu_shellfolderviewdual_SelectItem call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_SELECTITEM);
    call.iface = (ULONG_PTR)view;
    call.v = (ULONG_PTR)v;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_SelectItem(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_SelectItem *c = (struct qemu_shellfolderviewdual_SelectItem *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_SelectItem(view->host_dual_view, QEMU_G2H(c->v), c->flags);
}

#endif

struct qemu_shellfolderviewdual_PopupItemMenu
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t item;
    uint64_t vx;
    uint64_t vy;
    uint64_t command;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_PopupItemMenu(IShellFolderViewDual3 *iface, FolderItem *item, VARIANT vx, VARIANT vy, BSTR *command)
{
    struct qemu_shellfolderviewdual_PopupItemMenu call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_POPUPITEMMENU);
    call.iface = (ULONG_PTR)view;
    call.item = (ULONG_PTR)item;
    call.vx = (ULONG_PTR)&vx;
    call.vy = (ULONG_PTR)&vy;
    call.command = (ULONG_PTR)command;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_PopupItemMenu(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_PopupItemMenu *c = (struct qemu_shellfolderviewdual_PopupItemMenu *)call;
    struct qemu_shellview *view;
    VARIANT vx, vy;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    memset(&vx, 0, sizeof(vx));
    memset(&vy, 0, sizeof(vy));

    c->super.iret = IShellFolderViewDual3_PopupItemMenu(view->host_dual_view, QEMU_G2H(c->item), vx, vy, QEMU_G2H(c->command));
}

#endif

struct qemu_shellfolderviewdual_get_Script
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t disp;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_get_Script(IShellFolderViewDual3 *iface, IDispatch **disp)
{
    struct qemu_shellfolderviewdual_get_Script call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GET_SCRIPT);
    call.iface = (ULONG_PTR)view;
    call.disp = (ULONG_PTR)disp;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_get_Script(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_get_Script *c = (struct qemu_shellfolderviewdual_get_Script *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_get_Script(view->host_dual_view, QEMU_G2H(c->disp));
}

#endif

struct qemu_shellfolderviewdual_get_ViewOptions
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t options;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_get_ViewOptions(IShellFolderViewDual3 *iface, LONG *options)
{
    struct qemu_shellfolderviewdual_get_ViewOptions call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GET_VIEWOPTIONS);
    call.iface = (ULONG_PTR)view;
    call.options = (ULONG_PTR)options;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_get_ViewOptions(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_get_ViewOptions *c = (struct qemu_shellfolderviewdual_get_ViewOptions *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_get_ViewOptions(view->host_dual_view, QEMU_G2H(c->options));
}

#endif

struct qemu_shellfolderviewdual_get_CurrentViewMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_get_CurrentViewMode(IShellFolderViewDual3 *iface, UINT *mode)
{
    struct qemu_shellfolderviewdual_get_CurrentViewMode call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GET_CURRENTVIEWMODE);
    call.iface = (ULONG_PTR)view;
    call.mode = (ULONG_PTR)mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_get_CurrentViewMode(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_get_CurrentViewMode *c = (struct qemu_shellfolderviewdual_get_CurrentViewMode *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_get_CurrentViewMode(view->host_dual_view, QEMU_G2H(c->mode));
}

#endif

struct qemu_shellfolderviewdual_put_CurrentViewMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t mode;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_put_CurrentViewMode(IShellFolderViewDual3 *iface, UINT mode)
{
    struct qemu_shellfolderviewdual_put_CurrentViewMode call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_PUT_CURRENTVIEWMODE);
    call.iface = (ULONG_PTR)view;
    call.mode = mode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_put_CurrentViewMode(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_put_CurrentViewMode *c = (struct qemu_shellfolderviewdual_put_CurrentViewMode *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_put_CurrentViewMode(view->host_dual_view, c->mode);
}

#endif

struct qemu_shellfolderviewdual_SelectItemRelative
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t relative;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_SelectItemRelative(IShellFolderViewDual3 *iface, int relative)
{
    struct qemu_shellfolderviewdual_SelectItemRelative call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_SELECTITEMRELATIVE);
    call.iface = (ULONG_PTR)view;
    call.relative = relative;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_SelectItemRelative(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_SelectItemRelative *c = (struct qemu_shellfolderviewdual_SelectItemRelative *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_SelectItemRelative(view->host_dual_view, c->relative);
}

#endif

struct qemu_shellfolderviewdual_get_GroupBy
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t groupby;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_get_GroupBy(IShellFolderViewDual3 *iface, BSTR *groupby)
{
    struct qemu_shellfolderviewdual_get_GroupBy call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GET_GROUPBY);
    call.iface = (ULONG_PTR)view;
    call.groupby = (ULONG_PTR)groupby;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_get_GroupBy(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_get_GroupBy *c = (struct qemu_shellfolderviewdual_get_GroupBy *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_get_GroupBy(view->host_dual_view, QEMU_G2H(c->groupby));
}

#endif

struct qemu_shellfolderviewdual_put_GroupBy
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t groupby;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_put_GroupBy(IShellFolderViewDual3 *iface, BSTR groupby)
{
    struct qemu_shellfolderviewdual_put_GroupBy call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_PUT_GROUPBY);
    call.iface = (ULONG_PTR)view;
    call.groupby = (ULONG_PTR)groupby;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_put_GroupBy(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_put_GroupBy *c = (struct qemu_shellfolderviewdual_put_GroupBy *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_put_GroupBy(view->host_dual_view, QEMU_G2H(c->groupby));
}

#endif

struct qemu_shellfolderviewdual_get_FolderFlags
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_get_FolderFlags(IShellFolderViewDual3 *iface, DWORD *flags)
{
    struct qemu_shellfolderviewdual_get_FolderFlags call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GET_FOLDERFLAGS);
    call.iface = (ULONG_PTR)view;
    call.flags = (ULONG_PTR)flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_get_FolderFlags(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_get_FolderFlags *c = (struct qemu_shellfolderviewdual_get_FolderFlags *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_get_FolderFlags(view->host_dual_view, QEMU_G2H(c->flags));
}

#endif

struct qemu_shellfolderviewdual_put_FolderFlags
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_put_FolderFlags(IShellFolderViewDual3 *iface, DWORD flags)
{
    struct qemu_shellfolderviewdual_put_FolderFlags call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_PUT_FOLDERFLAGS);
    call.iface = (ULONG_PTR)view;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_put_FolderFlags(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_put_FolderFlags *c = (struct qemu_shellfolderviewdual_put_FolderFlags *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_put_FolderFlags(view->host_dual_view, c->flags);
}

#endif

struct qemu_shellfolderviewdual_get_SortColumns
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sortcolumns;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_get_SortColumns(IShellFolderViewDual3 *iface, BSTR *sortcolumns)
{
    struct qemu_shellfolderviewdual_get_SortColumns call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GET_SORTCOLUMNS);
    call.iface = (ULONG_PTR)view;
    call.sortcolumns = (ULONG_PTR)sortcolumns;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_get_SortColumns(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_get_SortColumns *c = (struct qemu_shellfolderviewdual_get_SortColumns *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_get_SortColumns(view->host_dual_view, QEMU_G2H(c->sortcolumns));
}

#endif

struct qemu_shellfolderviewdual_put_SortColumns
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t sortcolumns;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_put_SortColumns(IShellFolderViewDual3 *iface, BSTR sortcolumns)
{
    struct qemu_shellfolderviewdual_put_SortColumns call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_PUT_SORTCOLUMNS);
    call.iface = (ULONG_PTR)view;
    call.sortcolumns = (ULONG_PTR)sortcolumns;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_put_SortColumns(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_put_SortColumns *c = (struct qemu_shellfolderviewdual_put_SortColumns *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_put_SortColumns(view->host_dual_view, QEMU_G2H(c->sortcolumns));
}

#endif

struct qemu_shellfolderviewdual_put_IconSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t icon_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_put_IconSize(IShellFolderViewDual3 *iface, int icon_size)
{
    struct qemu_shellfolderviewdual_put_IconSize call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_PUT_ICONSIZE);
    call.iface = (ULONG_PTR)view;
    call.icon_size = icon_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_put_IconSize(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_put_IconSize *c = (struct qemu_shellfolderviewdual_put_IconSize *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_put_IconSize(view->host_dual_view, c->icon_size);
}

#endif

struct qemu_shellfolderviewdual_get_IconSize
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t icon_size;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_get_IconSize(IShellFolderViewDual3 *iface, int *icon_size)
{
    struct qemu_shellfolderviewdual_get_IconSize call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_GET_ICONSIZE);
    call.iface = (ULONG_PTR)view;
    call.icon_size = (ULONG_PTR)icon_size;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_get_IconSize(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_get_IconSize *c = (struct qemu_shellfolderviewdual_get_IconSize *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_get_IconSize(view->host_dual_view, QEMU_G2H(c->icon_size));
}

#endif

struct qemu_shellfolderviewdual_FilterView
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t filter_text;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI shellfolderviewdual_FilterView(IShellFolderViewDual3 *iface, BSTR filter_text)
{
    struct qemu_shellfolderviewdual_FilterView call;
    struct qemu_shellview *view = impl_from_IShellFolderViewDual3(iface);

    call.super.id = QEMU_SYSCALL_ID(CALL_SHELLFOLDERVIEWDUAL_FILTERVIEW);
    call.iface = (ULONG_PTR)view;
    call.filter_text = (ULONG_PTR)filter_text;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_shellfolderviewdual_FilterView(struct qemu_syscall *call)
{
    struct qemu_shellfolderviewdual_FilterView *c = (struct qemu_shellfolderviewdual_FilterView *)call;
    struct qemu_shellview *view;

    WINE_FIXME("Unverified!\n");
    view = QEMU_G2H(c->iface);

    c->super.iret = IShellFolderViewDual3_FilterView(view->host_dual_view, QEMU_G2H(c->filter_text));
}

#endif

struct qemu_SHCreateShellFolderView
{
    struct qemu_syscall super;
    uint64_t desc;
    uint64_t shellview;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateShellFolderView(const SFV_CREATE *desc, IShellView **shellview)
{
    struct qemu_SHCreateShellFolderView call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESHELLFOLDERVIEW);
    call.desc = (ULONG_PTR)desc;
    call.shellview = (ULONG_PTR)shellview;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateShellFolderView(struct qemu_syscall *call)
{
    struct qemu_SHCreateShellFolderView *c = (struct qemu_SHCreateShellFolderView *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateShellFolderView(QEMU_G2H(c->desc), QEMU_G2H(c->shellview));
}

#endif

struct qemu_SHCreateShellFolderViewEx
{
    struct qemu_syscall super;
    uint64_t desc;
    uint64_t shellview;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI SHCreateShellFolderViewEx(CSFV *desc, IShellView **shellview)
{
    struct qemu_SHCreateShellFolderViewEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SHCREATESHELLFOLDERVIEWEX);
    call.desc = (ULONG_PTR)desc;
    call.shellview = (ULONG_PTR)shellview;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SHCreateShellFolderViewEx(struct qemu_syscall *call)
{
    struct qemu_SHCreateShellFolderViewEx *c = (struct qemu_SHCreateShellFolderViewEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = SHCreateShellFolderViewEx(QEMU_G2H(c->desc), QEMU_G2H(c->shellview));
}

#endif

#ifdef QEMU_DLL_GUEST

static const IShellView3Vtbl shellviewvtbl =
{
    qemu_shellview_QueryInterface,
    qemu_shellview_AddRef,
    qemu_shellview_Release,
    qemu_shellview_GetWindow,
    qemu_shellview_ContextSensitiveHelp,
    qemu_shellview_TranslateAccelerator,
    qemu_shellview_EnableModeless,
    qemu_shellview_UIActivate,
    qemu_shellview_Refresh,
    qemu_shellview_CreateViewWindow,
    qemu_shellview_DestroyViewWindow,
    qemu_shellview_GetCurrentInfo,
    qemu_shellview_AddPropertySheetPages,
    qemu_shellview_SaveViewState,
    qemu_shellview_SelectItem,
    qemu_shellview_GetItemObject,
    qemu_shellview_GetView,
    qemu_shellview_CreateViewWindow2,
    qemu_shellview_HandleRename,
    qemu_shellview_SelectAndPositionItem,
    qemu_shellview_CreateViewWindow3
};

static const IOleCommandTargetVtbl olecommandtargetvtbl =
{
    ISVOleCmdTarget_QueryInterface,
    ISVOleCmdTarget_AddRef,
    ISVOleCmdTarget_Release,
    ISVOleCmdTarget_QueryStatus,
    ISVOleCmdTarget_Exec
};

static const IDropTargetVtbl droptargetvtbl =
{
    ISVDropTarget_QueryInterface,
    ISVDropTarget_AddRef,
    ISVDropTarget_Release,
    ISVDropTarget_DragEnter,
    ISVDropTarget_DragOver,
    ISVDropTarget_DragLeave,
    ISVDropTarget_Drop
};

static const IDropSourceVtbl dropsourcevtbl =
{
    ISVDropSource_QueryInterface,
    ISVDropSource_AddRef,
    ISVDropSource_Release,
    ISVDropSource_QueryContinueDrag,
    ISVDropSource_GiveFeedback
};

static const IViewObjectVtbl viewobjectvtbl =
{
    ISVViewObject_QueryInterface,
    ISVViewObject_AddRef,
    ISVViewObject_Release,
    ISVViewObject_Draw,
    ISVViewObject_GetColorSet,
    ISVViewObject_Freeze,
    ISVViewObject_Unfreeze,
    ISVViewObject_SetAdvise,
    ISVViewObject_GetAdvise
};

static const IFolderView2Vtbl folderviewvtbl =
{
    FolderView_QueryInterface,
    FolderView_AddRef,
    FolderView_Release,
    FolderView_GetCurrentViewMode,
    FolderView_SetCurrentViewMode,
    FolderView_GetFolder,
    FolderView_Item,
    FolderView_ItemCount,
    FolderView_Items,
    FolderView_GetSelectionMarkedItem,
    FolderView_GetFocusedItem,
    FolderView_GetItemPosition,
    FolderView_GetSpacing,
    FolderView_GetDefaultSpacing,
    FolderView_GetAutoArrange,
    FolderView_SelectItem,
    FolderView_SelectAndPositionItems,
    FolderView2_SetGroupBy,
    FolderView2_GetGroupBy,
    FolderView2_SetViewProperty,
    FolderView2_GetViewProperty,
    FolderView2_SetTileViewProperties,
    FolderView2_SetExtendedTileViewProperties,
    FolderView2_SetText,
    FolderView2_SetCurrentFolderFlags,
    FolderView2_GetCurrentFolderFlags,
    FolderView2_GetSortColumnCount,
    FolderView2_SetSortColumns,
    FolderView2_GetSortColumns,
    FolderView2_GetItem,
    FolderView2_GetVisibleItem,
    FolderView2_GetSelectedItem,
    FolderView2_GetSelection,
    FolderView2_GetSelectionState,
    FolderView2_InvokeVerbOnSelection,
    FolderView2_SetViewModeAndIconSize,
    FolderView2_GetViewModeAndIconSize,
    FolderView2_SetGroupSubsetCount,
    FolderView2_GetGroupSubsetCount,
    FolderView2_SetRedraw,
    FolderView2_IsMoveInSameFolder,
    FolderView2_DoRename
};

/* Mingw's header is broken for C, the vtbl does not include the IUnknown functions. */
static const struct
{
    void *qi;
    void *addref;
    void *release;
    IShellFolderViewVtbl shellfolderviewvtbl;
}
shellfolderviewvtbl =
{
    IShellFolderView_fnQueryInterface,
    IShellFolderView_fnAddRef,
    IShellFolderView_fnRelease,
    {
        IShellFolderView_fnRearrange,
        IShellFolderView_fnGetArrangeParam,
        IShellFolderView_fnArrangeGrid,
        IShellFolderView_fnAutoArrange,
        IShellFolderView_fnGetAutoArrange,
        IShellFolderView_fnAddObject,
        IShellFolderView_fnGetObject,
        IShellFolderView_fnRemoveObject,
        IShellFolderView_fnGetObjectCount,
        IShellFolderView_fnSetObjectCount,
        IShellFolderView_fnUpdateObject,
        IShellFolderView_fnRefreshObject,
        IShellFolderView_fnSetRedraw,
        IShellFolderView_fnGetSelectedCount,
        IShellFolderView_fnGetSelectedObjects,
        IShellFolderView_fnIsDropOnSource,
        IShellFolderView_fnGetDragPoint,
        IShellFolderView_fnGetDropPoint,
        IShellFolderView_fnMoveIcons,
        IShellFolderView_fnSetItemPos,
        IShellFolderView_fnIsBkDropTarget,
        IShellFolderView_fnSetClipboard,
        IShellFolderView_fnSetPoints,
        IShellFolderView_fnGetItemSpacing,
        IShellFolderView_fnSetCallback,
        IShellFolderView_fnSelect,
        IShellFolderView_fnQuerySupport,
        IShellFolderView_fnSetAutomationObject
    }
};

static const IShellFolderViewDual3Vtbl shellfolderviewdualvtbl =
{
    shellfolderviewdual_QueryInterface,
    shellfolderviewdual_AddRef,
    shellfolderviewdual_Release,
    shellfolderviewdual_GetTypeInfoCount,
    shellfolderviewdual_GetTypeInfo,
    shellfolderviewdual_GetIDsOfNames,
    shellfolderviewdual_Invoke,
    shellfolderviewdual_get_Application,
    shellfolderviewdual_get_Parent,
    shellfolderviewdual_get_Folder,
    shellfolderviewdual_SelectedItems,
    shellfolderviewdual_get_FocusedItem,
    shellfolderviewdual_SelectItem,
    shellfolderviewdual_PopupItemMenu,
    shellfolderviewdual_get_Script,
    shellfolderviewdual_get_ViewOptions,
    shellfolderviewdual_get_CurrentViewMode,
    shellfolderviewdual_put_CurrentViewMode,
    shellfolderviewdual_SelectItemRelative,
    shellfolderviewdual_get_GroupBy,
    shellfolderviewdual_put_GroupBy,
    shellfolderviewdual_get_FolderFlags,
    shellfolderviewdual_put_FolderFlags,
    shellfolderviewdual_get_SortColumns,
    shellfolderviewdual_put_SortColumns,
    shellfolderviewdual_put_IconSize,
    shellfolderviewdual_get_IconSize,
    shellfolderviewdual_FilterView
};

void qemu_shellview_guest_init(struct qemu_shellview *view)
{
    view->IShellView3_iface.lpVtbl = &shellviewvtbl;
    view->IOleCommandTarget_iface.lpVtbl = &olecommandtargetvtbl;
    view->IDropTarget_iface.lpVtbl = &droptargetvtbl;
    view->IDropSource_iface.lpVtbl = &dropsourcevtbl;
    view->IViewObject_iface.lpVtbl = &viewobjectvtbl;
    view->IFolderView2_iface.lpVtbl = &folderviewvtbl;
    view->IShellFolderView_iface.lpVtbl = (const void *)&shellfolderviewvtbl;
    view->IShellFolderViewDual3_iface.lpVtbl = &shellfolderviewdualvtbl;
}

#else

struct qemu_shellview *qemu_shellview_host_create(IShellView3 *host)
{
    struct qemu_shellview *view;

    view = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*view));
    if (!view)
    {
        WINE_FIXME("Out of memory.\n");
        return NULL;
    }

    view->host_shellview = host;
    IShellView3_AddRef(host);

    /* The wrapper does not have its own referecen count and relies on the host refcount. */
    IShellView3_QueryInterface(host, &IID_IOleCommandTarget, (void **)&view->host_cmd_target);
    if (!view->host_cmd_target)
        WINE_ERR("Cannot get IOleCommandTarget.\n");
    IOleCommandTarget_Release(view->host_cmd_target);

    IShellView3_QueryInterface(host, &IID_IDropTarget, (void **)&view->host_drop_target);
    if (!view->host_drop_target)
        WINE_ERR("Cannot get IDropTarget.\n");
    IDropTarget_Release(view->host_drop_target);

    IShellView3_QueryInterface(host, &IID_IDropSource, (void **)&view->host_drop_source);
    IDropSource_Release(view->host_drop_source);
    if (!view->host_drop_source)
        WINE_ERR("Cannot get IDropSource.\n");

    IShellView3_QueryInterface(host, &IID_IViewObject, (void **)&view->host_view_object);
    if (!view->host_view_object)
        WINE_ERR("Cannot get IViewObject.\n");
    IViewObject_Release(view->host_view_object);

    IShellView3_QueryInterface(host, &IID_IFolderView2, (void **)&view->host_folder_view);
    if (!view->host_folder_view)
        WINE_ERR("Cannot get IFolderView2.\n");
    IFolderView2_Release(view->host_folder_view);

    IShellView3_QueryInterface(host, &IID_myIShellFolderView, (void **)&view->host_shell_folder_view);
    if (!view->host_shell_folder_view)
        WINE_ERR("Cannot get IShellFolderView.\n");
    IShellFolderView_Release(view->host_shell_folder_view);

    IShellView3_GetItemObject(host, SVGIO_BACKGROUND, &IID_IDispatch, (void **)&view->host_dual_view);
    if (!view->host_dual_view)
        WINE_ERR("Cannot get IShellFolderViewDual3.\n");
    IShellFolderViewDual3_Release(view->host_dual_view);

    WINE_TRACE("Created shell view wrapper %p.\n", view);

    return view;
}

#endif
