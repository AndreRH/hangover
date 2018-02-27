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

#include <winsock2.h>
#include <windows.h>
#include <commctrl.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_commctrl.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_comctl32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
#include "callback_helper.h"
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comctl32);
#endif


struct qemu_PropertySheet
{
    struct qemu_syscall super;
    uint64_t lppsh;
    uint64_t wrapper;
};

struct qemu_PropertySheet_cb
{
    uint64_t cb, hwnd, msg, lparam;
};

struct qemu_PropertySheetPage_cb
{
    uint64_t cb, hwnd, msg, page;
};

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall PropertySheet_guest_cb(struct qemu_PropertySheet_cb *data)
{
    PFNPROPSHEETCALLBACK cb = (PFNPROPSHEETCALLBACK)(ULONG_PTR)data->cb;
    return cb((HWND)(ULONG_PTR)data->hwnd, data->msg, data->lparam);
}

UINT __fastcall PropertySheetPage_guest_cb(struct qemu_PropertySheetPage_cb *data)
{
    LPFNPSPCALLBACKW func = (LPFNPSPCALLBACKW)(ULONG_PTR)data->cb;
    return func((HWND)(ULONG_PTR)data->hwnd, data->msg, (void *)(ULONG_PTR)data->page);
}

WINBASEAPI INT_PTR WINAPI PropertySheetA(LPCPROPSHEETHEADERA lppsh)
{
    struct qemu_PropertySheet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PROPERTYSHEETA);
    call.lppsh = (ULONG_PTR)lppsh;
    call.wrapper = (ULONG_PTR)PropertySheet_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

WINBASEAPI INT_PTR WINAPI PropertySheetW(LPCPROPSHEETHEADERW lppsh)
{
    struct qemu_PropertySheet call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PROPERTYSHEETW);
    call.lppsh = (ULONG_PTR)lppsh;
    call.wrapper = (ULONG_PTR)PropertySheet_guest_cb;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

struct propsheet_data
{
    /* Top level callback wrapper */
    struct callback_entry callback_entry;

    PROPSHEETHEADERW header;
    ULONG ref;
    uint64_t guest_wrapper;
    struct propsheet_data *old;

    /* I need to pass this array to PropertySheetW(), so I can't interleave it with my own data. */
    PROPSHEETPAGEW *pages;

    struct page_data page_data[1];

};

static UINT CALLBACK propsheet_host_cb(HWND hwnd, UINT msg, PROPSHEETPAGEW *page)
{
    /* We get a PROPSHEETPAGEW struct with the original data, but not our
     * original address.
     *
     * TODO: Think if we can get rid of data->pages, we're not using it here or anywhere
     * else after creating the property sheet pages. */
    struct page_data *page_data = (struct page_data *)page->lParam;
    struct propsheet_data *data = page_data->header;
    struct qemu_PropertySheetPage_cb call;
    UINT ret = 0;

    if (!data)
        return 0;

    if (page_data->guest_cb)
    {
        PROPSHEETPAGEW copy = *page;
        struct qemu_PROPSHEETPAGE copy32;

        copy.pfnCallback = (LPFNPSPCALLBACKW)(ULONG_PTR)page_data->guest_cb;
        copy.pfnDlgProc = (DLGPROC)(ULONG_PTR)page_data->guest_dlgproc;
        copy.lParam = page_data->guest_lparam;

        call.cb = page_data->guest_cb;
        call.hwnd = QEMU_H2G(hwnd);
        call.msg = msg;
#if HOST_BIT == GUEST_BIT
        call.page = QEMU_H2G(&copy);
#else
        copy32.dwSize = sizeof(copy32);
        PROPSHEETPAGE_h2g(&copy32, &copy);
        call.page = QEMU_H2G(&copy32);
#endif

        WINE_TRACE("Calling guest callback 0x%lx(%p, 0x%x, 0x%lx).\n", page_data->guest_cb, hwnd, msg, call.page);
        ret = qemu_ops->qemu_execute(QEMU_G2H(PropertySheetPage_guest_cb), QEMU_H2G(&call));
        WINE_TRACE("Guest callback returned %u.\n", ret);
    }

    /* Note: If the property sheet is created with PSH_PROPSHEETPAGE, only the first
     * page currently has data->header set. If the pages are created individually and
     * oassed to CreatePropertySheet by HANDLE all of them have a header structure
     * for memory management purposes. */
    switch (msg)
    {
        case PSPCB_ADDREF:
            /* Will be called from one thread only. */
            data->ref++;
            break;

        case PSPCB_RELEASE:
            if (!--data->ref)
            {
                WINE_TRACE("Release data %p.\n", data);
                HeapFree(GetProcessHeap(), 0, data->pages);
                if (data->old)
                    VirtualFree(data->old, 0, MEM_RELEASE);
                VirtualFree(data, 0, MEM_RELEASE);
            }
            break;

        default:
            break;
    }

    return ret;
}

