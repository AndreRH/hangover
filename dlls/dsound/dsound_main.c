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
#include <dsound.h>
#include <dsconf.h>

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_dsound.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
#else
#include <debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dsound);

struct qemu_GetDeviceID
{
    struct qemu_syscall super;
    uint64_t pGuidSrc;
    uint64_t pGuidDest;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI GetDeviceID(LPCGUID pGuidSrc, LPGUID pGuidDest)
{
    struct qemu_GetDeviceID call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETDEVICEID);
    call.pGuidSrc = (ULONG_PTR)pGuidSrc;
    call.pGuidDest = (ULONG_PTR)pGuidDest;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetDeviceID(struct qemu_syscall *call)
{
    struct qemu_GetDeviceID *c = (struct qemu_GetDeviceID *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetDeviceID(QEMU_G2H(c->pGuidSrc), QEMU_G2H(c->pGuidDest));
}

#endif

struct qemu_DirectSoundEnumerateA
{
    struct qemu_syscall super;
    uint64_t lpDSEnumCallback;
    uint64_t lpContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DirectSoundEnumerateA(LPDSENUMCALLBACKA lpDSEnumCallback, LPVOID lpContext)
{
    struct qemu_DirectSoundEnumerateA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTSOUNDENUMERATEA);
    call.lpDSEnumCallback = (ULONG_PTR)lpDSEnumCallback;
    call.lpContext = (ULONG_PTR)lpContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DirectSoundEnumerateA(struct qemu_syscall *call)
{
    struct qemu_DirectSoundEnumerateA *c = (struct qemu_DirectSoundEnumerateA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DirectSoundEnumerateA(QEMU_G2H(c->lpDSEnumCallback), QEMU_G2H(c->lpContext));
}

#endif

struct qemu_DirectSoundEnumerateW
{
    struct qemu_syscall super;
    uint64_t lpDSEnumCallback;
    uint64_t lpContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DirectSoundEnumerateW(LPDSENUMCALLBACKW lpDSEnumCallback, LPVOID lpContext)
{
    struct qemu_DirectSoundEnumerateW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTSOUNDENUMERATEW);
    call.lpDSEnumCallback = (ULONG_PTR)lpDSEnumCallback;
    call.lpContext = (ULONG_PTR)lpContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DirectSoundEnumerateW(struct qemu_syscall *call)
{
    struct qemu_DirectSoundEnumerateW *c = (struct qemu_DirectSoundEnumerateW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DirectSoundEnumerateW(QEMU_G2H(c->lpDSEnumCallback), QEMU_G2H(c->lpContext));
}

#endif

struct qemu_DirectSoundCaptureEnumerateA
{
    struct qemu_syscall super;
    uint64_t lpDSEnumCallback;
    uint64_t lpContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DirectSoundCaptureEnumerateA(LPDSENUMCALLBACKA lpDSEnumCallback, LPVOID lpContext)
{
    struct qemu_DirectSoundCaptureEnumerateA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTSOUNDCAPTUREENUMERATEA);
    call.lpDSEnumCallback = (ULONG_PTR)lpDSEnumCallback;
    call.lpContext = (ULONG_PTR)lpContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DirectSoundCaptureEnumerateA(struct qemu_syscall *call)
{
    struct qemu_DirectSoundCaptureEnumerateA *c = (struct qemu_DirectSoundCaptureEnumerateA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DirectSoundCaptureEnumerateA(QEMU_G2H(c->lpDSEnumCallback), QEMU_G2H(c->lpContext));
}

#endif

struct qemu_DirectSoundCaptureEnumerateW
{
    struct qemu_syscall super;
    uint64_t lpDSEnumCallback;
    uint64_t lpContext;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DirectSoundCaptureEnumerateW(LPDSENUMCALLBACKW lpDSEnumCallback, LPVOID lpContext)
{
    struct qemu_DirectSoundCaptureEnumerateW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DIRECTSOUNDCAPTUREENUMERATEW);
    call.lpDSEnumCallback = (ULONG_PTR)lpDSEnumCallback;
    call.lpContext = (ULONG_PTR)lpContext;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DirectSoundCaptureEnumerateW(struct qemu_syscall *call)
{
    struct qemu_DirectSoundCaptureEnumerateW *c = (struct qemu_DirectSoundCaptureEnumerateW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DirectSoundCaptureEnumerateW(QEMU_G2H(c->lpDSEnumCallback), QEMU_G2H(c->lpContext));
}

#endif

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
    WINE_FIXME("Stub!\n");
    return E_FAIL;
}

#endif

struct qemu_DllCanUnloadNow
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllCanUnloadNow(void)
{
    struct qemu_DllCanUnloadNow call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLCANUNLOADNOW);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DllCanUnloadNow(struct qemu_syscall *call)
{
    struct qemu_DllCanUnloadNow *c = (struct qemu_DllCanUnloadNow *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FALSE;
}

#endif

struct qemu_DllRegisterServer
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllRegisterServer(void)
{
    struct qemu_DllRegisterServer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLREGISTERSERVER);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DllRegisterServer(struct qemu_syscall *call)
{
    struct qemu_DllRegisterServer *c = (struct qemu_DllRegisterServer *)call;
    WINE_ERR("This should not be called on the guest DLL!\n");
    c->super.iret = E_FAIL;
}

#endif

struct qemu_DllUnregisterServer
{
    struct qemu_syscall super;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRESULT WINAPI DllUnregisterServer(void)
{
    struct qemu_DllUnregisterServer call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DLLUNREGISTERSERVER);

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DllUnregisterServer(struct qemu_syscall *call)
{
    struct qemu_DllUnregisterServer *c = (struct qemu_DllUnregisterServer *)call;
    WINE_ERR("This should not be called on the guest DLL!\n");
    c->super.iret = E_FAIL;
}

#endif

