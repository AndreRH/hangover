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

#include "thunk/qemu_windows.h"

#include "windows-user-services.h"
#include "dll_list.h"
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
#include <wine/unicode.h>
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
    call.pActCtx = (ULONG_PTR)pActCtx;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateActCtxA(struct qemu_syscall *call)
{
    struct qemu_CreateActCtxA *c = (struct qemu_CreateActCtxA *)call;
    ACTCTXA *copy = NULL, *orig;
    struct qemu_ACTCTX *orig32;
    WCHAR *appname, *p;
    char *appnameA = NULL;

    WINE_TRACE("\n");

#if HOST_BIT == GUEST_BIT
    orig = QEMU_G2H(c->pActCtx);
    if (!orig || orig->cbSize != sizeof(*orig))
    {
        c->super.iret = (uint64_t)CreateActCtxA(orig);
        return;
    }
#else
    orig32 = QEMU_G2H(c->pActCtx);
    if (!orig32)
    {
        c->super.iret = (uint64_t)CreateActCtxA(NULL);
        return;
    }
    else if (orig32->cbSize != sizeof(*orig32))
    {
        ACTCTXA invalid = {0};
        c->super.iret = (uint64_t)CreateActCtxA(&invalid);
        return;
    }
#endif

    copy = HeapAlloc(GetProcessHeap(), 0, sizeof(*copy));
    if (!copy)
    {
        c->super.iret = 0;
        return;
    }

#if HOST_BIT == GUEST_BIT
    *copy = *orig;
#else
    ACTCTX_g2h((ACTCTXW *)copy, orig32);
#endif

    if (!(copy->dwFlags & ACTCTX_FLAG_APPLICATION_NAME_VALID))
    {
        HMODULE mod = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);
        DWORD len;

        /* FIXME: How do I allocate this right? */
        appname = HeapAlloc(GetProcessHeap(), 0, MAX_PATH * sizeof(*appname));
        len = qemu_ops->qemu_GetModuleFileName(copy->hModule, appname, MAX_PATH);

        /* Yay, if there's an app name passed in, the getter later returns the app name.
         * If there is nothing, it returns the path. So pass in the path... */
        if ((p = strrchrW(appname, '\\' ))) p[1] = 0;

        appnameA = HeapAlloc(GetProcessHeap(), 0, p - appname + 2);
        WideCharToMultiByte(CP_ACP, 0, appname, -1, appnameA, p - appname + 2, NULL, NULL);
        HeapFree(GetProcessHeap(), 0, appname);

        copy->lpApplicationName = appnameA;
        copy->dwFlags |= ACTCTX_FLAG_APPLICATION_NAME_VALID;
    }

    c->super.iret = (uint64_t)CreateActCtxA(copy);
    WINE_ERR("Last errror %u\n", GetLastError());

    HeapFree(GetProcessHeap(), 0, copy);
    HeapFree(GetProcessHeap(), 0, appnameA);
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
    call.pActCtx = (ULONG_PTR)pActCtx;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_CreateActCtxW(struct qemu_syscall *call)
{
    struct qemu_CreateActCtxW *c = (struct qemu_CreateActCtxW *)call;
    ACTCTXW *copy = NULL, *orig;
    struct qemu_ACTCTX *orig32;
    WCHAR *appname = NULL, *p;

    WINE_TRACE("\n");
    orig = QEMU_G2H(c->pActCtx);

#if HOST_BIT == GUEST_BIT
    if (!orig || orig->cbSize != sizeof(*orig))
    {
        c->super.iret = (uint64_t)CreateActCtxW(orig);
        return;
    }
#else
    orig32 = QEMU_G2H(c->pActCtx);
    if (!orig32)
    {
        c->super.iret = (uint64_t)CreateActCtxW(NULL);
        return;
    }
    else if (orig32->cbSize != sizeof(*orig32))
    {
        ACTCTXW invalid = {0};
        c->super.iret = (uint64_t)CreateActCtxW(&invalid);
        return;
    }
#endif

    copy = HeapAlloc(GetProcessHeap(), 0, sizeof(*copy));
    if (!copy)
    {
        c->super.iret = 0;
        return;
    }

#if HOST_BIT == GUEST_BIT
    *copy = *orig;
#else
    ACTCTX_g2h(copy, orig32);
#endif

    if (!(copy->dwFlags & ACTCTX_FLAG_APPLICATION_NAME_VALID))
    {
        HMODULE mod = qemu_ops->qemu_GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL);
        DWORD len;

        /* FIXME: How do I allocate this right? */
        appname = HeapAlloc(GetProcessHeap(), 0, MAX_PATH * sizeof(*appname));
        len = qemu_ops->qemu_GetModuleFileName(copy->hModule, appname, MAX_PATH);

        /* Yay, if there's an app name passed in, the getter later returns the app name.
         * If there is nothing, it returns the path. So pass in the path... */
        if ((p = strrchrW(appname, '\\' ))) p[1] = 0;
        copy->lpApplicationName = appname;
        copy->dwFlags |= ACTCTX_FLAG_APPLICATION_NAME_VALID;
    }

    c->super.iret = (uint64_t)CreateActCtxW(copy);

    HeapFree(GetProcessHeap(), 0, copy);
    HeapFree(GetProcessHeap(), 0, appname);
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
    call.hActCtx = (LONG_PTR)hActCtx;
    call.ulCookie = (ULONG_PTR)ulCookie;

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
    call.dwFlags = dwFlags;
    call.ulCookie = ulCookie;

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
    call.phActCtx = (ULONG_PTR)phActCtx;

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
    call.hActCtx = (LONG_PTR)hActCtx;

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
    call.hActCtx = (LONG_PTR)hActCtx;

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
    call.hActCtx = (LONG_PTR)hActCtx;

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
    call.dwFlags = dwFlags;
    call.lpExtGuid = (ULONG_PTR)lpExtGuid;
    call.ulId = ulId;
    call.lpSearchStr = (ULONG_PTR)lpSearchStr;
    call.pInfo = (ULONG_PTR)pInfo;

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
    call.dwFlags = dwFlags;
    call.lpExtGuid = (ULONG_PTR)lpExtGuid;
    call.ulId = ulId;
    call.lpSearchStr = (ULONG_PTR)lpSearchStr;
    call.pInfo = (ULONG_PTR)pInfo;

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
    call.dwFlags = dwFlags;
    call.lpExtGuid = (ULONG_PTR)lpExtGuid;
    call.ulId = ulId;
    call.lpSearchGuid = (ULONG_PTR)lpSearchGuid;
    call.pInfo = (ULONG_PTR)pInfo;

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
    call.dwFlags = dwFlags;
    call.hActCtx = (ULONG_PTR)hActCtx;
    call.pvSubInst = (ULONG_PTR)pvSubInst;
    call.ulClass = ulClass;
    call.pvBuff = (ULONG_PTR)pvBuff;
    call.cbBuff = cbBuff;

    qemu_syscall(&call.super);

    if (pcbLen)
        *pcbLen = call.pcbLen;

    return call.super.iret;
}