static INT CALLBACK propsheet_header_host_cb(HWND hwnd, UINT msg, LPARAM lparam, struct callback_entry *entry)
{
    struct propsheet_data *data = CONTAINING_RECORD(entry, struct propsheet_data, callback_entry);
    struct qemu_PropertySheet_cb call;
    INT ret;

    call.cb = data->callback_entry.guest_proc;
    call.hwnd = (ULONG_PTR)hwnd;
    call.msg = msg;
    call.lparam = lparam;

    WINE_TRACE("Calling guest callback 0x%lx(%p, 0x%x, 0x%lx).\n", (unsigned long)call.cb,
            hwnd, msg, lparam);
    ret = qemu_ops->qemu_execute(QEMU_G2H(data->guest_wrapper), QEMU_H2G(&call));
    WINE_TRACE("Guest callback returned %u.\n", ret);

    return ret;
}

void qemu_PropertySheet(struct qemu_syscall *call)
{
    struct qemu_PropertySheet *c = (struct qemu_PropertySheet *)call;
    struct propsheet_data *data;
    unsigned int i, page_count;
    PROPSHEETHEADERW copy, *header_in = &copy;
    size_t offset;
    HPROPSHEETPAGE *handle_array = NULL;
    BOOL create_pages;

    /* FIXME: My god is this ugly and complicated. Is there some easier way? */
    WINE_TRACE("\n");

    if (!c->lppsh)
    {
        if (c->super.id == QEMU_SYSCALL_ID(CALL_PROPERTYSHEETA))
            c->super.iret = p_PropertySheetA(NULL);
        else
            c->super.iret = p_PropertySheetW(NULL);
        return;
    }

#if GUEST_BIT == HOST_BIT
    header_in = (PROPSHEETHEADERW *)QEMU_G2H(c->lppsh);
#else
    PROPSHEETHEADER_g2h(header_in, QEMU_G2H(c->lppsh));
#endif

    page_count = header_in->nPages;
    data = VirtualAlloc(NULL, FIELD_OFFSET(struct propsheet_data, page_data[page_count]), MEM_COMMIT,
            PAGE_EXECUTE_READWRITE);
    memcpy(&data->header, header_in, min(header_in->dwSize, sizeof(data->header)));
    data->header.hInstance = qemu_ops->qemu_module_g2h((uint64_t)header_in->hInstance);
    data->ref = 1;

    /* Does the top level callback (PFNPROPSHEETCALLBACK) allow us to pass a custom pointer somewhere?
     * Why do you ask, of course it doesn't... */
    callback_init(&data->callback_entry, 3, propsheet_header_host_cb);

    create_pages = data->header.dwFlags & PSH_PROPSHEETPAGE;
    if (create_pages)
    {
        data->pages = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, page_count * sizeof(*data->pages));
        if (!data->pages)
        {
            VirtualFree(data, 0, MEM_RELEASE);
            c->super.iret = -1;
            return;
        }

        for (i = 0; i < page_count; ++i)
        {
#if GUEST_BIT == HOST_BIT
            memcpy(&data->pages[i], &header_in->ppsp[i],
                    min(header_in->ppsp[i].dwSize, sizeof(data->pages[i])));
#else
            PROPSHEETPAGE_g2h(&data->pages[i], &((struct qemu_PROPSHEETPAGE *)header_in->ppsp)[i]);
#endif

            data->pages[i].hInstance = qemu_ops->qemu_module_g2h((uint64_t)data->pages[i].hInstance);
            data->page_data[i].guest_dlgproc = (ULONG_PTR)data->pages[i].pfnDlgProc;
            if (data->pages[i].pfnDlgProc)
                data->pages[i].pfnDlgProc = (DLGPROC)wndproc_guest_to_host((ULONG_PTR)data->pages[i].pfnDlgProc);

            if (data->pages[i].pfnCallback && (data->pages[i].dwFlags & PSP_USECALLBACK))
                data->page_data[i].guest_cb = (ULONG_PTR)data->pages[i].pfnCallback;

            data->pages[i].pfnCallback = propsheet_host_cb;
            data->page_data[i].guest_lparam = data->pages[i].lParam;
            data->pages[i].lParam = (LPARAM)&data->page_data[i];
        }
        data->header.ppsp = data->pages;
        data->pages[0].dwFlags |= PSP_USECALLBACK;
        data->page_data[0].header = data;
    }
    else
    {
        PROPSHEETPAGEW *page0;
        struct page_data *page_data;

#if HOST_BIT == GUEST_BIT
        handle_array = header_in->phpage;
#else
        qemu_ptr *array32 = QEMU_G2H(header_in->phpage);
        handle_array = HeapAlloc(GetProcessHeap(), 0, sizeof(*handle_array) * page_count);
        for (i = 0; i < page_count; ++i)
            handle_array[i] = QEMU_G2H((uint64_t)array32[i]);
        data->header.phpage = handle_array;
#endif

        page0 = (PROPSHEETPAGEW *)handle_array[0];
        page_data = (struct page_data *)page0->lParam;

        /* We can't release the old header here because the page data is a part of it.
         * Remember to destroy it later. */
        data->old = page_data->header;
        page_data->header = data;
        data->pages = data->old->pages;
    }

    if ((data->header.dwFlags & PSH_USECALLBACK) && data->header.pfnCallback)
    {
        data->callback_entry.guest_proc = (ULONG_PTR)data->header.pfnCallback;
        data->guest_wrapper = c->wrapper;
        data->header.pfnCallback = (PFNPROPSHEETCALLBACK)data;
    }

    if (c->super.id == QEMU_SYSCALL_ID(CALL_PROPERTYSHEETA))
        c->super.iret = p_PropertySheetA((PROPSHEETHEADERA *)&data->header);
    else
        c->super.iret = p_PropertySheetW(&data->header);

    if (create_pages)
    {
        /* Release our own reference. */
        if (!--data->ref)
        {
            WINE_TRACE("Release data %p.\n", data);
            HeapFree(GetProcessHeap(), 0, data->pages);
            if (data->old)
                VirtualFree(data->old, 0, MEM_RELEASE);
            VirtualFree(data, 0, MEM_RELEASE);
        }
    }

