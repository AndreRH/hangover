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

struct shellbrowser_wrapper
{
    IShellBrowser IShellBrowser_iface;
    ICommDlgBrowser ICommDlgBrowser_iface;
    uint64_t guest_iface, guest_commdlg_iface;
    LONG ref;
    struct qemu_shellview *shellview;
};

struct shellbrowser_wrapper_QI
{
    uint64_t iface;
    uint64_t comdlg_browser;
};

struct shellbrowser_wrapper_Refcnt
{
    uint64_t iface;
};

struct shellbrowser_wrapper_GetWindow
{
    uint64_t iface;
    uint64_t hwnd;
};

struct shellbrowser_wrapper_SetMenuSB
{
    uint64_t iface;
    uint64_t hmenuShared, holemenuReserved, hwndActiveObject;
};

struct shellbrowser_wrapper_SendControlMsg
{
    uint64_t iface;
    uint64_t id, msg, wparam, lparam, result;
};

struct shellbrowser_wrapper_IncludeObject
{
    uint64_t iface;
    uint64_t view, list;
};

struct shellbrowser_wrapper_OnViewWindowActive
{
    uint64_t iface;
    uint64_t view;
};

struct shellbrowser_wrapper_RemoveMenusSB
{
    uint64_t iface;
    uint64_t menu;
};

struct shellbrowser_wrapper_InsertMenusSB
{
    uint64_t iface;
    uint64_t menu;
    uint64_t widths;
};

struct shellbrowser_wrapper_OnStateChange
{
    uint64_t iface;
    uint64_t view, change;
};

#ifdef QEMU_DLL_GUEST

static HRESULT __fastcall shellbrowser_wrapper_QI(struct shellbrowser_wrapper_QI *call)
{
    IShellBrowser *browser = (IShellBrowser *)(ULONG_PTR)call->iface;
    IUnknown *obj;
    HRESULT hr;

    hr = IShellBrowser_QueryInterface(browser, &IID_ICommDlgBrowser, (void **)&obj);
    IUnknown_Release(obj); /* Ok, we should call this interface's release later, not here. */
    call->comdlg_browser = (ULONG_PTR)obj;
    return hr;
}

static ULONG __fastcall shellbrowser_wrapper_AddRef(struct shellbrowser_wrapper_Refcnt *call)
{
    IShellBrowser *browser = (IShellBrowser *)(ULONG_PTR)call->iface;
    return IShellBrowser_AddRef(browser);
}

static ULONG __fastcall shellbrowser_wrapper_Release(struct shellbrowser_wrapper_Refcnt *call)
{
    IShellBrowser *browser = (IShellBrowser *)(ULONG_PTR)call->iface;
    return IShellBrowser_Release(browser);
}

static HRESULT __fastcall shellbrowser_wrapper_GetWindow(struct shellbrowser_wrapper_GetWindow *call)
{
    IShellBrowser *browser = (IShellBrowser *)(ULONG_PTR)call->iface;
    HWND win;
    HRESULT hr;

    hr = IShellBrowser_GetWindow(browser, &win);
    call->hwnd = (ULONG_PTR)win;
    return hr;
}

static HRESULT __fastcall shellbrowser_wrapper_SetMenuSB(struct shellbrowser_wrapper_SetMenuSB *call)
{
    IShellBrowser *browser = (IShellBrowser *)(ULONG_PTR)call->iface;

    return IShellBrowser_SetMenuSB(browser, (HMENU)(ULONG_PTR)call->hmenuShared,
            (HWND)(ULONG_PTR)call->holemenuReserved, (HWND)(ULONG_PTR)call->hwndActiveObject);
}

static HRESULT __fastcall shellbrowser_wrapper_SendControlMsg(struct shellbrowser_wrapper_SendControlMsg *call)
{
    IShellBrowser *browser = (IShellBrowser *)(ULONG_PTR)call->iface;
    LRESULT result;
    HRESULT hr;

    hr = IShellBrowser_SendControlMsg(browser, call->id, call->msg, call->wparam, call->lparam, &result);
    call->result = result;
    return hr;
}

