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

#include <windows.h>
#include <stdio.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_comdlg32.h"

struct qemu_dll_init
{
    struct qemu_syscall super;
    uint64_t reason;
};

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMainCRTStartup(HMODULE mod, DWORD reason, void *reserved)
{
    struct qemu_dll_init call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLL_INIT);
    call.reason = reason;
    qemu_syscall(&call.super);
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_comdlg32);

const struct qemu_ops *qemu_ops;
static HMODULE comdlg32;

static void qemu_dll_init(struct qemu_syscall *call)
{
    struct qemu_dll_init *c = (struct qemu_dll_init *)call;

    switch (c->reason)
    {
        case DLL_PROCESS_ATTACH:
            /* The reason for runtime-loading comdlg32.dll is that comdlg32.dll links to
             * comctl32, which we have to runtime-load to register classes with the correct
             * name as required by the import manifest in the activation context. */

            WINE_TRACE("Loading comdlg32.dll.\n");
            comdlg32 = GetModuleHandleA("comdlg32");
            if (comdlg32)
                WINE_ERR("comdlg32.dll is already loaded.\n");

            comdlg32 = LoadLibraryA("comdlg32");
            if (!comdlg32)
                WINE_ERR("Failed to load comdlg32.dll.\n");

            p_DllGetClassObject = (void *)GetProcAddress(comdlg32, "DllGetClassObject");
            if (!p_DllGetClassObject)
                WINE_ERR("Cannot find DllGetClassObject\n");

            p_DllRegisterServer = (void *)GetProcAddress(comdlg32, "DllRegisterServer");
            if (!p_DllRegisterServer)
                WINE_ERR("Cannot find DllRegisterServer\n");

            p_DllUnregisterServer = (void *)GetProcAddress(comdlg32, "DllUnregisterServer");
            if (!p_DllUnregisterServer)
                WINE_ERR("Cannot find DllUnregisterServer\n");

            p_CommDlgExtendedError = (void *)GetProcAddress(comdlg32, "CommDlgExtendedError");
            if (!p_CommDlgExtendedError)
                WINE_ERR("Could not load CommDlgExtendedError from comdlg32.dll.\n");

            p_DllGetClassObject = (void *)GetProcAddress(comdlg32, "DllGetClassObject");
            if (!p_DllGetClassObject)
                WINE_ERR("Could not load DllGetClassObject from comdlg32.dll.\n");

            p_DllRegisterServer = (void *)GetProcAddress(comdlg32, "DllRegisterServer");
            if (!p_DllRegisterServer)
                WINE_ERR("Could not load DllRegisterServer from comdlg32.dll.\n");

            p_DllUnregisterServer = (void *)GetProcAddress(comdlg32, "DllUnregisterServer");
            if (!p_DllUnregisterServer)
                WINE_ERR("Could not load DllUnregisterServer from comdlg32.dll.\n");

            p_GetOpenFileNameA = (void *)GetProcAddress(comdlg32, "GetOpenFileNameA");
            if (!p_GetOpenFileNameA)
                WINE_ERR("Could not load GetOpenFileNameA from comdlg32.dll.\n");

            p_GetOpenFileNameW = (void *)GetProcAddress(comdlg32, "GetOpenFileNameW");
            if (!p_GetOpenFileNameW)
                WINE_ERR("Could not load GetOpenFileNameW from comdlg32.dll.\n");

            p_GetSaveFileNameA = (void *)GetProcAddress(comdlg32, "GetSaveFileNameA");
            if (!p_GetSaveFileNameA)
                WINE_ERR("Could not load GetSaveFileNameA from comdlg32.dll.\n");

            p_GetSaveFileNameW = (void *)GetProcAddress(comdlg32, "GetSaveFileNameW");
            if (!p_GetSaveFileNameW)
                WINE_ERR("Could not load GetSaveFileNameW from comdlg32.dll.\n");

            p_GetFileTitleA = (void *)GetProcAddress(comdlg32, "GetFileTitleA");
            if (!p_GetFileTitleA)
                WINE_ERR("Could not load GetFileTitleA from comdlg32.dll.\n");

            p_GetFileTitleW = (void *)GetProcAddress(comdlg32, "GetFileTitleW");
            if (!p_GetFileTitleW)
                WINE_ERR("Could not load GetFileTitleW from comdlg32.dll.\n");

            p_ChooseColorW = (void *)GetProcAddress(comdlg32, "ChooseColorW");
            if (!p_ChooseColorW)
                WINE_ERR("Could not load ChooseColorW from comdlg32.dll.\n");

            p_ChooseColorA = (void *)GetProcAddress(comdlg32, "ChooseColorA");
            if (!p_ChooseColorA)
                WINE_ERR("Could not load ChooseColorA from comdlg32.dll.\n");

            p_FindTextA = (void *)GetProcAddress(comdlg32, "FindTextA");
            if (!p_FindTextA)
                WINE_ERR("Could not load FindTextA from comdlg32.dll.\n");

            p_ReplaceTextA = (void *)GetProcAddress(comdlg32, "ReplaceTextA");
            if (!p_ReplaceTextA)
                WINE_ERR("Could not load ReplaceTextA from comdlg32.dll.\n");

            p_FindTextW = (void *)GetProcAddress(comdlg32, "FindTextW");
            if (!p_FindTextW)
                WINE_ERR("Could not load FindTextW from comdlg32.dll.\n");

            p_ReplaceTextW = (void *)GetProcAddress(comdlg32, "ReplaceTextW");
            if (!p_ReplaceTextW)
                WINE_ERR("Could not load ReplaceTextW from comdlg32.dll.\n");

            p_ChooseFontW = (void *)GetProcAddress(comdlg32, "ChooseFontW");
            if (!p_ChooseFontW)
                WINE_ERR("Could not load ChooseFontW from comdlg32.dll.\n");

            p_ChooseFontA = (void *)GetProcAddress(comdlg32, "ChooseFontA");
            if (!p_ChooseFontA)
                WINE_ERR("Could not load ChooseFontA from comdlg32.dll.\n");

            p_PrintDlgA = (void *)GetProcAddress(comdlg32, "PrintDlgA");
            if (!p_PrintDlgA)
                WINE_ERR("Could not load PrintDlgA from comdlg32.dll.\n");

            p_PrintDlgW = (void *)GetProcAddress(comdlg32, "PrintDlgW");
            if (!p_PrintDlgW)
                WINE_ERR("Could not load PrintDlgW from comdlg32.dll.\n");

            p_PageSetupDlgA = (void *)GetProcAddress(comdlg32, "PageSetupDlgA");
            if (!p_PageSetupDlgA)
                WINE_ERR("Could not load PageSetupDlgA from comdlg32.dll.\n");

            p_PageSetupDlgW = (void *)GetProcAddress(comdlg32, "PageSetupDlgW");
            if (!p_PageSetupDlgW)
                WINE_ERR("Could not load PageSetupDlgW from comdlg32.dll.\n");

            p_PrintDlgExA = (void *)GetProcAddress(comdlg32, "PrintDlgExA");
            if (!p_PrintDlgExA)
                WINE_ERR("Could not load PrintDlgExA from comdlg32.dll.\n");

            p_PrintDlgExW = (void *)GetProcAddress(comdlg32, "PrintDlgExW");
            if (!p_PrintDlgExW)
                WINE_ERR("Could not load PrintDlgExW from comdlg32.dll.\n");

            break;

        case DLL_PROCESS_DETACH:
            WINE_TRACE("Unloading comdlg32.dll.\n");
            FreeLibrary(comdlg32);
            break;
    }
}

static const syscall_handler dll_functions[] =
{
    qemu_ChooseColorA,
    qemu_ChooseColorW,
    qemu_ChooseFontA,
    qemu_ChooseFontW,
    qemu_CommDlgExtendedError,
    qemu_dll_init,
    qemu_DllGetClassObject,
    qemu_DllRegisterServer,
    qemu_DllUnregisterServer,
    qemu_FindTextA,
    qemu_FindTextW,
    qemu_GetFileTitleA,
    qemu_GetFileTitleW,
    qemu_GetOpenSaveFileName,
    qemu_GetOpenSaveFileName,
    qemu_GetOpenSaveFileName,
    qemu_GetOpenSaveFileName,
    qemu_PageSetupDlgA,
    qemu_PageSetupDlgW,
    qemu_PrintDlgA,
    qemu_PrintDlgExA,
    qemu_PrintDlgExW,
    qemu_PrintDlgW,
    qemu_ReplaceTextA,
    qemu_ReplaceTextW,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side comdlg32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    comdlg32_tls = TlsAlloc();
    if (comdlg32_tls == TLS_OUT_OF_INDEXES)
        WINE_ERR("Out of TLS indices\n");

    return dll_functions;
}

#endif
