/*
 * Copyright 2017 Stefan Dösinger for CodeWeavers
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
#include <richedit.h>

#ifdef QEMU_DLL_GUEST

#include <initguid.h>
DEFINE_GUID(IID_ITextServices, 0x8d33f740, 0xcf58, 0x11ce, 0xa8, 0x9d, 0x00, 0xaa, 0x00, 0x6c, 0xad, 0xc5);
DEFINE_GUID(IID_ITextHost, 0x13e670f4,0x1a5a,0x11cf,0xab,0xeb,0x00,0xaa,0x00,0xb6,0x5e,0xa1);
DEFINE_GUID(IID_ITextHost2, 0x13e670f5,0x1a5a,0x11cf,0xab,0xeb,0x00,0xaa,0x00,0xb6,0x5e,0xa1);

#endif

/* Separate because of <initguid.h>. */
#include <richole.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_richedit.h"
#include "user32_wrapper.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_riched20.h"

struct callback_impl
{
    /* Guest side */
    IRichEditOleCallback *guest;

    /* Host side */
    IRichEditOleCallback IRichEditOleCallback_iface;
    LONG refcount;
};

struct qemu_set_callbacks
{
    struct qemu_syscall super;
    uint64_t QueryInterface;
    uint64_t AddRef;
    uint64_t Release;
    uint64_t GetClipboardData;
    uint64_t editstream_cb;
    uint64_t breakproc;
};

struct qemu_editstream_cb
{
    uint64_t cb_func;
    uint64_t cookie;
    uint64_t buffer;
    uint64_t cb;
    uint64_t pcb;
};

struct qemu_breakproc_cb
{
    uint64_t cb;
    uint64_t text;
    uint64_t pos;
    uint64_t bytes;
    uint64_t code;
};

struct qemu_GetClipboardData_cb
{
    uint64_t impl;
    uint64_t chrg;
    uint64_t reco;
    uint64_t object;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall guest_ole_callback_AddRef(struct callback_impl *impl)
{
    return impl->guest->lpVtbl->AddRef(impl->guest);
}

static uint64_t __fastcall guest_ole_callback_Release(struct callback_impl *impl)
{
    return impl->guest->lpVtbl->Release(impl->guest);
}

static uint64_t __fastcall guest_GetClipboardData(struct qemu_GetClipboardData_cb *call)
{
    struct callback_impl *impl = (struct callback_impl *)(ULONG_PTR)call->impl;
    IDataObject *object = NULL;
    uint64_t ret;

    ret = impl->guest->lpVtbl->GetClipboardData(impl->guest, (CHARRANGE *)(ULONG_PTR)call->chrg,
            call->reco, &object);
    call->object = (ULONG_PTR)object;

    return ret;
}

static uint64_t __fastcall guest_editstream_cb(struct qemu_editstream_cb *data)
{
    EDITSTREAMCALLBACK cb = (EDITSTREAMCALLBACK)(ULONG_PTR)data->cb_func;
    return cb(data->cookie, (BYTE *)(ULONG_PTR)data->buffer, data->cb, (LONG *)(ULONG_PTR)data->pcb);
}

static uint64_t __fastcall guest_breakproc_cb(struct qemu_breakproc_cb *data)
{
    EDITWORDBREAKPROCW cb = (EDITWORDBREAKPROCW)(ULONG_PTR)data->cb;
    return cb((WCHAR *)(ULONG_PTR)data->text, data->pos, data->bytes, data->code);
}

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_set_callbacks call;

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            call.super.id = QEMU_SYSCALL_ID(CALL_SET_CALLBACKS);
            call.QueryInterface = 0;
            call.AddRef = (ULONG_PTR)guest_ole_callback_AddRef;
            call.Release = (ULONG_PTR)guest_ole_callback_Release;
            call.GetClipboardData = (ULONG_PTR)guest_GetClipboardData;
            call.editstream_cb = (ULONG_PTR)guest_editstream_cb;
            call.breakproc = (ULONG_PTR)guest_breakproc_cb;
            qemu_syscall(&call.super);
            break;
    }
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_riched20);

