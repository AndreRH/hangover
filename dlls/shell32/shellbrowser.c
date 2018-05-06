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
    uint64_t guest_iface;
    LONG ref;
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

#ifdef QEMU_DLL_GUEST

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

void shellbrowser_wrapper_get_funcs(struct shellbrowser_funcs *funcs)
{
    funcs->AddRef = (ULONG_PTR)shellbrowser_wrapper_AddRef;
    funcs->Release = (ULONG_PTR)shellbrowser_wrapper_Release;
    funcs->GetWindow = (ULONG_PTR)shellbrowser_wrapper_GetWindow;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_shell32);

static uint64_t shellbrowser_AddRef;
static uint64_t shellbrowser_Release;
static uint64_t shellbrowser_GetWindow;

void shellbrowser_wrapper_wrapper_set_funcs(const struct shellbrowser_funcs *funcs)
{
    if (funcs)
    {
        shellbrowser_AddRef = funcs->AddRef;
        shellbrowser_Release = funcs->Release;
        shellbrowser_GetWindow = funcs->GetWindow;
    }
    else
    {
        shellbrowser_AddRef = 0;
        shellbrowser_Release = 0;
        shellbrowser_GetWindow = 0;
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
    {
        /* Do I even need this? */
        WINE_FIXME("ICommDlgBrowser not there yet\n");
        *ppvObj = NULL;
    }
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
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_OnViewWindowActive(IShellBrowser *iface, IShellView *ppshv)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_QueryActiveShellView(IShellBrowser *iface, IShellView **ppshv)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_RemoveMenusSB(IShellBrowser *iface, HMENU hmenuShared)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_SendControlMsg(IShellBrowser *iface, UINT id, UINT uMsg,
        WPARAM wParam, LPARAM lParam, LRESULT *pret)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI IShellBrowserImpl_SetMenuSB(IShellBrowser *iface,
        HMENU hmenuShared, HOLEMENU holemenuReserved, HWND hwndActiveObject)
{
    WINE_FIXME("Not implemented\n");
    return E_NOTIMPL;
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

struct shellbrowser_wrapper *shellbrowser_wrapper_create(uint64_t guest_iface)
{
    struct shellbrowser_wrapper_Refcnt call;
    struct shellbrowser_wrapper *browser = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*browser));
    ULONG ref;

    if (!browser)
        WINE_ERR("Out of memory\n");

    browser->IShellBrowser_iface.lpVtbl = &IShellBrowserImpl_Vtbl;
    browser->guest_iface = guest_iface;
    browser->ref = 1;

    call.iface = guest_iface;

    WINE_TRACE("Calling guest callback %p.\n", (void *)shellbrowser_AddRef);
    ref = qemu_ops->qemu_execute(QEMU_G2H(shellbrowser_AddRef), QEMU_H2G(&call));
    WINE_TRACE("Guest CB returned 0x%x.\n", ref);

    return browser;
}

IShellBrowser *shellbrowser_wrapper_host_iface(struct shellbrowser_wrapper *wrapper)
{
    return wrapper ? &wrapper->IShellBrowser_iface : NULL;
}

#endif
