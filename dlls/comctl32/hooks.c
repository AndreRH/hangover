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
#include <commctrl.h>

#include "thunk/qemu_windows.h"
#include "thunk/qemu_commctrl.h"

#include "user32_wrapper.h"
#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_comctl32.h"

#ifndef QEMU_DLL_GUEST

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comctl32);

#if HOST_BIT == GUEST_BIT

void hook_wndprocs()
{
    /* Do nothing */
}

void register_notify_callbacks(void)
{
    /* Do nothing */
}

#else

static WNDPROC orig_rebar_wndproc;

static LRESULT WINAPI rebar_wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT ret;
    REBARINFO rbi_host;
    REBARBANDINFOW band_host;

    struct qemu_REBARINFO *rbi_guest;
    struct qemu_REBARBANDINFO *band_guest;

    WINE_TRACE("Message %x\n", msg);

    switch (msg)
    {
        case RB_SETBARINFO:
            rbi_guest = (struct qemu_REBARINFO *)lParam;
            if (rbi_guest->cbSize == sizeof(REBARINFO))
                WINE_ERR("Got a guest message with host size. Called from a Wine DLL?.\n");

            REBARINFO_g2h(&rbi_host, rbi_guest);
            lParam = (LPARAM)&rbi_host;
            break;

        case RB_INSERTBANDA:
        case RB_INSERTBANDW:
            band_guest = (struct qemu_REBARBANDINFO *)lParam;
            if (band_guest)
            {
                if (band_guest->cbSize == sizeof(REBARBANDINFOW))
                    WINE_ERR("Got a guest message with host size. Called from a Wine DLL?.\n");

                REBARBANDINFO_g2h(&band_host, band_guest);
                lParam = (LPARAM)&band_host;
            }
            break;
    }

    ret = CallWindowProcW(orig_rebar_wndproc, hWnd, msg, wParam, lParam);

    return ret;
}

static void nmmouse_notify(MSG *guest, MSG *host, BOOL ret)
{
    NMHDR *hdr = (NMHDR *)host->lParam;
    struct qemu_NMMOUSE *nmmouse;

    if (ret)
    {
        nmmouse = (struct qemu_NMMOUSE *)guest->lParam;
        NMMOUSE_g2h((NMMOUSE *)hdr, nmmouse);
    }
    else
    {
        nmmouse = HeapAlloc(GetProcessHeap(), 0, sizeof(*nmmouse));
        NMMOUSE_h2g(nmmouse, (NMMOUSE *)hdr);
        guest->lParam = (LPARAM)nmmouse;
    }
}