static HRESULT __fastcall shellbrowser_wrapper_IncludeObject(struct shellbrowser_wrapper_IncludeObject *call)
{
    ICommDlgBrowser *browser = (ICommDlgBrowser *)(ULONG_PTR)call->iface;
    struct qemu_shellview *view = (struct qemu_shellview *)(ULONG_PTR)call->view;

    return ICommDlgBrowser_IncludeObject(browser, (IShellView *)&view->IShellView3_iface,
            (void *)(ULONG_PTR)call->list);
}

static HRESULT __fastcall shellbrowser_wrapper_OnViewWindowActive(struct shellbrowser_wrapper_OnViewWindowActive *call)
{
    IShellBrowser *browser = (IShellBrowser *)(ULONG_PTR)call->iface;
    struct qemu_shellview *view = (struct qemu_shellview *)(ULONG_PTR)call->view;

    return IShellBrowser_OnViewWindowActive(browser, (IShellView *)&view->IShellView3_iface);
}

static HRESULT __fastcall shellbrowser_wrapper_RemoveMenusSB(struct shellbrowser_wrapper_RemoveMenusSB *call)
{
    IShellBrowser *browser = (IShellBrowser *)(ULONG_PTR)call->iface;
    return IShellBrowser_RemoveMenusSB(browser, (HMENU)(ULONG_PTR)call->menu);
}

static HRESULT __fastcall shellbrowser_wrapper_InsertMenusSB(struct shellbrowser_wrapper_InsertMenusSB *call)
{
    IShellBrowser *browser = (IShellBrowser *)(ULONG_PTR)call->iface;
    return IShellBrowser_InsertMenusSB(browser, (HMENU)(ULONG_PTR)call->menu, (void *)(ULONG_PTR)call->widths);
}

static HRESULT __fastcall shellbrowser_wrapper_OnStateChange(struct shellbrowser_wrapper_OnStateChange *call)
{
    ICommDlgBrowser *browser = (ICommDlgBrowser *)(ULONG_PTR)call->iface;
    struct qemu_shellview *view = (struct qemu_shellview *)(ULONG_PTR)call->view;

    return ICommDlgBrowser_OnStateChange(browser, (IShellView *)&view->IShellView3_iface,
            call->change);
}

void shellbrowser_wrapper_get_funcs(struct shellbrowser_funcs *funcs)
{
    funcs->AddRef = (ULONG_PTR)shellbrowser_wrapper_AddRef;
    funcs->Release = (ULONG_PTR)shellbrowser_wrapper_Release;
    funcs->GetWindow = (ULONG_PTR)shellbrowser_wrapper_GetWindow;
    funcs->SetMenuSB = (ULONG_PTR)shellbrowser_wrapper_SetMenuSB;
    funcs->SendControlMsg = (ULONG_PTR)shellbrowser_wrapper_SendControlMsg;
    funcs->QI = (ULONG_PTR)shellbrowser_wrapper_QI;
    funcs->IncludeObject = (ULONG_PTR)shellbrowser_wrapper_IncludeObject;
    funcs->OnViewWindowActive = (ULONG_PTR)shellbrowser_wrapper_OnViewWindowActive;
    funcs->OnStateChange = (ULONG_PTR)shellbrowser_wrapper_OnStateChange;
    funcs->RemoveMenusSB = (ULONG_PTR)shellbrowser_wrapper_RemoveMenusSB;
    funcs->InsertMenusSB = (ULONG_PTR)shellbrowser_wrapper_InsertMenusSB;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);

static uint64_t shellbrowser_AddRef;
static uint64_t shellbrowser_Release;
static uint64_t shellbrowser_GetWindow;
static uint64_t shellbrowser_SetMenuSB;
static uint64_t shellbrowser_SendControlMsg;
static uint64_t shellbrowser_QI;
static uint64_t shellbrowser_IncludeObject;
static uint64_t shellbrowser_OnViewWindowActive;
static uint64_t shellbrowser_OnStateChange;
static uint64_t shellbrowser_RemoveMenusSB;
static uint64_t shellbrowser_InsertMenusSB;