const struct qemu_ops *qemu_ops;

static uint64_t guest_ole_callback_QueryInterface;
static uint64_t guest_ole_callback_AddRef;
static uint64_t guest_ole_callback_Release;
static uint64_t guest_ole_callback_GetClipboardData;
static uint64_t guest_editstream_cb;
static uint64_t guest_breakproc_wrapper;

#if GUEST_BIT != HOST_BIT

static void riched20_notify(MSG *guest, MSG *host, BOOL ret)
{
    NMHDR *hdr = (NMHDR *)host->lParam;
    struct qemu_MSGFILTER *filter;
    struct qemu_SELCHANGE *selchange;

    WINE_TRACE("Handling a riched20 notify message\n");
    if (ret)
    {
        switch (hdr->code)
        {
            case EN_MSGFILTER:
                filter = (struct qemu_MSGFILTER *)guest->lParam;
                MSGFILTER_g2h((MSGFILTER *)hdr, filter);
                break;

            case EN_SELCHANGE:
                selchange = (struct qemu_SELCHANGE *)guest->lParam;
                SELCHANGE_g2h((SELCHANGE *)hdr, selchange);
                break;
        }

        if (guest->lParam != host->lParam)
            HeapFree(GetProcessHeap(), 0, (void *)guest->lParam);
        return;
    }

    switch (hdr->code)
    {
        case EN_MSGFILTER:
            WINE_TRACE("Handling notification message EN_MSGFILTER.\n");
            filter = HeapAlloc(GetProcessHeap(), 0, sizeof(*filter));
            MSGFILTER_h2g(filter, (MSGFILTER *)hdr);
            guest->lParam = (LPARAM)filter;
            break;

        case EN_LINK:
            WINE_FIXME("Unhandled notification message EN_LINK.\n");
            break;

        case EN_SETFOCUS:
            WINE_FIXME("Unhandled notification message EN_SETFOCUS.\n");
            break;

        case EN_KILLFOCUS:
            WINE_FIXME("Unhandled notification message EN_KILLFOCUS.\n");
            break;

        case EN_UPDATE:
            WINE_FIXME("Unhandled notification message EN_MSGFILTER.\n");
            break;

        case EN_DROPFILES:
            WINE_FIXME("Unhandled notification message EN_DROPFILES.\n");
            break;

        case EN_OLEOPFAILED:
            WINE_FIXME("Unhandled notification message EN_OLEOPFAILED.\n");
            break;

        case EN_PROTECTED:
            WINE_FIXME("Unhandled notification message EN_PROTECTED.\n");
            break;

        case EN_REQUESTRESIZE:
            WINE_FIXME("Unhandled notification message EN_MSGFILTER.\n");
            break;

        case EN_SAVECLIPBOARD:
            WINE_FIXME("Unhandled notification message EN_SAVECLIPBOARD.\n");
            break;

        case EN_SELCHANGE:
            WINE_TRACE("Handling notification message EN_SELCHANGE.\n");
            selchange = HeapAlloc(GetProcessHeap(), 0, sizeof(*selchange));
            SELCHANGE_h2g(selchange, (SELCHANGE *)hdr);
            guest->lParam = (LPARAM)selchange;
            break;

        case EN_STOPNOUNDO:
            WINE_FIXME("Unhandled notification message EN_STOPNOUNDO.\n");
            break;

        default:
            WINE_ERR("Unexpected notify message %x.\n", hdr->code);
    }
}

static void register_notify_callbacks(void)
{
    QEMU_USER32_NOTIFY_FUNC register_notify;
    HMODULE qemu_user32 = GetModuleHandleA("qemu_user32");

    if (!qemu_user32)
        WINE_ERR("Cannot get qemu_user32.dll\n");
    register_notify = (void *)GetProcAddress(qemu_user32, "qemu_user32_notify");
    if (!register_notify)
        WINE_ERR("Cannot get qemu_user32_notify\n");

    register_notify(RICHEDIT_CLASS20W, riched20_notify);
    register_notify(MSFTEDIT_CLASS, riched20_notify);
}