static void rebar_notify(MSG *guest, MSG *host, BOOL ret)
{
    NMHDR *hdr = (NMHDR *)host->lParam;
    struct qemu_NMREBARCHILDSIZE *childsize;
    struct qemu_NMHDR *guest_hdr;
    struct qemu_NMRBAUTOSIZE *autosize;
    struct qemu_NMCUSTOMDRAW *customdraw;
    struct qemu_NMREBAR *rebar;

    WINE_TRACE("Handling a rebar notify message\n");
    if (ret)
    {
        switch (hdr->code)
        {
            case NM_CUSTOMDRAW:
                customdraw = (struct qemu_NMCUSTOMDRAW *)guest->lParam;
                NMCUSTOMDRAW_g2h((NMCUSTOMDRAW *)hdr, customdraw);
                break;

            case RBN_CHILDSIZE:
                childsize = (struct qemu_NMREBARCHILDSIZE *)guest->lParam;
                NMREBARCHILDSIZE_g2h((NMREBARCHILDSIZE *)hdr, childsize);
                break;

            case RBN_AUTOSIZE:
                autosize = (struct qemu_NMRBAUTOSIZE *)guest->lParam;
                NMRBAUTOSIZE_g2h((NMRBAUTOSIZE *)hdr, autosize);
                break;

            case RBN_DELETEDBAND:
            case RBN_DELETINGBAND:
                rebar = (struct qemu_NMREBAR *)guest->lParam;
                NMREBAR_g2h((NMREBAR *)hdr, rebar);
                break;

            case NM_NCHITTEST:
                nmmouse_notify(guest, host, ret);
                break;
        }

        if (guest->lParam != host->lParam)
            HeapFree(GetProcessHeap(), 0, (void *)guest->lParam);
        return;
    }

    switch (hdr->code)
    {
        case NM_CUSTOMDRAW:
            WINE_TRACE("Handling notify message NM_CUSTOMDRAW.\n");
            customdraw = HeapAlloc(GetProcessHeap(), 0, sizeof(*customdraw));
            NMCUSTOMDRAW_h2g(customdraw, (NMCUSTOMDRAW *)hdr);
            guest->lParam = (LPARAM)customdraw;
            break;

        case NM_NCHITTEST:
            WINE_TRACE("Handling notify message NM_NCHITTEST.\n");
            nmmouse_notify(guest, host, ret);
            break;

        case RBN_CHILDSIZE:
            WINE_TRACE("Handling notify message RBN_CHILDSIZE.\n");
            childsize = HeapAlloc(GetProcessHeap(), 0, sizeof(*childsize));
            NMREBARCHILDSIZE_h2g(childsize, (NMREBARCHILDSIZE *)hdr);
            guest->lParam = (LPARAM)childsize;
            break;

        case RBN_HEIGHTCHANGE:
            WINE_TRACE("Handling notify message RBN_HEIGHTCHANGE.\n");
            guest_hdr = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest_hdr));
            NMHDR_h2g(guest_hdr, hdr);
            guest->lParam = (LPARAM)guest_hdr;
            break;

        case RBN_AUTOSIZE:
            WINE_TRACE("Handling notify message RBN_AUTOSIZE.\n");
            autosize = HeapAlloc(GetProcessHeap(), 0, sizeof(*autosize));
            NMRBAUTOSIZE_h2g(autosize, (NMRBAUTOSIZE *)hdr);
            guest->lParam = (LPARAM)autosize;
            break;

        case RBN_DELETEDBAND:
        case RBN_DELETINGBAND:
            WINE_TRACE("Handling notify message RBN_DELETINGBAND.\n");
            rebar = HeapAlloc(GetProcessHeap(), 0, sizeof(*rebar));
            NMREBAR_h2g(rebar, (NMREBAR *)hdr);
            guest->lParam = (LPARAM)rebar;
            break;

        case RBN_CHEVRONPUSHED:
            WINE_FIXME("Unhandled notify message RBN_CHEVRONPUSHED.\n");
            break;

        case RBN_LAYOUTCHANGED:
            WINE_FIXME("Unhandled notify message RBN_LAYOUTCHANGED.\n");
            break;

        case RBN_BEGINDRAG:
            WINE_FIXME("Unhandled notify message RBN_BEGINDRAG.\n");
            break;

        case RBN_ENDDRAG:
            WINE_FIXME("Unhandled notify message RBN_ENDDRAG.\n");
            break;

        default:
            WINE_ERR("Unexpected notify message %x.\n", hdr->code);
    }
}

