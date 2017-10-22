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

#else

static WNDPROC orig_rebar_wndproc;

static LRESULT WINAPI rebar_wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT ret;
    REBARINFO rbi_host;
    struct qemu_REBARINFO *rbi_guest;

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
    }

    ret = CallWindowProcW(orig_rebar_wndproc, hWnd, msg, wParam, lParam);

    return ret;
}

static WNDPROC hook_class(const WCHAR *name, WNDPROC replace)
{
    WNDPROC ret;
    HMODULE comctl32 = GetModuleHandleA("comctl32");
    HWND win;

    win = CreateWindowExW(0, name, NULL,
            WS_POPUP, 0, 0, 200, 60, NULL, NULL, comctl32, NULL);
    if (!win)
        WINE_ERR("Failed to instantiate a %s window.\n", wine_dbgstr_w(name));

    ret = (WNDPROC)SetClassLongPtrW(win, GCLP_WNDPROC, (ULONG_PTR)replace);
    if (!ret)
        WINE_ERR("Failed to set WNDPROC of %s.\n", wine_dbgstr_w(name));

    DestroyWindow(win);

    return ret;
}

void hook_wndprocs()
{
    orig_rebar_wndproc = hook_class(REBARCLASSNAMEW, rebar_wndproc);
}

#endif

#endif
