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
#include <xinput.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_xinput1_3.h"

#ifdef QEMU_DLL_GUEST

BOOL WINAPI DllMain(HMODULE mod, DWORD reason, void *reserved)
{
    return TRUE;
}

#else

#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_xinput);

const struct qemu_ops *qemu_ops;

static const syscall_handler dll_functions[] =
{
    qemu_XInputEnable,
    qemu_XInputGetBatteryInformation,
    qemu_XInputGetCapabilities,
    qemu_XInputGetDSoundAudioDeviceGuids,
    qemu_XInputGetKeystroke,
    qemu_XInputGetState,
    qemu_XInputGetStateEx,
    qemu_XInputSetState,
};

void (WINAPI *pXInputEnable)(BOOL enable);
DWORD (WINAPI *pXInputSetState)(DWORD index, XINPUT_VIBRATION* vibration);
DWORD (WINAPI *pXInputGetState)(DWORD index, XINPUT_STATE* state);
DWORD (WINAPI *pXInputGetStateEx)(DWORD index, void* state_ex);
DWORD (WINAPI *pXInputGetKeystroke)(DWORD index, DWORD reserved, PXINPUT_KEYSTROKE keystroke);
DWORD (WINAPI *pXInputGetCapabilities)(DWORD index, DWORD flags, XINPUT_CAPABILITIES* capabilities);
DWORD (WINAPI *pXInputGetDSoundAudioDeviceGuids)(DWORD index, GUID* render_guid, GUID* capture_guid);
DWORD (WINAPI *pXInputGetBatteryInformation)(DWORD index, BYTE type, XINPUT_BATTERY_INFORMATION* battery);

const WINAPI syscall_handler *qemu_dll_register(const struct qemu_ops *ops, uint32_t *dll_num)
{
    HMODULE xinput;

    WINE_TRACE("Loading host-side xinput wrapper.\n");

    xinput = LoadLibraryA("xinput1_3.dll");
    if (!xinput)
    {
        WINE_FIXME("Could not load xinput1_3.dll\n");
        return NULL;
    }

    qemu_ops = ops;
    *dll_num = QEMU_CURRENT_DLL;

    pXInputEnable = (void *)GetProcAddress(xinput, "XInputEnable");
    if (!pXInputEnable)
        WINE_ERR("Could not find XInputEnable in xinput.dll\n");

    pXInputSetState = (void *)GetProcAddress(xinput, "XInputSetState");
    if (!pXInputSetState)
        WINE_ERR("Could not find XInputSetState in xinput.dll\n");

    pXInputGetState = (void *)GetProcAddress(xinput, "XInputGetState");
    if (!pXInputGetState)
        WINE_ERR("Could not find XInputGetState in xinput.dll\n");

    pXInputGetStateEx = (void *)GetProcAddress(xinput, "XInputGetStateEx");
    if (!pXInputGetStateEx)
        WINE_ERR("Could not find XInputGetStateEx in xinput.dll\n");

    pXInputGetKeystroke = (void *)GetProcAddress(xinput, "XInputGetKeystroke");
    if (!pXInputGetKeystroke)
        WINE_ERR("Could not find XInputGetKeystroke in xinput.dll\n");

    pXInputGetCapabilities = (void *)GetProcAddress(xinput, "XInputGetCapabilities");
    if (!pXInputGetCapabilities)
        WINE_ERR("Could not find XInputGetCapabilities in xinput.dll\n");

    pXInputGetDSoundAudioDeviceGuids = (void *)GetProcAddress(xinput, "XInputGetDSoundAudioDeviceGuids");
    if (!pXInputGetDSoundAudioDeviceGuids)
        WINE_ERR("Could not find XInputGetDSoundAudioDeviceGuids in xinput.dll\n");

    pXInputGetBatteryInformation = (void *)GetProcAddress(xinput, "XInputGetBatteryInformation");
    if (!pXInputGetBatteryInformation)
        WINE_ERR("Could not find XInputGetBatteryInformation in xinput.dll\n");

    return dll_functions;
}

#endif