static void toolbar_notify(MSG *guest, MSG *host, BOOL ret)
{
    NMHDR *hdr = (NMHDR *)host->lParam;
    struct qemu_NMTBCUSTOMDRAW *customdraw;
    struct qemu_NMTOOLTIPSCREATED *tooltip;
    struct qemu_NMTBGETINFOTIP *infotip;
    struct qemu_NMTBHOTITEM *hotitem;
    struct qemu_NMTOOLBAR *toolbar;
    struct qemu_NMHDR *guest_hdr;
    struct qemu_NMKEY *key;
    struct qemu_NMTBSAVE *save;
    struct qemu_NMTBRESTORE *restore;
    struct qemu_NMTBDISPINFO *disp;

    WINE_TRACE("Handling a toolbar notify message\n");
    if (ret)
    {
        switch (hdr->code)
        {
            case NM_CUSTOMDRAW:
                customdraw = (struct qemu_NMTBCUSTOMDRAW *)guest->lParam;
                NMTBCUSTOMDRAW_g2h((NMTBCUSTOMDRAW *)hdr, customdraw);
                break;

            case NM_TOOLTIPSCREATED:
                tooltip = (struct qemu_NMTOOLTIPSCREATED *)guest->lParam;
                NMTOOLTIPSCREATED_g2h((NMTOOLTIPSCREATED *)hdr, tooltip);
                break;

            case NM_CLICK:
            case NM_RCLICK:
            case NM_LDOWN:
            case NM_RDOWN:
            case NM_RDBLCLK:
                nmmouse_notify(guest, host, ret);
                break;

            case NM_KEYDOWN:
                key = (struct qemu_NMKEY *)guest->lParam;
                NMKEY_g2h((NMKEY *)hdr, key);
                break;

            case NM_RELEASEDCAPTURE:
            case TBN_BEGINADJUST:
            case TBN_ENDADJUST:
                guest_hdr = (struct qemu_NMHDR *)guest->lParam;
                NMHDR_g2h(hdr, guest_hdr);
                break;

            case TBN_GETINFOTIPA:
                infotip = (struct qemu_NMTBGETINFOTIP *)guest->lParam;
                NMTBGETINFOTIP_g2h((NMTBGETINFOTIPW *)hdr, infotip);
                memcpy(((NMTBGETINFOTIPA *)hdr)->pszText, (void *)(ULONG_PTR)infotip->pszText,
                        infotip->cchTextMax);
                HeapFree(GetProcessHeap(), 0, (void *)(ULONG_PTR)infotip->pszText);
                break;

            case TBN_GETINFOTIPW:
                infotip = (struct qemu_NMTBGETINFOTIP *)guest->lParam;
                NMTBGETINFOTIP_g2h((NMTBGETINFOTIPW *)hdr, infotip);
                memcpy(((NMTBGETINFOTIPW *)hdr)->pszText, (void *)(ULONG_PTR)infotip->pszText,
                        infotip->cchTextMax * sizeof(WCHAR));
                HeapFree(GetProcessHeap(), 0, (void *)(ULONG_PTR)infotip->pszText);
                break;

            case TBN_HOTITEMCHANGE:
                hotitem = (struct qemu_NMTBHOTITEM *)guest->lParam;
                NMTBHOTITEM_g2h((NMTBHOTITEM *)hdr, hotitem);
                break;

            case TBN_SAVE:
                save = (struct qemu_NMTBSAVE *)guest->lParam;
                NMTBSAVE_g2h((NMTBSAVE *)hdr, save);
                break;

            case TBN_RESTORE:
                restore = (struct qemu_NMTBRESTORE *)guest->lParam;
                NMTBRESTORE_g2h((NMTBRESTORE *)hdr, restore);
                break;

            case TBN_GETDISPINFOA:
            case TBN_GETDISPINFOW:
                disp = (struct qemu_NMTBDISPINFO *)guest->lParam;
                NMTBDISPINFO_g2h((NMTBDISPINFOW *)hdr, disp);
                break;

            case TBN_ENDDRAG:
            case TBN_BEGINDRAG:
            case TBN_DROPDOWN:
            case TBN_DRAGOUT:
            case TBN_DELETINGBUTTON:
            case TBN_GETBUTTONINFOA:
            case TBN_GETBUTTONINFOW:
                toolbar = (struct qemu_NMTOOLBAR *)guest->lParam;
                NMTOOLBAR_g2h((NMTOOLBARW *)hdr, toolbar);
                break;
        }

        if (guest->lParam != host->lParam)
            HeapFree(GetProcessHeap(), 0, (void *)guest->lParam);
        WINE_TRACE("Free done\n");
        return;
    }

    switch (hdr->code)
    {
        case NM_CUSTOMDRAW:
            WINE_TRACE("Handling notify message NM_CUSTOMDRAW.\n");
            customdraw = HeapAlloc(GetProcessHeap(), 0, sizeof(*customdraw));
            NMTBCUSTOMDRAW_h2g(customdraw, (NMTBCUSTOMDRAW *)hdr);
            guest->lParam = (LPARAM)customdraw;
            break;

        case NM_TOOLTIPSCREATED:
            WINE_TRACE("Handling notify message NM_TOOLTIPSCREATED.\n");
            tooltip = HeapAlloc(GetProcessHeap(), 0, sizeof(*tooltip));
            NMTOOLTIPSCREATED_h2g(tooltip, (NMTOOLTIPSCREATED *)hdr);
            guest->lParam = (LPARAM)tooltip;
            break;

        case NM_CLICK:
        case NM_RCLICK:
        case NM_LDOWN:
        case NM_RDOWN:
            case NM_RDBLCLK:
            WINE_TRACE("Handling notify message NM_[R][DOWN/CLICK/DBLCLICK].\n");
            nmmouse_notify(guest, host, ret);
            break;

        case NM_KEYDOWN:
            WINE_TRACE("Handling notify message NM_KEYDOWN.\n");
            key = HeapAlloc(GetProcessHeap(), 0, sizeof(*key));
            NMKEY_h2g(key, (NMKEY *)hdr);
            guest->lParam = (LPARAM)key;
            break;

        case TBN_BEGINADJUST:
        case TBN_ENDADJUST:
        case NM_RELEASEDCAPTURE:
            WINE_TRACE("Handling notify message %d.\n", hdr->code);
            guest_hdr = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest_hdr));
            NMHDR_h2g(guest_hdr, hdr);
            guest->lParam = (LPARAM)guest_hdr;
            break;

        case TBN_GETDISPINFOA:
        case TBN_GETDISPINFOW:
            WINE_TRACE("Handling notify message TBN_GETDISPINFO.\n");
            disp = HeapAlloc(GetProcessHeap(), 0, sizeof(*disp));
            NMTBDISPINFO_h2g(disp, (NMTBDISPINFOW *)hdr);
            guest->lParam = (LPARAM)disp;
            break;

        case TBN_TOOLBARCHANGE:
            WINE_FIXME("Unhandled notify message TBN_TOOLBARCHANGE.\n");
            break;

        case TBN_QUERYINSERT:
            WINE_FIXME("Unhandled notify message TBN_QUERYINSERT.\n");
            break;

        case TBN_QUERYDELETE:
            WINE_FIXME("Unhandled notify message TBN_QUERYDELETE.\n");
            break;

        case TBN_INITCUSTOMIZE:
            WINE_FIXME("Unhandled notify message TBN_INITCUSTOMIZE.\n");
            break;

        case TBN_CUSTHELP:
            WINE_FIXME("Unhandled notify message TBN_CUSTHELP.\n");
            break;

        case TBN_RESET:
            WINE_FIXME("Unhandled notify message TBN_RESET.\n");
            break;

        case TBN_SAVE:
            WINE_TRACE("Handling notify message TBN_SAVE.\n");
            save = HeapAlloc(GetProcessHeap(), 0, sizeof(*save));
            NMTBSAVE_h2g(save, (NMTBSAVE *)hdr);
            guest->lParam = (LPARAM)save;
            break;

        case TBN_RESTORE:
            WINE_TRACE("Handling notify message TBN_RESTORE.\n");
            restore = HeapAlloc(GetProcessHeap(), 0, sizeof(*restore));
            NMTBRESTORE_h2g(restore, (NMTBRESTORE *)hdr);
            guest->lParam = (LPARAM)restore;
            break;

        case TBN_HOTITEMCHANGE:
            WINE_TRACE("Handling notify message TBN_HOTITEMCHANGE.\n");
            hotitem = HeapAlloc(GetProcessHeap(), 0, sizeof(*hotitem));
            NMTBHOTITEM_h2g(hotitem, (NMTBHOTITEM *)hdr);
            guest->lParam = (LPARAM)hotitem;
            break;

        case TBN_WRAPHOTITEM:
            WINE_FIXME("Unhandled notify message TBN_WRAPHOTITEM.\n");
            break;

        case TBN_ENDDRAG:
        case TBN_BEGINDRAG:
        case TBN_DROPDOWN:
        case TBN_DRAGOUT:
        case TBN_DELETINGBUTTON:
        case TBN_GETBUTTONINFOA:
        case TBN_GETBUTTONINFOW:
            WINE_TRACE("Handling notify message %d.\n", hdr->code);
            toolbar = HeapAlloc(GetProcessHeap(), 0, sizeof(*toolbar));
            NMTOOLBAR_h2g(toolbar, (NMTOOLBARW *)hdr);
            guest->lParam = (LPARAM)toolbar;
            break;

        case TBN_GETOBJECT:
            WINE_FIXME("Unhandled notify message TBN_GETOBJECT.\n");
            break;

        case TBN_DUPACCELERATOR:
            WINE_FIXME("Unhandled notify message TBN_DUPACCELERATOR.\n");
            break;

        case TBN_WRAPACCELERATOR:
            WINE_FIXME("Unhandled notify message TBN_WRAPACCELERATOR.\n");
            break;

        case TBN_DRAGOVER:
            WINE_FIXME("Unhandled notify message TBN_DRAGOVER.\n");
            break;

        case TBN_MAPACCELERATOR:
            WINE_FIXME("Unhandled notify message TBN_MAPACCELERATOR.\n");
            break;

        case TBN_GETINFOTIPA:
        case TBN_GETINFOTIPW:
            WINE_TRACE("Handling notify message TBN_GETINFOTIP.\n");
            infotip = HeapAlloc(GetProcessHeap(), 0, sizeof(*infotip));
            NMTBGETINFOTIP_h2g(infotip, (NMTBGETINFOTIPW *)hdr);
            infotip->pszText = (DWORD_PTR)HeapAlloc(GetProcessHeap(),
                    HEAP_ZERO_MEMORY, infotip->cchTextMax * sizeof(WCHAR));
            guest->lParam = (LPARAM)infotip;
            break;

        default:
            WINE_ERR("Unexpected notify message %x.\n", hdr->code);
    }
}