#if HOST_BIT != GUEST_BIT
    HeapFree(GetProcessHeap(), 0, handle_array);
#endif
}

#endif

struct qemu_CreatePropertySheetPage
{
    struct qemu_syscall super;
    uint64_t lpPropSheetPage;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HPROPSHEETPAGE WINAPI CreatePropertySheetPageA(LPCPROPSHEETPAGEA lpPropSheetPage)
{
    struct qemu_CreatePropertySheetPage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPROPERTYSHEETPAGEA);
    call.lpPropSheetPage = (ULONG_PTR)lpPropSheetPage;

    qemu_syscall(&call.super);

    return (HPROPSHEETPAGE)(ULONG_PTR)call.super.iret;
}

WINBASEAPI HPROPSHEETPAGE WINAPI CreatePropertySheetPageW(LPCPROPSHEETPAGEW lpPropSheetPage)
{
    struct qemu_CreatePropertySheetPage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPROPERTYSHEETPAGEW);
    call.lpPropSheetPage = (ULONG_PTR)lpPropSheetPage;

    qemu_syscall(&call.super);

    return (HPROPSHEETPAGE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreatePropertySheetPage(struct qemu_syscall *call)
{
    struct qemu_CreatePropertySheetPage *c = (struct qemu_CreatePropertySheetPage *)call;
    PROPSHEETPAGEW stack, *page = &stack;
    struct propsheet_data *data;
    WINE_TRACE("\n");

    if (!c->lpPropSheetPage)
    {
        if (c->super.id == QEMU_SYSCALL_ID(CALL_CREATEPROPERTYSHEETPAGEA))
            c->super.iret = (ULONG_PTR)p_CreatePropertySheetPageA(NULL);
        else
            c->super.iret = (ULONG_PTR)p_CreatePropertySheetPageW(NULL);
        return;
    }

#if GUEST_BIT == HOST_BIT
    page = QEMU_G2H(c->lpPropSheetPage);
#else
    PROPSHEETPAGE_g2h(page, QEMU_G2H(c->lpPropSheetPage));
#endif

    data = VirtualAlloc(NULL, FIELD_OFFSET(struct propsheet_data, page_data[1]), MEM_COMMIT,
            PAGE_EXECUTE_READWRITE);
    data->ref = 1;

    /* The callback code should not need initialization. This is just a dummy and will not be
     * called. CreatePropertySheet may later replace it with one that is actually called. */

    data->pages = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*data->pages));
    if (!data->pages)
    {
        VirtualFree(data, 0, MEM_RELEASE);
        c->super.iret = -1;
        return;
    }

    memcpy(&data->pages[0], page, min(page->dwSize, sizeof(data->pages[0])));

    data->pages[0].hInstance = qemu_ops->qemu_module_g2h((uint64_t)page->hInstance);
    data->page_data[0].guest_dlgproc = (ULONG_PTR)data->pages[0].pfnDlgProc;
    if (data->pages[0].pfnDlgProc)
        data->pages[0].pfnDlgProc = (DLGPROC)wndproc_guest_to_host((ULONG_PTR)data->pages[0].pfnDlgProc);

    if (data->pages[0].pfnCallback && (data->pages[0].dwFlags & PSP_USECALLBACK))
        data->page_data[0].guest_cb = (ULONG_PTR)data->pages[0].pfnCallback;

    data->page_data[0].guest_lparam = data->pages[0].lParam;
    data->pages[0].lParam = (LPARAM)&data->page_data[0];

    data->header.ppsp = data->pages;
    data->pages[0].dwFlags |= PSP_USECALLBACK;
    data->pages[0].pfnCallback = propsheet_host_cb;
    data->page_data[0].header = data;

    if (c->super.id == QEMU_SYSCALL_ID(CALL_CREATEPROPERTYSHEETPAGEA))
        c->super.iret = (ULONG_PTR)p_CreatePropertySheetPageA((PROPSHEETPAGEA *)&data->pages[0]);
    else
        c->super.iret = (ULONG_PTR)p_CreatePropertySheetPageW(&data->pages[0]);

    /* Release our own reference if we have a page with refcounting. Otherwise destroy it on failure. */
    if (page->dwSize > PROPSHEETPAGEA_V1_SIZE)
    {
        if (!--data->ref)
        {
            WINE_TRACE("Release data %p.\n", data);
            HeapFree(GetProcessHeap(), 0, data->pages);
            VirtualFree(data, 0, MEM_RELEASE);
        }
    }
    else if (!c->super.iret)
    {
        HeapFree(GetProcessHeap(), 0, data->pages);
        VirtualFree(data, 0, MEM_RELEASE);
    }
}