#else

static void register_notify_callbacks(void) {}

#endif
static void qemu_set_callbacks(struct qemu_syscall *call)
{
    struct qemu_set_callbacks *c = (struct qemu_set_callbacks *)call;
    WINE_TRACE("\n");

    guest_ole_callback_QueryInterface = c->QueryInterface;
    guest_ole_callback_AddRef = c->AddRef;
    guest_ole_callback_Release = c->Release;
    guest_ole_callback_GetClipboardData = c->GetClipboardData;
    guest_editstream_cb = c->editstream_cb;
    guest_breakproc_wrapper = c->breakproc;

    register_notify_callbacks();
}

static const syscall_handler dll_functions[] =
{
    qemu_CreateTextServices,
    qemu_REExtendedRegisterClass,
    qemu_RichEdit10ANSIWndProc,
    qemu_RichEditANSIWndProc,
    qemu_set_callbacks,
};

static inline struct callback_impl *impl_from_IRichEditOleCallback(IRichEditOleCallback *iface)
{
    return CONTAINING_RECORD(iface, struct callback_impl, IRichEditOleCallback_iface);
}

static HRESULT STDMETHODCALLTYPE RichEditOleCallback_QueryInterface(IRichEditOleCallback *iface,
        REFIID riid, void **obj)
{
    struct callback_impl *impl = impl_from_IRichEditOleCallback(iface);

    WINE_FIXME("(%p, %s, %p)\n", impl, wine_dbgstr_guid(riid), obj);
    if (IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, &IID_IRichEditOleCallback))
    {
        iface->lpVtbl->AddRef(iface);
        *obj = iface;
        return S_OK;
    }
    WINE_FIXME("Unknown interface: %s\n", wine_dbgstr_guid(riid));
    return E_NOINTERFACE;
}

static ULONG STDMETHODCALLTYPE RichEditOleCallback_AddRef(IRichEditOleCallback *iface)
{
    struct callback_impl *impl = impl_from_IRichEditOleCallback(iface);
    ULONG refcount = InterlockedIncrement(&impl->refcount);

    WINE_TRACE("%p increasing refcount to %u.\n", impl, refcount);
    return refcount;
}

static ULONG STDMETHODCALLTYPE RichEditOleCallback_Release(IRichEditOleCallback *iface)
{
    struct callback_impl *impl = impl_from_IRichEditOleCallback(iface);
    ULONG refcount = InterlockedDecrement(&impl->refcount);

    WINE_TRACE("%p decreasing refcount to %u.\n", impl, refcount);
    if (!refcount)
    {
        uint64_t ret;
        WINE_TRACE("Releasing guest inteface.\n");
        ret = qemu_ops->qemu_execute(QEMU_G2H(guest_ole_callback_Release), QEMU_H2G(impl));
        WINE_TRACE("Guest returned refcount %lu.\n", (unsigned long)ret);
    }

    return refcount;
}

