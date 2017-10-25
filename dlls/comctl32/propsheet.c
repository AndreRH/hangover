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

#ifdef QEMU_DLL_GUEST

static uint64_t __fastcall PropertySheet_guest_cb(struct qemu_PropertySheet_cb *data)
{
    PFNPROPSHEETCALLBACK cb = (PFNPROPSHEETCALLBACK)(ULONG_PTR)data->cb;
    return cb((HWND)(ULONG_PTR)data->hwnd, data->msg, data->lparam);
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

static UINT propsheet_host_cb(HWND hwnd, UINT msg, PROPSHEETPAGEW *page)
{
    /* We get a PROPSHEETPAGEW struct with the original data, but not our
     * original address.
     *
     * Why do I need to keep my alloc'ed struct around then? I guess for
     * calling the guest callback, if I implement this one day. */
    struct page_data *page_data = (struct page_data *)page->lParam;
    struct propsheet_data *data = page_data->header;

    if (!data)
        return 0;

    switch (msg)
    {
        case PSPCB_ADDREF:
            /* Will be called from one thread only. */
            data->ref++;
            return 0;

        case PSPCB_RELEASE:
            if (!--data->ref)
            {
                HeapFree(GetProcessHeap(), 0, data->pages);
                VirtualFree(data, 0, MEM_RELEASE);
            }
            return 0;

        default:
            return 0;
    }
}

static INT CALLBACK propsheet_header_host_cb(HWND hwnd, UINT msg, LPARAM lparam, struct propsheet_data *data)
{
    struct qemu_PropertySheet_cb stack, *call = &stack;
    INT ret;

#if GUEST_BIT != HOST_BIT
    call = HeapAlloc(GetProcessHeap(), 0, sizeof(*call));
#endif

    call->cb = data->guest_cb;
    call->hwnd = (ULONG_PTR)hwnd;
    call->msg = msg;
    call->lparam = lparam;

    WINE_TRACE("Calling guest callback 0x%lx(0x%lx, %lx, 0x%lx).\n", call->cb, call->hwnd,
            call->msg, call->lparam);
    ret = qemu_ops->qemu_execute(QEMU_G2H(data->guest_wrapper), QEMU_H2G(call));
    WINE_TRACE("Guest callback returned %u.\n", ret);

    if (call != &stack)
        HeapFree(GetProcessHeap(), 0, call);

    return ret;
}

void qemu_PropertySheet(struct qemu_syscall *call)
{
    struct qemu_PropertySheet *c = (struct qemu_PropertySheet *)call;
    struct propsheet_data *data;
    unsigned int i, page_count;
    PROPSHEETHEADERW copy, *header_in = &copy;
    size_t offset;

    /* FIXME: My god is this ugly and complicated. Is there some easier way? */
    WINE_TRACE("\n");

    if (!c->lppsh)
    {
        if (c->super.id == QEMU_SYSCALL_ID(CALL_PROPERTYSHEETA))
            c->super.iret = PropertySheetA(NULL);
        else
            c->super.iret = PropertySheetW(NULL);
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
    data->ref = 1;

    /* Does the top level callback (PFNPROPSHEETCALLBACK) allow us to pass a custom pointer somewhere?
     * Why do you ask, of course it doesn't... */
    offset = offsetof(struct propsheet_data, selfptr) - offsetof(struct propsheet_data, ldrx3);
    data->ldrx3 = 0x58000003 | (offset << 3); /* ldr x3, offset */
    offset = offsetof(struct propsheet_data, host_proc) - offsetof(struct propsheet_data, ldrx4);
    data->ldrx4 = 0x58000004 | (offset << 3);   /* ldr x4, offset */
    data->br = 0xd61f0080; /* br x4 */

    data->selfptr = data;
    data->host_proc = propsheet_header_host_cb;
    __clear_cache(&data->ldrx3, &data->br + 1);

    /* FIXME: What about phpage? How does it choose between the two? */

    if (data->header.dwFlags & PSH_PROPSHEETPAGE)
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

            if (data->pages[i].pfnDlgProc)
                data->pages[i].pfnDlgProc = (DLGPROC)wndproc_guest_to_host((ULONG_PTR)data->pages[i].pfnDlgProc);

            if (data->pages[i].pfnCallback && (data->pages[i].dwFlags & PSP_USECALLBACK))
                WINE_FIXME("Handle property sheet page callbacks.\n");

            data->page_data[i].guest_lparam = data->pages[i].lParam;
            data->page_data[i].guest_cb = (ULONG_PTR)data->pages[i].pfnCallback;
            data->pages[i].lParam = (LPARAM)&data->page_data[i];
        }
        data->header.ppsp = data->pages;
        data->pages[0].dwFlags |= PSP_USECALLBACK;
        data->pages[0].pfnCallback = propsheet_host_cb;
        data->page_data[0].header = data;
    }
    else
    {
        /* The main magic for this would be in the CreatePropertySheetPage wrapper. It should
         * set up the propery sheets with the right callbacks. This function here would have
         * to set page_data.header and addref the header. */
        WINE_FIXME("Property page handles not handled yet.\n");
    }

    if ((data->header.dwFlags & PSH_USECALLBACK) && data->header.pfnCallback)
    {
        data->guest_cb = (ULONG_PTR)data->header.pfnCallback;
        data->guest_wrapper = c->wrapper;
        data->header.pfnCallback = (PFNPROPSHEETCALLBACK)data;
    }

    if (c->super.id == QEMU_SYSCALL_ID(CALL_PROPERTYSHEETA))
        c->super.iret = PropertySheetA((PROPSHEETHEADERA *)&data->header);
    else
        c->super.iret = PropertySheetW(&data->header);

    if (data->header.dwFlags & PSH_PROPSHEETPAGE)
    {
        /* Release our own reference. */
        propsheet_host_cb(NULL, PSPCB_RELEASE, &data->pages[0]);
    }
}

#endif

struct qemu_CreatePropertySheetPageA
{
    struct qemu_syscall super;
    uint64_t lpPropSheetPage;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HPROPSHEETPAGE WINAPI CreatePropertySheetPageA(LPCPROPSHEETPAGEA lpPropSheetPage)
{
    struct qemu_CreatePropertySheetPageA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPROPERTYSHEETPAGEA);
    call.lpPropSheetPage = (ULONG_PTR)lpPropSheetPage;

    qemu_syscall(&call.super);

    return (HPROPSHEETPAGE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreatePropertySheetPageA(struct qemu_syscall *call)
{
    struct qemu_CreatePropertySheetPageA *c = (struct qemu_CreatePropertySheetPageA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreatePropertySheetPageA(QEMU_G2H(c->lpPropSheetPage));
}

#endif

struct qemu_CreatePropertySheetPageW
{
    struct qemu_syscall super;
    uint64_t lpPropSheetPage;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HPROPSHEETPAGE WINAPI CreatePropertySheetPageW(LPCPROPSHEETPAGEW lpPropSheetPage)
{
    struct qemu_CreatePropertySheetPageW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEPROPERTYSHEETPAGEW);
    call.lpPropSheetPage = (ULONG_PTR)lpPropSheetPage;

    qemu_syscall(&call.super);

    return (HPROPSHEETPAGE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreatePropertySheetPageW(struct qemu_syscall *call)
{
    struct qemu_CreatePropertySheetPageW *c = (struct qemu_CreatePropertySheetPageW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)CreatePropertySheetPageW(QEMU_G2H(c->lpPropSheetPage));
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
    WINE_FIXME("Unverified!\n");
    c->super.iret = DestroyPropertySheetPage(QEMU_G2H(c->hPropPage));
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
            break;
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

