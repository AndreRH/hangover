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
#include <d3d9.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_d3d9.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_d3d9);
#endif

struct qemu_DebugSetMute
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI DebugSetMute(void)
{
    struct qemu_DebugSetMute call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEBUGSETMUTE);

    qemu_syscall(&call.super);
}

#else

extern void WINAPI DebugSetMute(void);
void qemu_DebugSetMute(struct qemu_syscall *call)
{
    struct qemu_DebugSetMute *c = (struct qemu_DebugSetMute *)call;
    WINE_TRACE("\n");
    DebugSetMute();
}

#endif

struct qemu_Direct3DCreate9
{
    struct qemu_syscall super;
    uint64_t sdk_version;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI IDirect3D9 * WINAPI Direct3DCreate9(UINT sdk_version)
{
    struct qemu_Direct3DCreate9 call;
    struct qemu_d3d9_impl *d3d9;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECT3DCREATE9);
    call.sdk_version = (uint64_t)sdk_version;

    qemu_syscall(&call.super);

    d3d9 = (struct qemu_d3d9_impl *)call.super.iret;
    if (!d3d9)
        return NULL;

    d3d9->IDirect3D9Ex_iface.lpVtbl = &d3d9_vtbl;
    return (IDirect3D9 *)&d3d9->IDirect3D9Ex_iface;
}

#else

void qemu_Direct3DCreate9(struct qemu_syscall *call)
{
    struct qemu_Direct3DCreate9 *c = (struct qemu_Direct3DCreate9 *)call;
    struct qemu_d3d9_impl *impl;
    WINE_TRACE("\n");

    impl = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*impl));
    if (!impl)
        goto error;

    impl->host = (IDirect3D9Ex *)Direct3DCreate9(c->sdk_version);
    if (!impl->host)
        goto error;

    c->super.iret = QEMU_H2G(impl);
    return;

error:
    HeapFree(GetProcessHeap(), 0, impl);
    c->super.iret = 0;
    return;
}

#endif

struct qemu_Direct3DCreate9Ex
{
    struct qemu_syscall super;
    uint64_t sdk_version;
    uint64_t d3d9ex;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI Direct3DCreate9Ex(UINT sdk_version, IDirect3D9Ex **d3d9ex)
{
    struct qemu_Direct3DCreate9Ex call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECT3DCREATE9EX);
    call.sdk_version = (uint64_t)sdk_version;
    call.d3d9ex = (uint64_t)d3d9ex;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_Direct3DCreate9Ex(struct qemu_syscall *call)
{
    struct qemu_Direct3DCreate9Ex *c = (struct qemu_Direct3DCreate9Ex *)call;
    IDirect3D9Ex *d3d9;
    WINE_FIXME("This aint gonna work!\n");
    c->super.iret = Direct3DCreate9Ex(c->sdk_version, &d3d9);
    *(uint64_t *)QEMU_G2H(c->d3d9ex) = QEMU_H2G(d3d9);
}

#endif

struct qemu_Direct3DShaderValidatorCreate9
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void* WINAPI Direct3DShaderValidatorCreate9(void)
{
    struct qemu_Direct3DShaderValidatorCreate9 call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECT3DSHADERVALIDATORCREATE9);

    qemu_syscall(&call.super);

    return (void *)call.super.iret;
}

#else

extern void* WINAPI Direct3DShaderValidatorCreate9(void);
void qemu_Direct3DShaderValidatorCreate9(struct qemu_syscall *call)
{
    struct qemu_Direct3DShaderValidatorCreate9 *c = (struct qemu_Direct3DShaderValidatorCreate9 *)call;
    WINE_TRACE("\n");
    c->super.iret = QEMU_H2G(Direct3DShaderValidatorCreate9());
    if (c->super.iret)
        WINE_FIXME("Handle a non-NULL result\n");
}

#endif