static HRESULT STDMETHODCALLTYPE RichEditOleCallback_GetNewStorage(IRichEditOleCallback* iface,
        LPSTORAGE *lplpstg)
{
    struct callback_impl *impl = impl_from_IRichEditOleCallback(iface);
    WINE_FIXME("(%p, %p)\n", impl, lplpstg);
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE RichEditOleCallback_GetInPlaceContext(IRichEditOleCallback* iface,
        LPOLEINPLACEFRAME *lplpFrame, LPOLEINPLACEUIWINDOW *lplpDoc,
        LPOLEINPLACEFRAMEINFO lpFrameInfo)
{
    struct callback_impl *impl = impl_from_IRichEditOleCallback(iface);
    WINE_FIXME("(%p, %p, %p, %p) stub\n", impl, lplpFrame, lplpDoc, lpFrameInfo);
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE RichEditOleCallback_ShowContainerUI(IRichEditOleCallback* iface,
        BOOL fShow)
{
    struct callback_impl *impl = impl_from_IRichEditOleCallback(iface);
    WINE_FIXME("(%p, %d)\n", impl, fShow);
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE RichEditOleCallback_QueryInsertObject(IRichEditOleCallback* iface,
        LPCLSID lpclsid, LPSTORAGE lpstg, LONG cp)
{
    struct callback_impl *impl = impl_from_IRichEditOleCallback(iface);
    WINE_FIXME("(%p, %p, %p, %d)\n", impl, lpclsid, lpstg, cp);
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE RichEditOleCallback_DeleteObject(IRichEditOleCallback* iface,
        LPOLEOBJECT lpoleobj)
{
    struct callback_impl *impl = impl_from_IRichEditOleCallback(iface);
    WINE_FIXME("(%p, %p)\n", impl, lpoleobj);
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE RichEditOleCallback_QueryAcceptData(IRichEditOleCallback* iface,
        LPDATAOBJECT lpdataobj, CLIPFORMAT *lpcfFormat, DWORD reco, BOOL fReally,
        HGLOBAL hMetaPict)
{
    struct callback_impl *impl = impl_from_IRichEditOleCallback(iface);
    WINE_FIXME("(%p, %p, %p, %x, %d, %p)\n",
            impl, lpdataobj, lpcfFormat, reco, fReally, hMetaPict);
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE RichEditOleCallback_ContextSensitiveHelp(IRichEditOleCallback* iface,
        BOOL fEnterMode)
{
    struct callback_impl *impl = impl_from_IRichEditOleCallback(iface);
    WINE_FIXME("(%p, %d)\n", impl, fEnterMode);
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE RichEditOleCallback_GetClipboardData(IRichEditOleCallback* iface,
        CHARRANGE *lpchrg, DWORD reco, LPDATAOBJECT *lplpdataobj)
{
    struct callback_impl *impl = impl_from_IRichEditOleCallback(iface);
    struct qemu_GetClipboardData_cb stack, *call = &stack;
    struct
    {
        struct qemu_GetClipboardData_cb call;
        CHARRANGE chrg;
    } *alloc = NULL;
    HRESULT hr;

    WINE_TRACE("(%p, %p, %x, %p)\n", impl, lpchrg, reco, lplpdataobj);

#if GUEST_BIT != HOST_BIT
    alloc = HeapAlloc(GetProcessHeap(), 0, sizeof(*alloc));
    call = &alloc->call;
    call->chrg = (ULONG_PTR)&alloc->chrg;
#else
    call->chrg = (ULONG_PTR)lpchrg;
#endif

    call->impl = (ULONG_PTR)impl;
    call->reco = reco;

    hr = qemu_ops->qemu_execute(QEMU_G2H(guest_ole_callback_GetClipboardData), QEMU_H2G(call));

    if (SUCCEEDED(hr) && call->object)
        WINE_FIXME("Wrap returned IDataObject 0x%lx.\n", (unsigned long)call->object);
    *lplpdataobj = NULL;

    if (alloc)
    {
        *lpchrg = alloc->chrg;
        HeapFree(GetProcessHeap(), 0, call);
    }

    return hr;
}

static HRESULT STDMETHODCALLTYPE RichEditOleCallback_GetDragDropEffect( IRichEditOleCallback* iface, BOOL fDrag,
        DWORD grfKeyState, LPDWORD pdwEffect)
{
    struct callback_impl *impl = impl_from_IRichEditOleCallback(iface);
    WINE_FIXME("(%p, %d, %x, %p)\n", impl, fDrag, grfKeyState, pdwEffect);
    return E_FAIL;
}

static HRESULT STDMETHODCALLTYPE RichEditOleCallback_GetContextMenu(IRichEditOleCallback* iface, WORD seltype,
        LPOLEOBJECT lpoleobj, CHARRANGE *lpchrg, HMENU *lphmenu)
{
    struct callback_impl *impl = impl_from_IRichEditOleCallback(iface);
    WINE_TRACE("(%p, %x, %p, %p, %p)\n", impl, seltype, lpoleobj, lpchrg, lphmenu);

    return E_FAIL;
}

static const struct IRichEditOleCallbackVtbl ole_callback_vtbl =
{
    RichEditOleCallback_QueryInterface,
    RichEditOleCallback_AddRef,
    RichEditOleCallback_Release,
    RichEditOleCallback_GetNewStorage,
    RichEditOleCallback_GetInPlaceContext,
    RichEditOleCallback_ShowContainerUI,
    RichEditOleCallback_QueryInsertObject,
    RichEditOleCallback_DeleteObject,
    RichEditOleCallback_QueryAcceptData,
    RichEditOleCallback_ContextSensitiveHelp,
    RichEditOleCallback_GetClipboardData,
    RichEditOleCallback_GetDragDropEffect,
    RichEditOleCallback_GetContextMenu
};

WNDPROC orig_proc_w, orig_proc_a, orig_proc_10a;

static LRESULT handle_set_ole_callback(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL unicode)
{
    struct callback_impl *cb;
    uint64_t ref;
    LRESULT ret;

    /* Note that injecting the wrapper COM interface here only works because no other Wine DLL uses
     * riched20. If a builtin library called riched20 we would need a way to figure out if the message
     * comes from the guest application (and thus needs the wrapper) or comes from a host DLL (and thus
     * already has ARM code, and can't be called inside the VM). That would require integration with
     * user32's wndproc wrappers.
     *
     * One hack that wouldn't involve breaking DLL separation would be to try to call QueryInterface
     * in a try/catch handler and see if it returns something useful or crashes. */

    cb = HeapAlloc(GetProcessHeap(), 0, sizeof(*cb));
    cb->guest = (void *)lParam;
    cb->refcount = 1;
    cb->IRichEditOleCallback_iface.lpVtbl = &ole_callback_vtbl;

    WINE_TRACE("AddRefing guest inteface.\n");
    ref = qemu_ops->qemu_execute(QEMU_G2H(guest_ole_callback_AddRef), QEMU_H2G(cb));
    WINE_TRACE("Guest returned refcount %lu.\n", (unsigned long)ref);

    if (unicode)
        ret = CallWindowProcW(orig_proc_w, hWnd, msg, wParam, (LPARAM)&cb->IRichEditOleCallback_iface);
    else
        ret = CallWindowProcA(orig_proc_a, hWnd, msg, wParam, (LPARAM)&cb->IRichEditOleCallback_iface);

    /* This will destroy the callback in case the host procedure didn't do anything with it. */
    cb->IRichEditOleCallback_iface.lpVtbl->Release(&cb->IRichEditOleCallback_iface);

    return ret;
}

struct stream_cb_data
{
    uint64_t guest_cookie;
    uint64_t guest_cb;
};

static DWORD CALLBACK host_stream_cb(DWORD_PTR cookie, LPBYTE buffer, LONG cb, LONG *pcb)
{
    struct qemu_editstream_cb stack, *call = &stack;
    struct stream_cb_data *data = (struct stream_cb_data *)cookie;
    DWORD ret;
    struct alloc
    {
        struct qemu_editstream_cb call;
        LONG pcb;
        BYTE buffer[1];
    } *alloc = NULL;

#if HOST_BIT != GUEST_BIT
    alloc = HeapAlloc(GetProcessHeap(), 0, FIELD_OFFSET(struct alloc, buffer[cb]));
    memcpy(alloc->buffer, buffer, cb);
    alloc->pcb = *pcb;

    call = &alloc->call;
    call->buffer = (ULONG_PTR)alloc->buffer;
    call->pcb = (ULONG_PTR)&alloc->pcb;
#else
    call->buffer = (ULONG_PTR)buffer;
    call->pcb = (ULONG_PTR)pcb;
#endif

    call->cb_func = data->guest_cb;
    call->cookie = data->guest_cookie;
    call->cb = cb;

    WINE_TRACE("Calling guest callback 0x%lx(0x%lx, 0x%lx, %lu, 0x%lx).\n",
            (unsigned long)call->cb_func, (unsigned long)call->cookie, (unsigned long)call->buffer,
            (unsigned long)call->cb, (unsigned long)call->pcb);

    ret = qemu_ops->qemu_execute(QEMU_G2H(guest_editstream_cb), QEMU_H2G(call));

    WINE_TRACE("Guest callback returned %x.\n", ret);
    if (alloc)
    {
        *pcb = alloc->pcb;
        memcpy(buffer, alloc->buffer, cb);
        HeapFree(GetProcessHeap(), 0, alloc);
    }

    return ret;
}

static LRESULT handle_stream(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL unicode)
{
    struct stream_cb_data data;
    EDITSTREAM es;
    LRESULT ret;

#if GUEST_BIT == HOST_BIT
    es = *(EDITSTREAM *)lParam;
#else
    EDITSTREAM_g2h(&es, (void *)lParam);
#endif

    /* EDITSTREAM is only valid until the message is processed. */
    data.guest_cookie = es.dwCookie;
    data.guest_cb = (ULONG_PTR)es.pfnCallback;
    es.dwCookie = (DWORD_PTR)&data;
    es.pfnCallback = host_stream_cb;

    if (unicode)
        ret = CallWindowProcW(orig_proc_w, hWnd, msg, wParam, (LPARAM)&es);
    else
        ret = CallWindowProcA(orig_proc_a, hWnd, msg, wParam, (LPARAM)&es);

    es.dwCookie = data.guest_cookie;
    es.pfnCallback = (EDITSTREAMCALLBACK)data.guest_cb;
#if GUEST_BIT == HOST_BIT
    *(EDITSTREAM *)lParam = es;
#else
    EDITSTREAM_h2g((void *)lParam, &es);
#endif

    return ret;
}

static uint64_t guest_breakproc;

static LONG CALLBACK host_breakproc(WCHAR *text, int pos, int bytes, int code)
{
    struct qemu_breakproc_cb call;
    LONG ret;

    call.cb = guest_breakproc;
    call.text = (ULONG_PTR)text;
    call.pos = pos;
    call.bytes = bytes;
    call.code = code;

    WINE_TRACE("Calling guest callback 0x%lx(%p, %d, %d, %d).\n",
            (unsigned long)call.cb, text, pos, bytes, code);

    ret = qemu_ops->qemu_execute(QEMU_G2H(guest_breakproc_wrapper), QEMU_H2G(&call));

    WINE_TRACE("Guest callback returned %x.\n", ret);
    return ret;
}

static LRESULT handle_breakproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL unicode)
{
    /* There may be more than one richedit control active. */
    if (guest_breakproc && guest_breakproc != lParam)
        WINE_FIXME("Only one breakproc is supported at the moment.\n");

    guest_breakproc = lParam;

    if (unicode)
        return CallWindowProcW(orig_proc_w, hWnd, msg, wParam, lParam ? (LPARAM)host_breakproc : 0);
    else
        return CallWindowProcA(orig_proc_a, hWnd, msg, wParam, lParam ? (LPARAM)host_breakproc : 0);
}

static LRESULT handle_findtext(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL unicode)
{
    FINDTEXTW host;
    LRESULT ret;
    struct qemu_FINDTEXT *guest = (struct qemu_FINDTEXT *)lParam;

    FINDTEXT_g2h(&host, guest);

    if (unicode)
        ret = CallWindowProcW(orig_proc_w, hWnd, msg, wParam, (LPARAM)&host);
    else
        ret = CallWindowProcA(orig_proc_a, hWnd, msg, wParam, (LPARAM)&host);

    FINDTEXT_h2g(guest, &host);

    return ret;
}

static LRESULT handle_findtextex(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL unicode)
{
    FINDTEXTEXW host;
    LRESULT ret;
    struct qemu_FINDTEXTEX *guest = (struct qemu_FINDTEXTEX *)lParam;

    FINDTEXTEX_g2h(&host, guest);

    if (unicode)
        ret = CallWindowProcW(orig_proc_w, hWnd, msg, wParam, (LPARAM)&host);
    else
        ret = CallWindowProcA(orig_proc_a, hWnd, msg, wParam, (LPARAM)&host);

    FINDTEXTEX_h2g(guest, &host);

    return ret;
}

static LRESULT handle_formatrange(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL unicode)
{
    FORMATRANGE host;
    LRESULT ret;
    struct qemu_FORMATRANGE *guest = (struct qemu_FORMATRANGE *)lParam;

    if (guest)
        FORMATRANGE_g2h(&host, guest);

    if (unicode)
        ret = CallWindowProcW(orig_proc_w, hWnd, msg, wParam, guest ? (LPARAM)&host : 0);
    else
        ret = CallWindowProcA(orig_proc_a, hWnd, msg, wParam, guest ? (LPARAM)&host : 0);

    if (guest)
        FORMATRANGE_h2g(guest, &host);

    return ret;
}

static LRESULT WINAPI wrap_proc_w(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    WINE_TRACE("Richedit message %x\n", msg);

    switch (msg)
    {
        case EM_SETOLECALLBACK:
            return handle_set_ole_callback(hWnd, msg, wParam, lParam, TRUE);

        case EM_STREAMIN:
        case EM_STREAMOUT:
            return handle_stream(hWnd, msg, wParam, lParam, TRUE);
            break;

        case EM_SETWORDBREAKPROC:
            return handle_breakproc(hWnd, msg, wParam, lParam, TRUE);

#if HOST_BIT != GUEST_BIT
        case EM_FINDTEXT:
        case EM_FINDTEXTW:
            return handle_findtext(hWnd, msg, wParam, lParam, TRUE);
        case EM_FINDTEXTEX:
        case EM_FINDTEXTEXW:
            return handle_findtextex(hWnd, msg, wParam, lParam, TRUE);

        case EM_FORMATRANGE:
            return handle_formatrange(hWnd, msg, wParam, lParam, TRUE);
#endif

        default:
            return CallWindowProcW(orig_proc_w, hWnd, msg, wParam, lParam);
    }
}

LRESULT WINAPI wrap_proc_a(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    WINE_TRACE("Richedit message %x\n", msg);

    switch (msg)
    {
        case EM_SETOLECALLBACK:
            return handle_set_ole_callback(hWnd, msg, wParam, lParam, FALSE);

        case EM_STREAMIN:
        case EM_STREAMOUT:
            return handle_stream(hWnd, msg, wParam, lParam, FALSE);

        case EM_SETWORDBREAKPROC:
            return handle_breakproc(hWnd, msg, wParam, lParam, FALSE);

#if HOST_BIT != GUEST_BIT
        case EM_FINDTEXT:
        case EM_FINDTEXTW:
            return handle_findtext(hWnd, msg, wParam, lParam, FALSE);
        case EM_FINDTEXTEX:
        case EM_FINDTEXTEXW:
            return handle_findtextex(hWnd, msg, wParam, lParam, FALSE);

        case EM_FORMATRANGE:
            return handle_formatrange(hWnd, msg, wParam, lParam, FALSE);
#endif

        default:
            return CallWindowProcA(orig_proc_a, hWnd, msg, wParam, lParam);
    }
}

LRESULT WINAPI wrap_proc_10a(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    WINE_TRACE("Richedit 1.0 message %x\n", msg);
    if (msg == WM_NCCREATE && !GetWindowLongPtrW(hWnd, 0))
        return CallWindowProcA(orig_proc_10a, hWnd, msg, wParam, lParam);

    return wrap_proc_a(hWnd, msg, wParam, lParam);
}

static inline BOOL is_version_nt(void)
{
    return !(GetVersion() & 0x80000000);
}

void WINAPI qemu_riched20_hook_old(HMODULE riched32)
{
    HWND win;
    WINE_TRACE("Called to hook riched 1.0 %p.\n", riched32);

    win = CreateWindowExA(0, RICHEDIT_CLASS10A, NULL,
            WS_POPUP, 0, 0, 200, 60, NULL, NULL, riched32, NULL);
    if (!win)
        WINE_ERR("Failed to instantiate a RICHEDIT_CLASS10A window.\n");

    orig_proc_10a = (WNDPROC)SetClassLongPtrA(win, GCLP_WNDPROC, (ULONG_PTR)wrap_proc_10a);
    if (!orig_proc_10a)
        WINE_ERR("Failed to set WNDPROC of RICHEDIT_CLASS10A.\n");

    DestroyWindow(win);
}

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HWND win;
    HMODULE riched20 = GetModuleHandleA("riched20");
    WNDPROC wndproc2;

    WINE_TRACE("Loading host-side riched20 wrapper.\n");

    /* Apparently the only way to change the class wndproc is through a window of that class... */

    win = CreateWindowExA(0, RICHEDIT_CLASS20A, NULL,
            WS_POPUP, 0, 0, 200, 60, NULL, NULL, riched20, NULL);
    if (!win)
        WINE_ERR("Failed to instantiate a RICHEDIT_CLASS20A window.\n");

    orig_proc_a = (WNDPROC)SetClassLongPtrA(win, GCLP_WNDPROC, (ULONG_PTR)wrap_proc_a);
    if (!orig_proc_a)
        WINE_ERR("Failed to set WNDPROC of RICHEDIT_CLASS20A.\n");

    DestroyWindow(win);

    win = CreateWindowExA(0, "RichEdit50A", NULL,
            WS_POPUP, 0, 0, 200, 60, NULL, NULL, riched20, NULL);
    if (!win)
        WINE_ERR("Failed to instantiate a RichEdit50A window.\n");

    wndproc2 = (WNDPROC)SetClassLongPtrA(win, GCLP_WNDPROC, (ULONG_PTR)wrap_proc_a);
    if (wndproc2 != orig_proc_a)
        WINE_ERR("Failed to set WNDPROC of RichEdit50A.\n");

    DestroyWindow(win);

    if (is_version_nt())
    {
        win = CreateWindowExW(0, RICHEDIT_CLASS20W, NULL,
                WS_POPUP, 0, 0, 200, 60, NULL, NULL, riched20, NULL);
        if (!win)
            WINE_ERR("Failed to instantiate a RICHEDIT_CLASS20W window.\n");

        orig_proc_w = (WNDPROC)SetClassLongPtrW(win, GCLP_WNDPROC, (ULONG_PTR)wrap_proc_w);
        if (!orig_proc_w)
            WINE_ERR("Failed to set WNDPROC of RICHEDIT_CLASS20W.\n");

        DestroyWindow(win);

        win = CreateWindowExW(0, MSFTEDIT_CLASS, NULL,
                WS_POPUP, 0, 0, 200, 60, NULL, NULL, riched20, NULL);
        if (!win)
            WINE_ERR("Failed to instantiate a MSFTEDIT_CLASS window.\n");

        wndproc2 = (WNDPROC)SetClassLongPtrW(win, GCLP_WNDPROC, (ULONG_PTR)wrap_proc_w);
        if (wndproc2 != orig_proc_w)
            WINE_ERR("Failed to set WNDPROC of MSFTEDIT_CLASS.\n");

        DestroyWindow(win);
    }
    else
    {
        win = CreateWindowExA(0, "RichEdit20W", NULL,
                WS_POPUP, 0, 0, 200, 60, NULL, NULL, riched20, NULL);
        if (!win)
            WINE_ERR("Failed to instantiate a RICHEDIT_CLASS20W window.\n");

        orig_proc_w = (WNDPROC)SetClassLongPtrA(win, GCLP_WNDPROC, (ULONG_PTR)wrap_proc_w);
        if (!orig_proc_w)
            WINE_ERR("Failed to set WNDPROC of RICHEDIT_CLASS20W.\n");

        DestroyWindow(win);

        win = CreateWindowExA(0, "RichEdit50W", NULL,
                WS_POPUP, 0, 0, 200, 60, NULL, NULL, riched20, NULL);
        if (!win)
            WINE_ERR("Failed to instantiate a RichEdit50W window.\n");

        wndproc2 = (WNDPROC)SetClassLongPtrA(win, GCLP_WNDPROC, (ULONG_PTR)wrap_proc_w);
        if (wndproc2 != orig_proc_w)
            WINE_ERR("Failed to set WNDPROC of RichEdit50W.\n");

        DestroyWindow(win);
    }

    /* Overwrite W: Confused. */

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
