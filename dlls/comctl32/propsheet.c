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

#include "windows-user-services.h"
#include "dll_list.h"
#include "comctl32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comctl32);
#endif


struct qemu_PropertySheetA
{
    struct qemu_syscall super;
    uint64_t lppsh;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT_PTR WINAPI PropertySheetA(LPCPROPSHEETHEADERA lppsh)
{
    struct qemu_PropertySheetA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PROPERTYSHEETA);
    call.lppsh = (uint64_t)lppsh;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PropertySheetA(struct qemu_syscall *call)
{
    struct qemu_PropertySheetA *c = (struct qemu_PropertySheetA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PropertySheetA(QEMU_G2H(c->lppsh));
}

#endif

struct qemu_PropertySheetW
{
    struct qemu_syscall super;
    uint64_t lppsh;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI INT_PTR WINAPI PropertySheetW(LPCPROPSHEETHEADERW lppsh)
{
    struct qemu_PropertySheetW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_PROPERTYSHEETW);
    call.lppsh = (uint64_t)lppsh;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_PropertySheetW(struct qemu_syscall *call)
{
    struct qemu_PropertySheetW *c = (struct qemu_PropertySheetW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = PropertySheetW(QEMU_G2H(c->lppsh));
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
    call.lpPropSheetPage = (uint64_t)lpPropSheetPage;

    qemu_syscall(&call.super);

    return (HPROPSHEETPAGE)call.super.iret;
}

#else

void qemu_CreatePropertySheetPageA(struct qemu_syscall *call)
{
    struct qemu_CreatePropertySheetPageA *c = (struct qemu_CreatePropertySheetPageA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreatePropertySheetPageA(QEMU_G2H(c->lpPropSheetPage));
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
    call.lpPropSheetPage = (uint64_t)lpPropSheetPage;

    qemu_syscall(&call.super);

    return (HPROPSHEETPAGE)call.super.iret;
}

#else

void qemu_CreatePropertySheetPageW(struct qemu_syscall *call)
{
    struct qemu_CreatePropertySheetPageW *c = (struct qemu_CreatePropertySheetPageW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreatePropertySheetPageW(QEMU_G2H(c->lpPropSheetPage));
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
    call.hPropPage = (uint64_t)hPropPage;

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