void shellbrowser_wrapper_wrapper_set_funcs(const struct shellbrowser_funcs *funcs)
{
    if (funcs)
    {
        shellbrowser_AddRef = funcs->AddRef;
        shellbrowser_Release = funcs->Release;
        shellbrowser_GetWindow = funcs->GetWindow;
        shellbrowser_SetMenuSB = funcs->SetMenuSB;
        shellbrowser_SendControlMsg = funcs->SendControlMsg;
        shellbrowser_QI = funcs->QI;
        shellbrowser_IncludeObject = funcs->IncludeObject;
        shellbrowser_OnViewWindowActive = funcs->OnViewWindowActive;
        shellbrowser_OnStateChange = funcs->OnStateChange;
        shellbrowser_RemoveMenusSB = funcs->RemoveMenusSB;
        shellbrowser_InsertMenusSB = funcs->InsertMenusSB;
    }
    else
    {
        shellbrowser_AddRef = 0;
        shellbrowser_Release = 0;
        shellbrowser_GetWindow = 0;
        shellbrowser_SetMenuSB = 0;
        shellbrowser_SendControlMsg = 0;
        shellbrowser_QI = 0;
        shellbrowser_IncludeObject = 0;
        shellbrowser_OnViewWindowActive = 0;
        shellbrowser_OnStateChange = 0;
        shellbrowser_RemoveMenusSB = 0;
        shellbrowser_InsertMenusSB = 0;
    }
}

struct shellbrowser_wrapper *shellbrowser_wrapper_from_IShellBrowser(IShellBrowser *iface)
{
    return CONTAINING_RECORD(iface, struct shellbrowser_wrapper, IShellBrowser_iface);
}

static HRESULT WINAPI IShellBrowserImpl_QueryInterface(IShellBrowser *iface, REFIID riid, void **ppvObj)
{
    struct shellbrowser_wrapper *browser = shellbrowser_wrapper_from_IShellBrowser(iface);

    WINE_TRACE("(%p)->(%s, %p)\n", browser, wine_dbgstr_guid(riid), ppvObj);

    *ppvObj = NULL;

    if(IsEqualIID(riid, &IID_IUnknown))
        *ppvObj = &browser->IShellBrowser_iface;
    else if(IsEqualIID(riid, &IID_IOleWindow))
        *ppvObj = &browser->IShellBrowser_iface;
    else if(IsEqualIID(riid, &IID_IShellBrowser))
        *ppvObj = &browser->IShellBrowser_iface;
    else if(IsEqualIID(riid, &IID_ICommDlgBrowser))
        *ppvObj = &browser->ICommDlgBrowser_iface;
    else if(IsEqualIID(riid, &IID_IServiceProvider))
    {
        WINE_FIXME("IServiceProvider not there yet\n");
        *ppvObj = NULL;
    }

    if(*ppvObj) {
        IUnknown_AddRef((IUnknown*)*ppvObj);
        return S_OK;
    }

    WINE_FIXME("unsupported interface, %s\n", wine_dbgstr_guid(riid));
    return E_NOINTERFACE;
}

static ULONG WINAPI IShellBrowserImpl_AddRef(IShellBrowser * iface)
{
    struct shellbrowser_wrapper *browser = shellbrowser_wrapper_from_IShellBrowser(iface);
    ULONG ref = InterlockedIncrement(&browser->ref);

    WINE_TRACE("(%p,%u)\n", browser, ref - 1);

    return ref;
}

static ULONG WINAPI IShellBrowserImpl_Release(IShellBrowser * iface)
{
    struct shellbrowser_wrapper *browser = shellbrowser_wrapper_from_IShellBrowser(iface);
    ULONG ref = InterlockedDecrement(&browser->ref), ref2;

    WINE_TRACE("(%p,%u)\n", browser, ref + 1);

    if (!ref)
    {
        struct shellbrowser_wrapper_Refcnt call;
        call.iface = browser->guest_iface;

        WINE_TRACE("Calling guest callback %p.\n", (void *)shellbrowser_Release);
        ref2 = qemu_ops->qemu_execute(QEMU_G2H(shellbrowser_Release), QEMU_H2G(&call));
        WINE_TRACE("Guest CB returned 0x%x.\n", ref2);

        HeapFree(GetProcessHeap(), 0, browser);
    }

    return ref;
}