static void combobox_notify(MSG *guest, MSG *host, BOOL ret)
{
    NMHDR *hdr = (NMHDR *)host->lParam;
    struct qemu_NMCBEENDEDITW *editw;
    struct qemu_NMCBEENDEDITA *edita;
    struct qemu_NMHDR *guest_hdr;
    struct qemu_NMCOMBOBOXEX *insertmsg;

    WINE_TRACE("Handling a toolbar notify message\n");
    if (ret)
    {
        switch (hdr->code)
        {
            case NM_SETCURSOR:
                nmmouse_notify(guest, host, ret);
                break;

            case CBEN_ENDEDITA:
                edita = (struct qemu_NMCBEENDEDITA *)guest->lParam;
                NMCBEENDEDITA_g2h((NMCBEENDEDITA *)hdr, edita);
                break;

            case CBEN_ENDEDITW:
                editw = (struct qemu_NMCBEENDEDITW *)guest->lParam;
                NMCBEENDEDITW_g2h((NMCBEENDEDITW *)hdr, editw);
                break;

            case CBEN_INSERTITEM:
                insertmsg = (struct qemu_NMCOMBOBOXEX *)guest->lParam;
                NMCOMBOBOXEX_g2h((NMCOMBOBOXEXW *)hdr, insertmsg);
                break;
        }

        if (guest->lParam != host->lParam)
            HeapFree(GetProcessHeap(), 0, (void *)guest->lParam);
        return;
    }

    switch (hdr->code)
    {
        case CBEN_BEGINEDIT:
            WINE_TRACE("Handling notify message CBEN_BEGINEDIT.\n");
            guest_hdr = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest_hdr));
            NMHDR_h2g(guest_hdr, hdr);
            guest->lParam = (LPARAM)guest_hdr;
            break;

        case CBEN_ENDEDITA:
            WINE_TRACE("Handling notify message CBEN_ENDEDITA.\n");
            edita = HeapAlloc(GetProcessHeap(), 0, sizeof(*edita));
            NMCBEENDEDITA_h2g(edita, (NMCBEENDEDITA *)hdr);
            guest->lParam = (LPARAM)edita;
            break;

        case CBEN_ENDEDITW:
            WINE_TRACE("Handling notify message CBEN_ENDEDITW.\n");
            editw = HeapAlloc(GetProcessHeap(), 0, sizeof(*editw));
            NMCBEENDEDITW_h2g(editw, (NMCBEENDEDITW *)hdr);
            guest->lParam = (LPARAM)editw;
            break;

        case CBEN_DRAGBEGINA:
            WINE_FIXME("Unhandled notify message CBEN_DRAGBEGINA.\n");
            break;

        case CBEN_DRAGBEGINW:
            WINE_FIXME("Unhandled notify message CBEN_DRAGBEGINW.\n");
            break;

        case CBEN_GETDISPINFOA:
            WINE_FIXME("Unhandled notify message CBEN_GETDISPINFOA.\n");
            break;

        case CBEN_GETDISPINFOW:
            WINE_FIXME("Unhandled notify message CBEN_GETDISPINFOW.\n");
            break;

        case CBEN_INSERTITEM:
            WINE_TRACE("Handling notify message CBEN_INSERTITEM.\n");
            insertmsg = HeapAlloc(GetProcessHeap(), 0, sizeof(*insertmsg));
            NMCOMBOBOXEX_h2g(insertmsg, (NMCOMBOBOXEXW *)hdr);
            guest->lParam = (LPARAM)insertmsg;
            break;

        case CBEN_DELETEITEM:
            WINE_FIXME("Unhandled notify message CBEN_DELETEITEM.\n");
            break;

        case NM_SETCURSOR:
            WINE_TRACE("Handling notify message NM_SETCURSOR.\n");
            nmmouse_notify(guest, host, ret);
            break;

        default:
            WINE_ERR("Unexpected notify message %x.\n", hdr->code);
    }
}