struct qemu_D3DPERF_BeginEvent
{
    struct qemu_syscall super;
    uint64_t color;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI D3DPERF_BeginEvent(D3DCOLOR color, const WCHAR *name)
{
    struct qemu_D3DPERF_BeginEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DPERF_BEGINEVENT);
    call.color = (uint64_t)color;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_D3DPERF_BeginEvent(struct qemu_syscall *call)
{
    struct qemu_D3DPERF_BeginEvent *c = (struct qemu_D3DPERF_BeginEvent *)call;
    WINE_TRACE("\n");
    c->super.iret = D3DPERF_BeginEvent(c->color, QEMU_G2H(c->name));
}

#endif

struct qemu_D3DPERF_EndEvent
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI int WINAPI D3DPERF_EndEvent(void)
{
    struct qemu_D3DPERF_EndEvent call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DPERF_ENDEVENT);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_D3DPERF_EndEvent(struct qemu_syscall *call)
{
    struct qemu_D3DPERF_EndEvent *c = (struct qemu_D3DPERF_EndEvent *)call;
    WINE_TRACE("\n");
    c->super.iret = D3DPERF_EndEvent();
}

#endif

struct qemu_D3DPERF_GetStatus
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI D3DPERF_GetStatus(void)
{
    struct qemu_D3DPERF_GetStatus call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DPERF_GETSTATUS);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_D3DPERF_GetStatus(struct qemu_syscall *call)
{
    struct qemu_D3DPERF_GetStatus *c = (struct qemu_D3DPERF_GetStatus *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = D3DPERF_GetStatus();
}

#endif

struct qemu_D3DPERF_SetOptions
{
    struct qemu_syscall super;
    uint64_t options;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI D3DPERF_SetOptions(DWORD options)
{
    struct qemu_D3DPERF_SetOptions call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DPERF_SETOPTIONS);
    call.options = (uint64_t)options;

    qemu_syscall(&call.super);
}

#else

void qemu_D3DPERF_SetOptions(struct qemu_syscall *call)
{
    struct qemu_D3DPERF_SetOptions *c = (struct qemu_D3DPERF_SetOptions *)call;
    WINE_FIXME("Unverified!\n");
    D3DPERF_SetOptions(c->options);
}

#endif

struct qemu_D3DPERF_QueryRepeatFrame
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI D3DPERF_QueryRepeatFrame(void)
{
    struct qemu_D3DPERF_QueryRepeatFrame call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DPERF_QUERYREPEATFRAME);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_D3DPERF_QueryRepeatFrame(struct qemu_syscall *call)
{
    struct qemu_D3DPERF_QueryRepeatFrame *c = (struct qemu_D3DPERF_QueryRepeatFrame *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = D3DPERF_QueryRepeatFrame();
}

#endif

struct qemu_D3DPERF_SetMarker
{
    struct qemu_syscall super;
    uint64_t color;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI D3DPERF_SetMarker(D3DCOLOR color, const WCHAR *name)
{
    struct qemu_D3DPERF_SetMarker call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DPERF_SETMARKER);
    call.color = (uint64_t)color;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);
}

#else

void qemu_D3DPERF_SetMarker(struct qemu_syscall *call)
{
    struct qemu_D3DPERF_SetMarker *c = (struct qemu_D3DPERF_SetMarker *)call;
    WINE_FIXME("Unverified!\n");
    D3DPERF_SetMarker(c->color, QEMU_G2H(c->name));
}

#endif

struct qemu_D3DPERF_SetRegion
{
    struct qemu_syscall super;
    uint64_t color;
    uint64_t name;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI D3DPERF_SetRegion(D3DCOLOR color, const WCHAR *name)
{
    struct qemu_D3DPERF_SetRegion call;
    call.super.id = QEMU_SYSCALL_ID(CALL_D3DPERF_SETREGION);
    call.color = (uint64_t)color;
    call.name = (uint64_t)name;

    qemu_syscall(&call.super);
}

#else

void qemu_D3DPERF_SetRegion(struct qemu_syscall *call)
{
    struct qemu_D3DPERF_SetRegion *c = (struct qemu_D3DPERF_SetRegion *)call;
    WINE_FIXME("Unverified!\n");
    D3DPERF_SetRegion(c->color, QEMU_G2H(c->name));
}

#endif

