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
    qemu_d3d1_CreateLight,
    qemu_d3d1_CreateMaterial,
    qemu_d3d1_CreateViewport,
    qemu_d3d1_EnumDevices,
    qemu_d3d1_FindDevice,
    qemu_d3d1_Initialize,
    qemu_d3d2_CreateDevice,
    qemu_d3d2_CreateLight,
    qemu_d3d2_CreateMaterial,
    qemu_d3d2_CreateViewport,
    qemu_d3d2_EnumDevices,
    qemu_d3d2_FindDevice,
    qemu_d3d3_CreateDevice,
    qemu_d3d3_CreateLight,
    qemu_d3d3_CreateMaterial,
    qemu_d3d3_CreateVertexBuffer,
    qemu_d3d3_CreateViewport,
    qemu_d3d3_EnumDevices,
    qemu_d3d3_EnumZBufferFormats,
    qemu_d3d3_EvictManagedTextures,
    qemu_d3d3_FindDevice,
    qemu_d3d7_CreateDevice,
    qemu_d3d7_CreateVertexBuffer,
    qemu_d3d7_EnumDevices,
    qemu_d3d7_EnumZBufferFormats,
    qemu_d3d7_EvictManagedTextures,
    qemu_ddraw1_Compact,
    qemu_ddraw1_CreateClipper,
    qemu_ddraw1_CreatePalette,
    qemu_ddraw1_CreateSurface,
    qemu_ddraw1_DuplicateSurface,
    qemu_ddraw1_EnumDisplayModes,
    qemu_ddraw1_EnumSurfaces,
    qemu_ddraw1_FlipToGDISurface,
    qemu_ddraw1_GetCaps,
    qemu_ddraw1_GetDisplayMode,
    qemu_ddraw1_GetFourCCCodes,
    qemu_ddraw1_GetGDISurface,
    qemu_ddraw1_GetMonitorFrequency,
    qemu_ddraw1_GetScanLine,
    qemu_ddraw1_GetVerticalBlankStatus,
    qemu_ddraw1_Initialize,
    qemu_ddraw_Release,
    qemu_ddraw1_RestoreDisplayMode,
    qemu_ddraw1_SetCooperativeLevel,
    qemu_ddraw1_SetDisplayMode,
    qemu_ddraw1_WaitForVerticalBlank,
    qemu_ddraw2_Compact,
    qemu_ddraw2_CreateClipper,
    qemu_ddraw2_CreatePalette,
    qemu_ddraw2_CreateSurface,
    qemu_ddraw2_DuplicateSurface,
    qemu_ddraw2_EnumDisplayModes,
    qemu_ddraw2_EnumSurfaces,
    qemu_ddraw2_FlipToGDISurface,
    qemu_ddraw2_GetAvailableVidMem,
    qemu_ddraw2_GetCaps,
    qemu_ddraw2_GetDisplayMode,
    qemu_ddraw2_GetFourCCCodes,
    qemu_ddraw2_GetGDISurface,
    qemu_ddraw2_GetMonitorFrequency,
    qemu_ddraw2_GetScanLine,
    qemu_ddraw2_GetVerticalBlankStatus,
    qemu_ddraw2_Initialize,
    qemu_ddraw2_RestoreDisplayMode,
    qemu_ddraw2_SetCooperativeLevel,
    qemu_ddraw2_SetDisplayMode,
    qemu_ddraw2_WaitForVerticalBlank,
    qemu_ddraw4_Compact,
    qemu_ddraw4_CreateClipper,
    qemu_ddraw4_CreatePalette,
    qemu_ddraw4_CreateSurface,
    qemu_ddraw4_DuplicateSurface,
    qemu_ddraw4_EnumDisplayModes,
    qemu_ddraw4_EnumSurfaces,
    qemu_ddraw4_FlipToGDISurface,
    qemu_ddraw4_GetAvailableVidMem,
    qemu_ddraw4_GetCaps,
    qemu_ddraw4_GetDeviceIdentifier,
    qemu_ddraw4_GetDisplayMode,
    qemu_ddraw4_GetFourCCCodes,
    qemu_ddraw4_GetGDISurface,
    qemu_ddraw4_GetMonitorFrequency,
    qemu_ddraw4_GetScanLine,
    qemu_ddraw4_GetSurfaceFromDC,
    qemu_ddraw4_GetVerticalBlankStatus,
    qemu_ddraw4_Initialize,
    qemu_ddraw4_RestoreAllSurfaces,
    qemu_ddraw4_RestoreDisplayMode,
    qemu_ddraw4_SetCooperativeLevel,
    qemu_ddraw4_SetDisplayMode,
    qemu_ddraw4_TestCooperativeLevel,
    qemu_ddraw4_WaitForVerticalBlank,
    qemu_ddraw7_Compact,
    qemu_ddraw7_CreateClipper,
    qemu_ddraw7_CreatePalette,
    qemu_ddraw7_CreateSurface,
    qemu_ddraw7_DuplicateSurface,
    qemu_ddraw7_EnumDisplayModes,
    qemu_ddraw7_EnumSurfaces,
    qemu_ddraw7_EvaluateMode,
    qemu_ddraw7_FlipToGDISurface,
    qemu_ddraw7_GetAvailableVidMem,
    qemu_ddraw7_GetCaps,
    qemu_ddraw7_GetDeviceIdentifier,
    qemu_ddraw7_GetDisplayMode,
    qemu_ddraw7_GetFourCCCodes,
    qemu_ddraw7_GetGDISurface,
    qemu_ddraw7_GetMonitorFrequency,
    qemu_ddraw7_GetScanLine,
    qemu_ddraw7_GetSurfaceFromDC,
    qemu_ddraw7_GetVerticalBlankStatus,
    qemu_ddraw7_Initialize,
    qemu_ddraw7_RestoreAllSurfaces,
    qemu_ddraw7_RestoreDisplayMode,
    qemu_ddraw7_SetCooperativeLevel,
    qemu_ddraw7_SetDisplayMode,
    qemu_ddraw7_StartModeTest,
    qemu_ddraw7_TestCooperativeLevel,
    qemu_ddraw7_WaitForVerticalBlank,
    qemu_ddraw_clipper_GetClipList,
    qemu_ddraw_clipper_GetHWnd,
    qemu_ddraw_clipper_Initialize,
    qemu_ddraw_clipper_IsClipListChanged,
    qemu_ddraw_clipper_Release,
    qemu_ddraw_clipper_SetClipList,
    qemu_ddraw_clipper_SetHWnd,
    qemu_DirectDrawCreate,
    qemu_DirectDrawCreateClipper,
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