static void tooltips_notify(MSG *guest, MSG *host, BOOL ret)
{
    NMHDR *hdr = (NMHDR *)host->lParam;
    struct qemu_NMTTDISPINFOW *dispinfow;
    struct qemu_NMTTDISPINFOA *dispinfoa;
    struct qemu_NMTTCUSTOMDRAW *customdraw;

    WINE_TRACE("Handling a tooltip notify message\n");
    if (ret)
    {
        switch (hdr->code)
        {
            case TTN_GETDISPINFOA:
                dispinfoa = (struct qemu_NMTTDISPINFOA *)guest->lParam;
                NMTTDISPINFOA_g2h((NMTTDISPINFOA *)hdr, dispinfoa);
                break;

            case TTN_GETDISPINFOW:
                dispinfow = (struct qemu_NMTTDISPINFOW *)guest->lParam;
                NMTTDISPINFOW_g2h((NMTTDISPINFOW *)hdr, dispinfow);
                break;

            case NM_CUSTOMDRAW:
                customdraw = (struct qemu_NMTTCUSTOMDRAW *)guest->lParam;
                NMTTCUSTOMDRAW_g2h((NMTTCUSTOMDRAW *)hdr, customdraw);
                break;
        }

        if (guest->lParam != host->lParam)
            HeapFree(GetProcessHeap(), 0, (void *)guest->lParam);
        return;
    }

    switch (hdr->code)
    {
        case TTN_GETDISPINFOA:
            WINE_TRACE("Handling notify message TTN_GETDISPINFOA.\n");
            dispinfoa = HeapAlloc(GetProcessHeap(), 0, sizeof(*dispinfoa));
            NMTTDISPINFOA_h2g(dispinfoa, (NMTTDISPINFOA *)hdr);
            guest->lParam = (LPARAM)dispinfoa;
            break;

        case TTN_GETDISPINFOW:
            WINE_TRACE("Handling notify message TTN_GETDISPINFOW.\n");
            dispinfow = HeapAlloc(GetProcessHeap(), 0, sizeof(*dispinfow));
            NMTTDISPINFOW_h2g(dispinfow, (NMTTDISPINFOW *)hdr);
            guest->lParam = (LPARAM)dispinfow;
            break;

        case TTN_SHOW:
            WINE_FIXME("Unhandled notify message TTN_SHOW.\n");
            break;

        case TTN_POP:
            WINE_FIXME("Unhandled notify message TTN_POP.\n");
            break;

        case NM_CUSTOMDRAW:
            WINE_TRACE("Handling notify message NM_CUSTOMDRAW.\n");
            customdraw = HeapAlloc(GetProcessHeap(), 0, sizeof(*customdraw));
            NMTTCUSTOMDRAW_h2g(customdraw, (NMTTCUSTOMDRAW *)hdr);
            guest->lParam = (LPARAM)customdraw;
            break;

        default:
            WINE_ERR("Unexpected notify message %x.\n", hdr->code);
    }
}

