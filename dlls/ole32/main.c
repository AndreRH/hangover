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

#include "windows-user-services.h"
#include "dll_list.h"
#include "ole32.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_ole32);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_CLSIDFromProgID,
    qemu_CLSIDFromProgIDEx,
    qemu_CLSIDFromString,
    qemu_CoAddRefServerProcess,
    qemu_CoAllowSetForegroundWindow,
    qemu_CoBuildVersion,
    qemu_CoCopyProxy,
    qemu_CoCreateGuid,
    qemu_CoCreateInstance,
    qemu_CoCreateInstanceEx,
    qemu_CoDisconnectObject,
    qemu_CoFileTimeNow,
    qemu_CoFreeAllLibraries,
    qemu_CoFreeLibrary,
    qemu_CoFreeUnusedLibraries,
    qemu_CoFreeUnusedLibrariesEx,
    qemu_CoGetApartmentType,
    qemu_CoGetCallContext,
    qemu_CoGetClassObject,
    qemu_CoGetContextToken,
    qemu_CoGetCurrentLogicalThreadId,
    qemu_CoGetCurrentProcess,
    qemu_CoGetDefaultContext,
    qemu_CoGetInstanceFromFile,
    qemu_CoGetInstanceFromIStorage,
    qemu_CoGetObject,
    qemu_CoGetObjectContext,
    qemu_CoGetPSClsid,
    qemu_CoGetState,
    qemu_CoGetTreatAsClass,
    qemu_CoImpersonateClient,
    qemu_CoInitialize,
    qemu_CoInitializeEx,
    qemu_CoInitializeSecurity,
    qemu_CoInitializeWOW,
    qemu_CoIsHandlerConnected,
    qemu_CoIsOle1Class,
    qemu_CoLoadLibrary,
    qemu_CoLockObjectExternal,
    qemu_CoQueryClientBlanket,
    qemu_CoQueryProxyBlanket,
    qemu_CoRegisterChannelHook,
    qemu_CoRegisterClassObject,
    qemu_CoRegisterInitializeSpy,
    qemu_CoRegisterMessageFilter,
    qemu_CoRegisterPSClsid,
    qemu_CoRegisterSurrogate,
    qemu_CoRegisterSurrogateEx,
    qemu_CoReleaseServerProcess,
    qemu_CoResumeClassObjects,
    qemu_CoRevertToSelf,
    qemu_CoRevokeClassObject,
    qemu_CoRevokeInitializeSpy,
    qemu_CoSetProxyBlanket,
    qemu_CoSetState,
    qemu_CoSuspendClassObjects,
    qemu_CoSwitchCallContext,
    qemu_CoTreatAsClass,
    qemu_CoUninitialize,
    qemu_CoWaitForMultipleHandles,
    qemu_IIDFromString,
    qemu_IsEqualGUID,
    qemu_ProgIDFromCLSID,
    qemu_StringFromCLSID,
    qemu_StringFromGUID2,
};

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    WINE_TRACE("Loading host-side ole32 wrapper.\n");

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    return dll_functions;
}

#endif
