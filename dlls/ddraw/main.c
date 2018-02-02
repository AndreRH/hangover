/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
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
#include <ddraw.h>
#include <d3d.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_ddraw.h"

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_ddraw);

struct qemu_GetSurfaceFromDC
{
    struct qemu_syscall super;
    uint64_t dc;
    uint64_t surface;
    uint64_t device_dc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI GetSurfaceFromDC(HDC dc, IDirectDrawSurface4 **surface, HDC *device_dc)
{
    struct qemu_GetSurfaceFromDC call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETSURFACEFROMDC);
    call.dc = (ULONG_PTR)dc;
    call.surface = (ULONG_PTR)surface;
    call.device_dc = (ULONG_PTR)device_dc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

/* This function is not in the PSDK headers or Wine's headers, but it is in the import library. */
extern HRESULT WINAPI GetSurfaceFromDC(HDC dc, struct IDirectDrawSurface **surface, HDC *device_dc);
static void qemu_GetSurfaceFromDC(struct qemu_syscall *call)
{
    struct qemu_GetSurfaceFromDC *c = (struct qemu_GetSurfaceFromDC *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetSurfaceFromDC(QEMU_G2H(c->dc), QEMU_G2H(c->surface), QEMU_G2H(c->device_dc));
}

#endif

struct qemu_DirectDrawCreate
{
    struct qemu_syscall super;
    uint64_t driver_guid;
    uint64_t ddraw;
    uint64_t outer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DirectDrawCreate(GUID *driver_guid, IDirectDraw **ddraw, IUnknown *outer)
{
    struct qemu_DirectDrawCreate call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTDRAWCREATE);
    call.driver_guid = (ULONG_PTR)driver_guid;
    call.ddraw = (ULONG_PTR)ddraw;
    call.outer = (ULONG_PTR)outer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_DirectDrawCreate(struct qemu_syscall *call)
{
    struct qemu_DirectDrawCreate *c = (struct qemu_DirectDrawCreate *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DirectDrawCreate(QEMU_G2H(c->driver_guid), QEMU_G2H(c->ddraw), QEMU_G2H(c->outer));
}

#endif

struct qemu_DirectDrawCreateEx
{
    struct qemu_syscall super;
    uint64_t driver_guid;
    uint64_t ddraw;
    uint64_t interface_iid;
    uint64_t outer;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DirectDrawCreateEx(GUID *driver_guid, void **ddraw, REFIID interface_iid, IUnknown *outer)
{
    struct qemu_DirectDrawCreateEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTDRAWCREATEEX);
    call.driver_guid = (ULONG_PTR)driver_guid;
    call.ddraw = (ULONG_PTR)ddraw;
    call.interface_iid = (ULONG_PTR)interface_iid;
    call.outer = (ULONG_PTR)outer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_DirectDrawCreateEx(struct qemu_syscall *call)
{
    struct qemu_DirectDrawCreateEx *c = (struct qemu_DirectDrawCreateEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DirectDrawCreateEx(QEMU_G2H(c->driver_guid), QEMU_G2H(c->ddraw), QEMU_G2H(c->interface_iid), QEMU_G2H(c->outer));
}

#endif

struct qemu_DirectDrawEnumerateA
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DirectDrawEnumerateA(LPDDENUMCALLBACKA callback, void *context)
{
    struct qemu_DirectDrawEnumerateA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTDRAWENUMERATEA);
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_DirectDrawEnumerateA(struct qemu_syscall *call)
{
    struct qemu_DirectDrawEnumerateA *c = (struct qemu_DirectDrawEnumerateA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DirectDrawEnumerateA(QEMU_G2H(c->callback), QEMU_G2H(c->context));
}

#endif

struct qemu_DirectDrawEnumerateExA
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t context;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DirectDrawEnumerateExA(LPDDENUMCALLBACKEXA callback, void *context, DWORD flags)
{
    struct qemu_DirectDrawEnumerateExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTDRAWENUMERATEEXA);
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_DirectDrawEnumerateExA(struct qemu_syscall *call)
{
    struct qemu_DirectDrawEnumerateExA *c = (struct qemu_DirectDrawEnumerateExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DirectDrawEnumerateExA(QEMU_G2H(c->callback), QEMU_G2H(c->context), c->flags);
}

#endif

struct qemu_DirectDrawEnumerateW
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t context;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DirectDrawEnumerateW(LPDDENUMCALLBACKW callback, void *context)
{
    struct qemu_DirectDrawEnumerateW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTDRAWENUMERATEW);
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_DirectDrawEnumerateW(struct qemu_syscall *call)
{
    struct qemu_DirectDrawEnumerateW *c = (struct qemu_DirectDrawEnumerateW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DirectDrawEnumerateW(QEMU_G2H(c->callback), QEMU_G2H(c->context));
}

#endif

struct qemu_DirectDrawEnumerateExW
{
    struct qemu_syscall super;
    uint64_t callback;
    uint64_t context;
    uint64_t flags;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DirectDrawEnumerateExW(LPDDENUMCALLBACKEXW callback, void *context, DWORD flags)
{
    struct qemu_DirectDrawEnumerateExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTDRAWENUMERATEEXW);
    call.callback = (ULONG_PTR)callback;
    call.context = (ULONG_PTR)context;
    call.flags = flags;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

static void qemu_DirectDrawEnumerateExW(struct qemu_syscall *call)
{
    struct qemu_DirectDrawEnumerateExW *c = (struct qemu_DirectDrawEnumerateExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DirectDrawEnumerateExW(QEMU_G2H(c->callback), QEMU_G2H(c->context), c->flags);
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **out)
{
    WINE_FIXME("Stub!\n");
    return E_FAIL;
}

WINBASEAPI HRESULT WINAPI DllCanUnloadNow(void)
{
    WINE_FIXME("Stub!\n");
    return FALSE;
}

WINBASEAPI HRESULT WINAPI DllRegisterServer(void)
{
    WINE_ERR("Not expected to be called on the wrapper DLL!\n");
    return E_FAIL;
}

WINBASEAPI HRESULT WINAPI DllUnregisterServer(void)
{
    WINE_ERR("Not expected to be called on the wrapper DLL!\n");
    return E_FAIL;
}

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_DirectDrawCreate,
    qemu_DirectDrawCreateEx,
    qemu_DirectDrawEnumerateA,
    qemu_DirectDrawEnumerateExA,
    qemu_DirectDrawEnumerateExW,
    qemu_DirectDrawEnumerateW,
    qemu_GetSurfaceFromDC,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side ddraw wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
