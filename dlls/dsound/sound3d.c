/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
 *
 * buffer library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * buffer library is distributed in the hope that it will be useful,
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

#ifdef QEMU_DLL_GUEST
#include <debug.h>
#else
#include <wine/debug.h>
#endif

WINE_DEFAULT_DEBUG_CHANNEL(qemu_dsound);

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_QueryInterface(IDirectSound3DBuffer *iface, REFIID riid, void **obj)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);

    WINE_TRACE("(%p, %s, %p)\n", buffer, wine_dbgstr_guid(riid), obj);

    return IDirectSoundBuffer8_QueryInterface(&buffer->IDirectSoundBuffer8_iface, riid, obj);
}

static ULONG WINAPI IDirectSound3DBufferImpl_AddRef(IDirectSound3DBuffer *iface)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    ULONG ref = InterlockedIncrement(&buffer->ref_3d);

    WINE_TRACE("(%p) ref was %d\n", buffer, ref - 1);

    if(ref == 1)
        InterlockedIncrement(&buffer->iface_count);

    return ref;
}

static ULONG WINAPI IDirectSound3DBufferImpl_Release(IDirectSound3DBuffer *iface)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    ULONG ref = InterlockedDecrement(&buffer->ref_3d);

    WINE_TRACE("(%p) ref was %d\n", buffer, ref + 1);

    if (!ref && !InterlockedDecrement(&buffer->iface_count))
        secondarybuffer_destroy(buffer);

    return ref;
}

#endif