static void status_notify(MSG *guest, MSG *host, BOOL ret)
{
    NMHDR *hdr = (NMHDR *)host->lParam;

    WINE_TRACE("Handling a status notify message\n");
    if (ret)
    {
        switch (hdr->code)
        {
            case NM_CLICK:
            case NM_DBLCLK:
            case NM_RDBLCLK:
            case NM_RCLICK:
                nmmouse_notify(guest, host, ret);
                break;
        }

        if (guest->lParam != host->lParam)
            HeapFree(GetProcessHeap(), 0, (void *)guest->lParam);
        return;
    }

    switch (hdr->code)
    {
        case NM_CLICK:
        case NM_DBLCLK:
        case NM_RDBLCLK:
        case NM_RCLICK:
            WINE_TRACE("Handing NMMOUSE notify message %x.\n", hdr->code);
            nmmouse_notify(guest, host, ret);
            break;

        case SBN_SIMPLEMODECHANGE:
            WINE_FIXME("Unhandled notify message SBN_SIMPLEMODECHANGE.\n");
            break;

        default:
            WINE_ERR("Unexpected notify message %x.\n", hdr->code);
    }
}

static void tabcontrol_notify(MSG *guest, MSG *host, BOOL ret)
{
    NMHDR *hdr = (NMHDR *)host->lParam;
    struct qemu_NMTCKEYDOWN *keydown;
    struct qemu_NMTOOLTIPSCREATED *tooltip;
    struct qemu_NMHDR *guest_hdr;

    WINE_TRACE("Handling a tab control notify message\n");
    if (ret)
    {
        if (guest->lParam != host->lParam)
            HeapFree(GetProcessHeap(), 0, (void *)guest->lParam);
        return;
    }

    switch (hdr->code)
    {
        case NM_TOOLTIPSCREATED:
            WINE_TRACE("Handling notify message NM_TOOLTIPSCREATED.\n");
            tooltip = HeapAlloc(GetProcessHeap(), 0, sizeof(*tooltip));
            NMTOOLTIPSCREATED_h2g(tooltip, (NMTOOLTIPSCREATED *)hdr);
            guest->lParam = (LPARAM)tooltip;
            break;

        case TCN_KEYDOWN:
            WINE_TRACE("Handling notify message TCN_KEYDOWN.\n");
            keydown = HeapAlloc(GetProcessHeap(), 0, sizeof(*keydown));
            NMTCKEYDOWN_h2g(keydown, (NMTCKEYDOWN *)hdr);
            guest->lParam = (LPARAM)keydown;
            break;

        case NM_CLICK:
        case NM_RCLICK:
        case TCN_SELCHANGE:
        case TCN_SELCHANGING:
        case TCN_FOCUSCHANGE:
            WINE_TRACE("Handling notify message %x.\n", hdr->code);
            guest_hdr = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest_hdr));
            NMHDR_h2g(guest_hdr, hdr);
            guest->lParam = (LPARAM)guest_hdr;
            break;

        case TCN_GETOBJECT:
            WINE_FIXME("Unhandled notify message %x.\n", hdr->code);
            break;

        default:
            WINE_ERR("Unexpected notify message from %p id %lx code %x.\n", hdr->hwndFrom, hdr->idFrom, hdr->code);
    }
}