static HRESULT WINAPI IShellBrowserImpl_GetWindow(IShellBrowser * iface, HWND *phwnd)
{
    struct shellbrowser_wrapper *browser = shellbrowser_wrapper_from_IShellBrowser(iface);
    struct shellbrowser_wrapper_GetWindow call;
    HRESULT hr;

    call.iface = browser->guest_iface;

    WINE_TRACE("Calling guest callback %p.\n", (void *)shellbrowser_GetWindow);
    hr = qemu_ops->qemu_execute(QEMU_G2H(shellbrowser_GetWindow), QEMU_H2G(&call));
    *phwnd = QEMU_G2H(call.hwnd);
    WINE_TRACE("Guest CB returned 0x%x, window %p.\n", hr, *phwnd);

    return hr;
}

static HRESULT WINAPI IShellBrowserImpl_ContextSensitiveHelp(IShellBrowser * iface, BOOL fEnterMode)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_BrowseObject(IShellBrowser *iface, LPCITEMIDLIST pidl, UINT wFlags)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_EnableModelessSB(IShellBrowser *iface, BOOL fEnable)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_GetControlWindow(IShellBrowser *iface, UINT id, HWND *lphwnd)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_GetViewStateStream(IShellBrowser *iface, DWORD grfMode, LPSTREAM *ppStrm)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_InsertMenusSB(IShellBrowser *iface, HMENU hmenuShared,
        LPOLEMENUGROUPWIDTHS lpMenuWidths)
{
    struct shellbrowser_wrapper *browser = shellbrowser_wrapper_from_IShellBrowser(iface);
    struct shellbrowser_wrapper_InsertMenusSB call;
    HRESULT hr;

    call.iface = browser->guest_iface;
    call.menu = QEMU_H2G(hmenuShared);
    call.widths = QEMU_H2G(lpMenuWidths);

    WINE_TRACE("Calling guest callback %p.\n", (void *)shellbrowser_InsertMenusSB);
    hr = qemu_ops->qemu_execute(QEMU_G2H(shellbrowser_InsertMenusSB), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", hr);

    return hr;
}

static HRESULT WINAPI IShellBrowserImpl_OnViewWindowActive(IShellBrowser *iface, IShellView *ppshv)
{
    struct shellbrowser_wrapper *browser = shellbrowser_wrapper_from_IShellBrowser(iface);
    struct shellbrowser_wrapper_OnViewWindowActive call;
    HRESULT hr;

    if (browser->shellview->host_shellview != (IShellView3 *)ppshv)
        WINE_FIXME("Unexpected shellview interface %p, expect %p.\n", ppshv, &browser->shellview->host_shellview);

    call.iface = browser->guest_commdlg_iface;
    call.view = QEMU_H2G(browser->shellview);

    WINE_TRACE("Calling guest callback %p.\n", (void *)shellbrowser_OnViewWindowActive);
    hr = qemu_ops->qemu_execute(QEMU_G2H(shellbrowser_OnViewWindowActive), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", hr);

    return hr;
}

static HRESULT WINAPI IShellBrowserImpl_QueryActiveShellView(IShellBrowser *iface, IShellView **ppshv)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_RemoveMenusSB(IShellBrowser *iface, HMENU hmenuShared)
{
    struct shellbrowser_wrapper *browser = shellbrowser_wrapper_from_IShellBrowser(iface);
    struct shellbrowser_wrapper_RemoveMenusSB call;
    HRESULT hr;

    call.iface = browser->guest_iface;
    call.menu = QEMU_H2G(hmenuShared);

    WINE_TRACE("Calling guest callback %p.\n", (void *)shellbrowser_RemoveMenusSB);
    hr = qemu_ops->qemu_execute(QEMU_G2H(shellbrowser_RemoveMenusSB), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", hr);

    return hr;
}

static HRESULT WINAPI IShellBrowserImpl_SendControlMsg(IShellBrowser *iface, UINT id, UINT uMsg,
        WPARAM wParam, LPARAM lParam, LRESULT *pret)
{
    struct shellbrowser_wrapper *browser = shellbrowser_wrapper_from_IShellBrowser(iface);
    struct shellbrowser_wrapper_SendControlMsg call;
    HRESULT hr;

    call.iface = browser->guest_iface;
    call.id = id;
    call.msg = uMsg;
    call.wparam = wParam;
    call.lparam = lParam;

    WINE_TRACE("Calling guest callback %p.\n", (void *)shellbrowser_SendControlMsg);
    hr = qemu_ops->qemu_execute(QEMU_G2H(shellbrowser_SendControlMsg), QEMU_H2G(&call));
    *pret = call.result;
    WINE_TRACE("Guest CB returned 0x%x, pret=%lx.\n", hr, *pret);

    return hr;
}

static HRESULT WINAPI IShellBrowserImpl_SetMenuSB(IShellBrowser *iface,
        HMENU hmenuShared, HOLEMENU holemenuReserved, HWND hwndActiveObject)
{
    struct shellbrowser_wrapper *browser = shellbrowser_wrapper_from_IShellBrowser(iface);
    struct shellbrowser_wrapper_SetMenuSB call;
    HRESULT hr;

    call.iface = browser->guest_iface;
    call.hmenuShared = QEMU_H2G(hmenuShared);
    call.holemenuReserved = QEMU_H2G(holemenuReserved);
    call.hwndActiveObject = QEMU_H2G(hwndActiveObject);

    WINE_TRACE("Calling guest callback %p.\n", (void *)shellbrowser_SetMenuSB);
    hr = qemu_ops->qemu_execute(QEMU_G2H(shellbrowser_SetMenuSB), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", hr);

    return hr;
}

static HRESULT WINAPI IShellBrowserImpl_SetStatusTextSB(IShellBrowser *iface,
        LPCOLESTR lpszStatusText)

{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_SetToolbarItems(IShellBrowser *iface,
        LPTBBUTTON lpButtons, UINT nButtons, UINT uFlags)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_TranslateAcceleratorSB(IShellBrowser *iface,
        LPMSG lpmsg, WORD wID)

{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static const IShellBrowserVtbl IShellBrowserImpl_Vtbl =
{
    IShellBrowserImpl_QueryInterface,
    IShellBrowserImpl_AddRef,
    IShellBrowserImpl_Release,
    IShellBrowserImpl_GetWindow,
    IShellBrowserImpl_ContextSensitiveHelp,
    IShellBrowserImpl_InsertMenusSB,
    IShellBrowserImpl_SetMenuSB,
    IShellBrowserImpl_RemoveMenusSB,
    IShellBrowserImpl_SetStatusTextSB,
    IShellBrowserImpl_EnableModelessSB,
    IShellBrowserImpl_TranslateAcceleratorSB,
    IShellBrowserImpl_BrowseObject,
    IShellBrowserImpl_GetViewStateStream,
    IShellBrowserImpl_GetControlWindow,
    IShellBrowserImpl_SendControlMsg,
    IShellBrowserImpl_QueryActiveShellView,
    IShellBrowserImpl_OnViewWindowActive,
    IShellBrowserImpl_SetToolbarItems
};

static inline struct shellbrowser_wrapper *impl_from_ICommDlgBrowser( ICommDlgBrowser *iface )
{
    return CONTAINING_RECORD(iface, struct shellbrowser_wrapper, ICommDlgBrowser_iface);
}

static HRESULT WINAPI IShellBrowserImpl_ICommDlgBrowser_QueryInterface(
        ICommDlgBrowser *iface, REFIID riid, LPVOID *ppvObj)
{
    struct shellbrowser_wrapper *browser = impl_from_ICommDlgBrowser(iface);

    WINE_TRACE("(%p)\n", browser);

    return IShellBrowserImpl_QueryInterface(&browser->IShellBrowser_iface,riid,ppvObj);
}

static ULONG WINAPI IShellBrowserImpl_ICommDlgBrowser_AddRef(ICommDlgBrowser * iface)
{
    struct shellbrowser_wrapper *browser = impl_from_ICommDlgBrowser(iface);

    WINE_TRACE("(%p)\n", browser);

    return IShellBrowserImpl_AddRef(&browser->IShellBrowser_iface);
}

static ULONG WINAPI IShellBrowserImpl_ICommDlgBrowser_Release(ICommDlgBrowser * iface)
{
    struct shellbrowser_wrapper *browser = impl_from_ICommDlgBrowser(iface);

    WINE_TRACE("(%p)\n", browser);

    return IShellBrowserImpl_Release(&browser->IShellBrowser_iface);
}

static HRESULT WINAPI IShellBrowserImpl_ICommDlgBrowser_OnDefaultCommand(ICommDlgBrowser *iface,
        IShellView *ppshv)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_ICommDlgBrowser_OnStateChange(ICommDlgBrowser *iface,
        IShellView *ppshv, ULONG uChange)
{
    struct shellbrowser_wrapper *browser = impl_from_ICommDlgBrowser(iface);
    struct shellbrowser_wrapper_OnStateChange call;
    HRESULT hr;

    if (browser->shellview->host_shellview != (IShellView3 *)ppshv)
        WINE_FIXME("Unexpected shellview interface %p, expect %p.\n", ppshv, &browser->shellview->host_shellview);

    call.iface = browser->guest_commdlg_iface;
    call.view = QEMU_H2G(browser->shellview);
    call.change = uChange;

    WINE_TRACE("Calling guest callback %p.\n", (void *)shellbrowser_OnStateChange);
    hr = qemu_ops->qemu_execute(QEMU_G2H(shellbrowser_OnStateChange), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", hr);

    return hr;
}

static LRESULT send_includeitem_notification(HWND hwndParentDlg, LPCITEMIDLIST pidl)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_ICommDlgBrowser_IncludeObject(ICommDlgBrowser *iface,
        IShellView *ppshv, LPCITEMIDLIST pidl)
{
    struct shellbrowser_wrapper *browser = impl_from_ICommDlgBrowser(iface);
    struct shellbrowser_wrapper_IncludeObject call;
    HRESULT hr;

    if (browser->shellview->host_shellview != (IShellView3 *)ppshv)
        WINE_FIXME("Unexpected shellview interface %p, expect %p.\n", ppshv, &browser->shellview->host_shellview);

    call.iface = browser->guest_commdlg_iface;
    call.view = QEMU_H2G(browser->shellview);
    call.list = QEMU_H2G(pidl);

    WINE_TRACE("Calling guest callback %p.\n", (void *)shellbrowser_IncludeObject);
    hr = qemu_ops->qemu_execute(QEMU_G2H(shellbrowser_IncludeObject), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", hr);

    return hr;
}

static const ICommDlgBrowserVtbl IShellBrowserImpl_ICommDlgBrowser_Vtbl =
{
    IShellBrowserImpl_ICommDlgBrowser_QueryInterface,
    IShellBrowserImpl_ICommDlgBrowser_AddRef,
    IShellBrowserImpl_ICommDlgBrowser_Release,
    IShellBrowserImpl_ICommDlgBrowser_OnDefaultCommand,
    IShellBrowserImpl_ICommDlgBrowser_OnStateChange,
    IShellBrowserImpl_ICommDlgBrowser_IncludeObject
};

struct shellbrowser_wrapper *shellbrowser_wrapper_create(uint64_t guest_iface, struct qemu_shellview *shellview)
{
    struct shellbrowser_wrapper_Refcnt call;
    struct shellbrowser_wrapper_QI call_qi;
    struct shellbrowser_wrapper *browser = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*browser));
    ULONG ref;
    HRESULT hr;

    if (!browser)
        WINE_ERR("Out of memory\n");

    browser->IShellBrowser_iface.lpVtbl = &IShellBrowserImpl_Vtbl;
    browser->ICommDlgBrowser_iface.lpVtbl = &IShellBrowserImpl_ICommDlgBrowser_Vtbl;
    browser->guest_iface = guest_iface;
    browser->ref = 1;
    browser->shellview = shellview;

    call.iface = guest_iface;

    WINE_TRACE("Calling guest callback %p.\n", (void *)shellbrowser_AddRef);
    ref = qemu_ops->qemu_execute(QEMU_G2H(shellbrowser_AddRef), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", ref);

    call_qi.iface = guest_iface;
    WINE_TRACE("Calling guest callback %p.\n", (void *)shellbrowser_QI);
    hr = qemu_ops->qemu_execute(QEMU_G2H(shellbrowser_QI), QEMU_H2G(&call_qi));
    browser->guest_commdlg_iface = call_qi.comdlg_browser;
    WINE_TRACE("Guest CB returned 0x%x, comdlg interface at %p.\n", hr, (void *)call_qi.comdlg_browser);

    return browser;
}

IShellBrowser *shellbrowser_wrapper_host_iface(struct shellbrowser_wrapper *wrapper)
{
    return wrapper ? &wrapper->IShellBrowser_iface : NULL;
}

#endif
