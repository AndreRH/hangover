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
#include "kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_CreateActCtxA
{
    struct qemu_syscall super;
    uint64_t pActCtx;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateActCtxA(PCACTCTXA pActCtx)
{
    struct qemu_CreateActCtxA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEACTCTXA);
    call.pActCtx = (uint64_t)pActCtx;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateActCtxA(struct qemu_syscall *call)
{
    struct qemu_CreateActCtxA *c = (struct qemu_CreateActCtxA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateActCtxA(QEMU_G2H(c->pActCtx));
}

#endif

struct qemu_CreateActCtxW
{
    struct qemu_syscall super;
    uint64_t pActCtx;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI CreateActCtxW(PCACTCTXW pActCtx)
{
    struct qemu_CreateActCtxW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_CREATEACTCTXW);
    call.pActCtx = (uint64_t)pActCtx;

    qemu_syscall(&call.super);

    return (HANDLE)call.super.iret;
}

#else

void qemu_CreateActCtxW(struct qemu_syscall *call)
{
    struct qemu_CreateActCtxW *c = (struct qemu_CreateActCtxW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (uint64_t)CreateActCtxW(QEMU_G2H(c->pActCtx));
}

#endif

struct qemu_ActivateActCtx
{
    struct qemu_syscall super;
    uint64_t hActCtx;
    uint64_t ulCookie;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ActivateActCtx(HANDLE hActCtx, ULONG_PTR *ulCookie)
{
    struct qemu_ActivateActCtx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ACTIVATEACTCTX);
    call.hActCtx = (uint64_t)hActCtx;
    call.ulCookie = (uint64_t)ulCookie;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ActivateActCtx(struct qemu_syscall *call)
{
    struct qemu_ActivateActCtx *c = (struct qemu_ActivateActCtx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ActivateActCtx(QEMU_G2H(c->hActCtx), QEMU_G2H(c->ulCookie));
}

#endif

struct qemu_DeactivateActCtx
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t ulCookie;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI DeactivateActCtx(DWORD dwFlags, ULONG_PTR ulCookie)
{
    struct qemu_DeactivateActCtx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_DEACTIVATEACTCTX);
    call.dwFlags = (uint64_t)dwFlags;
    call.ulCookie = (uint64_t)ulCookie;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_DeactivateActCtx(struct qemu_syscall *call)
{
    struct qemu_DeactivateActCtx *c = (struct qemu_DeactivateActCtx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = DeactivateActCtx(c->dwFlags, c->ulCookie);
}

#endif

struct qemu_GetCurrentActCtx
{
    struct qemu_syscall super;
    uint64_t phActCtx;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI GetCurrentActCtx(HANDLE* phActCtx)
{
    struct qemu_GetCurrentActCtx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_GETCURRENTACTCTX);
    call.phActCtx = (uint64_t)phActCtx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_GetCurrentActCtx(struct qemu_syscall *call)
{
    struct qemu_GetCurrentActCtx *c = (struct qemu_GetCurrentActCtx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = GetCurrentActCtx(QEMU_G2H(c->phActCtx));
}

#endif

struct qemu_AddRefActCtx
{
    struct qemu_syscall super;
    uint64_t hActCtx;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI AddRefActCtx(HANDLE hActCtx)
{
    struct qemu_AddRefActCtx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ADDREFACTCTX);
    call.hActCtx = (uint64_t)hActCtx;

    qemu_syscall(&call.super);
}

#else

void qemu_AddRefActCtx(struct qemu_syscall *call)
{
    struct qemu_AddRefActCtx *c = (struct qemu_AddRefActCtx *)call;
    WINE_FIXME("Unverified!\n");
    AddRefActCtx(QEMU_G2H(c->hActCtx));
}

#endif

struct qemu_ReleaseActCtx
{
    struct qemu_syscall super;
    uint64_t hActCtx;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI void WINAPI ReleaseActCtx(HANDLE hActCtx)
{
    struct qemu_ReleaseActCtx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_RELEASEACTCTX);
    call.hActCtx = (uint64_t)hActCtx;

    qemu_syscall(&call.super);
}

#else

void qemu_ReleaseActCtx(struct qemu_syscall *call)
{
    struct qemu_ReleaseActCtx *c = (struct qemu_ReleaseActCtx *)call;
    WINE_FIXME("Unverified!\n");
    ReleaseActCtx(QEMU_G2H(c->hActCtx));
}

#endif

struct qemu_ZombifyActCtx
{
    struct qemu_syscall super;
    uint64_t hActCtx;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI ZombifyActCtx(HANDLE hActCtx)
{
    struct qemu_ZombifyActCtx call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ZOMBIFYACTCTX);
    call.hActCtx = (uint64_t)hActCtx;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_ZombifyActCtx(struct qemu_syscall *call)
{
    struct qemu_ZombifyActCtx *c = (struct qemu_ZombifyActCtx *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = ZombifyActCtx(QEMU_G2H(c->hActCtx));
}

#endif

struct qemu_FindActCtxSectionStringA
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t lpExtGuid;
    uint64_t ulId;
    uint64_t lpSearchStr;
    uint64_t pInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindActCtxSectionStringA(DWORD dwFlags, const GUID* lpExtGuid, ULONG ulId, LPCSTR lpSearchStr, PACTCTX_SECTION_KEYED_DATA pInfo)
{
    struct qemu_FindActCtxSectionStringA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDACTCTXSECTIONSTRINGA);
    call.dwFlags = (uint64_t)dwFlags;
    call.lpExtGuid = (uint64_t)lpExtGuid;
    call.ulId = (uint64_t)ulId;
    call.lpSearchStr = (uint64_t)lpSearchStr;
    call.pInfo = (uint64_t)pInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindActCtxSectionStringA(struct qemu_syscall *call)
{
    struct qemu_FindActCtxSectionStringA *c = (struct qemu_FindActCtxSectionStringA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindActCtxSectionStringA(c->dwFlags, QEMU_G2H(c->lpExtGuid), c->ulId, QEMU_G2H(c->lpSearchStr), QEMU_G2H(c->pInfo));
}

#endif

struct qemu_FindActCtxSectionStringW
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t lpExtGuid;
    uint64_t ulId;
    uint64_t lpSearchStr;
    uint64_t pInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindActCtxSectionStringW(DWORD dwFlags, const GUID* lpExtGuid, ULONG ulId, LPCWSTR lpSearchStr, PACTCTX_SECTION_KEYED_DATA pInfo)
{
    struct qemu_FindActCtxSectionStringW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDACTCTXSECTIONSTRINGW);
    call.dwFlags = (uint64_t)dwFlags;
    call.lpExtGuid = (uint64_t)lpExtGuid;
    call.ulId = (uint64_t)ulId;
    call.lpSearchStr = (uint64_t)lpSearchStr;
    call.pInfo = (uint64_t)pInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindActCtxSectionStringW(struct qemu_syscall *call)
{
    struct qemu_FindActCtxSectionStringW *c = (struct qemu_FindActCtxSectionStringW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindActCtxSectionStringW(c->dwFlags, QEMU_G2H(c->lpExtGuid), c->ulId, QEMU_G2H(c->lpSearchStr), QEMU_G2H(c->pInfo));
}

#endif

struct qemu_FindActCtxSectionGuid
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t lpExtGuid;
    uint64_t ulId;
    uint64_t lpSearchGuid;
    uint64_t pInfo;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FindActCtxSectionGuid(DWORD dwFlags, const GUID* lpExtGuid, ULONG ulId, const GUID* lpSearchGuid, PACTCTX_SECTION_KEYED_DATA pInfo)
{
    struct qemu_FindActCtxSectionGuid call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDACTCTXSECTIONGUID);
    call.dwFlags = (uint64_t)dwFlags;
    call.lpExtGuid = (uint64_t)lpExtGuid;
    call.ulId = (uint64_t)ulId;
    call.lpSearchGuid = (uint64_t)lpSearchGuid;
    call.pInfo = (uint64_t)pInfo;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FindActCtxSectionGuid(struct qemu_syscall *call)
{
    struct qemu_FindActCtxSectionGuid *c = (struct qemu_FindActCtxSectionGuid *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FindActCtxSectionGuid(c->dwFlags, QEMU_G2H(c->lpExtGuid), c->ulId, QEMU_G2H(c->lpSearchGuid), QEMU_G2H(c->pInfo));
}

#endif

struct qemu_QueryActCtxW
{
    struct qemu_syscall super;
    uint64_t dwFlags;
    uint64_t hActCtx;
    uint64_t pvSubInst;
    uint64_t ulClass;
    uint64_t pvBuff;
    uint64_t cbBuff;
    uint64_t pcbLen;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI QueryActCtxW(DWORD dwFlags, HANDLE hActCtx, PVOID pvSubInst, ULONG ulClass, PVOID pvBuff, SIZE_T cbBuff, SIZE_T *pcbLen)
{
    struct qemu_QueryActCtxW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_QUERYACTCTXW);
    call.dwFlags = (uint64_t)dwFlags;
    call.hActCtx = (uint64_t)hActCtx;
    call.pvSubInst = (uint64_t)pvSubInst;
    call.ulClass = (uint64_t)ulClass;
    call.pvBuff = (uint64_t)pvBuff;
    call.cbBuff = (uint64_t)cbBuff;
    call.pcbLen = (uint64_t)pcbLen;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_QueryActCtxW(struct qemu_syscall *call)
{
    struct qemu_QueryActCtxW *c = (struct qemu_QueryActCtxW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = QueryActCtxW(c->dwFlags, QEMU_G2H(c->hActCtx), QEMU_G2H(c->pvSubInst), c->ulClass, QEMU_G2H(c->pvBuff), c->cbBuff, QEMU_G2H(c->pcbLen));
}

#endif