static void listview_notify(MSG *guest, MSG *host, BOOL ret)
{
    NMHDR *hdr = (NMHDR *)host->lParam;
    struct qemu_NMLISTVIEW *nm_listview;
    struct qemu_NMHDR *guest_hdr;
    struct qemu_NMLVCUSTOMDRAW *customdraw;
    struct qemu_NMLVKEYDOWN *keydown;
    struct qemu_NMLVDISPINFO *dispinfo;

    WINE_TRACE("Handling a listview notify message\n");
    if (ret)
    {
        switch (hdr->code)
        {
            case NM_CLICK:
            case NM_DBLCLK:
            case NM_RDBLCLK:
            case NM_RCLICK:
                nmmouse_notify(guest, host, ret);
                break;

            case LVN_ITEMACTIVATE:
            case NM_RETURN:
            case NM_KILLFOCUS:
            case NM_RELEASEDCAPTURE:
            case NM_SETFOCUS:
            case NM_HOVER:
                guest_hdr = (struct qemu_NMHDR *)guest->lParam;
                NMHDR_g2h(hdr, guest_hdr);
                break;

            case NM_CUSTOMDRAW:
                customdraw = (struct qemu_NMLVCUSTOMDRAW *)guest->lParam;
                NMLVCUSTOMDRAW_g2h((NMLVCUSTOMDRAW *)hdr, customdraw);
                break;
        }

        if (guest->lParam != host->lParam)
            HeapFree(GetProcessHeap(), 0, (void *)guest->lParam);
        return;
    }

    switch (hdr->code)
    {
        case LVN_DELETEITEM:
        case LVN_BEGINDRAG:
        case LVN_ITEMCHANGING:
        case LVN_ITEMCHANGED:
        case LVN_DELETEALLITEMS:
        case LVN_INSERTITEM:
        case LVN_COLUMNCLICK:
        case LVN_BEGINRDRAG:
            WINE_TRACE("Handling NMLISTVIEW notify message %d.\n", hdr->code);
            nm_listview = HeapAlloc(GetProcessHeap(), 0, sizeof(*nm_listview));
            NMLISTVIEW_h2g(nm_listview, (NMLISTVIEW *)hdr);
            guest->lParam = (LPARAM)nm_listview;
            break;

        case LVN_ODCACHEHINT:
            WINE_FIXME("Unhandled listview notify message LVN_ODCACHEHINT.\n");
            break;
        case LVN_ODSTATECHANGED:
            WINE_FIXME("Unhandled listview notify message LVN_ODSTATECHANGED.\n");
            break;
        case LVN_HOTTRACK:
            WINE_FIXME("Unhandled listview notify message LVN_HOTTRACK.\n");
            break;
        case LVN_ODFINDITEMA:
            WINE_FIXME("Unhandled listview notify message LVN_ODFINDITEMA.\n");
            break;
        case LVN_ODFINDITEMW:
            WINE_FIXME("Unhandled listview notify message LVN_ODFINDITEMW.\n");
            break;
        case LVN_SETDISPINFOA:
            WINE_FIXME("Unhandled listview notify message LVN_SETDISPINFOA.\n");
            break;
        case LVN_SETDISPINFOW:
            WINE_FIXME("Unhandled listview notify message LVN_SETDISPINFOW.\n");
            break;

        case LVN_KEYDOWN:
            WINE_TRACE("Handling LVN_KEYDOWN notify message %d.\n", hdr->code);
            keydown = HeapAlloc(GetProcessHeap(), 0, sizeof(*keydown));
            NMLVKEYDOWN_h2g(keydown, (NMLVKEYDOWN *)hdr);
            guest->lParam = (LPARAM)keydown;
            break;

        case LVN_MARQUEEBEGIN:
            WINE_FIXME("Unhandled listview notify message LVN_MARQUEEBEGIN.\n");
            break;
        case LVN_GETINFOTIPA:
            WINE_FIXME("Unhandled listview notify message LVN_GETINFOTIPA.\n");
            break;
        case LVN_GETINFOTIPW:
            WINE_FIXME("Unhandled listview notify message LVN_GETINFOTIPW.\n");
            break;
        case LVN_INCREMENTALSEARCHA:
            WINE_FIXME("Unhandled listview notify message LVN_INCREMENTALSEARCHA.\n");
            break;
        case LVN_INCREMENTALSEARCHW:
            WINE_FIXME("Unhandled listview notify message LVN_INCREMENTALSEARCHW.\n");
            break;
        case LVN_COLUMNDROPDOWN:
            WINE_FIXME("Unhandled listview notify message LVN_COLUMNDROPDOWN.\n");
            break;
        case LVN_COLUMNOVERFLOWCLICK:
            WINE_FIXME("Unhandled listview notify message LVN_COLUMNOVERFLOWCLICK.\n");
            break;
        case LVN_BEGINSCROLL:
            WINE_FIXME("Unhandled listview notify message LVN_BEGINSCROLL.\n");
            break;
        case LVN_ENDSCROLL:
            WINE_FIXME("Unhandled listview notify message LVN_ENDSCROLL.\n");
            break;
        case LVN_LINKCLICK:
            WINE_FIXME("Unhandled listview notify message LVN_LINKCLICK.\n");
            break;
        case LVN_ASYNCDRAWN:
            WINE_FIXME("Unhandled listview notify message LVN_ASYNCDRAWN.\n");
            break;
        case LVN_GETEMPTYMARKUP:
            WINE_FIXME("Unhandled listview notify message LVN_GETEMPTYMARKUP.\n");
            break;

        case NM_CLICK:
        case NM_DBLCLK:
        case NM_RDBLCLK:
        case NM_RCLICK:
            WINE_TRACE("Handing NMMOUSE notify message %x.\n", hdr->code);
            nmmouse_notify(guest, host, ret);
            break;

        case NM_CUSTOMDRAW:
            WINE_TRACE("Handling notify message NM_CUSTOMDRAW.\n");
            customdraw = HeapAlloc(GetProcessHeap(), 0, sizeof(*customdraw));
            NMLVCUSTOMDRAW_h2g(customdraw, (NMLVCUSTOMDRAW *)hdr);
            guest->lParam = (LPARAM)customdraw;
            break;

        case LVN_ITEMACTIVATE:
        case NM_RETURN:
        case NM_KILLFOCUS:
        case NM_RELEASEDCAPTURE:
        case NM_SETFOCUS:
        case NM_HOVER:
            WINE_TRACE("Handling notify message %d.\n", hdr->code);
            guest_hdr = HeapAlloc(GetProcessHeap(), 0, sizeof(*guest_hdr));
            NMHDR_h2g(guest_hdr, hdr);
            guest->lParam = (LPARAM)guest_hdr;
            break;

        case LVN_GETDISPINFOA:
        case LVN_GETDISPINFOW:
        case LVN_BEGINLABELEDITA:
        case LVN_BEGINLABELEDITW:
        case LVN_ENDLABELEDITA:
        case LVN_ENDLABELEDITW:
            WINE_TRACE("Handling dispinfo message %d.\n", hdr->code);
            dispinfo = HeapAlloc(GetProcessHeap(), 0, sizeof(*dispinfo));
            NMLVDISPINFO_h2g(dispinfo, (NMLVDISPINFOW *)hdr);
            guest->lParam = (LPARAM)dispinfo;
            break;

        default:
            WINE_ERR("Unexpected notify message from %p id %lx code %x.\n", hdr->hwndFrom, hdr->idFrom, hdr->code);
    }
}

