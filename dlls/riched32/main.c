/*
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
#include <shlwapi.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_riched32.h"

/* The purpose of this DLL is to load the host-side riched32.dll to make it register its
 * window class. Afterwards riched20 will take over.
 *
 * This library isn't linked to riched32.dll and loads it via LoadLibrary to delay
 * calling PROCESS_ATTACH in riched32.dll until a guest process actually uses the guest-
 * side riched32. */

struct qemu_init_dll
{
    struct qemu_syscall super;
    uint64_t reason;
    uint64_t dummy;
};

#ifdef QEMU_DLL_GUEST

HRESULT WINAPI DllGetVersion (DLLVERSIONINFO *pdvi)
{
    struct qemu_syscall call;

    call.id = QEMU_SYSCALL_ID(CALL_DLLGETVERSION);
    qemu_syscall(&call);

    if (pdvi->cbSize != sizeof(DLLVERSIONINFO))
        return E_INVALIDARG;

    pdvi->dwMajorVersion = 4;
    pdvi->dwMinorVersion = 0;
    pdvi->dwBuildNumber = 0;
    pdvi->dwPlatformID = 0;

    return S_OK;
}

extern LRESULT WINAPI RichEdit10ANSIWndProc(HWND, UINT, WPARAM, LPARAM);

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_init_dll call;

    /* Reference RichEdit10ANSIWndProc, otherwise the linker will remove the
     * seemingly redundant import of riched20.dll. We want to load this DLL
     * because the application might expect it and to make riched20 resolve
     * its guest-client callback linkage in DllMain. */
    call.super.id = QEMU_SYSCALL_ID(CALL_INIT_DLL);
    call.reason = reason;
    call.dummy = (ULONG_PTR)RichEdit10ANSIWndProc;

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_PROCESS_DETACH:
            qemu_syscall(&call.super);
            break;
    }

    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_riched32);

static void qemu_DllGetVersion(struct qemu_syscall *call)
{
    WINE_TRACE("\n");
}

static void qemu_init_dll(struct qemu_syscall *call)
{
    struct qemu_init_dll *c = (struct qemu_init_dll *)call;
    static HMODULE native;
    HMODULE riched20_wrapper;
    void (* WINAPI p_qemu_riched20_hook_old)(HMODULE riched32);

    switch (c->reason)
    {
        case DLL_PROCESS_ATTACH:
            WINE_TRACE("Loading host-side riched32.dll.\n");
            native = LoadLibraryA("riched32");
            if (!native)
                WINE_ERR("Failed to load riched32.dll.\n");

            riched20_wrapper = GetModuleHandleA("qemu_riched20");
            if (!riched20_wrapper)
                WINE_ERR("Failed to get qemu_riched20.dll handle.\n");
            p_qemu_riched20_hook_old = (void *)GetProcAddress(riched20_wrapper, "qemu_riched20_hook_old");
            if (!p_qemu_riched20_hook_old)
                WINE_ERR("Failed to get qemu_riched20_hook_old().\n");
            p_qemu_riched20_hook_old(native);
            break;

        case DLL_PROCESS_DETACH:
            WINE_TRACE("Unloading host-side riched32.dll %p.\n", native);
            FreeLibrary(native);
            native = NULL;
            break;
    }
}

static const syscall_handler dll_functions[] =
{
    qemu_DllGetVersion,
    qemu_init_dll,
};

const struct qemu_ops *qemu_ops;

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side riched32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
