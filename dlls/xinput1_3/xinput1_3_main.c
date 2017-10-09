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
#include <xinput.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "xinput1_3.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_xinput1_3);
#endif


struct qemu_XInputEnable
{
    struct qemu_syscall super;
    uint64_t enable;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI XInputEnable(BOOL enable)
{
    struct qemu_XInputEnable call;
    call.super.id = QEMU_SYSCALL_ID(CALL_XINPUTENABLE);
    call.enable = enable;

    qemu_syscall(&call.super);
}

#else

void qemu_XInputEnable(struct qemu_syscall *call)
{
    struct qemu_XInputEnable *c = (struct qemu_XInputEnable *)call;
    WINE_TRACE("\n");
    XInputEnable(c->enable);
}

#endif

struct qemu_XInputSetState
{
    struct qemu_syscall super;
    uint64_t index;
    uint64_t vibration;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI XInputSetState(DWORD index, XINPUT_VIBRATION* vibration)
{
    struct qemu_XInputSetState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_XINPUTSETSTATE);
    call.index = (ULONG_PTR)index;
    call.vibration = (ULONG_PTR)vibration;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_XInputSetState(struct qemu_syscall *call)
{
    struct qemu_XInputSetState *c = (struct qemu_XInputSetState *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = XInputSetState(c->index, QEMU_G2H(c->vibration));
}

#endif

struct qemu_XInputGetState
{
    struct qemu_syscall super;
    uint64_t index;
    uint64_t state;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI XInputGetState(DWORD index, XINPUT_STATE* state)
{
    struct qemu_XInputGetState call;
    call.super.id = QEMU_SYSCALL_ID(CALL_XINPUTGETSTATE);
    call.index = index;
    call.state = (ULONG_PTR)state;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_XInputGetState(struct qemu_syscall *call)
{
    struct qemu_XInputGetState *c = (struct qemu_XInputGetState *)call;
    WINE_TRACE("\n");
    c->super.iret = XInputGetState(c->index, QEMU_G2H(c->state));
}

#endif

struct qemu_XInputGetStateEx
{
    struct qemu_syscall super;
    uint64_t index;
    uint64_t state_ex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI XInputGetStateEx(DWORD index, void* state_ex)
{
    struct qemu_XInputGetStateEx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_XINPUTGETSTATEEX);
    call.index = (ULONG_PTR)index;
    call.state_ex = (ULONG_PTR)state_ex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_XInputGetStateEx(struct qemu_syscall *call)
{
    struct qemu_XInputGetStateEx *c = (struct qemu_XInputGetStateEx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = XInputGetStateEx(c->index, QEMU_G2H(c->state_ex));
}

#endif

struct qemu_XInputGetKeystroke
{
    struct qemu_syscall super;
    uint64_t index;
    uint64_t reserved;
    uint64_t keystroke;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI XInputGetKeystroke(DWORD index, DWORD reserved, PXINPUT_KEYSTROKE keystroke)
{
    struct qemu_XInputGetKeystroke call;
    call.super.id = QEMU_SYSCALL_ID(CALL_XINPUTGETKEYSTROKE);
    call.index = (ULONG_PTR)index;
    call.reserved = (ULONG_PTR)reserved;
    call.keystroke = (ULONG_PTR)keystroke;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_XInputGetKeystroke(struct qemu_syscall *call)
{
    struct qemu_XInputGetKeystroke *c = (struct qemu_XInputGetKeystroke *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = XInputGetKeystroke(c->index, c->reserved, QEMU_G2H(c->keystroke));
}

#endif

struct qemu_XInputGetCapabilities
{
    struct qemu_syscall super;
    uint64_t index;
    uint64_t flags;
    uint64_t capabilities;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI XInputGetCapabilities(DWORD index, DWORD flags, XINPUT_CAPABILITIES* capabilities)
{
    struct qemu_XInputGetCapabilities call;
    call.super.id = QEMU_SYSCALL_ID(CALL_XINPUTGETCAPABILITIES);
    call.index = (ULONG_PTR)index;
    call.flags = (ULONG_PTR)flags;
    call.capabilities = (ULONG_PTR)capabilities;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_XInputGetCapabilities(struct qemu_syscall *call)
{
    struct qemu_XInputGetCapabilities *c = (struct qemu_XInputGetCapabilities *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = XInputGetCapabilities(c->index, c->flags, QEMU_G2H(c->capabilities));
}

#endif

struct qemu_XInputGetDSoundAudioDeviceGuids
{
    struct qemu_syscall super;
    uint64_t index;
    uint64_t render_guid;
    uint64_t capture_guid;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI XInputGetDSoundAudioDeviceGuids(DWORD index, GUID* render_guid, GUID* capture_guid)
{
    struct qemu_XInputGetDSoundAudioDeviceGuids call;
    call.super.id = QEMU_SYSCALL_ID(CALL_XINPUTGETDSOUNDAUDIODEVICEGUIDS);
    call.index = (ULONG_PTR)index;
    call.render_guid = (ULONG_PTR)render_guid;
    call.capture_guid = (ULONG_PTR)capture_guid;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_XInputGetDSoundAudioDeviceGuids(struct qemu_syscall *call)
{
    struct qemu_XInputGetDSoundAudioDeviceGuids *c = (struct qemu_XInputGetDSoundAudioDeviceGuids *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = XInputGetDSoundAudioDeviceGuids(c->index, QEMU_G2H(c->render_guid), QEMU_G2H(c->capture_guid));
}

#endif

struct qemu_XInputGetBatteryInformation
{
    struct qemu_syscall super;
    uint64_t index;
    uint64_t type;
    uint64_t battery;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI XInputGetBatteryInformation(DWORD index, BYTE type, XINPUT_BATTERY_INFORMATION* battery)
{
    struct qemu_XInputGetBatteryInformation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_XINPUTGETBATTERYINFORMATION);
    call.index = (ULONG_PTR)index;
    call.type = (ULONG_PTR)type;
    call.battery = (ULONG_PTR)battery;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_XInputGetBatteryInformation(struct qemu_syscall *call)
{
    struct qemu_XInputGetBatteryInformation *c = (struct qemu_XInputGetBatteryInformation *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = XInputGetBatteryInformation(c->index, c->type, QEMU_G2H(c->battery));
}

#endif

