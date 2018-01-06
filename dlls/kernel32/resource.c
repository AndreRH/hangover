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
#include "qemu_kernel32.h"

#ifndef QEMU_DLL_GUEST
#include <wine/debug.h>
WINE_DEFAULT_DEBUG_CHANNEL(qemu_kernel32);
#endif


struct qemu_FindResourceExA
{
    struct qemu_syscall super;
    uint64_t hModule;
    uint64_t type;
    uint64_t name;
    uint64_t lang;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRSRC WINAPI FindResourceExA(HMODULE hModule, LPCSTR type, LPCSTR name, WORD lang)
{
    struct qemu_FindResourceExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDRESOURCEEXA);
    call.hModule = (ULONG_PTR)hModule;
    call.type = (ULONG_PTR)type;
    call.name = (ULONG_PTR)name;
    call.lang = (ULONG_PTR)lang;

    qemu_syscall(&call.super);

    return (HRSRC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindResourceExA(struct qemu_syscall *call)
{
    struct qemu_FindResourceExA *c = (struct qemu_FindResourceExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FindResourceExA(QEMU_G2H(c->hModule), QEMU_G2H(c->type), QEMU_G2H(c->name), c->lang);
}

#endif

struct qemu_FindResourceA
{
    struct qemu_syscall super;
    uint64_t hModule;
    uint64_t name;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRSRC WINAPI FindResourceA(HMODULE hModule, LPCSTR name, LPCSTR type)
{
    struct qemu_FindResourceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDRESOURCEA);
    call.hModule = (ULONG_PTR)hModule;
    call.name = (ULONG_PTR)name;
    call.type = (ULONG_PTR)type;

    qemu_syscall(&call.super);

    return (HRSRC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindResourceA(struct qemu_syscall *call)
{
    struct qemu_FindResourceA *c = (struct qemu_FindResourceA *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)FindResourceA(QEMU_G2H(c->hModule), QEMU_G2H(c->name), QEMU_G2H(c->type));
}

#endif

struct qemu_FindResourceExW
{
    struct qemu_syscall super;
    uint64_t hModule;
    uint64_t type;
    uint64_t name;
    uint64_t lang;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRSRC WINAPI FindResourceExW(HMODULE hModule, LPCWSTR type, LPCWSTR name, WORD lang)
{
    struct qemu_FindResourceExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDRESOURCEEXW);
    call.hModule = (ULONG_PTR)hModule;
    call.type = (ULONG_PTR)type;
    call.name = (ULONG_PTR)name;
    call.lang = (ULONG_PTR)lang;

    qemu_syscall(&call.super);

    return (HRSRC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindResourceExW(struct qemu_syscall *call)
{
    struct qemu_FindResourceExW *c = (struct qemu_FindResourceExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FindResourceExW(QEMU_G2H(c->hModule), QEMU_G2H(c->type), QEMU_G2H(c->name), c->lang);
}

#endif

struct qemu_FindResourceW
{
    struct qemu_syscall super;
    uint64_t hModule;
    uint64_t name;
    uint64_t type;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HRSRC WINAPI FindResourceW(HINSTANCE hModule, LPCWSTR name, LPCWSTR type)
{
    struct qemu_FindResourceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FINDRESOURCEW);
    call.hModule = (ULONG_PTR)hModule;
    call.name = (ULONG_PTR)name;
    call.type = (ULONG_PTR)type;

    qemu_syscall(&call.super);

    return (HRSRC)(ULONG_PTR)call.super.iret;
}

#else

void qemu_FindResourceW(struct qemu_syscall *call)
{
    struct qemu_FindResourceW *c = (struct qemu_FindResourceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)FindResourceW(QEMU_G2H(c->hModule), QEMU_G2H(c->name), QEMU_G2H(c->type));
}

#endif

struct qemu_EnumResourceTypesA
{
    struct qemu_syscall super;
    uint64_t hmod;
    uint64_t lpfun;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumResourceTypesA(HMODULE hmod, ENUMRESTYPEPROCA lpfun, LONG_PTR lparam)
{
    struct qemu_EnumResourceTypesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMRESOURCETYPESA);
    call.hmod = (ULONG_PTR)hmod;
    call.lpfun = (ULONG_PTR)lpfun;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumResourceTypesA(struct qemu_syscall *call)
{
    struct qemu_EnumResourceTypesA *c = (struct qemu_EnumResourceTypesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumResourceTypesA(QEMU_G2H(c->hmod), QEMU_G2H(c->lpfun), c->lparam);
}

#endif

struct qemu_EnumResourceTypesW
{
    struct qemu_syscall super;
    uint64_t hmod;
    uint64_t lpfun;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumResourceTypesW(HMODULE hmod, ENUMRESTYPEPROCW lpfun, LONG_PTR lparam)
{
    struct qemu_EnumResourceTypesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMRESOURCETYPESW);
    call.hmod = (ULONG_PTR)hmod;
    call.lpfun = (ULONG_PTR)lpfun;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumResourceTypesW(struct qemu_syscall *call)
{
    struct qemu_EnumResourceTypesW *c = (struct qemu_EnumResourceTypesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumResourceTypesW(QEMU_G2H(c->hmod), QEMU_G2H(c->lpfun), c->lparam);
}

#endif

struct qemu_EnumResourceNamesA
{
    struct qemu_syscall super;
    uint64_t hmod;
    uint64_t type;
    uint64_t lpfun;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumResourceNamesA(HMODULE hmod, LPCSTR type, ENUMRESNAMEPROCA lpfun, LONG_PTR lparam)
{
    struct qemu_EnumResourceNamesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMRESOURCENAMESA);
    call.hmod = (ULONG_PTR)hmod;
    call.type = (ULONG_PTR)type;
    call.lpfun = (ULONG_PTR)lpfun;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumResourceNamesA(struct qemu_syscall *call)
{
    struct qemu_EnumResourceNamesA *c = (struct qemu_EnumResourceNamesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumResourceNamesA(QEMU_G2H(c->hmod), QEMU_G2H(c->type), QEMU_G2H(c->lpfun), c->lparam);
}

#endif

struct qemu_EnumResourceNamesW
{
    struct qemu_syscall super;
    uint64_t hmod;
    uint64_t type;
    uint64_t lpfun;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumResourceNamesW(HMODULE hmod, LPCWSTR type, ENUMRESNAMEPROCW lpfun, LONG_PTR lparam)
{
    struct qemu_EnumResourceNamesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMRESOURCENAMESW);
    call.hmod = (ULONG_PTR)hmod;
    call.type = (ULONG_PTR)type;
    call.lpfun = (ULONG_PTR)lpfun;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumResourceNamesW(struct qemu_syscall *call)
{
    struct qemu_EnumResourceNamesW *c = (struct qemu_EnumResourceNamesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumResourceNamesW(QEMU_G2H(c->hmod), QEMU_G2H(c->type), QEMU_G2H(c->lpfun), c->lparam);
}

#endif

struct qemu_EnumResourceLanguagesExA
{
    struct qemu_syscall super;
    uint64_t hmod;
    uint64_t type;
    uint64_t name;
    uint64_t lpfun;
    uint64_t lparam;
    uint64_t flags;
    uint64_t lang;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumResourceLanguagesExA(HMODULE hmod, LPCSTR type, LPCSTR name, ENUMRESLANGPROCA lpfun, LONG_PTR lparam, DWORD flags, LANGID lang)
{
    struct qemu_EnumResourceLanguagesExA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMRESOURCELANGUAGESEXA);
    call.hmod = (ULONG_PTR)hmod;
    call.type = (ULONG_PTR)type;
    call.name = (ULONG_PTR)name;
    call.lpfun = (ULONG_PTR)lpfun;
    call.lparam = (ULONG_PTR)lparam;
    call.flags = (ULONG_PTR)flags;
    call.lang = (ULONG_PTR)lang;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumResourceLanguagesExA(struct qemu_syscall *call)
{
    struct qemu_EnumResourceLanguagesExA *c = (struct qemu_EnumResourceLanguagesExA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumResourceLanguagesExA(QEMU_G2H(c->hmod), QEMU_G2H(c->type), QEMU_G2H(c->name), QEMU_G2H(c->lpfun), c->lparam, c->flags, c->lang);
}

#endif

struct qemu_EnumResourceLanguagesA
{
    struct qemu_syscall super;
    uint64_t hmod;
    uint64_t type;
    uint64_t name;
    uint64_t lpfun;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumResourceLanguagesA(HMODULE hmod, LPCSTR type, LPCSTR name, ENUMRESLANGPROCA lpfun, LONG_PTR lparam)
{
    struct qemu_EnumResourceLanguagesA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMRESOURCELANGUAGESA);
    call.hmod = (ULONG_PTR)hmod;
    call.type = (ULONG_PTR)type;
    call.name = (ULONG_PTR)name;
    call.lpfun = (ULONG_PTR)lpfun;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumResourceLanguagesA(struct qemu_syscall *call)
{
    struct qemu_EnumResourceLanguagesA *c = (struct qemu_EnumResourceLanguagesA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumResourceLanguagesA(QEMU_G2H(c->hmod), QEMU_G2H(c->type), QEMU_G2H(c->name), QEMU_G2H(c->lpfun), c->lparam);
}

#endif

struct qemu_EnumResourceLanguagesExW
{
    struct qemu_syscall super;
    uint64_t hmod;
    uint64_t type;
    uint64_t name;
    uint64_t lpfun;
    uint64_t lparam;
    uint64_t flags;
    uint64_t lang;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumResourceLanguagesExW(HMODULE hmod, LPCWSTR type, LPCWSTR name, ENUMRESLANGPROCW lpfun, LONG_PTR lparam, DWORD flags, LANGID lang)
{
    struct qemu_EnumResourceLanguagesExW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMRESOURCELANGUAGESEXW);
    call.hmod = (ULONG_PTR)hmod;
    call.type = (ULONG_PTR)type;
    call.name = (ULONG_PTR)name;
    call.lpfun = (ULONG_PTR)lpfun;
    call.lparam = (ULONG_PTR)lparam;
    call.flags = (ULONG_PTR)flags;
    call.lang = (ULONG_PTR)lang;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumResourceLanguagesExW(struct qemu_syscall *call)
{
    struct qemu_EnumResourceLanguagesExW *c = (struct qemu_EnumResourceLanguagesExW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumResourceLanguagesExW(QEMU_G2H(c->hmod), QEMU_G2H(c->type), QEMU_G2H(c->name), QEMU_G2H(c->lpfun), c->lparam, c->flags, c->lang);
}

#endif

struct qemu_EnumResourceLanguagesW
{
    struct qemu_syscall super;
    uint64_t hmod;
    uint64_t type;
    uint64_t name;
    uint64_t lpfun;
    uint64_t lparam;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EnumResourceLanguagesW(HMODULE hmod, LPCWSTR type, LPCWSTR name, ENUMRESLANGPROCW lpfun, LONG_PTR lparam)
{
    struct qemu_EnumResourceLanguagesW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENUMRESOURCELANGUAGESW);
    call.hmod = (ULONG_PTR)hmod;
    call.type = (ULONG_PTR)type;
    call.name = (ULONG_PTR)name;
    call.lpfun = (ULONG_PTR)lpfun;
    call.lparam = (ULONG_PTR)lparam;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EnumResourceLanguagesW(struct qemu_syscall *call)
{
    struct qemu_EnumResourceLanguagesW *c = (struct qemu_EnumResourceLanguagesW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EnumResourceLanguagesW(QEMU_G2H(c->hmod), QEMU_G2H(c->type), QEMU_G2H(c->name), QEMU_G2H(c->lpfun), c->lparam);
}

#endif

struct qemu_LoadResource
{
    struct qemu_syscall super;
    uint64_t hModule;
    uint64_t hRsrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HGLOBAL WINAPI LoadResource(HINSTANCE hModule, HRSRC hRsrc)
{
    struct qemu_LoadResource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOADRESOURCE);
    call.hModule = (ULONG_PTR)hModule;
    call.hRsrc = (ULONG_PTR)hRsrc;

    qemu_syscall(&call.super);

    return (HGLOBAL)(ULONG_PTR)call.super.iret;
}

#else

void qemu_LoadResource(struct qemu_syscall *call)
{
    struct qemu_LoadResource *c = (struct qemu_LoadResource *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)LoadResource(QEMU_G2H(c->hModule), QEMU_G2H(c->hRsrc));
}

#endif

struct qemu_LockResource
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI LPVOID WINAPI LockResource(HGLOBAL handle)
{
    struct qemu_LockResource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_LOCKRESOURCE);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return (LPVOID)(ULONG_PTR)call.super.iret;
}

#else

void qemu_LockResource(struct qemu_syscall *call)
{
    struct qemu_LockResource *c = (struct qemu_LockResource *)call;
    WINE_TRACE("\n");
    c->super.iret = (ULONG_PTR)LockResource(QEMU_G2H(c->handle));
}

#endif

struct qemu_FreeResource
{
    struct qemu_syscall super;
    uint64_t handle;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI FreeResource(HGLOBAL handle)
{
    struct qemu_FreeResource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_FREERESOURCE);
    call.handle = (ULONG_PTR)handle;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_FreeResource(struct qemu_syscall *call)
{
    struct qemu_FreeResource *c = (struct qemu_FreeResource *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = FreeResource(QEMU_G2H(c->handle));
}

#endif

struct qemu_SizeofResource
{
    struct qemu_syscall super;
    uint64_t hModule;
    uint64_t hRsrc;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI DWORD WINAPI SizeofResource(HINSTANCE hModule, HRSRC hRsrc)
{
    struct qemu_SizeofResource call;
    call.super.id = QEMU_SYSCALL_ID(CALL_SIZEOFRESOURCE);
    call.hModule = (ULONG_PTR)hModule;
    call.hRsrc = (ULONG_PTR)hRsrc;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_SizeofResource(struct qemu_syscall *call)
{
    struct qemu_SizeofResource *c = (struct qemu_SizeofResource *)call;
    WINE_TRACE("\n");
    c->super.iret = SizeofResource(QEMU_G2H(c->hModule), QEMU_G2H(c->hRsrc));
}

#endif

struct qemu_BeginUpdateResourceW
{
    struct qemu_syscall super;
    uint64_t pFileName;
    uint64_t bDeleteExistingResources;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI BeginUpdateResourceW(LPCWSTR pFileName, BOOL bDeleteExistingResources)
{
    struct qemu_BeginUpdateResourceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BEGINUPDATERESOURCEW);
    call.pFileName = (ULONG_PTR)pFileName;
    call.bDeleteExistingResources = (ULONG_PTR)bDeleteExistingResources;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_BeginUpdateResourceW(struct qemu_syscall *call)
{
    struct qemu_BeginUpdateResourceW *c = (struct qemu_BeginUpdateResourceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)BeginUpdateResourceW(QEMU_G2H(c->pFileName), c->bDeleteExistingResources);
}

#endif

struct qemu_BeginUpdateResourceA
{
    struct qemu_syscall super;
    uint64_t pFileName;
    uint64_t bDeleteExistingResources;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI HANDLE WINAPI BeginUpdateResourceA(LPCSTR pFileName, BOOL bDeleteExistingResources)
{
    struct qemu_BeginUpdateResourceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_BEGINUPDATERESOURCEA);
    call.pFileName = (ULONG_PTR)pFileName;
    call.bDeleteExistingResources = (ULONG_PTR)bDeleteExistingResources;

    qemu_syscall(&call.super);

    return (HANDLE)(ULONG_PTR)call.super.iret;
}

#else

void qemu_BeginUpdateResourceA(struct qemu_syscall *call)
{
    struct qemu_BeginUpdateResourceA *c = (struct qemu_BeginUpdateResourceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = (ULONG_PTR)BeginUpdateResourceA(QEMU_G2H(c->pFileName), c->bDeleteExistingResources);
}

#endif

struct qemu_EndUpdateResourceW
{
    struct qemu_syscall super;
    uint64_t hUpdate;
    uint64_t fDiscard;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EndUpdateResourceW(HANDLE hUpdate, BOOL fDiscard)
{
    struct qemu_EndUpdateResourceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENDUPDATERESOURCEW);
    call.hUpdate = (LONG_PTR)hUpdate;
    call.fDiscard = (ULONG_PTR)fDiscard;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EndUpdateResourceW(struct qemu_syscall *call)
{
    struct qemu_EndUpdateResourceW *c = (struct qemu_EndUpdateResourceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EndUpdateResourceW(QEMU_G2H(c->hUpdate), c->fDiscard);
}

#endif

struct qemu_EndUpdateResourceA
{
    struct qemu_syscall super;
    uint64_t hUpdate;
    uint64_t fDiscard;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI EndUpdateResourceA(HANDLE hUpdate, BOOL fDiscard)
{
    struct qemu_EndUpdateResourceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_ENDUPDATERESOURCEA);
    call.hUpdate = (LONG_PTR)hUpdate;
    call.fDiscard = (ULONG_PTR)fDiscard;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_EndUpdateResourceA(struct qemu_syscall *call)
{
    struct qemu_EndUpdateResourceA *c = (struct qemu_EndUpdateResourceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = EndUpdateResourceA(QEMU_G2H(c->hUpdate), c->fDiscard);
}

#endif

struct qemu_UpdateResourceW
{
    struct qemu_syscall super;
    uint64_t hUpdate;
    uint64_t lpType;
    uint64_t lpName;
    uint64_t wLanguage;
    uint64_t lpData;
    uint64_t cbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UpdateResourceW(HANDLE hUpdate, LPCWSTR lpType, LPCWSTR lpName, WORD wLanguage, LPVOID lpData, DWORD cbData)
{
    struct qemu_UpdateResourceW call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UPDATERESOURCEW);
    call.hUpdate = (LONG_PTR)hUpdate;
    call.lpType = (ULONG_PTR)lpType;
    call.lpName = (ULONG_PTR)lpName;
    call.wLanguage = (ULONG_PTR)wLanguage;
    call.lpData = (ULONG_PTR)lpData;
    call.cbData = (ULONG_PTR)cbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UpdateResourceW(struct qemu_syscall *call)
{
    struct qemu_UpdateResourceW *c = (struct qemu_UpdateResourceW *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UpdateResourceW(QEMU_G2H(c->hUpdate), QEMU_G2H(c->lpType), QEMU_G2H(c->lpName), c->wLanguage, QEMU_G2H(c->lpData), c->cbData);
}

#endif

struct qemu_UpdateResourceA
{
    struct qemu_syscall super;
    uint64_t hUpdate;
    uint64_t lpType;
    uint64_t lpName;
    uint64_t wLanguage;
    uint64_t lpData;
    uint64_t cbData;
};

#ifdef QEMU_DLL_GUEST

WINBASEAPI BOOL WINAPI UpdateResourceA(HANDLE hUpdate, LPCSTR lpType, LPCSTR lpName, WORD wLanguage, LPVOID lpData, DWORD cbData)
{
    struct qemu_UpdateResourceA call;
    call.super.id = QEMU_SYSCALL_ID(CALL_UPDATERESOURCEA);
    call.hUpdate = (LONG_PTR)hUpdate;
    call.lpType = (ULONG_PTR)lpType;
    call.lpName = (ULONG_PTR)lpName;
    call.wLanguage = (ULONG_PTR)wLanguage;
    call.lpData = (ULONG_PTR)lpData;
    call.cbData = (ULONG_PTR)cbData;

    qemu_syscall(&call.super);

    return call.super.iret;
}

#else

void qemu_UpdateResourceA(struct qemu_syscall *call)
{
    struct qemu_UpdateResourceA *c = (struct qemu_UpdateResourceA *)call;
    WINE_FIXME("Unverified!\n");
    c->super.iret = UpdateResourceA(QEMU_G2H(c->hUpdate), QEMU_G2H(c->lpType), QEMU_G2H(c->lpName), c->wLanguage, QEMU_G2H(c->lpData), c->cbData);
}

#endif