struct qemu_IDirectSound3DBufferImpl_GetAllParameters
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpDs3dBuffer;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_GetAllParameters(IDirectSound3DBuffer *iface, DS3DBUFFER *lpDs3dBuffer)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_GetAllParameters call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_GETALLPARAMETERS);
    call.iface = (ULONG_PTR)buffer;
    call.lpDs3dBuffer = (ULONG_PTR)lpDs3dBuffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_GetAllParameters(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_GetAllParameters *c = (struct qemu_IDirectSound3DBufferImpl_GetAllParameters *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_GetAllParameters(buffer->host_3d_buffer, QEMU_G2H(c->lpDs3dBuffer));
}

#endif

struct qemu_IDirectSound3DBufferImpl_GetConeAngles
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdwInsideConeAngle;
    uint64_t lpdwOutsideConeAngle;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_GetConeAngles(IDirectSound3DBuffer *iface, DWORD *lpdwInsideConeAngle, DWORD *lpdwOutsideConeAngle)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_GetConeAngles call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_GETCONEANGLES);
    call.iface = (ULONG_PTR)buffer;
    call.lpdwInsideConeAngle = (ULONG_PTR)lpdwInsideConeAngle;
    call.lpdwOutsideConeAngle = (ULONG_PTR)lpdwOutsideConeAngle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_GetConeAngles(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_GetConeAngles *c = (struct qemu_IDirectSound3DBufferImpl_GetConeAngles *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_GetConeAngles(buffer->host_3d_buffer, QEMU_G2H(c->lpdwInsideConeAngle), QEMU_G2H(c->lpdwOutsideConeAngle));
}

#endif

struct qemu_IDirectSound3DBufferImpl_GetConeOrientation
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpvConeOrientation;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_GetConeOrientation(IDirectSound3DBuffer *iface, D3DVECTOR *lpvConeOrientation)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_GetConeOrientation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_GETCONEORIENTATION);
    call.iface = (ULONG_PTR)buffer;
    call.lpvConeOrientation = (ULONG_PTR)lpvConeOrientation;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_GetConeOrientation(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_GetConeOrientation *c = (struct qemu_IDirectSound3DBufferImpl_GetConeOrientation *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_GetConeOrientation(buffer->host_3d_buffer, QEMU_G2H(c->lpvConeOrientation));
}

#endif

struct qemu_IDirectSound3DBufferImpl_GetConeOutsideVolume
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lplConeOutsideVolume;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_GetConeOutsideVolume(IDirectSound3DBuffer *iface, LONG *lplConeOutsideVolume)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_GetConeOutsideVolume call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_GETCONEOUTSIDEVOLUME);
    call.iface = (ULONG_PTR)buffer;
    call.lplConeOutsideVolume = (ULONG_PTR)lplConeOutsideVolume;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_GetConeOutsideVolume(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_GetConeOutsideVolume *c = (struct qemu_IDirectSound3DBufferImpl_GetConeOutsideVolume *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_GetConeOutsideVolume(buffer->host_3d_buffer, QEMU_G2H(c->lplConeOutsideVolume));
}

#endif

struct qemu_IDirectSound3DBufferImpl_GetMaxDistance
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpfMaxDistance;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_GetMaxDistance(IDirectSound3DBuffer *iface, D3DVALUE *lpfMaxDistance)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_GetMaxDistance call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_GETMAXDISTANCE);
    call.iface = (ULONG_PTR)buffer;
    call.lpfMaxDistance = (ULONG_PTR)lpfMaxDistance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_GetMaxDistance(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_GetMaxDistance *c = (struct qemu_IDirectSound3DBufferImpl_GetMaxDistance *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_GetMaxDistance(buffer->host_3d_buffer, QEMU_G2H(c->lpfMaxDistance));
}

#endif

struct qemu_IDirectSound3DBufferImpl_GetMinDistance
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpfMinDistance;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_GetMinDistance(IDirectSound3DBuffer *iface, D3DVALUE *lpfMinDistance)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_GetMinDistance call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_GETMINDISTANCE);
    call.iface = (ULONG_PTR)buffer;
    call.lpfMinDistance = (ULONG_PTR)lpfMinDistance;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_GetMinDistance(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_GetMinDistance *c = (struct qemu_IDirectSound3DBufferImpl_GetMinDistance *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_GetMinDistance(buffer->host_3d_buffer, QEMU_G2H(c->lpfMinDistance));
}

#endif

struct qemu_IDirectSound3DBufferImpl_GetMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpdwMode;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_GetMode(IDirectSound3DBuffer *iface, DWORD *lpdwMode)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_GetMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_GETMODE);
    call.iface = (ULONG_PTR)buffer;
    call.lpdwMode = (ULONG_PTR)lpdwMode;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_GetMode(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_GetMode *c = (struct qemu_IDirectSound3DBufferImpl_GetMode *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_GetMode(buffer->host_3d_buffer, QEMU_G2H(c->lpdwMode));
}

#endif

struct qemu_IDirectSound3DBufferImpl_GetPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpvPosition;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_GetPosition(IDirectSound3DBuffer *iface, D3DVECTOR *lpvPosition)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_GetPosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_GETPOSITION);
    call.iface = (ULONG_PTR)buffer;
    call.lpvPosition = (ULONG_PTR)lpvPosition;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_GetPosition(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_GetPosition *c = (struct qemu_IDirectSound3DBufferImpl_GetPosition *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_GetPosition(buffer->host_3d_buffer, QEMU_G2H(c->lpvPosition));
}

#endif

struct qemu_IDirectSound3DBufferImpl_GetVelocity
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpvVelocity;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_GetVelocity(IDirectSound3DBuffer *iface, D3DVECTOR *lpvVelocity)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_GetVelocity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_GETVELOCITY);
    call.iface = (ULONG_PTR)buffer;
    call.lpvVelocity = (ULONG_PTR)lpvVelocity;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_GetVelocity(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_GetVelocity *c = (struct qemu_IDirectSound3DBufferImpl_GetVelocity *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_GetVelocity(buffer->host_3d_buffer, QEMU_G2H(c->lpvVelocity));
}

#endif

struct qemu_IDirectSound3DBufferImpl_SetAllParameters
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpcDs3dBuffer;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_SetAllParameters(IDirectSound3DBuffer *iface, const DS3DBUFFER *lpcDs3dBuffer, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_SetAllParameters call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_SETALLPARAMETERS);
    call.iface = (ULONG_PTR)buffer;
    call.lpcDs3dBuffer = (ULONG_PTR)lpcDs3dBuffer;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_SetAllParameters(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_SetAllParameters *c = (struct qemu_IDirectSound3DBufferImpl_SetAllParameters *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_SetAllParameters(buffer->host_3d_buffer, QEMU_G2H(c->lpcDs3dBuffer), c->dwApply);
}

#endif

struct qemu_IDirectSound3DBufferImpl_SetConeAngles
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwInsideConeAngle;
    uint64_t dwOutsideConeAngle;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_SetConeAngles(IDirectSound3DBuffer *iface, DWORD dwInsideConeAngle, DWORD dwOutsideConeAngle, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_SetConeAngles call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_SETCONEANGLES);
    call.iface = (ULONG_PTR)buffer;
    call.dwInsideConeAngle = dwInsideConeAngle;
    call.dwOutsideConeAngle = dwOutsideConeAngle;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_SetConeAngles(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_SetConeAngles *c = (struct qemu_IDirectSound3DBufferImpl_SetConeAngles *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_SetConeAngles(buffer->host_3d_buffer, c->dwInsideConeAngle, c->dwOutsideConeAngle, c->dwApply);
}

#endif

struct qemu_IDirectSound3DBufferImpl_SetConeOrientation
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
    uint64_t z;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_SetConeOrientation(IDirectSound3DBuffer *iface, D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_SetConeOrientation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_SETCONEORIENTATION);
    call.iface = (ULONG_PTR)buffer;
    call.x = x;
    call.y = y;
    call.z = z;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_SetConeOrientation(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_SetConeOrientation *c = (struct qemu_IDirectSound3DBufferImpl_SetConeOrientation *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_SetConeOrientation(buffer->host_3d_buffer, c->x, c->y, c->z, c->dwApply);
}

#endif

struct qemu_IDirectSound3DBufferImpl_SetConeOutsideVolume
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lConeOutsideVolume;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_SetConeOutsideVolume(IDirectSound3DBuffer *iface, LONG lConeOutsideVolume, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_SetConeOutsideVolume call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_SETCONEOUTSIDEVOLUME);
    call.iface = (ULONG_PTR)buffer;
    call.lConeOutsideVolume = lConeOutsideVolume;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_SetConeOutsideVolume(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_SetConeOutsideVolume *c = (struct qemu_IDirectSound3DBufferImpl_SetConeOutsideVolume *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_SetConeOutsideVolume(buffer->host_3d_buffer, c->lConeOutsideVolume, c->dwApply);
}

#endif

struct qemu_IDirectSound3DBufferImpl_SetMaxDistance
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fMaxDistance;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_SetMaxDistance(IDirectSound3DBuffer *iface, D3DVALUE fMaxDistance, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_SetMaxDistance call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_SETMAXDISTANCE);
    call.iface = (ULONG_PTR)buffer;
    call.fMaxDistance = fMaxDistance;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_SetMaxDistance(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_SetMaxDistance *c = (struct qemu_IDirectSound3DBufferImpl_SetMaxDistance *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_SetMaxDistance(buffer->host_3d_buffer, c->fMaxDistance, c->dwApply);
}

#endif

struct qemu_IDirectSound3DBufferImpl_SetMinDistance
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fMinDistance;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_SetMinDistance(IDirectSound3DBuffer *iface, D3DVALUE fMinDistance, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_SetMinDistance call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_SETMINDISTANCE);
    call.iface = (ULONG_PTR)buffer;
    call.fMinDistance = fMinDistance;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_SetMinDistance(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_SetMinDistance *c = (struct qemu_IDirectSound3DBufferImpl_SetMinDistance *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_SetMinDistance(buffer->host_3d_buffer, c->fMinDistance, c->dwApply);
}

#endif

struct qemu_IDirectSound3DBufferImpl_SetMode
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t dwMode;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_SetMode(IDirectSound3DBuffer *iface, DWORD dwMode, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_SetMode call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_SETMODE);
    call.iface = (ULONG_PTR)buffer;
    call.dwMode = dwMode;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_SetMode(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_SetMode *c = (struct qemu_IDirectSound3DBufferImpl_SetMode *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_SetMode(buffer->host_3d_buffer, c->dwMode, c->dwApply);
}

#endif

struct qemu_IDirectSound3DBufferImpl_SetPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
    uint64_t z;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_SetPosition(IDirectSound3DBuffer *iface, D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_SetPosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_SETPOSITION);
    call.iface = (ULONG_PTR)buffer;
    call.x = x;
    call.y = y;
    call.z = z;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_SetPosition(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_SetPosition *c = (struct qemu_IDirectSound3DBufferImpl_SetPosition *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_SetPosition(buffer->host_3d_buffer, c->x, c->y, c->z, c->dwApply);
}

#endif

struct qemu_IDirectSound3DBufferImpl_SetVelocity
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
    uint64_t z;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DBufferImpl_SetVelocity(IDirectSound3DBuffer *iface, D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DBuffer(iface);
    struct qemu_IDirectSound3DBufferImpl_SetVelocity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DBUFFERIMPL_SETVELOCITY);
    call.iface = (ULONG_PTR)buffer;
    call.x = x;
    call.y = y;
    call.z = z;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DBufferImpl_SetVelocity(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DBufferImpl_SetVelocity *c = (struct qemu_IDirectSound3DBufferImpl_SetVelocity *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DBuffer_SetVelocity(buffer->host_3d_buffer, c->x, c->y, c->z, c->dwApply);
}

#endif

#ifdef QEMU_DLL_GUEST

const IDirectSound3DBufferVtbl buffer_3d_vtbl =
{
    /* IUnknown methods */
    IDirectSound3DBufferImpl_QueryInterface,
    IDirectSound3DBufferImpl_AddRef,
    IDirectSound3DBufferImpl_Release,
    /* IDirectSound3DBuffer methods */
    IDirectSound3DBufferImpl_GetAllParameters,
    IDirectSound3DBufferImpl_GetConeAngles,
    IDirectSound3DBufferImpl_GetConeOrientation,
    IDirectSound3DBufferImpl_GetConeOutsideVolume,
    IDirectSound3DBufferImpl_GetMaxDistance,
    IDirectSound3DBufferImpl_GetMinDistance,
    IDirectSound3DBufferImpl_GetMode,
    IDirectSound3DBufferImpl_GetPosition,
    IDirectSound3DBufferImpl_GetVelocity,
    IDirectSound3DBufferImpl_SetAllParameters,
    IDirectSound3DBufferImpl_SetConeAngles,
    IDirectSound3DBufferImpl_SetConeOrientation,
    IDirectSound3DBufferImpl_SetConeOutsideVolume,
    IDirectSound3DBufferImpl_SetMaxDistance,
    IDirectSound3DBufferImpl_SetMinDistance,
    IDirectSound3DBufferImpl_SetMode,
    IDirectSound3DBufferImpl_SetPosition,
    IDirectSound3DBufferImpl_SetVelocity,
};

#endif

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_QueryInterface(IDirectSound3DListener *iface, REFIID riid, void **obj)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);

    WINE_TRACE("(%p,%s,%p)\n", iface, wine_dbgstr_guid(riid), obj);

    return IDirectSoundBuffer_QueryInterface(&buffer->IDirectSoundBuffer8_iface, riid, obj);
}

static ULONG WINAPI IDirectSound3DListenerImpl_AddRef(IDirectSound3DListener *iface)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    ULONG ref = InterlockedIncrement(&buffer->ref_3d);

    WINE_TRACE("(%p) ref was %d\n", buffer, ref - 1);

    if(ref == 1)
        InterlockedIncrement(&buffer->iface_count);

    return ref;
}

static ULONG WINAPI IDirectSound3DListenerImpl_Release(IDirectSound3DListener *iface)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    ULONG ref;

    ref = capped_refcount_dec(&buffer->ref_3d);
    if(!ref)
        capped_refcount_dec(&buffer->iface_count);

    WINE_TRACE("(%p) ref is now %d\n", buffer, ref);

    return ref;
}

#endif

struct qemu_IDirectSound3DListenerImpl_GetAllParameter
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpDS3DL;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_GetAllParameter(IDirectSound3DListener *iface, DS3DLISTENER *lpDS3DL)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_GetAllParameter call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_GETALLPARAMETER);
    call.iface = (ULONG_PTR)buffer;
    call.lpDS3DL = (ULONG_PTR)lpDS3DL;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_GetAllParameter(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_GetAllParameter *c = (struct qemu_IDirectSound3DListenerImpl_GetAllParameter *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_GetAllParameters(buffer->host_3d_listener, QEMU_G2H(c->lpDS3DL));
}

#endif

struct qemu_IDirectSound3DListenerImpl_GetDistanceFactor
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpfDistanceFactor;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_GetDistanceFactor(IDirectSound3DListener *iface, D3DVALUE *lpfDistanceFactor)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_GetDistanceFactor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_GETDISTANCEFACTOR);
    call.iface = (ULONG_PTR)buffer;
    call.lpfDistanceFactor = (ULONG_PTR)lpfDistanceFactor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_GetDistanceFactor(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_GetDistanceFactor *c = (struct qemu_IDirectSound3DListenerImpl_GetDistanceFactor *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_GetDistanceFactor(buffer->host_3d_listener, QEMU_G2H(c->lpfDistanceFactor));
}

#endif

struct qemu_IDirectSound3DListenerImpl_GetDopplerFactor
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpfDopplerFactor;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_GetDopplerFactor(IDirectSound3DListener *iface, D3DVALUE *lpfDopplerFactor)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_GetDopplerFactor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_GETDOPPLERFACTOR);
    call.iface = (ULONG_PTR)buffer;
    call.lpfDopplerFactor = (ULONG_PTR)lpfDopplerFactor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_GetDopplerFactor(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_GetDopplerFactor *c = (struct qemu_IDirectSound3DListenerImpl_GetDopplerFactor *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_GetDopplerFactor(buffer->host_3d_listener, QEMU_G2H(c->lpfDopplerFactor));
}

#endif

struct qemu_IDirectSound3DListenerImpl_GetOrientation
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpvOrientFront;
    uint64_t lpvOrientTop;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_GetOrientation(IDirectSound3DListener *iface, D3DVECTOR *lpvOrientFront, D3DVECTOR *lpvOrientTop)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_GetOrientation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_GETORIENTATION);
    call.iface = (ULONG_PTR)buffer;
    call.lpvOrientFront = (ULONG_PTR)lpvOrientFront;
    call.lpvOrientTop = (ULONG_PTR)lpvOrientTop;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_GetOrientation(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_GetOrientation *c = (struct qemu_IDirectSound3DListenerImpl_GetOrientation *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_GetOrientation(buffer->host_3d_listener, QEMU_G2H(c->lpvOrientFront), QEMU_G2H(c->lpvOrientTop));
}

#endif

struct qemu_IDirectSound3DListenerImpl_GetPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpvPosition;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_GetPosition(IDirectSound3DListener *iface, D3DVECTOR *lpvPosition)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_GetPosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_GETPOSITION);
    call.iface = (ULONG_PTR)buffer;
    call.lpvPosition = (ULONG_PTR)lpvPosition;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_GetPosition(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_GetPosition *c = (struct qemu_IDirectSound3DListenerImpl_GetPosition *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_GetPosition(buffer->host_3d_listener, QEMU_G2H(c->lpvPosition));
}

#endif

struct qemu_IDirectSound3DListenerImpl_GetRolloffFactor
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpfRolloffFactor;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_GetRolloffFactor(IDirectSound3DListener *iface, D3DVALUE *lpfRolloffFactor)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_GetRolloffFactor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_GETROLLOFFFACTOR);
    call.iface = (ULONG_PTR)buffer;
    call.lpfRolloffFactor = (ULONG_PTR)lpfRolloffFactor;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_GetRolloffFactor(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_GetRolloffFactor *c = (struct qemu_IDirectSound3DListenerImpl_GetRolloffFactor *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_GetRolloffFactor(buffer->host_3d_listener, QEMU_G2H(c->lpfRolloffFactor));
}

#endif

struct qemu_IDirectSound3DListenerImpl_GetVelocity
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpvVelocity;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_GetVelocity(IDirectSound3DListener *iface, D3DVECTOR *lpvVelocity)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_GetVelocity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_GETVELOCITY);
    call.iface = (ULONG_PTR)buffer;
    call.lpvVelocity = (ULONG_PTR)lpvVelocity;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_GetVelocity(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_GetVelocity *c = (struct qemu_IDirectSound3DListenerImpl_GetVelocity *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_GetVelocity(buffer->host_3d_listener, QEMU_G2H(c->lpvVelocity));
}

#endif

struct qemu_IDirectSound3DListenerImpl_SetAllParameters
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t lpcDS3DL;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_SetAllParameters(IDirectSound3DListener *iface, const DS3DLISTENER *lpcDS3DL, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_SetAllParameters call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_SETALLPARAMETERS);
    call.iface = (ULONG_PTR)buffer;
    call.lpcDS3DL = (ULONG_PTR)lpcDS3DL;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_SetAllParameters(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_SetAllParameters *c = (struct qemu_IDirectSound3DListenerImpl_SetAllParameters *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_SetAllParameters(buffer->host_3d_listener, QEMU_G2H(c->lpcDS3DL), c->dwApply);
}

#endif

struct qemu_IDirectSound3DListenerImpl_SetDistanceFactor
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fDistanceFactor;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_SetDistanceFactor(IDirectSound3DListener *iface, D3DVALUE fDistanceFactor, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_SetDistanceFactor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_SETDISTANCEFACTOR);
    call.iface = (ULONG_PTR)buffer;
    call.fDistanceFactor = fDistanceFactor;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_SetDistanceFactor(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_SetDistanceFactor *c = (struct qemu_IDirectSound3DListenerImpl_SetDistanceFactor *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_SetDistanceFactor(buffer->host_3d_listener, c->fDistanceFactor, c->dwApply);
}

#endif

struct qemu_IDirectSound3DListenerImpl_SetDopplerFactor
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fDopplerFactor;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_SetDopplerFactor(IDirectSound3DListener *iface, D3DVALUE fDopplerFactor, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_SetDopplerFactor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_SETDOPPLERFACTOR);
    call.iface = (ULONG_PTR)buffer;
    call.fDopplerFactor = fDopplerFactor;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_SetDopplerFactor(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_SetDopplerFactor *c = (struct qemu_IDirectSound3DListenerImpl_SetDopplerFactor *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_SetDopplerFactor(buffer->host_3d_listener, c->fDopplerFactor, c->dwApply);
}

#endif

struct qemu_IDirectSound3DListenerImpl_SetOrientation
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t xFront;
    uint64_t yFront;
    uint64_t zFront;
    uint64_t xTop;
    uint64_t yTop;
    uint64_t zTop;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_SetOrientation(IDirectSound3DListener *iface, D3DVALUE xFront, D3DVALUE yFront, D3DVALUE zFront, D3DVALUE xTop, D3DVALUE yTop, D3DVALUE zTop, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_SetOrientation call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_SETORIENTATION);
    call.iface = (ULONG_PTR)buffer;
    call.xFront = xFront;
    call.yFront = yFront;
    call.zFront = zFront;
    call.xTop = xTop;
    call.yTop = yTop;
    call.zTop = zTop;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_SetOrientation(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_SetOrientation *c = (struct qemu_IDirectSound3DListenerImpl_SetOrientation *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_SetOrientation(buffer->host_3d_listener, c->xFront, c->yFront, c->zFront, c->xTop, c->yTop, c->zTop, c->dwApply);
}

#endif

struct qemu_IDirectSound3DListenerImpl_SetPosition
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
    uint64_t z;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_SetPosition(IDirectSound3DListener *iface, D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_SetPosition call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_SETPOSITION);
    call.iface = (ULONG_PTR)buffer;
    call.x = x;
    call.y = y;
    call.z = z;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_SetPosition(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_SetPosition *c = (struct qemu_IDirectSound3DListenerImpl_SetPosition *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_SetPosition(buffer->host_3d_listener, c->x, c->y, c->z, c->dwApply);
}

#endif

struct qemu_IDirectSound3DListenerImpl_SetRolloffFactor
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t fRolloffFactor;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_SetRolloffFactor(IDirectSound3DListener *iface, D3DVALUE fRolloffFactor, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_SetRolloffFactor call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_SETROLLOFFFACTOR);
    call.iface = (ULONG_PTR)buffer;
    call.fRolloffFactor = fRolloffFactor;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_SetRolloffFactor(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_SetRolloffFactor *c = (struct qemu_IDirectSound3DListenerImpl_SetRolloffFactor *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_SetRolloffFactor(buffer->host_3d_listener, c->fRolloffFactor, c->dwApply);
}

#endif

struct qemu_IDirectSound3DListenerImpl_SetVelocity
{
    struct qemu_syscall super;
    uint64_t iface;
    uint64_t x;
    uint64_t y;
    uint64_t z;
    uint64_t dwApply;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_SetVelocity(IDirectSound3DListener *iface, D3DVALUE x, D3DVALUE y, D3DVALUE z, DWORD dwApply)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_SetVelocity call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_SETVELOCITY);
    call.iface = (ULONG_PTR)buffer;
    call.x = x;
    call.y = y;
    call.z = z;
    call.dwApply = dwApply;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_SetVelocity(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_SetVelocity *c = (struct qemu_IDirectSound3DListenerImpl_SetVelocity *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_SetVelocity(buffer->host_3d_listener, c->x, c->y, c->z, c->dwApply);
}

#endif

struct qemu_IDirectSound3DListenerImpl_CommitDeferredSettings
{
    struct qemu_syscall super;
    uint64_t iface;
};

#ifdef QEMU_DLL_GUEST

static HRESULT WINAPI IDirectSound3DListenerImpl_CommitDeferredSettings(IDirectSound3DListener *iface)
{
    struct qemu_dsound_buffer *buffer = impl_from_IDirectSound3DListener(iface);
    struct qemu_IDirectSound3DListenerImpl_CommitDeferredSettings call;
    call.super.id = QEMU_SYSCALL_ID(CALL_IDIRECTSOUND3DLISTENERIMPL_COMMITDEFERREDSETTINGS);
    call.iface = (ULONG_PTR)buffer;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_IDirectSound3DListenerImpl_CommitDeferredSettings(struct qemu_syscall *call)
{
    struct qemu_IDirectSound3DListenerImpl_CommitDeferredSettings *c = (struct qemu_IDirectSound3DListenerImpl_CommitDeferredSettings *)call;
    struct qemu_dsound_buffer *buffer;

    WINE_FIXME("Unverified!\n");
    buffer = QEMU_G2H(c->iface);

    c->super.iret = IDirectSound3DListener_CommitDeferredSettings(buffer->host_3d_listener);
}

#endif

#ifdef QEMU_DLL_GUEST

const IDirectSound3DListenerVtbl listener_3d_vtbl =
{
    /* IUnknown methods */
    IDirectSound3DListenerImpl_QueryInterface,
    IDirectSound3DListenerImpl_AddRef,
    IDirectSound3DListenerImpl_Release,
    /* IDirectSound3DListener methods */
    IDirectSound3DListenerImpl_GetAllParameter,
    IDirectSound3DListenerImpl_GetDistanceFactor,
    IDirectSound3DListenerImpl_GetDopplerFactor,
    IDirectSound3DListenerImpl_GetOrientation,
    IDirectSound3DListenerImpl_GetPosition,
    IDirectSound3DListenerImpl_GetRolloffFactor,
    IDirectSound3DListenerImpl_GetVelocity,
    IDirectSound3DListenerImpl_SetAllParameters,
    IDirectSound3DListenerImpl_SetDistanceFactor,
    IDirectSound3DListenerImpl_SetDopplerFactor,
    IDirectSound3DListenerImpl_SetOrientation,
    IDirectSound3DListenerImpl_SetPosition,
    IDirectSound3DListenerImpl_SetRolloffFactor,
    IDirectSound3DListenerImpl_SetVelocity,
    IDirectSound3DListenerImpl_CommitDeferredSettings,
};

#endif