static WNDPROC hook_class(const WCHAR *name, WNDPROC replace)
{
    WNDPROC ret;
    HMODULE comctl32 = GetModuleHandleA("comctl32");
    HWND win, label;

    /* May need a parent to respond to various messages, e.g. WM_NOTIFYFORMAT. */
    label = CreateWindowExW(0, WC_STATICW, NULL,
            WS_POPUP, 0, 0, 200, 60, NULL, NULL, comctl32, NULL);
    win = CreateWindowExW(0, name, NULL,
            WS_POPUP, 0, 0, 200, 60, label, NULL, comctl32, NULL);
    if (!win)
        WINE_ERR("Failed to instantiate a %s window.\n", wine_dbgstr_w(name));

    ret = (WNDPROC)SetClassLongPtrW(win, GCLP_WNDPROC, (ULONG_PTR)replace);
    if (!ret)
        WINE_ERR("Failed to set WNDPROC of %s.\n", wine_dbgstr_w(name));

    DestroyWindow(win);
    DestroyWindow(label);

    return ret;
}

void hook_wndprocs(void)
{
    /* Intercepting messages before they enter the control has the advantage that we
     * don't have to bother the user32 mapper with comctl32 internals and that we don't
     * have to inspect the window class on every WM_USER + x message. The disadvantage
     * is that the hook wndproc will also run when the message is received from another
     * Wine DLL, in which case translation will break things. */

    orig_rebar_wndproc = hook_class(REBARCLASSNAMEW, rebar_wndproc);
    /* Toolbars: Used by Wine's comdlg32, and internal messages from comctl32. */
}

void register_notify_callbacks(void)
{
    QEMU_USER32_NOTIFY_FUNC register_notify;
    HMODULE qemu_user32 = GetModuleHandleA("qemu_user32");

    if (!qemu_user32)
        WINE_ERR("Cannot get qemu_user32.dll\n");
    register_notify = (void *)GetProcAddress(qemu_user32, "qemu_user32_notify");
    if (!register_notify)
        WINE_ERR("Cannot get qemu_user32_notify\n");

    register_notify(REBARCLASSNAMEW, rebar_notify);
    register_notify(TOOLBARCLASSNAMEW, toolbar_notify);
    register_notify(WC_COMBOBOXEXW, combobox_notify);
    register_notify(TOOLTIPS_CLASSW, tooltips_notify);
    register_notify(STATUSCLASSNAMEW, status_notify);
    register_notify(WC_TABCONTROLW, tabcontrol_notify);
    register_notify(WC_LISTVIEWW, listview_notify);
}

#endif

#endif