#else

void qemu_QueryActCtxW(struct qemu_syscall *call)
{
    struct qemu_QueryActCtxW *c = (struct qemu_QueryActCtxW *)call;
    ULONG class;
    SIZE_T retlen;
    void (*func)(void *, void *);

    struct
    {
        SIZE_T guest_size;
        SIZE_T host_size, host_struct_size;
        void *func;
    } convert;
    union
    {
        ACTIVATION_CONTEXT_BASIC_INFORMATION bi;
        ACTIVATION_CONTEXT_DETAILED_INFORMATION di;
        ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION adi;
        ASSEMBLY_FILE_DETAILED_INFORMATION fi;
    } host;
    char *ptr = (char *)&host.bi;

    WINE_TRACE("\n");

    class = c->ulClass;
#if GUEST_BIT == HOST_BIT
    c->super.iret = QueryActCtxW(c->dwFlags, QEMU_G2H(c->hActCtx), QEMU_G2H(c->pvSubInst), class,
            QEMU_G2H(c->pvBuff), c->cbBuff, &retlen);
    call->pcbLen = retlen;
    return;
#endif

    /* FIXME: Move all this to ntdll. */
    convert.host_size = -1;
    switch (class)
    {
        case ActivationContextBasicInformation:
            convert.guest_size = sizeof(struct qemu_ACTIVATION_CONTEXT_BASIC_INFORMATION);
            convert.host_struct_size = sizeof(host.bi);
            convert.func = ACTIVATION_CONTEXT_BASIC_INFORMATION_h2g;
            break;

        case ActivationContextDetailedInformation:
            convert.guest_size = sizeof(struct qemu_ACTIVATION_CONTEXT_DETAILED_INFORMATION);
            convert.host_struct_size = sizeof(host.di);
            convert.func = ACTIVATION_CONTEXT_DETAILED_INFORMATION_h2g;
            break;

        case AssemblyDetailedInformationInActivationContext:
            convert.guest_size = sizeof(struct qemu_ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION);
            convert.host_struct_size = sizeof(host.adi);
            convert.func = ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION_h2g;
            break;

        case FileInformationInAssemblyOfAssemblyInActivationContext:
            convert.guest_size = sizeof(struct qemu_ASSEMBLY_FILE_DETAILED_INFORMATION);
            convert.host_struct_size = sizeof(host.fi);
            convert.func = ASSEMBLY_FILE_DETAILED_INFORMATION_h2g;
            break;

        default:
            WINE_FIXME("Unhandled info class %u.\n", class);
            c->super.iret = QueryActCtxW(c->dwFlags, QEMU_G2H(c->hActCtx), QEMU_G2H(c->pvSubInst), class,
                    QEMU_G2H(c->pvBuff), c->cbBuff, &retlen);
            c->pcbLen = retlen;
            return;
    }

    c->super.iret = QueryActCtxW(c->dwFlags, QEMU_G2H(c->hActCtx), QEMU_G2H(c->pvSubInst), class,
            &host.adi, 0, &convert.host_size);
    if (!convert.host_size)
    {
        c->pcbLen = 0;
        return;
    }

    WINE_TRACE("%d: %p. sizes guest %ld, host %ld, fixed struct %ld extra %ld\n", class, QEMU_G2H(c->hActCtx),
            convert.guest_size, convert.host_size, convert.host_struct_size,
            convert.host_size - convert.host_struct_size);
    c->pcbLen = convert.guest_size + convert.host_size - convert.host_struct_size;
    if (c->cbBuff < c->pcbLen)
    {
        c->super.iret = QueryActCtxW(c->dwFlags, QEMU_G2H(c->hActCtx), QEMU_G2H(c->pvSubInst), class,
                ptr, 0, NULL);
        return;
    }

    if (convert.host_struct_size != convert.host_size)
        ptr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, convert.host_size);

    c->super.iret = QueryActCtxW(c->dwFlags, QEMU_G2H(c->hActCtx), QEMU_G2H(c->pvSubInst), class,
            ptr, convert.host_size, NULL);

    func = convert.func;
    func(QEMU_G2H(c->pvBuff), ptr);

    if (convert.host_struct_size != convert.host_size)
    {
        WINE_TRACE("Copy from host buf %p to guest buf %p, offsets %ld, %ld, size %ld\n",
                 ptr, QEMU_G2H(c->pvBuff), convert.host_struct_size, convert.guest_size,
                 convert.host_size - convert.host_struct_size);
        memcpy((char *)QEMU_G2H(c->pvBuff) + convert.guest_size, ptr + convert.host_struct_size,
                convert.host_size - convert.host_struct_size);

        switch (class)
        {
            case ActivationContextDetailedInformation:
            {
                struct qemu_ACTIVATION_CONTEXT_DETAILED_INFORMATION *g = QEMU_G2H(c->pvBuff);
                if (g->lpRootManifestPath)
                    g->lpRootManifestPath = g->lpRootManifestPath - (ULONG_PTR)ptr - convert.host_struct_size
                        + (ULONG_PTR)g + convert.guest_size;
                if (g->lpRootConfigurationPath)
                    g->lpRootConfigurationPath = g->lpRootConfigurationPath - (ULONG_PTR)ptr - convert.host_struct_size
                        + (ULONG_PTR)g + convert.guest_size;
                if (g->lpAppDirPath)
                    g->lpAppDirPath = g->lpAppDirPath - (ULONG_PTR)ptr - convert.host_struct_size
                        + (ULONG_PTR)g + convert.guest_size;
                break;
            }

            case AssemblyDetailedInformationInActivationContext:
            {
                struct qemu_ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION *g = QEMU_G2H(c->pvBuff);
                if (g->lpAssemblyEncodedAssemblyIdentity)
                    g->lpAssemblyEncodedAssemblyIdentity = g->lpAssemblyEncodedAssemblyIdentity
                        - (ULONG_PTR)ptr - convert.host_struct_size
                        + (ULONG_PTR)g + convert.guest_size;
                if (g->lpAssemblyManifestPath)
                    g->lpAssemblyManifestPath = g->lpAssemblyManifestPath - (ULONG_PTR)ptr - convert.host_struct_size
                        + (ULONG_PTR)g + convert.guest_size;
                if (g->lpAssemblyPolicyPath)
                    g->lpAssemblyPolicyPath = g->lpAssemblyPolicyPath - (ULONG_PTR)ptr - convert.host_struct_size
                        + (ULONG_PTR)g + convert.guest_size;
                if (g->lpAssemblyDirectoryName)
                    g->lpAssemblyDirectoryName = g->lpAssemblyDirectoryName - (ULONG_PTR)ptr - convert.host_struct_size
                        + (ULONG_PTR)g + convert.guest_size;
                break;
            }

            case FileInformationInAssemblyOfAssemblyInActivationContext:
            {
                struct qemu_ASSEMBLY_FILE_DETAILED_INFORMATION *g = QEMU_G2H(c->pvBuff);
                if (g->lpFileName)
                    g->lpFileName = g->lpFileName - (ULONG_PTR)ptr - convert.host_struct_size
                        + (ULONG_PTR)g + convert.guest_size;
                if (g->lpFilePath)
                    g->lpFilePath = g->lpFilePath - (ULONG_PTR)ptr - convert.host_struct_size
                        + (ULONG_PTR)g + convert.guest_size;

                /* Yeah, apparently this info class sets the size to 0 on success... */
                c->pcbLen = 0;
                break;
            }

        }

        HeapFree(GetProcessHeap(), 0, ptr);
    }
}

#endif