#endif

struct qemu_DestroyPropertySheetPage
{
    struct qemu_syscall super;
    uint64_t hPropPage;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DestroyPropertySheetPage(HPROPSHEETPAGE hPropPage)
{
    struct qemu_DestroyPropertySheetPage call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DESTROYPROPERTYSHEETPAGE);
    call.hPropPage = (ULONG_PTR)hPropPage;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DestroyPropertySheetPage(struct qemu_syscall *call)
{
    struct qemu_DestroyPropertySheetPage *c = (struct qemu_DestroyPropertySheetPage *)call;
    WINE_TRACE("\n");
    c->super.iret = p_DestroyPropertySheetPage(QEMU_G2H(c->hPropPage));
}

#endif

#ifndef QEMU_DLL_GUEST
struct qemu_NMHDR *propsheet_notify_h2g(NMHDR *host)
{
    struct qemu_PSHNOTIFY *notify;

    switch (host->code)
    {
        case PSN_SETACTIVE:
        case PSN_KILLACTIVE:
        case PSN_APPLY:
        case PSN_RESET:
        case PSN_HELP:
        case PSN_WIZBACK:
        case PSN_WIZNEXT:
        case PSN_WIZFINISH:
        case PSN_QUERYCANCEL:
        case PSN_GETOBJECT:
        case PSN_TRANSLATEACCELERATOR:
        case PSN_QUERYINITIALFOCUS:
            notify = HeapAlloc(GetProcessHeap(), 0, sizeof(*notify));
            PSHNOTIFY_h2g(notify, (PSHNOTIFY *)host);
            return &notify->hdr;

        default:
            WINE_ERR("Unexpected propsheet notify message %x.\n", host->code);
            return NULL;
    }
}

void propsheet_notify_g2h(NMHDR *host, NMHDR *guest)
{
    switch (host->code)
    {
    }

    if (guest != host)
        HeapFree(GetProcessHeap(), 0, guest);
}

#endif

